// my_functions.c

#include <advanlys.h>
#include "my_functions.h"
#include <userint.h>

// Function definitions



static double *filtru_mediere(void)
{
	double *filtruM = 0;
	double ret = 0.0; //variabila intermediara
	
	filtruM = (double*) calloc(npoints, sizeof(double));
	
	for (int i = 0; i < valmed - 1; ++i)
	{
		ret = ret + waveData[i];	
	}
	
	for (int i = 0; i < valmed - 1; ++i)
	{
		filtruM[i] = ret / valmed;	
	}
	
	for (int i = valmed; i < npoints; ++i)
	{
		ret = ret - waveData[i - valmed] + waveData[i];	
		filtruM[i] = ret / valmed;
	}
	
	return filtruM;
}

static double *filtruOrdin_I(void)
{
	double *filtruI = 0;
	
	filtruI = (double*) calloc(npoints, sizeof(double));
	
	filtruI[0] = waveData[0];
	
	for (int i = 1; i < npoints - 1; ++i)
	{
		filtruI[i] = (1 - alpha) * filtruI[i - 1] + alpha * waveData[i]; //formula curs
	}
	
	return filtruI;
}
*/