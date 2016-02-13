#! /usr/bin/python3

# haha, "daemon" :D
# aquí iré metiendo la lectura de datos y guardado en algún sitio

import serial
ser = serial.Serial("/dev/ttyACM0", 9600)  # 9600 bauds
while True:
	print(ser.readline())
