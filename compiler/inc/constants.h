#ifndef CONSTANTS_H_INCLUDED
#define CONSTANTS_H_INCLUDED

#define CONST_FOR_ELEM_T "%lf"

typedef double elem_t;                                      //set default stack type

static const char* INPUT_FILE        = "solve_square.txt";
static const char* ASSEMBLER_FILE    = "assembler.bin";
static const char* OUTPUT_FILE       = "output.txt";
static const char* DISASSEMBLER_FILE = "disassembler.txt";

static const double EPSILON          = 0.0001;              //to compare two double value

static const int S_LENGTH            = 255;                 //maximum string length
static const int AVG_COMMAND         = 3;                   //average argument in command
static const int LABELS_LENGTH       = 80;                  //max labels
static const int RAM_LENGTH          = 10000;               //RAM size
static const int STD_LENGTH_STACK    = 20;                  //default stack length
static const int POISON_BYTE         = 127;                 //poison for memset
static const int POISON_STACK        = 23546862;            //canary in stack

#endif // CONSTANTS_H_INCLUDED
