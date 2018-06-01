#include "xparameters.h"
#include"xintc.h"
#include"xil_io.h"
#include"xil_types.h"
#include"mb_interface.h"
#include"stdio.h"
#define sw_data 0x00
#define led_data 0x08
#define sw_tri 0x04
#define led_tri 0x0c
#define intc_isr 0x00
#define intc_ier 0x08
#define intc_iar 0x0c
#define intc_mer 0x1c
#define uart_rx 0x00
#define uart_tx 0x04
#define uart_stat 0x08
#define uart_ctl 0x0c
#define gpio_base 0x40000000//gpio ,uart address
#define intc_base 0x41200000
#define uart_base 0x40600000

void MY_ISR(void)_attribute_((interrupt_handler));//intr reg
void Initialize();
void Uarthandler();
void delay_50ms();
short Rx_flag;
unsigned char rxData;
int txtime;
int main(void)
{
	xil_printf("\r\n running test\r\n");
	Initialize();
	while(1)
	{
		/*if(Rx_flag)
		{xil_printf("the rx data is0x%x\r\n",rxData);
		Rx_flag=0;
		
	}*/
	delay_50ms();
	txtime=txtime+1;
	if(txtime==10000)txtime=0x00;
		int uart_flag;
		uart_flag=Xil_In32)(uart_base+uart_stat);
		if(uart_flag&0x04)
			{
				if(txtime%2)
					{int txdata;
						txdata=Xil_In32(gpio_base+sw_data);
						xil_Out32(uart_base+uart_tx,xtdata);
						}
			}
}
return0;
}
void Intalize()
 {
 	Rx_flag=0x00;
 	rxData=0x00;
 	txtime=0x00;
 	Xil_Out8(gpio_base+sw_tri,0xff);
 	xil_Out8(gpio_base+led_data,0x5a);
 	xil_Out32(uart_base+uart_ctl,0x13);
 	xil_Out32(intc_base+intc_iar,0xffffffff);
 	xil_Out32(intc_base+intc_ier,0x00000001);
  xil_Out32(intc_base+intc_mer,0x03);
  microblaze_enable_interrpts();
  
 	
 }
 int status;
 status=Xil_In32(intc_base+intc_isr);
 if(status&0x01)
 	{
 		Uarthandler();
 		
 	}
 	Xil_Out32(intc_base+intc_iar,status);
}

void Uarthandler()
{
	int uart_flag=Xil_In32(uart_base+uart_stat);
	if(uart_flag&0x01)
		{
			Rx_flag=1;
			rx_Data=Xil_In32(uart_base+urat_rx);
			xil_printf("0x%x\n\r",rxData);
			Xil_Out8(gpio_base+led_data,rxData);
			
		}
		Xil_Out32(uart_base+uart_ctl,0x13);
		
}

void delay_50ms();
{
	int i;
	for(i=0;i<50000000;i++);
	
}