#ifndef _KEYS_MICROSOFT_RT2300_H_
#define _KEYS_MICROSOFT_RT2300_H_

#include <stdbool.h>

/*
* _CAP are CAPITAL letters
* _REL are release codes
* there are also kkSHIFT_ESC
and kkSHIFT_ESC_REL things, still to complete
*/

/* TODO:
* _CAP_REL
*/

#define KEYS_QTY 114

#define kkQ 81
     #define kkQ_REL 32849
          #define kkQ_CAP 16465
               #define kkQ_CAP_REL 49233
#define kkW 87
     #define kkW_REL 32855
          #define kkW_CAP 16471
#define kkE 69
     #define kkE_REL 32837
          #define kkE_CAP 16453
#define kkEURO 1093
     #define kkEURO_REL 33861
#define kkR 82
     #define kkR_REL 32850
          #define kkR_CAP 16466
#define kkT 84
     #define kkT_REL 32852
          #define kkT_CAP 16468
#define kkY 89
     #define kkY_REL 32857
          #define kkY_CAP 16473
#define kkU 85
     #define kkU_REL 32853
          #define kkU_CAP 16469
#define kkI 73
     #define kkI_REL 32841
          #define kkI_CAP 16457
#define kkO 79
     #define kkO_REL 32847
          #define kkO_CAP 16463
#define kkP 80
     #define kkP_REL 32848
          #define kkP_CAP 16464
#define kkEE 93
     #define kkEE_REL 32861
#define kkEEE 16477
     #define kkEEE_REL 49245
#define kkPLUS 94
     #define kkPLUS_REL 32862
#define kkASTERISK 16478
     #define kkASTERISK_REL 49246

#define kkA 65
     #define kkA_REL 32833
          #define kkA_CAP 16449
#define kkS 83
     #define kkS_REL 32851
          #define kkS_CAP 16467
#define kkD 68
     #define kkD_REL 32836
          #define kkD_CAP 16452
#define kkF 70
     #define kkF_REL 32838
          #define kkF_CAP 16454
#define kkG 71
     #define kkG_REL 32839
          #define kkG_CAP 16455
#define kkH 72
     #define kkH_REL 32840
          #define kkH_CAP 16456
#define kkJ 74
     #define kkJ_REL 32842
          #define kkJ_CAP 16458
#define kkK 75
     #define kkK_REL 32843
          #define kkK_CAP 16459
#define kkL 76
     #define kkL_REL 32844
          #define kkL_CAP 16460
#define kkOO 91
     #define kkOO_REL 32859
#define kkCCEDILLA 16475
     #define kkCCEDILLA_REL 49243
#define kkAT 1115
     #define kkAT_REL 33833
#define kkAA 58
     #define kkAA_REL 32826
#define kkDEGREE 16442
     #define kkDEGREE_REL 49210
#define kkHASHTAG 1082
     #define kkHASHTAG_REL 33850
#define kkUU 92
     #define kkUU_REL 32860
#define kkSECTION 16476
     #define kkSECTION_REL 49244

#define kkANGL 139
     #define kkANGL_REL 32907
#define kkANGR 16523
     #define kkANGR_REL 49291
#define kkZ 90
     #define kkZ_CAP 16474
          #define kkZ_REL 32858
#define kkX 88
     #define kkX_CAP 16472
          #define kkX_REL 32856
#define kkC 67
     #define kkC_CAP 16451
          #define kkC_REL 32835
#define kkV 86
     #define kkV_CAP 16470
          #define kkV_REL 32854
#define kkB 66
     #define kkB_CAP 16450
          #define kkB_REL 32834
#define kkN 78
     #define kkN_CAP 16462
          #define kkN_REL 32846
#define kkM 77
     #define kkM_CAP 16461
          #define kkM_REL 32845
#define kkCOMMA 59
     #define kkCOMMA_REL 32827
#define kkPERIOD 61
     #define kkPERIOD_REL 32829
#define kkDASH 62
     #define kkDASH_REL 32830
#define kkSEMICOLON 16443
     #define kkSEMICOLON_REL 49211
#define kkCOLON 16445
     #define kkCOLON_REL 49213
#define kkUNDERSCORE 16446
     #define kkUNDERSCORE_REL 49214

#define kkSPACE 287
     #define kkSPACE 287
#define kkSPACE_REL 33055

#define kkBACKSLASH 64
     #define kkBACKSLASH_REL 32832
