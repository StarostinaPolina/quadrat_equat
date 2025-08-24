#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define BIGSIZE 30
#define DELTA 1.0e-5

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



//  ОБЩЕЕ

//решает ВВЕДЁННОЕ ур-е, возвращает колво решений и записывает их в *p1, *p2
enum Solution solve_equat(const double a, const double b, const double c, double * p1, double * p2);

// подчищает буфер
void eat_left_string(FILE * fp);

//сравнивает даблы
bool compare_double(double your, double sample);




// ДЛЯ МЭИН

//создаёт строку вида "Otvet: x = ..." и записывает её в str
enum Messages answer_to_string(const enum Solution SOLVES, const double x1, const double x2, char * str);


//проверяет равны ли коэфы NAN, eсли да - закрывает программу, если нет - выводит их на экран
void check_input(const double a, const double b, const double c);


//рекурсия: требует повторить ввод пока не введут q
bool recur_input(double * pa, double * pb, double * pc);


//цикл: требует повторить ввод пока не введут q
enum Messages cycle_input(double * pa, double * pb, double * pc);


//выводит сообщение в зависимости от причины выхода
void message_close(enum Messages reason_close);




// ДЛЯ ТЕСТА

//считывает корни из файла в зависимости от колва решений
enum Messages analys(double * p01, double * p02, const enum Solution SOLVES);

//проверяет решателя
int check(const double a, const double b, const double c,
                const enum Solution in_solves, const double x01, const double x02);


