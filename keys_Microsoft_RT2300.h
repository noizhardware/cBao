#include <stdbool.h>

// _C are CAPITAL letters

#define kkQ 81
     #define kkQ_C 16465
#define kkW 87
     #define kkW_C 16471
#define kkE 69
     #define kkE_C 16453
#define kkEURO 1093
#define kkR 82
     #define kkR_C 16466
#define kkT 84
     #define kkT_C 16468
#define kkY 89
     #define kkY_C 16473
#define kkU 85
     #define kkU_C 16469
#define kkI 73
     #define kkI_C 16457
#define kkO 79
     #define kkO_C 16463
#define kkP 80
     #define kkP_C 16464
#define kkEE 93
#define kkEEE 16477
#define kkPLUS 94
#define kkASTERISK 16478

#define kkA 65
     #define kkA_C 16449
#define kkS 83
     #define kkS_C 16467
#define kkD 68
     #define kkD_C 16452
#define kkF 70
     #define kkF_C 16454
#define kkG 71
     #define kkG_C 16455
#define kkH 72
     #define kkH_C 16456
#define kkJ 74
     #define kkJ_C 16458
#define kkK 75
     #define kkK_C 16459
#define kkL 76
     #define kkL_C 16460
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
     #define kkZ_C 16474
#define kkX 88
     #define kkX_C 16472
#define kkC 67
     #define kkC_C 16451
#define kkV 86
     #define kkV_C 16470
#define kkB 66
     #define kkB_C 16450
#define kkN 78
     #define kkN_C 16462
#define kkM 77
     #define kkM_C 16461
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
     #define kkSHIFTL_RELEASE 33030
#define kkSHIFTR 16647
     #define kkSHIFTR_RELEASE 33031
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
               'Q'*(kbd==kkQ_C) +
          'w'*(kbd==kkW) +
               'W'*(kbd==kkW_C) +
          'e'*(kbd==kkE) +
               'E'*(kbd==kkE_C) +
          '€'*(kbd==kkEURO) + /* not actually supported by Keyboard.write */
          'r'*(kbd==kkR) +
          't'*(kbd==kkT) +
          'y'*(kbd==kkY) +
          'u'*(kbd==kkU) +
          'i'*(kbd==kkI) +
          'o'*(kbd==kkO) +
          'p'*(kbd==kkP) +
                         'R'*(kbd==kkR_C) +
                         'T'*(kbd==kkT_C) +
                         'Y'*(kbd==kkY_C) +
                         'U'*(kbd==kkU_C) +
                         'I'*(kbd==kkI_C) +
                         'O'*(kbd==kkO_C) +
                         'P'*(kbd==kkP_C) +
               130*(kbd==kkEE) +
                    138*(kbd==kkEEE) +
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
                         'A'*(kbd==kkA_C) +
                         'S'*(kbd==kkS_C) +
                         'D'*(kbd==kkD_C) +
                         'F'*(kbd==kkF_C) +
                         'G'*(kbd==kkG_C) +
                         'H'*(kbd==kkH_C) +
                         'J'*(kbd==kkJ_C) +
                         'K'*(kbd==kkK_C) +
                         'L'*(kbd==kkL_C) +
               162*(kbd==kkOO) + /* ò */
                    'ç'*(kbd==kkCCEDILLA) +
                         '@'*(kbd==kkAT) +
               133*(kbd==kkAA) + /* à */
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
                         'Z'*(kbd==kkZ_C) +
                         'X'*(kbd==kkX_C) +
                         'C'*(kbd==kkC_C) +
                         'V'*(kbd==kkV_C) +
                         'B'*(kbd==kkB_C) +
                         'N'*(kbd==kkN_C) +
                         'M'*(kbd==kkM_C) +
               ','*(kbd==kkCOMMA) +
                    ';'*(kbd==kkSEMICOLON) +
               '.'*(kbd==kkPERIOD) +
                    ':'*(kbd==kkCOLON) +
               '-'*(kbd==kkDASH) +
                    '_'*(kbd==kkUNDERSCORE) +
          ' '*(kbd==kkSPACE) +
          '\\'*(kbd==kkBACKSLASH) +
               '|'*(kbd==kkPIPE) +
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
                    '\?'*(kbd==kkQUESTION) +
               141*(kbd==kkII) + /* ì */
                    '^'*(kbd==kkANGLEUP) +
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
          '^'*(kbd==kkANGLEUP) +
               176*(kbd==kkENTER) +
          '['*(kbd==kkSQUAREOPEN) +
          ']'*(kbd==kkSQUARECLOSE) +
          '{'*(kbd==kkCURLYOPEN) +
          '}'*(kbd==kkCURLYCLOSE) +
               '\t'*(kbd==kkTAB);}
               
