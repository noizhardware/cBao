static inline void vibInit(unsigned char vibPin);
static inline void vibDash(unsigned int ms);


unsigned char vibroPin;

static inline void vibInit(unsigned char vibPin){
     vibroPin = vibPin;}

static inline void vibDash(unsigned int ms){
     digitalWrite(vibroPin, 1);
     delay(ms);
     digitalWrite(vibroPin, 0);}