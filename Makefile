flags := -Wshadow -Winit-self -Wredundant-decls -Wcast-align -Wundef -Wfloat-equal -Winline -Wunreachable-code -Wmissing-declarations -Wmissing-include-dirs -Wswitch-enum -Wswitch-default -Weffc++ -Wmain -Wextra -Wall -g -pipe -fexceptions -Wcast-qual -Wconversion -Wctor-dtor-privacy -Wempty-body -Wformat-security -Wformat=2 -Wignored-qualifiers -Wlogical-op -Wno-missing-field-initializers -Wnon-virtual-dtor -Woverloaded-virtual -Wpointer-arith -Wsign-promo -Wstack-usage=8192 -Wstrict-aliasing -Wstrict-null-sentinel -Wtype-limits -Wwrite-strings -Werror=vla -D_DEBUG -D_EJUDGE_CLIENT_SIDE

all: quad-eq

quad-eq: build/main.o build/mode_solver.o build/mode_tester.o build/util.o
	g++ $(flags) build/main.o build/mode_solver.o build/mode_tester.o build/util.o -o quad-eq

build/main.o: main.cpp
	g++ $(flags) -c main.cpp -o build/main.o

build/mode_solver.o: src/mode_solver.cpp
	g++ $(flags) -c src/mode_solver.cpp -o build/mode_solver.o

build/mode_tester.o: src/mode_tester.cpp
	g++ $(flags) -c src/mode_tester.cpp -o build/mode_tester.o

build/util.o: src/util.cpp
	g++ $(flags) -c src/util.cpp -o build/util.o

clean:
	rm -rf *.o *.exe