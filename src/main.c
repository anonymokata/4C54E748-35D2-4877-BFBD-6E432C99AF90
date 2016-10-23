#include "infix2rpn.h"
#include "rpn2infix.h"

#include <stdio.h>
#include <check.h>
#include <string.h>

static void check_infix2rpn(const char * input_str, const char * gold_result)
{
  const char * converted = infix2rpn_convert(
    input_str, strlen(input_str));
  ck_assert_str_eq(converted, gold_result);
}

START_TEST (test0_forward)
{
  check_infix2rpn("a+b-c", "abc-+");
}
END_TEST

START_TEST (test1_forward)
{
  check_infix2rpn("(a+b)-c", "ab+c-");
}
END_TEST

START_TEST (test2_forward)
{
  check_infix2rpn("l/m^n*o-p", "lmn^/o*p-");
}
END_TEST

START_TEST (test3_forward)
{
  check_infix2rpn("((l/(m^n))*o)-p", "lmn^/o*p-");
}
END_TEST

START_TEST (test4_forward)
{
  check_infix2rpn("((v/w)^x)*(y-z)", "vw/x^yz-*");
}
END_TEST

START_TEST (test5_forward)
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

  tcase_add_test(tc_core, test0_forward);
  tcase_add_test(tc_core, test1_forward);
  tcase_add_test(tc_core, test2_forward);
  tcase_add_test(tc_core, test3_forward);
  tcase_add_test(tc_core, test4_forward);
  tcase_add_test(tc_core, test5_forward);
  suite_add_tcase(s, tc_core);

  return s;
}

static void check_rpn2infix(const char * input_str, const char * gold_result)
{
  const char * converted = rpn2infix_convert(
    input_str, strlen(input_str));
  ck_assert_str_eq(converted, gold_result);
}

START_TEST (test0_reverse)
{
  check_rpn2infix("abc-+", "a+b-c");
}
END_TEST

START_TEST (test1_reverse)
{
  check_rpn2infix("ab+c-", "(a+b)-c");
}
END_TEST

START_TEST (test2_reverse)
{
  check_rpn2infix("lmn^/o*p-", "l/m^n*o-p");
}
END_TEST

START_TEST (test3_reverse)
{
  check_rpn2infix("vw/x^yz-*", "(v/w)^x*(y-z)");
}
END_TEST

START_TEST (test4_reverse)
{
  check_rpn2infix("ag+ba-c+cedf^*+^*", "(a+g)*(b-a+c)^(c+e*d^f)");
}
END_TEST

Suite * rpn2infix_suite(void)
{
  Suite *s;
  TCase *tc_core;

  s = suite_create("rpn2infix");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test0_reverse);
  tcase_add_test(tc_core, test1_reverse);
  tcase_add_test(tc_core, test2_reverse);
  tcase_add_test(tc_core, test3_reverse);
  tcase_add_test(tc_core, test4_reverse);
  suite_add_tcase(s, tc_core);

  return s;
}

int main(int argc, char * argv[])
{
  int number_failed1;
  int number_failed2;
  Suite *s1, *s2;
  SRunner *sr1, *sr2;

  s1 = infix2rpn_suite();
  sr1 = srunner_create(s1);

  srunner_run_all(sr1, CK_NORMAL);
  number_failed1 = srunner_ntests_failed(sr1);
  srunner_free(sr1);

  s2 = rpn2infix_suite();
  sr2 = srunner_create(s2);

  srunner_run_all(sr2, CK_NORMAL);
  number_failed2 = srunner_ntests_failed(sr2);
  srunner_free(sr2);

  return 0;
}
