#include "button.h"

volatile uint8_t brightness = 50;

// button 1  -> PC6
// button 2  -> PC5
// button 3  -> PC4
// button 4  -> PC3

void Buttons_init()
    {
        DDRC &= ~((1<<3)|(1<<4)|(1<<5)|(1<<6)); // input 3,4,5,6,
        PORTC |= (1<<3)|(1<<4)|(1<<5)|(1<<6); //up

        DDRD |= (1<<6);  // snd pin to output
		PORTD |= (1<<6); // pull up 

    }

// Добавлен отладочный вывод и проверка настройки пинов
void Buttons_Handler()
{
    // press button 1 
    if (Debounce(6)) Edit_LCD_bright(); // +25% brightness

   // press button 2 
    if (Debounce(5)) PORTD ^= (1 << 6); // invert pin sound
    
   
}


void Edit_LCD_bright() // яркость дисплея 
    {             // изменяет по кругу % скважности ШИМ на PB3
        brightness = brightness + 25;   
        if (brightness >= 110) brightness = 0;   
        OCR0 = proc2num(brightness);
    } 

int Debounce(uint8_t pin){ // обработка нажатия кнопки (дребезг + состояние)

static uint8_t current_state[8] = {[0 ... 7] = RELEASED}; 
// стартовые состояния "отпущено"
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
            return 0;
            }
        }
    break;

    default:
        current_state[pin] = RELEASED;
    break;

    }
return 0;
}




