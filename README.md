# Tank-Level-Detector
The aim of our project is to sense the level of water in the tank using ultrasonic sensor. This sensed distance is displayed on the serial monitor. The maximum distance between ultrasonic sensor and the water level in this case is kept at 15 cm. As the distance between the ultrasonic and the water level decreases and falls below this threshold value, a message is sent through the GSM Module to the specified user indicating them to switch off the tap. In case if they fail to switch it off and the distance falls below 10cm the user will get a call from the GSM Module. They can switch off the tap through a mobile application, which in turn, is connected with the stepper motor. As soon as the app sends an off signal the stepper motor is rotated and the tap can be turned off.
