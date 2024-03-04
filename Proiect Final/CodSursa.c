#include <ansi_c.h>
#include <formatio.h>
#include <cvirte.h>		
#include <userint.h>
#include "Et1.h"
#include <advanlys.h>
#include <analysis.h>
#include <utility.h>

static int panelHandle; //handle pentru panoul principal (in timp)
//este wavePanel
static int histogramHandle; //handle pentru panoul histogramei
static int derivataHandle; //handle pentru panoul derivatei

//handle pentru graficele cu data nefiltrata si filtrata
static int filteredDataHandle = -1;
static int rawDataHandle = -1;

static char file_name[256] = {0}; // salvare imagine

//Constants
#define SAMPLE_RATE 	0
#define NPOINTS 		1

#define MAX_SECOND_WAVE 6
#define MIN_SECOND_WAVE 0

int start = -1;
int stop = 0;

int waveInfo[2];
double sampleRate = 1.0;
int npoints = 1; 

double *waveData = 0, *filteredData = 0, *envelopleData = 0;
double alpha;

double maxVal=0;
double minVal=0;//valorile de maxim si minim, pentru histograma

double* filteredSignal = 0; //vector cu datele semnalului filtrat in dom. timp
int valmed=16; //valoarea pentru filtru de mediere

double *anvelopa=0; //anvelopa
int npointsAnvelopa; //numar de esantioane pentru anvelopa
int anvelopaInfo[1]; 

double *derivata=0; //derivata

//int wavePanel = 0;
static int freqPanel = 0;

static int N;//numar de puncte de pe interfata


int main (int argc, char *argv[])
{
	if (InitCVIRTE (0, argv, 0) == 0)
		return -1;	/* out of memory */
	if ((panelHandle = LoadPanel (0, "Et1.uir", PANEL)) < 0)
		return -1;
	if ((freqPanel = LoadPanel (0, "Et1.uir", FREQ_PANEL)) < 0)
		return -1;
	DisplayPanel (panelHandle);
	RunUserInterface ();
	DiscardPanel (panelHandle);
	return 0;
}

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

void updateTextControl(int panel, double* waveData,int npoints){
	
	double zero=0;
	int maxIndex=0;
	int minIndex=0;
	double mean=0; //media
	double median=0; //mediana
	double stdDev=0; //dispersia
	//double maxVal=0;
	//double minVal=0;
	//calculare val min si val max
	MaxMin1D(waveData, npoints, &maxVal, &maxIndex, &minVal, &minIndex);
	//calculare medie
	Mean(waveData,npoints,&mean);
	//calculare mediana
	Median(waveData,npoints,&median);
	//calculare dispersie
	StdDev(waveData,npoints,&mean,&stdDev); 
			
	//setare valori pe interfata
	SetCtrlVal(panel,PANEL_MIN_VAL,minVal);
	SetCtrlVal(panel,PANEL_MAX_VAL,maxVal);
	SetCtrlVal(panel,PANEL_MIN_INDEX, minIndex);
	SetCtrlVal(panel,PANEL_MAX_INDEX, maxIndex);  
	SetCtrlVal(panel,PANEL_MEAN_VAL,mean);
	SetCtrlVal(panel,PANEL_MEDIAN_VAL,median);
	SetCtrlVal(panel,PANEL_DISPERSION_VAL,stdDev);
			
			
	//zero crossing
	for(int i=0;i<npoints-1;++i)
		{
			if( ( (waveData[i]<0) && (waveData[i+1]>0) ) || ( (waveData[i]>0) && (waveData[i+1]<0))  )
			{
				zero++;
			}
		}
		
	//valoarea pentru zero crossing
	SetCtrlVal(panel,PANEL_ZERO_COUNT_VAL,zero);
}
int CVICALLBACK mainPanel (int panel, int event, void *callbackData,
						   int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_GOT_FOCUS:

			break;
		case EVENT_LOST_FOCUS:

			break;
		case EVENT_CLOSE:
			QuitUserInterface(0);
			break;
	}
	return 0;
}


