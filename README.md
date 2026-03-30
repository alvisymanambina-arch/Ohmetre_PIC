#include <LCDI2C.h>

#define LCD_ADDR (0x3F << 1)
//!#use rs232(baud=9600, xmit=PIN_C6, rcv=PIN_C7)

float mesurePin = PIN_A0;
float rfR = 1000.0;
float r;
char buffer[10];

void floatToStr(float valeur, char* buffer) {
   long temp = (long)(valeur * 100);
   int entier = temp / 100;
   int decimale = temp % 100;
   
   int pos = 0;
   if (entier >= 1000) buffer[pos++] = (entier / 1000) % 10 + '0';
   if (entier >= 100)  buffer[pos++] = (entier / 100) % 10 + '0';
   if (entier >= 10)   buffer[pos++] = (entier / 10) % 10 + '0';
   buffer[pos++] = (entier % 10) + '0';
   
   buffer[pos++] = '.';
   buffer[pos++] = (decimale / 10) + '0';
   buffer[pos++] = (decimale % 10) + '0';
   buffer[pos] = '\0';
}

void setup() {
  lcd_init();
  delay(1000);
  lcd_setCursor(0, 0);
  char* mes = "Mesure Resistance";
  lcd_print(mes);
  delay(1000);
   lcd_setCursor(0, 0);
  char* I = "Initialisation...";
  lcd_print(I);
  delay(1000);
 
}

void loop() {
  initADC();
  float Val = analogRead(mesurePin);
  float voltage = Val * (5.0 / 1023.0);

  char* Ohm = " Ohm";
  char* kOhm = " kOhm";
  char* MOhm = " MOhm";

  if (voltage == 0) {
    lcd_setCursor(0, 0);
    char* errr = "Placez une resistance";
    lcd_print(errr);
  } else {
    r = (rfR * (5.0 - voltage)) / voltage;
    lcd_setCursor(0, 0);
    char* ra = " R = ";
    lcd_print(ra);

    if (r < 1000) {
      floatToStr(r, buffer);
      lcd_print(buffer);           
      lcd_print(Ohm);
    } else if (r < 1000000) {
      floatToStr(r / 1000.0, buffer);
      lcd_print(buffer);           
      lcd_print(kOhm);
    } else if (r < 10000000) {
      floatToStr(r / 1000000.0, buffer);
      lcd_print(buffer);           
      lcd_print(MOhm);
    } else {
      char* T = "Trop grande R !";
      lcd_print(T);
    }
  }
}
