#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "mode_tester.h"


// считывает корни из файла в зависимости от колва решений
enum Messages analys(struct Roots * const pst) {

      switch (pst->amt) {

        case ERR_SOLUT:
           return FAILURE_MSG;

        case INF_SOLUT:
        case NO_SOLUT:
           pst->x1 = pst->x2 = NAN;
           break;

        case ONE_SOLUT:
           pst->x2 = NAN;
           break;

        case TWO_SOLUT:
           break;

      }

      return SUCCESS_MSG;
}

//проверяет решателя
int check(const struct Equat reference) {

     struct Roots result {
            ERR_SOLUT,
            NAN, NAN 
     };

     result = solve_equat(reference.coef); 

     if ((result.amt != reference.roots.amt) || !compare_double(result.x1, reference.roots.x1) || !compare_double(result.x2, reference.roots.x2))  {

           printf("FAILED:   solve_equat(%.3lf,  %.3lf,  %.3lf) \nSOLVES = %d  (inst. %d)", reference.coef.a, reference.coef.b, reference.coef.c, result.amt, reference.roots.amt);

           output_x('1', result.x1, reference.roots.x1);
           output_x('2', result.x2, reference.roots.x2);

           return 0;
      }

      else {
         printf("Good!");
         return 1;
      }
}

// ПОДФ check:  удобный вывод
void output_x(const char c, const double x, const double x0) {

   printf("    x%c = ", c);

   if (isnan(x)) printf("NAN");
   else printf("%.3lf", x);

   printf(" (inst. ");

   if (isnan(x0)) printf("NAN)");
   else printf("%.3lf)", x0);
}

//тестирует solve_equat
enum Messages test_solve_equat(FILE * fp) {

      if (fp == NULL)
          return NULL_FILE_MSG;

      struct Equat reference {
        { NAN, NAN, NAN },
        { ERR_SOLUT, NAN, NAN }
      };

    int int_SOLVES = -2;
    int all_tests = NAN, succ_tests = 0;


    eat_left_string(fp);
    fscanf(fp, "%d", &all_tests);

    if (isnan(all_tests))
          return FAILURE_MSG;


    for (int i = 0; i < all_tests; i++)  {


        fscanf(fp, "%lf %lf %lf %d %lf %lf", &reference.coef.a, &reference.coef.b, &reference.coef.c, &int_SOLVES, &reference.roots.x1, &reference.roots.x2);
        
        reference.roots.amt = (enum Solution) int_SOLVES;

        analys(&reference.roots);

        succ_tests += check(reference);

        reference = {
        { NAN, NAN, NAN },
        { ERR_SOLUT, NAN, NAN }
        };

        printf("\n\n");
    }

    printf("All test: %d.  Test complete: %d", all_tests, succ_tests);

    return SUCCESS_MSG;
}




// режим теста
int mode_tester(void) {
    FILE * fp = NULL;
    fp = fopen("C:\\Users\\HONOR\\Desktop\\Polina C\\PR KvadrEquation\\pr_quad-equat\\tests.txt", "r");

    enum Messages message_test = INIT_MSG;

    switch (test_solve_equat(fp)) {

          case INIT_MSG:
                printf("Error:  test_solve_equat() hasn't started");
                break;

          case FAILURE_MSG:
                printf("Error:  cannot read file");
                break;

          case NULL_FILE_MSG:
                printf("Error:  file pointer is NULL");
                break;
        }
    return 0;
}



// КОНЕЦ тест






