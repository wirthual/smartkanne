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
| docs/housing/ | Contains a enlargement for the housing of the tea pot. The .slt file can be printed with a 3D-printer. Created with [FreeCAD](https://www.freecadweb.org/?lang=de).  Also an [image](http://www.rfidsign.eu/html/graphics.html) to indicate the RFID capability is included.  |
| docs/misc/ | Contains a Business model plan as well as a cost estimation made with COSYSMO. 

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

### 6. Information about the tea types
In order to steep the right  amount of time, information about the right times are taken from 
[here](https://www.lebensmittellexikon.de/t0002940.php#0) 
### 7. Hardware
In oder to build the device which fulfill the requirements from the table above, additional hardware is needed. In this section you find the bill of materials.

| Amount   |      Part Type      |  Descripiton | Price |
|----------|:---------------------|:------| :------| 
|1| DS18B20 1-Wire Temperature Sensor|Temperature sensor to measure the current temperature as well as detect if water is in the pot or not|  3,65 € 
|1|Piezo Speaker|Speaker to give accustic feedback to user| 2,10 €
|1|LCD screen|Screen for the user interface of the device|  7,99 € 
|1|LCM1602 IIC|Additional hardware for controlling LCD screen over IIC| (Included in display price)
|1|Arduino Uno (Rev3)|Arduino as the core of the device| 24,00 €
|1|RFID-RC522|RFID Reader to allow automatic tea selection| 9,99 €
|1|220Ω Resistor|Needed for piezo speeker| 0,01€
|1|4.7kΩ Resistor|Needed for temperature sensor| 0,01€
|2|Momentary Switch|Switches to allow user interaction| 0,20€
|1|Battery Holder 6xAA|Power supply. Recommended for Arduino: 7 - 12 Volts| 3,00€

Overall price of the electronic components for the prototype:  50,95 €
Tea pot: 15 €
3d-printed housing: ca. 150g of PLA, ca. 7 €
Total: 72,95 €
-----------------------------------------------

### 8. Schema
Shows the general setup and connection of the hardware components.  Created with [Fritzing](http://fritzing.org/home/)

![schema of project][schema]


### 9. Software
The source code can be found in this repository. The basic concept behind it is to use a finite state machine for the general structure of the program. Here you can see the simple structure of the states and its transitions which is then implemented using the fsm library for arduino. For the control of the screen and the rfid reader available libraries are used. 

![states and transitions][states]

### 10. Housing
For the prototype an tea pot like [this](https://www.amazon.de/Emsa-504232-Isolierkanne-Verschluss-Transluzent/dp/B002BWOOYS?th=1)  is used. 

You can easily open up the bottom part and put the cable through the housing in the glass cylinder to measure the temperature. However, then the seiling does not work as expected, thats why the cable is put outside the housing and back into the can from outside. This way the pot does not have to be motified and this approach seems sufficient for a prototype.

For the electronic stuff an enlargement for the pot can be printed. You an find the CAD-model in the folder *docs/housing*. Also an ready-to-print SLT file is included for easy replication.

For further improvements you could add a thread to the model and replace the hole bottom of the tea pot to get a nicer product. 

To get an idea about the model you can see the model [here](docs/housing/housing.pdf)

And here is a timelapse of the printing:
![timelapse of printing][print]

The full video can be found [here](https://youtu.be/i6MLm4RjLGM)
 
 
### 11. Business Model Canvas
In order to get an overview over the business model, here you can see the business model canvas of SmartKanne. It can also be accessed over this [link](https://canvanizer.com/canvas/rdbEy04koZJil).

![business model canvas][bmc]

### 12. Cost Estimation
The cost estimation of around $13000 for this project was done using [COSYSMO](http://csse.usc.edu/tools/ExpertCOSYSMO.php). 

The full result can be found in this [PDF](docs/misc/Smartkanne_COSYSMO.pdf)

### 13. Possible Improvements
* In order to avoid a too long steep time, there could be a motor to pull out the tea bags as soon as the tea is ready.
* By now, the time starts as soon as the water temperature is over a certain threshold. However, if the water temparature is to high or to low for the selected kind of tea there is no warning by now. This behaviour could improve overall tea quality.
* Think about getting the right steep time per tea automatically from the internet depending on scanned [EPC](https://www.epc-rfid.info/). Starting point could be *product markup language* [PML](http://web.mit.edu/mecheng/pml/overview.htm), especially so called [Controls](http://web.mit.edu/mecheng/pml/spec_control.htm) to allow a product to communicate with devices. This would require additional internet connection for the tea pot which would then be a part of the IoT.
* Think about an concept to store additional information right on the RFID tag of the product to give additional information for the customer without needing an internet connection as stated before.(e.g Best Before, Recommended Temerature,etc.) This way customers could also benefit directly from the usage of rfid in retail stores without needing an internet connection for every product. Most of literature only focuses on benefits for retailers or the supply chain, not directly for customers. 
Here some examples:
	* Article in [Forbes](https://www.forbes.com/sites/barbarathau/2017/05/15/is-the-rfid-retail-revolution-finally-here-a-macys-case-study/#151a36b13294) about Macys 
	* White Paper about the [State of RFID](https://www.beacontree.net/wp-content/uploads/2017/12/Auburn-state-of-rfid-2016-white-paper.pdf) in apparel shops
	* [Rfid in retail Study 2016](http://webcache.googleusercontent.com/search?q=cache:http://www.kurtsalmon.com/en-us/Retail/vertical-insight/1628/Kurt-Salmon-RFID-in-Retail-Study-2016) (only accessible through google cache)
	* [BENEFITS AND RISKS OF RFID TECHNOLOGY IN RETAIL FROM THE YOUNGER CUSTOMERS POINT OF VIEW](https://hrcak.srce.hr/ojs/index.php/plusm/article/download/3871/2258) 
	* [EPC/RFID – Die Zukunft hat begonnen ](https://www.gs1-germany.de/fileadmin/gs1/basis_informationen/epc_rfid_die_zukunft_hat_begonnen.pdf)

* By now, the only way the user is notified is over an audio signal (beeping). Think about using blinking or haptic as well for impaired people
* Think about measuring the amount of tea, this way Smartkanne could provide extensive statistics about the consum of a user for the quantified self

### 13. Further Information
#####Rough Lifetime estimation (very conservative):
Power consumption:
[LCD](https://www.sparkfun.com/datasheets/LCD/GDM1602K.pdf): 4mA + 160mA with Backlight
[RFID](https://www.nxp.com/docs/en/data-sheet/MFRC522.pdf) 100mA
[Temperature Sensor](https://datasheets.maximintegrated.com/en/ds/DS18B20.pdf) 1mA
[Buuzzer](https://www.cui.com/product/resource/cem-1203-42-.pdf) 35mA
[Arduino](https://store.arduino.cc/arduino-uno-rev3) 50 mA

Overall: ca. 300mA
Alkaline Batteries AA: ca. 2100mAh

Lifetime in use: 7h

Time per Usage: 10min (Longest tea needs 8 minutes + 2 minutes buffer)

Approx. usages per battery load: (7*60min)/10min = 42 usages

With around 1,5 usages a day: Lifetime around 28 days

Note: Turning off the backlight of the display will double the lifetime.

#####Market Research:
Accoding to [this](https://www.statista.com/statistics/326384/global-tea-beverage-market-size/) statistics, the global global tea beverage market is growing constantly and will reach 44.3 billion USD in 2021.

As relation, the [Global TV market revenue](https://www.statista.com/statistics/461324/global-tv-market-sales/) in 2017 was estimated to 105 billion USD. 

#####Similar Products:
[the Smart Tea Pot™](https://sageappliances.co.uk/products/the-sage-smart-tea-pot?variant=52066480708)  £129.95 (01.03.2018)

[the Tea Maker](https://sageappliances.co.uk/collections/tea-makers/products/the-one-touch-tea-maker?variant=40399807556)  £199.95 (01.03.2018) 
in the [YouTube-Video](https://youtu.be/JXULYQFoPrc?t=3m6s) he says: "...its the only one in the world..."but wait: 
[the Tea Maker™](https://www.brevilleusa.com/products/the-one-touch-tea-maker?variant=33819867281) 249$ (01.03.2018) 






[sketch1]: docs/sketches/kanne_smartphone.png "Sketch from SmartKanne with Smartphone"
[sketch2]: docs/sketches/kanne_standalone.png "Sketch from SmartKanne Standalone"
[sketch3]: docs/sketches/kanne_base_station.png "Sketch from SmartKanne with base station"
[schema]: docs/schema/SmartKanne_0.1_bb.png "Schema from SmartKanne"
[states]: docs/state_diagram/states.jpeg "State diagram" 
[bmc]: docs/misc/business_model_canvas.png "Business Model Canvas" 
[print]: docs/housing/printing.gif  "3d printing of housing timelapse" 