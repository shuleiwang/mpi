/******************************************************************************/
//@File      mpi.cpp
//@Brief     Multiple precesion integer arithmetic library.References from MPI 
//******     and LibTomMath.
//@Author    Shulei Wang, shulwang2g@gmail.com
//@License   The code is free for all purposes without any express guarantee 
//@*******   it works.(Public Domain)
/******************************************************************************/

#include "mpi.h" 
#include "../mpi_abs/mpi_abs_compare.h" 
#include "../mpi_abs/mpi_abs_basic_arithmetic.h" 

namespace multiple_precesion_integer
{
    /*------------------------------------------------------------------------*/
    /* MPI class public member functions                                      */
    /* Basic arithmetic in class                                              */
    MPI& MPI::operator+=(const MPI &kB)
    {
        if (sign_ == kB.sign_)
            abs_ += kB.abs_;
        else
        {
            if (abs_ < kB.abs_)
            {
                sign_ = kB.sign_;
                abs_ = kB.abs_ - abs_;
            }
            else
                abs_ -= kB.abs_;
        }
        return *this;
    }

    MPI& MPI::operator-=(const MPI &kB)
    {
        if (sign_ != kB.sign_)
            abs_ += kB.abs_;
        else
        {
            if (abs_ >= kB.abs_)
                abs_ -= kB.abs_;
            else
                sign_ = (sign_ == kMpiZpos) ? kMpiNeg : kMpiZpos;
                abs_ = kB.abs_ - abs_;
        }

        return *this;
    }
}
