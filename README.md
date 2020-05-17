# HAUShomeAutomationSystem
This is a university project for Microprocessors course in Işık University.

# Summary
![IMG_4629](https://user-images.githubusercontent.com/53571773/82151822-361a4980-9866-11ea-9bff-d774017bd394.JPG)
The Wifi Based Home Automation System is including main features which are lamps, temperature and gas sensor, and additionally a sterilization box for sterilizing the bags and cargos that wanted to be sterilized. A mobile application for controlling all those has been built.

# Design 
Basic circuit design is given below.
![Untitled Sketch 2_bb](https://user-images.githubusercontent.com/53571773/82151854-5fd37080-9866-11ea-8d83-9b56c153c298.jpg)
Materials used in circuit: 
- 2* NodeMcu 
- 3*Led 
- 4 Channel Relay Module 
- 6 Volt Liquid Pump 
- Dht11 Temperature-Humidity Sensor 
- Hc-sr04 Ultrasonic Distance Sensor 
- MQ2 Gas Sensor

# Requirements
Interrupt: A wireless interrupt is used in this project which is triggered by another NodeMcu board. The emergency button in the mobile application changes a variable called power from “0” to “1” on the database. As soon as the value changes the interrupt NodeMcu reads the data, triggers a relay which is connected to the main NodeMcu board, and changes the variables that controls the states of output elements to off. The interrupt triggered on the main board changes every output elements to off state and waits 6 second to restart working.  
Timer: Timer is used for a Morning Routine. Every morning the routine starts with switching on bedroom lights and at the same time triggering a relay that is used in kitchen, then switches on the bathroom lights, then living room lights, switches off and morning routine finishes. 
EEPROM: EEPROM is used to store a authentication code like a customer number to change the password and it is also stored in the database and updated everytime NodeMcu boots up.
Wireless Communication: Wifi is used to communicate with the android app.

# Implementation
The project can be divided to five parts. 
1. **Model House**
![IMG_4622](https://user-images.githubusercontent.com/53571773/82151921-c5276180-9866-11ea-8fe6-56c40adcb574.JPG)
Model house has the leds, temperature sensor, gas sensor. All the leds are controlled from the mobile application and the sensor data can be read from the app. Box cardboard is used for the whole structure. Some printed papers are glued to the floor to have more realistic look. A morning routine using timer is also added to the house, there will be more depth information about that in requirements section.

2. **Sterilization Box**
![IMG_4626](https://user-images.githubusercontent.com/53571773/82151990-2ea77000-9867-11ea-8dc0-6af58227ef85.JPG)
Sterilization box has a tank for the disinfectant liquid with a 6V liquid pump.  It has a ultrasonic sensor(hc-sr04) to indicate in the app that if the box is full or not. The box itself is made of aluminum and pvc transparent cover. Disinfectant liquid is push to the box by a plastic pipe, and sprayed by a nozzle. The nozzle is made by myself from a plastic part which is drilled from the tip. Ultrasonic sensor looks top to bottom vertically. Nozzle looks from a corner to the furthest corner. 
![IMG_4628](https://user-images.githubusercontent.com/53571773/82152005-4252d680-9867-11ea-9a08-3b5b49f9e39d.JPG)

3. **Mobile Application**
![Group 1](https://user-images.githubusercontent.com/53571773/82152039-70d0b180-9867-11ea-8027-33932e5d69cd.png)
The mobile application named H.A.U.S is designed in  a graphic design software called Figma, and built in MIT App Inventor. Application starts with a login page, asks for a password. Password can be changed if the authentication code which is embedded to the NodeMcu’s EEPROM known. The password and authentication code are both stored in database. In main page of the app there are 3 sections: bedroom, living room, bathroom, sterilization box and emergency section. Bedroom, living room and bathroom a have lighting control, kitchen has a relay control that can be used for any electric device, sterilization box has a cleaning button to trigger the liquid pump and box state indicator that shows if box is full or not, and finally the emergency section has an emergency button to stop anything that is going on and restart.  

4. **Database**
![firebase](https://user-images.githubusercontent.com/53571773/82152066-8c3bbc80-9867-11ea-86d9-84a681f75d9b.jpg)
Firebase is used as database for this project. It is best of the free cloud data bases that is tried in process of this project. It doesn’t have a limit for data transfer when for example Thingspeak has 1 data per 15 seconds.  Any data that should be transferred between NodeMcu and mobile application are flows through this data base that can be seen above. 

5. **Circuit Board**
![IMG_4631](https://user-images.githubusercontent.com/53571773/82152077-a5446d80-9867-11ea-8288-469785828002.JPG)
For the circuit board, double side epoxy prototype pcb is used. The NodeMcu’s, leds, sensors and relays are connected to the board by using headers that are soldered to the board. Sketch of the circuit is given in design section.

# Results
The project is successfully done except two bugs are not fixed yet:
1. When the liquid pump is triggered, the interrupt is  triggered. The reason of this is most probably solderings on the prototype pcb. As the interrupt and liquid pump uses the same relay module, there can be a short circuit between these two relays. 
2. When interrupt is triggered the power on the components goes off, on and then off again. This should be an error occurs because of the code. 

Presentation Video Link: https://youtu.be/YyeN4h14otE 
