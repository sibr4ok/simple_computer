#include "mySimpleComputer.h"
#include "myReadKey.h"
#include "sc.h"
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

extern int ALU(int command, int operand);

void CU(void)
{
    int value, sign, command, operand;
    int jump_occurred = 0; // Флаг для отслеживания команд перехода

    // Проверяем флаг игнорирования тактов
    if (sc_flags & SC_FLAG_IGNORE_PULSE) {
        return;
    }

    // Получаем команду из памяти по адресу счетчика команд
    if (sc_memoryGet(sc_icounter, &value) != 0) {
        sc_regSet(SC_FLAG_OUT_OF_MEMORY, 1);
        sc_regSet(SC_FLAG_IGNORE_PULSE, 1);
        return;
    }

    // Декодируем команду
    if (sc_commandDecode(value, &sign, &command, &operand) != 0) {
        sc_regSet(SC_FLAG_INVALID_CMD, 1);
        sc_regSet(SC_FLAG_IGNORE_PULSE, 1);
        return;
    }

    // Проверяем валидность команды
    if (sc_commandValidate(command) != 0) {
        sc_regSet(SC_FLAG_INVALID_CMD, 1);
        sc_regSet(SC_FLAG_IGNORE_PULSE, 1);
        return;
    }

    // Обработка команд ввода-вывода и управления
    if (command < 0x14) {
        switch (command) {
            case SC_CMD_NOP:
                // Ничего не делаем
                break;

            case SC_CMD_CPUINFO:
                // Вывод информации об авторах внизу консоли
                mt_gotoXY(MIN_ROWS, 1);
                mt_setfgcolor(WHITE);
                mt_setbgcolor(BLACK);
                printf("%-*s", MIN_COLS, "");
                mt_gotoXY(MIN_ROWS, 1);
                printf("Ромашко Дмитрий, Рудиш Тимофей, Бурим Кирилл, ИП 414");
                fflush(stdout);
                mt_setdefaultcolor();
                break;

            case SC_CMD_READ: {
                // Ввод с терминала
                int input_value;

                // Убираем O_NONBLOCK для блокирующего ввода
                int flags = fcntl(STDIN_FILENO, F_GETFL, 0);
                fcntl(STDIN_FILENO, F_SETFL, flags & ~O_NONBLOCK);

                // Определяем позицию для ввода: если история заполнена - внизу, иначе - на первой свободной строке
                int count = getInoutCount();
                int input_row = (count >= INOUT_LINES) ? (INOUT_ROW + INOUT_LINES - 1) : (INOUT_ROW + count);

                // Показываем приглашение для ввода
                mt_gotoXY(input_row, INOUT_COL);
                mt_setfgcolor(WHITE);
                mt_setbgcolor(BLACK);
                printf("%02x< ", operand);
                fflush(stdout);
                mt_setcursorvisible(1);

                // Временно восстанавливаем нормальный режим терминала для ввода
                rk_mytermregime(0, 0, 1, 1, 0);
                if (scanf("%d", &input_value) != 1) {
                    sc_regSet(SC_FLAG_INVALID_CMD, 1);
                    rk_mytermregime(1, 0, 0, 0, 0);
                    fcntl(STDIN_FILENO, F_SETFL, flags | O_NONBLOCK);
                    mt_setcursorvisible(0);
                    // Очищаем строку ввода
                    mt_gotoXY(input_row, INOUT_COL);
                    printf("         ");
                    fflush(stdout);
                    break;
                }
                rk_mytermregime(1, 0, 0, 0, 0);

                // Восстанавливаем O_NONBLOCK
                fcntl(STDIN_FILENO, F_SETFL, flags | O_NONBLOCK);
                mt_setcursorvisible(0);

                // Очищаем строку ввода
                mt_gotoXY(input_row, INOUT_COL);
                printf("         ");
                fflush(stdout);

                if (input_value < SC_VALUE_MIN || input_value > SC_VALUE_MAX) {
                    sc_regSet(SC_FLAG_OVERFLOW, 1);
                    break;
                }
                int raw_value = sc_from_decimal(input_value);
                sc_memorySet(operand, raw_value);

                // Добавляем в историю через printTerm (input=1 для READ)
                printTerm(operand, 1);

                mt_setdefaultcolor();
                break;
            }

            case SC_CMD_WRITE: {
                // Вывод на терминал
                int output_value;
                if (sc_memoryGet(operand, &output_value) == 0) {
                    // Добавляем в историю через printTerm (input=0 для WRITE)
                    printTerm(operand, 0);
                }
                break;
            }
        }
    }
    // Команды загрузки/выгрузки и арифметические операции
    else if (command >= 0x14 && command < 0x28) {
        switch (command) {
            case SC_CMD_LOAD: {
                // Загрузка в аккумулятор
                int mem_value;
                if (sc_memoryGet(operand, &mem_value) == 0) {
                    sc_accumulatorSet(mem_value);
                }
                break;
            }

            case SC_CMD_STORE:
                // Выгрузка из аккумулятора
                sc_memorySet(operand, sc_accumulator);
                break;

            case SC_CMD_ADD:
            case SC_CMD_SUB:
            case SC_CMD_DIVIDE:
            case SC_CMD_MUL:
                // Арифметические операции через ALU
                if (ALU(command, operand) != 0) {
                    sc_regSet(SC_FLAG_IGNORE_PULSE, 1);
                }
                break;
        }
    }
    // Команды передачи управления
    else if (command >= 0x28 && command < 0x2C) {
        switch (command) {
            case SC_CMD_JUMP:
                sc_icounterSet(operand);
                jump_occurred = 1;
                break;

            case SC_CMD_JNEG:
                if (sc_to_signed(sc_accumulator) < 0) {
                    sc_icounterSet(operand);
                    jump_occurred = 1;
                }
                break;

            case SC_CMD_JZ:
                if (sc_accumulator == 0) {
                    sc_icounterSet(operand);
                    jump_occurred = 1;
                }
                break;

            case SC_CMD_HALT:
                sc_regSet(SC_FLAG_IGNORE_PULSE, 1);
                break;
        }
    }
    // Пользовательские функции
    else if (command >= 0x33 && command < 0x50) {
        if (ALU(command, operand) != 0) {
            sc_regSet(SC_FLAG_IGNORE_PULSE, 1);
        }
    }
    else {
        sc_regSet(SC_FLAG_INVALID_CMD, 1);
        sc_regSet(SC_FLAG_IGNORE_PULSE, 1);
    }

    // Увеличиваем счетчик команд только если не было перехода
    if (!jump_occurred) {
        sc_icounter++;
        if (sc_icounter >= SC_MEMORY_SIZE) {
            sc_icounter = 0;
        }
    }
}
