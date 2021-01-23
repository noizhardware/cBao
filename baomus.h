#ifndef _BAOMUS_H_
     #ifdef __cplusplus
     extern "C" {
     #endif
#define _BAOMUS_H_
/* 2021a23-2033 */

#define OCT(freq, oct) (freq*pow(2, oct))

#define TET(x) pow(1.0594630943593, x) /* Twelve Equal Temperament ratio - https://en.wikipedia.org/wiki/Equal_temperament */
const uint8_t maj[7] = {0, 2, 4, 5, 7, 9, 11};
     #define ionian maj
const uint8_t dorian[7] = {0, 2, 3, 5, 7, 9, 10};
const uint8_t phrygian[7] = {0, 1, 3, 5, 7, 8, 10};
const uint8_t lydian[7] = {0, 2, 4, 6, 7, 9, 11};
const uint8_t mixolydian[7] = {0, 2, 4, 5, 7, 9, 10};
const uint8_t min[7] = {0, 2, 3, 5, 7, 8, 10}; /* natural minor */
     #define natmin min
     #define aeolian min
const uint8_t locrian[7] = {0, 1, 3, 5, 6, 8, 10};
const uint8_t superLocrian[7] = {0, 1, 3, 4, 6, 8, 10};
     
const uint8_t wholetone[6] = {0, 2, 4, 6, 8, 1};
const uint8_t blues[6] = {0, 3, 5, 6, 7, 10};

const uint8_t pentaMaj[5] = {0, 2, 4, 7, 9};
const uint8_t pentaMin[5] = {0, 3, 5, 7, 10};
const uint8_t jap[5] = {1, 3, 6, 8, 0}; /* cacca: missing root */

const uint8_t twZone[4] = {4, 8, 9, 10};

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