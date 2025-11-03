#include "button.h"

volatile int light = 25;


void buttons_init()
    {
        DDRC |= 0b10000000;
        PORTC |= 0b11111100;
    }

void buttons()
    {

        // press button 1 (to PC6)
        if (debounce(6)) edit_light(); // +25% brightness

        // press button 2 (to PC)
        if (debounce(2)) PORTC ^= (1<<7); // invert pin sound



        // press button 3 (to PC)
        //if (debounce(4)) { }

        // press button 4 (to PC)
        //if (debounce(3)) { }


    }

void edit_light() // яркость дисплея 
    {             // изменяет по кругу % скважности ШИМ на PB3
        light = light + 25;   

        if (light >= 110)
        {
            light = 0;   

        }
    } 


uint8_t debounce(uint8_t pin) // обработка нажатия кнопки (дребезг + состояние)
    {

    static uint8_t current_state[8] = {RELEASED}; // стартовые состояния "отпущено"
                                                  // массив для 8 кнопок
    switch (current_state[pin])
        {

        case RELEASED:
            if (!(BUTPIN & (1 << pin))) // если кнопка нажата (т.е. притянута к 0)
            {
            
            _delay_ms(20);

                if (!(BUTPIN & (1 << pin)))
                    {
                    current_state[pin] = PRESSED; // состояние "нажато"
                    return 1;

                    }
            }
        break;

        case PRESSED:
            if (BUTPIN & (1 << pin)) // если кнопка отпущена (т.е. уровень  VCС)
            {
            
            _delay_ms(20);

                if (BUTPIN & (1 << pin)) 
                    {
                        current_state[pin] = RELEASED; // состояние "отпущено"

                    }
            }
        break;

        default:

        current_state[pin] = RELEASED;
        break;
        }
        
    return 0;
    }




