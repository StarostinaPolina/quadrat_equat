#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>

#include "C:\\Users\\HONOR\\Desktop\\Polina C\\PR KvadrEquation\\pr_quad-equat\\includes\\mode_solver.h"

//-----------------------------------------------------------------------------------------------------------------------------------
//! Выводит на экран сообщение в зависимости от причины завершения режима решателя
//!
//! @param [in] reason_close Причина завершения режима решателя
//-----------------------------------------------------------------------------------------------------------------------------------
void message_close(enum Messages reason_close) {

    switch (reason_close) {

        case QUIT_MSG:
           printf("Correct quit\n");
           break;

        case TOOMUCH_INPUTS_MSG:
           printf("Too many wrong inputs. Close program.\n");
           break;

        case INIT_MSG:
           fprintf(stderr, "cycle_input() hasn't started\n");
           break;

        default:
           fprintf(stderr, "Undefined error\n");
           break;
    }
}


//-----------------------------------------------------------------------------------------------------------------------------------
//! Просит пользователя ввести коэффиценты с клавиатуры и считывает их
//!
//! @param [out] pts Указатель на структуру с коэффицентами
//!
//! @return Статус завершения функции
//!
//! @note В случае неверного ввода дает вторую попытку. Если 5 попыток подряд - неуспешные, завершает программу
//! @note Возвращает QUIT_MSG если пользователь захотел завершить программу,
//!         TOOMUCH_INPUTS_MSG если слишком много неуспешных попыток ввода,
//!         SUCCESS_MSG если коэффиценты считаны успешно
//-----------------------------------------------------------------------------------------------------------------------------------

enum Messages cycle_input(struct Coef * const pst) {

   assert (pst != NULL);

   printf("Enter coefficients of equation (\"q\" for quit):\n");

   for (int i=0; (scanf("%lf %lf %lf", &(pst->a), &(pst->b), &(pst->c)) != 3); i++) {

        if (getchar() == 'q') {

              eat_left_string(stdin);
              return QUIT_MSG;
        }

        else {
            eat_left_string(stdin);

            if (i>4)
                return TOOMUCH_INPUTS_MSG;
            else printf("Wrong input. Try again.\n\n");
        }
    }

    assert (!(isnan(pst->a) || isnan(pst->b) || isnan(pst->c)));
    printf("Entered: %.3lf %.3lf %.3lf\n", pst->a, pst->b, pst->c);

    return SUCCESS_MSG;
}


//-----------------------------------------------------------------------------------------------------------------------------------
//! Cоздаёт строку вида "Answer: x = ..." и записывает её в str
//!
//! @param [in] pts Указатель на структуру с корнями
//! @param [in] str Указатель на массив чаров в который будет записана строка
//!
//! @return Статус завершения функции
//!
//! @note В случае некорректного колва корней возвращает FAILURE_MSG, не создаёт строку и выводит сообщение, в противном случае возвращает SUCCESS_MSG
//-----------------------------------------------------------------------------------------------------------------------------------

enum Messages answer_to_string(const struct Roots rt, char * str) {

    assert (str != NULL);
    enum Messages res = SUCCESS_MSG;

    switch (rt.amt) {

        case INF_SOLUT:
            sprintf(str, "Answer:  Any solution");
            break;

        case NO_SOLUT:
            sprintf(str, "Answer:  No solution");
            break;

        case ONE_SOLUT:
           assert (!isnan(rt.x1));
           sprintf(str, "Answer:  x = %.3lf", rt.x1);
           break;

        case TWO_SOLUT:
            assert (!(isnan(rt.x1) || isnan(rt.x2)));
            sprintf(str, "Answer:  x1 = %.3lf,  x2 = %.3lf", rt.x1, rt.x2);
            break;

        default:
            res = FAILURE_MSG;
            printf("Incorrect amt_solves. Answer string not created\n");
            break;
    }
    return res;
}




//-----------------------------------------------------------------------------------------------------------------------------------
//! Запускает режим решателя
//!
//! @return Статус завершения функции
//!
//! @note Возвращает 1 если возникла ошибка, 0 в противном случае
//-----------------------------------------------------------------------------------------------------------------------------------
int mode_solver(void) {

    struct Equat eq {
        { NAN, NAN, NAN },
        { ERR_SOLUT, NAN, NAN }
    };


    char str_answer[BIGSIZE]; //память для строки с ответом

    enum Messages reason_close = INIT_MSG;

    
    for (reason_close = cycle_input(&eq.coef); reason_close == SUCCESS_MSG; reason_close = cycle_input(&eq.coef))  {


        eq.roots = solve_equat(eq.coef); 

        if (answer_to_string(eq.roots, str_answer) != FAILURE_MSG)
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

