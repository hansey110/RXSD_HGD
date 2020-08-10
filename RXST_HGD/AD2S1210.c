 //###########################################################################

#include "DSP28x_Project.h"     // Headerfile Include File

#pragma CODE_SECTION(AD2S1210_Read, "ramfuncs");

struct AD2S1210 AD2S1210_Resolver;

/*******************************************************************************
*函数名：Initial
*功能描述：读参数，初始化全局变量
*函数说明：
*调用函数：      AD2S1210配置一次之后能记住
*全局变量：
*全局变量：  0x88    LOS             ：输入信号低于该值报警；
*全局变量：  0x89    DOS Overange    ：输入信号高于该值报警；
*全局变量：  0x8A    DOS Mismatch    ：输入信号Vpp大于该值报警；
*全局变量：  0x8B    DOS Reset Max   ：初始输入信号幅值最大值；
*全局变量：  0x8C    DOS Reset Min   ：初始输入信号幅值最小值；
*全局变量：  0x8D    LOT High        ：闭环跟踪误差大于该值报警；
*全局变量：  0x8E    LOT LOW         ：闭环跟踪误差低于该值撤销LOT High报警。
*输入：
*返回：    10MHz  2.44KHz<AD2S1210_Resolver.EXC_Frq<12.2KHz        典型带宽305Hz
*******************************************************************************/
//Uint16 XB_FalutNum = 0;
void AD2S1210_Init (void)
{
//	DELAY_US(100000);

	AD2S1210_Resolver.EXC_Frq = (Uint16)(100*0.1*32768.0/10.0/1000.0 + 0.5);    // 激磁频率=(N*10*1000/2^15)=10kHz
//    AD2S1210_Resolver.EXC_Frq = (Uint16)(g_stDriverParamA.fExcitationFreq*32768/10000+0.5);   //激磁频率可配置
    AD2S1210_Resolver.CTL.all = 0x7F;                                       // 44°相位锁定，磁滞能力，16bit       0x7F
    AD2S1210_Resolver.LOS = 0;                                             // 1.9V下限       LSB=0.038V
    AD2S1210_Resolver.DOS_OverRange = 118;                                  // 4.5V上限
    AD2S1210_Resolver.DOS_MisMatch = 20;                                    // 失配760mV
    AD2S1210_Resolver.LOS_RST_Max = AD2S1210_Resolver.LOS+2;      			// 比 LOS 大2LSB
    AD2S1210_Resolver.LOS_RST_Min = AD2S1210_Resolver.DOS_OverRange-2;      // 比 DOS OVERRANGE小2LSB

    AD2S1210_SetPara(XB_EXC_FRQ_REG, AD2S1210_Resolver.EXC_Frq<<8);         // 设置激磁频率
    AD2S1210_SetPara(XB_CTL_REG, AD2S1210_Resolver.CTL.all<<8);             // 设置控制寄存器
    AD2S1210_SetPara(XB_LOS_REG, AD2S1210_Resolver.LOS<<8);                 // LOS THRESHOLD REGISTER
    AD2S1210_SetPara(XB_LOS_OVER_REG, AD2S1210_Resolver.DOS_OverRange<<8);  // DOS OVERRANGE THRESHOLD REGISTER
    AD2S1210_SetPara(XB_DOS_MIS_REG, AD2S1210_Resolver.DOS_MisMatch<<8);    // DOS MISMATCH THRESHOLD REGISTER
    AD2S1210_SetPara(XB_LOS_RST_MAX_REG, AD2S1210_Resolver.LOS_RST_Max<<8); // LOS RESET MAX REGISTER
    AD2S1210_SetPara(XB_LOS_RST_MIN_REG, AD2S1210_Resolver.LOS_RST_Min<<8); // LOS RESET MIN REGISTER
    AD2S1210_SetPara(XB_SOFT_RST_REG, 0xFF00);                              // Soft RST
    DELAY_US(100000);                                                          //

    AD2S1210_ClearFault();          //tmp1 = Spia_xmit(XB_POSITIONL_REG);
    DELAY_US(100000);

    Spia_xmit(XB_FAULT_REG);                        						// 输入故障寄存器地址
    if(Spia_xmit(XB_POSITIONH_REG) & 0x40)                     				// 获得故障内容，同时写入位置寄存器地址XB_POSITIONH_REG
	{
//    	SYSReg.Pc.AlmReg.bit.PosSensor_Err = 1;								// 经常误报，关闭
	}

/*
    while(Spia_xmit(XB_FAULT_REG) & 0x7F)                     				// 获得故障内容，同时写入位置寄存器地址XB_POSITIONH_REG
    {
        SYSReg.Bus_Rd.Alm_Reg.bit.PSensor_Err = 1;          				// 位置传感器异常

        AD2S1210_ClearFault();          //tmp1 = Spia_xmit(XB_POSITIONL_REG);
        DELAY_US(100000);

    }

//    Spia_xmit(XB_FAULT_REG);                        						// 输入故障寄存器地址
//	XB_FalutNum = Spia_xmit(XB_POSITIONH_REG) & 0x7F;
//	if(XB_FalutNum)                     				// 获得故障内容，同时写入位置寄存器地址
//	{
		SYSReg.Bus_Rd.Alm_Reg.bit.PSensor_Err = 0;          				// 位置传感器异常
//	}
*/
}	
 
