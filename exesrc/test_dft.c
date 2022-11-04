#define _USE_MATH_DEFINES

#include <fcntl.h>

#include "cmplx.h"
#include "io.h"

#define SAMPLE 200
#define TIME 5

float vrijednost0, vrijednost1;
int vrijednost_ieee, vrijednost_cijeli_broj;
void *a;

int main (void) {
	int sample_size = SAMPLE * TIME;
	cmplx_t signal[sample_size];
	for (int i = 0; i < sample_size; i++) {
		double t = i / SAMPLE;
		signal[i][0] = sin(2 * M_PI * 50 * t);
		signal[i][1] = 0;
	}
	
	cmplx_t t_signal[sample_size];
	cmplx_dft(signal, t_signal, sample_size);
	
	int fd = open("bin_dft.bin", O_WRONLY | O_CREAT, 00700);
	for (int i = 0; i < sizeof(t_signal); i++) {
		vrijednost0 = t_signal[i][0];
		a = (void *) &vrijednost0;
		vrijednost_ieee = *((int *) a);
		vrijednost_cijeli_broj = (int) vrijednost0;
		write_word(fd, vrijednost_ieee);
		
		vrijednost1 = t_signal[i][1];
		a = (void *) &vrijednost1;
		vrijednost_ieee = *((int *) a);
		vrijednost_cijeli_broj = (int) vrijednost1;
		write_word(fd, vrijednost_ieee);
	}
	
	close(fd);
	return 0;
}
