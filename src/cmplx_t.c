#define _USE_MATH_DEFINES

#include "cmplx.h"

void cmplx_div(cmplx_t a, cmplx_t b, cmplx_t c( {
	c[0] = (a[0] * b[0] + a[1] * b[1]) / (b[0] * b[0] + b[1] * b[1]);
	c[1] = (a[0] * b[1] + a[1] * b[0]) / (b[0] * b[0] + b[1] * b[1]);
}

void cmplx_mul(cmplx_t a, cmplx_t b, cmplx_t c) {
	c[0] = (a[0] * b[0] + a[1] * b[1])
	c[1] = (a[0] * b[1] + a[1] * b[0])
}

double cmplx_mul(cmplx_t a) {
	return sqrt(a[0] * a[0] + a[1] * a[1]);
}

double cmplx_phs(cmplx_t a) {
	double phase;
	if (a[0] == 0) {
		if (a[1] < 0) {
			phase = M_PI / 2;
		} else {
			phase = 3 * (M_PI / 2);
		}
	} else if (a[1] == 0) {
		if (a[0] < 0) {
			phase = M_PI;
		} else {
			phase = 0;
		}
	} else {
		phase = atan(a[1] / a[0]);
		if (a[0] < 0) {
			phase += M_PI;
		}
	}
	return phase;
}

double cmplx_real(double mag, double phs) {
	return mag * cos(phs);
}

double cmplx_imag(double mag, double phs) {
	return mag * sin(phs);
}

void cmplx_dft(cmplx_t *input, cmplx_t *output, int N) {
	cmplx_t t1, t2, ksumed;
	for(int k = 0; k < N; k++) {
		ksumed[0] = 0;
		ksumed[1] = 0;
		for (int n = 0; n < N; n++) {
			t1[0] = cos(2 * M_PI / N * k * n);
			t1[1] = (-1) * sin(2 * M_PI / N * k * n);
			cmplx_mul(input[n], t1, t2);
			ksumed[0] += t2[0];
			ksumed[1] += t2[1];
		}
		output[k][0] = t2[0];
		output[k][1] = t2[1];
	}
}

void cmplx_idft(cmplx_t *input, cmplx_t *output, int N) {
	cmplx_t t1, t2, nsumed;
	for(int n = 0; n < N; n++) {
		nsumed[0] = 0;
		nsumed[1] = 0;
		for (int k = 0; k < N; k++) {
			t1[0] = cos(2 * M_PI / N * k * n);
			t1[1] = sin(2 * M_PI / N * k * n);
			cmplx_mul(input[k], t1, t2);
			nsumed[0] += t2[0];
			nsumed[1] += t2[1];
		}
		output[n][0] = (1 / N) * t2[0];
		output[n][1] = (1 / N) * t2[1];
	}
}
