SRC     := Piece.cxx Joueur.cxx Echiquier.cxx
EXE     := testPiece
GTEST   := testGtest
LIBNAME := Echecs
OBJ     := ${SRC:.cxx=.o}

CC      := g++
CFLAGS  := -g -std=c++11 --coverage
# -fsanitize=address -fno-omit-frame-pointer
LDFLAGS := -L. --coverage

NAME    := $(LIBNAME)_$(shell uname -m)-$(shell uname -s)
SNAME   := lib$(NAME).a
DNAME   := lib$(NAME).so
LDLIBS  := -l$(NAME)
AR      :=  ar
ARFLAGS := -rv

all: $(EXE) clean-coverage

$(SNAME): $(OBJ)
	$(AR) $(ARFLAGS) $@ $^

$(DNAME): LDFLAGS += -shared
$(DNAME): CFLAGS += -fPIC
$(DNAME): $(OBJ)
	$(CC) $(LDFLAGS) $^ -o $@

export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:.
#$(EXE): $(DNAME) $(EXE).cxx
$(EXE): $(SNAME) $(EXE).cxx
	$(CC) $(CFLAGS) $(EXE).cxx $(LDFLAGS) $(LDLIBS) -o $(EXE)

cov: $(EXE)
	./$(EXE)
	lcov --directory . --capture --output-file coverage.lcov
	lcov --summary coverage.lcov
	python lcov_cobertura.py coverage.lcov --output coverage.xml
	gcovr -r .

cov-html: cov
	gcovr -r . --html -o coverage.html --html-details
	#open coverage.html

doc:
	doxygen
	#open doc/html/index.html

filelist.txt:
	git ls-files | grep "\.[ch]" > filelist.txt

cppcheck: filelist.txt
	cppcheck -v -f --language=c++ --enable=all --xml --xml-version=2 --file-list=./filelist.txt 2> check.xml

cppcheck-html: cppcheck
	cppcheck-htmlreport --source-dir=. --report-dir=check --file=check.xml
	#open check/index.html

rats: filelist.txt
	rats -w 3 --xml `cat filelist.txt` > rats.xml

rats-html:
	rats -w 3 --html `cat filelist.txt` > rats.html
	#open rats.html

sonarqube:
	sonar-scanner
	#open http://localhost:9000/dashboard/index/mes:echecs
	#(first start : sonar console)
	#(admin/admin)

valgrind:
	valgrind --leak-check=full ./$(EXE)

googletest:
	(git clone git://github.com/google/googletest.git ; cd googletest ; mkdir build ; cd build ; cmake .. ; make)

gtest: $(SNAME) googletest
	$(CC) $(CFLAGS) $(GTEST).cxx $(LDFLAGS) $(LDLIBS) -lgtest -lpthread -I./googletest/googletest/include -L./googletest/build/lib -o $(GTEST)
	./$(GTEST)

-include ${OBJ:.o=.d}

%.o: %.cxx
	$(CC) $(CFLAGS) -c $*.cxx -o $*.o
	$(CC) $(CFLAGS) -MM $*.cxx > $*.d

clean-coverage:
	@rm -f *.gcda

clean:
	@rm -f $(OBJ) $(EXE).o $(EXE) $(GTEST) $(SNAME) $(DNAME) filelist.txt *~ *.xml *.html *.lcov *.gcda *.gcno *.d
	@rm -rf build doc check *.dSYM

gclean:
	@rm -rf googletest