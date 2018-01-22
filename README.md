# SmartKanne

### 1. Introduction
This project was created for the Ubiquitous Computing Course at the Karlsruhe Institute of Technology. The goal of this course is to learn about the development process of a smart appliance. Topics covered in this course are techniques for finding a good idea, analyse your potential customers, sketching methods as well as the technical part like hardware including sensors, actuators and knowledge about arduino.

#### 1.1 Project structure
| Folder    |     Content |
|:--------|:-------------------- |
| README.md | This file. Information about the project in github flavoured markup ([GFM](https://github.github.com/gfm/) )|
| src/ | Contains source code for uploading to arduino|
| docs/schema/ | Contains schema of the electrocins and bill of material. Created with [Fritzing](http://fritzing.org/home/) |
| docs/sketches/ |Contains images of the sketches that were made in the project planning |
|docs/state_diagram/| Contains the state diagram of the finite state machine used in this project. Created with [Dia](https://wiki.gnome.org/Apps/Dia) 
| docs/housing/ | Contains images of the used pot as well as a very basic draft for the 3D printer to enlarge the pot housing. Created with [FreeCAD](https://www.freecadweb.org/?lang=de) |

### 2. Project idea
The idea for this problem came to me during the winter months drinking a lot of tea. However, every time I made a tea I forgot to take the tea bags out of the pot so very often the tea became bitter in the end.
I want to solve this problem by developing this SmartKanne. This device should help me not to forget about my tea. Also it should be able to give me instructions about the right temperature and time for each tea to get the best possible result when steeping tea.

### 3. Requirements
Here I list the basic requierements SmartKanne should be able to cover:

| Requirement    |     Description |
|:--------|:-------------------- |
|Tea selection|The user should be able to select the type of tea he wants to make|
|Tea information|Depending on the type of tea, SmartKanne should know the recommended temperature as well as the steep time |
|Notification|If the tea is ready to drink, SmartKanne should be able to notify to the user |
|Monitor process|In order to let the user know about the progress of his tea, SmartKanne should be able to give feedback to the user about the process|
|Mobile|The device should be able to be carried around while the tea is in progress, so there is no need to wait at a certain point.|


### 4. Designs
In order to cover the features from section 3, SmartKanne needs some additional hardware to fullfill the requierements. In this section I show you some sketches I made in the development process.

#### 4.1 Use Smartphone as user interface
One idea to satisfy the requirements is to control SmartKanne by a smartphone which can communicate over bluetooth low energy or  wifi or something similar. This would have the advantage to allow a lot of settings for the smart kanne, since you have an full interface with all possible UI elements.

![sketch smartphone][sketch1]


#### 4.2 Standalone
Onaother possibility to create the user interface for SmartKanne is to use additional hardware. This design allows the gadget to be used independently from other devices and lowers the complexity of usage. Furthermore external sources of errors are excluded. For the power supply there has to be an battery pack included to ensure a convenient usage of the device.

![sketch standalone][sketch2]

#### 4.3 Base station
Design number 3 is an approach without external devices as well. However, the idea here is to put all the electronics in an base station where you can put an pot that is then connected automatically. This way multiple pots could be used with one base station(multi user support with multiple pots). The pot would then just include the temerature sensor which would be connected when the pot is put into the station. The disadvantage is that you have to wait till the tea is done to take the pot with you and leave the station behind. Then the base station could be powered by an outlet since it will be stationary anyway. 

![sketch base station][sketch3]

### 5. Design Decicion 
In order to build a n appliance the approch number 4.2 seems the best choice in order to have a big impact in the process of making tea. The limitation of user interaction prevents the device from getting to complex and developing some kind of “feature creep”. 
The usage of an additional smart phone brings a lot of overhead an in total two devices are needed for the process of making tea. The idea with the base station interferes with the idea that you are not bound to a certain place and you can carry the hole device around to the place where you want to enjoy your tea.

### 6. Inforamtion about the tea types
In order to steep the right  amount of time, information about the right times are taken from 
[here](https://www.lebensmittellexikon.de/t0002940.php#0) 
### 7. Hardware
In oder to build the device which fulfill the requirements from the table above, additional hardware is needed. In this section you find the bill of materials.

| Amount   |      Part Type      |  Descripiton |
|----------|:---------------------|:------| 
|1| DS18B20 1-Wire Temperature Sensor|Temperature sensor to measure the current temperature as well as detect if water is in the pot or not|
|1|Piezo Speaker|Speaker to give accustic feedback to user|
|1|LCD screen|Screen for the user interface of the device|
|1|LCM1602 IIC|Additional hardware for controlling LCD screen over IIC|
|1|Arduino Uno (Rev3)|Arduino as the core of the device|
|1|RFID-RC522|RFID Reader to allow automatic tea selection|
|1|220Ω Resistor|Needed for piezo speeker|
|1|4.7kΩ Resistor|Needed for temperature sensor|
|2|Momentary Switch|Switches to allow user interaction|

### 8. Schema
Shows the general setup and connection of the hardware components.  Created with [Fritzing](http://fritzing.org/home/)

![schema of project][schema]


### 9. Software
The source code can be found in this repository. The basic concept behind it is to use a finite state machine for the general structure of the program. Here you can see the simple structure of the states and its transitions which is then implemented using the fsm library for arduino. For the control of the screen and the rfid reader available libraries are used. 

![states and transitions][states]

### 10. Housing
For the prototype an tea pot like [this](https://www.amazon.de/Emsa-504232-Isolierkanne-Verschluss-Transluzent/dp/B002BWOOYS?th=1)  is used. 

![pot][pot]

You can easily open up the bottom part and take out the glass cylinder. As first approch all the hardware is simply placed in the space beetween the housing and the bottom, which means the bottom can not be closed properly. In order to fix this, fearure approcheds could enlarge the space by 3D printing a new bottom part like the one which can be seen in the 3d Sketch.

![housing extension][pot extension]

 It is only a very basic base where you can put the pot on top with a cutout for the display. For more advanced approches you can add a thread for fixing the part at the bottom of the pot.
 
 
### 11. Business Model Canvas
In order to get an overview over the business model, here you can see the business model canvas of SmartKanne. It can also be accessed over this [link](https://canvanizer.com/canvas/rdbEy04koZJil).

![business model canvas][bmc]


[sketch1]: docs/sketches/kanne_smartphone.png "Sketch from SmartKanne with Smartphone"
[sketch2]: docs/sketches/kanne_standalone.png "Sketch from SmartKanne Standalone"
[sketch3]: docs/sketches/kanne_base_station.png "Sketch from SmartKanne with base station"
[schema]: docs/schema/SmartKanne_0.1_bb.png "Schema from SmartKanne"
[pot]: docs/housing/kanne.png "Image of pot used for project" 
[pot extension]: docs/housing/base.svg "Image of pot extension" 
[states]: docs/state_diagram/states.jpeg "State diagram" 
[bmc]: docs/business_model_canvas/business_model_canvas.png "Business Model Canvas" 