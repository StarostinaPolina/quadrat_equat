#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

#define MY_ASSERT(E) if (! (E)) {printf("Error: in file  %s  line %d", __FILE__, __LINE__); exit(EXIT_FAILURE);}




#include "mode_solver.h"
#include "mode_tester.h"


int main( ) {
   int f = 0;
  

   MY_ASSERT(f != 0);

    bool is_input_incorrect = true;
    int ret = NAN;

    while (is_input_incorrect) {

      enum Modes mode = select_mode();

      switch (mode) {

        case SOLVER:
           printf("Solver mode selected:\n\n");
           is_input_incorrect = false;
           ret = mode_solver();
           break;

        case TESTER:
           printf("Tester mode selected:\x1b[38;2;255;0;188m\n\n");
           is_input_incorrect = false;
           ret = mode_tester();
           break;

        case MAIN_QUIT:
           printf("Final\n");
           is_input_incorrect = false;
           ret = 0;
           break;

        case INC_INPUT:
           break;

       }
    }
    printf("\n\n \x1b[38;2;0;230;255mCOMMIT GITHUB\n");

    return ret;
}
