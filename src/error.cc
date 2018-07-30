/******************************************************************************/
//@File      error.cc
//@Brief     Build error message report machanism.
//@Author    Shulei Wang, shulwang2g@gmail.com
//@License   The code is free for all purposes without any express guarantee 
//@*******   it works.(Public Domain)
/******************************************************************************/

#include <iostream> 
#include "error.h"

using std::cout;
using std::endl;
using std::string;

void ShowErrorMsg(const std::string &file_name, const std::string &func_name, 
        const int line_num, const std::string &reason)
{
    cout << "Error message is as follows: \n" 
         << "error file name: " << file_name << '\n'
         << "error function name: " << func_name  << '\n'
         << "error line number: " << line_num << '\n'
         << "error reason: " << reason << endl;
}

