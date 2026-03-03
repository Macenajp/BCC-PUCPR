# https://wokwi.com/projects/new/micropython-esp32
# https://wokwi.com/projects/457428994427060225

from machine import Pin
import time

#Configuraçao do LED no pino GPID 15:
led = Pin(15, Pin.OUT)
while True:
  #Acende o LED:
    led.value(1)
  
  #Espera dois segundos:
    time.sleep(2)

  # Apaga o LED:
    led.value(0)

  #Espera um segundo:
    time.sleep(1)
