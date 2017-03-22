//////////////////////////////////////////////////////////////////////////////
// * File name: fpa_core_dsplib.c
// *                                                                          
// * Description:  Implementacao de filtro passa-altas.
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

#include "fpa_fir_eqrple_8k.h"

extern Int16 AIC3204_rset( Uint16 regnum, Uint16 regval);

/*
 *
 *  Filtrar entrada com filtro FIR
 *  Aplica o filtro no sinal em LINE IN para LINE OUT
 *
 */
Int16 filtrar_entrada( )
{
    Int16 dataLeft, dataRight;
    
    Int16 buff[N]; // buffer circular para guardar as amostras
    
    Uint16 i; // indice do buffer indicando a posicao da ultima leitura
    
    Uint16 j; // indice para iteracao no buffer circular
    Uint16 k; // indice para iteracao nos coeficientes
    
    Int32 acc; // acumulador usado para a convolucao
  
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
    	}
    }
    
    EZDSP5502_MCBSP_close(); // Disable McBSP
    AIC3204_rset( 1, 1 );    // Reset codec
    
    return 0;
}

#endif
