#! /usr/bin/python3

# haha, "daemon" :D
# aquí iré metiendo la lectura de datos y guardado en algún sitio

# alias arduinousb='sudo chmod a+rw /dev/ttyACM0'

import serial
import influxdb
import time
import os.path

while True:
	try:
		influx = influxdb.InfluxDBClient("localhost", 8086, "root", "root", "hometv")

		ser = serial.Serial("/dev/ttyACM0" if os.path.exists("/dev/ttyACM0") else "/dev/ttyACM1", 9600)  # 9600 bauds
		while True:
			line = ser.readline()
			parts = line.decode('ascii').strip().split(" ")
			print(time.ctime(), line, parts)

			if parts[0] != "D":
				continue

			influx.write_points([
				{
					"measurement": "humedad",
					"tags": {
						"location": "home"
					},
					"fields": {
						"v": float(parts[1][2:])
					}
				},
				{
					"measurement": "temperatura",
					"tags": {
						"location": "home"
					},
					"fields": {
						"real": float(parts[2][2:]),
						"sensacion": float(parts[3][2:])
					}
				},
				{
					"measurement": "luminosidad",
					"tags": {
						"location": "home"
					},
					"fields": {
						"avg": float(parts[4][3:]),
						"min": float(parts[5][3:]),
						"max": float(parts[6][3:])
					}
				}
			])

	except Exception as e:
		print(e)
		time.sleep(60)
