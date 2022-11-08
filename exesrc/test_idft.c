#define _USE_MATH_DEFINES

#include <fcntl.h>
#include <stdio.h>
#include <math.h>
#include <unistd.h>

#include "cmplx.h"
#include "io.h"

#define SAMPLE 200
#define TIME 5

int vrijednost_ieee;
double vrijednost0, vrijednost1;
void *a;

int main (void) {
	int sample_size = SAMPLE * TIME;
	cmplx_t t_signal[sample_size];
	
	int fd = open("bin_dft.bin", O_RDONLY, 00700);
	for (int i = 0; i < sizeof(t_signal); i++) {
		vrijednost_ieee = read_word(fd);
		a = (void *) &vrijednost_ieee;
		vrijednost0 = *((double *) a);
		t_signal[i][0] = vrijednost0;
		
		vrijednost_ieee = read_word(fd);
		a = (void *) &vrijednost_ieee;
		vrijednost1 = *((double *) a);
		t_signal[i][1] = vrijednost1;
	}
	close(fd);
	
	cmplx_t signal[sample_size];
	cmplx_idft(t_signal, signal, sample_size);
	
	return 0;
}
