/******************************************************************************/
//@File      us_mpi_shift.cpp
//@Brief     Multiple precesion integer arithmetic library.References from MPI 
//@*****     and LibTomMath.
//@Author    Shulei Wang, shulwang2g@gmail.com
//@License   The code is free for all purposes without any express guarantee 
//@*******   it works.(Public Domain)
/******************************************************************************/

#include "us_mpi_compare.h" 
#include "us_mpi_shift.h" 

namespace us_mpi
{
    UsMpi& operator<<=(UsMpi &a, const DigitNum shift_dig_num)
    {
        if (shift_dig_num == 0)
            return a;

        a.GrowDigNum(shift_dig_num);

        auto top = a.GetEndIter() - 1;
        auto bottom = a.GetEndIter() - 1 - shift_dig_num;
        DigitNum idx = a.GetDigNum();
        for (; idx != shift_dig_num; --idx)
            *top-- = *bottom--;

        top = a.GetBeginIter();
        for (idx = 0; idx != shift_dig_num; ++idx)
            *top++ = 0;

        return a;
    }

    UsMpi operator<<(const UsMpi &a, const DigitNum shift_dig_num)
    {
        UsMpi tmp(a);
        tmp <<= shift_dig_num;
        return tmp;
    }

    UsMpi& operator>>=(UsMpi &a, const DigitNum shift_dig_num)
    {
        if (shift_dig_num == 0)
            return a;

        if (a.GetDigNum() <= shift_dig_num)
        {
            a.SetZero();
            return a;
        }

        auto top = a.GetBeginIter() + shift_dig_num;
        auto bottom = a.GetBeginIter();
        DigitNum idx = 0;
        for (; idx != a.GetDigNum() - shift_dig_num; ++idx)
            *bottom++ = *top++;
        for (; idx != a.GetDigNum(); ++idx)
            *bottom++ = 0;

        a.Trim();
        return a;
    }

    UsMpi operator>>(const UsMpi &a, const DigitNum shift_dig_num)
    {
        UsMpi tmp(a);
        tmp >>= shift_dig_num;
        return tmp;
    }

    void LeftShiftInBit(const UsMpi &a, const DigitNum shift_bit_num, UsMpi &b)
    {
        if (a != b) { b = a; }

        if (shift_bit_num == 0) { return; }

        b.GrowDigNum(shift_bit_num / eDigitBitNum + 1);
        b <<= (shift_bit_num / eDigitBitNum);

        DigitNum remain_bit = shift_bit_num % eDigitBitNum;
        if (remain_bit != 0)
        {
            Digit mask = (static_cast<Digit>(1) << remain_bit) - 1;
            DigitNum shift_num = eDigitBitNum - remain_bit;
            Digit carry1 = 0;
            Digit carry2 = 0;
            auto iter = b.GetBeginIter();
            for (; iter != b.GetEndIter() - 1; ++iter)
            {
                carry2 = (*iter >> shift_num) & mask;
                *iter = (*iter | carry1) & eDigitMask;
                carry1 = carry2;
            }
            if (carry1 != 0)
                *iter = carry1;
        }

        b.Trim();
        return;
    }

    void RightShiftInBit(const UsMpi &a, const DigitNum shift_bit_num, UsMpi &b)
    {
        if (a != b) { b = a; }

        if (shift_bit_num == 0) { return; }

        b >>= (shift_bit_num / eDigitBitNum);

        DigitNum remain_bit = shift_bit_num % eDigitBitNum;
        if (remain_bit != 0)
        {
            Digit carry1 = 0;
            Digit carry2 = 0;
            Digit mask = (static_cast<Digit>(1) << remain_bit) - 1;
            DigitNum shift_cnt = eDigitBitNum - remain_bit;
            auto iter = b.GetRbeginIter();
            for (; iter != b.GetRendIter(); ++iter)
            {
                carry2 = *iter & mask;
                *iter = (carry1 << shift_cnt) | (*iter >> remain_bit);
                carry1 = carry2;
            }
        }

        b.Trim();
        return; 
    }
}

