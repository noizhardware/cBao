#include <EEPROM.h>

#define EEPROM_SIZE EEPROM.length()

#define EEPROM_START 2 // 0 and 1 are reserved for possible flags-stuff


#ifndef SUCCESS
     #define SUCCESS 1
#endif
#ifndef FAIL
     #define FAIL 0
#endif

void wipeEEPROMsoft(){
     uint16_t i;
     for (i = 0 ; i < EEPROM_SIZE ; i++) {
          EEPROM.update(i, 0);} //write 0 to address i
     #ifdef DEBUG
          Serial.println("EEPROM softly wiped");
          #endif
}
void wipeEEPROMhard(){
     uint16_t i;
     for (i = 0 ; i < EEPROM_SIZE ; i++) {
          EEPROM.write(i, 0);} //write 0 to address i
     #ifdef DEBUG
          Serial.println("EEPROM hard wiped");
          #endif
}   

static inline bool getBit (const unsigned char source, const unsigned char bitpos){ // bitpos=[0..7] [LSB..MSB]
  return ((source & (1 << bitpos)) >> bitpos)!=0;}

static inline unsigned char setBit (const unsigned char source, const unsigned char bitpos, const bool bittoset){ // bitpos=[0..7] [LSB..MSB]
  return (bittoset) ? (source | (1 << bitpos)) : (source & ~(1 << bitpos));}

static inline unsigned char flipBit (const unsigned char source, const unsigned char bitpos){ // bitpos=[0..7] [LSB..MSB]
  return source ^ (1 << bitpos);}

static inline bool EEPROMaddrisOK(const unsigned int eepromAddr){
  return ((eepromAddr <= EEPROM_SIZE) && (eepromAddr >= 0));
}

static inline bool setEEPROMbit (const uint16_t eepromAddr, const uint8_t bitpos, const bool bittoset){ // bitpos=[0..7] [LSB..MSB]
    EEPROM.update(eepromAddr, setBit(EEPROM.read(eepromAddr), bitpos, bittoset)); // do it only if necessary (update checks identity before writing)
    return SUCCESS;}

static inline bool getEEPROMbit (const uint16_t eepromAddr, const uint8_t bitpos){ // bitpos=[0..7] [LSB..MSB]
  return getBit(EEPROM.read(eepromAddr), bitpos);}

static inline bool setEEPROMbyte (const uint16_t eepromAddr, const uint8_t bytetoset){
    if(EEPROMaddrisOK(eepromAddr)){
      EEPROM.update(eepromAddr, bytetoset);
      return SUCCESS;}
    else{
      return FAIL;}}
      
static inline unsigned char getEEPROMbyte (const unsigned int eepromAddr){
  if(EEPROMaddrisOK(eepromAddr)){
    return EEPROM.read(eepromAddr);}
  else{
    /* ERROR!!! address out of range!*/}
}
      
static inline bool setEEPROMshort(const uint16_t eepromAddr, const uint16_t valuetoset){
     EEPROM.update(eepromAddr, valuetoset);
     EEPROM.update(eepromAddr + 1, valuetoset >> 8);
     return SUCCESS;}

static inline uint16_t getEEPROMshort(const uint16_t eepromAddr){
     uint16_t out = (EEPROM.read(eepromAddr + 1) << 8);
     out |= EEPROM.read(eepromAddr);
     return out;}

static inline uint16_t getEEPROMptr(){ /* gets the position of the first '\0' in the eeprom. for when I'm using the eeprom as a string */
     uint16_t i;
     for (i = EEPROM_START ; i < EEPROM_SIZE ; i++) {
          #ifdef DEBUG
               Serial.print(i);
               Serial.print("th byte: ");
               Serial.println(getEEPROMbyte(i));
               #endif
          if(getEEPROMbyte(i)=='\0'){
               return i;}}
     return EEPROM_SIZE;} // if a '\0' is not found, max memory usage is assumed (cacca) might create problems */





// (0) 1-bit EEPROMflags [0..7]
// (0) 1-bit EEPROMflags [8..15]
// (0) 1-bit EEPROMflags [16..23]
// (0) 1-bit EEPROMflags [24..31]

static inline bool setEEPROMflag(const unsigned char flagID, const bool bittoset){ // flagID=[0..31]
    if(flagID <= 7){
      setEEPROMbit(0, flagID, bittoset);
      return 1;}
    else if((flagID > 7) && (flagID <= 15)){
      setEEPROMbit(1, (flagID - 8), bittoset);
      return 1;}
    else if((flagID > 15) && (flagID <= 23)){
      setEEPROMbit(2, (flagID - 16), bittoset);
      return 1;}
    else if((flagID > 23) && (flagID <= 31)){
      setEEPROMbit(3, (flagID - 24), bittoset);
      return 1;}
    else{
      return 0;} // ERROR!!! flagID out of range!
    }

static inline bool EEPROMflag(const unsigned char flagID){ // GET : flagID=[0..31]
  if(flagID <= 7){
    return getEEPROMbit(0, flagID);}
  else if((flagID > 7) && (flagID <= 15)){
    return getEEPROMbit(1, (flagID - 8));}
  else if((flagID > 15) && (flagID <= 23)){
    return getEEPROMbit(2, (flagID - 16));}
  else if((flagID > 23) && (flagID <= 31)){
    return getEEPROMbit(3, (flagID - 24));}
  else{/* ERROR!!! flagID out of range!*/}} 
  
