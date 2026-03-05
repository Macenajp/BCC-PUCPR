# https://wokwi.com/projects/457691666153842689

# Bibliotecas:
import dht
from machine import Pin
import time

#Configuraçao do LED no pino GPID 15:
ledAzul = Pin(15, Pin.OUT)
ledVermelho = Pin(2, Pin.OUT)
ledAmarelo = Pin(0, Pin.OUT)
ledVerde = Pin(17, Pin.OUT)

# Configuração do sensor DHT:
sensor = dht.DHT22(Pin(15))

while True:
    sensor.measure()
    print("Temperatura: " + str(sensor.temperature()));
    print("Umidade: " + str(sensor.humidity()))
    time.sleep(2)

while True:
    led.value(1)
