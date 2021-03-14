#ifndef _FONT_STD_H_
#define _FONT_STD_H_

#define FONT_STD_VERSION "2021c14-2328"

/*** TODO

*/

/*** INCLUDES */
     #include "baofont.h"
/* INCLUDES end. */

#ifdef __cplusplus
     extern "C" {
#endif

/*** DEFINES */
/* DEFINES end. */

/*** TYPEDEFS */
/* TYPEDEFS end. */

/*** GLOBALS */
/* letters are rotated 90deg ccw */
font5x8_t font_std={ /* 0-127 standard ascii - 128-255 bao custom chars */
     {    C_XXXXXXXX,/* 000 */
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX},
     {    C_XXXXXXXX,/* 001 */
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX},
     {    C_XXXXXXXX,/* 002 */
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX},
     {    C_XXXXXXXX,/* 003 */
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX},
     {    C_XXXXXXXX,/* 004 */
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX},
     {    C_XXXXXXXX,/* 005 */
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX},
     {    C_XXXXXXXX,/* 006 */
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX},
     {    C_XXXXXXXX,/* 007 */
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX},
     {    C_XXXXXXXX,/* 008 */
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX},
     {    C_XXXXXXXX,/* 009 */
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX},
     {    C_XXXXXXXX,/* 010 */
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX},
     {    C_XXXXXXXX,/* 011 */
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX},
     {    C_XXXXXXXX,/* 012 */
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX},
     {    C_XXXXXXXX,/* 013 */
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX},
     {    C_XXXXXXXX,/* 014 */
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX},
     {    C_XXXXXXXX,/* 015 */
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX},
     {    C_XXXXXXXX,/* 016 */
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX},
     {    C_XXXXXXXX,/* 017 */
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX},
     {    C_XXXXXXXX,/* 018 */
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX},
     {    C_XXXXXXXX,/* 019 */
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX},
     {    C_XXXXXXXX,/* 020 */
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX},
     {    C_XXXXXXXX,/* 021 */
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX},
     {    C_XXXXXXXX,/* 022 */
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX},
     {    C_XXXXXXXX,/* 023 */
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX},
     {    C_XXXXXXXX,/* 024 */
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX},
     {    C_XXXXXXXX,/* 025 */
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX},
     {    C_XXXXXXXX,/* 026 */
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX},
     {    C_XXXXXXXX,/* 027 */
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX},
     {    C_XXXXXXXX,/* 028 */
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX},
     {    C_XXXXXXXX,/* 029 */
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX},
     {    C_XXXXXXXX,/* 030 */
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX},
     {    C_XXXXXXXX,/* 031 */
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX},
     {    C_________,/* 032 space */
          C_________,
          C_________,
          C_________,
          C_________},
     {    C_XXXXXXXX,/* 033 */
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX},
     {    C_XXXXXXXX,/* 034 */
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX},
     {    C_XXXXXXXX,/* 035 */
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX},
     {    C_XXXXXXXX,/* 036 */
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX},
     {    C_XXXXXXXX,/* 037 */
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX},
     {    C_XXXXXXXX,/* 038 */
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX},
     {    C_XXXXXXXX,/* 039 */
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX},
     {    C_X_____X_,/* 040 ( */
          C__X___X__,
          C___XXX___,
          C_________,
          C_________},
     {    C_________,/* 041 ) */
          C_________,
          C___XXX___,
          C__X___X__,
          C_X_____X_},
     {    C_XXXXXXXX,/* 042 */
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX},
     {    C_XXXXXXXX,/* 043 */
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX},
     {    C_XXXXXXXX,/* 044 */
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX},
     {    C_XXXXXXXX,/* 045 */
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX},
     {    C_XXXXXXXX,/* 046 */
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX},
     {    C_XXXXXXXX,/* 047 */
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX},
     {    C_XXXXXXXX,/* 048 */
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX},
     {    C_XXXXXXXX,/* 049 */
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX},
     {    C_XXXXXXXX,/* 050 */
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX},
     {    C_XXXXXXXX,/* 051 */
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX},
     {    C_XXXXXXXX,/* 052 */
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX},
     {    C_XXXXXXXX,/* 053 */
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX},
     {    C_XXXXXXXX,/* 054 */
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX},
     {    C_XXXXXXXX,/* 055 */
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX},
     {    C_XXXXXXXX,/* 056 */
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX},
     {    C_XXXXXXXX,/* 057 */
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX},
     {    C_XXXXXXXX,/* 058 */
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX},
     {    C_XXXXXXXX,/* 059 */
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX},
     {    C_XXXXXXXX,/* 060 */
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX},
     {    C_XXXXXXXX,/* 061 */
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX},
     {    C_XXXXXXXX,/* 062 */
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX},
     {    C_XXXXXXXX,/* 063 */
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX},
     {    C_XXXXXXXX,/* 064 */
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX},
     {    C__XXXXXX_,/* 065 */
          C_X___X___,
          C_X___X___,
          C_X___X___,
          C__XXXXXX_},
     {    C__XX_XX__,/* 066 */
          C_X__X__X_,
          C_X__X__X_,
          C_X__X__X_,
          C_XXXXXXX_},
     {    C_X_____X_,/* 067 */
          C_X_____X_,
          C_X_____X_,
          C_X_____X_,
          C__XXXXX__},
     {    C__XXXXX__,/* 068 */
          C_X_____X_,
          C_X_____X_,
          C_X_____X_,
          C_XXXXXXX_},
     {    C_X_____X_,/* 069 */
          C_X__X__X_,
          C_X__X__X_,
          C_X__X__X_,
          C_XXXXXXX_},
     {    C_X_______,/* 070 */
          C_X__X____,
          C_X__X____,
          C_X__X____,
          C_XXXXXXX_},
     {    C_X___XXX_,/* 071 */
          C_X___X_X_,
          C_X_____X_,
          C_X_____X_,
          C__XXXXX__},
     {    C_XXXXXXX_,/* 072 */
          C____X____,
          C____X____,
          C____X____,
          C_XXXXXXX_},
     {    C_________,/* 073 */
          C_X_____X_,
          C_XXXXXXX_,
          C_X_____X_,
          C_________},
     {    C_X_______,/* 074 */
          C_XXXXXX__,
          C_X_____X_,
          C_______X_,
          C______X__},
     {    C_X_____X_,/* 075 */
          C__X___X__,
          C___X_X___,
          C____X____,
          C_XXXXXXX_},
     {    C_______X_,/* 076 */
          C_______X_,
          C_______X_,
          C_______X_,
          C_XXXXXXX_},
     {    C_XXXXXXX_,/* 077 */
          C__X______,
          C___XX____,
          C__X______,
          C_XXXXXXX_},
     {    C_XXXXXXX_,/* 078 */
          C_____X___,
          C____X____,
          C___X_____,
          C_XXXXXXX_},
     {    C__XXXXX__,/* 079 */
          C_X_____X_,
          C_X_____X_,
          C_X_____X_,
          C__XXXXX__},
     {    C__XX_____,/* 080 */
          C_X__X____,
          C_X__X____,
          C_X__X____,
          C_XXXXXXX_},
     {    C__XXXX_X_,/* 081 */
          C_X____X__,
          C_X___X_X_,
          C_X_____X_,
          C__XXXXX__},
     {    C__XX___X_,/* 082 */
          C_X__X_X__,
          C_X__XX___,
          C_X__X____,
          C_XXXXXXX_},
     {    C__X__XX__,/* 083 */
          C_X__X__X_,
          C_X__X__X_,
          C_X__X__X_,
          C__XX__X__},
     {    C_X_______,/* 084 */
          C_X_______,
          C_XXXXXXX_,
          C_X_______,
          C_X_______},
     {    C_XXXXXX__,/* 085 */
          C_______X_,
          C_______X_,
          C_______X_,
          C_XXXXXX__},
     {    C_XXXXX___,/* 086 */
          C______X__,
          C_______X_,
          C______X__,
          C_XXXXX___},
     {    C_XXXXXX__,/* 087 */
          C_______X_,
          C____XXX__,
          C_______X_,
          C_XXXXXX__},
     {    C_XX___XX_,/* 088 */
          C___X_X___,
          C____X____,
          C___X_X___,
          C_XX___XX_},
     {    C_XXX_____,/* 089 */
          C____X____,
          C_____XXX_,
          C____X____,
          C_XXX_____},
     {    C_XX____X_,/* 090 */
          C_X_X___X_,
          C_X__X__X_,
          C_X___X_X_,
          C_X____XX_},
     {    C_XXXXXXXX,/* 091 */
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX},
     {    C_XXXXXXXX,/* 092 */
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX},
     {    C_XXXXXXXX,/* 093 */
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX},
     {    C_XXXXXXXX,/* 094 */
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX},
     {    C_XXXXXXXX,/* 095 */
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX},
     {    C_XXXXXXXX,/* 096 */
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX},
     {    C____XXXX_,/* 097 a */
          C___X_X_X_,
          C___X_X_X_,
          C___X_X_X_,
          C______X__},
     {    C____XXX__,/* 098 b */
          C___X___X_,
          C___X___X_,
          C____X__X_,
          C_XXXXXXX_},
     {    C______X__,/* 099 c */
          C___X___X_,
          C___X___X_,
          C___X___X_,
          C____XXX__},
     {    C_XXXXXXX_,/* 100 d */
          C____X__X_,
          C___X___X_,
          C___X___X_,
          C____XXX__},
     {    C____XX___,/* 101 e */
          C___X_X_X_,
          C___X_X_X_,
          C___X_X_X_,
          C____XXX__},
     {    C__X______,/* 102 f */
          C_X_______,
          C_X__X____,
          C__XXXXXX_,
          C____X____},
     {    C___XXXX__,/* 103 g */
          C___X_X_X_,
          C___X_X_X_,
          C___X_X_X_,
          C____X____},
     {    C____XXXX_,/* 104 h */
          C___X_____,
          C___X_____,
          C____X____,
          C_XXXXXXX_},
     {    C_________,/* 105 i */
          C_______X_,
          C_X_XXXXX_,
          C____X__X_,
          C_________},
     {    C_________,/* 106 j */
          C_X_XXXX__,
          C___X___X_,
          C_______X_,
          C______X__},
     {    C_________,/* 107 k */
          C___X___X_,
          C____X_X__,
          C_____X___,
          C_XXXXXXX_},
     {    C_________,/* 108 l */
          C_______X_,
          C_XXXXXXX_,
          C_X_____X_,
          C_________},
     {    C____XXXX_,/* 109 m */
          C___X_____,
          C____XXXX_,
          C___X_____,
          C___XXXXX_},
     {    C____XXXX_,/* 110 n */
          C___X_____,
          C___X_____,
          C____X____,
          C___XXXXX_},
     {    C____XXX__,/* 111 o */
          C___X___X_,
          C___X___X_,
          C___X___X_,
          C____XXX__},
     {    C____X____,/* 112 p */
          C___X_X___,
          C___X_X___,
          C___X_X___,
          C___XXXXX_},
     {    C___XXXXX_,/* 113 q */
          C____XX___,
          C___X_X___,
          C___X_X___,
          C____X____},
     {    C____X____,/* 114 r */
          C___X_____,
          C___X_____,
          C____X____,
          C___XXXXX_},
     {    C______X__,/* 115 s */
          C___X_X_X_,
          C___X_X_X_,
          C___X_X_X_,
          C____X__X_},
     {    C______X__,/* 116 t */
          C_______X_,
          C___X___X_,
          C_XXXXXX__,
          C___X_____},
     {    C___XXXXX_,/* 117 u */
          C______X__,
          C_______X_,
          C_______X_,
          C___XXXX__},
     {    C___XXX___,/* 118 v */
          C______X__,
          C_______X_,
          C______X__,
          C___XXX___},
     {    C___XXXX__,/* 119 w */
          C_______X_,
          C_____XX__,
          C_______X_,
          C___XXXX__},
     {    C___X___X_,/* 120 x */
          C____X_X__,
          C_____X___,
          C____X_X__,
          C___X___X_},
     {    C___XXXX__,/* 121 y */
          C_____X_X_,
          C_____X_X_,
          C_____X_X_,
          C___XX____},
     {    C___X___X_,/* 122 z */
          C___XX__X_,
          C___X_X_X_,
          C___X__XX_,
          C___X___X_},
     {    C_XXXXXXXX,/* 123 */
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX},
     {    C_XXXXXXXX,/* 124 */
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX},
     {    C_XXXXXXXX,/* 125 */
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX},
     {    C_XXXXXXXX,/* 126 */
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX},
     {    C_XXXXXXXX,/* 127 */
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX},
     {    C_XXXXXXXX,/* 128 */
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX},
     {    C_XXXXXXXX,/*  */
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX},
     {    C_XXXXXXXX,/*  */
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX},
     {    C_XXXXXXXX,/*  */
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX},
     {    C_XXXXXXXX,/*  */
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX},
     {    C_XXXXXXXX,/*  */
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX},
     {    C_XXXXXXXX,/*  */
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX},
     {    C_XXXXXXXX,/*  */
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX},
     {    C_XXXXXXXX,/*  */
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX},
     {    C_XXXXXXXX,/*  */
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX},
     {    C_XXXXXXXX,/*  */
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX},
     {    C_XXXXXXXX,/*  */
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX},
     {    C_XXXXXXXX,/*  */
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX},
     {    C_XXXXXXXX,/*  */
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX},
     {    C_XXXXXXXX,/*  */
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX},
     {    C_XXXXXXXX,/*  */
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX},
     {    C_XXXXXXXX,/*  */
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX},
     {    C_XXXXXXXX,/*  */
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX},
     {    C_XXXXXXXX,/*  */
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX},
     {    C_XXXXXXXX,/*  */
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX},
     {    C_XXXXXXXX,/*  */
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX},
     {    C_XXXXXXXX,/*  */
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX},
     {    C_XXXXXXXX,/*  */
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX},
     {    C_XXXXXXXX,/*  */
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX},
     {    C_XXXXXXXX,/*  */
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX},
     {    C_XXXXXXXX,/*  */
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX},
     {    C_XXXXXXXX,/*  */
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX},
     {    C_XXXXXXXX,/*  */
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX},
     {    C_XXXXXXXX,/*  */
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX},
     {    C_XXXXXXXX,/*  */
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX},
     {    C_XXXXXXXX,/*  */
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX},
     {    C_XXXXXXXX,/*  */
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX},
     {    C_XXXXXXXX,/*  */
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX},
     {    C_XXXXXXXX,/*  */
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX},
     {    C_XXXXXXXX,/*  */
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX},
     {    C_XXXXXXXX,/*  */
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX},
     {    C_XXXXXXXX,/*  */
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX},
     {    C_XXXXXXXX,/*  */
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX},
     {    C_XXXXXXXX,/*  */
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX},
     {    C_XXXXXXXX,/*  */
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX},
     {    C_XXXXXXXX,/*  */
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX},
     {    C_XXXXXXXX,/*  */
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX},
     {    C_XXXXXXXX,/*  */
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX},
     {    C_XXXXXXXX,/*  */
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX},
     {    C_XXXXXXXX,/*  */
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX},
     {    C_XXXXXXXX,/*  */
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX},
     {    C_XXXXXXXX,/*  */
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX},
     {    C_XXXXXXXX,/*  */
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX},
     {    C_XXXXXXXX,/*  */
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX},
     {    C_XXXXXXXX,/*  */
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX},
     {    C_XXXXXXXX,/*  */
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX},
     {    C_XXXXXXXX,/*  */
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX},
     {    C_XXXXXXXX,/*  */
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX},
     {    C_XXXXXXXX,/*  */
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX},
     {    C_XXXXXXXX,/*  */
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX},
     {    C_XXXXXXXX,/*  */
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX},
     {    C_XXXXXXXX,/*  */
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX},
     {    C_XXXXXXXX,/*  */
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX},
     {    C_XXXXXXXX,/*  */
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX},
     {    C_XXXXXXXX,/*  */
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX},
     {    C_XXXXXXXX,/*  */
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX},
     {    C_XXXXXXXX,/*  */
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX},
     {    C_XXXXXXXX,/*  */
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX},
     {    C_XXXXXXXX,/*  */
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX},
     {    C_XXXXXXXX,/*  */
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX},
     {    C_XXXXXXXX,/*  */
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX},
     {    C_XXXXXXXX,/*  */
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX},
     {    C_XXXXXXXX,/*  */
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX},
     {    C_XXXXXXXX,/*  */
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX},
     {    C_XXXXXXXX,/*  */
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX},
     {    C_XXXXXXXX,/*  */
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX},
     {    C_XXXXXXXX,/*  */
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX},
     {    C_XXXXXXXX,/*  */
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX},
     {    C_XXXXXXXX,/*  */
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX},
     {    C_XXXXXXXX,/*  */
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX},
     {    C_XXXXXXXX,/*  */
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX},
     {    C_XXXXXXXX,/*  */
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX},
     {    C_XXXXXXXX,/*  */
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX},
     {    C_XXXXXXXX,/*  */
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX},
     {    C_XXXXXXXX,/*  */
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX},
     {    C_XXXXXXXX,/*  */
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX},
     {    C_XXXXXXXX,/*  */
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX},
     {    C_XXXXXXXX,/*  */
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX},
     {    C_XXXXXXXX,/*  */
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX},
     {    C_XXXXXXXX,/*  */
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX},
     {    C_XXXXXXXX,/*  */
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX},
     {    C_XXXXXXXX,/*  */
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX},
     {    C_XXXXXXXX,/*  */
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX},
     {    C_XXXXXXXX,/*  */
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX},
     {    C_XXXXXXXX,/*  */
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX},
     {    C_XXXXXXXX,/*  */
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX},
     {    C_XXXXXXXX,/*  */
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX},
     {    C_XXXXXXXX,/*  */
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX},
     {    C_XXXXXXXX,/*  */
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX},
     {    C_XXXXXXXX,/*  */
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX},
     {    C_XXXXXXXX,/*  */
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX},
     {    C_XXXXXXXX,/*  */
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX},
     {    C_XXXXXXXX,/*  */
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX},
     {    C_XXXXXXXX,/*  */
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX},
     {    C_XXXXXXXX,/*  */
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX},
     {    C_XXXXXXXX,/*  */
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX},
     {    C_XXXXXXXX,/*  */
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX},
     {    C_XXXXXXXX,/*  */
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX},
     {    C_XXXXXXXX,/*  */
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX},
     {    C_XXXXXXXX,/*  */
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX},
     {    C_XXXXXXXX,/*  */
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX},
     {    C_XXXXXXXX,/*  */
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX},
     {    C_XXXXXXXX,/*  */
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX},
     {    C_XXXXXXXX,/*  */
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX},
     {    C_XXXXXXXX,/*  */
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX},
     {    C_XXXXXXXX,/*  */
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX},
     {    C_XXXXXXXX,/*  */
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX},
     {    C_XXXXXXXX,/*  */
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX},
     {    C_XXXXXXXX,/*  */
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX},
     {    C_XXXXXXXX,/*  */
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX},
     {    C_XXXXXXXX,/*  */
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX},
     {    C_XXXXXXXX,/*  */
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX},
     {    C_XXXXXXXX,/*  */
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX},
     {    C_XXXXXXXX,/*  */
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX},
     {    C_XXXXXXXX,/*  */
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX},
     {    C_XXXXXXXX,/*  */
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX},
     {    C_XXXXXXXX,/*  */
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX},
     {    C_XXXXXXXX,/*  */
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX},
     {    C_XXXXXXXX,/*  */
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX},
     {    C_XXXXXXXX,/*  */
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX},
     {    C_XXXXXXXX,/*  */
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX},
     {    C_XXXXXXXX,/*  */
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX},
     {    C_XXXXXXXX,/*  */
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX,
          C_XXXXXXXX}
};
     
     
/* GLOBALS end. */

/*** FUNCTION DECLARATIONS */
/* FUNCTION DECLARATIONS end. */

/*** FUNCTION DEFINITIONS */
/* FUNCTION DEFINITIONS end. */

#ifdef __cplusplus
     }
#endif
#endif /* _FONT_STD_H_ */