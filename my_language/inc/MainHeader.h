#ifndef MAINHEADER_H_INCLUDED
#define MAINHEADER_H_INCLUDED

#include <string>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <assert.h>

template <typename type_t>
class TreeNode;

/*!
@brief convert type_t to int
@return int number
*/
template <typename type_t>
int MyRound(type_t num);


/*!
@brief convert operands, variable, value to str
*/
template <typename type_t>
const char* NodeDataToStr(TreeNode<type_t>* current);

#ifndef NOLATEX
FILE* BeginLatexFile(const char* output);
void CloseLatexFile(FILE*& file);
#endif // NOLATEX

#include "constants.h"

#include "Node.h"

#include "CalcTree.h"

#include "OperationArray.h"

#include "WorkString.h"

#include "NodeFunction.h"

#include "DiffRules.h"

#include "Parser.h"

#include "Assembler.h"

#endif // MAINHEADER_H_INCLUDED
