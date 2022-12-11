#include "mbed.h"
#include "display_helpers.h"
#include "drivers/LCD_DISCO_F429ZI.h"



// Read Analog Inputs


// Initialize a pins to perform analog input and digital output functions
// AnalogIn   ain(PA_0);
// DigitalOut dout(LED1);

// int main(void)
// {
//     while (1) {
//         ain.set_reference_voltage(1.0);
//         printf("percentage: %3.5f%%\n", ain.read() * 1000000.0f);
//         thread_sleep_for(25);
//     }
// }

InterruptIn userButton(USER_BUTTON); // The user button. Used to start detection
bool volatile start_flag = false;

DigitalOut buzzer(PF_0); // Buzzer. used to make some noise when we detect a stop of breathing (set to 1)

DigitalOut green_led(LED1); // Green LED. used to indicate the detection has started (set to true)
DigitalOut red_led(LED2); // Red LED. used to indicate when we detect a stop of breathing (set to true)

LCD_DISCO_F429ZI lcd;

Thread breath_thread;



void breathing_thread_proc() {
    display_breathing_effect(lcd);
}

void start_button_interrupt(){
  start_flag = true;
  green_led = true;
}

int main() {
  clear_display(lcd);
  breath_thread.start(breathing_thread_proc);
  thread_sleep_for(1000);

  userButton.fall(&start_button_interrupt);
  
  while (true){
    if (start_flag){
      breath_thread.terminate();
      // this is just an example. Basically we want to do something here.
      display_warning(lcd);
    }
  }
}
