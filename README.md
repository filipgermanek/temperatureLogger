# temperatureLogger

## Contents: 
1.Introduction
2.Assembly
3.Installation
4.Interaction

## 1.Introduction
This is a project for temperature logging and publishing the results to Adafruit feed. The way it works is that we have a DHT11 temperature sensor connected to Wemos board. The sensor measures temperature and publishes the results to the specified Adafruit feed. 

## 2.Assembly
Materials: Wemos board, DHT11 sensor, Micro USB cable
Wiring: You need to connect three wires from the wemos board to the DHT11 sensor. Connect 5v to v5, Di to D2 on the board and G to G.
![Wiring](https://user-images.githubusercontent.com/6553481/50425413-c8870b00-0875-11e9-9c3a-52ab4571ee87.png)


## 3.Installation
You will need Arduino software which can be downloaded using this link: https://www.arduino.cc/en/main/software
After the install is complete you will need to install ESP8266 package.
To do it follow these steps : 
1. Open the Preferences window in the Arduino IDE
2. Enter http://arduino.esp8266.com/stable/package_esp8266com_index.json into Additional Board Manager URLs field.
3. Open the Boards Manager from Tools > Board menu and install the esp8266 platform

You will also need to install DHT sensor library.
Last step is creating Adafruit account if you dont have one yet. It can be done here: http://io.adafruit.com/

## 4.Interaction
Wifi name, password as well as Adafruit feed name and key are hardcoded.
To interact with the code you have to change the wifi name and password to match your wifi name and password. Adafruit feed name and key has to be changed as well.
