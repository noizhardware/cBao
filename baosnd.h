/* this file has to be included as the first thing */
#ifndef __BAOSND_H__
#define __BAOSND_H__

/* 2020h29-1211 */

/* C90 compliant <3 */

/* TODO:

*/


#define MA_NO_DECODING
#define MA_NO_ENCODING
#define MINIAUDIO_IMPLEMENTATION
     #include "miniaudio.h"

#define F32 ma_format_f32 /* [-1, 1] */
#define I16 ma_format_s16 /* [-32768, 32767] */
#define I24 ma_format_s24 /* [-8388608, 8388607] */
#define I32 ma_format_s32 /* [-2147483648, 2147483647] */
#define U8 ma_format_u8 /* [0, 255] */

#define MONO 1
#define STEREO 2

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
     

#endif /* __BAOSND_H__ */