int CVICALLBACK loadWaveFunction (int panel, int control, int event,
								  void *callbackData, int eventData1, int eventData2)
{
	
	
	switch (event)
	{
		case EVENT_COMMIT:
			FileToArray("d:\\Marian Tudor\\waveInfo.txt", waveInfo, VAL_INTEGER, 2, 1, VAL_GROUPS_TOGETHER, VAL_GROUPS_AS_COLUMNS,VAL_ASCII);
			sampleRate = waveInfo[SAMPLE_RATE];
			npoints = waveInfo[NPOINTS];
			
			//Durata semnalului trebuie sa fie de 6 secunde
			double durata = 6.0;
			npoints = (int)(sampleRate * durata);
			
			waveData = (double *) calloc(npoints, sizeof(double));
			//trebuie sa verific numarul de puncte si sa fac a.i. sa imi dea 6 secunde

			FileToArray("d:\\Marian Tudor\\waveData.txt", waveData, VAL_DOUBLE, npoints, 1, VAL_GROUPS_TOGETHER, VAL_GROUPS_AS_COLUMNS, VAL_ASCII);
			start = -1;
			stop = 0;
			
			
			if(rawDataHandle)
			{
				DeleteGraphPlot(panel,PANEL_GRAPH,-1, VAL_IMMEDIATE_DRAW);
			}
			
			rawDataHandle = PlotY(panel, PANEL_GRAPH, waveData, npoints, VAL_DOUBLE, VAL_THIN_LINE, VAL_EMPTY_SQUARE, VAL_SOLID, VAL_CONNECTED_POINTS, VAL_RED);
			
			updateTextControl(panel, waveData, npoints);
			
	}
	return 0;
}




int CVICALLBACK onBackwardCB (int panel, int control, int event,
							  void *callbackData, int eventData1, int eventData2)
{
	int dim = (int)sampleRate;
    double temp[dim];

    switch (event)
    {
        case EVENT_COMMIT:

            if (start > 0 && start <= 5)
            {
                start--;
                SetCtrlVal(panel, PANEL_START, start);
                stop--;
                SetCtrlVal(panel, PANEL_STOP, stop);

                for (int i = 0; i < sampleRate; i++)
                {
                    temp[i] = waveData[start * (int)sampleRate + i];
                }
				
                DeleteGraphPlot(panel, PANEL_GRAPH, -1, VAL_IMMEDIATE_DRAW);
                PlotY(panel, PANEL_GRAPH, temp, (int)sampleRate, VAL_DOUBLE, VAL_THIN_LINE, VAL_EMPTY_SQUARE, VAL_SOLID, 1, VAL_RED);
				updateTextControl(panel,temp, (int)sampleRate);
            }
            break;
    }
    return 0;
}

int CVICALLBACK onForwardCB (int panel, int control, int event,
							 void *callbackData, int eventData1, int eventData2)
{
	int dim=(int)sampleRate;
	double temp[dim];
	
	switch (event)
	{
		case EVENT_COMMIT:
			
			if(start >= -1 && start < 5)
			{
				start++;
				SetCtrlVal(panel,PANEL_START,start);
				stop++;
				SetCtrlVal(panel, PANEL_STOP,stop);
				
				for(int i = 0; i < sampleRate; i++)
				{
					temp[i] = waveData[start*(int)sampleRate+i]; 
					
				}
				
				DeleteGraphPlot(panel, PANEL_GRAPH, -1, VAL_IMMEDIATE_DRAW);
				PlotY(panel, PANEL_GRAPH, temp, (int)sampleRate, VAL_DOUBLE, VAL_THIN_LINE, VAL_EMPTY_SQUARE, VAL_SOLID, 1, VAL_RED);
				updateTextControl(panel,temp,(int)sampleRate);
			}
			break;
	}
	return 0;
}


