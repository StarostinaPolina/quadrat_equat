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

//!!!!!!!!!!! ������� ������

//������ ���Ĩ���� ��-�, ���������� ����� ������� � ���������� �� � *p1, *p2
enum Solution solve_equat(const double a, const double b, const double c, double * p1, double * p2);


//������ ������ ���� "Otvet: x = ..." � ���������� � � str
enum Messages answer_to_string(const enum Solution SOLVES, const double x1, const double x2, char * str);


//��������� ����� �� ����� NAN, e��� �� - ��������� ���������, ���� ��� - ������� �� �� �����
void check_input(const double a, const double b, const double c);


//��������: ������� ��������� ���� ���� �� ������ q
bool recur_input(double * pa, double * pb, double * pc);


//����: ������� ��������� ���� ���� �� ������ q
enum Messages cycle_input(double * pa, double * pb, double * pc);


//������� ��������� � ����������� �� ������� ������
void message_close(enum Messages reason_close);

// ��������� �����
void eat_left_string(void);

//��������� � ����������
