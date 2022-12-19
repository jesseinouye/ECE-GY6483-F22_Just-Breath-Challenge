#include "mbed.h"
#include "display_helpers.h"
#include "drivers/LCD_DISCO_F429ZI.h"

// Group Member (Ordered by Last Name Alphabetically)
// Irving Fang - zf540
// Xing Fang - xf757
// Jesse Inouye - jai9962
// Peiyu Tian - pt2203

#define BREATH_CHECK_THRESHOLD 5 // this number control how sensitive our detection is. Lower the number, the easier the warning will be triggered

// Piezosensor for motion detection
AnalogIn ain(PC_3);

// Timer for 10 seconds cycle
Timer timer1;

// The user button. 
InterruptIn userButton(USER_BUTTON); // The user button. Used to start detection

// Peripherals for Signaling
DigitalOut green_led(LED1); // Green LED. used to indicate the detection has started (set to true)
DigitalOut red_led(LED2);   // Red LED. used to indicate when we detect a stop of breathing (set to true)
DigitalOut buzzer(PF_6);    // Buzzer. used to make some noise when we detect a stop of breathing (set to 1)


enum PROG_STATE
{
    STOPPED,
    MONITORING,
    ALERTING
};
PROG_STATE volatile state;

uint16_t breath_check = 0;

// Threads and Flags for LCD display
uint8_t volatile starting_display_flag = 0; // used to indicate that starting page is already being displayed
uint8_t volatile warning_display_flag = 0; // used to indicate that warning is already being displayed
LCD_DISCO_F429ZI lcd;
Thread lcd_thread;


void alert()
// this function will trigger all the warnings, including visual and audio
{
    red_led = true;
    green_led = false;
    state = ALERTING;
    buzzer = 1;
}

void check()
// this function checks if the user is continuously breathing by checking if there is no 0 in BREATH_CHECK_THRESHOLD consecutive samples
// the Piezosensor will produce consecutive 0 readings when streched. If there is an extended period of time with no consecutive 0, we consider a warning.
{
    red_led = false;
    green_led = true;
    state = MONITORING;

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
// this function is another thread handling all the needs for displaying messages on the screen for different scenarios.
{
    while (true)
    {
        switch (state)
        {
        case ALERTING:
            // display warning
            if (!warning_display_flag){
                display_warning(lcd);
                warning_display_flag = 1;
            }
            break;
        case MONITORING:
            // display a breathing effect, indicating normal breathing
            while(state == MONITORING){
                display_breathing_msg1(lcd);
                thread_sleep_for(500);
                display_breathing_msg2(lcd);
                thread_sleep_for(500);
            }
            break;
        default:
            // display a welcome message and instruction
            if (!starting_display_flag){
                display_starting_msg(lcd);
                starting_display_flag = 1;
            }
            break;
        }
    }
}

void start()
// the ISR for button pressing. Start the workflow
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
