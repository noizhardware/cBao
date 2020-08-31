/* this file has to be included as the first thing */
#ifndef __BAOSND_H__
#define __BAOSND_H__

/* 2020h31-0101 */

/* C90 compliant <3 */

/***
* `sine(freq)` : frequency(float)
* `saw(freq, rise)` : frequency(float), rising or falling saw (use constants RISE and FALL)
* `sq(freq, duty)` : frequency(float), duty cycle[0..1]

 TODO:
     * clip(th)
     * phase control
     * triangle wave with slew
     * trapezoid (slewable square - dual control on rise and fall)
     * looping AR - ASR - ADSR
     * noises
     * s&h
***/

#include <stdbool.h>
#include <math.h>
#include <float.h>

#define MA_NO_DECODING
#define MA_NO_ENCODING
#define MINIAUDIO_IMPLEMENTATION
     #include "miniaudio.h"
     
/***
Formats:
***/
/*a*/
#define F32 ma_format_f32 /* [-1, 1] */
#define I16 ma_format_s16 /* [-32768, 32767] */
#define I24 ma_format_s24 /* [-8388608, 8388607] */
#define I32 ma_format_s32 /* [-2147483648, 2147483647] */
#define U8 ma_format_u8 /* [0, 255] */
/*b*/

#define MONO 1
#define STEREO 2
#define QUAD 4

#define sndOut *Samples

#define SND_INIT \
     ma_device_config deviceConfig; \
     ma_device device; \
      \
     /* audio output device configuration */ \
     deviceConfig = ma_device_config_init(ma_device_type_playback); /* initialize for playback (not capture) */ \
     deviceConfig.playback.format   = DEVICE_FORMAT; \
     deviceConfig.playback.channels = DEVICE_CHANNELS; \
     deviceConfig.sampleRate        = DEVICE_SAMPLE_RATE; \
     deviceConfig.dataCallback      = data_callback; /* name of the callback function */ \
     /*deviceConfig.pUserData         = &sineWave;*/ /* this data is fed to data_callback (Can be accessed from the device object (device.pUserData) inside the callback) */ \
     /*************************************/ \
 \
     /* audio output device initialization */ \
     if(ma_device_init(NULL, &deviceConfig, &device) != MA_SUCCESS){ \
          printf("Failed to open playback device.\n"); \
          return -4;} \
     /**************************************/ \
     
#define SND_START \
     /* this is the actual sound start */ \
     if (ma_device_start(&device) != MA_SUCCESS) { \
          printf("== Failed to start playback device.\n"); \
          ma_device_uninit(&device); \
          return -5;} \
          
#define SND_STOP \
     ma_device_uninit(&device); /* turn off sound */ \

#define DEVICE_NAME \
     device.playback.name


     /*In playback mode copy data to pOutput. In capture mode read data from pInput. In full-duplex mode, both
     pOutput and pInput will be valid and you can move data from pInput into pOutput. Never process more than
     frameCount frames.*/
     /* "Samples" is just a (castless in this case) cast of the "pOutput" float pointer */ 
#define WAVE_BEGIN(format, ch, sr) \
          int DEVICE_FORMAT = format; \
          int DEVICE_CHANNELS = ch; \
          int DEVICE_SAMPLE_RATE = sr; \
          /* \
          #define DEVICE_FORMAT F32 \
          #define DEVICE_CHANNELS     MONO \
          #define DEVICE_SAMPLE_RATE  48000 \
          */     \
     void data_callback(ma_device* pDevice, void* pOutput, const void* pInput, ma_uint32 frameCount){ \
          static float clk = 0; \
          float* Samples = pOutput; \
          ma_uint32 SampleIndex \

#define WAVE_PRE_SOUND \
     for(SampleIndex = 0; SampleIndex < frameCount; SampleIndex++){ \
          clk=clk*(clk<FLT_MAX); /* 0 to 1 continually rising, zeroes out when float is at its max value, to prevent float overflow - might cause a dicontinuity after 227,730,624,142,661,179,698,216,735 years of continuous running. Needs fixing LoL. */
          
#define WAVE_END \
          clk++; \
          Samples++;} \
     (void)pDevice; \
     (void)pInput;} \
     __asm__("nop") /* just a dummy line to allow a semicolon after the function */
     
#define RISE 1
#define FALL 0

#define sigNorm(x) \
     ((x/2)+.5)
     
#define saw(freq, rise) \
     (rise*(fmod(clk, (DEVICE_SAMPLE_RATE/freq))/(DEVICE_SAMPLE_RATE/freq)*2-1)) + \
     (!rise*((1-(fmod(clk, (DEVICE_SAMPLE_RATE/freq))/(DEVICE_SAMPLE_RATE/freq)))*2-1))
#define sine(freq) \
     ((float)sin(clk/DEVICE_SAMPLE_RATE*MA_TAU*freq))
#define sq(freq, duty) \
     (((fmod(clk, (DEVICE_SAMPLE_RATE/freq))/(DEVICE_SAMPLE_RATE/freq))<duty)*2-1)


#endif /* __BAOSND_H__ */