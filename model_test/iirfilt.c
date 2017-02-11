#include <stdio.h>
#include <stdlib.h>

#define Int16 short
#define Int32 int

#define Uint16 int

#define N 8

//Int16 B[N] = { 581, -3940, 11573, -19087,  19087, -11573, 3940, -581 };
//Int16 A[N] = { /*1200*/ 0 , -6440, 15182, -20279, 16526, -8190, 2276, -271 };

double B[N] = { 0.4843, -3.2835, 9.6445, -15.9059, 15.9059, -9.6445, 3.2835, -0.4843 };
double A[N] = { 0.0000, -5.3666, 12.6514, -16.8995, 13.7713, -6.8246, 1.8970, -0.2262 };

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

    double x[N]; // vetor usado para delay line
    double y[N]; // vetor usado para delay line

    Int16 s;
    
    double acc; // acumulador usado
    
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
        
        x[i] = (double)dataLeft;
        
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

        //acc = acc + 0x00004000; // arredondamento
        dataLeft = (Int16) (acc  * 2); // converte p/ 16 bits

        printf("%d ", dataLeft);
      }
    }

    printf("];");

    return 0;
}
