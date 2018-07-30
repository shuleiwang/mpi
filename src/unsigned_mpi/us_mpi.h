/******************************************************************************/
//@File      us_mpi.h
//@Brief     Multiple precesion integer arithmetic library.References from MPI 
//******     and LibTomMath.
//@Author    Shulei Wang, shulwang2g@gmail.com
//@License   The code is free for all purposes without any express guarantee 
//@*******   it works.(Public Domain)
/******************************************************************************/

#ifndef US_MPI_H
#define US_MPI_H 

#include <stdexcept> 
#include <vector> 

// us_mpi:: unsigned multiple precision integer
namespace us_mpi 
{
    using std::range_error;

    typedef unsigned char Byte;
    // The bit number of Digit depends on specific machine. 
    typedef unsigned int Digit; // 4 bytes type
    // The bit numer of Word must be double Digit.
    typedef unsigned long long Word; // 8 bytes type

    typedef std::vector<Digit>::size_type DigitNum;
    typedef std::vector<Digit>::iterator Iter;
    typedef std::vector<Digit>::const_iterator CstIter;
    typedef std::vector<Digit>::reverse_iterator RvsIter;
    typedef std::vector<Digit>::const_reverse_iterator CstRvsIter;

    enum DigitParam
    {
        eCharBit = 8,
        eDigitBitNum = 28,
        eDigitMask = 0x0FFFFFFF
        // eDigitMask = (1 << kDigitBitNum) - 1
    };

    class UsMpi
    {
        public:
            UsMpi(): us_mpi_(1, 0) { }
            explicit UsMpi(const DigitNum digit_num): us_mpi_(digit_num, 0) { }
            UsMpi(const DigitNum digit_num, const Digit val):
                us_mpi_(digit_num, val) { }

            UsMpi& operator=(const UsMpi &b);
            UsMpi& operator=(const Digit &b) 
            {
                us_mpi_.resize(1, b);
                return *this;
            }

            Digit& operator[](const DigitNum sub_idx)
            { 
                if (sub_idx >= us_mpi_.size())
                    throw range_error("sub idx is too large!");

                return us_mpi_[sub_idx];
            }
            const Digit& operator[](const DigitNum sub_idx) const
            { 
                if (sub_idx >= us_mpi_.size())
                    throw range_error("sub idx is too large!");

                return us_mpi_[sub_idx];
            }

        public:
            void GrowDigNum(const DigitNum dig_num) 
            {
                us_mpi_.resize(us_mpi_.size() + dig_num, 0);
            } 

            void Trim() 
            {
                while (!us_mpi_.empty() && (*(us_mpi_.end() - 1) == 0)) 
                    us_mpi_.pop_back();
            }

            DigitNum GetBitNum() const 
            {
                DigitNum bit_num = (us_mpi_.size() - 1) * eDigitBitNum;
                Digit msd = *(us_mpi_.end() - 1);
                while (msd) 
                {
                    ++bit_num;
                    msd >>= static_cast<Digit>(1);
                }

                return bit_num;
            }

            void Swap(UsMpi &b) { us_mpi_.swap(b.us_mpi_); }

            DigitNum GetDigNum() const { return us_mpi_.size(); }

            Iter GetBeginIter() { return us_mpi_.begin(); }
            Iter GetEndIter() { return us_mpi_.end(); }
            CstIter GetCbeginIter() const { return us_mpi_.begin(); }
            CstIter GetCendIter() const { return us_mpi_.end(); }

            RvsIter GetRbeginIter() { return us_mpi_.rbegin(); }
            RvsIter GetRendIter() { return us_mpi_.rend(); }
            CstRvsIter GetCrbeginIter() const { return us_mpi_.rbegin(); }
            CstRvsIter GetCrendIter() const { return us_mpi_.rend(); }

            void SetZero() { us_mpi_.resize(1, 0); }
            bool IsZero() const 
            { 
                if ((us_mpi_.size() == 1) && (us_mpi_[0] == 0))
                    return true;
                return false;
            }

        private:
            std::vector<Digit> us_mpi_;
    };

    template<typename Type> inline Type Min(Type val1, Type val2)
    {
        return val1 < val2 ? val1 : val2;
    }

    template<typename Type> inline Type Max(Type val1, Type val2)
    {
        return val1 > val2 ? val1 : val2;
    }
}

#endif /* US_MPI_H */

