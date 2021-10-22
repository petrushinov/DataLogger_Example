DataLogger Example Project
==========================

The project:
------------
This is an example project of a data logger based on the sends data from sensors to a server via a wireless network. 
My plan is that project will develop in the future with more software modules.

Video presentation
------------------
[![Watch the video](https://img.youtube.com/vi/bKMoh82h2LE/2.jpg)](https://www.youtube.com/watch?v=bKMoh82h2LE)



Code algorithm at the moment
---------------------------------
If the authorization data is in the code

1. checks WIFI module status (connect or disconnect)

	1.1 If disconnect -> configuration of room-02 -> connecting to a wifi network goes to step 2
	
	1.2 If is connected goes to step 2
	
2. connecting to the server
4. measuring value from analog input
5. sending data to the server goes to step 1

If the authorization data is entered through a terminal

1. checking the first FLSH address

	1.1 If the address is empty goes to step 2
	
	1.2 If the address is not empty goes to step 4
	
2. fill in ssid, ssid password, APYkey, server address, server port
3. writes authorization data to internal flash on a microcontroller
4. read authorization data from internal flash on a microcontroller
5. checks WIFI module status (connect or disconnect)

	5.1 If disconnect -> configuration of room-02 -> connecting to a wifi network goes to step 6
	
	5.2 If is connected goes to step 6
	
6. connecting to the server
7. measuring value from analog input
8. sending data to the server goes to step 5

Hardware:
---------
WIFI

For wireless connection to WIFI network, my choice is  esp-wroom-02.
This WIFI module communicates with external MCU via UART with AT commands. 
More information about esp-wroom-02 https://www.espressif.com/en/products/modules

MCU - PIC24FJ256GA106

Server:
------
The data collection server used in the project is https://thingspeak.com/
