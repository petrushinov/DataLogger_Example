# DataLogger_Example

This is an example project of a datalogger based on the sends data to a server via wireless to the internet. 

For wireless connection to WIFI network, my choice is  esp-wroom-02.
This WIFI module communicates with external MCU via UART with AT commands. 
More information about esp-wroom-02 https://www.espressif.com/en/products/modules

The data collection server used in the project is https://thingspeak.com/

The project provides a service communication port (UART1) for configuration and error reading.
