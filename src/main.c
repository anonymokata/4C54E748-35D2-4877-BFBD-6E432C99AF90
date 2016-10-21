#include "infix2rpn.h"

#include <stdio.h>
#include <check.h>
#include <string.h>

START_TEST (test0)
{
  const char * input_str = "a+b-c";

  const char * converted = infix2rpn_convert(
    input_str, strlen(input_str));
  
  const char * gold_result = "abc-+";

  ck_assert_str_eq(converted, gold_result);
}
END_TEST

START_TEST (test1)
{
  const char * input_str = "(a+b)-c";

  const char * converted = infix2rpn_convert(
    input_str, strlen(input_str));
  
  const char * gold_result = "ab+c-";

  ck_assert_str_eq(converted, gold_result);
}
END_TEST

Suite * infix2rpn_suite(void)
{
  Suite *s;
  TCase *tc_core;

  s = suite_create("infix2rpn");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test0);
  tcase_add_test(tc_core, test1);
  suite_add_tcase(s, tc_core);

  return s;
}

int main(int argc, char * argv[])
{
  int number_failed;
  Suite *s;
  SRunner *sr;

  s = infix2rpn_suite();
  sr = srunner_create(s);

  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return (number_failed == 0) ? 1 : -1;
}
