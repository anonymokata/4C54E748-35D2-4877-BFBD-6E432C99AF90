#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "infix2rpn.h"
#include "vector_char.h"

static int infix2rpn_getPrecedence(char c)
{
  switch(c)
  {
    case '^':
      return 1;
    case '/':
      return 2;
    case '*':
      return 3;
    case '-':
      return 4;
    case '+':
      return 5;
  }
}

/*
static int infix2rpn_findBasicExpIndex(const char * input, int input_len)
{
  for(int i = 1; i < input_len - 1; ++i)
  {
    if(infix2rpn_isOperator(input[i]))
    {
      if(input[i-1] != '(' && input[i+1] != ')')
      {
        return i;
      }
    }
  }
  return -1;
}
*/

static int infix2rpn_isOperator(char c)
{
  if(c == '^' || c == '/' || c == '*' ||
     c == '-' || c == '+' || c == '(')
  {
    return true;
  }
  else
  {
    return false;
  }
}

//------------------------------------------------------------------------------
// infix2rpn_convert:
//    convert from infix to rpn using Shunting-yard algorithm
//------------------------------------------------------------------------------
const char * infix2rpn_convert(const char * input, int input_len)
{
  vector_char op_stack = vectorChar_create();
  vector_char output_vec = vectorChar_create();

  for(int i = 0; i < input_len; ++i)
  {
    char token = input[i];
    if(infix2rpn_isOperator(token))
    {
      if(vectorChar_size(op_stack) > 0)
      {
        char vector_top = vectorChar_element(op_stack, 
          vectorChar_size(op_stack) - 1);

        int prec_top = infix2rpn_getPrecedence(vector_top);
        int prec_token = infix2rpn_getPrecedence(token);

        if(prec_token <= prec_top)
        {
          vectorChar_pushBack(op_stack, token);
        }
        else
        {
          vectorChar_pushBack(output_vec, vector_top);
          vectorChar_popBack(op_stack);
          vectorChar_pushBack(op_stack, token);
        }
      }
      else 
      {
        vectorChar_pushBack(op_stack, token);
      }
    } 
    else if(token == ')')
    {
      while(vectorChar_size(op_stack) > 0)
      {
        char vector_top = vectorChar_element(op_stack, 
          vectorChar_size(op_stack) - 1);
        vectorChar_pushBack(output_vec, vector_top);
        vectorChar_popBack(op_stack);
        if(vector_top == '(')
        {
          break;
        }
      }
    }
    else
    {
      vectorChar_pushBack(output_vec, token);
    }
  }

  while(vectorChar_size(op_stack) > 0)
  {
    char token = vectorChar_element(op_stack, vectorChar_size(op_stack) - 1);
    vectorChar_pushBack(output_vec, token);
    vectorChar_popBack(op_stack);
  }

  int output_len = vectorChar_size(output_vec);
  char * retval = (char *) malloc(sizeof(char) * output_len);   
  memcpy(retval, output_vec->data, sizeof(char) * output_len);
  vectorChar_destroy(op_stack);
  vectorChar_destroy(output_vec);

  printf("%s", retval);

  return retval;
}
