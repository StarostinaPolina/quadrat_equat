
//������ ������ ���� "ax^2+bx+c=0" � ���������� � � eq
void equat_to_string(char * eq, const double a, const double b, const double c);


int main() {

    double a = NAN, b = NAN, c = NAN;
    double x1 = NAN, x2 = NAN;


    //char str_equat[BIGSIZE];    //������ ��� ������ ���� "ax^2+bx+c=0"
    char str_answer[BIGSIZE]; //������ ��� ������ � �������


    enum Solution amt_solves = ERR; //����� �������

    while (cycle_input(&a, &b, &c))  {

        check_input(a, b, c);

        //equat_to_string(str_equat, a, b, c);
        amt_solves = solve_equat(a, b, c, &x1, &x2);
        answer_to_string(amt_solves, x1, x2, str_answer);


        //fputs(str_equat, stdout);
        //printf("\n");
        fputs(str_answer, stdout);

        a = b = c = x1 = x2 = NAN;
        printf("\n\n");
    }

    return 0;
}



//���������� ��� equat_to_string():  ������ ��������� ���������� ���� �������� � ���������� � � str
void odnochlen_to_string(const double koef, const char * pow_x, char * const str, const _Bool is_first) {

   //IsFirst ����� ����� �� ������� ���� ����� ������ � ������������� ���������� � ��-�.
   //�������� ��� b=5 a=c=0 �������� ������ ��� ���� ��������� �� ��� "+5x = 0", � �� ��� "5x = 0"

    if (compare_double_with_0(koef)) {
        *str='\0';
    }
    else {
        if ((koef < 0) || (is_first))
            sprintf(str, "%.2f%s%c", koef, pow_x, '\0');
        else
            sprintf(str, "+%.2f%s%c", koef, pow_x, '\0'); // TODO: snprintf
    }

    printf("str = %s\n", str);
}



//������ ������ ���� "ax^2+bx+c=0" � ���������� � � eq
void equat_to_string(char * const str_eq, const double a, const double b, const double c) {

    if (compare_double_with_0(a) && compare_double_with_0(b) && compare_double_with_0(c))
            strcpy(str_eq, "0 = 0");

    else {
        char a_str[SIZE]={};  //�������� ������ ��� ��������-����������
        char b_str[SIZE]={};
        char c_str[SIZE]={};


        odnochlen_to_string(a, "x^2", a_str, true);
        printf("a_str = %s\n", a_str);
        for (int i = 0; i < SIZE; i++)
            printf("<%c> - %d", a_str[i], a_str[i]);

        if (compare_double_with_0(a)) {
            odnochlen_to_string(b, "x", b_str, true);

            if (compare_double_with_0(b))
                  odnochlen_to_string(c, "", c_str, true);
            else
                  odnochlen_to_string(c, "", c_str, false);
        }
        else {
            odnochlen_to_string(b, "x", b_str, false);
            odnochlen_to_string(c, "", c_str, false);
        }
        printf(str_eq, "%s%s%s = 0", a_str, b_str, c_str);
        sprintf(str_eq, "%s%s%s = 0", a_str, b_str, c_str);   //��������� ��������� � ����������� � �������� ������ eq
    }
}
