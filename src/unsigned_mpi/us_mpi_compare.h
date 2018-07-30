/******************************************************************************/
//@File      us_mpi_compare.h
//@Brief     Multiple precesion integer arithmetic library.References from MPI 
//******     and LibTomMath.
//@Author    Shulei Wang, shulwang2g@gmail.com
//@License   The code is free for all purposes without any express guarantee 
//@*******   it works.(Public Domain)
/******************************************************************************/

#ifndef US_MPI_COMPARE_H
#define US_MPI_COMPARE_H 

#include "us_mpi.h" 

namespace us_mpi 
{
    /* Unsigned mpi compare with unsigned mpi */
    bool operator<(const UsMpi &a, const UsMpi &b);
    bool operator>(const UsMpi &a, const UsMpi &b);
    bool operator<=(const UsMpi &a, const UsMpi &b);
    bool operator>=(const UsMpi &a, const UsMpi &b);
    bool operator==(const UsMpi &a, const UsMpi &b);
    bool operator!=(const UsMpi &a, const UsMpi &b);

    /* Unsigned mpi compare with single digit */
    bool operator<(const UsMpi &a, const Digit b);
    bool operator<=(const UsMpi &a, const Digit b);
    bool operator>(const UsMpi &a, const Digit b);
    bool operator>=(const UsMpi &a, const Digit b);
    bool operator==(const UsMpi &a, const Digit b);
    bool operator!=(const UsMpi &a, const Digit b);
}

#endif /* US_MPI_COMPARE_H */

