/* 
 * CS:APP Data Lab 
 * 
 * <Please put your name and userid here>
 * 
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.  
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:
 
  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code 
  must conform to the following style:
 
  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>
    
  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.

 
  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting an integer by more
     than the word size.

EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }

FLOATING POINT CODING RULES

For the problems that require you to implent floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to 
     check the legality of your solutions.
  2. Each function has a maximum number of operators (! ~ & ^ | + << >>)
     that you are allowed to use for your implementation of the function. 
     The max operator count is checked by dlc. Note that '=' is not 
     counted; you may use as many of these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies 
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce 
 *      the correct answers.
 */


#endif
/* Copyright (C) 1991-2016 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */
/* This header is separate from features.h so that the compiler can
   include it implicitly at the start of every compilation.  It must
   not itself include <features.h> or any other header that includes
   <features.h> because the implicit include comes before any feature
   test macros that may be defined in a source file before it first
   explicitly includes a system header.  GCC knows the name of this
   header in order to preinclude it.  */
/* glibc's intent is to support the IEC 559 math functionality, real
   and complex.  If the GCC (4.9 and later) predefined macros
   specifying compiler intent are available, use them to determine
   whether the overall intent is to support these features; otherwise,
   presume an older compiler has intent to support these features and
   define these macros by default.  */
/* wchar_t uses Unicode 8.0.0.  Version 8.0 of the Unicode Standard is
   synchronized with ISO/IEC 10646:2014, plus Amendment 1 (published
   2015-05-15).  */
/* We do not support C11 <threads.h>.  */
/*
 * changeHigh : if low 16-bit of x == y, then let high 16-bit of z = x, otherwise let
 *     high 16-bit of z = y. return z.
 *   Example: changeHigh(0xaaaabbbb, 0xbbbbaaaa, 0xcccccccc) = 0xbbbbcccc,
 *   changeHigh(0xaaaabbbb, 0xddddbbbb, 0xcccccccc) = 0xaaaacccc
 *   Legal ops: ! ~ & ^ | << >>
 *   Max ops: 24
 *   Rating: 1
 */
int changeHigh(int x, int y, int z) {//solved
  int ff=0xff;
  int ffff=(ff<<8)|ff;
  int ffff0000=ffff<<16;
  int k=!((x^y)&ffff);//如果相同末尾是1，否则是0
  int k_16_high=(k<<31)>>15;
  return (z&ffff)|((x&k_16_high)|(y&((~k_16_high)&ffff0000)));
}
/* 
 * newOp - define a new bit-wise opertor PKU : 1PKU1 = 1, 1PKU0 = 1, 0PKU1 = 0, 0PKU0 = 1
 *   input int x, y return xPKUy(bit-wise)
 *   Legal ops: ! ~ & ^ |
 *   Max ops: 6
 *   Rating: 1
 */
int newOp(int x, int y) {//solved
  return x | ~y;
}
/* 
 * onlyOne - input x, y return 1 if only one bit of the two numbers is different, return 0 otherwise
 *   Examples onlyOne(12, 14) = 1, onlyOne(12, 15) = 0
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */
int onlyOne(int x, int y) {//not solved
  int differ = x ^ y;//所有不一样的位设置为1
  return (!!differ)&!(differ & (differ + (~0)));//消掉最后一位1
}
/*
 * truncAvg - Compute the average of the two numbers rounded toward 0
 *          without causing overflow
 *   Example: truncAvg(1, 10) = 5,
 *            truncAvg(-3, 6) = 1,
 *            truncAvg(-3, -4) = -3,
 *            truncAvg(0x7fffffff, 0x7fffffff) = 0x7fffffff
 *   Legal ops: ! ~ & | ^ + << >>
 *   Max ops: 12
 *   Rating: 2
 */
int truncAvg(int x, int y) {//solved
  int xor_ = x ^ y;
  int and_ = x & y;
  int Avg_ = (xor_ >> 1) + and_;
  return Avg_ + ((Avg_ >> 31) &(xor_)& 1);
}
/* 
 * absVal - absolute value of x
 *   Example: absVal(-1) = 1.
 *   You may assume -TMax <= x <= TMax
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 10
 *   Rating: 2
 */
