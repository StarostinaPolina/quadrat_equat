#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>

#include "util.h"

const short SIZE_MODE = 3;  //const



//!!!!! НАЧАЛО масенькие и полезные

// подчищает буфер

void eat_left_string(FILE * fp) {
    char c = NAN;
    c = fgetc(fp);
    while (c !='\n' &&  c != EOF)
         c = fgetc(fp);
}


//сравнивает даблы
bool compare_double(double your, double sample) {

    bool res;

    if (isnan(your))
        res = (isnan(sample));
    else
        res = (fabs(your-sample) <= DELTA); // TODO: в константу

    return res;
}


// КОНЕЦ масенькие и полезные





//!!!!! НАЧАЛО solve_equat


// протипы пф
enum Solution solve_linar(const double b, const double c, double * p1);
enum Messages solve_quadrat(const struct Coef coef, struct Roots * const p);

// ГЛАВНАЯ
struct Roots solve_equat(const struct Coef coef)  {

    struct Roots result {
            ERR_SOLUT,
            NAN, NAN 
     };

    if (compare_double(coef.a, 0))
        result.amt = solve_linar(coef.b, coef.c, &result.x1); //решаем линейное ур-е
    else
        solve_quadrat(coef, &result); //решаем квадратное ур-е
    return result;
}

//  ПОДФ:       решает КВАДРАТНОЕ ур-е, возвращает колво решений и записывает их в *p1, *p2
enum Messages solve_quadrat(const struct Coef coef, struct Roots * const p) {

    if (p == NULL)
        return FAILURE_MSG;

    double D = NAN; //дискриминант

    D = coef.b * coef.b - 4 * coef.a * coef.c;
    if (D < 0) {
        p->amt = NO_SOLUT;
    }
    else if (D > 0) {
        p->amt = TWO_SOLUT;
        D = sqrt(D);
        p->x1 = (-coef.b - D) / (2 * coef.a);
        p->x2 = (-coef.b + D) / (2 * coef.a);
    }
    else {
        p->amt = ONE_SOLUT;
        p->x1 = (-coef.b) / (2 * coef.a);
    }

    return SUCCESS_MSG;
}

//  ПОДФ:       решает ЛИНЕЙНОЕ ур-е, возвращает колво решений и записывает их в *p1
enum Solution solve_linar(const double b, const double c, double * p1) {

    assert (p1 != NULL);

    enum Solution SOLVES;
    if (compare_double(b,0)) {

         if (compare_double(c,0) )
              SOLVES = INF_SOLUT;
         else SOLVES = NO_SOLUT;
    }

    else {
            *p1 = -c / b;
            SOLVES = ONE_SOLUT;
    }
    return SOLVES;
}


// КОНЕЦ solve_equat



//для мэин

enum Modes select_mode(void) {

    char str[SIZE_MODE] = {};  //инициализирует чем??

    printf("Select a mode:  's' for solver,  't' for tester, 'q' for quit\n");

    if (fgets(str, SIZE_MODE, stdin)) // TODO: {     }

        if (str[1] != '\n') {

                eat_left_string(stdin);
                printf("Incorrect input. Try again\n\n");
                return INC_INPUT;
        }

    else
        if (str[0] == 0)  {

            eat_left_string(stdin);
            printf("Incorrect input. Try again\n\n");
            return INC_INPUT;
         }


    switch (str[0]) {

        case 's':
            return SOLVER;

        case 't':
            return TESTER;

        case 'q':
            return MAIN_QUIT;

        default:
            fprintf(stderr, "Incorrect input. Try again\n\n");
            return INC_INPUT;

    }
}
//g++ флагиmain.cpp mode_solver.cpp mode_tester.cpp util.cpp -o eq.exe
//"C:\Users\HONOR\Desktop\Polina C\PR KvadrEquation\pr_quad-equat"






















