/* { dg-do run { target bitint } } */

/* (signed char) a < 0 ? (_BitInt(9)) a : 255 must not become
   MAX (a, 255): the signed maximum is that of unsigned char, 127.  */

[[gnu::noipa]] _BitInt(9)
foo (unsigned char a)
{
  signed char s = a;
  _BitInt(9) r = a;
  if (s < 0)
    return r;
  return 255;
}

[[gnu::noipa]] _BitInt(9)
bar (unsigned char a)
{
  signed char s = a;
  _BitInt(9) r = a;
  if (s >= 0)
    return r;
  return 255;
}

int
main ()
{
  if (foo (200) != 200 || foo (5) != 255
      || bar (200) != 255 || bar (5) != 5)
    __builtin_abort ();
}
