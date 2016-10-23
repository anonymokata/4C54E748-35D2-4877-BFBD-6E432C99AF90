#include "infix2rpn.h"
#include "infix_rpn_common.h"
#include "vector_char.h"

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void infix2rpn_getPrecedencePair(vector_char vec, char token, int * prec_top, 
  int * prec_token)
{
  if(vectorChar_size(vec) > 0)
  {
    char vector_top = vectorChar_element(vec, vectorChar_size(vec) - 1);
    *prec_top = infix_rpn_common_getPrecedence(vector_top);
    *prec_token = infix_rpn_common_getPrecedence(token);
  }
  else
  {
    *prec_top = -2;
    *prec_token = -1;
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

    if(infix_rpn_common_isOperator(token))
    {
      int prec_top;
      int prec_token;

      infix2rpn_getPrecedencePair(op_stack, token, &prec_top, &prec_token);

      while(prec_token <= prec_top)
      {
        char vector_top = 
          vectorChar_element(op_stack, vectorChar_size(op_stack) - 1);
        vectorChar_pushBack(output_vec, vector_top);
        vectorChar_popBack(op_stack);

        infix2rpn_getPrecedencePair(op_stack, token, &prec_top, &prec_token);
      }

      vectorChar_pushBack(op_stack, token);
    }
    else if(token == '(')
    {
      vectorChar_pushBack(op_stack, token);
    }
    else if(token == ')')
    {
      token = vectorChar_element(op_stack, vectorChar_size(op_stack) - 1);
      while(token != '(')
      {
        vectorChar_pushBack(output_vec, token);
        vectorChar_popBack(op_stack);
        if(vectorChar_size(op_stack) > 0)
        {
          token = vectorChar_element(op_stack, vectorChar_size(op_stack) - 1);
        }
        else
        {
          break;
        }
      }
      if(token == '(')
      {
        vectorChar_popBack(op_stack);
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
  char * retval = (char *) malloc(sizeof(char) * (output_len + 1));   
  memcpy(retval, output_vec->data, sizeof(char) * output_len);
  vectorChar_destroy(op_stack);
  vectorChar_destroy(output_vec);
  retval[output_len] = '\0';

  return retval;
}
