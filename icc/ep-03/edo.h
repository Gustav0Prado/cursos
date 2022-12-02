typedef struct{
   double *d, *a, *c, *b;
   int n;
} SL_Tridiag;

typedef struct{
   double a, b, ya, yb;
   double (*p)(double), (*q)(double), (*r)(double);
   int n;
} Edo;

void seidelDiag();

void seidelFunc();