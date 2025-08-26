#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>

#include "mode_solver.h"

//!!!!! НАЧАЛО функции (без пф) для ввода/вывода


//выводит сообщение в зависимости от причины выхода
void message_close(enum Messages reason_close) {

    switch (reason_close) {

        case QUIT_MSG:
           printf("Correct quit");
           break;

        case TOOMUCH_INPUTS_MSG:
           printf("Too many wrong inputs. Close program.");
           break;

        case FAILURE_MSG:
           printf("reason_close = FAILURE");
           break;

        case SUCCESS_MSG:
           printf("reason_close = SUCCESS");
           break;
    }
}

//рекурсия: требует повторить ввод пока не введут q
bool recur_input(struct Coef * const pst) {

   assert (pst != NULL);
   bool res;

   printf("Vvedite koefficenty uravnenya (\"q\" for quit):\n");

   if (scanf("%lf %lf %lf", pst->a, pst->b, pst->c) != 3) {

        if (getchar() == 'q') {

              eat_left_string(stdin);
              res = false;
        }

        else {
            eat_left_string(stdin);
            printf("Wrong input. Try again.\n\n");

            if (recur_input(pst))
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

//цикл: требует повторить ввод пока не введут q
enum Messages cycle_input(struct Coef * const pst) {

   assert (pst != NULL);

   enum Messages flag = SUCCESS_MSG;

   printf("Vvedite koefficenty uravnenya (\"q\" for quit):\n");

   for (int i=0; (flag == SUCCESS_MSG) && (scanf("%lf %lf %lf", &(pst->a), &(pst->b), &(pst->c)) != 3); i++) {

        if (getchar() == 'q') {

              eat_left_string(stdin);
              flag = QUIT_MSG;
        }

        else {
            eat_left_string(stdin);

            if (i>4)
                flag = TOOMUCH_INPUTS_MSG;
            else printf("Wrong input. Try again.\n\n");


        }
    }

    return flag;
}

// создаёт строку вида "Otvet: x = ..." и записывает её в str
enum Messages answer_to_string(const struct Roots rt, char * str) {

    assert (str != NULL);
    enum Messages res = SUCCESS_MSG;

    switch (rt.amt) {

        case INF_SOLUT:
            sprintf(str, "Otvet:  Any solution");
            break;

        case NO_SOLUT:
            sprintf(str, "Otvet:  No solution");
            break;

        case ONE_SOLUT:
           assert (!isnan(rt.x1));
           sprintf(str, "Otvet:  x = %.3lf", rt.x1);
           break;

        case TWO_SOLUT:
            assert (!(isnan(rt.x1) || isnan(rt.x2)));
            sprintf(str, "Otvet:  x1 = %.3lf,  x2 = %.3lf", rt.x1, rt.x2);
            break;

        case ERR_SOLUT:
            res = FAILURE_MSG;
            break;
    }
    return res;
}

//проверяет равны ли коэфы NAN, eсли да - закрывает программу, если нет - выводит их на экран
void check_input(const struct Coef cf) {

    assert (!(isnan(cf.a) || isnan(cf.b) || isnan(cf.c)));
    printf("Vvedeno: %.3lf %.3lf %.3lf\n", cf.a, cf.b, cf.c);
}

// КОНЕЦ функции (без пф) для ввода/вывода





// режим решателя
int mode_solver(void) {

    struct Equat eq {
        { NAN, NAN, NAN },
        { ERR_SOLUT, NAN, NAN }
    };


    char str_answer[BIGSIZE]; //память для строки с ответом

    enum Messages reason_close = FAILURE_MSG;

    reason_close = cycle_input(&eq.coef);

    for (; reason_close == SUCCESS_MSG; reason_close = cycle_input(&eq.coef))  {

        check_input(eq.coef);

//главная суть (
        eq.roots = solve_equat(eq.coef); 
        answer_to_string(eq.roots, str_answer);              
//главная суть )

        fputs(str_answer, stdout);

        eq = {
        { NAN, NAN, NAN },
        { ERR_SOLUT, NAN, NAN }
        };

        printf("\n\n");
    }

    message_close(reason_close);

    return 0;

}

