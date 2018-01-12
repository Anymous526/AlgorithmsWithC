#ifndef LEX_H
#define LEX_H

#include "chtbl.h"

/*Define the tocken recognized by the lexical analyzer. */
typedef enum Token_ {
    lexit, error, digit, other
}Token;

/*public Interface*/
Token lex(const char *istream, CHTbl *systbl);

#endif // LEX_H
