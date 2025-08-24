#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <assert.h>

#define DELTA 1.0e-5


enum Solution {

    ONE = 1,
    TWO = 2,
    NO  = 0,
    INF = -1,
    ERR = -2,

};

enum Messages {

    SUCCESS = 1,
    FAILURE = 0,

};




//считывает корни из файла в зависимости от колва решений
enum Messages analys(double * p01, double * p02, const enum Solution SOLVES);

//сравнивает даблы
bool compare_double(double your, double sample);

//проверяет решателя
int check(const double a, const double b, const double c,
                const enum Solution in_solves, const double x01, const double x02);

void eat_left_string(FILE * fp);
void output_x(const char c, const double x, const double x0);



//тест мэин
int main() {

    double a = NAN, b = NAN, c = NAN;

    double x01 = NAN, x02 = NAN;

    enum Solution SOLVES = ERR; //колво решений
    short int_SOLVES = -2;
    int all_tests = NAN, succ_tests = 0;

    FILE * fp = NULL;
    fp = fopen("C:\\Users\\HONOR\\Desktop\\Polina C\\PR KvadrEquation\\1f  quad-equat\\tests.txt", "r");

    assert (fp != NULL);

    eat_left_string(fp);
    fscanf(fp, "%d", &all_tests);

    assert (! isnan(all_tests));


    for (int i = 0; i < all_tests; i++)  {


        fscanf(fp, "%lf %lf %lf %d %lf %lf", &a, &b, &c, &int_SOLVES, &x01, &x02);
        SOLVES = (enum Solution) int_SOLVES;

        analys(&x01, &x02, SOLVES);

        succ_tests += check(a, b, c, SOLVES, x01, x02);

        a = b = c = NAN;
        printf("\n\n");
    }

    printf("All test: %d.  Test complete: %d", all_tests, succ_tests);

    return 0;
}



//ФУНКЦИИ

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





//ПОДФУНКЦИИ:

//сравнение дабл
bool compare_double(double your, double sample) {

    bool res;

    if (isnan(your))
        res = (isnan(sample));
    else
        res = (fabs(your-sample) <= DELTA); // TODO: в константу

    return res;
}


//подчищает буфер
void eat_left_string(FILE * fp) {
    char c = NAN;
    c = fgetc(fp);
    while (c !='\n' &&  c != EOF)
         c = fgetc(fp);
}



///!!!!! НАЧАЛО solve_equat


// протипы пф
enum Solution solve_linar(const double b, const double c, double * p1);
enum Solution solve_quadrat(const double a, const double b, const double c, double * p1, double * p2);

// ГЛАВНАЯ
enum Solution solve_equat(const double a, const double b, const double c,
                                        double * p1, double * p2)  {

    enum Solution SOLVES;

    if (compare_double(a,0)) SOLVES = solve_linar(b, c, p1); //решаем линейное ур-е
    else SOLVES = solve_quadrat(a, b, c, p1, p2); //решаем квадратное ур-е

    return SOLVES;
}

//  ПОДФ:       решает КВАДРАТНОЕ ур-е, возвращает колво решений и записывает их в *p1, *p2
enum Solution solve_quadrat(const double a, const double b, const double c, double * p1, double * p2) {

    assert (p1 != NULL && p2 != NULL);

    enum Solution SOLVES; //колво решений  // TODO: enum
    double D = NAN; //дискриминант

    D = b * b - 4 * a * c;
    if (D < 0) {
        SOLVES = NO;
    }
    else if (D > 0) {
        SOLVES = TWO;
        D = sqrt(D);
        *p1 = (-b - D) / (2 * a);
        *p2 = (-b + D) / (2 * a);
    }
    else {
        SOLVES = ONE;
        *p1 = (-b) / (2 * a);
    }
    return SOLVES;
}

//  ПОДФ:       решает ЛИНЕЙНОЕ ур-е, возвращает колво решений и записывает их в *p1
enum Solution solve_linar(const double b, const double c, double * p1) {

    assert (p1 != NULL);

    enum Solution SOLVES;
    if (compare_double(b,0)) {

         if (compare_double(c,0) )
              SOLVES = INF;
         else SOLVES = NO;
    }

    else {
            *p1 = -c / b;
            SOLVES = ONE;
    }
    return SOLVES;
}



// КОНЕЦ solve_equat






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


void output_x(const char c, const double x, const double x0) {

   printf("    x%c = ", c);

   if (isnan(x)) printf("NAN");
   else printf("%.3lf", x);

   printf(" (inst. ");

   if (isnan(x0)) printf("NAN)");
   else printf("%.3lf)", x0);
}

