# Exemplo simples do uso do DHT22 para medição de temperatura e umidade.
# https://wokwi.com/projects/457691430029173761

import dht
from machine import Pin
import time

sensor = dht.DHT22(Pin(15))

while True:
    sensor.measure()
    print("Temperatura: " + str(sensor.temperature()));
    print("Umidade: " + str(sensor.humidity()))
    time.sleep(2)
