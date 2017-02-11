#include <stdio.h>

#define Int16 short
#define Uint16 unsigned int
#define Int32 int

#define NSEC 4

Int16 Blen[NSEC] = { 2,3,3,3 };
Int16 B[NSEC][3] = {
  {
    32767, -32768,      0 
  },
  {
    32767, -32768,  32767 
  },
  {
    32767, -32768,  32767 
  },
  {
    32767, -32768,  32767 
  }
};

Int16 Alen[NSEC] = { 2,3,3,3 };
Int16 A[NSEC][3] = {
  {
    32767, -14759,      0 
  },
  {
    32767, -32768,  19418 
  },
  {
    32767, -32768,  28596 
  },
  {
    32767, -32768,  31823 
  }
};

int impulso = 1;

// simular a leitura de impulso
void EZDSP5502_MCBSP_read(Int16 *var)
{
    *var = impulso;

    if(impulso)
    {
        impulso--;
    }

}

int main()
{
    Int16 dataLeft;
    Int16 dataRight;
    Uint16 i; // indice
    Int32 acc; // acumulador usado
    Int32 d[NSEC+1][3]; // vetor usado para delay line

    int k;
    
    // set vetor para valor inicial
    for( i = 0 ; i < (NSEC+1) ; ++i )
    {
        d[i][0] = 0;
        d[i][1] = 0;
        d[i][2] = 0;
    }
  
    //InicializaAudio();

    printf("h = [ ");
    
    for ( k = 0 ; k < 2000 ; k++ )
    {
        EZDSP5502_MCBSP_read(&dataLeft);    // RX left channel
        EZDSP5502_MCBSP_read(&dataRight);   // RX right  channel
        
        d[0][2] = d[0][1];
        d[0][1] = d[0][0];
        d[0][0] = (Int32) dataLeft;
        
        for( i = 0 ; i < NSEC ;  )
        {
            acc = 0;
            acc -= (Int32)A[i][2] * d[i+1][0];
            acc -= (Int32)A[i][1] * d[i+1][1];
            acc -= (Int32)A[i][0] * d[i+1][2];
            acc += (Int32)B[i][2] * d[i  ][0];
            acc += (Int32)B[i][1] * d[i  ][1];
            acc += (Int32)B[i][0] * d[i  ][2];
            
            ++i;
            
            d[i][2] = d[i][1];
            d[i][1] = d[i][0];
            d[i][0] = acc;
        }

        //acc = acc + 0x00004000; // arredondamento
        dataLeft = (Int16) (acc /*>> 15*/); // converte p/ 16 bits

        printf("%d ", dataLeft);

        //printf("%d ", acc);

    }

    printf("]\n");

    return 0;
}
