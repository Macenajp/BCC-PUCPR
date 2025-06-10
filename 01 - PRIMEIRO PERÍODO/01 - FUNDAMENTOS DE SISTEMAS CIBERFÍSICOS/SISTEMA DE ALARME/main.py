import network                                         # Biblioteca para configurar a rede
from machine import Pin, PWM, time_pulse_us            # Biblioteca para controlar pinos digitais, GPIO sinais PWM e medir pulsos
from time import sleep                                 # Biblioteca para fazer o esp32 pausar
from umqtt.simple import MQTTClient                    # Biblioteca de protocolo mqtt que permite conectar receber e publicar mensagens

wlan = network.WLAN(network.STA_IF)                    # Cria um interface de rede e define o modo station que vai conectar a um roteador
wlan.active(True)                                      # Liga o radio wifi do esp32
wlan.connect('Wokwi-GUEST', '')                        # Conecta o esp32 a rede simulada com o nome Wokwi-GUEST e sem senha 

while not wlan.isconnected():                          # Enquanto o esp32 nao conseguir se conectar no wifi sera exibido a mensagem
    print('conectando...')                             # Exibe enquanto o esp nao esta conectado a internet
print('conectado!')                                    # Exibido apos a conexao com a internet

broker = 'mqtt-dashboard.com'                          # Informa o broker para onde a mensagem foi enviada
client_id = 'esp32teste!'                              # Nome do cliente para identificaçao no broker
topico = 'enviar/projeto/esp32'                        # Endereço do broker para onde as mensagens sao publicadas
topico2 = 'receber/projeto/esp32'                      # Endereço do broker para onde as mensagens vao ser publicadas para o esp

led = Pin(23, Pin.OUT)                                 # Informa que o led esta no pino 23 e que esta configurado como saida de dados

buzzer = PWM(Pin(22))                                  # Informa que o buzzer esta no pino 22 e que e controlado por sinal PWM
buzzer.freq(1000)                                      # Define a frequencia do buzzer     
buzzer.duty(0)                                         # Define o ciclo de trabalho do PWM como 0        

sensor = Pin(34, Pin.IN)                               # Informa que o sensor esta no pino 34 e que esta configurado como entrada de dados

distancia_simulada = 500                               # Valor para simular o quão próximo está o intruso - para a simulação (em cm)           

trig = Pin(12, Pin.OUT)                                # Pino TRIG do HC-SR04 (serve para enviar o pulso) - Sensor ultrassônico
echo = Pin(14, Pin.IN)                                 # Pino ECHO do HC-SR04 (serve para receber o echo) - Sensor ultrassônico

def callback(topic, msg):                              # Funcao para receber as mensagens do usuario pelo mqtt
    if str(msg.decode()) == 'ligar':                   # Se no topico for publicado 'ligar' o led o buzzer serao ligados 
        led.value(1)                                   # Liga o led
        buzzer.duty(600)                               # Liga o buzzer
        client.publish(topico, 'ligado')               # Irá publicar que o led e o buzzer foram ligados
    elif str(msg.decode()) == 'desligar':              # Se no topico for publicado 'desligar' o led e o buzzer serao desligados
        led.value(0)                                   # Desliga o led
        buzzer.duty(0)                                 # Desliga o buzzer
        client.publish(topico, 'desligado')            # Irá publicar que led e o buzzer foram desligados

client = MQTTClient(client_id, broker)         # Cria um objeto cliente mqtt com o id e endereço do broker
client.set_callback(callback)                  # Chama a funcao callback sempre que uma mensagem for publicada
client.connect(True)                           # Conecta o cliente ao broker
client.subscribe(topico2)                      # Se inscreve no topico2 para receber as mensagens enviadas

while True: #Incia o loop

    client.check_msg()                                                 # Verifica as mensagens e chama o callback()
    
    if sensor.value() == 1:                                            # Se o sensor for ativado o movimento sera detectado
        print('movimento detectado!')                                  # Exibe movimento detectado quando o sensor e ativado

        dist = distancia_simulada                                      # Usa valor escolhido - para simulação de distância entre o intruso e o sensor
        print("distância: {:.2f} cm".format(dist))                     # informa a distancia simulada

        if dist <= 50:                                                 # Se distância for igual ou menor que 500 cm (ou outro valor escolhido)
            print("aproximação detectada! o alarme será ativado!")     # Imprime na tela se algo foi detectado pelo sensor, baseando-se no valor escolhido
            
            while sensor.value() == 1:
                led.value(1)             # Liga o led
                buzzer.duty(600)         # Liga o buzzer
                sleep(0.3)               # Faz uma pausa de 0.3s
                led.value(0)             # Desliga o led
                buzzer.duty(0)           # Desliga o buzzer
                sleep(0.3)               # Faz uma pausa de 0.3s
    
        client.publish(topico, 'INVASAO DETECTADA!')                  # Se o sensor for ativado o esp32 publica uma mensagem no topico
        print('mensagem enviada')                                     # Informa se a mensagem foi enviada 
