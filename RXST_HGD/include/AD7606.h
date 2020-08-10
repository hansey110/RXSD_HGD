//----------------------------------------------------------------------------------
//	FILE:			ADS1210.h
//
//	Description:	shared variables and constants
//
//   Revision/ Version: See Resolver-Main.c
//----------------------------------------------------------------------------------
#ifndef _AD7606_H_
#define _AD7606_H_



#define AD_SAMPLE_Start()        GpioDataRegs.GPBCLEAR.bit.GPIO33 = 1
#define AD_SAMPLE_Stop()         GpioDataRegs.GPBSET.bit.GPIO33=1

#define AD_Reset_Set()          GpioDataRegs.GPBSET.bit.GPIO32 = 1
#define AD_Reset_Clear()        GpioDataRegs.GPBCLEAR.bit.GPIO32 = 1



// ============================================
// variables used for library support 
// ============================================

extern void InitialAD7606(void);
extern void InitialAD7606Offset();
extern void ReadAD7606();
extern int AD_sample[4];


#endif


//===========================================================================
// No more.
//===========================================================================

