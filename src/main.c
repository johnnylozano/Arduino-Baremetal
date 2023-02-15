#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
    // Initialize LED Pin as output
    DDRB |= (1 << PB5);
    PORTB &= ~(1 << PB5);

    // Initialize ADC Pin as input
    DDRF &= ~(1 << PF0);
    PORTF &= ~(1 << PF0);

    // Set up Timer/Counter 1 for Fast PWM mode
    TCCR1A |= (1 << WGM10) | (1 << WGM11) | (1 << COM1A1);
    TCCR1B |= (1 << CS10);

    // Set TOP value for Timer/Counter 1
    ICR1 = 0xFFFF;

    while (1)
    {
        // Read the analog value from ADC Pin
        ADMUX = (1 << REFS0) | PF0;
        ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
        ADCSRA |= (1 << ADSC);
        while (ADCSRA & (1 << ADSC))
            ;
        uint16_t val = ADC;

        // Set the duty cycle for the PWM signal on Pin 11
        OCR1A = val;

        // Wait for 10 ms
        _delay_ms(10);
    }

    return 0;
}
