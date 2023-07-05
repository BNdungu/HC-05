# HC-05 AT Commands

This repository provides a simple example of how I used AT commands to communicate with the HC-05 Bluetooth module using a Microcontroller board.

### please note that the default baud rate for communication with the HC-05 module is set to 38400.

## Getting Started

To get started, follow these steps:

### Prerequisites

- Arduino IDE
- Micro-controler Board in my case using an ESP32 Devkit V1 module
- HC-05 Bluetooth module

### Wiring

Connect the HC-05 module to the Microcontroller board as follows:

- HC-05 VCC -> Microcontroller 3v3 or 5V
- HC-05 GND -> Microcontroller GND pin
- HC-05 RXD -> Microcontroller TX in my case (Pin 16)
- HC-05 TXD -> Microcontroller RX in my case (Pin 17)
- HC-05 ENA -> Microcontroller 3V3

### NB: ENA pin in the HC-05 needs to be set to high to enable AT command mode.

Make sure to cross-connect the RX and TX pins between the Microcontroller board and the HC-05 module.

### Uploading the Code

1. Download or clone this repository to your local machine.
2. Open the included `.ino` file in the Arduino IDE.
3. Ensure that the correct board and port are selected in the Arduino IDE.
4. Compile and upload the code to your Microcontroller board.

### Using AT Commands

1. Power on the Microcontroller board and HC-05 module.
2. Open the Serial Monitor in the Arduino IDE.
3. Set the baud rate of the Serial Monitor to 115200.
4. Enter AT commands in the Serial Monitor to communicate with the HC-05 module.

The HC-05 expects commands to include a carriage return and newline characters (\r\n). You can add these automatically in the serial monitor by selecting “Both NL & CR” at the bottom of the window.

## AT Commands

Here are some common AT commands that can be used with the HC-05 module:

| Command      | Description                                      | Response                                                              |
| ------------ | ------------------------------------------------ | --------------------------------------------------------------------- |
| AT           | Checking communication                           | OK                                                                    |
| AT+PSWD=XXXX | Set Password                                     | OK                                                                    |
| AT+NAME=XXXX | Set Bluetooth Device Name                        | OK                                                                    |
| AT+UART=XXXX | Change Baud rate                                 | OK                                                                    |
| AT+VERSION?  | Respond version no. of Bluetooth module          | +Version: XX OK                                                       |
| AT+ORGL      | Send detail of settings done by the manufacturer | Parameters: device type, module mode, serial parameter, passkey, etc. |
| AT+NAME      | check the name of the HC-S04                     | Parameters: device type, module mode, serial parameter, passkey, etc. |

### Please refer to the [HC-05 datasheet](https://s3-sa-east-1.amazonaws.com/robocore-lojavirtual/709/HC-05_ATCommandSet.pdf) for more information on available AT commands and their specific usage.

### Example Code

The following code snippet demonstrates the basic setup for sending and receiving AT commands:

```cpp
#include <SoftwareSerial.h>

SoftwareSerial bt(16, 17); // create an instance named bt(bluetooth) on rx pin 16 and tx pin 17
char c = ' ';      //c variable reads from the uart buffer(rx pin)
boolean newLine = true;
void setup() {
    bt.begin(38400);  //please remember the baudrate is 38400 by default on the module
    Serial.begin(115200); // serial communication between my Esp32 board and my PC works well at this baud
}

void loop(){

        // this if statement checks to see any available data from the the bt module and displays it on the serial monitor if present
    if (bt.available())
    {
        c = bt.read();
        Serial.write(c);
    }
         // this if statement checks to see any available data from the the serial monitor on user input and displays it after sending it to the hc-05's rx buffer.
    if (Serial.available())
    {
        c = Serial.read();
        bt.write(c);

        if (newLine) { Serial.print(">");  newLine = false; }
        Serial.write(c);
        if (c==10) newLine = true;
    }
 }
```
