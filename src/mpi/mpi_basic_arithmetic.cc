/******************************************************************************/
//@File      mpi_basic_arithmetic.cc
//@Brief     Multiple precesion integer arithmetic library.References from MPI 
//******     and LibTomMath.
//@Author    Shulei Wang, shulwang2g@gmail.com
//@License   The code is free for all purposes without any express guarantee 
//@*******   it works.(Public Domain)
/******************************************************************************/

#include "mpi_basic_arithmetic.h" 

namespace multiple_precesion_integer
{
    /**************************************************************************/
    /* Signed mpi basic arithmetic operation                                  */
    MPI operator+(const MPI &kA, const MPI &kB)
    {
        MPI sum(kA);
        sum += kB;
        return sum;
    }

    MPI operator-(const MPI &kA, const MPI &kB)
    {
        MPI sum(kA);
        sum -= kB;
        return sum;
    }

    MPI operator*(const MPI &kA, const MPI &kB)
    {
        MPI sum(kA);
        sum *= kB;
        return sum;
    }

    MPI operator/(const MPI &kA, const MPI &kB)
    {
        MPI sum(kA);
        sum /= kB;
        return sum;
    }

// Improvement: replace these overload operators with function template
}
