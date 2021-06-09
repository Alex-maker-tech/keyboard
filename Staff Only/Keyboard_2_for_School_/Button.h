/*
    Ультра лёгкая и быстрая библиотека для энкодера, энкодера с кнопкой или просто кнопки
    Документация:
    GitHub: https://github.com/GyverLibs/EncButton
    
    AlexGyver, alex@alexgyver.ru
    https://alexgyver.ru/
    MIT License
*/

// [05.06.2021] Обрезана для удобства работы

#ifndef Button_h
#define Button_h

// =========== НАСТРОЙКИ (можно передефайнить из скетча) ============
#define _EB_FAST 30     // таймаут быстрого поворота
#define _EB_DEB 80      // дебаунс кнопки
#define _EB_HOLD 1000   // таймаут удержания кнопки
#define _EB_STEP 500    // период срабатывания степ
#define _EB_CLICK 400	// таймаут накликивания

// =========== НЕ ТРОГАЙ ============
#include <Arduino.h>
#include "FastIO.h"
// флаг макро
#define _setFlag(x) (flags |= 1 << x)
#define _clrFlag(x) (flags &= ~(1 << x))
#define _readFlag(x) ((flags >> x) & 1)

#ifndef EB_FAST
#define EB_FAST _EB_FAST
#endif
#ifndef EB_DEB
#define EB_DEB _EB_DEB
#endif
#ifndef EB_HOLD
#define EB_HOLD _EB_HOLD
#endif
#ifndef EB_STEP
#define EB_STEP _EB_STEP
#endif
#ifndef EB_CLICK
#define EB_CLICK _EB_CLICK
#endif

enum eb_callback {
    TURN_HANDLER,
    RIGHT_HANDLER,
    LEFT_HANDLER,
    RIGHT_H_HANDLER,
    LEFT_H_HANDLER,
    CLICK_HANDLER,
    HOLDED_HANDLER,
    STEP_HANDLER,
    HOLD_HANDLER,
    CLICKS_HANDLER,
    PRESS_HANDLER,
    RELEASE_HANDLER,
};

#define EB_TICK 0
#define EB_CALLBACK 1

#define EB_NO_PIN 255

#define VIRT_ENC 254
#define VIRT_ENCBTN 253
#define VIRT_BTN 252

// класс
template < uint8_t _EB_MODE, uint8_t _S1 = EB_NO_PIN, uint8_t _S2 = EB_NO_PIN, uint8_t _KEY = EB_NO_PIN >
class EncButton {
public:
    EncButton(byte mode = INPUT) { if (mode == INPUT_PULLUP) pullUp(); }
    
    // подтянуть пины внутренней подтяжкой
    void pullUp() {
        if (_S1 < 252) {                    // реальное устройство
            if (_S2 == EB_NO_PIN) {         // обычная кнопка
                pinMode(_S1, INPUT_PULLUP);
            } else if (_KEY == EB_NO_PIN) { // энк без кнопки
                pinMode(_S1, INPUT_PULLUP);
                pinMode(_S2, INPUT_PULLUP);
            } else {                        // энк с кнопкой
                pinMode(_S1, INPUT_PULLUP);
                pinMode(_S2, INPUT_PULLUP);
                pinMode(_KEY, INPUT_PULLUP);
            }
        }
    }
    
