CC = gcc -lstdc++
GCOVFLAGS = -coverage
WCHECK = -std=c++17 -g
WFLAGS = -Wall -Werror -Wextra
CHECKFLAGS = -lgtest -lm

all: s21_matrix_oop.a test

s21_matrix_oop.a: clean
	$(CC) $(WCHECK) $(WFLAGS) -c s21_matrix_oop.cpp
	ar rcs s21_matrix_oop.a *.o

clean:
	rm -rf *.o *.a *.gcno *.gcda *.info *.out *.gch *.dSYM tests report build

test:
	$(CC) $(CHECKFLAGS) s21_matrix_oop.cpp  s21_matrix_oop_test.cpp -o tests
	./tests

rebuild: clean all

gcov_report: test
	$(CC) $(GCOVFLAGS) $(CHECKFLAGS) *.cpp -o tests
	./tests
	lcov -t “tests” -o tests.info -c -d . --no-external
	genhtml -o report tests.info
	open report/index.html

linter:
	@cp ../materials/linters/CPPLINT.cfg ./
	@python3 ../materials/linters/cpplint.py --extensions=cpp *.cpp *.h
	@rm -rf CPPLINT.cfg

cppcheck:
	cppcheck --std=c++17 --enable=all --language=c++ --suppress=missingIncludeSystem *.cpp *.h

leaks: clean test
	CK_FORK=no leaks --atExit -- ./tests
	leaks --atExit -- ./tests