#define kk1 49
     #define kk1_REL 32817
#define kk2 50
     #define kk2_REL 32818
#define kk3 51
     #define kk3_REL 32819
#define kk4 52
     #define kk4_REL 32820
#define kk5 53
     #define kk5_REL 32821
#define kk6 54
     #define kk6_REL 32822
#define kk7 55
     #define kk7_REL 32823
#define kk8 56
     #define kk8_REL 32824
#define kk9 57
     #define kk9_REL 32825
#define kk0 48
     #define kk0_REL 32816
#define kkQUOTESINGLE 60
     #define kkQUOTESINGLE_REL 32828
#define kkII 95
     #define kkII_REL 32863
#define kkHAT 16479
     #define kkHAT_REL 49247

#define kkPIPE 16448
     #define kkPIPE_REL 49216
#define kkEXCLAMATION 16433
     #define kkEXCLAMATION_REL 49201
#define kkQUOTEDOUBLE 16434
     #define kkQUOTEDOUBLE_REL 49202
#define kkGBP 16435
     #define kkGBP_REL 49203
#define kkDOLLAR 16436
     #define kkDOLLAR_REL 49204
#define kkPERCENT 16437
     #define kkPERCENT_REL 49205
#define kkAMPERSAND 16438
     #define kkAMPERSAND_REL 49206
#define kkSLASH 16439
     #define kkSLASH_REL 49207
#define kkBRACKETOPEN 16440 
     #define kkBRACKETOPEN_REL 49208
#define kkBRACKETCLOSE 16441
     #define kkBRACKETCLOSE_REL 49209
#define kkEQUAL 16432
     #define kkEQUAL_REL 49200
#define kkQUESTION 16444
     #define kkQUESTION_REL 49212

#define kkENTER 286
     #define kkENTER_REL 33054
#define kkBACKSPACE 284
     #define kkBACKSPACE_REL 33052
#define kkESC 283
     #define kkESC_REL 33051
          #define kkSHIFT_ESC 16667
               /*#define kkSHIFT_ESC_REL 49435*/
               #define kkCTRL_ESC 8475
               
/* specials */               
#define kkCTRLL_T 8276 /* left CTRL + T */

#define kkSQUAREOPEN 1117
     #define kkSQUAREOPEN_REL 33885
#define kkSQUARECLOSE 1118
     #define kkSQUARECLOSE_REL 33886
#define kkCURLYOPEN 17501
     #define kkCURLYOPEN_REL 50269
#define kkCURLYCLOSE 17502
     #define kkCURLYCLOSE_REL 50270

#define kkMAIL 385
     #define kkMAIL_REL 33153
#define kkHOME 389
     #define kkHOME_REL 33157
#define kkSTAR 394
     #define kkSTAR_REL 33162
#define kkPLAY 380
     #define kkPLAY_REL 33148
#define kkVOLUP 382
     #define kkVOLUP_REL 33150
#define kkVOLDN 383
     #define kkVOLDN_REL 33151
#define kkMUTE 381
     #define kkMUTE_REL 33149
#define kkMUSIC 384
     #define kkMUSIC_REL 33152
#define kkSCREEN 387
     #define kkSCREEN_REL 33155
#define kkCALC 386
     #define kkCALC_REL 33154
#define kkTAB 285
     #define kkTAB_REL 33053
#define kkSHIFTL 16646
     #define kkSHIFTL_REL 33030
#define kkSHIFTR 16647
     #define kkSHIFTR_REL 33031
#define kkCTRLL 8456
     #define kkCTRLL_REL 33032
#define kkCTRLR 8457
     #define kkCTRLR_REL 33033
#define kkALT 2314
     #define kkALT_REL 33034
#define kkALTGR 1291
     #define kkALTGR_REL 33035
#define kkWINL 780
     #define kkWINL_REL 33036
#define kkWINR 270
     #define kkWINR_REL 33038
#define kkARROWUP 279
     #define kkARROWUP_REL 33047
#define kkARROWDN 280
     #define kkARROWDN_REL 33048
#define kkARROWL 277
     #define kkARROWL_REL 33045
#define kkARROWR 278
     #define kkARROWR_REL 33046
     
#define kkF1 353
     #define kkF1_REL 33121
#define kkF2 354
     #define kkF2_REL 33122
#define kkF3 355
     #define kkF3_REL 33123
#define kkF4 356
     #define kkF4_REL 33124
