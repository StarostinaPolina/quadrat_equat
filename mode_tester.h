
//��������� ����� �� ����� � ����������� �� ����� �������
enum Messages analys(double * p01, double * p02, const enum Solution SOLVES);

//��������� ��������
int check(const double a, const double b, const double c,
                const enum Solution in_solves, const double x01, const double x02);

//��������� solve_equat
enum Messages test_solve_equat(FILE * fp);

//����� ��������
int mode_tester(void);
