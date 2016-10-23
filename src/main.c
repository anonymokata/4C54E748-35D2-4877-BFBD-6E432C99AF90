#include "infix2rpn.h"

#include <stdio.h>
#include <check.h>
#include <string.h>

static void check_infix2rpn(const char * input_str, const char * gold_result)
{
  const char * converted = infix2rpn_convert(
    input_str, strlen(input_str));
  ck_assert_str_eq(converted, gold_result);
}

START_TEST (test0)
{
  check_infix2rpn("a+b-c", "abc-+");
}
END_TEST

START_TEST (test1)
{
  check_infix2rpn("(a+b)-c", "ab+c-");
}
END_TEST

START_TEST (test2)
{
  check_infix2rpn("l/m^n*o-p", "lmn^/o*p-");
}
END_TEST

START_TEST (test3)
{
  check_infix2rpn("((l/(m^n))*o)-p", "lmn^/o*p-");
}
END_TEST

START_TEST (test4)
{
  check_infix2rpn("((v/w)^x)*(y-z)", "vw/x^yz-*");
}
END_TEST

START_TEST (test5)
{
  check_infix2rpn("(a+g)*(((b-a)+c)^(c+(e*(d^f))))", "ag+ba-c+cedf^*+^*");
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
  tcase_add_test(tc_core, test2);
  tcase_add_test(tc_core, test3);
  tcase_add_test(tc_core, test4);
  tcase_add_test(tc_core, test5);
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
