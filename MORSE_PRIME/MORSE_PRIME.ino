const int morseInputPin = 3; // Pin for Morse code input
const int resetPin = 4;      // Pin for reset button
const int ledPin = 13;       // Pin for LED
const int resetFeedbackLedPin = 12; // Pin for reset feedback LED

String morseCode = "";       // Store the Morse code sequence
String message = "";         // Store the full message
unsigned long pressStartTime = 0; // Time when button is pressed
bool buttonPressed = false;      // State to track button press

void setup() {
  pinMode(morseInputPin, INPUT_PULLUP); // Morse code input pin with pull-up resistor
  pinMode(resetPin, INPUT_PULLUP);      // Reset button pin with pull-up resistor
  pinMode(ledPin, OUTPUT);              // LED output pin
  pinMode(resetFeedbackLedPin, OUTPUT); // Reset feedback LED pin

  Serial.begin(9600);                  // Initialize serial communication
  Serial.println("Morse Code Reader Ready!");
  printRulesAndTranslationList();
}

void loop() {
  // Check if reset button is pressed
  if (digitalRead(resetPin) == LOW) {
    if (message.length() > 0) {
      // Remove the last character of the message
      message.remove(message.length() - 1);
      Serial.print("Last character removed. Current Message: ");
      Serial.println(message);

      // Blink reset feedback LED
      digitalWrite(resetFeedbackLedPin, HIGH);
      delay(200);
      digitalWrite(resetFeedbackLedPin, LOW);
      delay(200);
    } else {
      Serial.println("Message is already empty.");
    }
    delay(300); // Debounce delay
  }

  // Read the Morse input pin
  if (digitalRead(morseInputPin) == LOW) {
    if (!buttonPressed) {
      pressStartTime = millis(); // Record the time when button press starts
      buttonPressed = true;
      digitalWrite(ledPin, HIGH); // Turn on LED to indicate button press
    }
  } else {
    if (buttonPressed) {
      // Button release
      unsigned long pressDuration = millis() - pressStartTime;
      buttonPressed = false;
      digitalWrite(ledPin, LOW); // Turn off LED

      // Determine if it's a dot or a dash based on press duration
      if (pressDuration < 400) {
        morseCode += "."; // Short press = dot
        Serial.println("Dot detected.");
      } else {
        morseCode += "-"; // Long press = dash
        Serial.println("Dash detected.");
      }

      // Print the Morse code so far
      Serial.print("Morse Code: ");
      Serial.println(morseCode);
    }
  }

  // Check for a pause to determine the end of a letter
  static unsigned long lastReleaseTime = 0;
  if (buttonPressed) {
    lastReleaseTime = millis(); // Update the last release time while pressing
  } else if (millis() - lastReleaseTime > 1000 && morseCode.length() > 0) {
    // If no input for 1 second, assume end of a letter
    char detectedLetter = translateMorse(morseCode);
    if (detectedLetter != '?') {
      message += detectedLetter; // Append the letter to the message
    }
    else
    {
      Serial.println("Invalid");
    }
    Serial.print("Current Message: ");
    Serial.println(message);
    morseCode = ""; // Clear the code for the next letter
  }

  // Check for input in the serial monitor
  if (Serial.available() > 0) {
    String inputMessage = Serial.readStringUntil('\n'); // Read user input
    inputMessage.trim();
    Serial.print("Converting message to Morse code: ");
    Serial.println(inputMessage);
    convertToMorse(inputMessage);
  }

  delay(10); // Short delay to debounce and avoid rapid reads
}

// Function to print Morse code rules and translation table
void printRulesAndTranslationList() {
  Serial.println("Morse Code Translation Rules:");
  Serial.println("Use dot (.) for short press and dash (-) for long press.");
  Serial.println("Morse Code to Character Mapping:");
  Serial.println(".-  -> A  |  -... -> B  |  -.-. -> C  |  -..  -> D");
  Serial.println(".    -> E  |  ..-. -> F  |  --.  -> G  |  .... -> H");
  Serial.println("..   -> I  |  .--- -> J  |  -.-  -> K  |  .-.. -> L");
  Serial.println("--   -> M  |  -.   -> N  |  ---  -> O  |  .--. -> P");
  Serial.println("--.- -> Q  |  .-.  -> R  |  ...  -> S  |  -    -> T");
  Serial.println("..-  -> U  |  ...- -> V  |  .--  -> W  |  -..- -> X");
  Serial.println("-.-- -> Y  |  --.. -> Z  |  ----- -> 0  |  .---- -> 1");
  Serial.println("..--- -> 2  |  ...-- -> 3  |  ....- -> 4  |  ..... -> 5");
  Serial.println("-.... -> 6  |  --... -> 7  |  ---.. -> 8  |  ----. -> 9");
  Serial.println("Use the button to input Morse code and interact with the system.");
}

