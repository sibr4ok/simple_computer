#include "mySimpleComputer.h"
#include "sc.h"

int ALU(int command, int operand)
{
    int mem_value;
    int acc_signed, mem_signed, result;

    if (sc_memoryGet(operand, &mem_value) != 0) {
        sc_regSet(SC_FLAG_OUT_OF_MEMORY, 1);
        return -1;
    }

    switch (command) {
        case SC_CMD_ADD: {
            acc_signed = sc_to_signed(sc_accumulator);
            mem_signed = sc_to_signed(mem_value);
            result = acc_signed + mem_signed;

            if (result > SC_VALUE_MAX || result < SC_VALUE_MIN) {
                sc_regSet(SC_FLAG_OVERFLOW, 1);
                return -1;
            }
            sc_accumulatorSet(sc_from_decimal(result));
            break;
        }

        case SC_CMD_SUB: {
            acc_signed = sc_to_signed(sc_accumulator);
            mem_signed = sc_to_signed(mem_value);
            result = acc_signed - mem_signed;

            if (result > SC_VALUE_MAX || result < SC_VALUE_MIN) {
                sc_regSet(SC_FLAG_OVERFLOW, 1);
                return -1;
            }
            sc_accumulatorSet(sc_from_decimal(result));
            break;
        }

        case SC_CMD_DIVIDE: {
            acc_signed = sc_to_signed(sc_accumulator);
            mem_signed = sc_to_signed(mem_value);

            if (mem_signed == 0) {
                sc_regSet(SC_FLAG_DIVISION_ZERO, 1);
                return -1;
            }

            result = acc_signed / mem_signed;

            if (result > SC_VALUE_MAX || result < SC_VALUE_MIN) {
                sc_regSet(SC_FLAG_OVERFLOW, 1);
                return -1;
            }
            sc_accumulatorSet(sc_from_decimal(result));
            break;
        }

        case SC_CMD_MUL: {
            acc_signed = sc_to_signed(sc_accumulator);
            mem_signed = sc_to_signed(mem_value);
            result = acc_signed * mem_signed;

            if (result > SC_VALUE_MAX || result < SC_VALUE_MIN) {
                sc_regSet(SC_FLAG_OVERFLOW, 1);
                return -1;
            }
            sc_accumulatorSet(sc_from_decimal(result));
            break;
        }

        case SC_CMD_NOT: {
            int inverted = ((~sc_accumulator) + 1) & 0x7FFF;
            sc_memorySet(operand, inverted);
            break;
        }

        case SC_CMD_AND: {
            int result_and = (sc_accumulator & mem_value) & 0x7FFF;
            sc_accumulatorSet(result_and);
            break;
        }

        case SC_CMD_OR: {
            int result_or = (sc_accumulator | mem_value) & 0x7FFF;
            sc_accumulatorSet(result_or);
            break;
        }

        case SC_CMD_XOR: {
            int result_xor = (sc_accumulator ^ mem_value) & 0x7FFF;
            sc_accumulatorSet(result_xor);
            break;
        }

        default:
            sc_regSet(SC_FLAG_INVALID_CMD, 1);
            return -1;
    }

    return 0;
}
