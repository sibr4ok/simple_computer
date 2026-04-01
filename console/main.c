#include "myBigChars.h"
#include "mySimpleComputer.h"
#include "myTerm.h"
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define FONT_SIZE 18
#define DEFAULT_FONT "font.bin"

#define TEST_FL_OVERFLOW 0
#define TEST_FL_DIVZERO 0
#define TEST_FL_OUTMEM 0
#define TEST_FL_IGNORE 1
#define TEST_FL_INVCMD 1

#define TEST_EDIT_CELL 0

#define MEM_BOX_ROW 1
#define MEM_BOX_COL 1
#define MEM_BOX_H 15
#define MEM_BOX_W 62

#define ACC_BOX_ROW 1
#define ACC_BOX_COL 63
#define ACC_BOX_H 3
#define ACC_BOX_W 23          

#define FLAGS_BOX_ROW 1
#define FLAGS_BOX_COL 86      
#define FLAGS_BOX_H 3
#define FLAGS_BOX_W 18        

#define IC_BOX_ROW 4
#define IC_BOX_COL 63
#define IC_BOX_H 3
#define IC_BOX_W 23

#define CMD_BOX_ROW 4
#define CMD_BOX_COL 86
#define CMD_BOX_H 3
#define CMD_BOX_W 18

#define BIGCELL_BOX_ROW 7
#define BIGCELL_BOX_COL 63
#define BIGCELL_BOX_H 12
#define BIGCELL_BOX_W 41      

#define DECODE_BOX_ROW 16
#define DECODE_BOX_COL 1
#define DECODE_BOX_H 3
#define DECODE_BOX_W 62

#define CACHE_BOX_ROW 19
#define CACHE_BOX_COL 1
#define CACHE_BOX_H 7
#define CACHE_BOX_W 62

#define INOUT_BOX_ROW 19
#define INOUT_BOX_COL 63
#define INOUT_BOX_H 7
#define INOUT_BOX_W 11        

#define KEYS_BOX_ROW 19
#define KEYS_BOX_COL 74       
#define KEYS_BOX_H 7
#define KEYS_BOX_W 30         

#define BIGCELL_CHAR_ROW 9
#define BIGCELL_CHAR_COL 66

static int bigfont[FONT_SIZE][2];

static int
load_font (const char *filename)
{
  int fd = open (filename, O_RDONLY);
  if (fd < 0)
    return -1;

  int count = 0;
  if (bc_bigcharread (fd, (int *)bigfont, FONT_SIZE, &count) != 0
      || count != FONT_SIZE)
    {
      close (fd);
      return -1;
    }
  close (fd);
  return 0;
}

static void
draw_boxes (void)
{
  /* Оперативная память */
  bc_box (MEM_BOX_ROW, MEM_BOX_COL, MEM_BOX_H, MEM_BOX_W, WHITE, BLACK,
          "Оперативная память", RED, BLACK);

  /* Аккумулятор */
  bc_box (ACC_BOX_ROW, ACC_BOX_COL, ACC_BOX_H, ACC_BOX_W, WHITE, BLACK,
          "Аккумулятор", RED, BLACK);

  /* Регистр флагов */
  bc_box (FLAGS_BOX_ROW, FLAGS_BOX_COL, FLAGS_BOX_H, FLAGS_BOX_W, WHITE,
          BLACK, "Регистр флагов", RED, BLACK);

  /* Счетчик команд */
  bc_box (IC_BOX_ROW, IC_BOX_COL, IC_BOX_H, IC_BOX_W, WHITE, BLACK,
          "Счетчик команд", RED, BLACK);

  /* Команда */
  bc_box (CMD_BOX_ROW, CMD_BOX_COL, CMD_BOX_H, CMD_BOX_W, WHITE, BLACK,
          "Команда", RED, BLACK);

  /* Редактируемая ячейка (увеличено) */
  bc_box (BIGCELL_BOX_ROW, BIGCELL_BOX_COL, BIGCELL_BOX_H, BIGCELL_BOX_W,
          WHITE, BLACK, "Редактируемая ячейка (увеличено)", RED, WHITE);

  /* Редактируемая ячейка (формат) */
  bc_box (DECODE_BOX_ROW, DECODE_BOX_COL, DECODE_BOX_H, DECODE_BOX_W, WHITE,
          BLACK, "Редактируемая ячейка (формат)", RED, WHITE);

  /* Кеш процессора */
  bc_box (CACHE_BOX_ROW, CACHE_BOX_COL, CACHE_BOX_H, CACHE_BOX_W, WHITE,
          BLACK, "Кеш процессора", GREEN, WHITE);

  /* IN--OUT */
  bc_box (INOUT_BOX_ROW, INOUT_BOX_COL, INOUT_BOX_H, INOUT_BOX_W, WHITE,
          BLACK, "IN--OUT", GREEN, WHITE);

  /* Клавиши */
  bc_box (KEYS_BOX_ROW, KEYS_BOX_COL, KEYS_BOX_H, KEYS_BOX_W, WHITE, BLACK,
          "Клавиши", GREEN, WHITE);
}

