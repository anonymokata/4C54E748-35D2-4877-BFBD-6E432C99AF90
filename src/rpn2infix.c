#include "rpn2infix.h"
#include "infix_rpn_common.h"
#include "vector_reftype.h"
#include "vector_char.h"

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

static vector_char rpn2infix_findOperators(const char * input, int input_len)
{
  vector_char retval = vectorChar_create();

  for(int i = 0; i < input_len; ++i)
  {
    char token = input[i];
    if(infix_rpn_common_isOperator(token))
    {
      vectorChar_pushBack(retval, token);
    }
  }

  return retval;
}

//------------------------------------------------------------------------------
// rpn2infix_convert:
//    convert from rpn to infix using algorithm from [1].
//    [1] http://scanftree.com/Data_Structure/postfix-to-infix
//------------------------------------------------------------------------------
const char * rpn2infix_convert(const char * input, int input_len)
{
  vector_char operators = rpn2infix_findOperators(input, input_len);
  vector_reftype visitor_stack = vectorRefType_create();

  int operator_index = 0;

  for(int i = 0; i < input_len; ++i)
  {
    char token = input[i];
    if(infix_rpn_common_isOperator(token))
    {
      const char * stack_lhs = (const char *)
        vectorRefType_element(visitor_stack, vectorRefType_size(visitor_stack) - 1);
      vectorRefType_popBack(visitor_stack);

      const char * stack_rhs = (const char *)
        vectorRefType_element(visitor_stack, vectorRefType_size(visitor_stack) - 1);
      vectorRefType_popBack(visitor_stack);

      char token_str[2];
      token_str[0] = token;
      token_str[1] = '\0';

      int stack_lhs_len = strlen(stack_lhs);
      int stack_rhs_len = strlen(stack_rhs);

      bool need_parens = true;
      int extra_space = 4;
      if(operator_index + 1 < vectorChar_size(operators))
      {
        char next_op = vectorChar_element(operators, operator_index+1);
        
        int op0_precedence = infix_rpn_common_getPrecedence(token);
        int op1_precedence = infix_rpn_common_getPrecedence(next_op);

        if(op0_precedence > op1_precedence)
        {
          need_parens = false;
          extra_space = 2;
        }
      }
      else
      {
        need_parens = false;
        extra_space = 2;
      }

      int combined_len = stack_lhs_len + stack_rhs_len + extra_space;
      char * new_stack_element = (char *) calloc(combined_len, sizeof(char));

      if(need_parens)
      {
        strcat(new_stack_element, "(");
        strcat(new_stack_element, stack_rhs);
        strcat(new_stack_element, (const char *) token_str);
        strcat(new_stack_element, stack_lhs);
        strcat(new_stack_element, ")");
      } 
      else 
      {
        strcat(new_stack_element, stack_rhs);
        strcat(new_stack_element, (const char *) token_str);
        strcat(new_stack_element, stack_lhs);
      }

      free((void *) stack_lhs);
      free((void *) stack_rhs);

      vectorRefType_pushBack(visitor_stack, (size_t) new_stack_element);

      ++operator_index;
    }
    else 
    {
      char * visitor_operand = (char *) calloc(2, sizeof(char));
      visitor_operand[0] = token;
      vectorRefType_pushBack(visitor_stack, (size_t) visitor_operand);
    }
  }

  const char * retval = (const char *)
    vectorRefType_element(visitor_stack, 0);
  vectorRefType_destroy(visitor_stack);

  return retval;
}
