#ifndef UNIT_H
#define UNIT_H



const double DELTA = 1.0e-5;

enum Solution {

    ONE_SOLUT = 1,
    TWO_SOLUT = 2,
    NO_SOLUT  = 0,
    INF_SOLUT = -1,
    ERR_SOLUT = -2,

};

enum Messages {

    SUCCESS_MSG = 0,
    FAILURE_MSG = -1,
    TOOMUCH_INPUTS_MSG = 1,
    QUIT_MSG = 2,
    NULL_FILE_MSG = 3,
    INIT_MSG = 4

};

enum Modes {

   INC_INPUT = 0,
   SOLVER = 1,
   TESTER = 2,
   MAIN_QUIT = 3

};



struct Coef {
    double a, b, c;
};

struct Roots {
    enum Solution amt;
    double x1, x2; 
};

struct Equat {
    struct Coef coef;
    struct Roots roots;
};


//решает ВВЕДЁННОЕ ур-е, возвращает колво решений и записывает их в *p1, *p2
struct Roots solve_equat(const struct Coef coef);

// подчищает буфер
void eat_left_string(FILE * fp);

//сравнивает даблы
bool compare_double(double your, double sample);

//мэин: выбирает режим
enum Modes select_mode(void);
enum Modes cmd_select_mode(const char* str);

//режим тестировщика
int mode_tester(void);

// режим решателя
int mode_solver(void);

//пф для solve_equat()
enum Solution solve_linar(const double b, const double c, double * p1);
enum Messages solve_quadrat(const struct Coef coef, struct Roots * const p);



#endif // UNIT_H
