/******************************************************************************/
//@File      us_mpi_basic_arithmetic.cpp
//@Brief     Multiple precesion integer arithmetic library.References from MPI 
//******     and LibTomMath.
//@Author    Shulei Wang, shulwang2g@gmail.com
//@License   The code is free for all purposes without any express guarantee 
//@*******   it works.(Public Domain)
/******************************************************************************/

#include <stdexcept> 
#include "us_mpi_compare.h" 
#include "us_mpi_shift.h" 
#include "us_mpi_basic_arithmetic.h" 

namespace us_mpi
{
    using std::invalid_argument;

    namespace
    {
      void BasicMul(const UsMpi &a, const UsMpi &b, UsMpi &c)
      {
          UsMpi rst(a.GetDigNum() + b.GetDigNum(), 0);
          auto a_iter = a.GetCbeginIter();
          auto b_iter = b.GetCbeginIter();
          auto rst_iter = rst.GetBeginIter();

          Word tmp_val = 0;
          Digit carry = 0;
          DigitNum col_idx = 0;

          for (; a_iter != a.GetCendIter(); ++a_iter, ++rst_iter) 
          {
              carry = 0;
              col_idx = 0;
              for (; b_iter != b.GetCendIter(); ++b_iter, ++col_idx)
              {
                  tmp_val = *(rst_iter + col_idx) + *a_iter * *b_iter + carry;
                  *(rst_iter + col_idx) = 
                      tmp_val & static_cast<Word>(eDigitMask);
                  carry = tmp_val >> eDigitBitNum;
              }
          }

          rst.Trim();
          c = rst;
      }

      void CombaMul(const UsMpi &a, const UsMpi &b, UsMpi &c)
      {
          UsMpi rst(a.GetDigNum() + b.GetDigNum(), 0);

          DigitNum rst_idx = 0;
          DigitNum row_cnt = 0, row_idx = 0;
          DigitNum ta = 0, tb = 0;
          CstIter a_iter, b_iter;
          Word tmp = 0;
          for (; rst_idx != rst.GetDigNum(); ++rst_idx)
          {
              tb = Min(b.GetDigNum() - 1, rst_idx);
              ta = rst_idx - tb;

              a_iter = a.GetCbeginIter() + ta;
              b_iter = b.GetCbeginIter() + tb;

              row_cnt = Min(a.GetDigNum() - ta, tb + 1);
              for (row_idx = 0; row_idx != row_cnt; ++row_idx)
              {
                  tmp += *a_iter++ * *b_iter--;
              }

              rst[rst_idx] = tmp & static_cast<Word>(eDigitMask);
              tmp >>= eDigitBitNum;
          }
          
          rst.Trim();
          c = rst;
      }

      void KaratsubaMul(const UsMpi &a, const UsMpi &b, UsMpi &c)
      {
      }

      void ToomcookMul(const UsMpi &a, const UsMpi &b, UsMpi &c)
      {
      }

      void DivWithRemainder(const UsMpi &a, const UsMpi &b, UsMpi &q, UsMpi &r)
      {
      }
    }

    /**************************************************************************/
    /* Unsigned mpi basic arithmetic operation                                */
    UsMpi& operator+=(UsMpi &a, const UsMpi &b)
    {
        UsMpi tmp_usmpi(b);

        /* Make a is bigger */
        if (a.GetDigNum() < b.GetDigNum())
            a.Swap(tmp_usmpi);

        // Make a have enough size 
        a.GrowDigNum(1);

        Digit carry = 0;
        auto tmp_usmpi_iter = tmp_usmpi.GetCbeginIter();
        auto a_iter = a.GetBeginIter();
        for (; tmp_usmpi_iter != tmp_usmpi.GetCendIter();
               ++tmp_usmpi_iter, ++a_iter)
        {
            *a_iter += (*tmp_usmpi_iter + carry);
            carry = *a_iter >> static_cast<Digit>(eDigitBitNum);
            *a_iter &= static_cast<Digit>(eDigitMask);
        }

        for (; a_iter != a.GetEndIter() - 1; ++a_iter)
        {
            *a_iter += carry;
            carry = *a_iter >> static_cast<Digit>(eDigitBitNum);
            *a_iter &= static_cast<Digit>(eDigitMask);
        }
        *(a.GetEndIter() - 1) = carry;
    
        a.Trim();
        return a;
    }