int CVICALLBACK onApply (int panel, int control, int event,
						 void *callbackData, int eventData1, int eventData2)
{
	int filterType;
	filteredSignal = (double *) calloc(npoints, sizeof(double));
	
	switch (event)
	{
		case EVENT_COMMIT:
			if(waveData !=0)
			{
				GetCtrlVal(panel,PANEL_SELECT_FILTER,&filterType);
				if(filterType == 0)
				{
					GetCtrlVal(panel,PANEL_WINDOW_SIZE, &valmed);
					filteredSignal = filtru_mediere();
					
					
					if (filteredDataHandle)
					{
						DeleteGraphPlot(panel, PANEL_FILTERED_GRAPH, filteredDataHandle, VAL_IMMEDIATE_DRAW);
					}
					filteredDataHandle = PlotY(panel, PANEL_FILTERED_GRAPH, filteredSignal, npoints, VAL_DOUBLE, VAL_THIN_LINE, VAL_EMPTY_SQUARE, VAL_SOLID, VAL_CONNECTED_POINTS, VAL_GREEK_CHARSET);
					updateTextControl(panel,filteredSignal,(int)sampleRate);
				}
				else
				{
					GetCtrlVal(panel, PANEL_ALPHA_VAL, &alpha);		
					filteredSignal = filtruOrdin_I();
					
					if (filteredDataHandle)
					{
						DeleteGraphPlot(panel, PANEL_FILTERED_GRAPH, filteredDataHandle, VAL_IMMEDIATE_DRAW);
					}
					filteredDataHandle = PlotY(panel, PANEL_FILTERED_GRAPH, filteredSignal, npoints, VAL_DOUBLE, VAL_THIN_LINE, VAL_EMPTY_SQUARE, VAL_SOLID, VAL_CONNECTED_POINTS, VAL_GREEK_CHARSET);
					updateTextControl(panel,filteredSignal,(int)sampleRate);
				}
			}
			break;
	}
	return 0;
}

int CVICALLBACK onHistogramPanel (int panel, int event, void *callbackData,
								  int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_GOT_FOCUS:

			break;
		case EVENT_LOST_FOCUS:

			break;
		case EVENT_CLOSE:
			RemovePopup(histogramHandle);
			break;
	}
	return 0;
}

int CVICALLBACK onHistogram (int panel, int control, int event,
							 void *callbackData, int eventData1, int eventData2)
{
	int interv=100;
	double axis[100];
	int hist[100];
	
	switch (event)
	{
		case EVENT_COMMIT:
			if(waveData != 0)
			{
				Histogram(waveData, npoints, minVal-1, maxVal+1, hist, axis, interv);
				//popup pt histograma
				histogramHandle=LoadPanel(1, "Et1.uir", PANEL_HIST);
				InstallPopup(histogramHandle);
				//plotare histograma
				DeleteGraphPlot (histogramHandle,PANEL_HIST_HISTOGRAM, -1, VAL_DELAYED_DRAW);
	            PlotXY (histogramHandle,PANEL_HIST_HISTOGRAM, axis,  hist, interv, VAL_DOUBLE, VAL_SSIZE_T, VAL_VERTICAL_BAR, VAL_EMPTY_SQUARE, VAL_SOLID, 1, VAL_DK_BLUE);
			}
			break;
	}
	return 0;
}


int CVICALLBACK onAnvelopare (int panel, int control, int event,
							  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			FileToArray("d:\\Marian Tudor\\anvelopaInfo.txt", anvelopaInfo, VAL_INTEGER, 1, 1, VAL_GROUPS_TOGETHER, VAL_GROUPS_AS_COLUMNS, VAL_ASCII);
			npointsAnvelopa=anvelopaInfo[0]; //numar de valori
			anvelopa = (double *) calloc(npoints, sizeof(double)); 
			
			//plotare 
			FileToArray("d:\\Marian Tudor\\anvelopaData.txt", anvelopa, VAL_DOUBLE, npointsAnvelopa, 1, VAL_GROUPS_TOGETHER, VAL_GROUPS_AS_COLUMNS, VAL_ASCII);
			PlotY(panel,PANEL_GRAPH, anvelopa, npoints, VAL_DOUBLE, VAL_THIN_LINE, VAL_EMPTY_SQUARE, VAL_SOLID, VAL_CONNECTED_POINTS, VAL_BLACK); 
			break;
	}
	return 0;
}

int CVICALLBACK onDerivataPanel (int panel, int event, void *callbackData,
								 int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_GOT_FOCUS:

			break;
		case EVENT_LOST_FOCUS:

			break;
		case EVENT_CLOSE:
			RemovePopup(derivataHandle);
			break;
	}
	return 0;
}


