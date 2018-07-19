#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "../include/externs.h"
#include "../include/utilities.h"
#include "../include/cephes.h"  


//二元推导检测
void BinaryDerivative(int k, int n)
{
	int i = 0;
	int j = 0;
	double sum = 0.0;
	double dPValue = 0.0;
	double dSqrt2 = 1.41421356237309504880;
	unsigned char* newSequence = NULL;
	
	//create new Sequence
  newSequence = (unsigned char*)calloc(n, sizeof(unsigned char));
	if(newSequence == NULL)
	{
	  printf("BinaryDerivative Test: Insufficient memory for calloc!");
		return;
	}
	
	//copy binary stream
	for(i = 0;i < n; ++i)
	{
		newSequence[i] = epsilon[i];
	}
	
	//异或k次得到新序列
	for(i = 0;i < k; ++i)
	{
		for(j = 0;j < (n - k - 1); ++j)
		{
			newSequence[j] = newSequence[j] ^ newSequence[j + 1];
		}
	}
	
	for(i = 0;i < n - k; ++i)
	{
		sum += newSequence[i] ? (1) : (-1);
	}
	
	//free tmp pbsStream
	if(newSequence != NULL)
	{
		free(newSequence);
		newSequence = NULL;
	}
	
	
	sum = fabs(sum);
	
	sum = sum / sqrt(n - k);
	
	dPValue = erfc(fabs(sum) / dSqrt2);
	
  fprintf(stats[TEST_BINARYDERIVATIVE], "\t\t\tBINARY DERIVATIVE TEST\n");
  fprintf(stats[TEST_BINARYDERIVATIVE], "\t\t---------------------------------------------\n");
  fprintf(stats[TEST_BINARYDERIVATIVE], "\t\tCOMPUTATIONAL INFORMATION:\n");
  fprintf(stats[TEST_BINARYDERIVATIVE], "\t\t---------------------------------------------\n");
  fprintf(stats[TEST_BINARYDERIVATIVE], "\t\t(a) k               = %d\n", k);
  fprintf(stats[TEST_BINARYDERIVATIVE], "\t\t(a) sum             = %f\n", sum);
  fprintf(stats[TEST_BINARYDERIVATIVE], "\t\t---------------------------------------------\n");

  fprintf(stats[TEST_BINARYDERIVATIVE], "%s\t\tp_value = %f\n\n", dPValue < ALPHA ? "FAILURE": "SUCCESS", dPValue); 
  fflush(stats[TEST_BINARYDERIVATIVE]);
  fprintf(results[TEST_BINARYDERIVATIVE], "%f\n", dPValue); 
  fflush(results[TEST_BINARYDERIVATIVE]);
}
