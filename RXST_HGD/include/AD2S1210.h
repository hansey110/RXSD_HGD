//----------------------------------------------------------------------------------
//	FILE:			ADS1210.h
//
//	Description:	shared variables and constants
//
//   Revision/ Version: See Resolver-Main.c
//----------------------------------------------------------------------------------
#ifndef _AD2S1210_H_
#define _AD2S1210_H_

//--------------------------------------------------------------------------------
#define XB_POSITIONH_REG       0x8000
#define XB_POSITIONL_REG       0x8100
#define XB_SPEEDH_REG          0x8200
#define XB_SPEEDL_REG          0x8300
#define XB_LOS_REG             0x8800
#define XB_LOS_OVER_REG        0x8900
#define XB_DOS_MIS_REG         0x8A00
#define XB_LOS_RST_MAX_REG     0x8B00
#define XB_LOS_RST_MIN_REG     0x8C00
#define XB_LOT_HIGH_REG        0x8D00
#define XB_LOT_LOW_REG         0x8E00
#define XB_EXC_FRQ_REG         0x9100
#define XB_CTL_REG             0x9200
#define XB_SOFT_RST_REG        0xF000
#define XB_FAULT_REG           0xFF00

#define XB_SAMPLE_Set()    		GpioDataRegs.GPBSET.bit.GPIO54 = 1
#define XB_SAMPLE_Reset()   	GpioDataRegs.GPBCLEAR.bit.GPIO54 = 1

#define XB_CS_HIGH()          GpioDataRegs.GPASET.bit.GPIO11 = 1
#define XB_CS_LOW()           GpioDataRegs.GPACLEAR.bit.GPIO11 = 1

struct AD2S1210_CTL_BIT {                    //                      ADDR:
    Uint16 Rsvd0:8;                         //保留                                        0-7
    Uint16 RES:2;                           //位数                                      8-9
    Uint16 EnRES:2;                         //编码器输出位数                    10-11
    Uint16 Hysteresis_EN:1;                 //滞环                                        12
    Uint16 PhaseLock:1;                     //相位锁定范围                          13
    Uint16 Rsvd1:1;                         //保留                                        14
    Uint16 ADDR_DATA:1;                     //地址数据选择                          15
};

union AD2S1210_CTL_REG {
    Uint16                      all;
    struct AD2S1210_CTL_BIT      bit;
};

struct AD2S1210  {
    Uint16  EXC_Frq;       //
    union   AD2S1210_CTL_REG  CTL;
    Uint16  LOS;
    Uint16  DOS_OverRange;
    Uint16  DOS_MisMatch;
    Uint16  LOS_RST_Max;
    Uint16  LOS_RST_Min;
};

// ============================================
// variables used for library support 
// ============================================
extern struct AD2S1210 AD2S1210_Resolver;

extern void AD2S1210_ClearFault (void);
extern void AD2S1210_SetPara (Uint16 addr, Uint16 val);
extern void AD2S1210_Read (Uint16 *tmp);
extern void AD2S1210_Init ();

#endif

//===========================================================================
// No more.
//===========================================================================

