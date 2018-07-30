/******************************************************************************/
//@File      us_mpi_convert.h
//@Brief     Multiple precesion integer arithmetic library.References from MPI 
//******     and LibTomMath.
//@Author    Shulei Wang, shulwang2g@gmail.com
//@License   The code is free for all purposes without any express guarantee 
//@*******   it works.(Public Domain)
/******************************************************************************/

#ifndef US_MPI_CONVERT_H
#define US_MPI_CONVERT_H 

#include "us_mpi.h" 

namespace us_mpi
{

    bool ReadUnsignedBin(const Byte *bin, size_t bin_size, UsMpi &us_mpi);
    bool ToUnsignedBin(const UsMpi &us_mpi, Byte *bin);

    void ReadRadix(const std::string &radix_str, UsMpi &us_mpi);
    void ToRadix(const UsMpi& us_mpi, std::string &radix_str);

    void ByteSeqReverse(Byte *bin, size_t len);
}

#endif /* US_MPI_CONVERT_H */

