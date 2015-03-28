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
*
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

*
 * STEP 2: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce 
 *      the correct answers.
 */


#endif
/* 
 * bitOr - x|y using only ~ and & 
 *   Example: bitOr(6, 5) = 7
 *   Legal ops: ~ &
 *   Max ops: 8
 *   Rating: 1
 */
int bitOr(int x, int y) {
	/* first do "not" operation on x,y and then do "and" operation. At last do "not" operation.*/
	int a, b, c;
	a = ~x;
	b = ~y;
	c = a&b;
	return ~c;
}
/* 
 * tmin - return minimum two's complement integer 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmin(void) {
	/*      just shift one for 31 bits  */
	return (1 << 31);
}
/* 
 * negate - return -x 
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int negate(int x) {
	/*first do "not" operation and then plus one*/
	int a, b;
	a = ~x;
	b = a + 1;
	return b;
}
/* 
 * getByte - Extract byte n from word x
 *   Bytes numbered from 0 (LSB) to 3 (MSB)
 *   Examples: getByte(0x12345678,1) = 0x5
6
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 2
 */
int getByte(int x, int n) {
	/*   just do & operation between x and 0xff (x >> (n << 3)) */	
	int a, b, c;
	a = 0xFF;
	b = n << 3;
	c = x >> b;
    return a&c;
}
/* 
 * divpwr2 - Compute x/(2^n), for 0 <= n <= 30
 *  Round toward zero
 *   Examples: divpwr2(15,1) = 7, divpwr2(-33,4) = -2
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
int divpwr2(int x, int n) {
	/* for negative numbers minus one first and then right shift for
n bits, lastly if negative then plus one */
	int y, z;
	y = x >> n;
	z = y << n;
	y += ((((x) & (~x + 1 + z)) >> 31) & 1);
	return y;
}
/* 
 * logicalShift - shift x to the right by n, using a logical shift
 *   Can assume that 0 <= n <= 31
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3 
 */

int logicalShift(int x, int n) {
	/* first shift and then do & operation between the shifted number and 00..011 where there are n zeros */	
	int y, z;
	y = (x >> n);
	z = ~((~1) << (32 + ~n));
	return z & y;

}

/* 
 * isPositive - return 1 if x > 0, return 0 otherwise 
 *   Example: isPositive(-1) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 3
 */
int isPositive(int x) {
	/*first exclude the zero and then exclude the negative number*/	
	int y;
	y = (x >> 31) + 1;	
	return y^(!x);
}
/* 
 * isLess - if x < y  then return 
1, else return 0 
 *   Example: isLess(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLess(int x, int y) {
	/* two situations: 1) when x and y have the same sign, then do subtraction
                           2) when x and y have different sign, output the result   */
	int sign1, sign2, sign, minus_y, sub, sign_sub;
	sign1 = x;
	sign2 = ~y;
	sign = sign1 ^ sign2;
	minus_y = sign2 + 1;
	sub = x + minus_y;
	sign_sub = sub;
	return (((sign_sub & sign)|(sign1 & sign2)) >> 31) & 1;   // ops may be reduced more here?
	// total 9 ops
}
/* 
 * bang - Compute !x without using !
 *   Examples: bang(3) = 0, bang(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4 
 */
int bang(int x) {
	/* two trials: 1) trial1: check whether x >= 0 
	               2) trial2: check whether x <= 0  */
	int trial1, trial2;
	trial1 = ~x;
	trial2 = x + ~0;
	return ((trial1 & trial2) >> 31) & 1;
	// 6 ops  how to make this into 5 ops?	
		
	//int trial1, trial2;
	//trial1 = ~x;
	//trial2 = trial1 + 1;
	//return ((x ^ trial2) >> 31) & 1;
}
/*
 * isPower2 - returns 1 if x is a power of 2, and 0 otherwise
 *   Examples: isPower2(5) = 0, isPower2(8) = 1, isPower2(0) = 0
 *   Note that no negative number is a power of 2.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 4
 */
int isPower2(int x) {
	/* check whether x & (x-1) is zero and then exclude negative number and zero.*/
	int y;
	y = x + ~0;
	return !((x & y)|((x >> 31) | !x));	
	// total 8 ops
} 
/*
 * ilog2 - return floor(log base 2 of x), where x > 0
 *   Example: ilog2(16) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 90
 *   Rating: 4
 */
int ilog2(int x) {
 	/* every time shift half length of the unknown part and record the rersult in ax then
	add axs together */	
	int a16, a8, a4, a2, a1, b16, b8, b4, b2;
	a16 = !(!(x >> 16));
	b16 = a16 << 4;
	a8 = !(!(x >> (8 + b16)));
	b8 = (a8 << 3) + b16;
	a4 = !(!(x >> (4 + b8)));
	b4 = (a4 << 2) + b8; 
	a2 = !(!(x >> (2 + b4)));
	b2 = (a2 << 1) + b4;
	a1 = (x >> (1 + b2));
	return a1 + b2;
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
 *   Rating: 4
 */
unsigned float_half(unsigned uf) {
	/* 3 cases: 1) when expo of uf is 11111111 or uf is 0, return uf;
	    	    2) when first 7 dit of expo is 0000000, right shift, then round, finally change the sign.
	            3) otherwise, expo minus one.    */	
	unsigned expo, expo_7, expo_2, uf_new;
	expo = uf & 0x7F800000;
    	expo_7 = uf & 0x7F000000;   
	expo_2 = uf & 3;
	if (expo == 0x7F800000){ 
		return uf;
	}
	else if (expo_7){      
		uf_new = uf + 0xFF800000;  
	}	
	else{
		uf_new = uf >> 1;
		if (expo_2 == 3){
			uf_new += 1;
		}
		if (uf & 0x80000000){   
			uf_new += (0x40000000);   	
		}
	} 
	return uf_new;
}

/* 
* float_i2f - Return bit-level equivalent of expression (float) x
 *   Result is returned as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point values.
 *   Legal ops: Any integer/unsigned operations incl. |, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned float_i2f(int x) {
/*      1) when x = 0, return 0;
	2) then make x positive;
	3) next find log2(2);
	4) add exponent;
	5) add fraction;
	6) round;
	7) return x_new;  			*/ 
	unsigned i, a, y, x_new, b, c, d, x_plus;		
	d = 1;
	if (x){                     
		d = 0;
	}	
	if (d){
		return x;
	}
	c = 0x80000000;
	x_new = c & x;               
	if (x_new){		   // make x positive
		x = -x;
	}
	a = x;	
	i = 126;			// find log2(x)
	while (a){
		a >>= 1;
		i += 1;	
	};
	
	x_new += (i << 23);
	x <<= (157 - i);	      
	y = x >> 7;
	b = 0x007FFFFF;
	y &= b;
	x_new += y;			// fraction
	x_new += (0x40 & x) && (0x40 ^ (x & 0xff));  			// round
	return x_new;
}
