#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define BIGSIZE 30

enum Solution {

    ONE = 1,
    TWO = 2,
    NO  = 0,
    INF = -1,
    ERR = -2,

};

enum Messages {

    SUCCESS = 0,
    FAILURE = -1,
    TOOMUCH_INPUTS = 1,
    QUIT = 2,

};

//!!!!!!!!!!! “–ќ√ј“№ Ќ≈Ћ№«я

//решает ¬¬≈ƒ®ЌЌќ≈ ур-е, возвращает колво решений и записывает их в *p1, *p2
enum Solution solve_equat(const double a, const double b, const double c, double * p1, double * p2);


//создаЄт строку вида "Otvet: x = ..." и записывает еЄ в str
enum Messages answer_to_string(const enum Solution SOLVES, const double x1, const double x2, char * str);


//провер€ет равны ли коэфы NAN, eсли да - закрывает программу, если нет - выводит их на экран
void check_input(const double a, const double b, const double c);


//рекурси€: требует повторить ввод пока не введут q
bool recur_input(double * pa, double * pb, double * pc);


//цикл: требует повторить ввод пока не введут q
enum Messages cycle_input(double * pa, double * pb, double * pc);


//выводит сообщение в зависимости от причины выхода
void message_close(enum Messages reason_close);

// подчищает буфер
void eat_left_string(void);

//ќ—“јЋ№Ќќ≈ ¬ –ј«–јЅќ“ ≈
