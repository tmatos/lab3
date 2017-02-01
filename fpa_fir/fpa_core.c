//////////////////////////////////////////////////////////////////////////////
// * File name: fpa_core.c
// *                                                                          
// * Description:  Implementacao de filtro passa-altas.
// *                                                                          
// * Copyright (C) 2011 Texas Instruments Incorporated - http://www.ti.com/ 
// * Copyright (C) 2011 Spectrum Digital, Incorporated
// * Copyright (C) 2017 Tiago Matos - tmatos.github.io
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

#include "fpa_fir_eqrple_11k.h"

extern Int16 AIC3204_rset( Uint16 regnum, Uint16 regval);

/*
 *
 *  Filtrar entrada com filtro FIR
 *      Aplica o filtro no sinal em LINE IN para LINE OUT
 *
 */
Int16 filtrar_entrada( )
{
    //Int16 sec, msec;
    //Int16 sample;
    Int16 dataLeft, dataRight;
    
    Int16 buff[N]; // buffer circular para guardar as amostras
    
    Uint16 i; // indice do buffer indicando a posicao da ultima leitura
    
    Uint16 j; // indice para iteracao no buffer circular
    Uint16 k; // indice para iteracao nos coeficientes
    
    Int32 acc; // acumulador usado para a convolucao
  
    /* ---------------------------------------------------------------- *
     *  Configure AIC3204                                               *
     * ---------------------------------------------------------------- */
    AIC3204_rset( 0, 0 );      // Select page 0
    AIC3204_rset( 1, 1 );      // Reset codec
    AIC3204_rset( 0, 1 );      // Select page 1
    AIC3204_rset( 1, 8 );      // Disable crude AVDD generation from DVDD
    AIC3204_rset( 2, 1 );      // Enable Analog Blocks, use LDO power
    AIC3204_rset( 0, 0 );
    
    /* PLL and Clocks config and Power Up  */
    AIC3204_rset( 27, 0x0d );  // BCLK and WCLK are set as o/p; AIC3204(Master)
    AIC3204_rset( 28, 0x00 );  // Data ofset = 0
    AIC3204_rset( 4, 3 );      // PLL setting: PLLCLK <- MCLK, CODEC_CLKIN <-PLL CLK
    AIC3204_rset( 6, 7 );      // PLL setting: J=7
    AIC3204_rset( 7, 0x06 );   // PLL setting: HI_BYTE(D=1680)
    AIC3204_rset( 8, 0x90 );   // PLL setting: LO_BYTE(D=1680)
    AIC3204_rset( 30, 0x9C );  // For 32 bit clocks per frame in Master mode ONLY
                               // BCLK=DAC_CLK/N =(12288000/8) = 1.536MHz = 32*fs
    AIC3204_rset( 5, 0x91 );   // PLL setting: Power up PLL, P=1 and R=1
    AIC3204_rset( 13, 0 );     // Hi_Byte(DOSR) for DOSR = 128 decimal or 0x0080 DAC oversamppling
    AIC3204_rset( 14, 0x80 );  // Lo_Byte(DOSR) for DOSR = 128 decimal or 0x0080
    AIC3204_rset( 20, 0x80 );  // AOSR for AOSR = 128 decimal or 0x0080 for decimation filters 1 to 6
    AIC3204_rset( 11, 0x82 );  // Power up NDAC and set NDAC value to 2
    AIC3204_rset( 12, 0x87 );  // Power up MDAC and set MDAC value to 7
    AIC3204_rset( 18, 0x87 );  // Power up NADC and set NADC value to 7
    AIC3204_rset( 19, 0x82 );  // Power up MADC and set MADC value to 2

    /* DAC ROUTING and Power Up */
    AIC3204_rset( 0, 1 );      // Select page 1
    AIC3204_rset( 0x0c, 8 );   // LDAC AFIR routed to HPL
    AIC3204_rset( 0x0d, 8 );   // RDAC AFIR routed to HPR
    AIC3204_rset( 0, 0 );      // Select page 0
    AIC3204_rset( 64, 2 );     // Left vol=right vol
    AIC3204_rset( 65, 0);      // Left DAC gain to 0dB VOL; Right tracks Left
    AIC3204_rset( 63, 0xd4 );  // Power up left,right data paths and set channel
    AIC3204_rset( 0, 1 );      // Select page 1
    AIC3204_rset( 9, 0x30 );   // Power up HPL,HPR
    AIC3204_rset( 0x10, 0x00 );// Unmute HPL , 0dB gain
    AIC3204_rset( 0x11, 0x00 );// Unmute HPR , 0dB gain
    AIC3204_rset( 0, 0 );      // Select page 0
    EZDSP5502_waitusec( 1000000 ); // wait
        
    /* ADC ROUTING and Power Up */
    AIC3204_rset( 0, 1 );      // Select page 1
    AIC3204_rset( 0x34, 0x30 );// STEREO 1 Jack
                               // IN2_L to LADC_P through 40 kohm
    AIC3204_rset( 0x37, 0x30 );// IN2_R to RADC_P through 40 kohmm
    AIC3204_rset( 0x36, 3 );   // CM_1 (common mode) to LADC_M through 40 kohm
    AIC3204_rset( 0x39, 0xc0 );// CM_1 (common mode) to RADC_M through 40 kohm
    AIC3204_rset( 0x3b, 0 );   // MIC_PGA_L unmute
    AIC3204_rset( 0x3c, 0 );   // MIC_PGA_R unmute
    AIC3204_rset( 0, 0 );      // Select page 0
    AIC3204_rset( 0x51, 0xc0 );// Powerup Left and Right ADC
    AIC3204_rset( 0x52, 0 );   // Unmute Left and Right ADC
    AIC3204_rset( 0, 0 );    
    EZDSP5502_waitusec( 200 ); // Wait

    /* Initialize McBSP */
    EZDSP5502_MCBSP_init( );
    
    // set bufffer para valor inicial
    for( i = 0 ; i < N ; ++i )
    {
    	buff[i] = 0;
    }
    
    dataLeft = 0;
    dataRight = 0;
    
    i = 0;
    k = 0;
    
    for ( ; ; )
    {
    	for ( i = 0 ; i < N ; ++i )
    	{
            EZDSP5502_MCBSP_read(&dataLeft);      // RX left channel
        	EZDSP5502_MCBSP_read(&dataRight);      // RX right  channel
        	
        	buff[i] = dataLeft;
        	
        	k = 0;        	
        	acc = 0;
        	
        	for( j = i ; j < N ; ++j , ++k )
        	{
        		acc += (Int32)h[k] * (Int32)buff[j]; 
        	}
        	
        	for( j = 0 ; j < i ; ++j , ++k )
        	{
        		acc += (Int32)h[k] * (Int32)buff[j];
        	}

            acc = acc + 0x00004000; // arredondamento ?

            dataLeft = (Int16) (acc >> 15); // converte para os 16 bits
            
            EZDSP5502_MCBSP_write( dataLeft );      // TX left channel first (FS Low)
            EZDSP5502_MCBSP_write( dataLeft );      // TX right channel next (FS High)
            
            //EZDSP5502_MCBSP_write( dataLeft);      // TX left channel first (FS Low)
            //EZDSP5502_MCBSP_write( dataRight);      // TX right channel next (FS High)
    	}
    }
    
    EZDSP5502_MCBSP_close(); // Disable McBSP
    AIC3204_rset( 1, 1 );    // Reset codec
    
    return 0;
}
