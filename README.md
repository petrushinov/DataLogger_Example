DataLogger Example Project
==========================

The project:
------------
This is an example project of a data logger based on the sends data from sensors to a server via a wireless network. 
My plan is that project will develop in the future with more software modules.

Code functionality at the moment
---------------------------------
If the authorization data is in the code

1. configuration of room-02
2. connecting to a wifi network
3. connecting to the server
4. measuring value from analog input
5. sending data to the server

If the authorization data is entered through a terminal

1. fill in ssid, ssid password, APYkey, server address, server port
2. writes authorization data to internal flash on a microcontroller
3. read authorization data from internal flash on a microcontroller
4. wroom-02 configuration
5. connect to wifi network
6. connecting to the server
7. measuring value from analog input
8. sending data to the server

Hardware:
---------
WIFI

For wireless connection to WIFI network, my choice is  esp-wroom-02.
This WIFI module communicates with external MCU via UART with AT commands. 
More information about esp-wroom-02 https://www.espressif.com/en/products/modules

MCU

PIC24FJ256GA106

Server:
------
The data collection server used in the project is https://thingspeak.com/
