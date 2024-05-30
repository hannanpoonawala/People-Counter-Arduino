# Arduino Visitor Counter

This Arduino project implements a visitor counter using passive infrared (PIR) sensors to detect entry and exit of individuals. The system utilizes a LiquidCrystal display for real-time visitor count updates and status messages. The code is organized into functions for clarity and ease of understanding.

## Key Features

1. **Dual PIR Sensors**: The system incorporates two PIR sensors, one for entry and the other for exit detection.

2. **Real-time Display**: A 16x2 LiquidCrystal display provides real-time updates on visitor count and status messages, making it easy to monitor the entry and exit activities.

3. **Visitor Counting Logic**: The code employs logic to accurately count visitors by incrementing or decrementing the count based on entry and exit events detected by the PIR sensors.

4. **Status Messages**: Informative status messages are displayed on the LCD screen, indicating whether a visitor is entering or exiting the premises.

5. **Efficient Code Structure**: The code is well-structured with separate functions for various tasks such as updating the visitor count, displaying messages, and handling sensor inputs, enhancing readability and maintainability.

## Usage

To use this visitor counter:

1. Set up your Arduino board with the specified components (LCD, PIR sensors).
2. Upload the provided Arduino sketch (`visitor_counter.ino`) to your Arduino board.
3. Connect the PIR sensors to the designated input pins on the Arduino board as per the sketch.
4. Power on the Arduino board and observe the real-time visitor count and status messages on the LiquidCrystal display.

## Contributions

Contributions and improvements are welcome to enhance the functionality and usability of this visitor counting system. Feel free to submit pull requests or open issues for any suggestions or bug fixes.
