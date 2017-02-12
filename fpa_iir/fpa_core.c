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

#include "fpa_iir_elip_8k_tf_float.h"

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
    
    Int16 i; // indice
    Int16 j; // indice
    Int16 k; // indice
    
    double x[N]; // vetor usado para delay line
    double y[N]; // vetor usado para delay line
    
    Int32 acc; // acumulador usado
    
    // set vetor para valor inicial
    for( i = 0 ; i < N ; ++i )
    {
        x[i] = 0;
        y[i] = 0;
    }
  
    InicializaAudio();
    
    for ( ; ; )
    {	
    	for( i = 0 ; i < N ; ++i )
    	{
	        EZDSP5502_MCBSP_read(&dataLeft);    // RX left channel
	    	EZDSP5502_MCBSP_read(&dataRight);   // RX right  channel
	    	
	    	x[i] = (double) dataLeft;
	    	
	    	k = 0;
	    	acc = 0;
        
		    for( j = i ; j >= 0 ; --j , ++k )
		    {
		      acc += x[j] * B[k];
		      acc -= y[j] * A[k];
		    }
		    
		    for( j = N-1 ; j > i ; --j , ++k )
		    {
		      acc += x[j] * B[k];
		      acc -= y[j] * A[k];
		    }
		
		    y[i] = acc;
        	
        	//acc += 0x400;                  // Rounding
    		//y[i] = (Int16)(acc >> 10);     // Place the Q15 result into y[0]
        	
			//acc = acc + 0x00004000; // arredondamento
	    	//dataLeft = (Int16) (acc >> 15); // converte p/ 16 bits
	    	
        	dataLeft = (Int16) (acc/* * 2*/); // converte p/ 16 bits
	        
	        EZDSP5502_MCBSP_write( dataLeft );  // TX left channel first (FS Low)
	        EZDSP5502_MCBSP_write( dataLeft );  // TX right channel next (FS High)
    	}
    }
    
    EZDSP5502_MCBSP_close(); // Disable McBSP
    AIC3204_rset( 1, 1 );    // Reset codec
    
    return 0;
}
