#ifndef Keyboard_Functions_h
#define Keyboard_Functions_h
#include <Arduino.h>

#include <Keyboard.h>     // Библиотека для эмуляции клавиатуры ПК

#include <Keypad.h>       // Библиотека для работы клавиатуры с Arduino
static char keys[4][4] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
static byte rowPins[4] = {2, 3, 4, 5}; byte colPins[4] = {6, 7, 8, 9};
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, 4, 4); 

#include <GyverTM1637.h>  // Библиотека для работы дисплея с Arduino
GyverTM1637 disp(/*CLK*/A0, /*DIO*/A1);

#include "Button.h"
EncButton<EB_TICK, 10> btn;

#include "Parser.h"       // Библиотека парсера
#include "AsyncStream.h"  // Асинхронное чтение сериал
AsyncStream<50> serial(&Serial, ';');   // Указываем обработчик и стоп символ

#include <EEPROM.h>

// Массив, содержащий названия режимов
static byte banners[][4] = { 
  { _1, 0x40, 0x40, 0x40 },     //       (0)
  { _2, 0x40, 0x40, 0x40 },     //       (1)
  { _3, 0x40, 0x40, 0x40 },     //       (2)
};

static byte* shortcutsKeys[][16][3] = {
  { {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, 
    {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, 
    {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, 
    {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0} },
  { {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, 
    {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, 
    {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, 
    {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0} },
  { {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, 
    {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, 
    {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, 
    {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0} } }; 



/* СЛУЖЕБНЫЕ ФУНКЦИИ */

// 
void pushKeys(int key1, int key2 = 0, int key3 = 0, int key4 = 0) {
  Keyboard.press(key1); delay(20);
  if (key2 != 0 && key2 != 255) Keyboard.press(key2); delay(20);
  if (key3 != 0 && key3 != 255) Keyboard.press(key3); delay(20);
  if (key4 != 0 && key4 != 255) Keyboard.press(key4); delay(20);
  Keyboard.releaseAll();
}

/*
// 
void pushKeys(String inputStr, bool modeKey = 0) {
  if (modeKey == false) Keyboard.print(inputStr);
  else if (modeKey == true) Keyboard.println(inputStr);
}
*/

/*
// 
void pushKeys(const char *inputStr, bool modeKey = 0) {
  if (modeKey == false) Keyboard.print(inputStr);
  else if (modeKey == true) Keyboard.println(inputStr);
}
*/

void sendDataToEEPROM() {
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 16; ++j) {
      for (int k = 0; k < 3; ++k) { EEPROM.update(i*48+j*3+k, shortcutsKeys[i][j][k]); } }
  }
}

void getDataFromEEPROM() {
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 16; ++j) {
      for (int k = 0; k < 3; ++k) { shortcutsKeys[i][j][k] = EEPROM[i*48+j*3+k]; } }
  }
}

//
void pressShortcuts(int num, char key) {
  disp.displayByte(banners[num][0], banners[num][1], banners[num][2], banners[num][3]);
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

void parsing() {
  if (serial.available()) {
    Parser data(serial.buf, ',');  // отдаём парсеру
    int ints[10];           // массив для данных
    data.parseInts(ints);   // парсим в него

    switch ((char)ints[1]) {
      case '1': 
        shortcutsKeys[ints[0]-(int)'1'][0][0] = ints[2]; shortcutsKeys[ints[0]-(int)'1'][0][1] = ints[3]; shortcutsKeys[ints[0]-(int)'1'][0][2] = ints[4]; 
        break;
      case '2': 
        shortcutsKeys[ints[0]-(int)'1'][1][0] = ints[2]; shortcutsKeys[ints[0]-(int)'1'][1][1] = ints[3]; shortcutsKeys[ints[0]-(int)'1'][1][2] = ints[4]; 
        break;
      case '3': 
        shortcutsKeys[ints[0]-(int)'1'][2][0] = ints[2]; shortcutsKeys[ints[0]-(int)'1'][2][1] = ints[3]; shortcutsKeys[ints[0]-(int)'1'][2][2] = ints[4]; 
        break;
      case 'A':  
        shortcutsKeys[ints[0]-(int)'1'][3][0] = ints[2]; shortcutsKeys[ints[0]-(int)'1'][3][1] = ints[3]; shortcutsKeys[ints[0]-(int)'1'][3][2] = ints[4]; 
        break;
      case '4':  
        shortcutsKeys[ints[0]-(int)'1'][4][0] = ints[2]; shortcutsKeys[ints[0]-(int)'1'][4][1] = ints[3]; shortcutsKeys[ints[0]-(int)'1'][4][2] = ints[4]; 
        break;
      case '5':
        shortcutsKeys[ints[0]-(int)'1'][5][0] = ints[2]; shortcutsKeys[ints[0]-(int)'1'][5][1] = ints[3]; shortcutsKeys[ints[0]-(int)'1'][5][2] = ints[4]; 
        break;
      case '6':  
        shortcutsKeys[ints[0]-(int)'1'][6][0] = ints[2]; shortcutsKeys[ints[0]-(int)'1'][6][1] = ints[3]; shortcutsKeys[ints[0]-(int)'1'][6][2] = ints[4]; 
        break;
      case 'B':  
        shortcutsKeys[ints[0]-(int)'1'][7][0] = ints[2]; shortcutsKeys[ints[0]-(int)'1'][7][1] = ints[3]; shortcutsKeys[ints[0]-(int)'1'][7][2] = ints[4]; 
        break;
      case '7':  
        shortcutsKeys[ints[0]-(int)'1'][8][0] = ints[2]; shortcutsKeys[ints[0]-(int)'1'][8][1] = ints[3]; shortcutsKeys[ints[0]-(int)'1'][8][2] = ints[4]; 
        break;
      case '8':
        shortcutsKeys[ints[0]-(int)'1'][9][0] = ints[2]; shortcutsKeys[ints[0]-(int)'1'][9][1] = ints[3]; shortcutsKeys[ints[0]-(int)'1'][9][2] = ints[4]; 
        break;
      case '9':  
        shortcutsKeys[ints[0]-(int)'1'][10][0] = ints[2]; shortcutsKeys[ints[0]-(int)'1'][10][1] = ints[3]; shortcutsKeys[ints[0]-(int)'1'][10][2] = ints[4]; 
        break;
      case 'C': 
        shortcutsKeys[ints[0]-(int)'1'][11][0] = ints[2]; shortcutsKeys[ints[0]-(int)'1'][11][1] = ints[3]; shortcutsKeys[ints[0]-(int)'1'][11][2] = ints[4]; 
        break;
      case '*': 
        shortcutsKeys[ints[0]-(int)'1'][12][0] = ints[2]; shortcutsKeys[ints[0]-(int)'1'][12][1] = ints[3]; shortcutsKeys[ints[0]-(int)'1'][12][2] = ints[4]; 
        break;
      case '0':  
        shortcutsKeys[ints[0]-(int)'1'][13][0] = ints[2]; shortcutsKeys[ints[0]-(int)'1'][13][1] = ints[3]; shortcutsKeys[ints[0]-(int)'1'][13][2] = ints[4]; 
        break;
      case '#': 
        shortcutsKeys[ints[0]-(int)'1'][14][0] = ints[2]; shortcutsKeys[ints[0]-(int)'1'][14][1] = ints[3]; shortcutsKeys[ints[0]-(int)'1'][14][2] = ints[4]; 
        break;
      case 'D': 
        shortcutsKeys[ints[0]-(int)'1'][15][0] = ints[2]; shortcutsKeys[ints[0]-(int)'1'][15][1] = ints[3]; shortcutsKeys[ints[0]-(int)'1'][15][2] = ints[4]; 
        break;
    } 

    sendDataToEEPROM();
  }
}


#endif

//
