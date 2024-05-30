#include <LiquidCrystal.h>

// Define the pin numbers for the LCD
const int rs = 13, en = 12, d4 = 11, d5 = 10, d6 = 9, d7 = 8;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// Define the input pin numbers for the two PIR sensors
#define avoidIn 2
#define avoidOut 3

// Variable to hold the current status of the system
bool stat = true;

// Variables to keep track of visitors and their last detected action
int visitors = 0;
int lastDetected = 0;

// Flags to track the current state of the PIR sensors
bool avoidIn_active = false;
bool avoidOut_active = false;

// Define intervals for checking PIR sensor inputs
unsigned long previousA = 0;
unsigned long intervalA = 100;
unsigned long previousB = 0;
unsigned long intervalB = 100;

// Function to display messages on the LCD
void DisplayMsg(String s1, String s2, bool stat) {
  if (stat){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(s1);
    lcd.setCursor(0,1);
    lcd.print(s2);
  } 
}

// Function to update the visitors counter based on sensor input
void UpdateVisitorsCounter(int x){ 
  int duration=100;
  visitors = visitors + x;
  lastDetected = 0;  
}

// Setup function runs once at the beginning
void setup() {
  Serial.begin(9600); // Start serial communication
  lcd.begin(16, 2); // Initialize the LCD
  pinMode(avoidIn, INPUT); // Set avoidIn pin as input
  pinMode(avoidOut, INPUT); // Set avoidOut pin as input
  DisplayMsg("Visitor counter", "Welcome", stat); // Display welcome message on LCD
}

// Loop function runs repeatedly
void loop() {
  // Check PIR sensor input for entry
  unsigned long current = millis();
  if(current - previousA >= intervalA){
    previousA = current;
    if (digitalRead(avoidIn) == false) {
    
      if ( !avoidIn_active ) {
        avoidIn_active = true;
      
        if (lastDetected == 0 && !avoidOut_active) { 
          lastDetected = 1;    
          DisplayMsg("In PIR1", "Visit started", stat); // Display visit started message on LCD
        } 
        else if (lastDetected == 2) { 
          UpdateVisitorsCounter(-1); // Update visitor count
          DisplayMsg("Visitor exited", "Visitors:" + String(visitors), stat); // Display visitor exited message on LCD
        } 
      }
    }else{
      avoidIn_active = false ;
    }
  }

  // Check PIR sensor input for exit
  if(current - previousB >= intervalB){
    previousB = current;
    if (digitalRead(avoidOut) == false ) {
    
      if ( !avoidOut_active ) {
        avoidOut_active = true;
      
        if (lastDetected == 0 && !avoidIn_active) { 
          if (visitors > 0) {
            lastDetected = 2;   
            DisplayMsg("In PIR2", "Exit started", stat); // Display exit started message on LCD
          } 
          else{
            DisplayMsg("No more visitors", "to exit", stat); // Display no more visitors to exit message on LCD
          }
                
        }
        else if (lastDetected == 1) {  
          UpdateVisitorsCounter(1); // Update visitor count
          DisplayMsg("Visitor entered", "Visitors:" + String(visitors), stat); // Display visitor entered message on LCD
        }
      }
    } 
    else{
       avoidOut_active = false;
    }
  }
}
