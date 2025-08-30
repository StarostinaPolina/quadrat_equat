#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>

#include "C:\\Users\\HONOR\\Desktop\\Polina C\\PR KvadrEquation\\pr_quad-equat\\includes\\mode_tester.h"


//-----------------------------------------------------------------------------------------------------------------------------------
//! Записывает данные из файла в строку
//!
//! @param [in] fp Указатель на файл который нужно считать
//!
//! @return Указатель на строку, где хранятся считанные из файла данные
//! 
//! @note Возвращает NULL если fp = 0 или файл был считан не до конца
//!
//! @note Подфункция для test_solve_equat()
//-----------------------------------------------------------------------------------------------------------------------------------
char* file_to_string(FILE * fp) {

    if (! fp) return NULL;

    long file_size = 0;
    char* file_content = NULL;


    fseek(fp, 0L, SEEK_END);
    file_size = ftell(fp);
    rewind(fp);


    file_content = (char *) calloc(file_size, sizeof (char));


    int count = fread(file_content, sizeof file_content[0], (size_t) file_size, fp);


    if (count != file_size) return NULL;
    
    return file_content;
}



//-----------------------------------------------------------------------------------------------------------------------------------
//! Пропускает символы в строке до '\n' включительно 
//!
//! @param [in] str  Указатель на строку откуда нужно считать
//!
//! @return Колво пропущенных символов
//!
//! @note Подфункция для test_solve_equat()
//-----------------------------------------------------------------------------------------------------------------------------------
int skip_string_in_filestring(const char* str) {
    int i = 0;
    while (str[i++] != '\n')
        continue;
    return i;
}

// !!!! НЕ РАБОТАЕТ !!!!
//-----------------------------------------------------------------------------------------------------------------------------------
//! Проверяет, какой символ в строке встретится раньше: '\n' или любой непробельный 
//!
//! @param [in] str  Указатель на строку откуда нужно считать
//!
//! @return Сообщение о том, какой символ встретился первым
//!
//! @note Возвращает SUCCESS_MSG если первым встретился '\n', FAILURE_MSG если непробельный
//! 
//! @note Подфункция для test_solve_equat()
//-----------------------------------------------------------------------------------------------------------------------------------
enum Messages is_end_of_string(const char* str) {
    char c = NAN;

    for (int i = 0; true; i++) {
        c = str[i];
        if (! isspace(c))
            return FAILURE_MSG;
        else
            if (c == '\n')
                return SUCCESS_MSG;
    }
}



//-----------------------------------------------------------------------------------------------------------------------------------
//! Проверяет успешно ли прошёл конкретный тест
//!
//! @param [in] reference Указатель на структуру содержащую тестовые данные
//!
//! @return Статус прохождения теста
//! 
//! @note Возвращает 1 если тест прошел успешно, 0 если нет
//! @note Печатает информацию о непройденном тесте, "Good!" в противном случае
//!
//! @note Подфункция для test_solve_equat()
//-----------------------------------------------------------------------------------------------------------------------------------
int check(const struct Equat reference) {

     struct Roots result {
            ERR_SOLUT,
            NAN, NAN 
     };

     result = solve_equat(reference.coef); 

     if ((result.amt != reference.roots.amt) || !compare_double(result.x1, reference.roots.x1) || !compare_double(result.x2, reference.roots.x2))  {

           printf("FAILED:   solve_equat(%.3lf,  %.3lf,  %.3lf)\n", reference.coef.a, reference.coef.b, reference.coef.c);

           output_smart("AMT_SOLVES", result.amt, reference.roots.amt);
           output_smart("x1", result.x1, reference.roots.x1);
           output_smart("x2", result.x2, reference.roots.x2);

           return 0;
      }

      else {
         printf("Good!");
         return 1;
      }
}

//-----------------------------------------------------------------------------------------------------------------------------------
//! Выводит строку вида "[имя переменой] = [значение от solve_equat()] (inst. [верное значение])"
//!
//! @param [in] str  Указатель на строку с названием переменной
//! @param [in] x    Значение этой переменной полученное от solve_equat()
//! @param [in] x0   Верное значение
//!
//! @note Печатает значение NAN как строку "NAN"
//!
//! @note Подфункция для check()
//-----------------------------------------------------------------------------------------------------------------------------------

