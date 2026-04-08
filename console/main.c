#include "myBigChars.h"
#include "myReadKey.h"
#include "mySimpleComputer.h"
#include "myTerm.h"
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define FONT_SIZE 18
#define DEFAULT_FONT "font.bin"
#define DEFAULT_SAVEFILE "memory.bin"

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
static int current_cell = 0;

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
  bc_box (MEM_BOX_ROW, MEM_BOX_COL, MEM_BOX_H, MEM_BOX_W, WHITE, BLACK,
          "Оперативная память", RED, BLACK);

  bc_box (ACC_BOX_ROW, ACC_BOX_COL, ACC_BOX_H, ACC_BOX_W, WHITE, BLACK,
          "Аккумулятор", RED, BLACK);

  bc_box (FLAGS_BOX_ROW, FLAGS_BOX_COL, FLAGS_BOX_H, FLAGS_BOX_W, WHITE, BLACK,
          "Регистр флагов", RED, BLACK);

  bc_box (IC_BOX_ROW, IC_BOX_COL, IC_BOX_H, IC_BOX_W, WHITE, BLACK,
          "Счетчик команд", RED, BLACK);

  bc_box (CMD_BOX_ROW, CMD_BOX_COL, CMD_BOX_H, CMD_BOX_W, WHITE, BLACK,
          "Команда", RED, BLACK);

  bc_box (BIGCELL_BOX_ROW, BIGCELL_BOX_COL, BIGCELL_BOX_H, BIGCELL_BOX_W,
          WHITE, BLACK, "Редактируемая ячейка (увеличено)", RED, WHITE);

  bc_box (DECODE_BOX_ROW, DECODE_BOX_COL, DECODE_BOX_H, DECODE_BOX_W, WHITE,
          BLACK, "Редактируемая ячейка (формат)", RED, WHITE);

  bc_box (CACHE_BOX_ROW, CACHE_BOX_COL, CACHE_BOX_H, CACHE_BOX_W, WHITE, BLACK,
          "Кеш процессора", GREEN, WHITE);

  bc_box (INOUT_BOX_ROW, INOUT_BOX_COL, INOUT_BOX_H, INOUT_BOX_W, WHITE, BLACK,
          "IN--OUT", GREEN, WHITE);

  bc_box (KEYS_BOX_ROW, KEYS_BOX_COL, KEYS_BOX_H, KEYS_BOX_W, WHITE, BLACK,
          "Клавиши", GREEN, WHITE);
}

