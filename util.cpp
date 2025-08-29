#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include <string.h> 

#include "C:\\Users\\HONOR\\Desktop\\Polina C\\PR KvadrEquation\\pr_quad-equat\\includes\\util.h"



//-----------------------------------------------------------------------------------------------------------------------------------
//! Отбрасывает все символы до символа новой строки или EOF включительно
//!
//! @param [in]  fp  Указатель на файл откуда ведётся чтение
//-----------------------------------------------------------------------------------------------------------------------------------


void eat_left_string(FILE * fp) {
    char c = NAN;
    c = fgetc(fp);
    while (c !='\n' &&  c != EOF)
         c = fgetc(fp);
}


//-----------------------------------------------------------------------------------------------------------------------------------
//! Сравнивает числа типа double с точностью до константы DELTA
//!
//! @param [in]  a Первое число
//! @param [in]  b Второе число
//!
//! @return Результат сравнения (значение типа bool)
//-----------------------------------------------------------------------------------------------------------------------------------


bool compare_double(double a, double b) {

    bool res;

    if (isnan(a))
        res = (isnan(b));
    else
        res = (fabs(a - b) <= DELTA); 
    return res;
}






//-----------------------------------------------------------------------------------------------------------------------------------
//! Решает квадратное ур-е по 3-м коэффицентам (в том числе нулевым)
//!
//! @param [in]  coef  Структура типа Coef с коэффицентами 
//!
//! @return Структура типа Roots с корнями ур-я
//-----------------------------------------------------------------------------------------------------------------------------------
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

//-----------------------------------------------------------------------------------------------------------------------------------
//! Решает квадратное ур-е
//!
//! @param [in]  coef  Структура типа Coef с коэффицентами 
//! @param [out] p     Указатель на структуру типа Roots с корнями
//!
//! @return Статус завершения функции
//!
//! @note Подфункция для solve_equat()
//-----------------------------------------------------------------------------------------------------------------------------------

enum Messages solve_quadrat(const struct Coef coef, struct Roots * const p) {

    if (p == NULL)
        return FAILURE_MSG;

    double D = NAN; 

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

//-----------------------------------------------------------------------------------------------------------------------------------
//! Решает линейное ур-е
//!
//! @param [in]  b  b-коэффицент 
//! @param [in]  c  c-коэффицент 
//! @param [out] p1 Указатель на x1
//!
//! @return Количество решений
//!
//! @note Подфункция для solve_equat()
//-----------------------------------------------------------------------------------------------------------------------------------

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




//--------------------------------------------------------------------------------------------------------------------------------------------------
//! Выбирает режим
//!
//! @param [in] str Второй аргумент командной строки
//!
//! @return Выбранный режим (тип enum Modes)
//-----------------------------------------------------------------------------------------------------------------------------------


enum Modes cmd_select_mode(const char * str) {

    if (strlen(str) == 1) {

        switch (str[0]) {

            case 's':
                return SOLVER;

            case 't':
                return TESTER;

            case 'q':
                return MAIN_QUIT;

            default:
                return INC_INPUT;
            };
        }
    else {
        return INC_INPUT;   
    };    
}























