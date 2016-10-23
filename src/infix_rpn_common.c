#include "infix_rpn_common.h"
#include <stdbool.h>

int infix_rpn_common_getPrecedence(char c)
{
  switch(c)
  {
    case '^':
      return 5;
    case '/':
      return 4;
    case '*':
      return 3;
    case '-':
      return 2;
    case '+':
      return 1;
    case '(':
      return 0;
  }
}

int infix_rpn_common_isOperator(char c)
{
  if(c == '^' || c == '/' || c == '*' ||
     c == '-' || c == '+')
  {
    return true;
  }
  else
  {
    return false;
  }
}

