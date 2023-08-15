#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>

void LeibnizSerial(long int iterationNumber) {

	double total = 0;
	long int i;

	const clock_t START = clock();

	for (i = 0; i < iterationNumber; i++) {
		total += pow(-1, i) / (2.0 * i + 1.0);
	}

	const double T_ELAPSED = ((double)clock() - (double)START) / CLOCKS_PER_SEC;

	printf("\nThe value of Pi is: %.50lf\n", total * 4);

	printf("\nCalculated at %lf seconds.\n", T_ELAPSED);
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Usage: %s <iterations>\n", argv[0]);
        return 1;
    }

	long int iterationNumber = atoi(argv[1]);

	LeibnizSerial(iterationNumber);

	return 0;
}
