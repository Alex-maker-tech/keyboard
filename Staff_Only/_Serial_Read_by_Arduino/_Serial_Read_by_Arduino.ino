#include "Parser.h"       // библиотека парсера
#include "AsyncStream.h"  // асинхронное чтение сериал
AsyncStream<50> serial(&Serial, ';');   // указываем обработчик и стоп символ

#include <Keyboard.h>

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels
#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

byte shortcutsKeys[][16][3] = {
  { {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0} },
  { {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0} },
  { {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0} } }; 

void pushKeys(int key1, int key2 = 0, int key3 = 0, int key4 = 0) {
  Keyboard.press(key1);
  if (key2 != 0) Keyboard.press(key2);
  if (key3 != 0) Keyboard.press(key3);
  if (key4 != 0) Keyboard.press(key4);
  Keyboard.releaseAll();
}

void pushKeys(String inputStr, bool modeKey = 0) {
  if (modeKey == false) Keyboard.print(inputStr);
  else if (modeKey == true) Keyboard.println(inputStr);
}

void pressShortcuts(int num, char key) {
  switch (key) {
    case '1': pushKeys(shortcutsKeys[num][0][0],  shortcutsKeys[num][0][1],  shortcutsKeys[num][0][2]);  break;
    case '2': pushKeys(shortcutsKeys[num][1][0],  shortcutsKeys[num][1][1],  shortcutsKeys[num][1][2]);  break;
    case '3': pushKeys(shortcutsKeys[num][2][0],  shortcutsKeys[num][2][1],  shortcutsKeys[num][2][2]);  break;
    case 'A': pushKeys(shortcutsKeys[num][3][0],  shortcutsKeys[num][3][1],  shortcutsKeys[num][3][2]);  break;
    case '4': pushKeys(shortcutsKeys[num][4][0],  shortcutsKeys[num][4][1],  shortcutsKeys[num][4][2]);  break;
    case '5': pushKeys(shortcutsKeys[num][5][0],  shortcutsKeys[num][5][1],  shortcutsKeys[num][5][2]);  break;
    case '6': pushKeys(shortcutsKeys[num][6][0],  shortcutsKeys[num][6][1],  shortcutsKeys[num][6][2]);  break;
    case 'B': pushKeys(shortcutsKeys[num][7][0],  shortcutsKeys[num][7][1],  shortcutsKeys[num][7][2]);  break;
    case '7': pushKeys(shortcutsKeys[num][8][0],  shortcutsKeys[num][8][1],  shortcutsKeys[num][8][2]);  break;
    case '8': pushKeys(shortcutsKeys[num][9][0],  shortcutsKeys[num][9][1],  shortcutsKeys[num][9][2]);  break;
    case '9': pushKeys(shortcutsKeys[num][10][0], shortcutsKeys[num][10][1], shortcutsKeys[num][10][2]); break;
    case 'C': pushKeys(shortcutsKeys[num][11][0], shortcutsKeys[num][11][1], shortcutsKeys[num][11][2]); break;
    case '*': pushKeys(shortcutsKeys[num][12][0], shortcutsKeys[num][12][1], shortcutsKeys[num][12][2]); break;
    case '0': pushKeys(shortcutsKeys[num][13][0], shortcutsKeys[num][13][1], shortcutsKeys[num][13][2]); break;
    case '#': pushKeys(shortcutsKeys[num][14][0], shortcutsKeys[num][14][1], shortcutsKeys[num][14][2]); break;
    case 'D': pushKeys(shortcutsKeys[num][15][0], shortcutsKeys[num][15][1], shortcutsKeys[num][15][2]); break;
  }
}

void setup() {
  Serial.begin(115200);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);

  display.clearDisplay();
  display.display();
}


void loop() {
  parsing();
}


void printOnDisplay(int i, int j) {
  char charA = (char) shortcutsKeys[i][j][0]; char charB = (char) shortcutsKeys[i][j][1]; char charC = (char) shortcutsKeys[i][j][2];
  display.setTextSize(1); display.setTextColor(SSD1306_WHITE);
  display.println(/*"\n" +*/ String( charA ) + "..." 
                           + String( charB ) + "..."
                           + String( charC ) );
  display.display(); delay(750);
}


void convertData() {
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 16; ++j) {
      for (int k = 0; k < 3; ++k) {
        if ((shortcutsKeys[i][j][k] >= 65 && shortcutsKeys[i][j][k] <= 90) || (shortcutsKeys[i][j][k] >= 48 && shortcutsKeys[i][j][k] <= 57)) {
          shortcutsKeys[i][j][k] = (char)shortcutsKeys[i][j][k];
        }
      }
    }
  }
}


