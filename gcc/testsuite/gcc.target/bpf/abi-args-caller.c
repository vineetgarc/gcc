/* Verify ABI: narrow args are promoted in caller.  */
/* { dg-do compile } */
/* { dg-options "-O2 -mcpu=v4" } */

typedef struct {
    int a;
    short b;
    signed char c;
} my_t;

void foo(signed char, short, int);
char args_setup(my_t *s)
{
    foo(s->c, s->b, s->a);
}

/* { dg-final { scan-assembler-times {w. = \(s8\) w.\n} 1 } } */
/* { dg-final { scan-assembler-times {w. = \(s16\) w.\n} 1 } } */
