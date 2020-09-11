/* this file has to be included as the first thing */
#ifndef _BAOSND_H_
     #ifdef __cplusplus
     extern "C" {
     #endif
#define _BAOSND_H_

/* 2020i05-1829 */

/***
# ANSI C sound library
## OS backend is managed by [miniaudio](https://miniaud.io)
All functions are currently branchless
Use -O3 to optimize for branchless

Sample usage:
~~~~
#include "baosnd.h"
WAVE_BEGIN(F32, MONO, 48000);
     --user variables definitions here
WAVE_PRE_SOUND;
     sndOut = --put your signal generating code here
WAVE_END;

int main(){
     SND_INIT;
          --do something before the sound start here
     SND_START;
          --Do something here. Probably your program's main loop.
     SND_STOP;
return 0;}
~~~~

Compile with:
* Windows:
     - `gcc -g0 test.c -o test.exe -Wall -Wextra -Wshadow -Wvla -pedantic-errors -I $(includePath) -ansi`
* Linux>
     - `gcc -g0 test.c -o test -ldl -lm -lpthread -Wall -Wextra -Wshadow -Wvla -pedantic-errors -I $(includePath) -ansi`

### System variables:
     - `DEVICE_NAME` : string containing the name of the currently selected audio device
     - `clk` : float, [0..FLT_MAX], constantly rising, +1 at each sample
     - `tt` : float, seconds from the start of the program
     
### Signal Generators:
     * `sine(freq)` : frequency(float)
     * `saw(freq, rise)` : frequency(float), rising or falling saw (use constants RISE and FALL)
     * `sq(freq, duty)` : frequency(float), duty cycle[0..1]
     * `noiw()` : white noise

### Utilities:
     * `sigNorm(sig)` : normalize signal `x` from range [-1..1] to [0..1]
     * `normSig(sig)` : reverse of sigNorm,  `x` from range [0..1] to [-1..1]
     * `clip(sig, th)` : threshold(float) - everything outside the range [-th..th] gets clipped to th
     * `tclip(sig, mul)` : soft clipping with tanh, mul premultiplies the signal
     * `hwav(sig)` : half-wave rectifier - keeps positive part
     * `hwavn(sig)` : half-wave rectifier - keeps negative part
     * `fwav(sig)` : full-wave rectifier
     * `mix(unsigned char qty, ...)` : mixes a number(qty) of signals, total amplitude will be maintaned at 0dB
     * `inv(signal)` : returns the inverted signal

 #### TODO:
     * stdint all types
     * **separate : _baosnd.h_ for OS backend and _baodsp.h_ for functions**
     * range(sig, x, y, z, w) : shift signal range from [x..y] to [z..w]
     * ntof(root) - fton(root)
     * linn(a, b, t) - linearly interpolate a to b in t time
     * coinflip(a, b) : returns a or b randomly
     * crossfade : equal power
     * phase control
     * triangle wave with slew
     * trapezoid (slewable square - dual control on rise and fall)
     * looping AR - ASR - ADSR - exponential: ear
     * noises (see "Numerical Recipes in C")
     * perlin noise (see https://gpfault.net/posts/perlin-sound.txt.html)
     * s&h
     * sidechain compressor
     * vactrol
     * stereo
     * stereo positioning - pan
     * sig-in >> split >> rnd jitter->(distortion) >> stereo out
     
     - file output (.wav)(.mp3)
***/

#include <stdbool.h>
#include <math.h>
#include <float.h>
#include <stdarg.h>
#include <stdint.h>

#define MA_NO_DECODING
#define MA_NO_ENCODING
#define MINIAUDIO_IMPLEMENTATION
     #include "miniaudio.h"
     
     
     static float clk = 0;
     static float tt = 0;
     int32_t DEVICE_FORMAT;
     int32_t DEVICE_CHANNELS;
     int32_t DEVICE_SAMPLE_RATE;

     
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
          int32_t DEVICE_FORMAT = format; \
          int32_t DEVICE_CHANNELS = ch; \
          int32_t DEVICE_SAMPLE_RATE = sr; \
          /* \
          #define DEVICE_FORMAT F32 \
          #define DEVICE_CHANNELS     MONO \
          #define DEVICE_SAMPLE_RATE  48000 \
          */     \
     void data_callback(ma_device* pDevice, void* pOutput, const void* pInput, ma_uint32 frameCount){ \
          /*static float clk = 0;*/ \
          float* Samples = pOutput; \
          ma_uint32 SampleIndex \

#define WAVE_PRE_SOUND \
     for(SampleIndex = 0; SampleIndex < frameCount; SampleIndex++){ \
          clk=clk*(clk<FLT_MAX); /* 0 to 1 continually rising, zeroes out when float is at its max value, to prevent float overflow - might cause a discontinuity after 227,730,624,142,661,179,698,216,735 years of continuous running at 48kHz. Needs fixing LoL. */ \
          tt = clk/DEVICE_SAMPLE_RATE; /* same problem here LoL */
          
#define WAVE_END \
          clk++; \
          Samples++;} \
     (void)pDevice; \
     (void)pInput;} \
     __asm__("nop") /* just a dummy line to allow a semicolon after the function */
     
#define RISE 1
#define FALL 0

/* UTILITIES */
static __inline__ float sigNorm(float x){
     return ((x/2)+.5);}

static __inline__ float normSig(float x){
     return ((x-.5)*2);}

static __inline__ float clip(float sig, float th){
     return (sig *((sig<=th)&&(sig>=(-th)))) + ((th)*(sig>th)) + ((-th)*(sig<(-th)));}

static __inline__ float tclip(float sig, float mul){
     return tanh(sig*mul);}

static __inline__ float hwav(float sig){
     return (sig*(sig>0));}

static __inline__ float hwavn(float sig){
     return (sig*(sig<0));}

static __inline__ float fwav(float sig){
     return (sig*(sig>0))-(sig*(sig<0));}

static __inline__ float mix(unsigned char qty, ...){
     va_list ap;
     unsigned char i;
     float out = 0;
     va_start (ap, qty); /* Initialize the argument list. */
     for (i = 0; i < qty; i++){
          out += va_arg(ap, double) / qty;} /* va_arg advances the pointer ap every tine it gets called */
     va_end (ap); /* Clean up. */
     return out;}

static __inline__ float inv(float sig){
     return -sig;}

/* GENERATORS */               
static __inline__ float saw(float freq, bool rise){
     return (rise*(fmod(clk, (DEVICE_SAMPLE_RATE/freq))/(DEVICE_SAMPLE_RATE/freq)*2-1)) +
     (!rise*((1-(fmod(clk, (DEVICE_SAMPLE_RATE/freq))/(DEVICE_SAMPLE_RATE/freq)))*2-1));} 
     
static __inline__ float sq(float freq, float duty){
     return ((fmod(clk, (DEVICE_SAMPLE_RATE/freq))/(DEVICE_SAMPLE_RATE/freq))<duty)*2-1;}
     
static __inline__ float sine(float freq){
     return (float)sin(clk/DEVICE_SAMPLE_RATE*MA_TAU*freq);}
     
static __inline__ float noiw(){ /* white noise - based on https://github.com/velipso/sndfilter/blob/master/src/reverb.c*/
	static uint32_t seed = 123; /* doesn't matter */
	static uint32_t i = 456; /* doesn't matter */
	uint32_t m = 0x5bd1e995;
	uint32_t k = i++ * m;
     uint32_t R;
     union { uint32_t i; float f; } u;
     
	seed = (k ^ (k >> 24) ^ (seed * m)) * m;
	R = (seed ^ (seed >> 13)) & 0x007FFFFF; /* get 23 random bits */
	u.i = 0x3F800000 | R;
	return (u.f - 1.5) *2;}


     #ifdef __cplusplus
     }
     #endif
#endif /* _BAOSND_H_ */