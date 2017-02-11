#include <stdio.h>
#include <stdlib.h>

#define Int16 double
#define Int32 double
#define Uint16 int

#define N 8

Int16 B[N] = { 0.4843, -3.2835, 9.6445, -15.9059, 15.9059, -9.6445, 3.2835, -0.4843 };

Int16 A[N] = { 0.0000, -5.3666, 12.6514, -16.8995, 13.7713, -6.8246, 1.8970, -0.2262 };

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
    fscanf(fp, "%lf", var);
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

    int i; // indice
    int j; // indice
    int k; // indice

    Int16 x[N]; // vetor usado para delay line
    Int16 y[N]; // vetor usado para delay line

    Int16 posOldest; // posicao no buffer da amostra mais antiga

    Uint16 s;
    
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

        // printf(">>> y[] =");

        // for(k=0 ; k<N ; k++)
        // {
        //   printf(" %f ", y[k]);
        // }

        // printf("\n");
        
        y[i] = (Int16) acc;

        //acc = acc + 0x00004000; // arredondamento
        //dataLeft = (Int16) (acc /*>> 15*/); // converte p/ 16 bits

        //printf("%f ", y[i]);

        printf("%f ", acc);
      }
    }

    printf("];\n");

    //printf("plot(h)\n");

    return 0;
}
