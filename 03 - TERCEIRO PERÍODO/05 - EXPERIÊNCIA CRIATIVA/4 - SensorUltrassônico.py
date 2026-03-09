# https://wokwi.com/projects/458055684714798081

# Corrigir:
from machine import Pin, Timer
import time

trig = Pin(0, Pin.IN)
echo = Pin(2, Pin.OUT)

def medir_distancia():

    trig.value(0)
    time.sleep_us(2)
    trig.value(1)
    time.sleep_us(10)
    trig.value(0)

    while echo.value() == 0:
        pulse_start = time.ticks_us()    
    while echo.value() == 1:
        pulse_end = time.ticks_us()

    pulse_duration = time.ticks_us_diff(pulse_end, pulse_start)

    distancia = (pulse_duration / 2) * 0.0343
    return distancia

while True:
    distancia = medir_distancia()
    print("Distância: %.1f cm" % distancia)
    time.sleep(1)
