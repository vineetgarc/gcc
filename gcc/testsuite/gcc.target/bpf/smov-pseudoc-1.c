/* Check signed mov instructions (pseudo-C asm dialect).  */
/* { dg-do compile } */
/* { dg-options "-mcpu=v4 -O2 -masm=pseudoc" } */

long
foo (char a, short b, int c, unsigned long d)
{
  long x = a;
  long y = b;
  long z = c;
  long w = (long) d;

  return x + y + z + w;
}

/* { dg-final { scan-assembler-times {r. = \(s32\) w.\n} 3 } } */
