/* Verify ABI: narrow args are not promoted in callee.  */
/* { dg-do compile } */
/* { dg-options "-O2 -mcpu=v4" } */

int args_consume (signed char a, short b, int c)
{
  int x = a;
  int y = b;
  int z = c;

  return x + y + z;
}

/* { dg-final { scan-assembler-not {w. = \(s8\) w.\n} } } */
/* { dg-final { scan-assembler-not {w. = \(s16\) w.\n} } } */
