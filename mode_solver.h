#define BIGSIZE 30

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

// ����� ��������
int mode_solver(void);
