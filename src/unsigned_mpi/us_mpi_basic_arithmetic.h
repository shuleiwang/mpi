/******************************************************************************/
//@File      us_mpi_basic_arithmetic.h
//@Brief     Multiple precesion integer arithmetic library.References from MPI 
//******     and LibTomMath.
//@Author    Shulei Wang, shulwang2g@gmail.com
//@License   The code is free for all purposes without any express guarantee 
//@*******   it works.(Public Domain)
/******************************************************************************/

#ifndef US_MPI_BASIC_ARITHMETIC_H
#define US_MPI_BASIC_ARITHMETIC_H

#include "us_mpi.h" 

namespace us_mpi
{
    /* Unsigned mpi basic arithmetic with antother unsigned mpi */
    UsMpi& operator+=(UsMpi &a, const UsMpi &b);
    UsMpi& operator-=(UsMpi &a, const UsMpi &b);
    UsMpi& operator*=(UsMpi &a, const UsMpi &b);
    UsMpi& operator/=(UsMpi &a, const UsMpi &b);
    UsMpi& operator%=(UsMpi &a, const UsMpi &b);

    UsMpi operator+(const UsMpi &a, const UsMpi &b);
    UsMpi operator-(const UsMpi &a, const UsMpi &b);
    UsMpi operator*(const UsMpi &a, const UsMpi &b);
    UsMpi operator/(const UsMpi &a, const UsMpi &b);
    UsMpi operator%(const UsMpi &a, const UsMpi &b);

    /* Unsigned mpi basic arithmetic with single digit */
    UsMpi& operator+=(UsMpi &a, const Digit &b);
    UsMpi& operator-=(UsMpi &a, const Digit &b);
    UsMpi& operator*=(UsMpi &a, const Digit &b);
    UsMpi& operator/=(UsMpi &a, const Digit &b);
    UsMpi& operator%=(UsMpi &a, const Digit &b);

    UsMpi operator+(const UsMpi &a, const Digit &b);
    UsMpi operator-(const UsMpi &a, const Digit &b);
    UsMpi operator*(const UsMpi &a, const Digit &b);
    UsMpi operator/(const UsMpi &a, const Digit &b);
    UsMpi operator%(const UsMpi &a, const Digit &b);

    void Square(const UsMpi &a, UsMpi b);
}

#endif /* US_MPI_BASIC_ARITHMETIC_H */
 
