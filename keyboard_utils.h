/* shitty legacy things */
/* 2021c28-1506 */
#define KEYSTROKE_SENDER Keyboard.write(key_to_char(c));

bool isKey_Microsoft_RT2300(uint16_t key){
     return (key<=18000 && key>0) ? true : false;}

char key_to_char(uint16_t key){ // this is old, now you should use the branchless kbdToChar from keys_Microsoft_RT2300.h
     if(key==kkQ){return 'q';}
     else if(key==kkW){return 'w';}
     else if(key==kkE){return 'e';}
     else if(key==kkR){return 'r';}
     else if(key==kkT){return 't';}
     else if(key==kkY){return 'y';}
     else if(key==kkU){return 'u';}
     else if(key==kkI){return 'i';}
     else if(key==kkO){return 'o';}
     else if(key==kkP){return 'p';}
     /*else if(key==kkEE){return 'è';}*/
     else if(key==kkPLUS){return '+';}
          /*else if(key==kkEEE){return 'é';}*/
          else if(key==kkASTERISK){return '*';}
               else if(key==kkSQUAREOPEN){return '[';}
               else if(key==kkSQUARECLOSE){return ']';}
     else if(key==kkA){return 'a';}
     else if(key==kkS){return 's';}
     else if(key==kkD){return 'd';}
     else if(key==kkF){return 'f';}
     else if(key==kkG){return 'g';}
     else if(key==kkH){return 'h';}
     else if(key==kkJ){return 'j';}
     else if(key==kkK){return 'k';}
     else if(key==kkL){return 'l';}
     /*else if(key==kkOO){return 'ò';}
     else if(key==kkAA){return 'à';}
     else if(key==kkUU){return 'ù';}
          else if(key==kkCCEDILLA){return 'ç';}
          else if(key==kkDEGREE){return '°';}
          else if(key==kkSECTION){return '§';}
               else if(key==kkAT){return '@';}
               else if(key==kkHASHTAG){return '#';}*/
     else if(key==kkANGL){return '<';}
     else if(key==kkANGR){return '>';}
     else if(key==kkZ){return 'z';}
     else if(key==kkX){return 'x';}
     else if(key==kkC){return 'c';}
     else if(key==kkV){return 'v';}
     else if(key==kkB){return 'b';}
     else if(key==kkN){return 'n';}
     else if(key==kkM){return 'm';}
     else if(key==kkCOMMA){return ',';}
     else if(key==kkPERIOD){return '.';}
     else if(key==kkDASH){return '-';}
          else if(key==kkSEMICOLON){return ';';}
          else if(key==kkCOLON){return ':';}
          else if(key==kkUNDERSCORE){return '_';}
     else if(key==kkSPACE){return ' ';}
     else if(key==kk1){return '1';}
     else if(key==kk2){return '2';}
     else if(key==kk3){return '3';}
     else if(key==kk4){return '4';}
     else if(key==kk5){return '5';}
     else if(key==kk6){return '6';}
     else if(key==kk7){return '7';}
     else if(key==kk8){return '8';}
     else if(key==kk9){return '9';}
     else if(key==kk0){return '0';}
     // else if(key==kk){return '';}
     else{return 0;}}

static inline char* makeString(uint16_t* sequence, uint16_t maxLen){ //transform a uint16_t sequence in a sequence of chars // needs FREE after use!!!!! memory leak DANGER
     uint16_t* seqq = sequence;
     char* temp;
     temp = (char*)malloc(maxLen);
     char* out = temp;
     //Serial.println("outside while...");
     //unsigned char tempIndex = 0;
     while(*seqq!=0){
          //Serial.println(key_to_char(*seqq));
          *temp = key_to_char(*seqq); // the uint16_t's are mapped to char bytes using that special keymapper, that's why this function is not in the baostring library. it's somewhat specific to NYX
          temp++;
          seqq++;}
     *temp = 0;
          //Serial.println(out);
     return out;}

/*
// #define KEYSTROKE_SENDER \
// if(c == 81){Keyboard.write('q');}\
// if(c == 87){Keyboard.write('w');}\
// if(c == 69){Keyboard.write('e');}\
// if(c == 82){Keyboard.write('r');}\
// if(c == 84){Keyboard.write('t');}\
// if(c == 89){Keyboard.write('y');}\
// if(c == 85){Keyboard.write('u');}\
// if(c == 73){Keyboard.write('i');}\
// if(c == 79){Keyboard.write('o');}\
// if(c == 80){Keyboard.write('p');}\
// if(c == 93){Keyboard.write('è');}\
// if(c == 94){Keyboard.write('+');}\
// if(c == 65){Keyboard.write('a');}\
// if(c == 83){Keyboard.write('s');}\
// if(c == 68){Keyboard.write('d');}\
// if(c == 70){Keyboard.write('f');}\
// if(c == 71){Keyboard.write('g');}\
// if(c == 72){Keyboard.write('h');}\
// if(c == 74){Keyboard.write('j');}\
// if(c == 75){Keyboard.write('k');}\
// if(c == 76){Keyboard.write('l');}\
// if(c == 91){Keyboard.write('ò');}\
// if(c == 58){Keyboard.write('à');}\
// if(c == 92){Keyboard.write('ù');}\
// if(c == 139){Keyboard.write('<');}\
// if(c == 90){Keyboard.write('z');}\
// if(c == 88){Keyboard.write('x');}\
// if(c == 67){Keyboard.write('c');}\
// if(c == 86){Keyboard.write('v');}\
// if(c == 66){Keyboard.write('b');}\
// if(c == 78){Keyboard.write('n');}\
// if(c == 77){Keyboard.write('m');}\
// if(c == 59){Keyboard.write(',');}\
// if(c == 61){Keyboard.write('.');}\
// if(c == 62){Keyboard.write('-');}\
// if(c == 287){Keyboard.write(' ');}\
// if(c == 49){Keyboard.write('1');}\
// if(c == 50){Keyboard.write('2');}\
// if(c == 51){Keyboard.write('3');}\
// if(c == 52){Keyboard.write('4');}\
// if(c == 53){Keyboard.write('5');}\
// if(c == 54){Keyboard.write('6');}\
// if(c == 55){Keyboard.write('7');}\
// if(c == 56){Keyboard.write('8');}\
// if(c == 57){Keyboard.write('9');}\
// if(c == 48){Keyboard.write('0');}
*/
