#ifndef MODE_SOLVER_H
#define MODE_SOLVER_H

const short BIGSIZE = 30; // TODO: const

#include "util.h"


////создаёт строку вида "Otvet: x = ..." и записывает её в str
enum Messages answer_to_string(const struct Roots rt, char * str);


//проверяет равны ли коэфы NAN, eсли да - закрывает программу, если нет - выводит их на экран
void check_input(const struct Coef cf);


//рекурсия: требует повторить ввод пока не введут q
bool recur_input(struct Coef * const pst);


//цикл: требует повторить ввод пока не введут q
enum Messages cycle_input(struct Coef * const pst);


//выводит сообщение в зависимости от причины выхода
void message_close(enum Messages reason_close);

// режим решателя
int mode_solver(void);


#endif // MODE_SOLVER_H