static void
print_keys (void)
{
  mt_setfgcolor (WHITE);
  mt_gotoXY (KEYS_BOX_ROW + 1, KEYS_BOX_COL + 1); 
  printf ("l - load  s - save i - reset");
  mt_gotoXY (KEYS_BOX_ROW + 2, KEYS_BOX_COL + 1);
  printf ("r - run   t - step");
  mt_gotoXY (KEYS_BOX_ROW + 3, KEYS_BOX_COL + 1);
  printf ("ESC - выход");
  mt_gotoXY (KEYS_BOX_ROW + 4, KEYS_BOX_COL + 1);
  printf ("F5  - accumulator");
  mt_gotoXY (KEYS_BOX_ROW + 5, KEYS_BOX_COL + 1);
  printf ("F6  - instr cntr");
  fflush (stdout);
  mt_setdefaultcolor ();
}


static int
hex_to_fontidx (int hex_digit)
{
  if (hex_digit >= 0 && hex_digit <= 15)
    return hex_digit;
  return 0;
}

void
printBigCell (void)
{
  int raw;
  sc_memoryGet (TEST_EDIT_CELL, &raw);

  int sign = (raw >> 14) & 0x01;
  int high7 = (raw >> 7) & 0x7F;
  int low7 = raw & 0x7F;

  /* 5 big chars: sign, h1, h0, l1, l0 */
  int sign_idx = sign ? 17 : 16; /* '-' or '+' */
  int h1 = hex_to_fontidx ((high7 >> 4) & 0x0F);
  int h0 = hex_to_fontidx (high7 & 0x0F);
  int l1 = hex_to_fontidx ((low7 >> 4) & 0x0F);
  int l0 = hex_to_fontidx (low7 & 0x0F);

  int digits[5] = { sign_idx, h1, h0, l1, l0 };

  for (int i = 0; i < 5; i++)
    {
      bc_printbigchar (bigfont[digits[i]], BIGCELL_CHAR_ROW,
                       BIGCELL_CHAR_COL + i * 7, WHITE, BLACK);
    }

  /* Номер редактируемой ячейки */
  mt_gotoXY (BIGCELL_CHAR_ROW + 8, BIGCELL_BOX_COL + 2);
  mt_setfgcolor (BLUE);
  printf ("Номер редактируемой ячейки: %03d", TEST_EDIT_CELL);
  fflush (stdout);
  mt_setdefaultcolor ();
}