void output_smart(const char * str, const double x, const double x0) {

   printf("%10s = ", str);

   if (isnan(x)) printf("NAN");
   else printf("%.3lf", x);

   printf(" (inst. ");

   if (isnan(x0)) printf("NAN)");
   else printf("%.3lf)", x0);
}

//-----------------------------------------------------------------------------------------------------------------------------------
//! Считывает тесты из файла и запускает их
//!
//! @param [in] fp Указатель на файл откуда ведётся чтение
//!
//! @return Статус завершения функции
//!
//! @note Подсчитывает колво успешных и проваленных тестов и выводит его на экран
//! @note Если передан нулевой указатель на файл возвращает NULL_FILE_MSG
//! @note В случае ошибки чтения возращает FAILURE_MSG
//!
//! @note Подфункция для mode_tester()
//-----------------------------------------------------------------------------------------------------------------------------------
enum Messages test_solve_equat(FILE * fp) {

      if (fp == NULL)
          return NULL_FILE_MSG;

      struct Equat reference {
        { NAN, NAN, NAN },
        { ERR_SOLUT, NAN, NAN }
      };

    int int_SOLVES = -2;
    int all_tests = NAN, succ_tests = 0;
    char * content_file = NULL;
    long pos = NAN;
    int shift = NAN;

    content_file = file_to_string(fp);

    printf("%s", content_file);
    pos = skip_string_in_filestring(content_file);

    

    sscanf(content_file + pos, "%d %n", &all_tests, &shift);

    pos += shift;

    if (isnan(all_tests))
          return FAILURE_MSG;


    for (int i = 0; i < all_tests; i++)  {


        if (sscanf(content_file + pos, "%lf %lf %lf %d %lf %lf %n", &reference.coef.a, &reference.coef.b, &reference.coef.c, &int_SOLVES, &reference.roots.x1, &reference.roots.x2, &shift) != 6)
            return FAILURE_MSG;

        
        pos += shift;

        //if (is_end_of_string(content_file + pos) == FAILURE_MSG) return FAILURE_MSG;  ПОЧЕМУ НЕ РАБОТАЕТ


        reference.roots.amt = (enum Solution) int_SOLVES;

        if (analys(&reference.roots) == FAILURE_MSG)
            return FAILURE_MSG;

        succ_tests += check(reference);

        reference = {
        { NAN, NAN, NAN },
        { ERR_SOLUT, NAN, NAN }
        };

        printf("\n\n");
    }

    printf("All tests: %d.  Completed: %d.  Failed: %d.", all_tests, succ_tests, (all_tests - succ_tests));

    free(content_file);

    return SUCCESS_MSG;
}



//-----------------------------------------------------------------------------------------------------------------------------------
//! Запускает режим тестировщика
//!
//! @return Статус завершения функции
//!
//! @note Возвращает 1 если возникла ошибка, 0 в противном случае
//! @note Если во время выполнения возникла ошибка, выводит в stderr сообщение, в чём она заключается
//-----------------------------------------------------------------------------------------------------------------------------------

int mode_tester(const char * file_name) {
    FILE * fp = NULL;
    fp = fopen(file_name, "rb");

    enum Messages message_test = INIT_MSG;

    switch (test_solve_equat(fp)) {

          case INIT_MSG:
                fprintf(stderr, "Error:  test_solve_equat() hasn't started");
                return 1;

          case FAILURE_MSG:
                fprintf(stderr, "Error:  incorrect file content");
                return 1;

          case NULL_FILE_MSG:
                fprintf(stderr, "Error:  cannot open file");
                return 1;
        }
    return 0;
}

//-----------------------------------------------------------------------------------------------------------------------------------
//! Меняет значения отсутвующих корней на NAN
//!
//! @param [out] pts Указатель на структуру типа Roots со считанными из файла корнями
//!
//! @return Статус завершения функции
//!
//! @note Если pts->amt = ERR_SOLUT - возвращает значение ошибки
//!
//! @note Подфункция для test_solve_equat()
//-----------------------------------------------------------------------------------------------------------------------------------

enum Messages analys(struct Roots * const pst) {

      switch (pst->amt) {

        case INF_SOLUT:
        case NO_SOLUT:
           pst->x1 = pst->x2 = NAN;
           break;

        case ONE_SOLUT:
           pst->x2 = NAN;
           break;

        case TWO_SOLUT:
           break;

        default:
           return FAILURE_MSG;  
      }

      return SUCCESS_MSG;
}







