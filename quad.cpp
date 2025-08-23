#include <math.h>
//#include хэдер




//!!!!! НАЧАЛО функции (без пф) для ввода/вывода в мэин


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

              eat_left_string();
              res = false;
        }

        else {
            eat_left_string();
            printf("Wrong input. Try again.\n\n");

            if (recur_input(pa, pb, pc))
                 res = true;
            else res = false;
        }

    }

   else {
        res = true;
        eat_left_string();
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


// КОНЕЦ функции (без пф) для ввода/вывода в мэин






//!!!!! НАЧАЛО масенькие и полезные


// подчищает буфер
void eat_left_string(void) {
    char c = NAN;
    c = getchar();
    while (c !='\n' &&  c != EOF)
         c = getchar();
}


// КОНЕЦ масенькие и полезные







//!!!!! НАЧАЛО solve_equat


// протипы пф
enum Solution solve_linar(const double b, const double c, double * p1);
enum Solution solve_quadrat(const double a, const double b, const double c, double * p1, double * p2);

// ГЛАВНАЯ
enum Solution solve_equat(const double a, const double b, const double c,
                                        double * p1, double * p2)  {

    enum Solution SOLVES;

    if (compare_double(a,0)) SOLVES = solve_linar(b, c, p1); //решаем линейное ур-е
    else SOLVES = solve_quadrat(a, b, c, p1, p2); //решаем квадратное ур-е

    return SOLVES;
}

//  ПОДФ:       решает КВАДРАТНОЕ ур-е, возвращает колво решений и записывает их в *p1, *p2
enum Solution solve_quadrat(const double a, const double b, const double c, double * p1, double * p2) {

    assert (p1 != NULL && p2 != NULL);

    enum Solution SOLVES; //колво решений  // TODO: enum
    double D = NAN; //дискриминант

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

//  ПОДФ:       решает ЛИНЕЙНОЕ ур-е, возвращает колво решений и записывает их в *p1
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



// КОНЕЦ solve_equat








//В РАЗРАБОТКЕ


/*

void check(const double a, const double b, const double c, double * p1, double * p2, const enum Solution IN_SOLVES, const double x01, const double x02) {

     enum Solution OUT_SOLVES = solve_equat(a, b, c, p1, p2);

     if ((OUT_SOLVES != IN_SOLVES))  {
                                     kl
           printf("FAILED:   solve_equat( %.3lf,  %.3lf,  %.3lf ) \nSOLVES = %d  (inst. %d)", a, b, c, OUT_SOLVES, IN_SOLVES);

           output_x('1', *p1, x01);
           output_x('2', *p2, x02);
      }

      else printf("Good!");
}


void output_x(const char c, const double x, const double x0) {

   printf("    x%c = ", c);

   if (isnan(x)) printf("NAN");
   else printf("%lf", x);

   printf(" (inst. ");

   if (isnan(x0)) printf("NAN)");
   else printf("%lf)", x0);
}


//сравнение дабл с 0
bool compare_double(double your, double sample) {
    return  (fabs(your-sample) <= 1e-5);
}

*/





