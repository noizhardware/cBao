#ifndef _BAOFONT_H_
#define _BAOFONT_H_

#define BAOFONT_VERSION "2021c14-2328"

/*** TODO

*/

/*** INCLUDES */
/* INCLUDES end. */

#ifdef __cplusplus
     extern "C" {
#endif

/*** DEFINES */
#define C_________ 0
#define C________X 1
#define C_______X_ 2
#define C_______XX 3
#define C______X__ 4
#define C______X_X 5
#define C______XX_ 6
#define C______XXX 7
#define C_____X___ 8
#define C_____X__X 9
#define C_____X_X_ 10
#define C_____X_XX 11
#define C_____XX__ 12
#define C_____XX_X 13
#define C_____XXX_ 14
#define C_____XXXX 15
#define C____X____ 16
#define C____X___X 17
#define C____X__X_ 18
#define C____X__XX 19
#define C____X_X__ 20
#define C____X_X_X 21
#define C____X_XX_ 22
#define C____X_XXX 23
#define C____XX___ 24
#define C____XX__X 25
#define C____XX_X_ 26
#define C____XX_XX 27
#define C____XXX__ 28
#define C____XXX_X 29
#define C____XXXX_ 30
#define C____XXXXX 31
#define C___X_____ 32
#define C___X____X 33
#define C___X___X_ 34
#define C___X___XX 35
#define C___X__X__ 36
#define C___X__X_X 37
#define C___X__XX_ 38
#define C___X__XXX 39
#define C___X_X___ 40
#define C___X_X__X 41
#define C___X_X_X_ 42
#define C___X_X_XX 43
#define C___X_XX__ 44
#define C___X_XX_X 45
#define C___X_XXX_ 46
#define C___X_XXXX 47
#define C___XX____ 48
#define C___XX___X 49
#define C___XX__X_ 50
#define C___XX__XX 51
#define C___XX_X__ 52
#define C___XX_X_X 53
#define C___XX_XX_ 54
#define C___XX_XXX 55
#define C___XXX___ 56
#define C___XXX__X 57
#define C___XXX_X_ 58
#define C___XXX_XX 59
#define C___XXXX__ 60
#define C___XXXX_X 61
#define C___XXXXX_ 62
#define C___XXXXXX 63
#define C__X______ 64
#define C__X_____X 65
#define C__X____X_ 66
#define C__X____XX 67
#define C__X___X__ 68
#define C__X___X_X 69
#define C__X___XX_ 70
#define C__X___XXX 71
#define C__X__X___ 72
#define C__X__X__X 73
#define C__X__X_X_ 74
#define C__X__X_XX 75
#define C__X__XX__ 76
#define C__X__XX_X 77
#define C__X__XXX_ 78
#define C__X__XXXX 79
#define C__X_X____ 80
#define C__X_X___X 81
#define C__X_X__X_ 82
#define C__X_X__XX 83
#define C__X_X_X__ 84
#define C__X_X_X_X 85
#define C__X_X_XX_ 86
#define C__X_X_XXX 87
#define C__X_XX___ 88
#define C__X_XX__X 89
#define C__X_XX_X_ 90
#define C__X_XX_XX 91
#define C__X_XXX__ 92
#define C__X_XXX_X 93
#define C__X_XXXX_ 94
#define C__X_XXXXX 95
#define C__XX_____ 96
#define C__XX____X 97
#define C__XX___X_ 98
#define C__XX___XX 99
#define C__XX__X__ 100
#define C__XX__X_X 101
#define C__XX__XX_ 102
#define C__XX__XXX 103
#define C__XX_X___ 104
#define C__XX_X__X 105
#define C__XX_X_X_ 106
#define C__XX_X_XX 107
#define C__XX_XX__ 108
#define C__XX_XX_X 109
#define C__XX_XXX_ 110
#define C__XX_XXXX 111
#define C__XXX____ 112
#define C__XXX___X 113
#define C__XXX__X_ 114
#define C__XXX__XX 115
#define C__XXX_X__ 116
#define C__XXX_X_X 117
#define C__XXX_XX_ 118
#define C__XXX_XXX 119
#define C__XXXX___ 120
#define C__XXXX__X 121
#define C__XXXX_X_ 122
#define C__XXXX_XX 123
#define C__XXXXX__ 124
#define C__XXXXX_X 125
#define C__XXXXXX_ 126
#define C__XXXXXXX 127
#define C_X_______ 128
#define C_X______X 129
#define C_X_____X_ 130
#define C_X_____XX 131
#define C_X____X__ 132
#define C_X____X_X 133
#define C_X____XX_ 134
#define C_X____XXX 135
#define C_X___X___ 136
#define C_X___X__X 137
#define C_X___X_X_ 138
#define C_X___X_XX 139
#define C_X___XX__ 140
#define C_X___XX_X 141
#define C_X___XXX_ 142
#define C_X___XXXX 143
#define C_X__X____ 144
#define C_X__X___X 145
#define C_X__X__X_ 146
#define C_X__X__XX 147
#define C_X__X_X__ 148
#define C_X__X_X_X 149
#define C_X__X_XX_ 150
#define C_X__X_XXX 151
#define C_X__XX___ 152
#define C_X__XX__X 153
#define C_X__XX_X_ 154
#define C_X__XX_XX 155
#define C_X__XXX__ 156
#define C_X__XXX_X 157
#define C_X__XXXX_ 158
#define C_X__XXXXX 159
#define C_X_X_____ 160
#define C_X_X____X 161
#define C_X_X___X_ 162
#define C_X_X___XX 163
#define C_X_X__X__ 164
#define C_X_X__X_X 165
#define C_X_X__XX_ 166
#define C_X_X__XXX 167
#define C_X_X_X___ 168
#define C_X_X_X__X 169
#define C_X_X_X_X_ 170
#define C_X_X_X_XX 171
#define C_X_X_XX__ 172
#define C_X_X_XX_X 173
#define C_X_X_XXX_ 174
#define C_X_X_XXXX 175
#define C_X_XX____ 176
#define C_X_XX___X 177
#define C_X_XX__X_ 178
#define C_X_XX__XX 179
#define C_X_XX_X__ 180
#define C_X_XX_X_X 181
#define C_X_XX_XX_ 182
#define C_X_XX_XXX 183
#define C_X_XXX___ 184
#define C_X_XXX__X 185
#define C_X_XXX_X_ 186
#define C_X_XXX_XX 187
#define C_X_XXXX__ 188
#define C_X_XXXX_X 189
#define C_X_XXXXX_ 190
#define C_X_XXXXXX 191
#define C_XX______ 192
#define C_XX_____X 193
#define C_XX____X_ 194
#define C_XX____XX 195
#define C_XX___X__ 196
#define C_XX___X_X 197
#define C_XX___XX_ 198
#define C_XX___XXX 199
#define C_XX__X___ 200
#define C_XX__X__X 201
#define C_XX__X_X_ 202
#define C_XX__X_XX 203
#define C_XX__XX__ 204
#define C_XX__XX_X 205
#define C_XX__XXX_ 206
#define C_XX__XXXX 207
#define C_XX_X____ 208
#define C_XX_X___X 209
#define C_XX_X__X_ 210
#define C_XX_X__XX 211
#define C_XX_X_X__ 212
#define C_XX_X_X_X 213
#define C_XX_X_XX_ 214
#define C_XX_X_XXX 215
#define C_XX_XX___ 216
#define C_XX_XX__X 217
#define C_XX_XX_X_ 218
#define C_XX_XX_XX 219
#define C_XX_XXX__ 220
#define C_XX_XXX_X 221
#define C_XX_XXXX_ 222
#define C_XX_XXXXX 223
#define C_XXX_____ 224
#define C_XXX____X 225
#define C_XXX___X_ 226
#define C_XXX___XX 227
#define C_XXX__X__ 228
#define C_XXX__X_X 229
#define C_XXX__XX_ 230
#define C_XXX__XXX 231
#define C_XXX_X___ 232
#define C_XXX_X__X 233
#define C_XXX_X_X_ 234
#define C_XXX_X_XX 235
#define C_XXX_XX__ 236
#define C_XXX_XX_X 237
#define C_XXX_XXX_ 238
#define C_XXX_XXXX 239
#define C_XXXX____ 240
#define C_XXXX___X 241
#define C_XXXX__X_ 242
#define C_XXXX__XX 243
#define C_XXXX_X__ 244
#define C_XXXX_X_X 245
#define C_XXXX_XX_ 246
#define C_XXXX_XXX 247
#define C_XXXXX___ 248
#define C_XXXXX__X 249
#define C_XXXXX_X_ 250
#define C_XXXXX_XX 251
#define C_XXXXXX__ 252
#define C_XXXXXX_X 253
#define C_XXXXXXX_ 254
#define C_XXXXXXXX 255
/* DEFINES end. */

/*** TYPEDEFS */
typedef uint8_t char5x8_t[5];
typedef char5x8_t font5x8_t[256]; /* 0-127 standard ascii + 128-255 custom chars :)) */
/* TYPEDEFS end. */

/*** GLOBALS */
/* GLOBALS end. */

/*** FUNCTION DECLARATIONS */
/* FUNCTION DECLARATIONS end. */

/*** FUNCTION DEFINITIONS */
/* FUNCTION DEFINITIONS end. */

#ifdef __cplusplus
     }
#endif
#endif /* _BAOFONT_H_ */
