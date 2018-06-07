/*
 * gpio.c
 *
 *  Created on: 2018-6-4
 *      Author: Landers Ƥ
 */
#include "xparameters.h"
#include"xintc.h"
#include"xil_io.h"
#include"xil_types.h"
#include"mb_interface.h"
#include"stdio.h"
#define dip_data 0x00
#define dip_tri 0x04
#define dip_isr 0x0120

#define led_data 0x00
#define led_tri 0x04
#define led_isr 0x0120

#define intc_isr 0x00
#define intc_ier 0x08
#define intc_iar 0x0c
#define intc_mer 0x1c

#define uart_rx 0x00
#define uart_tx 0x04
#define uart_stat 0x08
#define uart_ctl 0x0c

#define gpio_base 0x40000000//gpio ,uart address
#define led 0x40040000
#define intc_base 0x41200000
#define uart_base 0x40640000

void My_ISR(void)__attribute__((interrupt_handler));
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
		if(Rx_flag)
		{   xil_printf("the rx data is0x%x\r\n",rxData);
		    Rx_flag=0;

	}
	delay_50ms();
	txtime=txtime+1;
	if(txtime==10000) txtime=0x00;
		int uart_flag;
		uart_flag=Xil_In32(uart_base+uart_stat);
		if(uart_flag&0x04)
			{
				if(txtime%2)
					{   int txdata;
						txdata=Xil_In32(gpio_base+dip_data);
						Xil_Out32(uart_base+uart_tx,txdata);
						}
			}
}
return 0;
}
void Initialize()
 {
 	Rx_flag=0x00;
 	rxData=0x00;
 	txtime=0x00;
 	Xil_Out8(gpio_base+dip_tri,0xff);
 	Xil_Out8(led+led_tri,0x00);
 	Xil_Out8(led+led_data,0x5a);

 	Xil_Out32(uart_base+uart_ctl,0x13);
 	Xil_Out32(intc_base+intc_iar,0xffffffff);
 	Xil_Out32(intc_base+intc_ier,0x80000003);
    Xil_Out32(intc_base+intc_mer,0x03);
    microblaze_enable_interrupts();


 }
void My_ISR(void)
{
 int status;
 status=Xil_In32(intc_base+intc_isr);
 if(status&0x01)
 	{
 		Uarthandler();

 	}
 	Xil_Out32(intc_base+intc_iar,status);
}

void Uarthandler()
{   int uart_flag;
    uart_flag=Xil_In32(uart_base+uart_stat);
	if(uart_flag&0x01)
		{
			Rx_flag=1;
			rxData=Xil_In32(uart_base+uart_rx);
			Xil_Out8(led+led_data,rxData);

		}
		Xil_Out32(uart_base+uart_ctl,0x13);

}

void delay_50ms()
{
	int i;
	for(i=0;i<5000000;i++);

}
