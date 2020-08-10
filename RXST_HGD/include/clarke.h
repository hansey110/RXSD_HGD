/* =================================================================================
File name:       CLARKE.H  (IQ version)                  
                    
Originator:	Digital Control Systems Group
			Texas Instruments

Description: 
Header file containing constants, data type, and macro definition for the CLARKE.
=====================================================================================
 History:
-------------------------------------------------------------------------------------
 04-15-2010	Version 1.1                                                  
------------------------------------------------------------------------------*/
#ifndef __CLARKE_H__
#define __CLARKE_H__
#include "math.h"
typedef struct {  float32  As;  		// Input: phase-a stator variable
				  float32  Bs;			// Input: phase-b stator variable
				  float32  Cs;          // Input: phase-c stator variable
				  float32  Alpha;		// Output: stationary d-axis stator variable
				  float32  Beta;		// Output: stationary q-axis stator variable
		 	 	} CLARKE;	            

typedef CLARKE *CLARKE_handle;
/*-----------------------------------------------------------------------------
	Default initalizer for the CLARKE object.
-----------------------------------------------------------------------------*/                     
#define CLARKE_DEFAULTS { 0, \
                          0, \
                          0, \
                          0, \
                          0, \
              			} 

/*------------------------------------------------------------------------------
	CLARKE Transformation Macro Definition
------------------------------------------------------------------------------*/

	
#define CLARKE_MACRO(v)											\
																\
v.Alpha = v.As;													\
v.Beta = (v.As+2*v.Bs)*0.57735026918963;                     \
v.Beta = sin(v.As);

#endif // __CLARKE_H__
