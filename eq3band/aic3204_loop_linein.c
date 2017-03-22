//////////////////////////////////////////////////////////////////////////////
// * File name: aic3204_loop_linein.c
// *                                                                          
// * Description:  AIC3204 Loop test.
// *                                                                          
// * Copyright (C) 2011 Texas Instruments Incorporated - http://www.ti.com/ 
// * Copyright (C) 2011 Spectrum Digital, Incorporated
// *                                                                          
// *                                                                          
// *  Redistribution and use in source and binary forms, with or without      
// *  modification, are permitted provided that the following conditions      
// *  are met:                                                                
// *                                                                          
// *    Redistributions of source code must retain the above copyright        
// *    notice, this list of conditions and the following disclaimer.         
// *                                                                          
// *    Redistributions in binary form must reproduce the above copyright     
// *    notice, this list of conditions and the following disclaimer in the   
// *    documentation and/or other materials provided with the                
// *    distribution.                                                         
// *                                                                          
// *    Neither the name of Texas Instruments Incorporated nor the names of   
// *    its contributors may be used to endorse or promote products derived   
// *    from this software without specific prior written permission.         
// *                                                                          
// *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS     
// *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT       
// *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR   
// *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT    
// *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,   
// *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT        
// *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,   
// *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY   
// *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT     
// *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE   
// *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.    
// *                                                                          
//////////////////////////////////////////////////////////////////////////////

#include "stdio.h"
#include "ezdsp5502.h"
#include "ezdsp5502_mcbsp.h"
#include "csl_mcbsp.h"

#include "util.h"

extern Int16 AIC3204_rset( Uint16 regnum, Uint16 regval);

/*
 *
 *  AIC3204 Loop
 *      Loops audio from LINE IN to LINE OUT
 *
 */
Int16 aic3204_loop_linein( )
{
    Int16 sec, msec;
    Int16 sample, dataLeft, dataRight;
  
    InicializaAudio();
    
    /* Play Loopback for 5 seconds */
    dataLeft = 0;
    dataRight = 0;
    for ( sec = 0 ; sec < 5777 ; sec++ )
    {
        for ( msec = 0 ; msec < 1000 ; msec++ )
        {
            for ( sample = 0 ; sample < 48 ; sample++ )
            {
                EZDSP5502_MCBSP_read(&dataLeft);      // RX right channel
                EZDSP5502_MCBSP_write( dataLeft);      // TX left channel first (FS Low)

                EZDSP5502_MCBSP_read(&dataRight);      // RX left channel
                EZDSP5502_MCBSP_write( dataRight);      // TX right channel next (FS High)
            }
        }
    }
    
    EZDSP5502_MCBSP_close(); // Disable McBSP
    AIC3204_rset( 1, 1 );    // Reset codec
    
    return 0;
}