void parsing() {
  static int i = 0;
  if (serial.available()) {
    Parser data(serial.buf, ',');  // отдаём парсеру
    int ints[10];           // массив для данных
    data.parseInts(ints);   // парсим в него

    display.clearDisplay(); display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE); display.setCursor(0, 0);
    display.println(String(ints[2]) + " " + String(ints[3]) + " " + String(ints[4]) + "  " + String(i % 48 + 1)); ++i;
    display.display();

    switch ((char)ints[1]) {
      case '1': 
        shortcutsKeys[ints[0]-(int)'1'][0][0] = ints[2]; shortcutsKeys[ints[0]-(int)'1'][0][1] = ints[3]; shortcutsKeys[ints[0]-(int)'1'][0][2] = ints[4]; 
        convertData(); printOnDisplay(ints[0]-(int)'1', 0);
        break;
      case '2': 
        shortcutsKeys[ints[0]-(int)'1'][1][0] = ints[2]; shortcutsKeys[ints[0]-(int)'1'][1][1] = ints[3]; shortcutsKeys[ints[0]-(int)'1'][1][2] = ints[4]; 
        convertData(); printOnDisplay(ints[0]-(int)'1', 1);
        break;
      case '3': 
        shortcutsKeys[ints[0]-(int)'1'][2][0] = ints[2]; shortcutsKeys[ints[0]-(int)'1'][2][1] = ints[3]; shortcutsKeys[ints[0]-(int)'1'][2][2] = ints[4]; 
        convertData(); printOnDisplay(ints[0]-(int)'1', 2);
        break;
      case 'A':  
        shortcutsKeys[ints[0]-(int)'1'][3][0] = ints[2]; shortcutsKeys[ints[0]-(int)'1'][3][1] = ints[3]; shortcutsKeys[ints[0]-(int)'1'][3][2] = ints[4]; 
        convertData(); printOnDisplay(ints[0]-(int)'1', 3);
        break;
      case '4':  
        shortcutsKeys[ints[0]-(int)'1'][4][0] = ints[2]; shortcutsKeys[ints[0]-(int)'1'][4][1] = ints[3]; shortcutsKeys[ints[0]-(int)'1'][4][2] = ints[4]; 
        convertData(); printOnDisplay(ints[0]-(int)'1', 4);
        break;
      case '5':
        shortcutsKeys[ints[0]-(int)'1'][5][0] = ints[2]; shortcutsKeys[ints[0]-(int)'1'][5][1] = ints[3]; shortcutsKeys[ints[0]-(int)'1'][5][2] = ints[4]; 
        convertData(); printOnDisplay(ints[0]-(int)'1', 5);
        break;
      case '6':  
        shortcutsKeys[ints[0]-(int)'1'][6][0] = ints[2]; shortcutsKeys[ints[0]-(int)'1'][6][1] = ints[3]; shortcutsKeys[ints[0]-(int)'1'][6][2] = ints[4]; 
        convertData(); printOnDisplay(ints[0]-(int)'1', 6);
        break;
      case 'B':  
        shortcutsKeys[ints[0]-(int)'1'][7][0] = ints[2]; shortcutsKeys[ints[0]-(int)'1'][7][1] = ints[3]; shortcutsKeys[ints[0]-(int)'1'][7][2] = ints[4]; 
        convertData(); printOnDisplay(ints[0]-(int)'1', 7);
        break;
      case '7':  
        shortcutsKeys[ints[0]-(int)'1'][8][0] = ints[2]; shortcutsKeys[ints[0]-(int)'1'][8][1] = ints[3]; shortcutsKeys[ints[0]-(int)'1'][8][2] = ints[4]; 
        convertData(); printOnDisplay(ints[0]-(int)'1', 8);
        break;
      case '8':
        shortcutsKeys[ints[0]-(int)'1'][9][0] = ints[2]; shortcutsKeys[ints[0]-(int)'1'][9][1] = ints[3]; shortcutsKeys[ints[0]-(int)'1'][9][2] = ints[4]; 
        convertData(); printOnDisplay(ints[0]-(int)'1', 9);
        break;
      case '9':  
        shortcutsKeys[ints[0]-(int)'1'][10][0] = ints[2]; shortcutsKeys[ints[0]-(int)'1'][10][1] = ints[3]; shortcutsKeys[ints[0]-(int)'1'][10][2] = ints[4]; 
        convertData(); printOnDisplay(ints[0]-(int)'1', 10);
        break;
      case 'C': 
        shortcutsKeys[ints[0]-(int)'1'][11][0] = ints[2]; shortcutsKeys[ints[0]-(int)'1'][11][1] = ints[3]; shortcutsKeys[ints[0]-(int)'1'][11][2] = ints[4]; 
        convertData(); printOnDisplay(ints[0]-(int)'1', 11);
        break;
      case '*': 
        shortcutsKeys[ints[0]-(int)'1'][12][0] = ints[2]; shortcutsKeys[ints[0]-(int)'1'][12][1] = ints[3]; shortcutsKeys[ints[0]-(int)'1'][12][2] = ints[4]; 
        convertData(); printOnDisplay(ints[0]-(int)'1', 12);
        break;
      case '0':  
        shortcutsKeys[ints[0]-(int)'1'][13][0] = ints[2]; shortcutsKeys[ints[0]-(int)'1'][13][1] = ints[3]; shortcutsKeys[ints[0]-(int)'1'][13][2] = ints[4]; 
        convertData(); printOnDisplay(ints[0]-(int)'1', 13);
        break;
      case '#': 
        shortcutsKeys[ints[0]-(int)'1'][14][0] = ints[2]; shortcutsKeys[ints[0]-(int)'1'][14][1] = ints[3]; shortcutsKeys[ints[0]-(int)'1'][14][2] = ints[4]; 
        convertData(); printOnDisplay(ints[0]-(int)'1', 14);
        break;
      case 'D': 
        shortcutsKeys[ints[0]-(int)'1'][15][0] = ints[2]; shortcutsKeys[ints[0]-(int)'1'][15][1] = ints[3]; shortcutsKeys[ints[0]-(int)'1'][15][2] = ints[4]; 
        convertData(); printOnDisplay(ints[0]-(int)'1', 15);
        break;
    }
    convertData();
  }
}




/*  */
