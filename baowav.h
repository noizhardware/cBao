#ifndef _BAOWAV_H_
#define _BAOWAV_H_

#define BAOWAV_VERSION "2021g09-2038"

/*** TODO

*/

/*** INCLUDES */
/* INCLUDES end. */

#ifdef __cplusplus
     extern "C" {
#endif

/*** DEFINES */
     #define SUBCHUNK1SIZE   (16)
     #define AUDIO_FORMAT    (1) /*For PCM*/
/* DEFINES end. */

/*** TYPEDEFS */
     /*
     The header of a wav file Based on:
     https://ccrma.stanford.edu/courses/422/projects/WaveFormat/
     */
     typedef struct wavfile_header_s
     {
         char    ChunkID[4];     /*  4   */
         int32_t ChunkSize;      /*  4   */
         char    Format[4];      /*  4   */

         char    Subchunk1ID[4]; /*  4   */
         int32_t Subchunk1Size;  /*  4   */
         int16_t AudioFormat;    /*  2   */
         int16_t NumChannels;    /*  2   */
         int32_t SampleRate;     /*  4   */
         int32_t ByteRate;       /*  4   */
         int16_t BlockAlign;     /*  2   */
         int16_t BitsPerSample;  /*  2   */

         char    Subchunk2ID[4];
         int32_t Subchunk2Size;
     } wavfile_header_t;
/* TYPEDEFS end. */

/*** GLOBALS */
/* GLOBALS end. */

/*** FUNCTION DECLARATIONS */
     int write_wav_header(
          FILE*   file_p,
          int32_t SampleRate,
          int32_t FrameCount, /* in mono, 8bit, un frame è 1byte, se era stereo 8bit, erano 2bytes, ecc... */
          uint8_t numChans, /* number of channels (1=MONO, 2=STEREO) */
          uint8_t bits /* bits per sample */
     );
/* FUNCTION DECLARATIONS end. */

/*** FUNCTION DEFINITIONS */
/*Return 0 on success and -1 on failure*/
     int write_wav_header(
          FILE*   file_p,
          int32_t SampleRate,
          int32_t FrameCount, /* in mono, 8bit, un frame è 1byte, se era stereo 8bit, erano 2bytes, ecc... */
          uint8_t numChans, /* number of channels (1=MONO, 2=STEREO) */
          uint8_t bits /* bits per sample */
     ){
         int ret;

         wavfile_header_t wav_header;
         int32_t subchunk2_size;
         int32_t chunk_size;

         size_t write_count;
         
         subchunk2_size  = FrameCount * numChans * bits/8;
         chunk_size      = 4 + (8 + SUBCHUNK1SIZE) + (8 + subchunk2_size);

         wav_header.ChunkID[0] = 'R';
         wav_header.ChunkID[1] = 'I';
         wav_header.ChunkID[2] = 'F';
         wav_header.ChunkID[3] = 'F';

         wav_header.ChunkSize = chunk_size;

         wav_header.Format[0] = 'W';
         wav_header.Format[1] = 'A';
         wav_header.Format[2] = 'V';
         wav_header.Format[3] = 'E';

         wav_header.Subchunk1ID[0] = 'f';
         wav_header.Subchunk1ID[1] = 'm';
         wav_header.Subchunk1ID[2] = 't';
         wav_header.Subchunk1ID[3] = ' ';

         wav_header.Subchunk1Size = SUBCHUNK1SIZE;
         wav_header.AudioFormat = AUDIO_FORMAT;
         wav_header.NumChannels = numChans;
         wav_header.SampleRate = SampleRate;
         wav_header.ByteRate = (SampleRate * numChans * bits/8);
         wav_header.BlockAlign = (numChans * bits/8);
         wav_header.BitsPerSample = bits;

         wav_header.Subchunk2ID[0] = 'd';
         wav_header.Subchunk2ID[1] = 'a';
         wav_header.Subchunk2ID[2] = 't';
         wav_header.Subchunk2ID[3] = 'a';
         wav_header.Subchunk2Size = subchunk2_size;

         write_count = fwrite(   &wav_header, 
                                 sizeof(wavfile_header_t), 1,
                                 file_p);

         ret = (1 != write_count)? -1 : 0;

         return ret;
     }
/* FUNCTION DEFINITIONS end. */

#ifdef __cplusplus
     }
#endif
#endif /* _BAOWAV_H_ */