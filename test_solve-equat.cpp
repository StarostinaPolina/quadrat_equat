#include "quad.h"


//тест мэин
int main() {

    double a = NAN, b = NAN, c = NAN;

    double x01 = NAN, x02 = NAN;

    enum Solution SOLVES = ERR; //колво решений
    short int_SOLVES = -2;
    int all_tests = NAN, succ_tests = 0;

    FILE * fp = NULL;
    fp = fopen("C:\\Users\\HONOR\\Desktop\\Polina C\\PR KvadrEquation\\1f  quad-equat\\tests.txt", "r");

    assert (fp != NULL);

    eat_left_string(fp);
    fscanf(fp, "%d", &all_tests);

    assert (! isnan(all_tests));


    for (int i = 0; i < all_tests; i++)  {


        fscanf(fp, "%lf %lf %lf %d %lf %lf", &a, &b, &c, &int_SOLVES, &x01, &x02);
        SOLVES = (enum Solution) int_SOLVES;

        analys(&x01, &x02, SOLVES);

        succ_tests += check(a, b, c, SOLVES, x01, x02);

        a = b = c = NAN;
        printf("\n\n");
    }

    printf("All test: %d.  Test complete: %d", all_tests, succ_tests);

    return 0;
}

