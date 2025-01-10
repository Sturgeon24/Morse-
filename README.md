# Morse-
Morse code converter using Arduino uno and IR sensor.
# Morse Code Translator with Arduino

This project implements a Morse Code Translator using an Arduino. It allows users to input Morse code using a button and receive real-time translation into English via the serial monitor. Additionally, users can enter English text via the serial monitor and observe the translation into Morse code, which is output using an LED.

## Features

1. **Morse Code Input**:
   - Use a button to input dots (short presses) and dashes (long presses).
   - Automatic detection of character breaks after a pause.
   - Real-time translation of Morse code into English, displayed on the serial monitor.

2. **Reset Functionality**:
   - A dedicated reset button allows users to delete the last entered character.

3. **English to Morse Conversion**:
   - Enter English messages via the serial monitor.
   - The Arduino converts the message to Morse code and blinks it using the onboard LED.

4. **Visual Feedback**:
   - The onboard LED indicates button presses and blinks Morse output for English-to-Morse translation.

## How It Works
- **Morse-to-English**: Press the button to input dots (`.`) and dashes (`-`). Release the button to signal the end of a character.
- **English-to-Morse**: Enter a text message in the serial monitor, and the onboard LED will blink the Morse code equivalent.

## Hardware Requirements
- Arduino board
- Button
- LED
- Resistors (for pull-up configuration)

This project is an engaging way to explore Morse code and Arduino programming!