int CVICALLBACK onDerivata (int panel, int control, int event,
							void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			if (npoints == 0)
				return -1;
			
			derivata = (double *) calloc(npoints, sizeof(double));
			DifferenceEx (waveData, npoints, 1.0, waveData + 1, 1, waveData + npoints - 1, 1, DIFF_SECOND_ORDER_CENTRAL, derivata); 
			//popup pentru derivata
			derivataHandle=LoadPanel(1, "Et1.uir", PANEL_DER);
			InstallPopup(derivataHandle);
			//plotare derivata
			DeleteGraphPlot(derivataHandle, PANEL_DER_GRAPH_DERIVATA, -1, VAL_DELAYED_DRAW);
            PlotY(derivataHandle, PANEL_DER_GRAPH_DERIVATA, derivata, npoints, VAL_DOUBLE, VAL_THIN_LINE, VAL_EMPTY_SQUARE, VAL_SOLID, VAL_CONNECTED_POINTS, VAL_BLUE);
			
			break;
	}
	
	return 0;
}

int CVICALLBACK onSave (int panel, int control, int event,
						void *callbackData, int eventData1, int eventData2)
{
	int year = 0;
	int month = 0;
	int day = 0;
	int hour = 0;
	int minute = 0;
	int second = 0;
	
	//pentru a salva imaginea
	int bitmap = 0;
	int label = 0;
	
	
	switch (event)
	{
		case EVENT_COMMIT:
			// pentru Data neprelucrata
	
				label = ConfirmPopup("Salvare.", "Imaginea cu Data Nefiltrata/Raw va fi salvata.");
				if (1 == label)
				{
					//preluam date&time
					GetSystemDate(&month, &day, &year);
					GetSystemTime(&hour, &minute, &second);
					//scrie in file Date&Time pe care le-am furnizat
					sprintf(file_name, "Data_Initiala_%d.%d.%d_%d-%d-%d.jpg", year, month, day, hour, minute, second);
					
					//face un ss la panou
					//salveaza imaginea
					GetCtrlDisplayBitmap(panel, PANEL_GRAPH , label, &bitmap);
					SaveBitmapToJPEGFile(bitmap, file_name, JPEG_PROGRESSIVE, 100);
					DiscardBitmap(bitmap);
					//resetam date&time
					month = 0;
					day = 0;
					year = 0;
					hour = 0;
					minute = 0;
					second = 0;
					
					bitmap = 0;
					label = 0;
				}
				
			
			// pentru Data prelucrata
				label = ConfirmPopup("Salvare.", "Imaginea cu Data Filtrata va fi salvata.");
				if (1 == label)
				{
					int filter_switch= 0;
					
					GetSystemDate(&month, &day, &year);
					GetSystemTime(&hour, &minute, &second);
					
					GetCtrlVal(panel, PANEL_SELECT_FILTER, &filter_switch);
					
					if (1 == filter_switch)		
					{
						// Element de ordin I
						sprintf(file_name, "Element_de_Ordin_I_%.2lf_%d.%d.%d_%d-%d-%d.jpg", alpha, year, month, day, hour, minute, second);
					}
					else								
					{
						// Mediere
						sprintf(file_name, "Mediere_%d_%d.%d.%d_%d-%d-%d.jpg", valmed, year, month, day, hour, minute, second);
					}
					
					GetCtrlDisplayBitmap(panel,PANEL_FILTERED_GRAPH, label, &bitmap);
					SaveBitmapToJPEGFile(bitmap, file_name, JPEG_PROGRESSIVE, 100);
					DiscardBitmap(bitmap);
					
					month = 0;
					day = 0;
					year = 0;
					hour = 0;
					minute = 0;
					second = 0;
					
					bitmap = 0;
					label = 0;
					
				}
			break;
	}
	return 0;
}

int CVICALLBACK onSet (int panel, int control, int event,
					   void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
				
				//preluam valorile de pe panou
				GetCtrlVal(panel, PANEL_START, &start);
				GetCtrlVal(panel, PANEL_STOP, &stop);
				
				//setam intervalul pentru axe
				//SetAxisRange(panel, PANEL_GRAPH, VAL_MANUAL, start* waveInfo[0], stop * waveInfo[0], VAL_AUTOSCALE, 1, 2);
				SetAxisRange(panel, PANEL_FILTERED_GRAPH, VAL_MANUAL, start* waveInfo[0], stop * waveInfo[0], VAL_AUTOSCALE, 1, 2);
			break;
	}
	return 0;
}

