import serial
import math as m
import struct

COM_FLAG = 68

class MSL_UART_handler():
    def __init__(self):
        self._port_name = ''
        print('MS Lab. project - UART communication initialization...')
        self._port_name = input('Port name to which NUCLEO is connected (eg. "COM4" - no spaces!): ')
        self.ser = serial.Serial(self._port_name,baudrate = 115200, timeout = 1, parity=serial.PARITY_NONE)  # open serial port
        print('Port ' + self.ser.name + ' has been opened...')
        print("Make sure that baudrate == 115200, parity == none and comunicatiom flag == 68")


    def read_data(self, RPM_actual, status_code):
        if self.ser.is_open == True:
            s = self.ser.read(1)
            if int.from_bytes(s,'big') == COM_FLAG:
                s = self.ser.read(4)
                RPM_actual = int.from_bytes(s)
                s = self.ser.read(4)
                status_code = int.from_bytes(s)

    def send_data(self, Kp, Ki, Kd, RPM_set):
        self.ser.write(struct.pack("B", COM_FLAG))
        self.ser.write(struct.pack("I", Kp))
        self.ser.write(struct.pack("I", Ki))
        self.ser.write(struct.pack("I", Kd))
        self.ser.write(struct.pack("I", RPM_set))