/*******************************************************************************
*函数名：ClearFault
*功能描述：读参数，初始化全局变量
*函数说明：
*调用函数：
*全局变量：
*输入：
*返回：
*******************************************************************************/
void AD2S1210_ClearFault (void)
{
    XB_SAMPLE_Set();
    XB_SAMPLE_Reset();          //SAMPLE下降沿更新速度、位置、故障数据
    DELAY_US(1);              // 要求大于0.22us   保证建立时间
    XB_SAMPLE_Set();

    XB_CS_LOW();
    Spia_xmit(XB_FAULT_REG);    // 先发高位     FF故障寄存器地址
    Spia_xmit(0);
    XB_CS_HIGH();

    XB_SAMPLE_Reset();
    DELAY_US(1);              // 要求大于0.22us   保证建立时间
    XB_SAMPLE_Set();
}

/*******************************************************************************
*函数名：AD2S1210_SetPara
*功能描述：读参数，初始化全局变量
*函数说明：
*调用函数：
*全局变量：
*输入：
*返回：
*******************************************************************************/
void AD2S1210_SetPara (Uint16 addr, Uint16 val)
{
    Spia_xmit(addr);                            // 写寄存器地址
    DELAY_US(1);                              // 最小分辨率0.15us
    Spia_xmit(val);                             // 写值
    DELAY_US(1);
}

/*******************************************************************************
*函数名：AD2S1210_Read
*功能描述：寄存器信息
*函数说明：
*调用函数：  读顺序：
*全局变量：
*输入：
*返回：
*******************************************************************************/
void AD2S1210_Read (Uint16 *tmp)
{
    Uint16 tmp1;

    XB_SAMPLE_Reset();          //SAMPLE下降沿更新速度、位置、故障数据
    DELAY_US(0.3);              // 要求大于0.22us   保证建立时间
    XB_SAMPLE_Set();

    XB_CS_LOW();
    Spia_xmit(XB_POSITIONH_REG);                         //
    XB_CS_HIGH();
    DELAY_US(0.3);

    XB_CS_LOW();
    tmp1=(Spia_xmit(XB_POSITIONL_REG) & 0xFF);     // 得到位置
    XB_CS_HIGH();
    DELAY_US(0.3);

    XB_CS_LOW();
    *tmp++ = (tmp1<<8) +  Spia_xmit(XB_SPEEDH_REG);
    XB_CS_HIGH();
    DELAY_US(0.3);

    XB_CS_LOW();
    tmp1 =(Spia_xmit(XB_SPEEDL_REG) & 0xFF);      // 得到速度
    XB_CS_HIGH();
    DELAY_US(0.3);

    XB_CS_LOW();
    *tmp++ = (tmp1<<8) + Spia_xmit(XB_FAULT_REG);                        // 输入故障寄存器地址
    XB_CS_HIGH();
    DELAY_US(0.3);

    XB_CS_LOW();
    *tmp++ =Spia_xmit(XB_POSITIONL_REG);           // 得到故障
    XB_CS_HIGH();


/*
    Spia_xmit(XB_FAULT_REG);                        // 输入故障寄存器地址
    *tmp++ = Spia_xmit(XB_POSITIONL_REG);			// 得到故障
    tmp1 = Spia_xmit(XB_POSITIONH_REG);
	*tmp++ = (Spia_xmit(XB_SPEEDL_REG)<<8) | ( tmp1 & 0xFF);     // 得到位置
	tmp1 = Spia_xmit(XB_SPEEDH_REG);
	*tmp++ = (Spia_xmit(XB_FAULT_REG)<<8) | (tmp1 & 0xFF);      // 得到速度
*/
}

//===========================================================================
// No more.
//===========================================================================

