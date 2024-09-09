/* Reduced from libgcc/_divtc3.c
   - Interim version of changes would cause a hang in for (;;) in
     predecessor promotion
   - -O2 -march=rv64gc_zba_zbb_zbs_zfa -mabi=lp64d -fPIC */

float a, b;
void c() {
  if (__builtin_fabsl(a) < __builtin_fabsl(b))
    a = 2;
}
