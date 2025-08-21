//���������� �����
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

//���������� ��� �������
#include <math.h>
#include <string.h>

//���������
#define SIZE 8
#define BIGSIZE 30

//��������� ������� ��� ����:

//������ ������ ���� "ax^2+bx+c=0" � ���������� � � eq
void equat_to_string(char * eq, const double a, const double b, const double c);

//������ ���Ĩ���� ��-�, ���������� ����� ������� � ���������� �� � *p1, *p2
short solve_equat(const double a,const double b, const double c, double * p1, double * p2);

//������ ������ ���� "Otvet: x = ..." � ���������� � � str
void answer_to_string(const short SOLVES, const double x1, const double x2, char * str);



//����
int main() {

    double a,b,c;
    double x1,x2;
    char equat[BIGSIZE]; //������ ��� ������ ���� "ax^2+bx+c=0"
    char answer[BIGSIZE]; //������ ��� ������ � �������
    short amt_solves; //����� �������

    printf("Vvedite koefficenty uravnenya (\"q\" for quit): \n");

    while (scanf("%lf %lf %lf",&a,&b,&c) ==3) {
        printf("Vvedeno: %.3lf %.3lf %.3lf\n", a, b, c);

        equat_to_string(equat, a, b, c);

        amt_solves = solve_equat(a, b, c, &x1, &x2);
        answer_to_string(amt_solves, x1, x2, answer);

        fputs(equat, stdout);
        printf("\n");
        fputs(answer, stdout);
        printf("\n\nVvedite koefficenty uravnenya (\"q\" for quit): \n");
    }
    return 0;
}





//�������:

//���������� ��� equat_to_string():  ������ ��������� ���������� ���� �������� � ���������� � � str
void odnochlen_to_string(const double K, const char * xx, char * str, const _Bool IsFirst) {

   //IsFirst ����� ����� �� ������� ���� ����� ������ � ������������� ���������� � ��-�.
   //�������� ��� b=5 a=c=0 �������� ������ ��� ���� ��������� �� ��� "+5x = 0", � �� ��� "5x = 0"

    if (K==0) *str='\0';
    else {
        if ((K < 0) || (IsFirst))
            sprintf(str, "%.2f%s", K, xx);
        else
            sprintf(str, "+%.2f%s", K, xx);
    }
}

//���������� ��� solve_equat(): ������ ���������� (�!=0) ��-�, ���������� ����� ������� � ���������� �� � *p1, *p2
short solve_quadrat(const double a,const double b, const double c, double * p1, double * p2) {

    short solves; //����� �������
    double D; //������������

    D = b*b - 4*a*c;
    if (D<0)
        solves = 0;
    else if (D>0) {
        solves = 2;
        *p1 = (-b - sqrt(D)) / (2 * a);
        *p2 = (-b + sqrt(D)) / (2 * a);
    }
    else {
        solves = 1;
        *p1 = (-b)/(2*a);
    }
    return solves;
    }



//������� �������������� � ����:

void equat_to_string(char * eq, const double a, const double b, const double c) {


    if ((a==0) && (b==0) && (c==0))
            strcpy(eq, "0 = 0");

    else {
        char a_str[SIZE];  //�������� ������ ��� ��������-����������
        char b_str[SIZE];
        char c_str[SIZE];

        odnochlen_to_string(a, "x^2", a_str, true);

        if (a == 0) {
            odnochlen_to_string(b, "x", b_str, true);

            if (b == 0)
                  odnochlen_to_string(c, "", c_str, true);
            else
                  odnochlen_to_string(c, "", c_str, false);
        }
        else {
            odnochlen_to_string(b, "x", b_str, false);
            odnochlen_to_string(c, "", c_str, false);
        }
        sprintf(eq, "%s%s%s = 0", a_str, b_str, c_str);   //��������� ��������� � ����������� � �������� ������ eq
    }
}

short solve_equat(const double a,const double b, const double c, double * p1, double * p2) {

    short SOLVES;

    if ((a==0) && (b==0) &&(c==0))
        SOLVES = 5; //����������� ����� �������
    else
        if (a==0)  //������ �������� ��-�
            if (b==0)
                SOLVES = 0;
            else {
                *p1 = (-c/b);
                SOLVES = 1; }

        else SOLVES = solve_quadrat(a,b,c, p1,p2); //������ ���������� ��-�

    return SOLVES;
}

void answer_to_string(const short SOLVES, const double x1, const double x2, char * str) {

    switch (SOLVES) {
        case 5:
            sprintf(str, "Otvet:  Infinity");
            break;
        case 0:
            sprintf(str, "Otvet:  No solution");
            break;
        case 1:
            sprintf(str, "Otvet:  x = %.3lf", x1);
            break;
        case 2:
            sprintf(str, "Otvet:  x1 = %.3lf,  x2 = %.3lf", x1, x2);
            break;
    }
}



