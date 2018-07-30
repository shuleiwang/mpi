/******************************************************************************/
//@File      us_mpi_shift.h
//@Brief     Multiple precesion integer arithmetic library.References from MPI 
//******     and LibTomMath.
//@Author    Shulei Wang, shulwang2g@gmail.com
//@License   The code is free for all purposes without any express guarantee 
//@*******   it works.(Public Domain)
/******************************************************************************/

#ifndef US_MPI_SHIFT_H
#define US_MPI_SHIFT_H 

#include "us_mpi.h" 

namespace us_mpi
{
    // Shifts left a certain amount of digits: b = a * beta**n  
    UsMpi& operator<<=(UsMpi &a, const DigitNum shift_dig_num);
    UsMpi operator<<(const UsMpi &a, const DigitNum shift_dig_num);
    // Shifts right a certain amount of digits: b = a / beta**n  
    UsMpi& operator>>=(UsMpi &a, const DigitNum shift_dig_num);
    UsMpi operator>>(const UsMpi &a, const DigitNum shift_dig_num);

    void // Shifts left a certain bit count: b = a * 2**n
    LeftShiftInBit(const UsMpi &a, const DigitNum shift_bit_num, UsMpi &b);
    void // Shifts right a certain bit count: b = a / 2**n
    RightShiftInBit(const UsMpi &a, const DigitNum shift_bit_num, UsMpi &b);
}

#endif /* US_MPI_SHIFT_H */