static __inline__ bool isTypable(uint16_t kbd){ // it's missing capital letters
     return
          (kbd==kkQ) ||
          (kbd==kkW) ||
          (kbd==kkE) ||
          (kbd==kkEURO) ||
          (kbd==kkR) ||
          (kbd==kkT) ||
          (kbd==kkY) ||
          (kbd==kkU) ||
          (kbd==kkI) ||
          (kbd==kkO) ||
          (kbd==kkP) ||
               (kbd==kkEE) ||
                    (kbd==kkEEE) ||
               (kbd==kkPLUS) ||
                    (kbd==kkASTERISK) ||
          (kbd==kkA) ||
          (kbd==kkS) ||
          (kbd==kkD) ||
          (kbd==kkF) ||
          (kbd==kkG) ||
          (kbd==kkH) ||
          (kbd==kkJ) ||
          (kbd==kkK) ||
          (kbd==kkL) ||
               (kbd==kkOO) ||
                    (kbd==kkCCEDILLA) ||
                         (kbd==kkAT) ||
               (kbd==kkAT) ||
                    (kbd==kkDEGREE) ||
                         (kbd==kkHASHTAG) ||
               (kbd==kkUU) ||
                    (kbd==kkSECTION) ||
          (kbd==kkANGL) ||
               (kbd==kkANGR) ||
          (kbd==kkZ) ||
          (kbd==kkX) ||
          (kbd==kkC) ||
          (kbd==kkV) ||
          (kbd==kkB) ||
          (kbd==kkN) ||
          (kbd==kkM) ||
               (kbd==kkCOMMA) ||
                    (kbd==kkSEMICOLON) ||
               (kbd==kkPERIOD) ||
                    (kbd==kkCOLON) ||
               (kbd==kkDASH) ||
                    (kbd==kkUNDERSCORE) ||
          (kbd==kkSPACE) ||
          (kbd==kkBACKSLASH) ||
               (kbd==kkPIPE) ||
          (kbd==kk1) ||
          (kbd==kk2) ||
          (kbd==kk3) ||
          (kbd==kk4) ||
          (kbd==kk5) ||
          (kbd==kk6) ||
          (kbd==kk7) ||
          (kbd==kk8) ||
          (kbd==kk9) ||
          (kbd==kk0) ||
               (kbd==kkQUOTESINGLE) ||
                    (kbd==kkQUESTION) ||
               (kbd==kkII) ||
                    (kbd==kkANGLEUP) ||
          (kbd==kkEXCLAMATION) ||
          (kbd==kkQUOTEDOUBLE) ||
          (kbd==kkGBP) ||
          (kbd==kkDOLLAR) ||
          (kbd==kkPERCENT) ||
          (kbd==kkAMPERSAND) ||
          (kbd==kkSLASH) ||
          (kbd==kkBRACKETOPEN) ||
          (kbd==kkBRACKETCLOSE) ||
          (kbd==kkEQUAL) ||
          (kbd==kkANGLEUP) ||
               (kbd==kkENTER) ||
          (kbd==kkSQUAREOPEN) ||
          (kbd==kkSQUARECLOSE) ||
          (kbd==kkCURLYOPEN) ||
          (kbd==kkCURLYCLOSE) ||
               (kbd==kkTAB);}

static __inline__ bool isKey_Microsoft_RT2300(uint16_t key){ /* verify if it's not a key release code */
     return (key<=18000);}

static __inline__ int toKeyboardCode(int in){
     Serial.print("============= ");
     Serial.println(in);
     if(in==130){return 123;} // è
     else if(in==138){return 91;} // é
     else if(in=='ù'){return 92;} // ù
     else if(in==133){return 39;} // à
     else if(in==162){return 59;} // ò
     else if(in=='ç'){return 58;} // ç
     else if(in==141){return 61;} // ì
     else if(in=='-'){return 47;} // -
     else{return in;} // all other raw bytes*
     /* !°£$%/à)=(^,'.-0123456789çò;ì:_"ABCDEFGHIJKLMNOPQRSTUVWXYZèù+&?\abcdefghijklmnopqrstuvwxyzé§*| */
}
















