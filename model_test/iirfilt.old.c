#include <stdio.h>
#include <stdlib.h>

#define Int16 short
#define Int32 int

#define Uint16 int

#define N 8

Int16 B[N] = { 581, -3940, 11573, -19087,  19087, -11573, 3940, -581 };
Int16 A[N] = { /*1200*/ 0 , -6440, 15182, -20279, 16526, -8190, 2276, -271 };

Int16 impulso = 1;

// simular a leitura de impulso
void EZDSP5502_MCBSP_read(Int16 *var)
{
    *var = impulso;

    if(impulso)
    {
        impulso--;
    }
}

FILE *fp;

void EZDSP5502_MCBSP_read_signal(Int16 *var)
{
    fscanf(fp, "%hd", var);
}

void InicializaAudio()
{
    fp = fopen("2sine.dat", "r");

    if( !fp )
    {
        printf("File??????\n");
        exit(1);
    }
}

int main()
{
    Int16 dataLeft;
    Int16 dataRight;

    Int16 i; // indice
    Int16 j; // indice
    Int16 k; // indice

    Int16 x[N]; // vetor usado para delay line
    Int16 y[N]; // vetor usado para delay line

    Int16 posOldest; // posicao no buffer da amostra mais antiga

    Int16 s;
    
    Int32 acc; // acumulador usado
    
    // set vetor para valor inicial
    for( i = 0 ; i < N ; ++i )
    {
        x[i] = 0;
        y[i] = 0;
    }
  
    InicializaAudio();

    printf("h = [ ");

    //for ( s = 0 ; s < 10 ; s++ )
    while( !feof(fp) )
    {
      for( i = 0 ; i < N ; ++i , !feof(fp) )
      {
        EZDSP5502_MCBSP_read_signal(&dataLeft);    // RX left channel
        //EZDSP5502_MCBSP_read_signal(&dataRight);   // RX right  channel
        
        x[i] = dataLeft;
        
        k = 0;
        acc = 0;

        posOldest = (i+1) % N;
        
        for( j = i ; j >= 0 ; --j , ++k )
        {
          acc += (Int32)x[j] * (Int32)B[k];
          acc -= (Int32)y[j] * (Int32)A[k];
        }
        
        for( j = N-1 ; j > i ; --j , ++k )
        {
          acc += (Int32)x[j] * (Int32)B[k];
          acc -= (Int32)y[j] * (Int32)A[k];
        }

        acc = acc + 0x00004000; // arredondamento
        dataLeft = (Int16) (acc >> 15); // converte p/ 16 bits
        
        //y[i] = (Int16) acc;
        y[i] = dataLeft;

        printf("%d ", y[i]);

        //printf("%d ", acc);
      }
    }

    printf("];");

    return 0;
}
