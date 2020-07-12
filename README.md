# Project 1 : “Logic Analyzer + Minimal Oscilloscope + Signal Generator” 

# 1.ABSTRACT
The aim of the project  is to design and construct a prototype with the functionality of a minimal oscilloscope, function generator with signal square, traingle and sin signal as output and also consist of a logic analyser. This  prototype was constructed on a breadboard using a Teensy 3.2 development board and operated by a button, potentiometer, and PC USB to UART communication. The system's display made use of an SSD1306 OLED screen and UART to PC USB, visualised on a program called SerialPlot.This 
prototype not included the logic analyser function.

# 2.INTRODUCTION

The aim of this project was to design and construct a prototype of a system with the functionality of a minimal oscilloscope, signal generator with square wave, triangle wave and sine wave as output signal, and a logic analyser.

The requirements of the project are as follows:

1.One channel oscilloscope (0V - 3.3V) using the uC ADC peripheral

2.One channel function generator using the uC DAC with the option to select between at least a square, triangle and sin signal)

3.One channel logic analyzer, that allows for decoding of a 9600 baud serial frame

4.When acting in one of the above-mentioned modes, the relevant signals should be streamed out in “real-time” via UART(-> USB) to a connected PC and visualized using a serial plotter and in parallel displayed on the provided OLED display.

5.It should be possible to control the different functions(modes) via connected push-buttons and in parallel via commands send from the PC to the uC via USB(->UART)

6.The system should be structured and implemented as a finite state machine

The protype was designed and constructed on a breadboard using the following components:

* Teensy 3.2 Microcontroller development board

* SDD1306 I2C controlled OLED Display

* 10kOhm potentiometer

* Pushbutton

* Jumper wires

# Youtube Link
  https://youtu.be/8VC8J7hFTMM

# 3.METHODS 

# Prototype Image
   
