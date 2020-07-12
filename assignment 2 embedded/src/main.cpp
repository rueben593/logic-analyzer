#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define potPin 14
#define buttonPin 12
#define ch1Pin 16
#define DAPin A14
#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
  void ISR_Button();
  void checkConditions();
  void initialiseOptionsScreen();
  void simpleOscilloscope();
  void resetSignal();
  void startScreen();
  void menuScreen();
  void selectionMenu();
  void osciMode();
  void funcGenMode();
  void logicAnalyserMode(); //Not completed
  void squareWave();
  void sinWave();
  void triangleWave();
volatile bool pressDetected = false;
volatile bool buttonPressed = false;
bool BP_pot0 = false; //Button pressed and pot value 0
bool BP_pot1 = false; //Button pressed and pot value 1
bool BP_pot2 = false;
bool BP_pot3 = false;
bool serialIn0 = false; //Serial input 0
bool serialIn1 = false; //Serial input 1
bool serialIn2 = false;
bool serialIn3 = false;

enum states {
  StartScreen, 
  SelectionMenu,
  OsciMode, 
  FuncGenMode, 
  LogicAnalyserMode, 
  SquareWave, 
  SinWave, 
  TriangleWave,
};

states currentState = StartScreen;
  uint16_t textColor0 = WHITE;
  uint16_t textColor1 = WHITE;
  uint16_t textColor2 = WHITE;
  uint16_t textColor3 = WHITE;
  const uint16_t Xpos = 4;
  const uint16_t Ypos0 = 22;
  const uint16_t Ypos1 = 32;
  const uint16_t Ypos2 = 42;
  const uint16_t Ypos3 = 52;
  uint16_t cursorXPos = 0;
  uint16_t cursorYPos = 0;
  const uint32_t plotWidthOffset = 1; //1 pixel from left
  const uint32_t plotWidth = SCREEN_WIDTH - plotWidthOffset - 1; 
  const uint32_t plotHeightOffset = 7; //Offset to allow for text at top of screen
  const uint32_t plotHeight = SCREEN_HEIGHT-1 - plotHeightOffset ;

  uint32_t currXDrawVal = 0;

  const uint32_t maxVoltage_mV = 3300;

  const uint32_t scanTime_us = 35000;

  //Triangle Wave function
  const uint32_t triangSigRange = 1023; //Signal range (0-1023)
  uint32_t currYSigVal = 0; //Current signal value

  //Sin Wave Function
  const uint32_t sinSigRange = 1023; //Signal range (0-1023)
  uint32_t YSigVal = 0;
  uint32_t XSigVal = 0;
  uint32_t XSinVal = 0;

  //Square Wave Function
  const uint32_t squareScanTime_us = 10000;
  const uint32_t squareSigRange = 1023; //Signal range (0-1023)

const uint32_t debounceTime_ms = 150; //80ms Debounce time
uint32_t potSelectVal = 0;
void setup() {
  pinMode(DAPin, OUTPUT);
  pinMode(ch1Pin, INPUT);
  pinMode(potPin,INPUT);
  pinMode(buttonPin, INPUT_PULLUP);
  attachInterrupt(buttonPin, ISR_Button, FALLING);
  analogReadResolution(10); //10 bit resolution
  analogWriteResolution(10); //10 bit resolution

  //Initialise serial interface
  Serial.begin(115200);

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3C for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); 
  }

  // Clear the buffer
  display.clearDisplay();
}

