#ifndef _BAOMUS_H_
     #ifdef __cplusplus
     extern "C" {
     #endif
#define _BAOMUS_H_
/* 2021b15-1445 */

/* TODO:
     - chords
     - todo: make scales with a list of semitone increments, loopable
       - eg: maj_all[MAX_SCALE_SIZE] = {2, 2, 1, 2, 2, 2, 1};
     - non-logarithmic TET?
*/

#include <stdint.h>
#include <math.h>

#define MAX_SCALE_SIZE 21 /* 3x a major scale in western tuning >> max 32 intervals per octave */

typedef struct scale_t_{
     const uint8_t size;
     const uint8_t scale[MAX_SCALE_SIZE];
} scale_t;

typedef struct tuningSystem_t_{
     float rootFreq; /* root frequency */
     float octMult; /* octave multiplier: you must multiply freq by this to obtain the same note in the next octave */
     uint8_t intervals; /* how many intervals an octave is divided in */
} tuningSystem_t;

void tuningInit(tuningSystem_t* ton, float rootFreq, float octMult, uint8_t intervals){
          ton->rootFreq = rootFreq;
          ton->octMult = octMult;
          ton->intervals = intervals;
}

typedef uint8_t interval_t;
typedef int8_t octave_t;

interval_t maj_all[MAX_SCALE_SIZE] = {0, 2, 4, 5, 7, 9, 11, 12, 14, 16, 17, 19, 21, 23, 24, 26, 28, 29, 31, 32, 34};

scale_t maj = {7, {0, 2, 4, 5, 7, 9, 11}};
     #define ionian maj
scale_t dorian = {7, {0, 2, 3, 5, 7, 9, 10}};
scale_t phrygian = {7, {0, 1, 3, 5, 7, 8, 10}};
scale_t lydian = {7, {0, 2, 4, 6, 7, 9, 11}};
scale_t mixolydian = {7, {0, 2, 4, 5, 7, 9, 10}};
scale_t min = {7, {0, 2, 3, 5, 7, 8, 10}}; /* natural minor */
     #define natmin min
     #define aeolian min
scale_t locrian = {7, {0, 1, 3, 5, 6, 8, 10}};
scale_t superLocrian = {7, {0, 1, 3, 4, 6, 8, 10}};
     
scale_t wholetone = {6, {0, 2, 4, 6, 8, 1}};
scale_t blues = {6, {0, 3, 5, 6, 7, 10}};

scale_t pentaMaj = {5, {0, 2, 4, 7, 9}};
scale_t pentaMin = {5, {0, 3, 5, 7, 10}};
scale_t jap = {5, {1, 3, 6, 8, 0}}; /* cacca: missing root */

scale_t twZone = {4, {4, 8, 9, 10}};

scale_t lydian_tet19 = {11,{0, 2, 4, 6, 7, 9, 11, 12, 14, 16, 18}};

scale_t maj_tet7 = {4,{0, 2, 4, 6}};

scale_t maj_tet9 = {5, {0, 2, 4, 5, 7}};

/* usage: oct(frequencyTotranspose, octavesbywhichitsgonabetransposed) */
static __inline__ float oct(float freq, octave_t oct){ /* octaves happen on Doubling the frequency */
     return (freq*pow(2., oct));}
static __inline__ float octT(float freq, octave_t oct){ /* octaves happen on Tripling the frequency */
     return (freq*pow(3., oct));}
static __inline__ float octX(float freq, octave_t oct, float octMult){ /* octaves happen on (* octMult) the frequency */
     return (freq*pow(octMult, oct));}

/* Twelve Equal Temperament ratio - https://en.wikipedia.org/wiki/Equal_temperament */
/* usage: rootFreq * tet(interval) */
static __inline__ float tet(uint8_t interval){
     return pow(1.0594630943592953, interval);} /* twelfth root of 2 - https://www.mathwarehouse.com/arithmetic/principal-nth-root-calculator.php */
     /* it's the root of "2" becouse octaves repeat od doubling(* 2) the frequency */
static __inline__ float tet19(uint8_t interval){
     return pow(1.0371550444461919, interval);} /* 19th root of 2 */
static __inline__ float tet7(uint8_t interval){
     return pow(1.1040895136738123, interval);} /* 7th root of 2 */

static __inline__ float tetT12(uint8_t interval){ /* Three 12 - octaves are on (* 3) and divided in 12 intervals */
     return pow(1.0958726911352443, interval);} /* 12th root of 3 */
static __inline__ float tetT7(uint8_t interval){ /* Three 7 - octaves are on (* 3) and divided in 7 intervals */
     return pow(1.169930812758687, interval);} /* 7th root of 3 */

static __inline__ float tetOH12(uint8_t interval){ /* One and Half 12 - octaves are on (* 1.5) and divided in 12 intervals */
     return pow(1.0343660831319166, interval);} /* 12th root of 1.5 */

static __inline__ float root(uint8_t n, float input){ /* nth root of input */
  return pow(input, 1./n);}

static __inline__ uint8_t majScaleSize(uint8_t intervals){ /* size of a major scale, depending on how many intervals I have in my equal temperament system */
    return floor(0.5833333333333333333333*intervals);} /* 7/12 */

static __inline__ float tetX(uint8_t interval, float octMult, uint8_t intervals){ /* octaves are on (* octMult) and divided in "intervals" intervals */
     return pow(root(intervals, octMult), interval);} /* intervals'th root of octMult */
     
static __inline__ uint8_t wrapz(uint8_t input, uint8_t wrapper){ /* modulus, including 0 in the loop */
    return input%(wrapper+1);}
static __inline__ uint8_t wrapzDone(uint8_t input, uint8_t wrapper){ /* how many times the wrapz did wrap */
     return (input - wrapz(input, wrapper))/(wrapper+1);}

static __inline__ float freqMaker(tuningSystem_t tun, octave_t octShift, interval_t scale[MAX_SCALE_SIZE], interval_t interval_in){
     return octX(
          octX(tun.rootFreq, octShift, tun.octMult) *
               tetX(
                    scale[wrapz(interval_in, majScaleSize(tun.intervals))]
                    , tun.octMult
                    , tun.intervals)
          , wrapzDone(interval_in, majScaleSize(tun.intervals))
          , tun.octMult
     );
}

#ifdef __cplusplus
}
#endif
#endif /* _BAOMUS_H_ */

/*
,,code
,,sound
,,synth
,,music
,,livecoding
*/