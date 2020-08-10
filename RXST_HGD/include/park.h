/* =================================================================================
File name:       PARK.H (IQ version)                    
                    
Originator:	Digital Control Systems Group
			Texas Instruments

Description: 
Header file containing constants, data type, and macro definitions for the PARK.
=====================================================================================
 History:
-------------------------------------------------------------------------------------
 10-15-2009	Version 1.0                                                  
------------------------------------------------------------------------------*/
#ifndef __PARK_H__
#define __PARK_H__

typedef struct {  float32  Alpha;  		// Input: stationary d-axis stator variable
				  float32  Beta;	 	// Input: stationary q-axis stator variable
				  float32  Angle;		// Input: rotating angle (pu)
				  float32  Ds;			// Output: rotating d-axis stator variable
				  float32  Qs;			// Output: rotating q-axis stator variable
				  float32  Sine;
				  float32  Cosine;
		 	 	} PARK;	            

typedef PARK *PARK_handle;
/*-----------------------------------------------------------------------------
Default initalizer for the PARK object.
-----------------------------------------------------------------------------*/                     
#define PARK_DEFAULTS {   0, \
                          0, \
                          0, \
                          0, \
                          0, \
						  0, \
                          0, \
              			  }

/*------------------------------------------------------------------------------
	PARK Transformation Macro Definition
------------------------------------------------------------------------------*/


#define PARK_MACRO(v)											\
																\
	v.Ds = v.Alpha*v.Cosine + v.Beta*v.Sine;	\
    v.Qs = v.Beta*v.Cosine - v.Alpha*v.Sine;

#endif // __PARK_H__
