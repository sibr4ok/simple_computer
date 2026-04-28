#include "mySimpleComputer.h"
#include "sc.h"
#include <signal.h>

extern void CU(void);

void IRC(int signum)
{
    (void)signum;

    if (signum == SIGALRM) {

        if (sc_flags & SC_FLAG_IGNORE_PULSE) {
            return;
        }

        CU();

        int current_ic;
        sc_icounterGet(&current_ic);

        printAccumulator();
        printCounters();
        printFlags();
        printCommand();

        if (current_ic > 0 && current_ic - 1 < SC_MEMORY_SIZE) {
            printCell(current_ic - 1, WHITE, BLACK);
        }
        if (current_ic >= 0 && current_ic < SC_MEMORY_SIZE) {
            printCell(current_ic, BLACK, GREEN);
        }
    }
    else if (signum == SIGUSR1) {
        sc_memoryInit();
        sc_regInit();
        sc_accumulatorInit();
        sc_icounterInit();

        mt_clrscr();
        resetTerm();

        for (int i = 0; i < SC_MEMORY_SIZE; i++) {
            printCell(i, WHITE, BLACK);
        }
        printAccumulator();
        printCounters();
        printFlags();
        printCommand();
    }
}
