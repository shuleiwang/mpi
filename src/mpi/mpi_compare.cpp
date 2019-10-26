/******************************************************************************/
//@File      mpi_compare.cpp
//@Brief     Multiple precesion integer arithmetic library.References from MPI 
//******     and LibTomMath.
//@Author    Shulei Wang, shulwang2g@gmail.com
//@License   The code is free for all purposes without any express guarantee 
//@*******   it works.(Public Domain)
/******************************************************************************/

#include "mpi_compare.h" 
#include "../mpi_abs/mpi_abs_compare.h" 

namespace multiple_precesion_integer
{
    /**************************************************************************/
    /* Signed mpi compare                                                     */
    bool operator<(const MPI &kA, const MPI &kB)
    {
        if (kA.get_sign_() != kB.get_sign_())
            return (kA.get_sign_() == kMpiNeg) ? true : false;
        else
        {
            if (kA.get_sign_() == kMpiNeg)
                return (kA.get_abs_() > kB.get_abs_()) ? true : false;
            else
                return (kA.get_abs_() < kB.get_abs_()) ? true : false;
        }
    }

    bool operator<=(const MPI &kA, const MPI &kB)
    {
        if (kA.get_sign_() != kB.get_sign_())
            return (kA.get_sign_() == kMpiNeg) ? true : false;
        else
        {
            if (kA.get_sign_() == kMpiNeg)
                return (kA.get_abs_() >= kB.get_abs_()) ? true : false;
            else
                return (kA.get_abs_() <= kB.get_abs_()) ? true : false;
        }
    }

    bool operator>(const MPI &kA, const MPI &kB)
    {
        return (kA <= kB) ? false : true;
    }

    bool operator>=(const MPI &kA, const MPI &kB)
    {
        return (kA < kB) ? false : true;
    }

    bool operator==(const MPI &kA, const MPI &kB)
    {
        return (kA < kB || kA > kB) ? false : true;
    }

    bool operator!=(const MPI &kA, const MPI &kB)
    {
        return (kA == kB) ? false : true;
    }
}

