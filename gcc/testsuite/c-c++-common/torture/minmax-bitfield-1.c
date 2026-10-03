/* { dg-do run { target int32plus } } */

/* ((signed) a < 0) ? a : C and ((signed) a >= 0) ? a : C, stored into a
   bit-field exactly one bit wider than a, must not become MAX/MIN (a, C)
   with the signed maximum computed in the wider precision.  */

struct S9 { unsigned x : 9; };
struct T9 { signed x : 9; };
struct S17 { unsigned x : 17; };
struct S33 { unsigned long long x : 33; };
#ifdef __SIZEOF_INT128__
struct S65 { unsigned __int128 x : 65; };
#endif

__attribute__((noipa)) void
f0 (struct S9 *s, unsigned char a)
{
  s->x = a <= 127 ? 255 : a;
}

__attribute__((noipa)) void
f1 (struct S9 *s, unsigned char a)
{
  s->x = ((signed char) a < 0) ? a : 255;
}

__attribute__((noipa)) void
f2 (struct S9 *s, unsigned char a)
{
  s->x = ((signed char) a >= 0) ? a : 255;
}

__attribute__((noipa)) void
f3 (struct T9 *s, unsigned char a)
{
  s->x = ((signed char) a < 0) ? a : 255;
}

__attribute__((noipa)) void
f4 (struct S17 *s, unsigned short a)
{
  s->x = ((short) a < 0) ? a : 0xffff;
}

__attribute__((noipa)) void
f5 (struct S33 *s, unsigned a)
{
  s->x = ((int) a < 0) ? a : 0xffffffffU;
}

#ifdef __SIZEOF_INT128__
__attribute__((noipa)) void
f6 (struct S65 *s, unsigned long long a)
{
  s->x = ((long long) a < 0) ? a : 0xffffffffffffffffULL;
}
#endif

int
main ()
{
  struct S9 s9 = {};
  struct T9 t9 = {};
  struct S17 s17 = {};
  struct S33 s33 = {};
  f0 (&s9, 200);
  if (s9.x != 200)
    __builtin_abort ();
  f0 (&s9, 5);
  if (s9.x != 255)
    __builtin_abort ();
  f1 (&s9, 200);
  if (s9.x != 200)
    __builtin_abort ();
  f1 (&s9, 5);
  if (s9.x != 255)
    __builtin_abort ();
  f2 (&s9, 200);
  if (s9.x != 255)
    __builtin_abort ();
  f2 (&s9, 5);
  if (s9.x != 5)
    __builtin_abort ();
  f3 (&t9, 200);
  if (t9.x != 200)
    __builtin_abort ();
  f3 (&t9, 5);
  if (t9.x != 255)
    __builtin_abort ();
  f4 (&s17, 0x8000);
  if (s17.x != 0x8000)
    __builtin_abort ();
  f5 (&s33, 0x80000000U);
  if (s33.x != 0x80000000U)
    __builtin_abort ();
#ifdef __SIZEOF_INT128__
  struct S65 s65 = {};
  f6 (&s65, 0x8000000000000000ULL);
  if (s65.x != 0x8000000000000000ULL)
    __builtin_abort ();
#endif
  return 0;
}
