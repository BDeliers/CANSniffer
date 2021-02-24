"""

    Simple script to receive data from the MCP2515 CAN bus module, over USART
    Here is used to make a bus sniffer over a PIC18F2550
    Frames are interpreted for a Peugeot 207 year 2011 car
    BDeliers - 02/2021

"""

# -*- coding: UTF-8 -*-

# Imports
import serial
import signal
import sys
import blessed
import math

class MCP2515Frame:
    """
        MCP2515 received frame formatting
    """

    def __init__(self, frame):
        """
            Constructor
            Get MCP2515 frame and make an object with it
            Cf datasheet p.30
        """

        # Containers
        self.srr = False
        self.ide = False
        self.rtr = False

        self.sid = 0
        self.eid = 0
        self.dlc = 0

        self.data = [0, 0, 0, 0, 0, 0, 0, 0]

        # If frame is full we can crate the object
        if (len(frame) >= 13):
            # Data formatting
            self.sid = ((frame[0] & 0b11111111) << 3) | ((frame[1] & 0b11100000) >> 5)
            self.eid = ((frame[1] & 0b00000011) << 16) | ((frame[2] & 0b11111111) << 8) | (frame[3] & 0b11111111)

            self.srr = frame[1] & 0b00010000
            self.rtr = frame[4] & 0b01000000
            self.ide = frame[1] & 0b00001000

            self.dlc = frame[4] & 0b00001111

            self.data = frame[5:]

        # Else do nothing
        else:
            del self

    def __str__(self):
        """
            Called when object is printed
        """
        ret = ""

        ret += "SRR = {},  RTR = {}, IDE = {}, DLC = {} \n".format(self.srr, self.rtr, self.ide, self.dlc)

        # If frame was a standard message
        if (not self.ide):
            ret += "Id = {} ".format(hex(self.sid))

        # If frame was an extended message
        else:
            ret += "Id = {} ".format(hex(self.eid))

        ret += "Data = "

        for i in range(0, self.dlc):
            ret += "{} ".format(self.data[i])

        return ret

    def __eq__(self, other):
        """
            Used to test if two objects are equal
        """

        test = 0

        test += (self.srr == other.srr)
        test += (self.ide == other.ide)
        test += (self.rtr == other.rtr)

        test += (self.sid == other.sid)
        test += (self.eid == other.eid)
        test += (self.dlc == other.dlc)

        test += (self.data == other.dlc)

        return test

    def __hash__(self):
        """
            Used to hash object when using a container
        """
        return hash(("sid", self.sid, "eid", self.eid, "datasum", sum(self.data)))

mainLoop = True

def sigHandler(signal, frame):
    """
        Handles signals by breaking main loop
    """
    global mainLoop
    mainLoop = False

