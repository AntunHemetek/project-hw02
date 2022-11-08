#include <stdio.h>
#include <math.h>
#include "cmplx.h"

int main(void) {
	cmplx_t s1[10];
	cmplx_t s2[10];
	cmplx_t s3[10];
	for(int i = 0; i < 10; i++) {
		s1[i][0] = i + 2;
	}
	
	cmplx_dft(s1, s2, 10);
	
	for(int i = 0; i < 10; i++) {
		printf("%.2f + %.2fj = %.2f + %.2fj\n", s1[i][0], s1[i][1], s2[i][0], s2[i][1]);
	}
	printf("\n");
	
	cmplx_idft(s2, s3, 10);
	
	for(int i = 0; i < 10; i++) {
		printf("%.2f + %.2fj = %.2f + %.2fj\n", s2[i][0], s2[i][1], s3[i][0], s3[i][1]);
	}
	return 0;
}
