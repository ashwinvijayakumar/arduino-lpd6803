# Arduino LPD8266
Arduino library for LPD6803 based LED strip. LPD6803 is a serial shift register based LED controller, so this library uses Arduino's HW SPI to shift data through the strips as against bit-banging GPIOs. This frees up the CPU from havng to bit-bang time-specific square pulses as in the case of WS2812.