if __name__ == "__main__":
    """
        Main program
    """

    # Handle end signals
    signal.signal(signal.SIGTERM, sigHandler)
    signal.signal(signal.SIGINT, sigHandler)

    # Prepare terminal
    term = blessed.Terminal()
    with term.cbreak(), term.hidden_cursor():
        # Clear the screen
        print(term.home + term.clear)

        # Terminal pointer
        pointer = 0
        # Displayed data
        displayed = ""
        
        if len(sys.argv) < 2:
            displayed = term.red_reverse("-- Fill in serial port --")
            # Center text on the console
            pointer = term.move_xy(math.floor((term.width/2) - (len(displayed)/2)), math.floor(term.height/2))
            print(term.clear_eol + pointer + displayed, end='', flush=True)

            time.sleep(2)
            exit()

        # Initialize serial port
        ser = serial.Serial()
        #ser.baudrate = 115200
        ser.baudrate = 921600
        ser.port = sys.argv[1]
        ser.timeout = 1

        try:
            ser.open()

        # If unable to open, quit program
        except serial.SerialException:
            displayed = term.red_reverse("-- Serial port error --")
            # Center text on the console
            pointer = term.move_xy(math.floor((term.width/2) - (len(displayed)/2)), math.floor(term.height/2))
            print(term.clear_eol + pointer + displayed, end='', flush=True)

            time.sleep(2)
            exit()

        # Else, let's have fun
        # Associate message ID and console position
        messagePosition = {}

        # Address incrementer
        row = 6
        col = 2

        # Acquired values
        currentSpeed = 0
        currentRpm  = 0
        currentTorque = 0
        fuelConsuption = 0
        tWater = 0
        tOil = 0
        tAir = 0
        steerwheel = 0
        braking = 0
        parking = 0
        clutch = 0
        gearbox = 0
        doors = 0


        # Display welcome data
        pointer = term.move_xy(2, 2)
        displayed = term.green("PSA CAN bus sniffer - \u00A9 BDELIERS - 2021")
        print(term.clear_eol + pointer + displayed, end='', flush=True)

        displayed = term.blue("Listening port {}".format(ser.portstr))
        pointer = term.move_xy(term.width - len(displayed) - 2, 2)
        print(term.clear_eol + pointer + displayed, end='', flush=True)

        # Display guidelines data
        pointer = term.move_xy(2, 4)
        displayed = term.underline("ID    Data")
        print(term.clear_eol + pointer + displayed, end='', flush=True)

        #pointer = term.move_xy(math.floor(term.width / 2) + 2, 4)
        #print(pointer + displayed, end='', flush=True)

        # Loop while not killed
        while (mainLoop):
            # Reset displayed buffer
            displayed = ""

            # Read line
            line = ser.readline()

            # If we received data
            if len(line) > 0:
                # Create object
                frame = MCP2515Frame(line)

                # If we have an error
                if frame.dlc > 8:
                    continue

            # Else we timed out, restart waiting
            else:
                continue

            # Add object to last message by standard ID
            if not (frame.sid in messagePosition):
                # First time, assign a place in terminal
                messagePosition[frame.sid] = (col, row)

                # Prepare next place
                if (col == 2):
                    #col = math.floor(term.width/2) + 2
                    col = 2
                    row += 1
                else:
                    col = 2
                    row += 1

                # Move pointer to frame ID place
                pointer = term.move_xy(messagePosition[frame.sid][0], messagePosition[frame.sid][1])

                # Print data to a static place
                displayed = hex(frame.sid) + " "

            else:
                # Move pointer to frame data place
                pointer = term.move_xy(messagePosition[frame.sid][0] + 6, messagePosition[frame.sid][1])

            for i in range(0, frame.dlc):
                displayed += "{} ".format(hex(frame.data[i]))

            # Display received message after parsing
            print(term.clear_eol + pointer + displayed, end='', flush=True)

            # Compute data from http://romain.raveaux.free.fr/teaching/TP207.pdf
            if frame.sid == 0x38D:
                currentSpeed = (frame.data[0] << 8) | (frame.data[1])
                currentSpeed /= 100

            elif frame.sid == 0x208:
                currentRpm = (frame.data[0] << 8) | (frame.data[1])
                currentRpm /= 8

                currentTorque = (frame.data[2] * 2) - 100

                braking = 1 if (frame.data[4] & 0b00000010) else 0

            elif frame.sid == 0x348:
                gearbox = ((frame.data[0] & 0b11110000) >> 4) if (((frame.data[0] & 0b11110000) >> 4) != 9) else 'R'

                clutch = 1 if (frame.data[4] & 0b00011000) else 0

            # No data on mine
            elif frame.sid == 0x305:
                steerwheel = (frame.data[0] << 8) | (frame.data[1])

            elif frame.sid == 0x488:
                tWater = frame.data[0] - 40

                fuelConsuption = math.floor(frame.data[1] / 80)

                tOil = frame.data[5] - 40

                tAir = frame.data[7] - 40

            elif frame.sid == 0x412:
                #braking = 1 if (frame.data[0] & 0b01000000) else 0

                parking = 1 if (frame.data[0] & 0b00001000) else 0

                doors = (frame.data[6] & 0b11111000) >> 3

            # Display current datas
            pointer = term.move_xy(2, term.height-4)
            # Clean line
            print(term.clear_eol + pointer + ' '*(term.width-2), end='', flush=True)

            displayed = "Torque: {} Nm \u0009|\u0009 Consumption: {} mm3 \u0009|\u0009 ".format(currentTorque, fuelConsuption)
            displayed += "Water: {} C \u0009|\u0009 Oil: {} C \u0009|\u0009 Air: {} C".format(tWater, tOil, tAir)
            print(pointer + displayed, end='', flush=True)

            pointer = term.move_xy(2, term.height-3)
            displayed = "Doors: {0:5b} \u0009|\u0009 ".format(doors)
            displayed += "Steerwheel: {} deg \u0009|\u0009 Gearbox: {} \u0009|\u0009 ".format(steerwheel, gearbox)
            displayed += "Clutch: {} \u0009|\u0009 Braking: {} \u0009|\u0009 Parking: {}".format(clutch, braking, parking)
            print(term.clear_eol + pointer + displayed, end='', flush=True)

            pointer = term.move_xy(2, term.height-1)
            displayed = "Speed: "
            #displayed += str(currentSpeed)
            displayed += math.floor(currentSpeed/4) * "I"
            print(term.clear_eol + pointer + term.green(displayed), end='', flush=True)

            pointer = term.move_xy(math.floor(term.width/2) + 2, term.height-1)
            displayed = "RPM: "
            #displayed += str(currentRpm)
            displayed += math.floor(currentRpm/65) * "I"
            print(term.clear_eol + pointer + term.green(displayed), end='', flush=True)

        # Exit program
        displayed = term.white_reverse("-- Exiting --")
        # Center text on the console
        pointer = term.move_xy(math.floor((term.width/2) - (len(displayed)/2)), math.floor(term.height/2))
        print(term.clear + pointer + displayed, end='', flush=True)

        ser.close()

        exit()
