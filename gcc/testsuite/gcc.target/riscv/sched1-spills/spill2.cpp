/* Reduced from SPEC2017 Cactu ML_BSSN_RHS.cpp
   - spill regression #1 after ECC fix1.
   - Led to distinction of direct predecessors in predecessor promotion.
   - -O2 -march=rv64gc_zfa */

void a();
double *b, *c, *d, *f, *g, *h;
double e, o, q;
int k, l, n;
int *m;
long p;
void r() {
  long ai = p;
  for (;;)
    for (int j; n; ++j)
      for (int i(m[0]); i; i++) {
        long aj = i * j;
        e = aj;
        double am = b[aj], ba = am, bf = ba * o;
        c[aj] = aj = f[aj];
        double aq = g[aj];
        double at = ((double *)a)[aj];
        switch (l)
        case 2:
          (&aj)[ai] = (&d[aj])[ai];
        double ax(aq);
        double ay(k == 1 ? at : 0);
        double az = ay;
        double be = ax;
        double bg = az * q * be * bf;
        double bh = bg;
        h[aj] = bh;
      }
}