int CVICALLBACK OnFreqPanelCB (int panel, int event, void *callbackData,
							   int eventData1, int eventData2)
{
		switch (event)
	{
		case EVENT_GOT_FOCUS:

			break;
		case EVENT_LOST_FOCUS:

			break;
		case EVENT_CLOSE:
			QuitUserInterface(0);
			break;
	}
	return 0;
	
}

int CVICALLBACK OnSwitchPanelCB (int panel, int control, int event,
								 void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			if(panel == panelHandle)
			{
				
				SetCtrlVal(panelHandle, PANEL_IDC_SWITCH_PANEL, 1);
				DisplayPanel(freqPanel);
				HidePanel(panel);
			}
			else
			{
				SetCtrlVal(freqPanel, FREQ_PANEL_IDC_SWITCH_PANEL, 0);
				DisplayPanel(panelHandle);
				HidePanel(panel);
			}
			break;
	}
	return 0;
}

int CVICALLBACK onFrequency (int panel, int control, int event,
							 void *callbackData, int eventData1, int eventData2)
{
	GetCtrlVal(freqPanel, FREQ_PANEL_POINTS_NUMBER, &N);
	
	WindowConst winConst;
	
	//vectorul ce contine spectrul semnalului convertit in volti
	double convertedSpectrum[(int)sampleRate/2];
	//spectrul de putere
	double autoSpectrum[(int)sampleRate/2];
	
	double df = 0.0; //pasul in domeniul frecventei
	double freqPeak = 0.0; //valoarea maxima din spectrul de putere
	double powerPeak = 0.0; //frecventa estimata pentru spectrul de putere
	
	char unit[32] = "V";  //voltage		  	
	
	switch (event)
	{
		case EVENT_COMMIT:
			
			ScaledWindowEx(waveData, (int)sampleRate, RECTANGLE_, 0, &winConst); 
			AutoPowerSpectrum(waveData, (int)sampleRate, 1.0/sampleRate, autoSpectrum, &df);
			PowerFrequencyEstimate(autoSpectrum, (int)sampleRate/2, -1.0, winConst, df, 6, &freqPeak, &powerPeak);
					
			//afisare pe interfata a Frequency Peak si Power Peak
			SetCtrlVal(freqPanel,FREQ_PANEL_FREQ_PEAK,freqPeak);
			SetCtrlVal(freqPanel,FREQ_PANEL_POWER_PEAK,powerPeak);
					
			SpectrumUnitConversion(autoSpectrum, (int)sampleRate/2, 0, SCALING_MODE_LINEAR, DISPLAY_UNIT_VRMS, df, winConst, convertedSpectrum, unit);
			
			//afisare spectru
			DeleteGraphPlot(panel, FREQ_PANEL_GRAPH_SPECTRU, -1, VAL_IMMEDIATE_DRAW);
			PlotWaveform(panel, FREQ_PANEL_GRAPH_SPECTRU, convertedSpectrum, (int)sampleRate/2, VAL_DOUBLE, 1.0, 0.0, 0.0, df,VAL_THIN_LINE, VAL_EMPTY_SQUARE, VAL_SOLID,  VAL_CONNECTED_POINTS, VAL_RED);	
			
			break;
	}
	return 0;
}

