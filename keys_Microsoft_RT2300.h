#include <stdbool.h>

#define kkQ 81
#define kkW 87
#define kkE 69
#define kkEURO 1093
#define kkR 82
#define kkT 84
#define kkY 89
#define kkU 85
#define kkI 73
#define kkO 79
#define kkP 80
#define kkEE 93
#define kkEEE 16477
#define kkPLUS 94
#define kkASTERISK 16478

#define kkA 65
#define kkS 83
#define kkD 68
#define kkF 70
#define kkG 71
#define kkH 72
#define kkJ 74
#define kkK 75
#define kkL 76
#define kkOO 91
#define kkCCEDILLA 16475
#define kkAT 1115
#define kkAA 58
#define kkDEGREE 16442
#define kkHASHTAG 1082
#define kkUU 92
#define kkSECTION 16476

#define kkANGL 139
#define kkANGR 16523
#define kkZ 90
#define kkX 88
#define kkC 67
#define kkV 86
#define kkB 66
#define kkN 78
#define kkM 77
#define kkCOMMA 59
#define kkPERIOD 61
#define kkDASH 62
#define kkSEMICOLON 16443
#define kkCOLON 16445
#define kkUNDERSCORE 16446

#define kkSPACE 287
#define kkSPACERELEASE 33055

#define kkBACKSLASH 64
#define kk1 49
#define kk2 50
#define kk3 51
#define kk4 52
#define kk5 53
#define kk6 54
#define kk7 55
#define kk8 56
#define kk9 57
#define kk0 48
#define kkQUOTESINGLE 60
#define kkII 95

#define kkPIPE 16448
#define kkEXCLAMATION 16433
#define kkQUOTEDOUBLE 16434
#define kkGBP 16435
#define kkDOLLAR 16436
#define kkPERCENT 16437
#define kkAMPERSAND 16438
#define kkSLASH 16439
#define kkBRACKETOPEN 16440 
#define kkBRACKETCLOSE 16441
#define kkEQUAL 16432
#define kkQUESTION 16444
#define kkANGLEUP 16479

#define kkENTER 286
#define kkBACKSPACE 284
#define kkESC 283

#define kkSQUAREOPEN 1117
#define kkSQUARECLOSE 1118
#define kkCURLYOPEN 17501
#define kkCURLYCLOSE 17502

#define kkEMAIL 385
#define kkHOUSE 389
#define kkSTAR 394
#define kkPLAY 380
#define kkVOLUP 382
#define kkVOLDN 383
#define kkMUTE 381
#define kkMUSIC 384
#define kkSCREEN 387
#define kkCALC 386
#define kkTAB 285
#define kkSHIFTL 16646
#define kkSHIFTR 16647
#define kkCTRLL 8456
#define kkCTRLR 8457
#define kkALT 2314
#define kkALTGR 1291
#define kkWINL 780
#define kkWINR 270
#define kkBACKSLASH 64
#define kkARROWUP 279
#define kkARROWDN 280
#define kkARROWL 277
#define kkARROWR 278
#define kkF1 353
#define kkF2 354
#define kkF3 355
#define kkF4 356
#define kkF5 357
#define kkF6 358
#define kkF7 359
#define kkF8 360
#define kkF9 361
#define kkF10 362
#define kkF11 363
#define kkF12 364

static __inline__ uint8_t kbdToChar(uint16_t kbd){
     return
          'q'*(kbd==kkQ) +
          'w'*(kbd==kkW) +
          'e'*(kbd==kkE) +
          '€'*(kbd==kkEURO) +
          'r'*(kbd==kkR) +
          't'*(kbd==kkT) +
          'y'*(kbd==kkY) +
          'u'*(kbd==kkU) +
          'i'*(kbd==kkI) +
          'o'*(kbd==kkO) +
          'p'*(kbd==kkP) +
          'è'*(kbd==kkEE) +
          'é'*(kbd==kkEEE) +
          '+'*(kbd==kkPLUS) +
          '*'*(kbd==kkASTERISK) +
          'a'*(kbd==kkA) +
          's'*(kbd==kkS) +
          'd'*(kbd==kkD) +
          'f'*(kbd==kkF) +
          'g'*(kbd==kkG) +
          'h'*(kbd==kkH) +
          'j'*(kbd==kkJ) +
          'k'*(kbd==kkK) +
          'l'*(kbd==kkL) +
          'ò'*(kbd==kkOO) +
          'ç'*(kbd==kkCEDILLA) +
          '@'*(kbd==kkAT) +
          'à'*(kbd==kkAT) +
          '°'*(kbd==kkDEGREE) +
          '#'*(kbd==kkHASHTAG) +
          'ù'*(kbd==kkUU) +
          '§'*(kbd==kkSECTION) +
          '<'*(kbd==kkANGL) +
          '>'*(kbd==kkANGR) +
          'z'*(kbd==kkZ) +
          'x'*(kbd==kkX) +
          'c'*(kbd==kkC) +
          'v'*(kbd==kkV) +
          'b'*(kbd==kkB) +
          'n'*(kbd==kkN) +
          'm'*(kbd==kkM) +
          ','*(kbd==kkCOMMA) +
          '.'*(kbd==kkPERIOD) +
          '-'*(kbd==kkDASH) +
          ';'*(kbd==kSEMICOLON) +
          ':'*(kbd==kCOLON) +
          '_'*(kbd==kkUNDERSCORE) +
          ' '*(kbd==kkSPACE) +
          '\\'*(kbd==kkBACKSLASH) +
          '1'*(kbd==kk1) +
          '2'*(kbd==kk2) +
          '3'*(kbd==kk3) +
          '4'*(kbd==kk4) +
          '5'*(kbd==kk5) +
          '6'*(kbd==kk6) +
          '7'*(kbd==kk7) +
          '8'*(kbd==kk8) +
          '9'*(kbd==kk9) +
          '0'*(kbd==kk0) +
          '\''*(kbd==kkQUOTESINGLE) +
          'ì'*(kbd==kkII) +
          '|'*(kbd==kkPIPE) +
          '!'*(kbd==kkEXCLAMATION) +
          '\"'*(kbd==kkQUOTEDOUBLE) +
          '£'*(kbd==kkGBP) +
          '$'*(kbd==kkDOLLAR) +
          '%'*(kbd==kkPERCENT) +
          '&'*(kbd==kkAMPERSAND) +
          '/'*(kbd==kkSLASH) +
          '('*(kbd==kkBRACKETOPEN) +
          ')'*(kbd==kkBRACKETCLOSE) +
          '='*(kbd==kkEQUAL) +
          '?'*(kbd==kkQUESTION) +
          '^'*(kbd==kkANGLEUP) +
          '\r'*(kbd==kkENTER) +
          '['*(kbd==kkSQUAREOPEN) +
          ']'*(kbd==kkSQUARECLOSE) +
          '{'*(kbd==kkCURLYOPEN) +
          '}'*(kbd==kkCURLYCLOSE) +
          '\t'*(kbd==kkTAB) +
          '^'*(kbd==kkANGLEUP);}

static __inline__ bool isKey_Microsoft_RT2300(uint16_t key){
     return (key<=18000);}