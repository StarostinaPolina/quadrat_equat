//�����

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
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


//������ ���Ĩ���� ��-�, ���������� ����� ������� � ���������� �� � *p1, *p2
enum Solution solve_equat(const double a, const double b, const double c, double * p1, double * p2);

//������ ������ ���� "Otvet: x = ..." � ���������� � � str
enum Messages answer_to_string(const enum Solution SOLVES, const double x1, const double x2, char * str);

//��������� ����� �� ����� NAN, e��� �� - ��������� ���������, ���� ��� - ������� �� �� �����
void check_input(const double a, const double b, const double c);

//����: ������� ��������� ���� ���� �� ������ q
enum Messages cycle_input(double * pa, double * pb, double * pc);

//������� ��������� � ����������� �� ������� ������
void message_close(enum Messages reason_close);

// ��������� �����
void eat_left_string(void);


//����� �����



//����

int main() {

    double a = NAN, b = NAN, c = NAN;
    double x1 = NAN, x2 = NAN;

    char str_answer[BIGSIZE]; //������ ��� ������ � �������

    enum Solution amt_solves = ERR; //����� �������
    enum Messages reason_close = FAILURE;

    reason_close = cycle_input(&a, &b, &c);

    for (; reason_close == SUCCESS; reason_close = cycle_input(&a, &b, &c))  {

        check_input(a, b, c);

//������� ���� (
        amt_solves = solve_equat(a, b, c, &x1, &x2);
        answer_to_string(amt_solves, x1, x2, str_answer);
//������� ���� )

        fputs(str_answer, stdout);

        a = b = c = x1 = x2 = NAN;
        printf("\n\n");
    }

    message_close(reason_close);

    return 0;
}







//?????????????????? ���������� �������:

//��������� ���� � 0
bool compare_double(double your, double sample) {
    return  (fabs(your-sample) <= 1e-5);
}





//�������


//!!!!! ������ ������� (��� ��) ��� �����/������ � ����


// ������� ��������� � ����������� �� ������� ������
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


// ����: ������� ��������� ���� ���� �� ������ q
enum Messages cycle_input(double * pa, double * pb, double * pc) {

   assert (pa != NULL && pb != NULL && pc != NULL);

   enum Messages flag = SUCCESS;

   printf("Vvedite koefficenty uravnenya (\"q\" for quit):\n");

   for (int i=0; (flag == SUCCESS) && (scanf("%lf %lf %lf", pa, pb, pc) != 3); i++) {

        if (getchar() == 'q') {

              eat_left_string();
              flag = QUIT;
        }

        else {
            eat_left_string();

            if (i>4)
                flag = TOOMUCH_INPUTS;
            else printf("Wrong input. Try again.\n\n");

        }
    }

    return flag;
}

// ������ ������ ���� "Otvet: x = ..." � ���������� � � str
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

// �������� ����� �� NAN
void check_input(const double a, const double b, const double c) {

    assert (!(isnan(a) || isnan(b) || isnan(c)));
    printf("Vvedeno: %.3lf %.3lf %.3lf\n", a, b, c);
}


// ����� ������� (��� ��) ��� �����/������ � ����






//!!!!! ������ ��������� � ��������


// ��������� �����
void eat_left_string(void) {
    char c = NAN;
    c = getchar();
    while (c !='\n' &&  c != EOF)
         c = getchar();
}


// ����� ��������� � ��������







//!!!!! ������ solve_equat


// ������� ��
enum Solution solve_linar(const double b, const double c, double * p1);
enum Solution solve_quadrat(const double a, const double b, const double c, double * p1, double * p2);

// �������
enum Solution solve_equat(const double a, const double b, const double c,
                                        double * p1, double * p2)  {

    enum Solution SOLVES;

    if (compare_double(a,0)) SOLVES = solve_linar(b, c, p1); //������ �������� ��-�
    else SOLVES = solve_quadrat(a, b, c, p1, p2); //������ ���������� ��-�

    return SOLVES;
}

//  ����:       ������ ���������� ��-�, ���������� ����� ������� � ���������� �� � *p1, *p2
enum Solution solve_quadrat(const double a, const double b, const double c, double * p1, double * p2) {

    assert (p1 != NULL && p2 != NULL);

    enum Solution SOLVES; //����� �������  // TODO: enum
    double D = NAN; //������������

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

//  ����:       ������ �������� ��-�, ���������� ����� ������� � ���������� �� � *p1
enum Solution solve_linar(const double b, const double c, double * p1) {

    assert (p1 != NULL);

    enum Solution SOLVES;
    if (compare_double(b,0)) {

         if (compare_double(b,0) )
              SOLVES = INF;
         else SOLVES = NO;
    }

    else {
            *p1 = -c / b;
            SOLVES = ONE;
    }
    return SOLVES;
}



// ����� solve_equat
