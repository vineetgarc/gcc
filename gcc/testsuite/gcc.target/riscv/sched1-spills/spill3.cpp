/* Reduced from SPEC2017 Cactu ML_BSSN_RHS.cpp
   - spills regression #2 after ECC fix1.
   - predecessor promotion of 2 recursion levels causing seperation of deps,
     increasing the live range.
   - -O2 -std=c++03 -march=rv64gc_zba  */

void r();
int b, h, l;
double *c, *d, *e, *f;
long g;
int *m;
void s() {
  double *o((double *)r);
  for (int k; k < 2; ++k)
    for (int j; j < l; ++j)
      for (int i(h); i < m[0]; i++) {
        long a = i + g * j * k;
        double n(d[a] * e[a] - f[a]);
        double p = c[b * a] * n;
        double q = b * p;
        o[a] = q;
      }
}
