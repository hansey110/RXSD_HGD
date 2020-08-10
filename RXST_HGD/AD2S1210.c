 //###########################################################################

#include "DSP28x_Project.h"     // Headerfile Include File

#pragma CODE_SECTION(AD2S1210_Read, "ramfuncs");

struct AD2S1210 AD2S1210_Resolver;

/*******************************************************************************
*��������Initial
*��������������������ʼ��ȫ�ֱ���
*����˵����
*���ú�����      AD2S1210����һ��֮���ܼ�ס
*ȫ�ֱ�����
*ȫ�ֱ�����  0x88    LOS             �������źŵ��ڸ�ֵ������
*ȫ�ֱ�����  0x89    DOS Overange    �������źŸ��ڸ�ֵ������
*ȫ�ֱ�����  0x8A    DOS Mismatch    �������ź�Vpp���ڸ�ֵ������
*ȫ�ֱ�����  0x8B    DOS Reset Max   ����ʼ�����źŷ�ֵ���ֵ��
*ȫ�ֱ�����  0x8C    DOS Reset Min   ����ʼ�����źŷ�ֵ��Сֵ��
*ȫ�ֱ�����  0x8D    LOT High        ���ջ����������ڸ�ֵ������
*ȫ�ֱ�����  0x8E    LOT LOW         ���ջ����������ڸ�ֵ����LOT High������
*���룺
*���أ�    10MHz  2.44KHz<AD2S1210_Resolver.EXC_Frq<12.2KHz        ���ʹ���305Hz
*******************************************************************************/
//Uint16 XB_FalutNum = 0;
void AD2S1210_Init (void)
{
//	DELAY_US(100000);

	AD2S1210_Resolver.EXC_Frq = (Uint16)(100*0.1*32768.0/10.0/1000.0 + 0.5);    // ����Ƶ��=(N*10*1000/2^15)=10kHz
//    AD2S1210_Resolver.EXC_Frq = (Uint16)(g_stDriverParamA.fExcitationFreq*32768/10000+0.5);   //����Ƶ�ʿ�����
    AD2S1210_Resolver.CTL.all = 0x7F;                                       // 44����λ����������������16bit       0x7F
    AD2S1210_Resolver.LOS = 0;                                             // 1.9V����       LSB=0.038V
    AD2S1210_Resolver.DOS_OverRange = 118;                                  // 4.5V����
    AD2S1210_Resolver.DOS_MisMatch = 20;                                    // ʧ��760mV
    AD2S1210_Resolver.LOS_RST_Max = AD2S1210_Resolver.LOS+2;      			// �� LOS ��2LSB
    AD2S1210_Resolver.LOS_RST_Min = AD2S1210_Resolver.DOS_OverRange-2;      // �� DOS OVERRANGEС2LSB

    AD2S1210_SetPara(XB_EXC_FRQ_REG, AD2S1210_Resolver.EXC_Frq<<8);         // ���ü���Ƶ��
    AD2S1210_SetPara(XB_CTL_REG, AD2S1210_Resolver.CTL.all<<8);             // ���ÿ��ƼĴ���
    AD2S1210_SetPara(XB_LOS_REG, AD2S1210_Resolver.LOS<<8);                 // LOS THRESHOLD REGISTER
    AD2S1210_SetPara(XB_LOS_OVER_REG, AD2S1210_Resolver.DOS_OverRange<<8);  // DOS OVERRANGE THRESHOLD REGISTER
    AD2S1210_SetPara(XB_DOS_MIS_REG, AD2S1210_Resolver.DOS_MisMatch<<8);    // DOS MISMATCH THRESHOLD REGISTER
    AD2S1210_SetPara(XB_LOS_RST_MAX_REG, AD2S1210_Resolver.LOS_RST_Max<<8); // LOS RESET MAX REGISTER
    AD2S1210_SetPara(XB_LOS_RST_MIN_REG, AD2S1210_Resolver.LOS_RST_Min<<8); // LOS RESET MIN REGISTER
    AD2S1210_SetPara(XB_SOFT_RST_REG, 0xFF00);                              // Soft RST
    DELAY_US(100000);                                                          //

    AD2S1210_ClearFault();          //tmp1 = Spia_xmit(XB_POSITIONL_REG);
    DELAY_US(100000);

    Spia_xmit(XB_FAULT_REG);                        						// ������ϼĴ�����ַ
    if(Spia_xmit(XB_POSITIONH_REG) & 0x40)                     				// ��ù������ݣ�ͬʱд��λ�üĴ�����ַXB_POSITIONH_REG
	{
//    	SYSReg.Pc.AlmReg.bit.PosSensor_Err = 1;								// �����󱨣��ر�
	}

/*
    while(Spia_xmit(XB_FAULT_REG) & 0x7F)                     				// ��ù������ݣ�ͬʱд��λ�üĴ�����ַXB_POSITIONH_REG
    {
        SYSReg.Bus_Rd.Alm_Reg.bit.PSensor_Err = 1;          				// λ�ô������쳣

        AD2S1210_ClearFault();          //tmp1 = Spia_xmit(XB_POSITIONL_REG);
        DELAY_US(100000);

    }

//    Spia_xmit(XB_FAULT_REG);                        						// ������ϼĴ�����ַ
//	XB_FalutNum = Spia_xmit(XB_POSITIONH_REG) & 0x7F;
//	if(XB_FalutNum)                     				// ��ù������ݣ�ͬʱд��λ�üĴ�����ַ
//	{
		SYSReg.Bus_Rd.Alm_Reg.bit.PSensor_Err = 0;          				// λ�ô������쳣
//	}
*/
}	
 
