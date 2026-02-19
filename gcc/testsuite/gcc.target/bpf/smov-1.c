/* Check signed mov instructions.  */
/* { dg-do compile } */
/* { dg-options "-mcpu=v4 -O2 -masm=normal" } */

long
foo (char a, short b, int c, unsigned long d)
{
  long x = a;
  long y = b;
  long z = c;
  long w = (long) d;

  return x + y + z + w;
}

/* { dg-final { scan-assembler-times {movs\t%r.,%r.,32\n} 3 } } */
