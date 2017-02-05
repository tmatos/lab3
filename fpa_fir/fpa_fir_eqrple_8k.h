/*
 * Filter Design and Analysis Tool - Generated Filter Coefficients - C Source 
 *  Generated by MATLAB - Signal Processing Toolbox
 */
 
/* General type conversion for MATLAB generated C-code  */
//#include "tmwtypes.h"
/* 
 * Expected path to tmwtypes.h 
 * C:\MATLAB6p5\extern\include\tmwtypes.h 
 */
 
/*
 * Warning - Filter coefficients were truncated to fit specified data type.  
 *   The resulting response may not match generated theoretical response.
 *   Use the Filter Design & Analysis Tool to design accurate fixed-point
 *   filter coefficients.
 */
 
/*
 * Filtro: FIR (equal ripple)
 * Freq. amostragem: 8000 kHz
 * Especif.: Passa altas
 * Pass band freq.: 500 Hz (0.1 dB)
 * Rej. band freq.: 400 Hz (-50 dB)
 */
 
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
