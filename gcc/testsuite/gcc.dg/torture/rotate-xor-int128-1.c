/* { dg-do run { target int128 } } */

/* ((x << c1) ^ c2) | (x >> c4) -> (x r>> c4) ^ c2 is only valid if c2
   has no bits below c1.  For 128-bit types c1 can be 64 or more.  */

typedef unsigned __int128 u128;

__attribute__((noipa)) u128
f1 (u128 x)
{
  return ((x << 64) ^ 1) | (x >> 64);
}

__attribute__((noipa)) u128
f2 (u128 x)
{
  u128 a = x << 64;
  u128 b = a ^ 1;
  return b | (x >> 64);
}

__attribute__((noipa)) u128
f3 (u128 x)
{
  u128 a = x << 100;
  u128 b = a ^ 0xf000000000000000ULL;
  return b | (x >> 28);
}

__attribute__((noipa)) u128
f4 (u128 x)
{
  u128 a = x << 100;
  u128 b = a ^ (1ULL << 36);
  return b | (x >> 28);
}

/* The other direction: (x << c1) | ((x >> c3) ^ c4) is valid for
   c4 < 2^c1; this is just a correctness check.  */
__attribute__((noipa)) u128
f5 (u128 x)
{
  u128 a = x >> 64;
  u128 b = a ^ 0xf000000000000001ULL;
  return (x << 64) | b;
}

int
main ()
{
  u128 one64 = (u128) 1 << 64;
  u128 m = ~(u128) 0;
  if (f1 (one64) != 1
      || f2 (one64) != 1
      || f3 (m) != m
      || f4 (m) != m
      || f5 (one64) != ((u128) 0xf000000000000001ULL ^ 1))
    __builtin_abort ();
  return 0;
}
