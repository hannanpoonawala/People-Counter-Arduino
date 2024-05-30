#include <LiquidCrystal.h>

const int rs = 13, en = 12, d4 = 11, d5 = 10, d6 = 9, d7 = 8;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

#define avoidIn 2
#define avoidOut 3

bool stat = true;

int visitors = 0;
int lastDetected = 0;
bool avoidIn_active = false;
bool avoidOut_active = false;

unsigned long previousA = 0;
unsigned long intervalA = 100;
unsigned long previousB = 0;
unsigned long intervalB = 100;

void DisplayMsg(String s1, String s2, bool stat) {
  if (stat){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(s1);
    lcd.setCursor(0,1);
    lcd.print(s2);
  } 
}

void UpdateVisitorsCounter(int x){ 
  int duration=100;
  visitors = visitors + x;
  lastDetected = 0;  
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  lcd.begin(16, 2);
  pinMode(avoidIn, INPUT);
  pinMode(avoidOut, INPUT);
  DisplayMsg("Visitor counter", "Welcome", stat);
}

void loop() {
  //for ENTERY---------------------------------------
  unsigned long current = millis();
  if(current - previousA >= intervalA){
    previousA = current;
    if (digitalRead(avoidIn) == false) {
    
      if ( !avoidIn_active ) {
        avoidIn_active = true;
      
        if (lastDetected == 0 && !avoidOut_active) { 
          lastDetected = 1;    
          DisplayMsg("In PIR1", "Visit started", stat);

        } 
        else if (lastDetected == 2) { 
          UpdateVisitorsCounter(-1);  
          DisplayMsg("Visitor exited", "Visitors:" + String(visitors), stat);
        } 
      }
    }else{
      avoidIn_active = false ;
    }
  }

  //for EXIT -----------------------------------
  if(current - previousB >= intervalB){
    previousB = current;
    if (digitalRead(avoidOut) == false ) {
    
      if ( !avoidOut_active ) {
        avoidOut_active = true;
      
        if (lastDetected == 0 && !avoidIn_active) { 
          if (visitors > 0) {
            lastDetected = 2;   

            DisplayMsg("In PIR2", "Exit started", stat);
          } 
          else{
            DisplayMsg("No more visitors", "to exit", stat);
          }
                
        }
        else if (lastDetected == 1) {  
          UpdateVisitorsCounter(1);      
          DisplayMsg("Visitor entered", "Visitors:" + String(visitors), stat);
        }
      }
    } 
    else{
       avoidOut_active = false;
    }
  }

}
