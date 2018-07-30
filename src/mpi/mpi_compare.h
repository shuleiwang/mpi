/******************************************************************************/
//@File      mpi_compare.h
//@Brief     Multiple precesion integer arithmetic library.References from MPI 
//******     and LibTomMath.
//@Author    Shulei Wang, shulwang2g@gmail.com
//@License   The code is free for all purposes without any express guarantee 
//@*******   it works.(Public Domain)
/******************************************************************************/

#ifndef MPI_COMPARE_H
#define MPI_COMPARE_H 

#include "mpi.h" 

namespace multiple_precesion_integer
{
    /* Signed mpi compare */
    bool operator<(const MPI &kA, const MPI &kB);
    bool operator<=(const MPI &kA, const MPI &kB);
    bool operator>(const MPI &kA, const MPI &kB);
    bool operator>=(const MPI &kA, const MPI &kB);
    bool operator==(const MPI &kA, const MPI &kB);
    bool operator!=(const MPI &kA, const MPI &kB);
}

#endif /* MPI_COMPARE_H */
