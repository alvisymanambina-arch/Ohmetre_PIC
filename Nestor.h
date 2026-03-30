#ifndef __Nestor__
#define __Nestor__


#include <16F877A.h>
#device ADC=10
#fuses HS
#use delay(crystal=20000000)


#define ultrasonDCm  (18.382)
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#fuses HS ,NOWDT , NOPUT , NOLVP 

void lcd_command(unsigned uint8_t );
 

char dera[41] =  {0,0,PIN_A0,PIN_A1,PIN_A2,PIN_A3,PIN_A4, PIN_A5,PIN_E0,
               PIN_E1,PIN_E2,0,0,0,0,PIN_C0,PIN_C1,PIN_C2,PIN_C3,PIN_D0
               ,PIN_D1,PIN_D2,PIN_D3,PIN_D4,PIN_C5,PIN_C6,PIN_C7,PIN_D4
               ,PIN_D5,PIN_D6,PIN_D7,0,0,PIN_B0,PIN_B1,PIN_B2,PIN_B3,PIN_B4,
               PIN_B5,PIN_B6,PIN_B7};
#define map(value, inMIN, inMAX, outMIN, outMAX)  ((value - inMIN)*(outMAX - outMIN)
#define IINPUT                        0
#define OUTPUT                        1
#define INPUT_PULLUP                  2

#define LSBFIRST                      0
#define MSBFIRST                      1

#define LOW                           0
#define HIGH                          1

#define int8_t                        char
#define int16_t                       int16 long
#define int32_t                       int32 long long
#define uint8_t                       unsigned int8_t
#define uint16_t                      unsigned int16_t
#define uint32_t                      unsigned int32_t
#define bool                          int1

#define lowByte(w)                    ((uint8_t) ((w) & 0xff))
#define highByte(w)                   (uint8_t) ((w) >> 8))

#define bit(i)                        (1<<i)
#define bitRead(x,bit)                ((x >> bit) & 0x01)
#define bitClear                      bit_clear
#define bitSet                        bit_set
#define bitWrite(x, bit,bitvalue)     ((bitvalue) ? bit_set(x, bit) : bit_clear(s, bit))

#define delay                         delay_ms
#define delayMicroseconds             delay_us

#define digitalWrite(i, status)    output_bit(i, status)
#define digitalRead(i)              input(dera[i])


#define SerialAvailable             kbhit
#define SerialRead                  getc
#define SerialPrint                 printf


#define pulseIn(char alfa, bool s)           int8 read_adc(int8 mode);
#define parseInt(message)               atoi(message)
#define parseFloat(message)             atof(message)
#define CHANGE                          1
#define FALLING                         2
#define RISING                          3
void setup();
void loop();
void lcd_init();
void lcd_command(unsigned int8_t cmd);
void lcd_pulse(uint8_t data);
void start();
void stop();
void write(uint8_t data);
void lcd_print( char* str);
void initADC();
float analogRead(int pin);
void main(){setup();while (TRUE){loop();}}


uint8_t shiftIn(char Din, char Clk, bool bitOrder){
   uint8_t value = 0;
   for(char i = 0; i < 8; ++i){
      value |= digitalRead(Din) << (bitOrder?(7 - i):i);
      digitalWrite(Clk, HIGH);
      digitalWrite(Clk, LOW);
   }
   return value;
}
void shiftOut(char Din, char Clk, bool bitOrder, char data){
    for (char i = 0;i<8;i++){
        digitalWrite(Din, (data>>(bitOrder?(7 - i):i))&1);
        digitalWrite(Clk, HIGH);
        digitalWrite(Clk, LOW);
    }
}


void floatToString(float value, char *buffer, int precision);

void initADC(){

    setup_adc_ports(ALL_ANALOG);
    setup_adc(ADC_CLOCK_INTERNAL);
}
float analogRead(int pin){
set_adc_channel(pin);
delay_us(10);
return read_adc();

}
#define analogReadMode initADC


void pinMode(int16 pin,int state){
int16 bit;
   if(pin>=PIN_A0 && pin<=PIN_A5){
   bit = get_tris_a();
    if(state==1){
      bit |=(1<<(pin-PIN_A0));
    }else{
      bit &= ~(1<<(pin-PIN_A0));
    }
    set_tris_a(bit);
   }
int16 bat;
   if(pin>=PIN_B0 && pin<=PIN_B7){
   bat = get_tris_b();
   if(state==1){
      bat |=(1<<(pin-PIN_B0));
   }else{
      bat &= ~(1<<(pin-PIN_B0));
   }
   set_tris_b(bat);
   }
int16 bet;
   if(pin>=PIN_C0 && pin<=PIN_C7){
   bet = get_tris_c();
   if(state==1){
      bet |=(1<<(pin-PIN_C0));
   }else{
      bet &= ~(1<<(pin-PIN_C0));
   }
   set_tris_c(bet);
   }
 int16 bit1;
   if(pin>=PIN_D0 && pin<=PIN_D5){
   bit1 = get_tris_d();
    if(state==1){
      bit1 |=(1<<(pin-PIN_D0));
    }else{
      bit1 &= ~(1<<(pin-PIN_D0));
    }
    set_tris_d(bit1);
   }

}

void dtostrf( float val , int8 width , int8 prec , char* sout ){
char fmt[10];
sprintf(fmt , "%%%d.%df" , width , prec);
sprintf(sout , fmt , val);
}



#endif



