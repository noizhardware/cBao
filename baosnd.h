/* this file has to be included as the first thing */
#ifndef _BAOSND_H_
     #ifdef __cplusplus
     extern "C" {
     #endif
#define _BAOSND_H_
#define _BAOSND_VERSION "2022f21-1654"

/***
# ANSI C sound library
## OS backend is managed by [miniaudio](https://miniaud.io)
All functions are currently branchless
Use -O3 to optimize for branchless

Sample usage:
~~~~
#include "baosnd.h"
     -- global variable and function definitions here
WAVE_BEGIN(MONO, 48000);
     -- audio-callback variable definitions here
WAVE_PRE_SOUND;
     sndOut = sn(432.);
WAVE_END;

int main(){
     SND_INIT;
          printf("== Device Name: %s\n", DEVICE_NAME);
     SND_START;
          printf("~~~ You should hear sound now ~~~\n");
          printf("== Press Enter to quit...");
          getchar();
     SND_STOP;
return 0;}
~~~~

You can also use `DEFAULT_MAIN;` right after `WAVE_END;` if you don't need to do anything in the main loop
Short mode:
~~~~
#include "baosnd.h"
     -- global variable and function definitions here
WAVE_BEGIN(F32, MONO, 48000);
     -- audio-callback variable definitions here
WAVE_PRE_SOUND;
     sndOut = (
          sn(50.)
               *tclip(sigNorm(sn(1.)
                    /sn(2.)), 2.) );
WAVE_END;
DEFAULT_MAIN;
~~~~

Ultrashort mode:
~~~~
#include "baosnd.h"
     snd(sn(432.));
~~~~

Compile with:
* Windows:
     - `gcc -g0 test.c -o test.exe -Wall -Wextra -Wshadow -Wvla -pedantic-errors -I $(includePath) -ansi`
* Linux:
     - `gcc -g0 test.c -o test -ldl -lm -lpthread -Wall -Wextra -Wshadow -Wvla -pedantic-errors -I $(includePath) -ansi`

### System variables:
     - `DEVICE_NAME` : string containing the name of the currently selected audio device
     - `clk` : float, [0..FLT_MAX], constantly rising, +1 at each sample
     - `tt` : float, seconds from the start of the program
     
### Signal Generators: (output in range [-1..1])
     * `sn(freq)` : sinewave
     * `saw(freq, rise)` : rising or falling saw (use constants RISE and FALL)
     * `sq(freq, duty)` : square wave, duty cycle in range [0..1]
     * `noiw()` : white noise

### Utilities:
     * `sigNorm(sig)` : normalize signal `x` from range [-1..1] to [0..1]
     * `normSig(sig)` : reverse of sigNorm,  `x` from range [0..1] to [-1..1]
     * `clip(sig, th)` : threshold(float) - everything outside the range [-th..th] gets clipped to th
     * `tclip(sig, mul)` : soft clipping with tanh, mul premultiplies the signal. multiply for TANH_MAKEUP to compensate gain loss
     * `hwav(sig)` : half-wave rectifier - keeps positive part
     * `hwavn(sig)` : half-wave rectifier - keeps negative part
     * `fwav(sig)` : full-wave rectifier
     * `mix(uint8_t qty, ...)` : mixes a number(qty) of signals, each signal equally present in the mix, output is MAX 0dB if none of the inputs exceeds 0dB
     * `inv(signal)` : returns the inverted signal
     * `tik(interval, length, offset)` : jumps to 1 every "interval" seconds, and stays up for "length" seconds. if "length" is 0, it stays up for a single sample(digital trigger)
     * `tikS(interval, length, offset)` : jumps to 1 every "interval" SAMPLES, and stays up for "length" SAMPLES. if "length" is 0, it stays up for a single sample(digital trigger)
     * `sh(input, trigger)` : sample and hold, triggers whenever trigger>=1.
     * `gate(input, threshold)` : sound is passing thru only when trigger>=threshold
     * `asr(freq, attack, sustain, release)` : looping ASR envelope generator - range [0..1]

 #### TODO:
     * need to adjust these functions so they can maintain state and rely on phase instead of frequency:
          - sq
          - asr
     * exp envelope generator
     * soft gate
     * linear interpolator
     * ttog : trigger to gate
     * flipflop (for triggers)
     * **separate : _baosnd.h_ for OS backend and _baodsp.h_ for functions**
     * range(sig, x, y, z, w) : shift signal range from [x..y] to [z..w]
     * ntof(root) - fton(root)
     * linn(a, b, t) - linearly interpolate a to b in t time
     * coinflip(a, b) : returns a or b randomly
     * bernoulli gate
     * crossfade : equal power
     * phase control
     * dirac
     * triangle wave with slew
     * trapezoid (ASR envelope(loopable))(slewable square - dual control on rise and fall)
     * looping AR - ASR - ADSR - exponential: ear
     * noises (see "Numerical Recipes in C")
     * perlin noise (see https://gpfault.net/posts/perlin-sound.txt.html)
     * sidechain compressor
     * vactrol
     * stereo
     * stereo positioning - pan
     * more than stereo? 4ch
     * sig-in >> split >> rnd jitter->(distortion) >> stereo out
     
     - file output (.wav)(.mp3)
     - midi CC-notes input (http://www.cs.cmu.edu/~rbd/software/midi.htm)
     - OSC input
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

	static uint32_t clk = 0;
	static float tt = 0.f;
		typedef struct timelong_t_{
			uint32_t inte;
			float frac;
		}timelong_t;
		static timelong_t ttLong = {0, 0.f};
	int32_t DEVICE_FORMAT;
	int32_t DEVICE_CHANNELS;
	int32_t DEVICE_SAMPLE_RATE;


/* Formats: */
#define F32 ma_format_f32 /* [-1, 1] */
#define I16 ma_format_s16 /* [-32768, 32767] */
#define I24 ma_format_s24 /* [-8388608, 8388607] */
#define I32 ma_format_s32 /* [-2147483648, 2147483647] */
#define U8 ma_format_u8 /* [0, 255] */

#define MONO 1
#define STEREO 2
#define QUAD 4

#define sndOut *Samples

#define MUTE 0.* /* use to quickly mute a part of a function */

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
#ifndef BAOSND_FORMAT /* sooooooooo the default format is F32 */
     #define WAVE_BEGIN(ch, sr) \
               int32_t DEVICE_FORMAT = F32; \
               int32_t DEVICE_CHANNELS = ch; \
               int32_t DEVICE_SAMPLE_RATE = sr; \
          void data_callback(ma_device* pDevice, void* pOutput, const void* pInput, ma_uint32 frameCount){ \
               float* Samples = pOutput; \
               ma_uint32 SampleIndex
#endif
#ifdef BAOSND_FORMAT
     #if BAOSND_FORMAT == U8
          #define WAVE_BEGIN(ch, sr) \
                    int32_t DEVICE_FORMAT = BAOSND_FORMAT; \
                    int32_t DEVICE_CHANNELS = ch; \
                    int32_t DEVICE_SAMPLE_RATE = sr; \
               void data_callback(ma_device* pDevice, void* pOutput, const void* pInput, ma_uint32 frameCount){ \
                    uint8_t* Samples = pOutput; \
                    ma_uint32 SampleIndex
     #elif BAOSND_FORMAT == F32
          #define WAVE_BEGIN(ch, sr) \
                    int32_t DEVICE_FORMAT = BAOSND_FORMAT; \
                    int32_t DEVICE_CHANNELS = ch; \
                    int32_t DEVICE_SAMPLE_RATE = sr; \
               void data_callback(ma_device* pDevice, void* pOutput, const void* pInput, ma_uint32 frameCount){ \
                    float* Samples = pOutput; \
                    ma_uint32 SampleIndex
     #endif
#endif

#define WAVE_PRE_SOUND \
     for(SampleIndex = 0; SampleIndex < frameCount; SampleIndex++){ \
          clk*=(clk<0xFFFFFFFF); /* continually rising, zeroes out when uint32 is at its max value, to prevent overflow - might cause a discontinuity after ~27 hours continuously running @ 44100Hz */ \
		  ttLong.inte += ((clk % DEVICE_SAMPLE_RATE)==0);\
		  ttLong.frac = ((float)(clk-(ttLong.inte-1)*DEVICE_SAMPLE_RATE))/((float)DEVICE_SAMPLE_RATE);\
		  tt = ((float)(ttLong.inte-1)) + ttLong.frac;
          /*tt = ((float)clk)/DEVICE_SAMPLE_RATE;*/ /* same problem here */
          
#define WAVE_END \
          clk++; \
          Samples++;} \
     (void)pDevice; \
     (void)pInput;} \
     __asm__("") /* just a dummy line to allow a semicolon after the function */

/* for ultracompact code */
#define MAIN \
     WAVE_END; \
     int main(){ \
     SND_INIT;
#define END \
     SND_STOP; \
     return 0;} \
     __asm__("")

#define JUST_PRE_SOUND \
     WAVE_BEGIN(MONO, 48000); \
     WAVE_PRE_SOUND;

#define JUST_POST_SOUND \
     MAIN; \
          printf("== Device Name: %s\n", DEVICE_NAME); \
          printf("== Sample rate: %u Hz\n", DEVICE_SAMPLE_RATE); \
     SND_START; \
          printf("~~~ You should hear sound now ~~~\n"); \
          printf("== used [%u] unique IDs\n", __COUNTER__); \
          printf("== Press Enter to quit..."); \
          getchar(); \
     END; \
     __asm__("")

/* uberfucking compact */
#define snd(x) \
     JUST_PRE_SOUND; \
          sndOut=x; \
     JUST_POST_SOUND; \
     __asm__("")

#define DEFAULT_MAIN \
     int main(){ \
          SND_INIT; \
               printf("== Device Name: %s\n", DEVICE_NAME); \
               printf("== Sample rate: %u Hz\n", DEVICE_SAMPLE_RATE); \
          SND_START; \
               printf("~~~ You should hear sound now ~~~\n"); \
               printf("== used [%u] unique IDs\n", __COUNTER__); \
               printf("== Press Enter to quit...\n"); \
               getchar(); \
          SND_STOP; \
     return 0;} \
     __asm__("")

/*************************************/
/********** static variables *********/
/*************************************/
static float global_cycles[255] = {0.f}; /* to maintain state of phase, unit of measurement: cycles -- max 255 slots, so it can be indexed with an uint8_t */

/*************************************/
/************* UTILITIES *************/
/*************************************/
static __inline__ float sigNorm(float x){
     return ((x/2)+.5);}

static __inline__ float normSig(float x){
     return ((x-.5)*2);}

static __inline__ float clip(float sig, float th){
     return (sig *((sig<=th)&&(sig>=(-th)))) + ((th)*(sig>th)) + ((-th)*(sig<(-th)));}

#define TANH_MAKEUP 1.3130352855 /* multiplier to bring tanh(1) to 1 */
static __inline__ float tclip(float sig, float mul){
     return tanh(sig*mul);}

static __inline__ float hwav(float sig){
     return (sig*(sig>0));}

static __inline__ float hwavn(float sig){
     return (sig*(sig<0));}

static __inline__ float fwav(float sig){
     /*return (sig*(sig>0))-(sig*(sig<0));}*/
     return (float)fabs(sig);}

static __inline__ float mix(uint8_t qty, ...){
     va_list ap;
     uint8_t i;
     float out = 0.f;
     va_start (ap, qty); /* Initialize the argument list. */
     for (i = 0; i < qty; i++){
          out += va_arg(ap, double) / qty;} /* va_arg advances the pointer ap every time it gets called */
     va_end (ap); /* Clean up. */
     return out;}

static __inline__ float inv(float sig){
     return -sig;}

float tik(float interval, float len, float offset){
     return    (len<=0)*(fmod(tt-offset, interval)==0) +
               (len>0)*((fmod(tt-offset, interval)>=0)&&(fmod(tt-offset, interval)<=(len)));}

float tikLong(timelong_t interval){/* kak not working properly in the frac part */
	return ((ttLong.inte % interval.inte)==0) && (ttLong.frac==interval.frac);
}
float tikInt(uint32_t interval){
	return ((ttLong.inte % interval)==0) && (ttLong.frac==0.f);
}

float AAtik_(float interval, float len, float offset, uint8_t unique_id);
#define AAtik(interval, len, offset) tik_(interval, len, offset, __COUNTER__) /* call the tik_() function with a preprocessor-generated unique ID - naaaasty */
float AAtik_(float interval, float len, float offset, uint8_t unique_id){ /* kak bhooooooooooo non funzia */
	float out = (float)(global_cycles[unique_id] == 0.f);
	(void)len;
	(void)offset;
	global_cycles[unique_id] = fmod(global_cycles[unique_id] + ((1.f/interval) / (float)(DEVICE_SAMPLE_RATE)), 1.f);
	return out;
 }
static __inline__ float tikS(float interval, float len, float offset){ /* same, but in SAMPLES */
     return    (len<=0)*(fmod(((float)clk)-offset, interval)==0) +
               (len>0)*((fmod(((float)clk)-offset, interval)>=0)&&(fmod(((float)clk)-offset, interval)<=(len)));}

#define sh(i, t) sh_(i, t, __COUNTER__) /* call the sh_() function with a preprocessor-generated unique ID - naaaasty */
static __inline__ float sh_(float in, float trig, uint8_t sh_state_id){
     global_cycles[sh_state_id] = (trig>=1.)*in + (trig<1.)*global_cycles[sh_state_id];
     return global_cycles[sh_state_id];}

static __inline__ float gate(float in, float th){
     return in*(in>=th);}

/**************************************/
/************* GENERATORS *************/
/**************************************/
#define RISE 1
#define FALL 0
/*static __inline__ float saw(float freq, bool rise){*/
     /* (DEVICE_SAMPLE_RATE/freq) == wavelength, unit of measurement: samples 
     DEVICE_SAMPLE_RATE * wavelength(in seconds) == DEVICE_SAMPLE_RATE * (1/freq) */
     /*return (rise*(fmod(clk, (DEVICE_SAMPLE_RATE/freq))/(DEVICE_SAMPLE_RATE/freq)*2.-1.)) +
     (!rise*((1.-(fmod(clk, (DEVICE_SAMPLE_RATE/freq))/(DEVICE_SAMPLE_RATE/freq)))*2.-1.));
}*/

#define saw(f, r) sawwave(f, r, __COUNTER__) /* call the saw() function with a preprocessor-generated unique ID - naaaasty */
static __inline__ float sawwave(float freq, bool rise, uint8_t unique_id){
     global_cycles[unique_id]++; /* incrementing the number of cycles on each sample. unit of measurement: cycles */
     return (rise*(fmod(global_cycles[unique_id], ((float)DEVICE_SAMPLE_RATE/freq))/((float)DEVICE_SAMPLE_RATE/freq)*2.-1.)) +
     (!rise*((1.-(fmod(global_cycles[unique_id], ((float)DEVICE_SAMPLE_RATE/freq))/((float)DEVICE_SAMPLE_RATE/freq)))*2.-1.));
}

static __inline__ float asr(float freq, float attack, float sustain, float release){
     /*
          cycle length = 1/freq
          A = rising trapezoid, goes to 1 in (attack)seconds and stays 1, resets on each cycle
          B = falling trapezoid, is 1, and goes to 0 in (release)seconds, resets to 1 on each cycle
               B is phase-shifted, it's delayed of (sustain)seconds respect to A
          C = squarewave, ON for (attack+sustain+release)seconds, then 0 to delete the last part, until the next cycle
     */
     return 
     clip((fmod(((float)clk), (DEVICE_SAMPLE_RATE/freq))/(DEVICE_SAMPLE_RATE/freq)) * (1.f/attack)*(1.f/freq), 1.f) /* rising trapezoid */
     * clip(
          (1.-(fmod(
               ((float)clk)
                    + ((DEVICE_SAMPLE_RATE/freq) - (DEVICE_SAMPLE_RATE*attack + DEVICE_SAMPLE_RATE*sustain + DEVICE_SAMPLE_RATE*release))
               , (DEVICE_SAMPLE_RATE/freq))/(DEVICE_SAMPLE_RATE/freq))) * (1.f/release)*(1.f/freq)
          , 1.f) /* falling trapezoid */
     * (float)((fmod(((float)clk), (DEVICE_SAMPLE_RATE/freq))/(DEVICE_SAMPLE_RATE/freq))
          < ((DEVICE_SAMPLE_RATE*(attack+sustain+release))/(DEVICE_SAMPLE_RATE/freq)) ); /* squarewave that stays ON only in the a+s+r phase */
}
     
static __inline__ float sq(float freq, float duty){
     return (float)((fmod(((float)clk), (DEVICE_SAMPLE_RATE/freq))/(DEVICE_SAMPLE_RATE/freq))<duty)*2.f-1.f;}

#define sn(f) sinewave(f, __COUNTER__) /* call the sine() function with a preprocessor-generated unique ID - naaaasty */
static __inline__ float sinewave(float freq, uint8_t unique_id){
     /*   
          phase needs to advance for each sample
          multiplying by MA_TAU is needed to convert cycles>>radians
          freq / DEVICE_SAMPLE_RATE = (cycle/sec)/(samples/sec) = cycle/sample => how many cycles I need to advance every sample
          freq / DEVICE_SAMPLE_RATE * MA_TAU =>  how many RADIANS I need to advance every sample
          (freq / DEVICE_SAMPLE_RATE) = cycles that need to be added for each sample
          e.g. after 10 samples my position on the circumference is going to be (10 * (freq / DEVICE_SAMPLE_RATE)). unit of measurement: cycles
     
          Also, there's a problem with float precision; https://blog.demofox.org/2017/11/21/floating-point-precision/ 
          The global_cycles[unique_id] float value is always rising, it quite early hits the precision limis of floats, the smallest possible increment I can represent with the float gets smaller and smaller as global_cycles[unique_id] gets bigger.
          The solution is to wrap the value of global_cycles[unique_id]
          I'm wrapping to 1. as the unit of measurement here is "cycles", and sin(1cycle)==0
          So global_cycles[unique_id] will always reset when the function==0, and there won't be clicks
     */
     global_cycles[unique_id] = fmod(global_cycles[unique_id] + (freq / (float)(DEVICE_SAMPLE_RATE)), 1.f); /* incrementing the number of cycles on each sample. unit of measurement: cycles */
      /*
          y(phase) = sin(phase + phase_offset)
          phase = 2*PI*f*t
          phase = cycle*2*PI
          y(t) = sin(2 * PI * freq * time + phase_offset) -- TODO: user-exposed phase offset
      */
     return (float)sin((double)(global_cycles[unique_id] * (float)MA_TAU));} /* multiplying cycles by MA_TAU, doing the conversion (cycles)>>(radians) so I can finally plug the value in the sin() function */
     
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

/*
,,code
,,sound
,,synth
,,music
,,livecoding
*/