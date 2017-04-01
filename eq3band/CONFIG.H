
/*
 * Configurar algumas as opcoes do filtro
 * em tempo de compilacao
 */

#ifndef CONFIG_H_

#define CONFIG_H_


//#define USE_DSP_LIB

//#define FS_8K
#define FS_48K

#if FS_8K
  #define SAMPLE_RATE 8000
#else
  #define SAMPLE_RATE 48000
#endif


#endif /*CONFIG_H_*/
