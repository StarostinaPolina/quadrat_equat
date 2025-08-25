#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>

#include "unit.h"
#include "mode_solver.h"

//!!!!! НАЧАЛО функции (без пф) для ввода/вывода


// выводит сообщение в зависимости от причины выхода
void message_close(enum Messages reason_close) {

    switch (reason_close) {

        case QUIT:
           printf("Correct quit");
           break;

        case TOOMUCH_INPUTS:
           printf("Too many wrong inputs. Close program.");
           break;

        case FAILURE:
           printf("reason_close = FAILURE");
           break;

        case SUCCESS:
           printf("reason_close = SUCCESS");
           break;
    }
}

// рекурс: требует повторить ввод пока не введут q
bool recur_input(double * pa, double * pb, double * pc) {

   assert (pa != NULL && pb != NULL && pc != NULL);
   bool res;

   printf("Vvedite koefficenty uravnenya (\"q\" for quit):\n");

   if (scanf("%lf %lf %lf", pa, pb, pc) != 3) {

        if (getchar() == 'q') {

              eat_left_string(stdin);
              res = false;
        }

        else {
            eat_left_string(stdin);
            printf("Wrong input. Try again.\n\n");

            if (recur_input(pa, pb, pc))
                 res = true;
            else res = false;
        }

    }

   else {
        res = true;
        eat_left_string(stdin);
   }
   return res;
}

// цикл: требует повторить ввод пока не введут q
enum Messages cycle_input(double * pa, double * pb, double * pc) {

   assert (pa != NULL && pb != NULL && pc != NULL);

   enum Messages flag = SUCCESS;

   printf("Vvedite koefficenty uravnenya (\"q\" for quit):\n");

   for (int i=0; (flag == SUCCESS) && (scanf("%lf %lf %lf", pa, pb, pc) != 3); i++) {

        if (getchar() == 'q') {

              eat_left_string(stdin);
              flag = QUIT;
        }

        else {
            eat_left_string(stdin);

            if (i>4)
                flag = TOOMUCH_INPUTS;
            else printf("Wrong input. Try again.\n\n");

        }
    }

    return flag;
}

// создаёт строку вида "Otvet: x = ..." и записывает её в str
enum Messages answer_to_string(const enum Solution SOLVES, const double x1, const double x2, char * str) {

    assert (str != NULL);
    enum Messages res = SUCCESS;

    switch (SOLVES) {

        case INF:
            sprintf(str, "Otvet:  Any solution");
            break;

        case NO:
            sprintf(str, "Otvet:  No solution");
            break;

        case ONE:
           assert (!isnan(x1));
           sprintf(str, "Otvet:  x = %.3lf", x1);
           break;

        case TWO:
            assert (!(isnan(x1) || isnan(x2)));
            sprintf(str, "Otvet:  x1 = %.3lf,  x2 = %.3lf", x1, x2);
            break;

        case ERR:
            res = FAILURE;
            break;
    }
    return res;
}

// проверка чисел на NAN
void check_input(const double a, const double b, const double c) {

    assert (!(isnan(a) || isnan(b) || isnan(c)));
    printf("Vvedeno: %.3lf %.3lf %.3lf\n", a, b, c);
}


// КОНЕЦ функции (без пф) для ввода/вывода





// РЕЖИМ решателя
int mode_solver(void) {

    double a = NAN, b = NAN, c = NAN;
    double x1 = NAN, x2 = NAN;

    char str_answer[BIGSIZE]; //память для строки с ответом

    enum Solution amt_solves = ERR; //колво решений
    enum Messages reason_close = FAILURE;

    reason_close = cycle_input(&a, &b, &c);

    for (; reason_close == SUCCESS; reason_close = cycle_input(&a, &b, &c))  {

        check_input(a, b, c);

//главная суть (
        amt_solves = solve_equat(a, b, c, &x1, &x2);
        answer_to_string(amt_solves, x1, x2, str_answer);
//главная суть )

        fputs(str_answer, stdout);

        a = b = c = x1 = x2 = NAN;
        printf("\n\n");
    }

    message_close(reason_close);

    return 0;

}

