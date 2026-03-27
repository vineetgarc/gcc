/* Return value of first call is arg to second call.  */

/* { dg-do compile } */
/* { dg-options "-O2 -mcpu=v4" } */

int ret_int ();
void arg_int (int);

void foo () {
   arg_int(ret_int ());
}

/* { dg-final { scan-assembler-not {r1 = r0} } } */
/* { dg-final { scan-assembler-times {w1 = w0} 1 } } */
