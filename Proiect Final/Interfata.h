/**************************************************************************/
/* LabWindows/CVI User Interface Resource (UIR) Include File              */
/*                                                                        */
/* WARNING: Do not add to, delete from, or otherwise modify the contents  */
/*          of this include file.                                         */
/**************************************************************************/

#include <userint.h>

#ifdef __cplusplus
    extern "C" {
#endif

     /* Panels and Controls: */

#define  FREQ_PANEL                       1       /* callback function: OnFreqPanelCB */
#define  FREQ_PANEL_IDC_SWITCH_PANEL      2       /* control type: binary, callback function: OnSwitchPanelCB */
#define  FREQ_PANEL_GRAPH_NEFILTRAT       3       /* control type: graph, callback function: (none) */
#define  FREQ_PANEL_SPECTRU_BUTTON        4       /* control type: command, callback function: onFrequency */
#define  FREQ_PANEL_FREQ_PEAK             5       /* control type: numeric, callback function: (none) */
#define  FREQ_PANEL_POWER_PEAK            6       /* control type: numeric, callback function: (none) */
#define  FREQ_PANEL_SECONDS               7       /* control type: ring, callback function: (none) */
#define  FREQ_PANEL_POINTS_NUMBER         8       /* control type: ring, callback function: (none) */
#define  FREQ_PANEL_GRAPH_SPECTRU         9       /* control type: graph, callback function: (none) */
#define  FREQ_PANEL_GRAPH_WINDOW          10      /* control type: graph, callback function: (none) */
#define  FREQ_PANEL_GRAPH_SPEC_FILT       11      /* control type: graph, callback function: (none) */
#define  FREQ_PANEL_GRAPH_FILT            12      /* control type: graph, callback function: (none) */
#define  FREQ_PANEL_GRAPH_FERESTRUIT      13      /* control type: graph, callback function: (none) */
#define  FREQ_PANEL_WINDOW_TYPE           14      /* control type: ring, callback function: (none) */
#define  FREQ_PANEL_FILT_TYPE             15      /* control type: ring, callback function: (none) */
#define  FREQ_PANEL_APPLY                 16      /* control type: command, callback function: onApplyF */
#define  FREQ_PANEL_DECORATION            17      /* control type: deco, callback function: (none) */

#define  PANEL                            2       /* callback function: mainPanel */
#define  PANEL_FORWARD_BUTTON             2       /* control type: command, callback function: onForwardCB */
#define  PANEL_BACKWARDS_BUTTON           3       /* control type: command, callback function: onBackwardCB */
#define  PANEL_LOAD_BUTTON                4       /* control type: command, callback function: loadWaveFunction */
#define  PANEL_FILTERED_GRAPH             5       /* control type: graph, callback function: (none) */
#define  PANEL_START                      6       /* control type: numeric, callback function: (none) */
#define  PANEL_DISPERSION_VAL             7       /* control type: numeric, callback function: (none) */
#define  PANEL_MEDIAN_VAL                 8       /* control type: numeric, callback function: (none) */
#define  PANEL_ZERO_COUNT_VAL             9       /* control type: numeric, callback function: (none) */
#define  PANEL_MEAN_VAL                   10      /* control type: numeric, callback function: (none) */
#define  PANEL_MAX_INDEX                  11      /* control type: numeric, callback function: (none) */
#define  PANEL_MAX_VAL                    12      /* control type: numeric, callback function: (none) */
#define  PANEL_MIN_INDEX                  13      /* control type: numeric, callback function: (none) */
#define  PANEL_MIN_VAL                    14      /* control type: numeric, callback function: (none) */
#define  PANEL_STOP                       15      /* control type: numeric, callback function: (none) */
#define  PANEL_SELECT_FILTER              16      /* control type: ring, callback function: (none) */
#define  PANEL_TEXTMSG                    17      /* control type: textMsg, callback function: (none) */
#define  PANEL_DECORATION_4               18      /* control type: deco, callback function: (none) */
#define  PANEL_APPLY_BUTTON               19      /* control type: command, callback function: onApply */
#define  PANEL_WINDOW_SIZE                20      /* control type: numeric, callback function: (none) */
#define  PANEL_ALPHA_VAL                  21      /* control type: numeric, callback function: (none) */
#define  PANEL_HISTOGRAM_BUTTON           22      /* control type: command, callback function: onHistogram */
#define  PANEL_ANVELOPARE_BUTTON          23      /* control type: command, callback function: onAnvelopare */
#define  PANEL_DERIVATA_BUTTON            24      /* control type: command, callback function: onDerivata */
#define  PANEL_SAVE_BUTTON                25      /* control type: command, callback function: onSave */
#define  PANEL_SET_SECOND_BUTTON          26      /* control type: command, callback function: onSet */
#define  PANEL_IDC_SWITCH_PANEL           27      /* control type: binary, callback function: OnSwitchPanelCB */
#define  PANEL_DECORATION_2               28      /* control type: deco, callback function: (none) */
#define  PANEL_GRAPH                      29      /* control type: graph, callback function: (none) */
#define  PANEL_DECORATION                 30      /* control type: deco, callback function: (none) */

#define  PANEL_DER                        3       /* callback function: onDerivataPanel */
#define  PANEL_DER_GRAPH_DERIVATA         2       /* control type: graph, callback function: (none) */

#define  PANEL_HIST                       4       /* callback function: onHistogramPanel */
#define  PANEL_HIST_HISTOGRAM             2       /* control type: graph, callback function: (none) */


     /* Control Arrays: */

          /* (no control arrays in the resource file) */


     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */

int  CVICALLBACK loadWaveFunction(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK mainPanel(int panel, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK onAnvelopare(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK onApply(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK onApplyF(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK onBackwardCB(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK onDerivata(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK onDerivataPanel(int panel, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK onForwardCB(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK OnFreqPanelCB(int panel, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK onFrequency(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK onHistogram(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK onHistogramPanel(int panel, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK onSave(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK onSet(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK OnSwitchPanelCB(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif