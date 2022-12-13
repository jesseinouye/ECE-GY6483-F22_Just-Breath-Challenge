#include "mbed.h"
#include "display_helpers.h"
#include "drivers/LCD_DISCO_F429ZI.h"

#define BREATH_CHECK_THRESHOLD 5

// Piezosensor for motion detection
AnalogIn ain(PA_0);
// Timer for 10 seconds cycle
Timer timer1;

// ISR for start/stop button
// InterruptIn userButton(PA_0); // The user button. Used to start detection

// Peripherals for Signaling
DigitalOut green_led(LED1); // Green LED. used to indicate the detection has started (set to true)
DigitalOut red_led(LED2);   // Red LED. used to indicate when we detect a stop of breathing (set to true)
DigitalOut buzzer(PF_0);    // Buzzer. used to make some noise when we detect a stop of breathing (set to 1)
LCD_DISCO_F429ZI lcd;

enum PROG_STATE
{
    STOPPED,
    MONITORING,
    ALERTING
};
PROG_STATE state;

uint8_t breath_check = 0;

// Threads
Thread lcd_thread;

void alert()
{
    red_led = true;
    green_led = false;
    state = ALERTING;
    // display_warning(lcd);
}

void check()
{
    red_led = false;
    green_led = true;
    state = MONITORING;
    // printf("time: %d \n", timer1.read());
    printf("voltage: %f \n", ain.read() * 1'000'000.0f);
    if (ain.read() * 1'000'000.0f > 5000.0) // detect the first sample of breathing
    {
        // breath_check += 1; 
        timer1.reset();
    }
    if (breath_check >= BREATH_CHECK_THRESHOLD) // confirm one breath cycle from 5 continues sampling 
    {
        breath_check = 0;
        // timer1.reset();
    }
    // if (breath_check == 0 && ain.read() * 1'000'000.0f < 10.0) // resets timer when 
    // {
    //     timer1.reset();
    // }

}

void displaying_proc()
{
    while (true)
    {
        switch (state)
        {
        case ALERTING:
            display_warning(lcd);
            break;
        case MONITORING:
            while(state == MONITORING){
                display_breathing_msg1(lcd);
                thread_sleep_for(500);
                display_breathing_msg2(lcd);
                thread_sleep_for(500);
            }
            break;
        default:
            display_starting_msg(lcd);
            break;
        }
    }
}

void start()
{
    state = MONITORING;
    timer1.start();
}

int main()
{

    // Setups
    state = STOPPED;
    // ain.set_reference_voltage(1.0);

    // register ISR for button
    // userButton.fall(&start);
    start();
    lcd_thread.start(displaying_proc);

    while (true)
    {
        switch (state)
        {
            case MONITORING:
                if (timer1.read_ms() >= 10'000) // read time in ms
                {
                    alert();
                    break;
                }
                else
                {
                    check();
                }
                thread_sleep_for(25);
                break;

            case ALERTING:
                alert();
                break;

            default:
                break;
            }
    }
}
