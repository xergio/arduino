#! /usr/bin/python3

# haha, "daemon" :D
# aquí iré metiendo la lectura de datos y guardado en algún sitio

import serial
import influxdb 
import time

while True:
	try:
		influx = influxdb.InfluxDBClient("localhost", 8086, "root", "root", "hometv")

		ser = serial.Serial("/dev/ttyACM0", 9600)  # 9600 bauds
		while True:
			line = ser.readline()
			parts = line.decode('ascii').strip().split(" ")

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
				}
			])

	except Exception as e:
		print(e)
		time.sleep(60)
