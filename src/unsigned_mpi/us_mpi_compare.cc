/******************************************************************************/
//@File      us_mpi_compare.cc
//@Brief     Multiple precesion integer arithmetic library.References from MPI 
//@*****     and LibTomMath.
//@Author    Shulei Wang, shulwang2g@gmail.com
//@License   The code is free for all purposes without any express guarantee 
//@*******   it works.(Public Domain)
/******************************************************************************/

#include "us_mpi_compare.h" 

namespace us_mpi
{
    /**************************************************************************/
    /* Unsigned mpi compare with unsigned mpi                                 */
    bool operator<(const UsMpi &a, const UsMpi &b)
    {
        if (a.GetDigNum() < b.GetDigNum())
            return true;

        if (a.GetDigNum() > b.GetDigNum())
            return false;

        auto a_iter = a.GetCrbeginIter();
        auto b_iter = b.GetCrbeginIter();
        for (; a_iter != a.GetCrendIter(); ++a_iter, ++b_iter)
        {
            if (*a_iter < *b_iter)
                return true;

            if (*a_iter > *b_iter)
                return false;
        }

        return false;
    }

    bool operator<=(const UsMpi &a, const UsMpi &b)
    {
        if (a.GetDigNum() < b.GetDigNum())
            return true;

        if (a.GetDigNum() > b.GetDigNum())
            return false;

        auto a_iter = a.GetCrbeginIter();
        auto b_iter = b.GetCrbeginIter();
        for (; a_iter != a.GetCrendIter(); ++a_iter, ++b_iter)
        {
            if (*a_iter < *b_iter)
                return true;

            if (*a_iter > *b_iter)
                return false;
        }

        return true;
    }

    bool operator>(const UsMpi &a, const UsMpi &b)
    {
        return (a <= b) ? false : true;
    }

    bool operator>=(const UsMpi &a, const UsMpi &b)
    {
        return (a < b) ? false : true;
    }

    bool operator==(const UsMpi &a, const UsMpi &b)
    {
        return (a < b || a > b) ? false : true;
    }

    bool operator!=(const UsMpi &a, const UsMpi &b)
    {
        return (a == b) ? false : true;
    }

    /**************************************************************************/
    /* Unsigned mpi compare with single Digit                                 */
    bool operator<(const UsMpi &a, const Digit b)
    {
        if (a.GetDigNum() != 1)
            return false;

        if (*(a.GetCbeginIter()) >= b)
            return false;

        return true;
    }

    bool operator<=(const UsMpi &a, const Digit b)
    {
        if (a.GetDigNum() != 1)
            return false;

        if (*(a.GetCbeginIter()) > b)
            return false;

        return true;
    }

    bool operator>(const UsMpi &a, const Digit b)
    {
        return (a <= b) ? false : true;
    }

    bool operator>=(const UsMpi &a, const Digit b)
    {
        return (a < b) ? false : true;
    }

    bool operator==(const UsMpi &a, const Digit b)
    {
        return (a < b || a > b) ? false : true;
    }

    bool operator!=(const UsMpi &a, const Digit b)
    {
        return (a == b) ? false : true;
    }
}
