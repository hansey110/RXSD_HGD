//###########################################################################
//
// FILE:   CLAShared.h
//
// TITLE:  CLA and CPU shared variables and constants
//
//###########################################################################
// $TI Release: F2803x C/C++ Header Files and Peripheral Examples V130 $
// $Release Date: May  8, 2015 $
// $Copyright: Copyright (C) 2009-2015 Texas Instruments Incorporated -
//             http://www.ti.com/ ALL RIGHTS RESERVED $
//###########################################################################

#ifndef CLA_SHARED_H
#define CLA_SHARED_H

#ifdef __cplusplus
extern "C" {
#endif


//  #include "IQmathLib.h"
#include "DSP28x_Project.h"


extern float g_SinEleAngleA;
extern float g_CosEleAngleA;
extern float EleAngleA;
extern float g_fMeaCurrentU;
extern float g_fMeaCurrentV;
extern float g_fMeaCurrentW;
extern float g_fMeaCurrentD;
extern float g_fMeaCurrentQ;

// The following are symbols defined in the CLA assembly code
// Including them in the shared header file makes them
// .global and the main CPU can make use of them.

__interrupt void Cla1Task1();
__interrupt void Cla1Task2();
__interrupt void Cla1Task3();
__interrupt void Cla1Task4();
__interrupt void Cla1Task5();
__interrupt void Cla1Task6();
__interrupt void Cla1Task7();
__interrupt void Cla1Task8();

//extern Uint16 Cla1Prog_Start;
//extern Uint16 Cla1funcsLoadStart;
//extern Uint16 Cla1funcsLoadEnd;
//extern Uint16 Cla1funcsRunStart;
//extern Uint16 Cla1funcsLoadSize;
//extern Uint16 Cla1mathTablesLoadStart;
//extern Uint16 Cla1mathTablesLoadEnd;
//extern Uint16 Cla1mathTablesLoadSize;



extern Uint16 Cla1ProgRunStart, Cla1ProgLoadStart, Cla1ProgLoadSize;
extern Uint16 CLA1mathTablesRunStart, CLA1mathTablesLoadStart,CLA1mathTablesLoadSize;




#ifdef __cplusplus
}
#endif /* extern "C" */


#endif  // end of CLA_SHARED definition

