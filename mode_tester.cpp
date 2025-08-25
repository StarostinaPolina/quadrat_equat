#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "unit.h"
#include "mode_tester.h"


//!!!!! НАЧАЛО тест

//прототип пф
void output_x(const char c, const double x, const double x0);

// считывает корни из файла в зависимости от колва решений
enum Messages analys(double * p01, double * p02, const enum Solution SOLVES) {

      switch (SOLVES) {

        case ERR:
           return FAILURE;
        case INF:
        case NO:
          *p01 = *p02 = NAN;
           break;

        case ONE:
           *p02 = NAN;
           break;

        case TWO:
           break;

      }

      return SUCCESS;
}

//проверяет решателя
int check(const double a, const double b, const double c, const enum Solution in_solves, const double x01, const double x02) {

     double x1 = NAN, x2 = NAN;

     enum Solution out_solves = solve_equat(a, b, c, &x1, &x2);

     if ((out_solves != in_solves) || !compare_double(x1, x01) || !compare_double(x2, x02))  {

           printf("FAILED:   solve_equat(%.3lf,  %.3lf,  %.3lf) \nSOLVES = %d  (inst. %d)", a, b, c, out_solves, in_solves);

           output_x('1', x1, x01);
           output_x('2', x2, x02);

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
          return NULL_FILE;

    double a = NAN, b = NAN, c = NAN;
    double x01 = NAN, x02 = NAN;

    enum Solution SOLVES = ERR; //колво решений
    short int_SOLVES = -2;
    int all_tests = NAN, succ_tests = 0;



    eat_left_string(fp);
    fscanf(fp, "%d", &all_tests);

    if (isnan(all_tests))
          return FAILURE;


    for (int i = 0; i < all_tests; i++)  {


        fscanf(fp, "%lf %lf %lf %d %lf %lf", &a, &b, &c, &int_SOLVES, &x01, &x02);
        SOLVES = (enum Solution) int_SOLVES;

        analys(&x01, &x02, SOLVES);

        succ_tests += check(a, b, c, SOLVES, x01, x02);

        a = b = c = NAN;
        printf("\n\n");
    }

    printf("All test: %d.  Test complete: %d", all_tests, succ_tests);

    return SUCCESS;
}

// КОНЕЦ тест



//!!!!! НАЧАЛО режимы

// режим теста
int mode_tester(void) {
    FILE * fp = NULL;
    fp = fopen("C:\\Users\\HONOR\\Desktop\\Polina C\\PR KvadrEquation\\1f  quad-equat\\tests.txt", "r");

    enum Messages message_test = INIT;

    switch (test_solve_equat(fp)) {

          case INIT:
                printf("Error:  test_solve_equat() hasn't started");
                break;

          case FAILURE:
                printf("Error:  cannot read file");
                break;

          case NULL_FILE:
                printf("Error:  file pointer is NULL");
                break;
        }
    return 0;
}



// КОНЕЦ тест






