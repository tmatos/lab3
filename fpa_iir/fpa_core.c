//////////////////////////////////////////////////////////////////////////////
// * File name: fpa_core.c
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

#include "fpa_iir_elip_8k_tf.h"

extern Int16 AIC3204_rset( Uint16 regnum, Uint16 regval);

/*
 *
 *  Filtrar entrada com filtro IIR (forma direta sos)
 *  Aplica o filtro no sinal em LINE IN para LINE OUT
 *
 */
Int16 filtrar_entrada( )
{	
    Int16 dataLeft;
    Int16 dataRight;
    Uint16 i; // indice
    Uint16 j; // indice
    Uint16 k; // indice
    Int32 acc; // acumulador usado
    Int16 x[N]; // vetor usado para delay line
    Int16 y[N]; // vetor usado para delay line
    
    // set vetor para valor inicial
    for( i = 0 ; i < N ; ++i )
    {
        x[i] = 0;
        y[i] = 0;
    }
  
    InicializaAudio();
    
    for ( ; ; )
    {	
    	for( i = N-1 ; i >= 0 ; --i )
    	{
	        EZDSP5502_MCBSP_read(&dataLeft);    // RX left channel
	    	EZDSP5502_MCBSP_read(&dataRight);   // RX right  channel
	    	
	    	x[i] = dataLeft;
	    	
	    	k = 0;
	    	acc = 0;
	    	
	    	for( j = i ; j < N ; ++j , ++k )
	    	{
	    	    acc += (Int32)x[j] * (Int32)B[k];
	    	    acc -= (Int32)y[j] * (Int32)A[k];
	    	}
	    	
        	for( j = 0 ; j < i ; ++j , ++k )
        	{
        		acc += (Int32)x[j] * (Int32)B[k];
	    	    acc -= (Int32)y[j] * (Int32)A[k];
        	}
        	
        	y[i] = (Int16) acc;
        	
			//acc = acc + 0x00004000; // arredondamento
	    	//dataLeft = (Int16) (acc >> 15); // converte p/ 16 bits
	        
	        EZDSP5502_MCBSP_write( dataLeft );  // TX left channel first (FS Low)
	        EZDSP5502_MCBSP_write( dataLeft );  // TX right channel next (FS High)
    	}
			
    }
    
    EZDSP5502_MCBSP_close(); // Disable McBSP
    AIC3204_rset( 1, 1 );    // Reset codec
    
    return 0;
}
