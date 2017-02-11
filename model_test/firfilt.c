#include <stdio.h>
#include <stdlib.h>

//#define Int16 short
//#define Int32 int
//#define Uint16 unsigned int

#define Int16 short
#define Int32 int
#define Uint16 int
 
#define N 197

Int16 h[N] = {
       83,    -25,    -25,    -26,    -27,    -28,    -26,    -22,    -16,
       -8,      2,     13,     22,     30,     34,     33,     28,     19,
        6,     -9,    -24,    -38,    -47,    -52,    -50,    -41,    -26,
       -6,     16,     38,     57,     70,     75,     70,     55,     32,
        3,    -29,    -60,    -85,   -101,   -105,    -96,    -73,    -39,
        3,     48,     90,    123,    143,    145,    129,     95,     45,
      -14,    -76,   -133,   -177,   -201,   -201,   -174,   -123,    -51,
       34,    121,    199,    258,    289,    284,    241,    163,     56,
      -69,   -197,   -312,   -397,   -439,   -427,   -357,   -232,    -59,
      143,    355,    549,    699,    778,    765,    644,    408,     62,
     -383,   -902,  -1465,  -2035,  -2572,  -3037,  -3398,  -3625,  29065,
    -3625,  -3398,  -3037,  -2572,  -2035,  -1465,   -902,   -383,     62,
      408,    644,    765,    778,    699,    549,    355,    143,    -59,
     -232,   -357,   -427,   -439,   -397,   -312,   -197,    -69,     56,
      163,    241,    284,    289,    258,    199,    121,     34,    -51,
     -123,   -174,   -201,   -201,   -177,   -133,    -76,    -14,     45,
       95,    129,    145,    143,    123,     90,     48,      3,    -39,
      -73,    -96,   -105,   -101,    -85,    -60,    -29,      3,     32,
       55,     70,     75,     70,     57,     38,     16,     -6,    -26,
      -41,    -50,    -52,    -47,    -38,    -24,     -9,      6,     19,
       28,     33,     34,     30,     22,     13,      2,     -8,    -16,
      -22,    -26,    -28,    -27,    -26,    -25,    -25,     83
};


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
    Int16 dataLeft, dataRight;
    
    Int16 buff[N]; // buffer circular para guardar as amostras
    
    Uint16 i; // indice do buffer indicando a posicao da ultima leitura
    
    Uint16 j; // indice para iteracao no buffer circular
    Uint16 k; // indice para iteracao nos coeficientes

    Int16 posOldest; // posicao no buffer da amostra mais antiga

    int s;
    
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
    
    printf("h = [ ");
    
    //for ( s = 0 ; s < 10 ; s++ )
    while(!feof(fp))
    {
      for ( i = 0 ; i < N ; ++i , !feof(fp) )
      {
        EZDSP5502_MCBSP_read_signal(&dataLeft);      // RX left channel
        //EZDSP5502_MCBSP_read_signal(&dataRight);      // RX right  channel
        
        buff[i] = dataLeft;
        
        k = 0;          
        acc = 0;

        posOldest = (i+1) % N;
        
        for( j = posOldest ; j < N ; ++j , ++k )
        {
          acc += (Int32)h[k] * (Int32)buff[j]; 
        }
        
        for( j = 0 ; j < posOldest ; ++j , ++k )
        {
          acc += (Int32)h[k] * (Int32)buff[j]; 
        }

        acc = acc + 0x00004000; // arredondamento ?

        dataLeft = (Int16) (acc >> 15); // converte para os 16 bits

        printf("%hd ", dataLeft);
      }

    }

    printf("];\n");

    fclose(fp);

    return 0;
}