static void
print_keys (void)
{
  mt_setfgcolor (WHITE);
  mt_setbgcolor (BLACK);
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

static void
printBigCell (void)
{
  int raw;
  sc_memoryGet (current_cell, &raw);

  int sign = (raw >> 14) & 0x01;
  int high7 = (raw >> 7) & 0x7F;
  int low7 = raw & 0x7F;

  int sign_idx = sign ? 17 : 16;
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

  mt_gotoXY (BIGCELL_CHAR_ROW + 8, BIGCELL_BOX_COL + 2);
  mt_setfgcolor (BLUE);
  mt_setbgcolor (BLACK);
  printf ("Номер редактируемой ячейки: %03d", current_cell);
  fflush (stdout);
  mt_setdefaultcolor ();
}

static void
update_current_cell_display (void)
{
  int raw;
  sc_memoryGet (current_cell, &raw);
  printDecodedCommand (raw);
  printBigCell ();
}

static void
draw_all_cells (void)
{
  for (int i = 0; i < SC_MEMORY_SIZE; i++)
    {
      if (i == current_cell)
        printCell (i, BLACK, GREEN);
      else
        printCell (i, WHITE, BLACK);
    }
}

static void
redraw_all (void)
{
  mt_clrscr ();
  draw_boxes ();
  draw_all_cells ();
  printAccumulator ();
  printFlags ();
  printCounters ();
  printCommand ();
  update_current_cell_display ();
  print_keys ();
  fflush (stdout);
}

static void
move_cursor (int new_cell)
{
  if (new_cell < 0 || new_cell >= SC_MEMORY_SIZE)
    return;

  int old_cell = current_cell;
  current_cell = new_cell;

  printCell (old_cell, WHITE, BLACK);

  printCell (current_cell, BLACK, GREEN);

  update_current_cell_display ();
}

static void
handle_arrow (enum keys key)
{
  int row = current_cell / MEMORY_COLS_NUM;
  int col = current_cell % MEMORY_COLS_NUM;
  int total_rows = (SC_MEMORY_SIZE + MEMORY_COLS_NUM - 1) / MEMORY_COLS_NUM;

  switch (key)
    {
    case KEY_LEFT:
      col--;
      if (col < 0)
        col = MEMORY_COLS_NUM - 1;
      break;
    case KEY_RIGHT:
      col++;
      if (col >= MEMORY_COLS_NUM)
        col = 0;
      break;
    case KEY_UP:
      row--;
      if (row < 0)
        row = total_rows - 1;
      break;
    case KEY_DOWN:
      row++;
      if (row >= total_rows)
        row = 0;
      break;
    default:
      return;
    }

  int new_cell = row * MEMORY_COLS_NUM + col;

  if (new_cell >= SC_MEMORY_SIZE)
    {
      if (key == KEY_DOWN)
        new_cell = col;
      else if (key == KEY_RIGHT)
        new_cell = row * MEMORY_COLS_NUM;
      else if (key == KEY_LEFT)
        new_cell = SC_MEMORY_SIZE - 1;
      else
        new_cell = SC_MEMORY_SIZE - 1;
    }

  if (new_cell < 0)
    new_cell = 0;
  if (new_cell >= SC_MEMORY_SIZE)
    new_cell = SC_MEMORY_SIZE - 1;

  move_cursor (new_cell);
}

static void
edit_cell_inplace (int address)
{
  int row = MEMORY_ROW + (address / MEMORY_COLS_NUM);
  int col = MEMORY_COL + (address % MEMORY_COLS_NUM) * 6;

  mt_gotoXY (row, col);
  mt_setfgcolor (BLACK);
  mt_setbgcolor (YELLOW);
  mt_setcursorvisible (1);
  fflush (stdout);

  int new_value = 0;
  int rc = rk_readvalue (&new_value, 0);

  mt_setcursorvisible (0);

  if (rc == 0)
    {
      sc_memorySet (address, new_value);
      printTerm (address, 0);
    }

  printCell (address, BLACK, GREEN);
  update_current_cell_display ();
  printCommand ();
  fflush (stdout);
}

static void
edit_accumulator_inplace (void)
{
  mt_gotoXY (ACC_ROW, ACC_COL + 4);
  mt_setfgcolor (BLACK);
  mt_setbgcolor (YELLOW);
  mt_setcursorvisible (1);
  fflush (stdout);

  int new_value = 0;
  int rc = rk_readvalue (&new_value, 0);

  mt_setcursorvisible (0);

  if (rc == 0)
    {
      sc_accumulatorSet (new_value);
    }

  printAccumulator ();
  fflush (stdout);
}

static void
edit_icounter_inplace (void)
{
  mt_gotoXY (IC_ROW, IC_COL + 12);
  mt_setfgcolor (BLACK);
  mt_setbgcolor (YELLOW);
  mt_setcursorvisible (1);
  fflush (stdout);

  int new_value = 0;
  int rc = rk_readvalue (&new_value, 0);

  mt_setcursorvisible (0);

  if (rc == 0)
    {
      sc_icounterSet (new_value);
    }

  printCounters ();
  printCommand ();
  fflush (stdout);
}

static void
do_load (void)
{
  if (sc_memoryLoad (DEFAULT_SAVEFILE) == 0)
    {
      redraw_all ();
    }
}

static void
do_save (void)
{
  sc_memorySave (DEFAULT_SAVEFILE);
}

static void
do_reset (void)
{
  sc_memoryInit ();
  sc_regInit ();
  sc_accumulatorInit ();
  sc_icounterInit ();
  current_cell = 0;
  redraw_all ();
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
      fprintf (stderr, "Ошибка: не удалось определить размер терминала.\n");
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
      fprintf (stderr, "Ошибка: не удалось загрузить шрифт из '%s'.\n",
               font_file);
      return 1;
    }

  rk_mytermsave ();
  rk_mytermregime (1, 0, 1, 0, 0);

  sc_memoryInit ();
  sc_accumulatorInit ();
  sc_icounterInit ();
  sc_regInit ();

  mt_clrscr ();
  mt_setcursorvisible (0);
  setbuf (stdout, NULL);

  redraw_all ();

  enum keys key;
  int running = 1;

  while (running)
    {
      if (rk_readkey (&key) != 0)
        continue;

      switch (key)
        {
        case KEY_UP:
        case KEY_DOWN:
        case KEY_LEFT:
        case KEY_RIGHT:
          handle_arrow (key);
          break;

        case KEY_ENTER:
          edit_cell_inplace (current_cell);
          break;

        case KEY_ESC:
          running = 0;
          break;

        case KEY_F5:
          edit_accumulator_inplace ();
          break;

        case KEY_F6:
          edit_icounter_inplace ();
          break;

        case KEY_L:
          do_load ();
          break;

        case KEY_S:
          do_save ();
          break;

        case KEY_I:
          do_reset ();
          break;

        default:
          break;
        }
    }

  mt_gotoXY (MIN_ROWS, 1);
  mt_setcursorvisible (1);
  mt_setdefaultcolor ();
  rk_mytermrestore ();

  return 0;
}