/*******************************************************************************
*��������ClearFault
*��������������������ʼ��ȫ�ֱ���
*����˵����
*���ú�����
*ȫ�ֱ�����
*���룺
*���أ�
*******************************************************************************/
void AD2S1210_ClearFault (void)
{
    XB_SAMPLE_Set();
    XB_SAMPLE_Reset();          //SAMPLE�½��ظ����ٶȡ�λ�á���������
    DELAY_US(1);              // Ҫ�����0.22us   ��֤����ʱ��
    XB_SAMPLE_Set();

    XB_CS_LOW();
    Spia_xmit(XB_FAULT_REG);    // �ȷ���λ     FF���ϼĴ�����ַ
    Spia_xmit(0);
    XB_CS_HIGH();

    XB_SAMPLE_Reset();
    DELAY_US(1);              // Ҫ�����0.22us   ��֤����ʱ��
    XB_SAMPLE_Set();
}

/*******************************************************************************
*��������AD2S1210_SetPara
*��������������������ʼ��ȫ�ֱ���
*����˵����
*���ú�����
*ȫ�ֱ�����
*���룺
*���أ�
*******************************************************************************/
void AD2S1210_SetPara (Uint16 addr, Uint16 val)
{
    Spia_xmit(addr);                            // д�Ĵ�����ַ
    DELAY_US(1);                              // ��С�ֱ���0.15us
    Spia_xmit(val);                             // дֵ
    DELAY_US(1);
}

/*******************************************************************************
*��������AD2S1210_Read
*�����������Ĵ�����Ϣ
*����˵����
*���ú�����  ��˳��
*ȫ�ֱ�����
*���룺
*���أ�
*******************************************************************************/
void AD2S1210_Read (Uint16 *tmp)
{
    Uint16 tmp1;

    XB_SAMPLE_Reset();          //SAMPLE�½��ظ����ٶȡ�λ�á���������
    DELAY_US(0.3);              // Ҫ�����0.22us   ��֤����ʱ��
    XB_SAMPLE_Set();

    XB_CS_LOW();
    Spia_xmit(XB_POSITIONH_REG);                         //
    XB_CS_HIGH();
    DELAY_US(0.3);

    XB_CS_LOW();
    tmp1=(Spia_xmit(XB_POSITIONL_REG) & 0xFF);     // �õ�λ��
    XB_CS_HIGH();
    DELAY_US(0.3);

    XB_CS_LOW();
    *tmp++ = (tmp1<<8) +  Spia_xmit(XB_SPEEDH_REG);
    XB_CS_HIGH();
    DELAY_US(0.3);

    XB_CS_LOW();
    tmp1 =(Spia_xmit(XB_SPEEDL_REG) & 0xFF);      // �õ��ٶ�
    XB_CS_HIGH();
    DELAY_US(0.3);

    XB_CS_LOW();
    *tmp++ = (tmp1<<8) + Spia_xmit(XB_FAULT_REG);                        // ������ϼĴ�����ַ
    XB_CS_HIGH();
    DELAY_US(0.3);

    XB_CS_LOW();
    *tmp++ =Spia_xmit(XB_POSITIONL_REG);           // �õ�����
    XB_CS_HIGH();


/*
    Spia_xmit(XB_FAULT_REG);                        // ������ϼĴ�����ַ
    *tmp++ = Spia_xmit(XB_POSITIONL_REG);			// �õ�����
    tmp1 = Spia_xmit(XB_POSITIONH_REG);
	*tmp++ = (Spia_xmit(XB_SPEEDL_REG)<<8) | ( tmp1 & 0xFF);     // �õ�λ��
	tmp1 = Spia_xmit(XB_SPEEDH_REG);
	*tmp++ = (Spia_xmit(XB_FAULT_REG)<<8) | (tmp1 & 0xFF);      // �õ��ٶ�
*/
}

//===========================================================================
// No more.
//===========================================================================

