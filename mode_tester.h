#ifndef MODE_TESTER_H
#define MODE_TESTER_H

#include "util.h"

//красивый вывод
void output_smart(const char * str, const double x, const double x0);

//считывает корни из файла в зависимости от колва решений
enum Messages analys(struct Roots * const pst);

//проверяет решателя
int check(const struct Equat reference);
    
//тестирует solve_equat
enum Messages test_solve_equat(FILE * fp);

//режим тестировщика
int mode_tester(const char * file_name);

//пропустить строку в строке с файловыми данными
int skip_string_in_filestring(const char* str);

//был ли конец строки
enum Messages is_end_of_string(const char* str);

//файл в строку
char* file_to_string(FILE * fp);

#endif //MODE_TESTER_H
