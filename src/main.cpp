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

InterruptIn userButton(USER_BUTTON);
DigitalOut green_led(LED1); // used to indicate the detecting has started
DigitalOut red_led(LED2); // used to indicate there is something wrong
LCD_DISCO_F429ZI lcd;
 
bool volatile start_flag = false;


void start_button_interrupt(){
  start_flag = true;
  green_led = true;
}

int main() {
  //userButton.mode(PullUp);
  clear_display(lcd);
  userButton.fall(&start_button_interrupt);
  while (true){
    if (start_flag){
      // this is just an example. Basically we want to do something here.
      thread_sleep_for(5000);
      display_warning(lcd);
    }
  }
}
