# HAUShomeAutomationSystem
This is a university project for Microprocessors course in Işık University.

# Summary
![IMG_4629](https://user-images.githubusercontent.com/53571773/82151822-361a4980-9866-11ea-9bff-d774017bd394.JPG)
The Wifi Based Home Automation System is including main features which are lamps, temperature and gas sensor, and additionally a sterilization box for sterilizing the bags and cargos that wanted to be sterilized. A mobile application for controlling all those has been built.

# Design 
Basic circuit design is given below.
![Untitled Sketch 2_bb](https://user-images.githubusercontent.com/53571773/82151854-5fd37080-9866-11ea-8d83-9b56c153c298.jpg)
Materials used in circuit: 
• 2* NodeMcu 
• 3*Led 
• 4 Channel Relay Module 
• 6 Volt Liquid Pump 
• Dht11 Temperature-Humidity Sensor 
• Hc-sr04 Ultrasonic Distance Sensor 
• MQ2 Gas Sensor

# Requirements
Interrupt: A wireless interrupt is used in this project which is triggered by another NodeMcu board. The emergency button in the mobile application changes a variable called power from “0” to “1” on the database. As soon as the value changes the interrupt NodeMcu reads the data, triggers a relay which is connected to the main NodeMcu board, and changes the variables that controls the states of output elements to off. The interrupt triggered on the main board changes every output elements to off state and waits 6 second to restart working.  
Timer: Timer is used for a Morning Routine. Every morning the routine starts with switching on bedroom lights and at the same time triggering a relay that is used in kitchen, then switches on the bathroom lights, then living room lights, switches off and morning routine finishes. 
EEPROM: EEPROM is used to store a authentication code like a customer number to change the password and it is also stored in the database and updated everytime NodeMcu boots up.
Wireless Communication: Wifi is used to communicate with the android app.

# Implementation
The project can be divided to five parts. 
1.Model House
