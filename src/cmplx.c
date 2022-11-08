#define _USE_MATH_DEFINES

#include <math.h>
#include <stdio.h>

#include "cmplx.h"

void cmplx_div(cmplx_t a, cmplx_t b, cmplx_t c) {
	c[0] = (a[0] * b[0] + a[1] * b[1]) / (b[0] * b[0] + b[1] * b[1]);
	c[1] = (a[0] * b[1] + a[1] * b[0]) / (b[0] * b[0] + b[1] * b[1]);
}

void cmplx_mul(cmplx_t a, cmplx_t b, cmplx_t c) {
	c[0] = (a[0] * b[0] - a[1] * b[1]);
	c[1] = (a[0] * b[1] + a[1] * b[0]);
}

double cmplx_mag(cmplx_t a) {
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
	for(int k = 0; k < N; k++) {
		cmplx_t t1, t2, ksumed;
		ksumed[0] = 0.f;
		ksumed[1] = 0.f;
		for (int n = 0; n < (N - 1); n++) {
			t1[0] = cos(2 * M_PI / N * k * n);
			t1[1] = -sin(2 * M_PI / N * k * n);
			cmplx_mul(input[n], t1, t2);
			
			//debug:
			//printf("t1: %.2f + %.2fj\n", t1[0], t1[1]);
			//printf("t2: %.2f + %.2fj\n", t2[0], t2[1]);
			
			ksumed[0] += t2[0];
			ksumed[1] += t2[1];
		}
		output[k][0] = ksumed[0];
		output[k][1] = ksumed[1];
	}
}

void cmplx_idft(cmplx_t *input, cmplx_t *output, int N) {
	for(int n = 0; n < N; n++) {
		cmplx_t t1, t2, nsumed;
		nsumed[0] = 0.f;
		nsumed[1] = 0.f;
		for (int k = 0; k < (N - 1); k++) {
			t1[0] = cos(2 * M_PI / N * k * n);
			t1[1] = sin(2 * M_PI / N * k * n);
			cmplx_mul(input[k], t1, t2);
			
			//debug:
			//printf("t1: %.2f + %.2fj\n", t1[0], t1[1]);
			//printf("t2: %.2f + %.2fj\n", t2[0], t2[1]);
			
			nsumed[0] += t2[0];
			nsumed[1] += t2[1];
		}
		output[n][0] = nsumed[0] / N;
		output[n][1] = nsumed[1] / N;
	}
}