    // тикер, вызывать как можно чаще или в прерывании
    // вернёт отличное от нуля значение, если произошло какое то событие
    uint8_t tick(uint8_t s1 = 0, uint8_t s2 = 0, uint8_t key = 0) {
        uint32_t thisMls = millis();
        uint32_t debounce = thisMls - _debTimer;
        
        // обработка кнопки (компилятор вырежет блок если не используется)
        // если S2 не указан (кнопка) или указан KEY или выбран вирт. энкодер с кнопкой или кнопка
        if ((_S1 < 252 && _S2 == EB_NO_PIN) || _KEY != EB_NO_PIN || _S1 == VIRT_BTN || _S1 == VIRT_ENCBTN) {
            if (_S1 < 252 && _S2 == EB_NO_PIN) _btnState = !fastRead(_S1);      // обычная кнопка
            if (_KEY != EB_NO_PIN) _btnState = !fastRead(_KEY);                 // энк с кнопкой
            if (_S1 == VIRT_BTN) _btnState = s1;                                // вирт кнопка
            if (_S1 == VIRT_ENCBTN) _btnState = key;                            // вирт энк с кнопкой

            if (_btnState) {                                                	// кнопка нажата
                if (!_readFlag(3)) {                                          	// и не была нажата ранее
                    if (debounce > EB_DEB) {                                   	// и прошел дебаунс
                        _setFlag(3);                                            // флаг кнопка была нажата
                        _debTimer = thisMls;                                    // сброс таймаутов
                        EBState = 8;                                           	// кнопка нажата
                    }
                    if (debounce > EB_CLICK) {									// кнопка нажата после EB_CLICK
                        clicks = 0;												// сбросить счётчик и флаг кликов
                        flags &= ~0b01100000;
                    }
                } else {                                                      	// кнопка уже была нажата
                    if (!_readFlag(4)) {                                        // и удержание ещё не зафиксировано
                        if (debounce < EB_HOLD) {                              	// прошло меньше удержания
                            if (EBState != 0 && EBState != 8) _setFlag(2);      // но энкодер повёрнут! Запомнили
                        } else {                                                // прошло больше времени удержания
                            if (!_readFlag(2)) {                                // и энкодер не повёрнут
                                EBState = 6;                                   	// значит это удержание (сигнал)
                                _setFlag(4);                                    // запомнили что удерживается
                                _debTimer = thisMls;                            // сброс таймаута
                            }
                        }
                    } else {                                                    // удержание зафиксировано
                        if (debounce > EB_STEP) {                              	// таймер степа
                            EBState = 7;                                       	// сигналим
                            _debTimer = thisMls;                                // сброс таймаута
                        }
                    }
                }
            } else {                                                        	// кнопка не нажата
                if (_readFlag(3)) {                                           	// но была нажата
                    if (debounce > EB_DEB && !_readFlag(4) && !_readFlag(2)) {	// энкодер не трогали и не удерживали - это клик
                        EBState = 5;
                        clicks++;
                    } else EBState = 9;                                         // кнопка отпущена
                    flags &= ~0b00011100;                                       // clear 2 3 4                    
                    _debTimer = thisMls;                                        // сброс таймаута
                } else if (clicks > 0 && debounce > EB_CLICK && !_readFlag(5)) flags |= 0b01100000;	 // флаг на клики
            }
        }
        if (_EB_MODE) {
            if (*_callback[0] && isTurn()) _callback[0]();
            switch (EBState) {
            case 1: if (*_callback[1]) _callback[1](); break;	// isRight			
            case 2: if (*_callback[2]) _callback[2](); break;	// isLeft			
            case 3: if (*_callback[3]) _callback[3](); break;	// isRightH			
            case 4: if (*_callback[4]) _callback[4](); break;	// isLeftH			
            case 5: if (*_callback[5]) _callback[5](); break;	// isClick			
            case 6: if (*_callback[6]) _callback[6](); break;	// isHolded			
            case 7: if (*_callback[7]) _callback[7](); break;	// isStep
            case 8: if (*_callback[11]) _callback[11](); break;	// isPress			
            case 9: if (*_callback[12]) _callback[12](); break;	// isRelease
            }
            EBState = 0;
            if (*_callback[8] && _readFlag(4)) _callback[8](); 	// isHold
            if (_readFlag(6)) {			
                if (*_callback[9]) _callback[9]();				// clicks
                if (*_callback[10] && clicks == _amount) _callback[10]();
                _clrFlag(6);
            }		
        }
        return EBState;
    }

    // обработка энкодера (обрезанная)
    bool isTurn() {
        if (_readFlag(0)) {
            _clrFlag(0);
            return true;
        } return false;    
    }
    
    // обработка кнопки
    bool isPress() { return checkState(8); }
    bool isRelease() { return checkState(9); }
    bool isClick() { return checkState(5); }
    bool isHolded() { return checkState(6); }
    bool isHold() { return _readFlag(4); }
    bool isStep() { return checkState(7); }
    bool state() { return !fastRead(_S1); }
    bool hasClicks(uint8_t numClicks) { if (clicks == numClicks && _readFlag(6)) { _clrFlag(6); return 1; } return 0; }
    uint8_t hasClicks() { if (_readFlag(6)) {_clrFlag(6); return clicks; } return 0; }
    
    // счётчик энкодера
    int counter = 0;
    
    // счётчик кликов
    uint8_t clicks = 0;

private:
    bool checkState(uint8_t val) { if (EBState == val) { EBState = 0; return 1; } return 0; }
    uint32_t _debTimer = 0;
    uint8_t _lastState = 0, EBState = 0;
    bool _btnState = 0, _encRST = 0;
    uint8_t flags = 0;
    

    uint8_t _dir = 0;
    void (*_callback[_EB_MODE ? 13 : 0])() = {};
    uint8_t _amount = 0;
};

#endif
