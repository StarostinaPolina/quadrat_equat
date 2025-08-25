#define BIGSIZE 30

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

// режим решателя
int mode_solver(void);
