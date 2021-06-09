// Быстрый IO для AVR (для остальных будет digitalxxxxx)
// v1.0

#ifndef FastIO_h
#define FastIO_h
#include <Arduino.h>

bool fastRead(const uint8_t pin);				// быстрое чтение пина
// void fastWrite(const uint8_t pin, bool val);	// быстрая запись
// uint8_t fastShiftIn(uint8_t dataPin, uint8_t clockPin, uint8_t bitOrder); 				// быстрый shiftIn
// void fastShiftOut(uint8_t dataPin, uint8_t clockPin, uint8_t bitOrder, uint8_t data);	// быстрый shiftOut

// ================================================================
bool fastRead(const uint8_t pin) {
#if defined(__AVR_ATmega328P__) || defined(__AVR_ATmega168__)
    if (pin < 8) return bitRead(PIND, pin);
    else if (pin < 14) return bitRead(PINB, pin - 8);
    else if (pin < 20) return bitRead(PINC, pin - 14);

#elif defined(__AVR_ATtiny85__) || defined(__AVR_ATtiny13__)
    return bitRead(PINB, pin);

#elif defined(AVR)
    uint8_t *_pin_reg = portInputRegister(digitalPinToPort(pin));
    uint8_t _bit_mask = digitalPinToBitMask(pin);
    return bool(*_pin_reg & _bit_mask);

#else
    return digitalRead(pin);

#endif
    return 0;
}

/*
void fastWrite(const uint8_t pin, bool val) {
#if defined(__AVR_ATmega328P__) || defined(__AVR_ATmega168__)
    if (pin < 8) bitWrite(PORTD, pin, val);
    else if (pin < 14) bitWrite(PORTB, (pin - 8), val);
    else if (pin < 20) bitWrite(PORTC, (pin - 14), val);

#elif defined(__AVR_ATtiny85__) || defined(__AVR_ATtiny13__)
    bitWrite(PORTB, pin, val);

#elif defined(AVR)
    uint8_t *_port_reg = portInputRegister(digitalPinToPort(pin));
    uint8_t _bit_mask = digitalPinToBitMask(pin);
    _port_reg = portOutputRegister(digitalPinToPort(pin));
    _bit_mask = digitalPinToBitMask(pin);
    if (val) *_port_reg |= _bit_mask;	// HIGH
    else *_port_reg &= ~_bit_mask;		// LOW

#else
    digitalWrite(pin, val);

#endif
}


uint8_t fastShiftIn(uint8_t dataPin, uint8_t clockPin, uint8_t bitOrder) {
#if defined(AVR)
    volatile uint8_t *_clk_port = portOutputRegister(digitalPinToPort(clockPin));
    volatile uint8_t *_dat_port = portInputRegister(digitalPinToPort(dataPin));
    uint8_t _clk_mask = digitalPinToBitMask(clockPin);
    uint8_t _dat_mask = digitalPinToBitMask(dataPin);
    uint8_t data = 0;
    for (uint8_t i = 0; i < 8; i++) {
        *_clk_port |= _clk_mask;
        if (bitOrder == MSBFIRST) {
            data <<= 1;
            if (bool(*_dat_port & _dat_mask)) data |= 1;
        } else {
            data >>= 1;
            if (bool(*_dat_port & _dat_mask)) data |= 1 << 7;
        }
        *_clk_port &= ~_clk_mask;
    }
    return data;
#else
    return shiftIn(dataPin, clockPin, bitOrder);
#endif
}


void fastShiftOut(uint8_t dataPin, uint8_t clockPin, uint8_t bitOrder, uint8_t data) {
#if defined(AVR)
    volatile uint8_t *_clk_port = portOutputRegister(digitalPinToPort(clockPin));
    volatile uint8_t *_dat_port = portOutputRegister(digitalPinToPort(dataPin));
    uint8_t _clk_mask = digitalPinToBitMask(clockPin);
    uint8_t _dat_mask = digitalPinToBitMask(dataPin);
    for (uint8_t i = 0; i < 8; i++)  {
        if (bitOrder == MSBFIRST) {
            if (data & (1 << 7)) *_dat_port |= _dat_mask;
            else *_dat_port &= ~_dat_mask;
            data <<= 1;
        } else {
            if (data & 1) *_dat_port |= _dat_mask;
            else *_dat_port &= ~_dat_mask;
            data >>= 1;
        }
        *_clk_port |= _clk_mask;
        *_clk_port &= ~_clk_mask;
    }
#else
    shiftOut(dataPin, clockPin, bitOrder, data);
#endif
}
*/


#endif
