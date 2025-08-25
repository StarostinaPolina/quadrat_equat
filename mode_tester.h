
//считывает корни из файла в зависимости от колва решений
enum Messages analys(double * p01, double * p02, const enum Solution SOLVES);

//проверяет решателя
int check(const double a, const double b, const double c,
                const enum Solution in_solves, const double x01, const double x02);

//тестирует solve_equat
enum Messages test_solve_equat(FILE * fp);

//режим решателя
int mode_tester(void);
