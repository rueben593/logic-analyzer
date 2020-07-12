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

# 3.METHODS 

# Prototype Image
   
![enter image description here](https://github.com/rueben593/logic-analyzer/blob/master/Bread%20Board.jpg)

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
   
   # OLED Screen
   
   # I2C PROTOCOL
   
 The Inter-Integrated Circuit (I2C) Protocol is a protocol intended to allow multiple "slave" digital integrated circuits ("chips") to communicate with one or more "master" chips. Like the Serial Peripheral Interface (SPI), it is only intended for short distance communications within a single device. Like Asynchronous Serial Interfaces (such as RS-232 or UARTs), it only requires two signal wires to exchange information.


![enter image description here](https://github.com/rueben593/logic-analyzer/blob/master/Introduction-to-I2C-Data-Transmission-Diagram-Data-Frame.png)

   # FIGURE: I2C PROTOCOL
   
   
   
   
  # Logic Analyzer
   
   In this experiment i caanot do the logic analyzer.
   
   
   
   # 4.Results
   
   In this experiment I get all the modes excluding logic analyzer.I am fully satisfied with the experiment.
     
   # 5. Discussion
   
   This prototype met all requirements apart from the logic analyzer function and have individual screens for every mode. I did not get enough time to implement the logic analyzer function even though there were ideas on how to do it. The screens for every mode weren't used to keep the state machine simple.
    The performance of the minimal oscilloscope was slow. Thus, the rest of the function generators were slow because of it. The progam was designed to make use of no blocking functions such as 'for' loops, which impacted the method of data plotting on the OLED screen. 
The function generators were not as customisable as they could have been due to the signals being based on the X value of the screen, rather than time. It would have been simpler and more conventional if the signals were time-based.
The sine wave generator serial plot mismatch may have been fixed by using a float variable type to plot the values. 


   
   # 6.REFERENCES
    
  Circuit Basics. (n.d.). Introduction to I2C Single Master Single Slave https://www.google.com/url?sa=i&url=https%3A%2F%2Fwww.circuitbasics.com%2Fbasics-of-the-i2c-communication-protocol%2F&psig=AOvVaw1plctt76g5Bf26Wgw3pCst&ust=1594630830851000&source=images&cd=vfe&ved=0CAMQjB1qFwoTCPixl_asx-oCFQAAAAAdAAAAABAD




   