int
main (int argc, char *argv[])
{
  int rows, cols;
  const char *font_file = DEFAULT_FONT;

  if (argc > 1)
    font_file = argv[1];

  if (!isatty (STDOUT_FILENO))
    {
      fprintf (stderr, "Ошибка: вывод не является терминалом.\n");
      return 1;
    }

  if (mt_getscreensize (&rows, &cols) != 0)
    {
      fprintf (stderr,
               "Ошибка: не удалось определить размер терминала.\n");
      return 1;
    }
  if (rows < MIN_ROWS || cols < MIN_COLS)
    {
      fprintf (stderr,
               "Ошибка: размер терминала %dx%d, "
               "требуется минимум %dx%d.\n",
               cols, rows, MIN_COLS, MIN_ROWS);
      return 1;
    }

  if (load_font (font_file) != 0)
    {
      fprintf (stderr,
               "Ошибка: не удалось загрузить шрифт из '%s'.\n",
               font_file);
      return 1;
    }

  sc_memoryInit ();
  sc_accumulatorInit ();
  sc_icounterInit ();
  sc_regInit ();

  sc_memorySet (0, SC_VAL (0, 0x34, 0x34));
  sc_memorySet (1, SC_VAL (0, 0x10, 0x00));
  sc_memorySet (2, SC_VAL (0, 0x11, 0x02));
  sc_memorySet (3, SC_VAL (0, 0x11, 0x03));
  sc_memorySet (4, SC_VAL (0, 0x11, 0x04));
  sc_memorySet (5, SC_VAL (0, 0x11, 0x05));
  sc_memorySet (6, SC_VAL (0, 0x11, 0x06));
  sc_memorySet (7, SC_VAL (0, 0x11, 0x07));
  sc_memorySet (8, SC_VAL (0, 0x11, 0x08));
  sc_memorySet (9, SC_VAL (0, 0x11, 0x09));
  sc_memorySet (10, SC_VAL (0, 0x11, 0x20));
  sc_memorySet (11, SC_VAL (0, 0x11, 0x39));
  sc_memorySet (12, SC_VAL (0, 0x11, 0x40));
  sc_memorySet (13, SC_VAL (0, 0x11, 0x57));
  sc_memorySet (14, SC_VAL (0, 0x00, 0x01));
  sc_memorySet (15, SC_VAL (0, 0x20, 0x7F));
  sc_memorySet (16, SC_VAL (0, 0x30, 0x7E));
  sc_memorySet (50, SC_VAL (0, 0x03, 0x7F));
  sc_memorySet (125, SC_VAL (0, 0x00, 0x01));
  sc_memorySet (127, SC_VAL (0, 0x7F, 0x7F));
  sc_memorySet (126, sc_from_decimal (-2));

  sc_accumulatorSet (sc_from_decimal (-2));
  sc_icounterSet (126);
  sc_regSet (SC_FLAG_OVERFLOW, TEST_FL_OVERFLOW);
  sc_regSet (SC_FLAG_DIVISION_ZERO, TEST_FL_DIVZERO);
  sc_regSet (SC_FLAG_OUT_OF_MEMORY, TEST_FL_OUTMEM);
  sc_regSet (SC_FLAG_IGNORE_PULSE, TEST_FL_IGNORE);
  sc_regSet (SC_FLAG_INVALID_CMD, TEST_FL_INVCMD);

  mt_clrscr ();
  mt_setcursorvisible (0);
  setbuf (stdout, NULL);

  /* Draw all pseudo-graphic boxes */
  draw_boxes ();

  /* Print memory cells */
  for (int i = 0; i < SC_MEMORY_SIZE; i++)
    {
      if (i == TEST_EDIT_CELL)
        printCell (i, BLACK, WHITE);
      else
        printCell (i, WHITE, BLACK);
    }

  printAccumulator ();
  printFlags ();
  printCounters ();
  printCommand ();

  printTerm (0, 0);
  printTerm (1, 0);
  printTerm (2, 0);
  printTerm (124, 0);
  printTerm (125, 0);
  printTerm (126, 0);
  printTerm (127, 0);

  int raw;
  sc_memoryGet (TEST_EDIT_CELL, &raw);
  printDecodedCommand (raw);

  /* Print big cell */
  printBigCell ();

  /* Print keys help */
  print_keys ();

  mt_gotoXY (MIN_ROWS, 1);
  mt_setcursorvisible (1);
  mt_setdefaultcolor ();

  return 0;
}