// Function to translate Morse code to a letter
char translateMorse(String code) {
  if (code == ".-") return 'A';
  if (code == "-...") return 'B';
  if (code == "-.-.") return 'C';
  if (code == "-..") return 'D';
  if (code == ".") return 'E';
  if (code == "..-.") return 'F';
  if (code == "--.") return 'G';
  if (code == "....") return 'H';
  if (code == "..") return 'I';
  if (code == ".---") return 'J';
  if (code == "-.-") return 'K';
  if (code == ".-..") return 'L';
  if (code == "--") return 'M';
  if (code == "-.") return 'N';
  if (code == "---") return 'O';
  if (code == ".--.") return 'P';
  if (code == "--.-") return 'Q';
  if (code == ".-.") return 'R';
  if (code == "...") return 'S';
  if (code == "-") return 'T';
  if (code == "..-") return 'U';
  if (code == "...-") return 'V';
  if (code == ".--") return 'W';
  if (code == "-..-") return 'X';
  if (code == "-.--") return 'Y';
  if (code == "--..") return 'Z';
  if (code == "-----") return '0';
  if (code == ".----") return '1';
  if (code == "..---") return '2';
  if (code == "...--") return '3';
  if (code == "....-") return '4';
  if (code == ".....") return '5';
  if (code == "-....") return '6';
  if (code == "--...") return '7';
  if (code == "---..") return '8';
  if (code == "----.") return '9';
  if (code == ".-.-.-") return ' ';
  return '?'; // Return '?' for unknown codes
}

// Function to convert English to Morse code and blink the LED
void convertToMorse(String inputMessage) {
  for (int i = 0; i < inputMessage.length(); i++) {
    char c = toupper(inputMessage[i]);
    String morse = getMorseCode(c);
    if (morse != "") {
      Serial.print(c);
      Serial.print(": ");
      Serial.println(morse);
      blinkMorseCode(morse);
      delay(500); // Delay between letters
    }
  }
  Serial.println("Message converted to Morse code.");
}

// Function to get Morse code for a given character
String getMorseCode(char c) {
  switch (c) {
    case 'A': return ".-";
    case 'B': return "-...";
    case 'C': return "-.-.";
    case 'D': return "-..";
    case 'E': return ".";
    case 'F': return "..-.";
    case 'G': return "--.";
    case 'H': return "....";
    case 'I': return "..";
    case 'J': return ".---";
    case 'K': return "-.-";
    case 'L': return ".-..";
    case 'M': return "--";
    case 'N': return "-.";
    case 'O': return "---";
    case 'P': return ".--.";
    case 'Q': return "--.-";
    case 'R': return ".-.";
    case 'S': return "...";
    case 'T': return "-";
    case 'U': return "..-";
    case 'V': return "...-";
    case 'W': return ".--";
    case 'X': return "-..-";
    case 'Y': return "-.--";
    case 'Z': return "--..";
    case '0': return "-----";
    case '1': return ".----";
    case '2': return "..---";
    case '3': return "...--";
    case '4': return "....-";
    case '5': return ".....";
    case '6': return "-....";
    case '7': return "--...";
    case '8': return "---..";
    case '9': return "----.";
    case ' ': return ".-.-.-"; // Space logic for Morse
    default: return "Morse code invalid";
  }
}

// Function to blink Morse code using the LED
void blinkMorseCode(String morse) {
  for (int i = 0; i < morse.length(); i++) {
    if (morse[i] == '.') {
      digitalWrite(ledPin, HIGH);
      delay(400); // Dot duration
      digitalWrite(ledPin, LOW);
    } else if (morse[i] == '-') {
      digitalWrite(ledPin, HIGH);
      delay(800); // Dash duration
      digitalWrite(ledPin, LOW);
    }
    delay(550); // Gap between dots and dashes
  }
}
