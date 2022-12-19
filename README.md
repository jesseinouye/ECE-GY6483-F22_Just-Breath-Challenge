# ECE-GY6483-F22_Just-Breath-Challenge

## Group Member (Ordered by Last Name Alphabetically)
Irving Fang - zf540
Xing Fang - xf757
Jesse Inouye - jai9962
Peiyu Tian - pt2203

## Project Overall Description
In this project, we utilize a **Piezoelectric Ribbon Sensor** to detect the breathing of a baby. 

### Workflow
When the **Ribbon** is put on the baby, the user needs to press the **User Button** to start the monitoring. When a lack of breathing for 10s has been detected, the **LCD Display** will display a warning message and produce an audio warning through the **Buzzer**. The user will need to press the **Reset Button** to stop the warning and press the **User Button** again to restart the workflow.

### Details

#### About the Piezoelectric Ribbon Sensor
Unlike regular disk-shaped Piezoelectric sensors, the sensor we used is a ribbon/strip that can wrap around a baby's chest. It will produce a current when there is a force applied to it AND the force is causing it to be stretched and then un-stretched. Our board would detect such a current and issue a warning if no such current has been observed for 10 seconds.

Some **advantages** of this sensor of choice:
1. The sensor is not simply a force sensor, and would not produce current if it's simply being pressed or being stretched for an extended period of time. The only motion that can make this sensor produce a current is stretching it and then un-stretching it. This provides great robustness for detecting the motion of breathing. As we know, babies would roll around and may cause the sensor to be held against a wall/side of a cradle. However, constant pressing this sensor will not produce current and, therefore, would not produce a false positive.

2. This sensor can be easily incorporated into a comfortably-wearable woven stripe as it does not require direct skin contact. Thus, we believe it can be adapted to a comfortable product that users would not find intrusive.

#### Topics Used in This Project
1. Interrupt and ISR to kick start the workflow when a button is pressed
2. Multithreading for displaying different message
3. ADC with the voltage producing sensor
4. GPIO for reading sensor reading and driving buzzer.
5. Finite State Machine for organizing the workflow

## Peripherals
### Onboard Peripherals

- **Green LED** to indicate that monitoring is ongoing and no abnormality has been detected.
- **Red LED** to indicate that we have detected an abnormality, that is, we believe the baby has stopped breathing.
- **User Button** to start the workflow after the sensor is placed on the baby by triggering a interrupt.
- **LCD Display**
  - Before the **User Button** is pressed, it will display a welcome message and the instruction to start the device
  - After the **User Button** is pressed, it will display a breathing effect indicating that monitoring is ongoing and no abnormality has been detected
  - When an abnormality is detected, it will display a warning message
- **Reset Button** to reset the board back to the state before the **User Button** is pressed. Users need to press the User button again to restart the workflow

### Self-Purchased Peripherals
- **KY-012 Active Buzzer** to produce an audio warning when an abnormality has been detected. 
  - Connected to pin `PF_6` and `GND`.
  - Price: roughly **$0.7** for one. [Link](https://www.amazon.com/mxuteuk-Electronic-Computers-Printers-Components/dp/B07VK1GJ9X/ref=d_pd_day0_sccl_2_1/131-7999765-9020454?pd_rd_w=Datua&content-id=amzn1.sym.8ca997d7-1ea0-4c8f-9e14-a6d756b83e30&pf_rd_p=8ca997d7-1ea0-4c8f-9e14-a6d756b83e30&pf_rd_r=G0CAFF0XREN8M9K0Z7HQ&pd_rd_wg=r2CBi&pd_rd_r=c627bcbd-8f84-4401-b0a1-c83f31e96942&pd_rd_i=B07VK1GJ9X&psc=1)

- **Piezoelectric Ribbon Sensor** to detect for breathing. 
  - Connected to pin `PC_3` and `GND`.
  - Price: **$24.95** for one. [Link](https://www.adafruit.com/product/4931)

## Project Structure
- `main.cpp` contains the main logic and workflow of the project.
- `display_helpers.cpp/display_helpers.h` contains all the helper functions that display different messages for different scenarios of the workflow, including instructions and warnings.
- `drivers` folder contains official drivers for the ST board we use.

## Future Improvement
- We planned to add an attention message like "Please Adjust the Strip" when the device is put on the baby and turned on, but no breathing has been detected. However, we noticed that this might further complicate our main logic, so we decided not to include it in the final project submission.

- Originally, the sensor is connected to `PA_0`, and it would produce a much more intuitive reading in the sense that when there is no stretching and un-stretching, the voltage reading is all 0, and we detect such a motion, the voltage reading is positive. However, since `PA_0` is connected to the User Button, we have to switch to another pin that has ADC connected. And on all the other pins the readings are inverse: motion will produce a zero voltage reading, while no motion would result in fluctuating positive readings. So far, we are unable to resolve this issue.


