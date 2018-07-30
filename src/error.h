/******************************************************************************/
//@File      error.h
//@Brief     Build error message report machanism.
//@Author    Shulei Wang, shulwang2g@gmail.com
//@License   The code is free for all purposes without any express guarantee 
//@*******   it works.(Public Domain)
/******************************************************************************/

#ifndef ERROR_H
#define ERROR_H 

#include <string>

/******************************************************************************
** error message include: 
** file name
** function name
** line number
** error reason
*******************************************************************************/

void ShowErrorMsg(const std::string &file_name, const std::string &func_name, 
        const int line_num, const std::string &reason);

#endif /* ERROR_H */