#define kkF5 357
     #define kkF5_REL 33125
#define kkF6 358
     #define kkF6_REL 33126
#define kkF7 359
     #define kkF7_REL 33127
#define kkF8 360
     #define kkF8_REL 33128
#define kkF9 361
     #define kkF9_REL 33129
#define kkF10 362
     #define kkF10_REL 33130
#define kkF11 363
     #define kkF11_REL 33131
#define kkF12 364
     #define kkF12_REL 33132

static __inline__ uint8_t kbdToChar(uint16_t kbd){ /* returns 0 if not typable */
     return
          'q'*(kbd==kkQ) +
               'Q'*(kbd==kkQ_CAP) +
          'w'*(kbd==kkW) +
               'W'*(kbd==kkW_CAP) +
          'e'*(kbd==kkE) +
               'E'*(kbd==kkE_CAP) +
          // '€'*(kbd==kkEURO) + /* not actually supported by Keyboard.write */
          'r'*(kbd==kkR) +
          't'*(kbd==kkT) +
          'y'*(kbd==kkY) +
          'u'*(kbd==kkU) +
          'i'*(kbd==kkI) +
          'o'*(kbd==kkO) +
          'p'*(kbd==kkP) +
                         'R'*(kbd==kkR_CAP) +
                         'T'*(kbd==kkT_CAP) +
                         'Y'*(kbd==kkY_CAP) +
                         'U'*(kbd==kkU_CAP) +
                         'I'*(kbd==kkI_CAP) +
                         'O'*(kbd==kkO_CAP) +
                         'P'*(kbd==kkP_CAP) +
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
                         'A'*(kbd==kkA_CAP) +
                         'S'*(kbd==kkS_CAP) +
                         'D'*(kbd==kkD_CAP) +
                         'F'*(kbd==kkF_CAP) +
                         'G'*(kbd==kkG_CAP) +
                         'H'*(kbd==kkH_CAP) +
                         'J'*(kbd==kkJ_CAP) +
                         'K'*(kbd==kkK_CAP) +
                         'L'*(kbd==kkL_CAP) +
               162*(kbd==kkOO) + /* ò */
                    // 'ç'*(kbd==kkCCEDILLA) +
                         '@'*(kbd==kkAT) +
               133*(kbd==kkAA) + /* à */
                    // '°'*(kbd==kkDEGREE) +
                         '#'*(kbd==kkHASHTAG) +
               // 'ù'*(kbd==kkUU) +
                    // '§'*(kbd==kkSECTION) +
          '<'*(kbd==kkANGL) +
               '>'*(kbd==kkANGR) +
          'z'*(kbd==kkZ) +
          'x'*(kbd==kkX) +
          'c'*(kbd==kkC) +
          'v'*(kbd==kkV) +
          'b'*(kbd==kkB) +
          'n'*(kbd==kkN) +
          'm'*(kbd==kkM) +
                         'Z'*(kbd==kkZ_CAP) +
                         'X'*(kbd==kkX_CAP) +
                         'C'*(kbd==kkC_CAP) +
                         'V'*(kbd==kkV_CAP) +
                         'B'*(kbd==kkB_CAP) +
                         'N'*(kbd==kkN_CAP) +
                         'M'*(kbd==kkM_CAP) +
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
                    '^'*(kbd==kkHAT) +
          '!'*(kbd==kkEXCLAMATION) +
          '\"'*(kbd==kkQUOTEDOUBLE) +
          // '£'*(kbd==kkGBP) +
          '$'*(kbd==kkDOLLAR) +
          '%'*(kbd==kkPERCENT) +
          '&'*(kbd==kkAMPERSAND) +
          '/'*(kbd==kkSLASH) +
          '('*(kbd==kkBRACKETOPEN) +
          ')'*(kbd==kkBRACKETCLOSE) +
          '='*(kbd==kkEQUAL) +
               176*(kbd==kkENTER) +
          '['*(kbd==kkSQUAREOPEN) +
          ']'*(kbd==kkSQUARECLOSE) +
          '{'*(kbd==kkCURLYOPEN) +
          '}'*(kbd==kkCURLYCLOSE) +
               '\t'*(kbd==kkTAB);}
               
