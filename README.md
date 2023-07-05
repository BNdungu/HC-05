# HC-05 AT Commands

This repository provides a simple example of how to use AT commands to communicate with the HC-05 Bluetooth module using an Arduino board. The default baud rate for communication with the HC-05 module is set to 38400.

## Getting Started

To get started, follow these steps:

### Prerequisites

- Arduino IDE
- Arduino board (e.g., Arduino Uno)
- HC-05 Bluetooth module

### Wiring

Connect the HC-05 module to the Arduino board as follows:

- HC-05 VCC -> Arduino 5V
- HC-05 GND -> Arduino GND
- HC-05 RXD -> Arduino TX (Pin 16)
- HC-05 TXD -> Arduino RX (Pin 17)

Make sure to cross-connect the RX and TX pins between the Arduino board and the HC-05 module.

### Uploading the Code

1. Download or clone this repository to your local machine.
2. Open the included `.ino` file in the Arduino IDE.
3. Ensure that the correct board and port are selected in the Arduino IDE.
4. Compile and upload the code to your Arduino board.

### Using AT Commands

1. Power on the Arduino board and HC-05 module.
2. Open the Serial Monitor in the Arduino IDE.
3. Set the baud rate of the Serial Monitor to 115200.
4. Enter AT commands in the Serial Monitor to communicate with the HC-05 module.

### Example Code

The following code snippet demonstrates the basic setup for sending and receiving AT commands:

```cpp
#include <SoftwareSerial.h>

SoftwareSerial bt(16, 17);
char c = ' ';
boolean NL = true;

void setup() {
    bt.begin(38400);
    Serial.begin(115200);
}

void loop() {
    if (bt.available()) {
        c = bt.read();
        Serial.write(c);
    }
    if (Serial.available()) {
        c = Serial.read();
        bt.write(c);
        if (NL) {
            Serial.print(">");
            NL = false;
        }
        Serial.write(c);
        if (c == 10)
            NL = true;
    }
}
```
