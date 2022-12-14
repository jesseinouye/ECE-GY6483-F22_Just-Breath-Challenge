#include "mbed.h"
#include "display_helpers.h"
#include "drivers/LCD_DISCO_F429ZI.h"

#define BREATH_CHECK_THRESHOLD 5

// Piezosensor for motion detection
AnalogIn ain(PC_3);
// Timer for 10 seconds cycle
Timer timer1;

// The user button. Used to start detection
InterruptIn userButton(USER_BUTTON); // The user button. Used to start detection

// Peripherals for Signaling
DigitalOut green_led(LED1); // Green LED. used to indicate the detection has started (set to true)
DigitalOut red_led(LED2);   // Red LED. used to indicate when we detect a stop of breathing (set to true)
DigitalOut buzzer(PF_6);    // Buzzer. used to make some noise when we detect a stop of breathing (set to 1)
LCD_DISCO_F429ZI lcd;

enum PROG_STATE
{
    STOPPED,
    MONITORING,
    ALERTING
};
PROG_STATE volatile state;

uint16_t breath_check = 0;

// Threads
Thread lcd_thread;

void alert()
{
    red_led = true;
    green_led = false;
    state = ALERTING;
    buzzer = 1;
    // display_warning(lcd);
}

void check()
{
    red_led = false;
    green_led = true;
    state = MONITORING;
    // printf("time: %d \n", timer1.read());

    printf("voltage: %f \n", ain.read() * 1'000'000.0f);
    if (ain.read() * 1'000'000.0f < 0.5) // detect the first sample of breathing
    {
        breath_check += 1; 
    }
    else
    {
        breath_check = 0;
    }
    if (breath_check >= BREATH_CHECK_THRESHOLD ) // confirm one breath cycle from 5 continues sampling 
    {
        breath_check = 0;
        timer1.reset();
    }

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

    // Initiate program state
    state = STOPPED;

    // Register ISR for button
    userButton.fall(&start);

    // Start LCD thread
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
            // case STOPPED not required
            // case ALERTING not required
            default:
                break;
        }
    }
}