    /* a -= b, assumes that a>=b */
    UsMpi& operator-=(UsMpi &a, const UsMpi &b)
    {
        Digit carry = 0;
        auto a_iter = a.GetBeginIter();
        auto b_iter = b.GetCbeginIter();

        for (; b_iter != b.GetCendIter(); ++b_iter, ++a_iter)
        {
            *a_iter = *a_iter - *b_iter - carry;
            carry = *a_iter >> (eCharBit * sizeof(Digit) - 1);
            *a_iter &= static_cast<Digit>(eDigitMask);
        }

        for (; a_iter != a.GetEndIter(); ++a_iter)
        {
            *a_iter -= carry;
            carry = *a_iter >> (eCharBit * sizeof(Digit) - 1);
            *a_iter &= static_cast<Digit>(eDigitMask);
        }

        a.Trim();
        return a;
    }

    UsMpi& operator*=(UsMpi &a, const UsMpi &b)
    {
        // case1: 
        if (a == 0 || b == 0) { a = 0; return a; }

        // case2:
        if (a == 1 || b == 1)
        {
            if (a == 1) { a = b; return a; }
            if (b == 1) { return a; }
        }

        // case3:
        if (a == 2 || b == 2) 
        {
            if (a == 2) {
                LeftShiftInBit(b, 1, a); 
                return a;
            } else {
                LeftShiftInBit(a, 1, a);
                return a;
            }
        }

        UsMpi tmp_usmpi(b);
        return a;
    }

    UsMpi& operator/=(UsMpi &a, const UsMpi &b)
    {
        if (b == 0) throw invalid_argument("Divisor must be not zero!");

        if (a < b) a = 0;
        if (a == b) a = 1;

        UsMpi tmpb(b);
        UsMpi q(a.GetDigNum() + 2);
        UsMpi t1(2);
        UsMpi t2(3);

        /* normalize */
        DigitNum norm = b.GetBitNum() % eDigitBitNum;
        if (norm < (eDigitBitNum - 1))
        {
            norm = eDigitBitNum - 1 - norm;
            LeftShiftInBit(a, norm, a);
            LeftShiftInBit(tmpb, norm, tmpb);
        }
        else
            norm = 0;

        DigitNum n = a.GetDigNum() - 1;
        DigitNum t = b.GetDigNum() - 1;

        /* determine leading digit */
        tmpb <<= (n - t);
        while (a >= tmpb)
        {
            ++(q[n - t]);
            a -= tmpb;
        }
        tmpb >>= (n - t);

        /* i from n down to t+1 */
        DigitNum i = 0;
        for (i = n; n != t; --n)
        {
            if (i > a.GetBitNum()) continue; 

            if (a[i] == tmpb[t])
                q[i - t - 1] = static_cast<Digit>(eDigitMask);
            else
            {
                Word tmp_word = 0;
                tmp_word = static_cast<Word>(a[i]) << eDigitBitNum;
                tmp_word |= static_cast<Word>(a[i - 1]);
                tmp_word /= static_cast<Word>(tmpb[t]);
                if (tmp_word > eDigitMask) 
                    tmp_word = static_cast<Word>(eDigitMask); 
                q[i - t - 1] = static_cast<Digit>
                    (tmp_word & (static_cast<Word>(eDigitMask)));
            }

            q[i -t - 1] = (q[i - t - 1] + 1) & eDigitMask;
            do {
                q[i -t - 1] = (q[i - t - 1] - 1) & eDigitMask;

                t1[0] = ((static_cast<int>(t) - 1) < 0) ? 0 : tmpb[t - 1];
                t1[1] = tmpb[t];
                t1 *= q[i - t - 1];

                t2[0] = ((static_cast<int>(i) - 2) < 0) ? 0 : a[i - 2];
                t2[1] = ((static_cast<int>(i) - 1) < 0) ? 0 : a[i - 1];
                t2[2] = a[i];

            } while (t1 > t2);

            t1 = tmpb * q[i - t - 1];
            t1 <<= (i - t - 1);
            a -= t1;

            if (a < 0)
            {
                t1 = tmpb;
                t1 <<= (i - t - 1);
                a += t1;
                q[i - t - 1] = (q[i - t - 1] - 1) & eDigitMask;
            }
        }

        q.Trim();
        q.Swap(a);
        return a;
    }

