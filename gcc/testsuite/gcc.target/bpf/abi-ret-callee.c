/* Verify ABI: narrow return values not promoted in callee.  */

/* { dg-do compile } */
/* { dg-options "-O2 -mcpu=v4" } */

typedef struct {
    int i;
    short b;
    char c;
} my_t;

int ret_int(my_t *s)
{
    return s->i;
}

char ret_char(my_t *s)
{
    return s->c;
}

int ret_char_as_int(my_t *s)
{
    return s->c;
}

char ret_int_as_char(my_t *s)
{
    return (char)s->i;
}

/* { dg-final { scan-assembler-times {\(s8\)} 3 } } */