![enter image description here](https://github.com/rueben593/logic-analyzer/blob/master/bread%20board%20ckt.jpg)

   # Schematic
   
   ![enter image description here](https://github.com/rueben593/logic-analyzer/blob/master/schematic%20fritz_schem.jpg)
   

# Finite State Machine
   
   A moore finite machine is used for the program.In moore output actions only determined by its current state
   
   # States
     
   Start Screen
 * Selection Menu
 * Osci. Mode
 * Func.Gen. Mode
* Logic An. Mode
* Square wave
 * Sine wave
 * Triangle Wave

# Events

 * Button_Pressed
 * Button_Pressed_and_potVal0
 * Button_Pressed_and_potVal1
 * Button_Pressed_and_potVal2
 * Button_Pressed_and_potVal3
 * Serial_input_1
 * Serial_input_2
 * Serial_input_3

# Actions

 Square wave signal
 Sine wave signal
 Triangle wave signal
 Read channel signal
 Analyse logic
 OLED waveform display
 OLED text display
 Serial plot waveform display

# State Transition Diagram

![enter image description here](https://github.com/rueben593/logic-analyzer/blob/master/state%20transition%20diagram.jpg)


# Implementation Of Finite State
   
   Finite State  Setups
   
//Events
volatile bool buttonPressed = false;
bool BP_pot0 = false; //Button pressed and pot value 0
bool BP_pot1 = false; //Button pressed and pot value 1
bool BP_pot2 = false;
bool BP_pot3 = false;
bool serialIn0 = false; //Serial input 0
bool serialIn1 = false; //Serial input 1
bool serialIn2 = false;
bool serialIn3 = false;

//States
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
   
  Enum -An enum type is a special data type that enables for a variable to be a set of predefined constants. The variable must be equal to one of the values that have been predefined for it.
  
  # Main program
  Finite State Machine 
  
switch (currentState) {
    case StartScreen:
        Serial.println("Screen");
        checkConditions();
        if(buttonPressed || serialIn1){
        currentState = SelectionMenu; 
        buttonPressed = false;
        }
        break;

    case SelectionMenu:
        Serial.println("Menu");
        checkConditions();
        if(buttonPressed || serialIn0){
        currentState = StartScreen; //Go back
        buttonPressed = false;
        } 
        if(BP_pot1 || serialIn1){currentState = OsciMode;}
        if(BP_pot2 || serialIn2){currentState = LogicAnalyserMode;}
        if(BP_pot3 || serialIn3){currentState = FuncGenMode;}
        break;

    case OsciMode:
        Serial.println("OsciMode");
        checkConditions();
        if(buttonPressed || serialIn0){
        currentState = SelectionMenu;  //Go back
        buttonPressed = false;
        }
        break;

    case FuncGenMode:
        Serial.println("FuncGenMode");
        checkConditions();
        if(buttonPressed || serialIn0){
        currentState = SelectionMenu; //Go back
        buttonPressed = false;
        } 
        if(BP_pot1 || serialIn1){currentState = SquareWave;}
        if(BP_pot2 || serialIn2){currentState = SinWave;}
        if(BP_pot3){currentState = TriangleWave;}
        break;

    case LogicAnalyserMode:
        Serial.println("LogicAnalyserMode");
        checkConditions();
        if(buttonPressed || serialIn0){
        currentState = FuncGenMode;  //Go back
        buttonPressed = false;
        }
        break;

    case SquareWave:
        Serial.println("SquareWave");
        checkConditions();
        if(buttonPressed || serialIn0){
        currentState = FuncGenMode;  //Go back
        buttonPressed = false;
        }
        break;

    case SinWave:
        Serial.println("SinWave");
        checkConditions();
        if(buttonPressed || serialIn0){
        currentState = FuncGenMode;  //Go back
        buttonPressed = false;
        }
        break;

    case TriangleWave:
        Serial.println("TriangleWave");
        checkConditions();
        if(buttonPressed || serialIn0){
        currentState = FuncGenMode;  //Go back
        buttonPressed = false;
        }
        break;

    default:
        //ignore
        break;
    }

Events Implementation

The events were checked using the code for the following function:

//***Function to check event conditions***
    void checkConditions(){
    //Pot value selection
    potSelectVal = map(analogRead(potPin),0,1023,0,3);//Pot value from 0-3
    
    /*
    //Debugging
    Serial.print(potSelectVal);
    Serial.print(",");
    Serial.print(buttonPressed);
    */
    
    //Serial inputs
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

Function to reset signal

    void resetSignal(){
    currYSigVal = 0; //Reset signal before moving
    currXDrawVal = 0; 
    analogWrite(DAPin, 0);

    YSigVal = 0;
    XSigVal = 0;
    XSinVal = 0;
    }
It uses 'if' and 'else' statements to determine which events are active (true) or nonactive (false).


   
   # I2C PROTOCOL
   
 The Inter-Integrated Circuit (I2C) Protocol is a protocol intended to allow multiple "slave" digital integrated circuits ("chips") to communicate with one or more "master" chips. Like the Serial Peripheral Interface (SPI), it is only intended for short distance communications within a single device. Like Asynchronous Serial Interfaces (such as RS-232 or UARTs), it only requires two signal wires to exchange information.


![enter image description here](https://github.com/rueben593/logic-analyzer/blob/master/Introduction-to-I2C-Data-Transmission-Diagram-Data-Frame.png)

   # FIGURE: I2C PROTOCOL
   
   
   # Push Button
   
  Push button assigned to the 12th pin of the teensy 3.2 .It intialises with the pins internal pullup resistor.
  
  # External Interrupt
  
  This is the program for the ISR . When the interrupt occur isr executes.
  
  void ISR_Button(){
    static uint32_t previousMillisButton = 0;
    uint32_t currentMillisButton = millis();
        if ((currentMillisButton - previousMillisButton) >= debounceTime_ms){
        previousMillisButton = currentMillisButton;
        buttonPressed = true;
        }
    }
    
   # Debouncing
   Pushbuttons often generate spurious open/close transitions when pressed, due to mechanical and physical issues: these transitions may be read as multiple presses in a very short time fooling the program.Without debouncing, pressing the button once may cause unpredictable results. 
   
   
  #  Potentiometer
  
   The potentiometer was used for the menu option selection cursor value by mapping its range of 0-1023 to a range of 0-3
   
   # Minimal Oscilloscope 
   
  Code for this program
 
   
   //X Draw Values
uint32_t prevXDrawVal = currXDrawVal-1;
if(currXDrawVal >= 0 && currXDrawVal <= plotWidth){currXDrawVal++;} //Configure counter
else{currXDrawVal = prevXDrawVal = 0; display.clearDisplay();}


//Channel 1 A/D reading and mV mapping
uint32_t potVal = analogRead(ch1Pin); 
uint32_t volts_mV = map(potVal,0,1023,0,maxVoltage_mV);

//Y Draw Values
static uint32_t prevYDrawVal = 0;
static uint32_t currYDrawVal = 0;
prevYDrawVal = currYDrawVal; //y value from previous cycle
currYDrawVal = plotHeight - map(analogRead(ch1Pin),0, 1023, 0, plotHeight);
currYDrawVal = currYDrawVal + plotHeightOffset;

//===================== OLED Screen Plotting =====================
//Draw X Axis
display.drawLine(0,SCREEN_HEIGHT-1,SCREEN_WIDTH-1,SCREEN_HEIGHT-1, WHITE);
//Draw Y Axis
display.drawLine(0, plotHeightOffset, 0, SCREEN_HEIGHT-1, WHITE);

//Display Value
static int16_t displayValXPos = (SCREEN_WIDTH-1)/2 + 2;  //Start at 1/3 of screen
display.fillRect(displayValXPos, 0, displayValXPos -2, plotHeightOffset, BLACK);
display.setTextSize(1); display.setTextColor(WHITE); // Draw white text, size 1
display.setCursor(displayValXPos, 0);                // Start at top middle
display.print(("Y = "));
display.print((volts_mV));
display.println(("mV"));

//Plot Values
display.drawLine(prevXDrawVal, prevYDrawVal, currXDrawVal, currYDrawVal, WHITE);
Serial.println(volts_mV);

//Update Screen
display.display(); 

# Function Generator

The function generator state in the program works as another menu screen.We can select square,triangle and sin wave in the function generator mode.

# Square Wave
 
 Code for the square wave signal

    static uint32_t previousTime_us = 0; //Declares only once
    uint32_t currentTime_us = micros();

    if ((currentTime_us - previousTime_us) >= squareScanTime_us){
        //============= Generating Signal =============
        //X signal Values
            if(XSigVal >= 0 && XSigVal <= plotWidth){XSigVal++;} //Configure counter
            else{XSigVal = 0; display.clearDisplay();}
        
        //Y signal Values
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

        //Output D/A signal
        analogWrite(DAPin, YSigVal);
        
        //Plot Values
        simpleOscilloscope();

        previousTime_us = currentTime_us; 
    }
    
# Triangle Wave

   Code for the triangle wave
   
//Declare Timing Variables
    static uint32_t previousTime_us = 0; //Declares only once
    uint32_t currentTime_us = micros();


#if ((currentTime_us - previousTime_us) >= scanTime_us){
        //Local Variables
        static bool countUp = false;
        static bool countDown = false;

  #//============= Generating Signal =============
        //Counting Conditions
        if(currYSigVal <= 0){
        countUp = true;
        countDown = false;
        }

  #if(currYSigVal >= triangSigRange){
        countDown = true;
        countUp = false;
        }

   #//Counting Up
        if(countUp){currYSigVal = currYSigVal + 50;}
        //Counting Down
        if(countDown){currYSigVal = currYSigVal - 50;}
        

  #analogWrite(DAPin, currYSigVal);
        

   #//Plot Values
     #simpleOscilloscope();

    }
    }
    
# Sine Wave

Code for the sine wave

//Sine Wave Mode
    void sinWave(){
    //Declare Timing Variables
    static uint32_t previousTime_us = 0; //Declares only once
    uint32_t currentTime_us = micros();


 #if ((currentTime_us - previousTime_us) >= scanTime_us){
  //============= Generating Signal =============
        //X signal Values
        if(XSigVal >= 0 && XSigVal <= plotWidth){XSigVal++;} //Configure counter
        else{XSigVal = 0; display.clearDisplay();}
        //Y signal Values
        YSigVal = 0; //Current signal value
        XSinVal = map(XSigVal,0,plotWidth,0,62831); //Map plot width to 2*Pi*10000
        YSigVal = sin((double)XSinVal/10000) * sinSigRange/2 + sinSigRange/2;

  #//Output D/A signal
        analogWrite(DAPin, YSigVal);

  #//Plot Values
        simpleOscilloscope();

   
   
  # Logic Analyzer
   
   In this experiment i caanot do the logic analyzer.
   
   
   
   # 4.Results
   
   In this experiment I get all the modes excluding logic analyzer.I do not konow the aspect of the logic analyser. I am fully satisfied with the experiment.
     
   # 5. Discussion
   
   This prototype succeds in all modes except logic analyzer.
   
   # 6.REFERENCES
    
  Circuit Basics. (n.d.). Introduction to I2C Single Master Single Slave https://www.google.com/url?sa=i&url=https%3A%2F%2Fwww.circuitbasics.com%2Fbasics-of-the-i2c-communication-protocol%2F&psig=AOvVaw1plctt76g5Bf26Wgw3pCst&ust=1594630830851000&source=images&cd=vfe&ved=0CAMQjB1qFwoTCPixl_asx-oCFQAAAAAdAAAAABAD




   
