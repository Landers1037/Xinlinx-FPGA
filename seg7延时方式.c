#include"xparameter.h"
#include "xil_io.h"
int main()
{   char segcode[8]={0xf9,0xf9,0xf9,0xf9,0xf9,0xf9,0xf9,0xf9};
    int i,j;
    int pos=0xff7f;//初始位码
    Xil_Out8(XPAR_SEG_0_BASEADDR+0x4,0x0);//gpio输出
    Xil_Out8(XPAR_SEG_0_BASEADDR+0xc,0x0);//gpio2 output
    while(1)
    {	for(i=0;i<8;i++)
    
    {
    Xil_Out8(XPAR_SEG_0_BASEADDR,pos);//输出位码
    Xil_Out8(XPAR_SEG_0_BASEADDR+0x8,segcode[i]);//输出段码
    for(j=0;j<0xa5e100;j++);//delay
    	pos=pos>>1;
	}
	pos=0xff7f;
}

	/* code */
	return 0;
}