#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <stdlib.h> 

#define MY_ASSERT(E) if (! (E)) {printf("Error: in file  %s  line %d", __FILE__, __LINE__); exit(EXIT_FAILURE);}

#include "C:\\Users\\HONOR\\Desktop\\Polina C\\PR KvadrEquation\\pr_quad-equat\\includes\\mode_solver.h"
#include "C:\\Users\\HONOR\\Desktop\\Polina C\\PR KvadrEquation\\pr_quad-equat\\includes\\mode_tester.h"


int main(int argc, char* argv[]) {
  
   MY_ASSERT((argc == 3) || (argc == 2));

    int ret = NAN;

      enum Modes mode = cmd_select_mode(argv[1]);

      switch (mode) {

        case SOLVER:
           printf("\n\x1b[38;2;255;255;102mSolver mode selected:\n\n");
           ret = mode_solver();
           break;

        case TESTER:
           printf("\n\x1b[38;2;102;255;225mTester mode selected:\n\n");
           ret = mode_tester(argv[2]);
           break;

        case MAIN_QUIT:
           printf("\n\x1b[38;2;255;102;178mFinal");
           ret = 0;
           break;

        case INC_INPUT:
           printf("\n\x1b[38;2;255;178;102mIncorrect input. Try again");
           break;

       }
    
    printf("\n\n\x1b[38;2;255;0;0mCOMMIT GITHUB\x1b[0;2;0;0;0m\n\n");

    return ret;
}
