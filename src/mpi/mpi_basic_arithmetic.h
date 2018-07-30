/******************************************************************************/
//@File      mpi_basic_arithmetic.h
//@Brief     Multiple precesion integer arithmetic library.References from MPI 
//******     and LibTomMath.
//@Author    Shulei Wang, shulwang2g@gmail.com
//@License   The code is free for all purposes without any express guarantee 
//@*******   it works.(Public Domain)
/******************************************************************************/

#ifndef MPI_BASIC_ARITHMETIC_H
#define MPI_BASIC_ARITHMETIC_H 

#include "mpi.h" 

namespace multiple_precesion_integer
{
    /* Signed mpi basic arithmetic */
    MPI operator+(const MPI &kA, const MPI &kB);
    MPI operator-(const MPI &kA, const MPI &kB);
    MPI operator*(const MPI &kA, const MPI &kB);
    MPI operator/(const MPI &kA, const MPI &kB);
}

#endif /* MPI_BASIC_ARITHMETIC_H */

