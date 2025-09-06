#define BLYNK_TEMPLATE_ID "TMPL3xW5WGAlZ"

#define BLYNK_TEMPLATE_NAME "GassNotify"

#define BLYNK_AUTH_TOKEN "e7JLQ1rNwKhAcY3Prw5F29CUhTFfuvAt"



#include <WiFi.h>

#include <BlynkSimpleEsp32.h>

#include <ESP32Servo.h>

#include <Keypad.h>



// WiFi Credentials

char ssid[] = "Geethanjali";      

char pass[] = "campus@123456";    



// Servo Motor

Servo servo;  

#define SERVO_PIN 23  // Servo connected to GPIO 23



// Keypad Configuration

const byte ROWS = 4;

const byte COLS = 4;

char keys[ROWS][COLS] = {

  {'1', '2', '3', 'A'},

  {'4', '5', '6', 'B'},

  {'7', '8', '9', 'C'},

  {'*', '0', '#', 'D'}

};



byte rowPins[ROWS] = {33, 25, 26, 14}; // Adjusted GPIOs

byte colPins[COLS] = {27, 13, 22, 4};  



Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);



// Define password

String correctPassword = "1234";

String inputPassword = "";



void setup() {

  Serial.begin(115200);

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  

  servo.attach(SERVO_PIN);  

  servo.write(0);  // Default position



  Serial.println("Enter Password:");

}



void loop() {

  Blynk.run();



  char key = keypad.getKey(); 



  if (key) {

    Serial.print("Key Pressed: ");

    Serial.println(key);



    if (key == '#') { // Check password when '#' is pressed

      checkPassword();

    } 

    else if (key == '*') { // Clear password

      inputPassword = "";

      Serial.println("Password Cleared");

    } 

    else {

      inputPassword += key; 

      Serial.print("Entered: ");

      Serial.println(inputPassword);

    }

  }

}



// Function to check password

void checkPassword() {

  if (inputPassword == correctPassword) {

    Serial.println("✅ Access Granted - Moving Servo...");

    servo.write(90);  // Move servo to 90°

    Blynk.logEvent("servo_moved", "⚠ Servo moved to 90°! Check the system.");

    delay(2000);

    servo.write(0);  // Reset back to 0°

  } else {

    Serial.println("❌ Access Denied");

  }

  

  inputPassword = ""; // Reset input

}