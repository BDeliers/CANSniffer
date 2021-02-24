# Can Sniffer

Connect your car's CAN bus and get interesting data about it !

**BDeliers, february 2021**

Under APACHE 2.0 License

---

This project is a complete harware and software project which allows you to get data from your CAN bus.
It was originally a school project for my last year in electronics engineering school, so it's more a proof of concept than a real working thing. Although, it's a good starting point to interface your car.

---

The concept is simple : every modern car has an OBD-II connector; which informations can we have with it ?
The hardware is simple : a MCP2551 CAN transciever is connected to the CAN bus lines. Then a MCP2515 CAN controller gets data from the bus. This data is then acquired by a PIC18F2550 over the SPI interface of the CAN controller, and the raw data is transferred to the computer through the native USB interface. You have my schematics in the repository.

With the data available on the computer, I did a script that displays raw data from the car and also transforms the raw data to interesting things, as you can see below.

The PC software is an enhanced shell app, using the [blessed](https://pypi.org/project/blessed/) module to have a pretty terminal. The microcontroller firmware is partly handcoded with C language in MPLABX. Of course I used a few librairies to help myself, you'll have all the links below.

The PIC firmware is platform-independant, but for the PC side, I worked on my car, a Peugeot 207 from 2011. The bus I worked on is the "critical" one, with the engine, ESP, Airbags, ABS and so on. All the interpreted datas (speed, temperatures...) are different for each manufacturer (and sometimes every cars). As long as the protocol is closed-source by the car's manufacturer, you'll have to do some retro-engineering or find good datasheets like the ones below to understand what the car says to you.

---

My sources:
- Starting point for the MCP2515 Library : [J1939 C Library for PIC16 MCUs and MCP2515](https://www.microchip.com/wwwproducts/en/en010406)
- USB stack for the PIC : [Microchip MLA](https://www.microchip.com/en-us/development-tools-tools-and-software/libraries-code-examples-and-more/microchip-libraries-for-applications)
- PSA CAN Frames : [PSA CAN](https://autowp.github.io/)
- Peugeot 207 BSI Frames : [Document](http://romain.raveaux.free.fr/teaching/TP207.pdf)

---

PC Software:
![alt tag](https://raw.githubusercontent.com/BDeliers/CANSniffer/main/images/PCSoft.png)

My PCB:
![alt tag](https://raw.githubusercontent.com/BDeliers/CANSniffer/main/images/PCB.jpg)
