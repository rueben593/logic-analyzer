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
   
![enter image description here](https://github.com/rueben593/logic-analyzer/blob/master/IMG_20200710_200306.jpg)

   # Schematic
   
![enter image description here](https://github.com/rueben593/logic-analyzer/blob/master/Untitled%20Sketch%20schematic.jpeg_schem.jpg)


# Finite State Machine
   
   A moore finite machine is used for the program.In more output actions only determined by its current state
   
   # States
     
  # Start Screen
# * Selection Menu
# * Osci. Mode
# * Func.Gen. Mode
# * Logic An. Mode
# * Square wave
# * Sine wave
# * Triangle Wave

# Events

# * Button_Pressed
# * Button_Pressed_and_potVal0
# * Button_Pressed_and_potVal1
# * Button_Pressed_and_potVal2
# * Button_Pressed_and_potVal3
# * Serial_input_1
# * Serial_input_2
# * Serial_input_3

# Actions

# Square wave signal
# Sine wave signal
# Triangle wave signal
# Read channel signal
# Analyse logic
# OLED waveform display
# OLED text display
# Serial plot waveform display
   
   # OLED Screen
   
   # I2C PROTOCOL
   
The Inter-Integrated Circuit (I2C) Protocol is a protocol intended to allow multiple "slave" digital integrated circuits ("chips") to communicate with one or more "master" chips. Like the Serial Peripheral Interface (SPI), it is only intended for short distance communications within a single device. Like Asynchronous Serial Interfaces (such as RS-232 or UARTs), it only requires two signal wires to exchange information.

[!\[enter image description here\](https://github.com/rueben593/logic-analyzer/blob/master/Untitled%20Sketch%20schematic.jpeg_schem.jpg)





