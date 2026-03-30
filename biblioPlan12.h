#include <Nestor.h>

#define SCL PIN_C3
#define SDA PIN_C4
#define String char*
#define BACKLIGHT 0x08

#define LCD_ADDR (0x3F << 1)
#use rs232(baud=9600, xmit=PIN_C6, rcv=PIN_C7)

void cursor();
void start();  
void stop();  
void write(uint8_t data); 
void lcd_pulse(uint8_t data);
void lcd_command(uint8_t cmd);
void lcd_send(uint8_t data, bool mode);
void lcd_write(char c);
void lcd_print(char* str);
int trans(String str); 
void lcd_setcursor(uint8_t row, uint8_t col);

void start() {
  digitalWrite(SDA, HIGH);
  digitalWrite(SCL, HIGH);
  delayMicroseconds(5);
  digitalWrite(SDA, LOW);
  delayMicroseconds(5);
  digitalWrite(SCL, LOW);
}

void stop() {
  digitalWrite(SDA, LOW);
  digitalWrite(SCL, HIGH);
  delayMicroseconds(5);
  digitalWrite(SDA, HIGH);
  delayMicroseconds(5);
}

void write(uint8_t data) {
  for (int i = 0; i < 8; i++) {
    digitalWrite(SDA, (data & 0x80) ? HIGH : LOW);
    digitalWrite(SCL, HIGH);
    delayMicroseconds(5);
    digitalWrite(SCL, LOW);
    data <<= 1;
  }
  input(SDA);
  digitalWrite(SCL, HIGH);
  delayMicroseconds(5);
  digitalWrite(SCL, LOW);
}

void lcd_pulse(uint8_t data) {
  start();
  write(0x27 << 1);       
  write((data | 0x04 |BACKLIGHT ));    
  write(data & ~0x04 | BACKLIGHT);   
  stop();
  delayMicroseconds(50);
}

void lcd_send(uint8_t data, bool mode) {
  uint8_t h = (data & 0xF0) | (mode ? 0x01 : 0x00);
  uint8_t l = ((data << 4) & 0xF0) | (mode ? 0x01 : 0x00);

  lcd_pulse(h);
  lcd_pulse(l);
}

void lcd_command(uint8_t cmd) {
  lcd_send(cmd, false);
}

void lcd_write(char c) {
  lcd_send(c, true);
}

void lcd_print(char* str) {
  while (*str) {
    lcd_write(*str++);
  }
}

void lcd_init() {
  set_tris_c(0b00011000); 
  delay_ms(50);          
  lcd_command(0x02);      
  lcd_command(0x28);      
  lcd_command(0x0C);      
  lcd_command(0x06);     
  lcd_command(0x01);     
  delay_ms(200);         
}

void lcd_setcursor(uint8_t row, uint8_t col) {
  uint8_t address;
  if (row == 0) {
    address = 0x00 + col;
  } else if (row == 1) {
    address = 0x40 + col;
  }
  lcd_command(0x80 | address);
}

int trans(String str) {
  return strlen(str);
}

void porte(int pin0, int pin1) {
  digitalWrite(pin1, 1);
  digitalWrite(pin0, 0);
  delay(500);
  digitalWrite(pin1, 0);
}

