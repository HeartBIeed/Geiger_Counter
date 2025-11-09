#include "button.h"

volatile int light = 25;


void buttons_init()
    {
        DDRC = 0b10000000; // input
        PORTC |= (1<<6)|(1<<5); //up
        PORTC &= ~(1<<7);

        DDRB |= (1<<2); // out
        PORTB |= (1<<2); // up
    }

// Добавлен отладочный вывод и проверка настройки пинов
void buttons()
{
    // press button 1 (to PC6)
    if (debounce(6)) edit_light(); // +25% brightness

    // press button 2 (to PC5)
    if (debounce(5)) PORTC ^= (1 << 7); // invert pin sound

    // press button 3 (to PC)
    //if (debounce(4)) { }

    // press button 4 (to PC)
    //if (debounce(3)) { }

    else asm("nop");
}

void edit_light() // яркость дисплея 
    {             // изменяет по кругу % скважности ШИМ на PB3
        light = light + 25;   
        if (light >= 110) light = 0;   

    } 


int debounce(uint8_t pin) // обработка нажатия кнопки (дребезг + состояние)
    {

    static uint8_t current_state[8] = {[0 ... 7] = RELEASED}; // стартовые состояния "отпущено"
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




