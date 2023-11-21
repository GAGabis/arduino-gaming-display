


#include <LiquidCrystal_I2C.h>     

#define button_pin 3
int lifeRemaining = 3;
bool isJumping, isOver, isStarted;
int startTime = millis();

LiquidCrystal_I2C lcd(0x27,16,2);  

byte mainChar[] = {
  B00000,
  B11111,
  B10101,
  B11111,
  B11111,
  B01110,
  B01010,
  B11011
};



byte obstaculesChar[] = {
  B00000,
  B00100,
  B01110,
  B11111,
  B11111,
  B01110,
  B00100,
  B00000
};


byte extraLifeChar[] = {
  B00000,
  B00000,
  B01010,
  B11111,
  B11111,
  B01110,
  B00100,
  B00000
};

void setup()
{
  Serial.begin(115200);
  pinMode(button_pin, INPUT_PULLUP);
  lcd.init();                       
  lcd.createChar(1, mainChar);   
  lcd.createChar(2, obstaculesChar);
  lcd.backlight();   
  startMenu();               
}


void loop()
{
  
  
  backgroundObstacules();
  

}

void backgroundObstacules(){
  for(byte i = 14; i > -1; i--){

      Serial.println(i);

      
      //obstacules
      
      lcd.setCursor(i,1);
      lcd.write(2);
      delay(100);
      lcd.setCursor(i,1);
      lcd.print(" ");

      int readingButton = digitalRead(button_pin);

      //Serial.println(readingButton);

      //jumping

      if(readingButton == 0){
        lcd.setCursor(0,0);
        lcd.write(1);
        lcd.setCursor(0,1);
        lcd.print(" ");
        isJumping = true;

      //if isnt jumping
      }else if(readingButton == 1){
        lcd.setCursor(0,0);
        lcd.print(" ");
        lcd.setCursor(0,1);
        lcd.write(1);
        isJumping = false;
        
      }
      
    //fixing the number bug, that goes to 255 after first cicle
    if(i == 0){
      if(isJumping == false){
        Serial.println("atingido!");
        lifeRemaining--;
        if(lifeRemaining == 0){
          quitGame();
        }
      }
      i = i + 15;
      
    }
    
  }
}

void startMenu(){

  isStarted = true;
  while(isStarted == true){
    lcd.setCursor(0,0);
    lcd.print("GABOSSAUROS GAME");
    lcd.setCursor(0,1);
    lcd.print("Press BTN to SRT");

    int readingButtonStart = digitalRead(button_pin);

    if(readingButtonStart == 0){
      lcd.clear();
      isStarted=false;
      
    }
  }
  
}


void quitGame(){
  
  
  Serial.println(" ");
  lcd.clear();
  isOver = true;
  while(isOver == true){

    lcd.setCursor(3,0);
    lcd.print("GAME OVER");

    int readingButtonOver = digitalRead(button_pin);

    Serial.println(readingButtonOver);

    lcd.setCursor(0,1);
    lcd.print("PRESS BT to RST");

    if(readingButtonOver == 0){
      lcd.clear();
      Serial.println("reseting");
      isOver=false;
      lifeRemaining = 3;
    }
  }
  
}
