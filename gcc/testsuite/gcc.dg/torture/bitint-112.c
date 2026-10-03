/* { dg-do run { target bitint128 } } */

/* ((x << c1) ^ c2) | (x >> c4) -> (x r>> c4) ^ c2 is only valid if c2
   has no bits below c1.  */

typedef unsigned _BitInt(128) U;

[[gnu::noipa]] U
foo (U x)
{
  U a = x << 64;
  U b = a ^ 1;
  return b | (x >> 64);
}

[[gnu::noipa]] U
bar (U x)
{
  return ((x << 100) ^ 0xf000000000000000uwb) | (x >> 28);
}

int
main ()
{
  if (foo ((U) 1 << 64) != 1 || bar (~(U) 0) != ~(U) 0)
    __builtin_abort ();
}
