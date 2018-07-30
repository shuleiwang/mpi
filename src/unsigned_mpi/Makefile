CXX = clang++
CXXFLAGS = -g --std=c++11

obj_files = test.o us_mpi.o us_mpi_basic_arithmetic.o us_mpi_compare.o \
		   	us_mpi_convert.o us_mpi_shift.o

test : ${obj_files}
	clang++ -o test ${obj_files}

test.o : test.cc
us_mpi.o: us_mpi.h
us_mpi_compare.o : us_mpi_compare.h
us_mpi_convert.o : us_mpi_convert.h us_mpi_shift.h
us_mpi_shift.o : us_mpi_shift.h us_mpi_compare.h

.PHONY : clean
clean:
	-rm *.o test
