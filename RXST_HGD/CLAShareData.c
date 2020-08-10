/*
 * CLAShareData.c
 *
 *  Created on: 2019Äê2ÔÂ20ÈÕ
 *      Author: QianJZ
 */

#include <CLAShared.h>
#include "DSP28x_Project.h"

#pragma DATA_SECTION(g_SinEleAngleA,"Cla1ToCpuMsgRAM")
float g_SinEleAngleA;

#pragma DATA_SECTION(g_CosEleAngleA,"Cla1ToCpuMsgRAM")
float g_CosEleAngleA;

#pragma DATA_SECTION(EleAngleA,"CpuToCla1MsgRAM")
float EleAngleA;

#pragma DATA_SECTION(g_fMeaCurrentU,"CpuToCla1MsgRAM")
float g_fMeaCurrentU;

#pragma DATA_SECTION(g_fMeaCurrentV,"CpuToCla1MsgRAM")
float g_fMeaCurrentV;

#pragma DATA_SECTION(g_fMeaCurrentW,"CpuToCla1MsgRAM")
float g_fMeaCurrentW;

#pragma DATA_SECTION(g_fMeaCurrentD,"Cla1ToCpuMsgRAM")
float g_fMeaCurrentD;

#pragma DATA_SECTION(g_fMeaCurrentQ,"Cla1ToCpuMsgRAM")
float g_fMeaCurrentQ;