    UsMpi& operator%=(UsMpi &a, const UsMpi &b);

    UsMpi operator+(const UsMpi &a, const UsMpi &b)
    {
        UsMpi sum(a);
        sum += b;
        return sum;
    }

    UsMpi operator-(const UsMpi &a, const UsMpi &b)
    {
        UsMpi sub(a);
        sub -= b;
        return sub;
    }

    UsMpi operator*(const UsMpi &a, const UsMpi &b)
    {
        UsMpi mul(a);
        mul *= b;
        return mul;
    }

    UsMpi operator/(const UsMpi &a, const UsMpi &b)
    {
        UsMpi rst(a);
        rst /= b;
        return rst;
    }

    UsMpi& operator+=(UsMpi &a, const Digit &b)
    {
        if (b == 0)
            return a;

        a.GrowDigNum(1);

        Digit carry = 0;
        auto a_iter = a.GetBeginIter();

        for (; a_iter != a.GetEndIter() - 1; ++a_iter)
        {
            *a_iter += (b + carry);
            carry = *a_iter >> static_cast<Digit>(eDigitBitNum);
            *a_iter &= static_cast<Digit>(eDigitMask);
        }
        if (carry != 0)
            *a_iter = carry;

        a.Trim();
        return a;
    }

    /* assumes that a >= b */
    UsMpi& operator-=(UsMpi &a, const Digit &b)
    {
        if (b == 0)
            return a;

        Digit carry = 0;
        auto a_iter = a.GetBeginIter();

        for (; a_iter != a.GetEndIter(); ++a_iter)
        {
            *a_iter -= (b + carry);
            carry = *a_iter >> static_cast<Digit>(sizeof(Digit) * eCharBit - 1);
            *a_iter &= static_cast<Digit>(eDigitMask);
        }

        a.Trim();
        return a;
    }

    UsMpi& operator*=(UsMpi &a, const Digit &b)
    {
        if (b == 0) { return (a = 0);  }
        if (b == 1) { return a; }
        if (b == 2) {
            LeftShiftInBit(a, 1, a);
            return a;
        }

        a.GrowDigNum(1);
        Digit carry = 0;
        Word  mul = 0;
        auto a_iter = a.GetBeginIter();
        for (; a_iter != (a.GetEndIter() - 1); ++a_iter)
        {
            mul = static_cast<Word>(*a_iter) * b + carry;
            *a_iter = static_cast<Digit>(mul & static_cast<Word>(eDigitMask));
            carry = static_cast<Digit>( mul >> static_cast<Word>(eDigitBitNum));
        }
        *a_iter = carry;

        a.Trim();
        return a;
    }

    UsMpi& operator/=(UsMpi &a, const Digit &b)
    {
        if (b == 0) throw invalid_argument("divisor must not be zero!");
        if (b == 1) return a;
        if (b == 2) {
            RightShiftInBit(a, 1, a);
            return a;
        }

        Word tmp_word = 0;
        Digit tmp_dig = 0;
        auto a_iter = a.GetEndIter() - 1;
        for (; a_iter != a.GetBeginIter(); --a_iter)
        {
            tmp_word = (tmp_word << static_cast<Word>(eDigitBitNum)) |
                       static_cast<Word>(*a_iter);
            if (tmp_word >= b)
            {
                tmp_dig = tmp_word / b;
                tmp_word -= static_cast<Word>(tmp_dig * b);
            }
            else 
                tmp_dig = 0;
            *a_iter = tmp_dig;
        }

        a.Trim();
        return a;
    }

    UsMpi& operator%=(UsMpi &a, const Digit &b);

    UsMpi operator+(const UsMpi &a, const Digit &b)
    {
        UsMpi rst(a);
        rst += b;
        return rst;
    }

    UsMpi operator-(const UsMpi &a, const Digit &b)
    {
        UsMpi rst(a);
        rst -= b;
        return rst;
    }

    UsMpi operator*(const UsMpi &a, const Digit &b)
    {
        UsMpi rst(a);
        rst *= b;
        return rst;
    }

    UsMpi operator/(const UsMpi &a, const Digit &b)
    {
        UsMpi rst(a);
        rst /= b;
        return rst;
    }

    UsMpi operator%(const UsMpi &a, const Digit &b);
}
