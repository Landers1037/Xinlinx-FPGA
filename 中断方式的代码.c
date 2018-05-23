#include"xtmrctr.h"
#include"xparameter.h"
#include"xintc.h"
#include"xil_exception.h"
#define IMRCTR_DEVICE_ID
XPAR_TMRCTR_0_DEVICE_ID
#define INTC_DEVICE_ID
XPAR_INTC_0_DEVICE_ID
#define TMRCTR_INTERRUPT_ID
XPAR_INTC_0_TMRCTR_0_VEC_ID
#define TIMER_CNTR_0 0
#define RESET_VALUE 0x5F5E100//100mhz


void Timercounterhandler()
XIntc InterruptController;
XTmrCtr TimerCounterInst;
u32 pos;
int i;
int main(void)
{int Status;
	i=0;
	pos=0xff7f;
	Xil_Out8(XPAR_SEG_7_BASEADDR+0x4,0x0);
	Xil_Out8(XPAR_SEG_7_BASEADDR+0xc,0x0);
	Status=XTmrCtr_Initialize(&TimerCounterInst,IMRCTR_DEVICE_ID);
	XTmrCtr_SetHandler(&TimerCounterInst,TimerCounterHandler,&TimerCounterInst);
	XTmrCtr_SetOptions(&TimerCounterInst,TIMER_CNTR_0,XTC_INT_MODE_OPTION|XTC_AUTO_RELOAD_OPTION|XTC_DOWN_COUNT_OPTION);
	XTmrCtr_SetResetValue(&TimerCounterInst,TIMER_CNTR_0,RESET_VALUE);
	XTmrCtr_Start(&TimerCounterInst,TIMER_CNTR_0);
	XIntc_Initialize(&InterruptController,INTC_DEVICE_ID);
	XIntc_Connect(&InterruptController,TMRCTR_INTERRUPT_ID,(XInterruptHandler)XTmrCtr_InterruptHandler,(void*)&TimerCounterInst);
	XIntc_Start(&InterruptController,XIN_REAL_MADE);
	XIntc_Enable(&InterruptController,TMRCTR_INTERRUPT_ID);
	microblaze_enable_interrupts();
	while(1)
	return XST_SUCCESS;
	}
	void TimerCounterHandler(void*CallBackRef,u8,TmrCtrNumber)
{Xil_Out8(XPAR_SEG_0_BASEADDR,pos);
	Xil_Out8(XPAR_SEG_0_BASEADR+0x8,0xf9);
	pos=pos>>1;
	i++;
	if(i==8)
		{i=0;
			pos=0xff7f;
		}
	}