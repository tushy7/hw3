CXX := g++
CXXFLAGS := -g -Wall --std=c++11
VALGRIND := valgrind --tool=memcheck --leak-check=yes

OBJS = llrec.o llrec-test.o
all: llrec-test

#-----------------------------------------------------
# ADD target(s) to build your llrec-test executable
#-----------------------------------------------------
llrec-test: $(OBJS)
	$(CXX) $(CXXFLAGS) $(DEFS) -o $@ $(OBJS)

llrec.o: llrec.h llrec.cpp
	$(CXX) $(CXXFLAGS) $(DEFS) -c llrec.cpp -o $@

llrec-test.o: llrec.h llrec-test.cpp
	$(CXX) $(CXXFLAGS) $(DEFS) -c llrec-test.cpp -o $@

clean:
	rm -f *.o rh llrec-test *~

.PHONY: clean 