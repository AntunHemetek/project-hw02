#include <math.h>

typedef float cmplx_t[2];

void cmplx_div(cmplx_t a, cmplx_t b, cmplx_t c);
void cmplx_mul(cmplx_t a, cmplx_t b, cmplx_t c);
double cmplx_mag(cmplx_t a);
double cmplx_phs(cmplx_t a);
double cmplx_real(double mag, double phs);
double cmplx_imag(double mag, double phs);
void cmplx_dft(cmplx_t *input, cmplx_t *output, int N);
void cmplx_idft(cmplx_t *input, cmplx_t *output, int N);
