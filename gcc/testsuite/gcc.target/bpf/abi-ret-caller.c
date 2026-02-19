/* Verify ABI: narrow return values are promoted in caller.  */

/* { dg-do compile } */
/* { dg-options "-O2 -mcpu=v4" } */

_Bool bar_bool(void);
signed char bar_char(void);
unsigned char bar_char_u(void);
short bar_short(void);
int bar_int(void);

int foo_bool_ne1(void) {
      if (bar_bool() != 1) return 0; else return 1;
}
int foo_bool_ne0(void) {
      if (bar_bool() != 0) return 0; else return 1;
}
int foo_bool2(void) {
      if (bar_bool() != 1) return 7; else return 9;
}
int foo_char(void) {
      if (bar_char() != 1) return 0; else return 1;
}
int foo_char2(void) {
      if (bar_char() != 20) return 0; else return 1;
}
int foo_char_u(void) {
      if (bar_char_u() != 1) return 0; else return 1;
}
int foo_char_u2(void) {
      if (bar_char_u() != 20) return 0; else return 1;
}
int foo_short(void) {
      if (bar_short() != 1) return 0; else return 1;
}
int foo_short2(void) {
      if (bar_short() != 30) return 0; else return 1;
}
int foo_int(void) {
      if (bar_int() != 1) return 0; else return 1;
}
int foo_int2(void) {
      if (bar_int() != 10) return 0; else return 1;
}
/* Bool and char tests will clamp the return value to 0xff .  */
/* { dg-final { scan-assembler-times {r. &= 0xff\n} 7 } } */
/* { dg-final { scan-assembler-times {r. &= 0xffff\n} 2 } } */
