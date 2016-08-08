/*
 * (c) Dmytro Nikandrov
 * 25.07.2016
 * A project to display 8-digit number
 * default number is "12345678"
 * 
 */


//Both 74HC595 chips are connected to the Arduino using:
#define DATA_PIN    11
#define LATCH_PIN   8
#define CLOCK_PIN   12

// Each 4-digit 7-segment indicator has digit selector pin
#define SEGM_DIGIT_PIN_1   5
#define SEGM_DIGIT_PIN_2   4
#define SEGM_DIGIT_PIN_3   3
#define SEGM_DIGIT_PIN_4   2



/*
 * Segments of the 7seg indicator
 * IC transmit this numbers as-written, so to light segment A 74HC595 chip will emit Q0=0,Q1=0,Q2=0,Q3=0,Q4=0,Q5=0,Q6=0,Q7=1

byte d0 = 0b00000001; //seg A
byte d1 = 0b00000010; //seg F 
byte d2 = 0b00000100; //seg B
byte d3 = 0b00001000; //seg G
byte d4 = 0b00010000; //seg C
byte d5 = 0b00100000; //seg dot
byte d6 = 0b01000000; //seg D
byte d7 = 0b10000000; //seg E
*/



byte d0 = 0b11010111;  //number 0 (segments used: f e d c b a)
byte d1 = 0b00010100;  //number 1 (segments used: b c)
byte d2 = 0b11001101;  //number 2 (segments used: a b d e g)
byte d3 = 0b01011101;  //number 3 (segments used: a b c d g)
byte d4 = 0b00011110;  //number 4 (segments used: b c f g)
byte d5 = 0b01011011;  //number 5 (segments used: a c d f g)
byte d6 = 0b11011011;  //number 6 (segments used: a c d e f g)
byte d7 = 0b00010101;  //number 7 (segments used: a b c)
byte d8 = 0b11011111;  //number 8 (segments used: a b c d e f g)
byte d9 = 0b01011111;  //number 9 (segments used: a b c d f g)
byte dd = 0b00100000;  //a dot symbol . (segments used: dot)

byte value1 = 0b00000000, value2 = 0b00000000;

int n = 0; // n is the number of 7-segment digit to which we apply value at any given moment
int delay_value = 0;


void setup()
{
  pinMode(DATA_PIN, OUTPUT);
  pinMode(CLOCK_PIN, OUTPUT);
  pinMode(LATCH_PIN, OUTPUT);

  pinMode(SEGM_DIGIT_PIN_1, OUTPUT);
  pinMode(SEGM_DIGIT_PIN_2, OUTPUT);
  pinMode(SEGM_DIGIT_PIN_3, OUTPUT);
  pinMode(SEGM_DIGIT_PIN_4, OUTPUT);

  digitalWrite(SEGM_DIGIT_PIN_1, LOW);
  digitalWrite(SEGM_DIGIT_PIN_2, LOW);
  digitalWrite(SEGM_DIGIT_PIN_3, LOW);
  digitalWrite(SEGM_DIGIT_PIN_4, LOW);

  delay_value = 1; // milliseconds
}



void loop()
{
  if (n > 4) n=0;
  n++;

  if (n == 1) {
    digitalWrite(SEGM_DIGIT_PIN_1, HIGH);
    digitalWrite(SEGM_DIGIT_PIN_2, LOW);
    digitalWrite(SEGM_DIGIT_PIN_3, LOW);
    digitalWrite(SEGM_DIGIT_PIN_4, LOW);
    value1 = d4, value2 = d8;}
    
  if (n == 2) {
    digitalWrite(SEGM_DIGIT_PIN_1, LOW);
    digitalWrite(SEGM_DIGIT_PIN_2, HIGH);
    digitalWrite(SEGM_DIGIT_PIN_3, LOW);
    digitalWrite(SEGM_DIGIT_PIN_4, LOW);
    value1 = d3, value2 = d7;}
    
  if (n == 3) {
    digitalWrite(SEGM_DIGIT_PIN_1, LOW);
    digitalWrite(SEGM_DIGIT_PIN_2, LOW);
    digitalWrite(SEGM_DIGIT_PIN_3, HIGH);
    digitalWrite(SEGM_DIGIT_PIN_4, LOW);
    value1 = d2, value2 = d6;}
  
  if (n == 4) {
    digitalWrite(SEGM_DIGIT_PIN_1, LOW);
    digitalWrite(SEGM_DIGIT_PIN_2, LOW);
    digitalWrite(SEGM_DIGIT_PIN_3, LOW);
    digitalWrite(SEGM_DIGIT_PIN_4, HIGH);
    value1 = d1, value2 = d5;}

  digitalWrite(LATCH_PIN, LOW);   
  shiftOut(DATA_PIN, CLOCK_PIN, LSBFIRST, value2);  // value for chip №2
  shiftOut(DATA_PIN, CLOCK_PIN, LSBFIRST, value1);  // value for chip №1
  digitalWrite(LATCH_PIN, HIGH);
  delay(2);
  
  // zeroing pins of the 74hc595 to eradicate IC memory effect
  digitalWrite(LATCH_PIN, LOW);
  shiftOut(DATA_PIN, CLOCK_PIN, LSBFIRST, 0b00000000);  // value for chip №2
  shiftOut(DATA_PIN, CLOCK_PIN, LSBFIRST, 0b00000000);  // value for chip №1
  digitalWrite(LATCH_PIN, HIGH);
  delay(delay_value);
}

