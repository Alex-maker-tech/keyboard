#include "Parser.h"       // библиотека парсера
#include "AsyncStream.h"  // асинхронное чтение сериал
AsyncStream<50> serial(&Serial, ';');   // указываем обработчик и стоп символ

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels
#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

int shortcutsKeys[][10][3] = {
  { {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0} },
  { {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0} },
  { {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0} } }; 

void setup() {
  Serial.begin(115200);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);

  display.clearDisplay();
  display.display();
}


void loop() {
  parsing();
}

int i = 0;
void parsing() {
  if (serial.available()) {
    Parser data(serial.buf, ',');  // отдаём парсеру
    int ints[10];           // массив для данных
    data.parseInts(ints);   // парсим в него

    display.clearDisplay(); display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE); display.setCursor(0, 0);
    display.println(String(ints[2]) + " " + String(ints[3]) + " " + String(ints[4]) + "  " + String((++i) %30));
    display.display();

    shortcutsKeys[ints[0] - (int)'1'][ints[1] - (int)'0'][0] = ints[2];
    shortcutsKeys[ints[0] - (int)'1'][ints[1] - (int)'0'][1] = ints[3];
    shortcutsKeys[ints[0] - (int)'1'][ints[1] - (int)'0'][2] = ints[4];
    
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.println(/*"\n" +*/ String((char)shortcutsKeys[ints[0] - (int)'1'][ints[1] - (int)'0'][0]) + " " 
                  + String((char)shortcutsKeys[ints[0] - (int)'1'][ints[1] - (int)'0'][1]) + " "
                  + String((char)shortcutsKeys[ints[0] - (int)'1'][ints[1] - (int)'0'][2]));
    display.display();
    delay(750);
    
    switch ((char)ints[0]) {      // свитч по ключу №1
      case '1':
        /*switch (ints[1]) {      // свитч по ключу №2
          case 0:

          break;
          case 1:

          break;
          case 2:

          break;
          case 3:

          break;
          case 4:

          break;
          case 5:

          break;
          case 6:

          break;
          case 7:

          break;
          case 8:

          break;
          case 9:

          break;
        }
      */
        
      break;
      case '2':
        /*switch (ints[1]) {      // свитч по ключу №2
          case 0:

          break;
          case 1:

          break;
          case 2:

          break;
          case 3:

          break;
          case 4:

          break;
          case 5:

          break;
          case 6:

          break;
          case 7:

          break;
          case 8:

          break;
          case 9:

          break;
        }
      */
        
      break;
      case '3':
        /*switch (ints[1]) {      // свитч по ключу №2
          case 0:

          break;
          case 1:

          break;
          case 2:

          break;
          case 3:

          break;
          case 4:

          break;
          case 5:

          break;
          case 6:

          break;
          case 7:

          break;
          case 8:

          break;
          case 9:

          break;
        }
      */
        
      break;
    }
  }
}