// static __inline__ bool isTypable(uint16_t kbd){ // it's missing capital letters
//      return
//           (kbd==kkQ) ||
//           (kbd==kkW) ||
//           (kbd==kkE) ||
//           (kbd==kkEURO) ||
//           (kbd==kkR) ||
//           (kbd==kkT) ||
//           (kbd==kkY) ||
//           (kbd==kkU) ||
//           (kbd==kkI) ||
//           (kbd==kkO) ||
//           (kbd==kkP) ||
//                (kbd==kkEE) ||
//                     (kbd==kkEEE) ||
//                (kbd==kkPLUS) ||
//                     (kbd==kkASTERISK) ||
//           (kbd==kkA) ||
//           (kbd==kkS) ||
//           (kbd==kkD) ||
//           (kbd==kkF) ||
//           (kbd==kkG) ||
//           (kbd==kkH) ||
//           (kbd==kkJ) ||
//           (kbd==kkK) ||
//           (kbd==kkL) ||
//                (kbd==kkOO) ||
//                     (kbd==kkCCEDILLA) ||
//                          (kbd==kkAT) ||
//                (kbd==kkAT) ||
//                     (kbd==kkDEGREE) ||
//                          (kbd==kkHASHTAG) ||
//                (kbd==kkUU) ||
//                     (kbd==kkSECTION) ||
//           (kbd==kkANGL) ||
//                (kbd==kkANGR) ||
//           (kbd==kkZ) ||
//           (kbd==kkX) ||
//           (kbd==kkC) ||
//           (kbd==kkV) ||
//           (kbd==kkB) ||
//           (kbd==kkN) ||
//           (kbd==kkM) ||
//                (kbd==kkCOMMA) ||
//                     (kbd==kkSEMICOLON) ||
//                (kbd==kkPERIOD) ||
//                     (kbd==kkCOLON) ||
//                (kbd==kkDASH) ||
//                     (kbd==kkUNDERSCORE) ||
//           (kbd==kkSPACE) ||
//           (kbd==kkBACKSLASH) ||
//                (kbd==kkPIPE) ||
//           (kbd==kk1) ||
//           (kbd==kk2) ||
//           (kbd==kk3) ||
//           (kbd==kk4) ||
//           (kbd==kk5) ||
//           (kbd==kk6) ||
//           (kbd==kk7) ||
//           (kbd==kk8) ||
//           (kbd==kk9) ||
//           (kbd==kk0) ||
//                (kbd==kkQUOTESINGLE) ||
//                     (kbd==kkQUESTION) ||
//                (kbd==kkII) ||
//                     (kbd==kkANGLEUP) ||
//           (kbd==kkEXCLAMATION) ||
//           (kbd==kkQUOTEDOUBLE) ||
//           (kbd==kkGBP) ||
//           (kbd==kkDOLLAR) ||
//           (kbd==kkPERCENT) ||
//           (kbd==kkAMPERSAND) ||
//           (kbd==kkSLASH) ||
//           (kbd==kkBRACKETOPEN) ||
//           (kbd==kkBRACKETCLOSE) ||
//           (kbd==kkEQUAL) ||
//           (kbd==kkANGLEUP) ||
//                (kbd==kkENTER) ||
//           (kbd==kkSQUAREOPEN) ||
//           (kbd==kkSQUARECLOSE) ||
//           (kbd==kkCURLYOPEN) ||
//           (kbd==kkCURLYCLOSE) ||
//                (kbd==kkTAB);}

// static __inline__ bool isTypable_Microsoft_RT2300(uint16_t keyCode){ /* verify it's a typable char, not a key release code, not the mysterious 170 or 250 that appears at startup */
//      return (keyCode<=17502)&&(keyCode>=48)&&(keyCode!=170)&(keyCode!=250);}

static __inline__ int toKeyboardCode(int in){
     Serial.print("============= ");
     Serial.println(in);
     if(in==130){return 123;} // è
     else if(in==138){return 91;} // é
     // else if(in=='ù'){return 92;} // ù
     else if(in==133){return 39;} // à
     else if(in==162){return 59;} // ò
     // else if(in=='ç'){return 58;} // ç
     else if(in==141){return 61;} // ì
     else if(in=='-'){return 47;} // -
     else{return in;} // all other raw bytes*
     /* !°£$%/à)=(^,'.-0123456789çò;ì:_"ABCDEFGHIJKLMNOPQRSTUVWXYZèù+&?\abcdefghijklmnopqrstuvwxyzé§*| */
}

#endif /* _KEYS_MICROSOFT_RT2300_H_ */