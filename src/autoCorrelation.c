#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "../include/externs.h"
#include "../include/cephes.h"

//×ÔÏà¹Ø¼ì²â
void AutoCorrelation(int d, int n)
{
	int i = 0;
	double sum = 0.0;
	double dPValue = 0.0;
	double dSqrt2 = 1.41421356237309504880;
	
	
	
	for(i = 0;i < n - d; ++i)
	{
		sum += epsilon[i] ^ epsilon[i + d];
	}

	sum -= (n - d) / 2;
	sum *= 2;
	sum /= sqrt(n - d);
	dPValue = cephes_erfc(fabs(sum) / dSqrt2);


  fprintf(stats[TEST_AUTOCORRELATION], "\t\t\tAUTOCORRELATION TEST\n");
  fprintf(stats[TEST_AUTOCORRELATION], "\t\t---------------------------------------------\n");
  fprintf(stats[TEST_AUTOCORRELATION], "\t\tCOMPUTATIONAL INFORMATION:\n");
  fprintf(stats[TEST_AUTOCORRELATION], "\t\t---------------------------------------------\n");
  fprintf(stats[TEST_AUTOCORRELATION], "\t\t(a) d               = %d\n", d);
  fprintf(stats[TEST_AUTOCORRELATION], "\t\t(b) sum             = %f\n", sum);
  
  fprintf(stats[TEST_AUTOCORRELATION], "\t\t---------------------------------------------\n");

  fprintf(stats[TEST_AUTOCORRELATION], "%s\t\tp_value = %f\n\n", dPValue < ALPHA ? "FAILURE" : "SUCCESS", dPValue);
  fflush(stats[TEST_AUTOCORRELATION]);
  fprintf(results[TEST_AUTOCORRELATION], "%f\n", dPValue);
  fflush(results[TEST_AUTOCORRELATION]);

}
