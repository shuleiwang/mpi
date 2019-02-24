/******************************************************************************/
//@File      mpi.h
//@Brief     Multiple precesion integer arithmetic library.References from MPI 
//******     and LibTomMath.
//@Author    Shulei Wang, shulwang2g@gmail.com
//@License   The code is free for all purposes without any express guarantee 
//@*******   it works.(Public Domain)
/******************************************************************************/

#ifndef MPI_H
#define MPI_H

#include "../unsigned_mpi/us_mpi.h" 

// mpi: multiple precesion integer
namespace mpi 
{
    using us_mpi::UsMpi;

    enum MpiSign 
    {
        eMpiZpos = 0, // positive integer
        eMpiNeg  = 1, // negative
    };

    class Mpi
    {
        private:
            int sign_;
            UsMpi abs_;
    };
}

#endif /* MPI_H */

