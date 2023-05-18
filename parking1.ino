#include <Servo.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <SPI.h>
#include <MFRC522.h>


#define RST_PIN         9         // Configurable, see typical pin layout above
#define SS_PIN          10        // Configurable, see typical pin layout above


MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create MFRC522 instance
Servo monservo;  // crée l’objet pour contrôler le servomoteur


// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27,16,2); 

char data ;


int led = 13;                // the pin that the LED is atteched to
int sensor = 2;              // the pin that the sensor is atteched to
int state = LOW;             // by default, no motion detected
int val = 0;                 // variable to store the sensor status (value)

void setup() {

    monservo.attach(9);  // utilise la broche 9 pour le contrôle du servomoteur
  monservo.write(0); // positionne le servomoteur à 0°
  
  pinMode(led, OUTPUT);      // initalize LED as an output
  pinMode(sensor, INPUT);    // initialize sensor as an input
  Serial.begin(9600);        // initialize serial

    // initialize the LCD
    lcd.init();
  
    // Turn on the backlight
    lcd.backlight();
  
    // Print a message to the LCD.
    lcd.setCursor(0,0);
    lcd.print("Welcome");

    
  
}

void loop()

{
  // Check for serial input
        if (Serial.available() > 0) {
            data = Serial.read(); 

            if (data == '1') {
                lcd.clear();                 // clear display
                Serial.write("Success\n");   // write in terminal
                lcd.setCursor(0,0);
                lcd.print("Success");
                delay(2000);                 // display the above for two seconds
            }
            else if ( data == '0') {
                lcd.clear();                 // clear display
                Serial.write("Echec\n");   // write in terminal
                lcd.setCursor(0,0);
                lcd.print("Echec");
                delay(2000);                 // display the above for two seconds
            }
        }


        
 val = digitalRead(sensor);   // read sensor value
if (val == HIGH) {           // check if the sensor is HIGH
  digitalWrite(led, HIGH);   // turn LED ON

  // add this code to turn the servo
  monservo.write(0);
  delay(1000);
  monservo.write(90);
  delay(1000);

  delay(100);                // delay 100 milliseconds 
  
  if (state == LOW) {
    Serial.println("Motion detected!"); 
    state = HIGH;       // update variable state to HIGH
  }
} 

  else {
  digitalWrite(led, LOW); // turn LED OFF
  delay(200);             // delay 200 milliseconds 
  
  if (state == HIGH){
    Serial.println("Motion stopped!");
    state = LOW;       // update variable state to LOW
  }
}

  
}
