/* =================================================================================
File name:       ServoModule.H
Description:伺服各个函数模块
Header file containing constants, data type definitions, and
function prototypes for the PIDREG3.
=====================================================================================
 History:
-------------------------------------------------------------------------------------
 04-15-2005 Version 3.20
------------------------------------------------------------------------------*/
extern void SetParameters(void);
extern void InitController(void);
extern void GetEncoder(void);
extern void ProcessEncoder(void);
extern void GetSerialCommand(void);
extern void ProcessSerialCommand(void);
extern void ReturnDataToMc(void);
extern void CheckFault(void);
extern void ProcessPositionLoopA(void);
extern void ProcessVelocityLoopA(void);
extern void CanTx(void);
extern void GetCanCommand(void);
extern void GetTemp(void);

extern float CtoF32(unsigned short* iChar);
extern void F32toC(float f, unsigned short* iChar);
extern void F32toC2(float f, unsigned short* iChar);
extern void F32toC2_3(float f, unsigned short* iChar);



//===========================================================================
// No more.
//===========================================================================
