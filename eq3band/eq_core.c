//////////////////////////////////////////////////////////////////////////////
// * File name: eq_core.c
// *                                                                          
// * Description:  Implementacao do equalizador de 3 bandas.
// * 
// * Copyright (C) 2017 Tiago Matos - tmatos.github.io
// *                                                                     
//////////////////////////////////////////////////////////////////////////////

#include "stdio.h"
#include "ezdsp5502.h"
#include "ezdsp5502_mcbsp.h"
#include "csl_mcbsp.h"

#include "util.h"

#include "CONFIG.H"

#ifndef USE_DSP_LIB

extern Int16 AIC3204_rset( Uint16 regnum, Uint16 regval);

#if FS_8K
  #include "filter_coefs/8k/lowpass.h"
  #include "filter_coefs/8k/midpass.h"
  #include "filter_coefs/8k/hipass.h"
#else
  #include "filter_coefs/48k/lowpass.h"
  #include "filter_coefs/48k/midpass.h"
  #include "filter_coefs/48k/hipass.h"
#endif

#define LOW 0
#define MID 1
#define HI 2

double ganho[3] = { 1.0, 1.0, 1.0 };

/*
 *
 *  Aplica o equaliz. no sinal em LINE IN para LINE OUT
 *
 */
Int16 equalizar_entrada( )
{
    Int16 dataLeft, dataRight;
    
    Int16 buff[N]; // buffer circular para guardar as amostras
    
    Uint16 i; // indice do buffer indicando a posicao da ultima leitura
    
    Uint16 j; // indice para iteracao no buffer circular
    Uint16 k; // indice para iteracao nos coeficientes

    Int16 posOldest; // posicao no buffer da amostra mais antiga
    
    Int32 acc[3]; // acumuladores usados para convolucao
  
    InicializaAudio();
    
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
            EZDSP5502_MCBSP_read(&dataLeft);    // RX left channel
        	EZDSP5502_MCBSP_read(&dataRight);   // RX right  channel
        	
        	buff[i] = dataLeft;

            posOldest = (i+1) % N;

	        //== LOW ==============================================================
	        for( k=0, acc[LOW]=0, j=posOldest ; j<N ; ++j, ++k )
	        {
	          acc[LOW] += (Int32)h_low[k] * (Int32)buff[j]; 
	        }
	        for( j=0 ; j<posOldest ; ++j, ++k )
	        {
	          acc[LOW] += (Int32)h_low[k] * (Int32)buff[j]; 
	        }
	        acc[LOW] += 0x00004000;
	        //=====================================================================
	        
	        //== MID ==============================================================
	        for( k=0, acc[MID]=0, j=posOldest ; j<N ; ++j, ++k )
	        {
	          acc[MID] += (Int32)h_mid[k] * (Int32)buff[j]; 
	        }
	        for( j=0 ; j<posOldest ; ++j, ++k )
	        {
	          acc[MID] += (Int32)h_mid[k] * (Int32)buff[j]; 
	        }
	        acc[MID] += 0x00004000;
	        //=====================================================================
	
	        //== HI ===============================================================
	        for( k=0, acc[HI]=0, j=posOldest ; j<N ; ++j, ++k )
	        {
	          acc[HI] += (Int32)h_hi[k] * (Int32)buff[j]; 
	        }
	        for( j=0 ; j<posOldest ; ++j, ++k )
	        {
	          acc[HI] += (Int32)h_hi[k] * (Int32)buff[j]; 
	        }
	        acc[HI] += 0x00004000;
	        //=====================================================================
	        
	        // converte para os 16 bits enquanto aplica os ganhos
	
	        dataLeft = (Int16)( (double)(acc[LOW] >> 15) * ganho[LOW] +
	                            (double)(acc[MID] >> 15) * ganho[MID] +
	                            (double)(acc[HI] >> 15)  * ganho[HI] );
            
            EZDSP5502_MCBSP_write( dataLeft );      // TX left channel first (FS Low)
            EZDSP5502_MCBSP_write( dataLeft );      // TX right channel next (FS High)
    	}
    }
    
    EZDSP5502_MCBSP_close(); // Disable McBSP
    AIC3204_rset( 1, 1 );    // Reset codec
    
    return 0;
}

#endif
