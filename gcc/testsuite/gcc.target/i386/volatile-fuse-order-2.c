/* { dg-do compile { target lp64 } } */
/* { dg-options "-O2 -fomit-frame-pointer -masm=att" } */
/* { dg-final { check-function-bodies "**" "" "" { target { ! *-*-darwin* } } {^\t?\.} } } */

/* Both reads of *P are in separate full expressions: the first read must
   be the one loaded into a register before the compare, which performs
   the second read.  */

/*
**f:
**.LFB0:
**	.cfi_startproc
**	movl	\(%rdi\), %eax
**	cmpl	\(%rdi\), %eax
**	setl	%al
**...
*/

int
f (volatile int *p)
{
  int a = *p;
  int b = *p;
  return a < b;
}
