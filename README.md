# RPN_CONV

RPN_CONV is a library that converts between RPN and INFIX. It is written in standard C99 and uses the Check unit testing framework ([1]). 

INFIX expressions are mathematical expressions that are commonly used in many places that math is used. And infix expression for the next item of a Linear Congruential Generator ([2]) is below.
```
((1103515245 * rand_prev) + 12345) % 2147483648
```
RPN stands for Reverse Polish Notation and can be used for mechanical or digital calculators. An RPN expression for the same equation of the LCG is below.
```
[1103515245,rand_prev,*,12345,+,2147483648,%]
```
Note: only single character variables are allowed in RPN_CONV and there is no modulus.

### API
There are two major functions in this library, one for each direction of conversion.  
  
To convert from INFIX to RPN ([3]), use the following function found in `infix2rpn.h`.

```
const char * infix2rpn_convert(const char * input, int input_len);
```

To convert from RPN to INFIX ([4]), use the following function found in `rpn2infix.h`

```
const char * rpn2infix_convert(const char * input, int input_len);
```

Once `make` is run, a static library (`librpnconv.a`) is available to include the RPN_CONV functionality in another project.

#### Example RPN_CONV Expressions
RPN_CONV supports exponentiation, division, multiplication, subtraction and addition. Some example strings that show the conversion between RPN and INFIX are shown in the table below.

RPN | INFIX
--- | ---
a+b-c | abc-+
(a+b)-c | ab+c-
l/m^n*o-p | lmn^/o*p-
(v/w)^x*(y-z) | vw/x^yz-* 

RPN_CONV simplifies parenthesis insertion when creating INFIX expressions and can be used to simplify any INFIX expression by converting to RPN and back.

### Building

To build RPN_CONV, simply type make at the command line
```
~/libraries/rpn_conv$ make
```
After this command is run, the `rpn_conv` file is made.

### Running

To run the RPN_CONV tdd test suite, use the `rpn_conv` command
```
~/libraries/rpn_conv$ ./rpn_conv
```
This will run two test suites, one for the forward direction and one for the reverse.
```
Running suite(s): infix2rpn
100%: Checks: 6, Failures: 0, Errors: 0
Running suite(s): rpn2infix
100%: Checks: 5, Failures: 0, Errors: 0
```

[1]: <https://libcheck.github.io/check/>
[2]: <https://en.wikipedia.org/wiki/Linear_congruential_generator>
[3]: <https://en.wikipedia.org/wiki/Shunting-yard_algorithm>  
[4]: <http://scanftree.com/Data_Structure/postfix-to-infix>
