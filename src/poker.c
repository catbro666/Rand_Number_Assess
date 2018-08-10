#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "../include/externs.h"
#include "../include/cephes.h"


//ÆË¿Ë¼ì²â
void Poker(int m, int n)
{
	int i = 0;
	int j = 0;
	int nBlocksNumber = 0;
	int nNArraySize = 0;
	long* Array = NULL;
	long decRep;
	double sum = 0.0;
	double dPValue = 0.0;
	
	nBlocksNumber = n / m; 
	nNArraySize = (int)pow(2, m);

	Array = (long*)calloc(nNArraySize, sizeof(long) );
	if(Array == NULL)
	{
		printf("Poker Test: Insufficient memory for calloc!\n");
		return ;
	}

	for(i = 0;i < nNArraySize; ++i)
	{
		Array[i] = 0;
	}
	
	for(i = 0;i < nBlocksNumber; ++i)
	{
		decRep = 0;
		for(j = 0; j < m; j++)
		{
			decRep += epsilon[i*m+j] * (long)pow(2, m-1-j);
		}
		++(Array[decRep]);
	}
	
	for(i = 0;i < nNArraySize; ++i)
	{
		sum += pow(Array[i], 2);
	}

	sum = nNArraySize / (double)nBlocksNumber* sum;
	sum = sum - (double)nBlocksNumber;
	
	dPValue = cephes_igamc(((nNArraySize - 1)/2), sum / 2);
	
	//free
	if(Array != NULL) free(Array);

  fprintf(stats[TEST_POKER], "\t\t\t       POKER TEST\n");
  fprintf(stats[TEST_POKER], "\t\t---------------------------------------------\n");
  fprintf(stats[TEST_POKER], "\t\t COMPUTATIONAL INFORMATION:      \n");
  fprintf(stats[TEST_POKER], "\t\t---------------------------------------------\n");
  fprintf(stats[TEST_POKER], "\t\t(a) m                   = %d\n", m);
  fprintf(stats[TEST_POKER], "\t\t(b) blocksNumber        = %d\n", nBlocksNumber);
  fprintf(stats[TEST_POKER], "\t\t(c) nNArraySize         = %d\n", nNArraySize);
  fprintf(stats[TEST_POKER], "\t\t(d) sum                 = %f\n", sum);
  fprintf(stats[TEST_POKER], "\t\t---------------------------------------------\n");

  fprintf(stats[TEST_POKER], "%s\t\tp_value = %f\n", dPValue < ALPHA ? "FAILURE" : "SUCCESS", dPValue);
  fprintf(results[TEST_POKER], "%f\n", dPValue);
  fflush(stats[TEST_POKER]);
  fflush(results[TEST_POKER]);

}