int CVICALLBACK onApplyF (int panel, int control, int event,
						  void *callbackData, int eventData1, int eventData2)
{
	int sec;
	double *raw;//semnal nefiltrat

	double final[npoints/6]; //semnal filtrat si ferestruit
	double window[npoints/6]; //semnal ferestruit

	
	int fcut = 800;
	
	int winType; //tip fereastra
	int signalType;//tip semnal
	
	static WindowConst winConst;
	double *powerSpectrum = 0;
	double *frequencyArray = 0;//converted
	
	char unit[32] = "V";
	double df = 0.0;
	
	switch (event)
	{
		case EVENT_COMMIT:	
			DeleteGraphPlot(freqPanel, FREQ_PANEL_GRAPH_WINDOW, -1, VAL_IMMEDIATE_DRAW);
			GetCtrlVal(freqPanel, FREQ_PANEL_POINTS_NUMBER, &N);
			
			GetCtrlVal(freqPanel, FREQ_PANEL_SECONDS, &sec);
			
			
			raw = (double*)calloc(npoints/6,sizeof(double));
			for(int i = 0; i < npoints/6; i++)
			{
				raw[i] = waveData[sec*npoints/6+i];
			}	 
			
			GetCtrlVal(freqPanel, FREQ_PANEL_WINDOW_TYPE, &winType);
			
			
			//plotare semnal pe secunde
			DeleteGraphPlot (freqPanel, FREQ_PANEL_GRAPH_NEFILTRAT, -1, VAL_IMMEDIATE_DRAW);
			PlotY (freqPanel, FREQ_PANEL_GRAPH_NEFILTRAT, raw, npoints/6, VAL_DOUBLE, VAL_THIN_LINE, VAL_EMPTY_SQUARE, VAL_SOLID, VAL_CONNECTED_POINTS, VAL_RED);
			
			
			LinEv1D(raw, npoints/6, 0, 1, window);//vectorul raw este umplut cu valori de 1
											//obtains the i element of the output array
			
			//tip de fereastra
			switch (winType)
			{
				case 0:
					HanWin(window, npoints/6);
					break;
				case 1:
					HamWin(window, npoints/6);
					break;
			}
			DeleteGraphPlot(freqPanel, FREQ_PANEL_GRAPH_WINDOW, -1, VAL_IMMEDIATE_DRAW);
			PlotY(freqPanel, FREQ_PANEL_GRAPH_WINDOW, window, npoints/6, VAL_DOUBLE, VAL_THIN_LINE, VAL_EMPTY_SQUARE, VAL_SOLID, VAL_CONNECTED_POINTS, VAL_RED);
			
			
			Mul1D(raw,window, npoints/6, final);//multiplies two arrays-->that lead to one
			DeleteGraphPlot(freqPanel, FREQ_PANEL_GRAPH_FERESTRUIT, -1, VAL_IMMEDIATE_DRAW);
			PlotY (freqPanel, FREQ_PANEL_GRAPH_FERESTRUIT, final, npoints/6, VAL_DOUBLE, VAL_THIN_LINE, VAL_EMPTY_SQUARE, VAL_SOLID, VAL_CONNECTED_POINTS, VAL_RED);
			
			
			GetCtrlVal(freqPanel, FREQ_PANEL_FILT_TYPE, &signalType);
			
			double *filteredSignal;
			filteredSignal = (double *)calloc(npoints, sizeof(double));
			
			//tip de semnal
			switch(signalType)
			{
				case 0:
					Elp_HPF(final, npoints/6, sampleRate, fcut, 0.1, 40.0, 5, filteredSignal);
					break;
				case 1:
					InvCh_HPF(final, npoints/6, sampleRate, fcut, 40.0, 5, filteredSignal);
					break;
			}
			DeleteGraphPlot (freqPanel, FREQ_PANEL_GRAPH_FILT, -1, VAL_IMMEDIATE_DRAW);
			PlotY (freqPanel, FREQ_PANEL_GRAPH_FILT, filteredSignal, npoints/6, VAL_DOUBLE, VAL_THIN_LINE, VAL_EMPTY_SQUARE, VAL_SOLID, VAL_CONNECTED_POINTS, VAL_RED);
			
				
			GetCtrlVal(freqPanel, FREQ_PANEL_POINTS_NUMBER, &N);
			//plotare spectru semnal filtrat
			powerSpectrum = (double *)calloc(sampleRate/2, sizeof(double));
			frequencyArray = (double *)calloc(sampleRate/2, sizeof(double));
			
			DeleteGraphPlot(freqPanel, FREQ_PANEL_GRAPH_SPEC_FILT, -1, VAL_IMMEDIATE_DRAW);
			ScaledWindowEx(filteredSignal, (int)sampleRate, RECTANGLE_, 0, &winConst); 
        	AutoPowerSpectrum(filteredSignal, (int)sampleRate, 1.0/sampleRate, powerSpectrum, &df);
			
			SpectrumUnitConversion(powerSpectrum, (int)sampleRate/2, 0, SCALING_MODE_LINEAR, DISPLAY_UNIT_VPK, df, winConst,frequencyArray, unit);
			PlotY(freqPanel, FREQ_PANEL_GRAPH_SPEC_FILT, frequencyArray, sampleRate/2, VAL_DOUBLE, VAL_THIN_LINE, VAL_EMPTY_SQUARE, VAL_SOLID, VAL_CONNECTED_POINTS, VAL_RED);
	}
	return 0;
}
