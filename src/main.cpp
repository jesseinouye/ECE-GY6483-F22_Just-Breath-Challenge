// Blink LED

// #include "mbed.h"
// // Blinking rate in milliseconds
// #define BLINKING_RATE     200ms

// int main()
// {
//     // Initialise the digital pin LED1 as an output
//     DigitalOut led1(LED1);
//     DigitalOut led2(LED2);
//     led2 = !led2;
//     ThisThread::sleep_for(BLINKING_RATE);
//     while (true) {
//         led2 = !led2;
//         led1 = !led1;
//         ThisThread::sleep_for(BLINKING_RATE);
//     }
// }


// Read Analog Inputs
#include "mbed.h"

// Initialize a pins to perform analog input and digital output functions
AnalogIn   ain(PA_0);
DigitalOut dout(LED1);

int main(void)
{
    while (1) {
        ain.set_reference_voltage(1.0);
        printf("percentage: %3.5f%%\n", ain.read() * 1000000.0f);
        thread_sleep_for(25);
    }
}

