/******************************************************************************/
//@File      us_mpi_convert.cc
//@Brief     Multiple precesion integer arithmetic library.References from MPI 
//******     and LibTomMath.
//@Author    Shulei Wang, shulwang2g@gmail.com
//@License   The code is free for all purposes without any express guarantee 
//@*******   it works.(Public Domain)
/******************************************************************************/

#include <stdexcept> 
#include "../error.h"
#include "us_mpi_shift.h" 
#include "us_mpi_convert.h" 

namespace us_mpi
{
    using std::invalid_argument;

    void ByteSeqReverse(Byte *bin, size_t bin_size)
    {
        Byte *bottom = bin;
        Byte *top = bin + bin_size - 1;

        Byte tmp = 0;
        while (bottom != top)
        {
            tmp = *top;
            *top-- = *bottom;
            *bottom++ = tmp;
        }
    }

    bool ReadUnsignedBin(const Byte *bin, size_t bin_size, UsMpi &us_mpi)
    {
        if (bin == 0) {
            ShowErrorMsg(__FILE__, __FUNCTION__, __LINE__,
                "The pointer to binary array is null!");
            return false; 
        }

        while (bin_size--) 
        {
            LeftShiftInBit(us_mpi, 8, us_mpi);
            *(us_mpi.GetBeginIter()) |= *bin++;
        }

        return true;
    }

    bool ToUnsignedBin(const UsMpi &us_mpi, Byte *bin)
    {
        if (bin == 0) {
            ShowErrorMsg(__FILE__, __FUNCTION__, __LINE__,
                "The pointer to binary array is null!");
            return false; 
        }

        UsMpi tmp(us_mpi);

        size_t idx = 0;
        while (!tmp.IsZero())
        {
            bin[idx++] = (*tmp.GetBeginIter()) & 0xFF;
            RightShiftInBit(tmp, 8, tmp);
        }

        ByteSeqReverse(bin, idx);

        return true;
    }
}