int absVal(int x) {//solved
  int mark=(x >> 31) ;//负数全是1，正数全是0
  return (x^mark)+(mark&1);
}
/* 
 * subOK - Determine if can compute x-y without overflow
 *   Example: subOK(0x80000000,0x80000000) = 1,
 *            subOK(0x80000000,0x70000000) = 0, 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 2
 */
int subOK(int x, int y) {
  int _y = ~y + 1;
  int __1 = ((x&_y) >> 31) & 1;//取进位
  int _1 = ((x + _y) >> 31) & 1;//取首位
  return !(x^y)|!(_1^__1);
}
/*
 * fullAdd - 4-bits add using bit-wise operations only.
 *   (0 <= x, y < 16) 
 *   Example: fullAdd(12, 7) = 3,
 *            fullAdd(7, 8) = 15,
 *   Legal ops: ~ | ^ & << >>
 *   Max ops: 30
 *   Rating: 2
 */
int fullAdd(int x, int y) {//solved
  int f=0xf;
  int xor_1=x^y;
  int and_1=(x&y)<<1;//最后一位一定为0；
  int xor_2=xor_1^and_1;
  int and_2=(xor_1&and_1)<<1;
  int xor_3=xor_2^and_2;
  int and_3=(xor_2&and_2)<<1;
  return (xor_3^and_3)&f;
}
/* 
 * theMax - the same as max(x, y) 
 *   Example: max(4,5) = 5, max(6,3) = 6
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 28
 *   Rating: 3
 */
int theMax(int x, int y) {
  int _y = ~y + 1;
  int differ = (x&y&(x + _y))|(x&_y);//x-y
  int t = differ >> 31;//负数全是1，需要返回y，非负全是0，需要返回x
  return (y&t) | (x&(~t));
}
/*
 * palindrome - return 1 if x is palindrome in binary form,
 *   return 0 otherwise
 *   A number is palindrome if it is the same when reversed
 *   YOU MAY USE BIG CONST IN THIS PROBLEM, LIKE 0xFFFF0000
 *   YOU MAY USE BIG CONST IN THIS PROBLEM, LIKE 0xFFFF0000
 *   YOU MAY USE BIG CONST IN THIS PROBLEM, LIKE 0xFFFF0000
 *   Example: palindrome(0xff0000ff) = 1,
 *            palindrome(0xff00ff00) = 0
 *   Legal ops: ~ ! | ^ & << >> +
 *   Max ops: 40
 *   Rating: 4
 */
int palindrome(int x) {
  int palindrome_x;
  int t1=((x&0x55555555)<<1)|(((x&0xaaaaaaaa)>>1)&0x55555555);
  int t2=((t1&0x33333333)<<2)|(((t1&0xcccccccc)>>2)&0x33333333);
  int t4=((t2&0x0f0f0f0f)<<4)|(((t2&0xf0f0f0f0)>>4)&0x0f0f0f0f);
  int t8=((t4&0x00ff00ff)<<8)|(((t4&0xff00ff00)>>8)&0x00ff00ff);
  int t16=((t8&0x0000ffff)<<16)|(((t8&0xffff0000)>>16)&0x0000ffff);
  palindrome_x=t16;
  return !(palindrome_x^x);
}
/*
 * distance - calculate how many bits are different between x and y
 *   Example: distance(0xabcdabcd, 0xabcddcba) = 12,
 *            distance(0x0000ffff, 0xffff0000) = 32,
 *   Legal ops: ~ ! | ^ & << >> +
 *   Max ops: 40
 *   Rating: 4
 */