void loop() {
 
  switch (currentState) {
      case StartScreen:
        Serial.println("Screen");
        startScreen();
        checkConditions();
        if(buttonPressed || serialIn1){
          display.clearDisplay(); display.display(); 
          currentState = SelectionMenu; 
          buttonPressed = false;
        }
        break;

      case SelectionMenu:
        menuScreen();
        checkConditions();
        if(buttonPressed || serialIn0){
          display.clearDisplay(); display.display(); 
          currentState = StartScreen; 
        } 
        if(BP_pot1 || serialIn1){
          display.clearDisplay(); display.display(); 
        }
        if(BP_pot2 || serialIn2){
          display.clearDisplay(); display.display(); 
          currentState = LogicAnalyserMode;
        }
        if(BP_pot3 || serialIn3){
          display.clearDisplay(); display.display(); 
          currentState = FuncGenMode;
        }
        break;

      case OsciMode:
        osciMode();
        checkConditions();
        if(buttonPressed || serialIn0){
          display.clearDisplay(); display.display(); 
          currentState = SelectionMenu;  
          buttonPressed = false;
        }
        break;

      case FuncGenMode:
        funcGenMode();
        checkConditions();

        if(buttonPressed || serialIn0){
          display.clearDisplay(); display.display(); 
          currentState = SelectionMenu; 
          buttonPressed = false;
        } 
        if(BP_pot1 || serialIn1){
          display.clearDisplay(); display.display(); 
          currentState = SquareWave;
        }
        if(BP_pot2 || serialIn2){
          display.clearDisplay(); display.display(); 
          currentState = SinWave;
        }
        if(BP_pot3 || serialIn3){
          display.clearDisplay(); display.display(); 
          currentState = TriangleWave;}
        break;

      case LogicAnalyserMode:
        checkConditions();
        if(buttonPressed || serialIn0){
          display.clearDisplay(); display.display(); 
          currentState = SelectionMenu;  
          buttonPressed = false;
        }
        break;

      case SquareWave:
        squareWave();
        checkConditions();
        if(buttonPressed || serialIn0){
          display.clearDisplay(); display.display(); 
          resetSignal();
          currentState = FuncGenMode;  
          buttonPressed = false;
        }
        break;

      case SinWave:
        sinWave();
        checkConditions();
        if(buttonPressed || serialIn0){
          display.clearDisplay(); display.display(); 
          resetSignal();
          currentState = FuncGenMode;  
          buttonPressed = false;
        }
        break;

      case TriangleWave:
        triangleWave();
        checkConditions();
        if(buttonPressed || serialIn0){
          display.clearDisplay(); display.display(); 
          resetSignal();
          currentState = FuncGenMode;  
          buttonPressed = false;
        }
        break;
  
      default:
        //ignore
        break;
    }
}


  
    void startScreen (){
      
      display.fillRoundRect(0, 0, display.width()-1, 45,
      10, WHITE);
      
      static int16_t WelcomeXPos = 17;  
      static int16_t WelcomeYPos = 16;  
      display.setTextSize(2); display.setTextColor(BLACK); // Draw white text, size 1
      display.setCursor(WelcomeXPos, WelcomeYPos);                
      display.println(("Welcome!"));
      
      static int16_t StartXPos = 0;  
      static int16_t StartYPos = 48; 
      display.setTextSize(1); display.setTextColor(WHITE); // Draw white text, size 1
      display.setCursor(StartXPos, StartYPos);       
      display.println(("Press Button OR"));
      display.println(("Send '1' Serial Char"));

      
      display.display();
    }

  
    void menuScreen(){
      display.clearDisplay();

      checkConditions();
      
     
        initialiseOptionsScreen();
        
        display.setTextSize(2); display.setTextColor(WHITE); // Draw white text, size 1
        display.setCursor(4, 4);                
        display.println(("Menu"));

        
        display.setTextSize(1); display.setTextColor(textColor0); // Draw white text, size 1
        display.setCursor(Xpos, Ypos0);                
        display.println(("0. Go Back"));

        
        display.setTextColor(textColor1); // Draw white text, size 1
        display.setCursor(Xpos, Ypos1);                
        display.println(("1. Osci Mode"));

        
        display.setTextColor(textColor2); // Draw white text, size 1
        display.setCursor(Xpos, Ypos2);                
        display.println(("2. Logic An. Mode"));

        
        display.setTextColor(textColor3); // Draw white text, size 1
        display.setCursor(Xpos, Ypos3);                
        display.println(("3. Func. Gen. Mode"));

        
        display.display();
    }

  
    void osciMode(){
      
      static uint32_t previousTime_us = 0; //Declares only once
      uint32_t currentTime_us = micros();

      if ((currentTime_us - previousTime_us) >= scanTime_us){
        simpleOscilloscope();

        
        previousTime_us = currentTime_us;
        
      }
    }

  
    void funcGenMode(){
      display.clearDisplay(); 
      
      checkConditions();
      initialiseOptionsScreen();

     
        display.setTextSize(2); display.setTextColor(WHITE); 
        display.setCursor(4, 4);                
        display.println(("Func. Gen."));

        //Option 0
        display.setTextSize(1); display.setTextColor(textColor0); 
        display.setCursor(Xpos, Ypos0);                
        display.println(("0. Go Back"));

        //Option 1
        display.setTextColor(textColor1); 
        display.setCursor(Xpos, Ypos1);                
        display.println(("1. Square Wave"));

        //Option 2
        display.setTextColor(textColor2); 
        display.setCursor(Xpos, Ypos2);                
        display.println(("2. Sine Wave"));

        //Option 3
        display.setTextColor(textColor3); 
        display.setCursor(Xpos, Ypos3);                
        display.println(("3. Triangle Wave"));

        //Display All
        display.display();

    }
  //Triangle Wave mode
    void triangleWave(){
      //Declare Timing Variables
      static uint32_t previousTime_us = 0; 
      uint32_t currentTime_us = micros();


      if ((currentTime_us - previousTime_us) >= scanTime_us){
       
        static bool countUp = false;
        static bool countDown = false;

       
        if(currYSigVal <= 0){
          countUp = true;
          countDown = false;
        }

        if(currYSigVal >= triangSigRange){
          countDown = true;
          countUp = false;
        }

        
        if(countUp){currYSigVal = currYSigVal + 50;}
       
        if(countDown){currYSigVal = currYSigVal - 50;}
        

        analogWrite(DAPin, currYSigVal);
        

        
        simpleOscilloscope();

      }
    }
  
  //Sine Wave Mode
    void sinWave(){
      //Declare Timing Variables
      static uint32_t previousTime_us = 0; //Declares only once
      uint32_t currentTime_us = micros();


    if ((currentTime_us - previousTime_us) >= scanTime_us){
      //============= Generating Signal =============
        //X signal Values
        if(XSigVal >= 0 && XSigVal <= plotWidth){XSigVal++;} //Configure counter
        else{XSigVal = 0; display.clearDisplay();}
        //Y signal Values
        YSigVal = 0; //Current signal value
        XSinVal = map(XSigVal,0,plotWidth,0,62831); //Map plot width to 2*Pi*10000
        YSigVal = sin((double)XSinVal/10000) * sinSigRange/2 + sinSigRange/2;

      //Output D/A signal
        analogWrite(DAPin, YSigVal);

      //Plot Values
        simpleOscilloscope();

    }
  }

  //Square Wave Mode
    void squareWave(){
      //Declare Timing Variables
      static uint32_t previousTime_us = 0;
      uint32_t currentTime_us = micros();

      if ((currentTime_us - previousTime_us) >= squareScanTime_us){
       
         
            if(XSigVal >= 0 && XSigVal <= plotWidth){XSigVal++;} 
            else{XSigVal = 0; display.clearDisplay();}
          
          
          if(XSigVal >= 0 && XSigVal < plotWidth/4){
            YSigVal = 0;
          }
          if(XSigVal >= plotWidth/4 && XSigVal < plotWidth/2){
            YSigVal = squareSigRange;
          }
          if(XSigVal >= plotWidth/2 && XSigVal < 3*plotWidth/4){
            YSigVal = 0;
          }
          if(XSigVal >= 3*plotWidth/4 && XSigVal < plotWidth){
            YSigVal = squareSigRange;
          }

        
          analogWrite(DAPin, YSigVal);
          
        
        simpleOscilloscope();

        previousTime_us = currentTime_us; 
      }
    }
    

  
    void ISR_Button(){
      static uint32_t previousMillisButton = 0;
      uint32_t currentMillisButton = millis();
        if ((currentMillisButton - previousMillisButton) >= debounceTime_ms){
          previousMillisButton = currentMillisButton;
          buttonPressed = true;
        }
    }

  
    void checkConditions(){
      
      potSelectVal = map(analogRead(potPin),0,1023,0,3);//Pot value from 0-3
      
      
      uint8_t incomingBit = Serial.read();
      
      if(buttonPressed == true && (potSelectVal ==0)){
        BP_pot0 = true; //Button pressed, potVal0
        //buttonPressed = false;
      } 
      else{BP_pot0 = false;}

      if(buttonPressed == true && (potSelectVal ==1)){
        BP_pot1 = true; //Button pressed, potVal1
        //buttonPressed = false;
      } 
      else{BP_pot1 = false;}

      if(buttonPressed == true && (potSelectVal ==2)){
        BP_pot2 = true; //Button pressed, potVal2
        //buttonPressed = false;
      } 
      else{BP_pot2 = false;}

      if(buttonPressed == true && (potSelectVal ==3)){
        BP_pot3 = true; //Button pressed, potVal3
        //buttonPressed = false;
      } 
      else{BP_pot3 = false;}

      if(incomingBit == '0'){serialIn0 = true;}
      else{serialIn0 = false;}

      if(incomingBit == '1'){serialIn1 = true;}
      else{serialIn1 = false;}

      if(incomingBit == '2'){serialIn2 = true;}
      else{serialIn2 = false;}

      if(incomingBit == '3'){serialIn3 = true;}
      else{serialIn3 = false;}
    }

  
    void resetSignal(){
      currYSigVal = 0; 
      currXDrawVal = 0; 
      analogWrite(DAPin, 0);

      YSigVal = 0;
      XSigVal = 0;
      XSinVal = 0;
    }
  
  
    void initialiseOptionsScreen(){
     
      uint16_t cursor = potSelectVal; 

      if(cursor==0){cursorYPos = Ypos0-2; textColor0 = BLACK;}
      else{textColor0 = WHITE;}

      if(cursor==1){cursorYPos = Ypos1-2; textColor1 = BLACK;}
      else{textColor1 = WHITE;}

      if(cursor==2){cursorYPos = Ypos2-2; textColor2 = BLACK;}
      else{textColor2 = WHITE;}

      if(cursor==3){cursorYPos = Ypos3-2; textColor3 = BLACK;}
      else{textColor3 = WHITE;}

      display.fillRoundRect(cursorXPos, cursorYPos, display.width()-1, 10,
      5, WHITE);
    }

  
    void simpleOscilloscope(){
    //X Draw Values
    uint32_t prevXDrawVal = currXDrawVal-1;
    if(currXDrawVal >= 0 && currXDrawVal <= plotWidth){currXDrawVal++;} //Configure counter
    else{currXDrawVal = prevXDrawVal = 0; display.clearDisplay();}
    

    
    uint32_t potVal = analogRead(ch1Pin); 
    uint32_t volts_mV = map(potVal,0,1023,0,maxVoltage_mV);

   
    static uint32_t prevYDrawVal = 0;
    static uint32_t currYDrawVal = 0;
    prevYDrawVal = currYDrawVal; //y value from previous cycle
    currYDrawVal = plotHeight - map(analogRead(ch1Pin),0, 1023, 0, plotHeight);
    currYDrawVal = currYDrawVal + plotHeightOffset;

    
    display.drawLine(0,SCREEN_HEIGHT-1,SCREEN_WIDTH-1,SCREEN_HEIGHT-1, WHITE);
   
    display.drawLine(0, plotHeightOffset, 0, SCREEN_HEIGHT-1, WHITE);
    
    
    static int16_t displayValXPos = (SCREEN_WIDTH-1)/2 + 2;  //Start at 1/3 of screen
    display.fillRect(displayValXPos, 0, displayValXPos -2, plotHeightOffset, BLACK);
    display.setTextSize(1); display.setTextColor(WHITE); // Draw white text, size 1
    display.setCursor(displayValXPos, 0);                // Start at top middle
    display.print(("Y = "));
    display.print((volts_mV));
    display.println(("mV"));

    
    display.drawLine(prevXDrawVal, prevYDrawVal, currXDrawVal, currYDrawVal, WHITE);
    Serial.println(volts_mV);
    
    
    display.display();  
}