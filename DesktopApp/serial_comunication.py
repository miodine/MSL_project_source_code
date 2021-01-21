import serial
import math as m
import struct

COM_FLAG = 68

class MSL_UART_handler():
    def __init__(self):
        self._port_name = ''
        print('MS Lab. project - UART communication initialization...')
        self._port_name = input('Port name to which NUCLEO is connected (eg. "COM4" - no spaces!): ')
        self.ser = serial.Serial(self._port_name,baudrate = 115200, timeout = 0.01, parity=serial.PARITY_NONE)  # open serial port
        print('Port ' + self.ser.name + ' has been opened...')
        print("Make sure that baudrate == 115200, parity == none and comunicatiom flag == 68")

        self.transmitting_ = False

    def read_data(self, RPM_actual, status_code):
        if self.ser.is_open == True and self.transmitting_ == False:
            s = self.ser.read(1)
            if s != b'':
                s = self.ser.read(4)
                RPM_actual = int.from_bytes(s,'little')
                print(RPM_actual)
                s = self.ser.read(1)
                status_code = int.from_bytes(s,'little')
                print(status_code)
                print("-------------")
        return RPM_actual, status_code

    def send_data(self, Kp, Ki, Kd, RPM_set):
        #self.ser.write(struct.pack("B", COM_FLAG))
        self.transmitting_ = True
        print("transmitting...")
        self.ser.write(struct.pack("I", Kp))
        self.ser.write(struct.pack("I", Ki))
        self.ser.write(struct.pack("I", Kd))
        self.ser.write(struct.pack("I", RPM_set))
        self.transmitting_ = False