int distance(int x, int y) {
  int differ = x ^ y, ff = 0xff;
  int _55 = 0x55;//0b01010101
  int _5555 = _55 | (_55 << 8);//0x5555
  int _55555555 = _5555 | (_5555 << 16);//0x55555555
  int sum_2 = ((differ>>1)&_55555555) + (differ&_55555555);
  int _33 = 0x33;//0b00110011
  int _3333 = _33 | (_33 << 8);//0xcccc
  int _33333333 = _3333 | (_3333 << 16);//0xcccccccc
  int sum_4 = ((sum_2 >> 2)&_33333333) + (sum_2&_33333333);
  int _0f = 0x0f;//0b00001111
  int _0f0f = _0f | (_0f << 8);//0x0f0f
  int _0f0f0f0f = _0f0f | (_0f0f << 16); //0x0f0f0f0f
  int sum_8 = ((sum_4 >> 4)&_0f0f0f0f) + (sum_4&_0f0f0f0f);
  int _00ff00ff = ff | (ff << 16);
  int sum_16 = ((sum_8 >> 8)&_00ff00ff) + (sum_8&_00ff00ff);
  int _0000ffff = ff | (ff << 8);
  int sum_all = ((sum_16 >> 16)&_0000ffff) + (sum_16&_0000ffff);
  return sum_all;
}
/*
 * divSix - calculate x / 6 without using /
 *   Example: divSix(6) = 1,
 *            divSix(2147483647) = 357913941,
 *   Legal ops: ~ ! | ^ & << >> +
 *   Max ops: 40
 *   Rating: 4
 */
int divSix(int x) {
    return 2;
}
/*
 * modThree - calculate x mod 3 without using %.
 *   Example: modThree(12) = 0,
 *            modThree(2147483647) = 1,
 *            modThree(-8) = -2,
 *   Legal ops: ~ ! | ^ & << >> +
 *   Max ops: 60
 *   Rating: 4
 */
int modThree(int x) {
  int sum_2 = x, ff = 0xff;
  int _33 = 0x33;//0b00110011
  int _3333 = _33 | (_33 << 8);//0xcccc
  int _33333333 = _3333 | (_3333 << 16);//0xcccccccc
  int sum_4 = ((sum_2 >> 2)&_33333333) + (sum_2&_33333333);
  int _0f = 0x0f;//0b00001111
  int _0f0f = _0f | (_0f << 8);//0x0f0f
  int _0f0f0f0f = _0f0f | (_0f0f << 16); //0x0f0f0f0f
  int sum_8 = ((sum_4 >> 4)&_0f0f0f0f) + (sum_4&_0f0f0f0f);
  int _00ff00ff = ff | (ff << 16);
  int sum_16 = ((sum_8 >> 8)&_00ff00ff) + (sum_8&_00ff00ff);
  int _0000ffff = ff | (ff << 8);
  int sum_all = ((sum_16 >> 16)&_0000ffff) + (sum_16&_0000ffff);//最多不会超过3*16=0b110000
  int sum_all_1 = (sum_all >> 4) + ((sum_all >> 2) & 3) + (sum_all & 3);//在后四个bit
  int sum_all_2 = (sum_all_1 >> 2) + (sum_all_1 & 3);
  int sum_all_3 = (sum_all_2 >> 2) + (sum_all_2 & 3);
  int flag = x >> 31;
  sum_all_3 = sum_all_3 + flag;
  int is_3 = !(sum_all_3 ^ 3);
  int low_0 = flag & 1;
  int mark = is_3 | (low_0&(!!sum_all_3));
  return sum_all_3 - (3 & ((mark << 1) | mark));
}
/* 
 * float_f2i - Return bit-level equivalent of expression (int) f
 *   for floating point argument f.
 *   Argument is passed as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point value.
 *   Anything out of range (including NaN and infinity) should return
 *   0x80000000u.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 3
 */
int float_f2i(unsigned uf) {
  return 2;
}
/* 
 * float_half - Return bit-level equivalent of expression 0.5*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 3
 */
unsigned float_half(unsigned uf) {
  return 2;
}
/* 
 * float_construct - Return bit-level equivalent of expression float(x*2^y),
 *   you should treat the input as integers: if x = 2, y = 3, you should return a float value of 16  
 *   we ensure the constructed number can be represented in float: X[-65535, 65535], y[-160, 60]
 *   Result is returned as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point value.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 90
 *   Rating: 4
 */
unsigned float_construct(int x, int y) {
  return 2;
}
