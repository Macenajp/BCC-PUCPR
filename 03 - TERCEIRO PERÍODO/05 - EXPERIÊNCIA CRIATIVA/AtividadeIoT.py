# main.py - Aplicacao MQTT no microcontrolador
import network                          # Controle de conexao Wi-Fi
from umqtt.simple import MQTTClient     # Biblioteca de comunicacao MQTT -> protocolo de mensagens para IoT
import machine                          # Acesso e controle de hardware (pinos, sensores, etc)       
import time                             # Configuração do tempo para criar delays e similares
import json                             # Permite a conversão de dados para JSON (envio / leitura de mensagens)
import random                           # Gera dados aleatórios para a simulação de sensores (temperatura, umidade, etc)

# ==== CONFIGURACOES - ALTERE AQUI ====
# Aqui é onde configuramos e definimos as informações e credenciais para a conexão: 
SSID = "iPhone de Pierre"               # Nome da rede wi-fi que será usada para a conexão da ESP32
SENHA = "19012006"                      
BROKER = "broker.hivemq.com"            # É o que vai distribuir e transmitir as mensagens entre o microcontrolador e o celular (ou outro dispositivo); Ele recebe a mensagem de um 
                                        # dispositivo e encaminha para o dispositivo que estiver inscrito no mesmo tópico.

PORTA = 1883                            # Porta padrão do MQTT
CLIENT_ID = "micro-Pierre"              # É o identificador único do dispositivo no broker. O broker usa isso para distinguir quem é quem, se dois dispostivos tentarem se conectar 
                                        #com o mesmo client_id, um deles será desconectado.

# Canais separados justamente para não criar um loop:
TOPICO_PUBLICAR = "pucpr/micro/dados"   # Tópico onde será enviado os dados da ESP32 (dados do sensor, estado do LED, etc)
TOPICO_ASSINAR = "pucpr/pc/comandos"    # Onde a ESP32 vai escutar os comandos de "pucpr/pc/comandos", 

# LED integrado ESP32 = pino 2
led = machine.Pin(2, machine.Pin.OUT)   # Cria um objeto que representa o pino físico da ESP32 onde o LED está conectado, configurado como saída (OUT)
led_estado = False                      # Guarda o estado atual do LED (nesse caso, começa desligado)


# Aqui, a função irá tentar se conectar à rede até 20 vezes. Se der certo, retornará "True" e mostrará o IP da ESP32. Se não, retornará "False" e uma mensagem de erro:
def conectar_wifi():
    wlan = network.WLAN(network.STA_IF)
    wlan.active(True)
    if not wlan.isconnected():
        print("Conectando ao Wi-Fi...")
        wlan.connect(SSID, SENHA)
        tentativas = 0
        while not wlan.isconnected() and tentativas < 20:
            time.sleep(1)
            tentativas += 1
            print(f"Tentativa {tentativas}/20...")
    if wlan.isconnected():
        print(f"Wi-Fi conectado! IP: {wlan.ifconfig()[0]}")
        return True
    else:
        print("ERRO: Nao foi possivel conectar ao Wi-Fi")
        return False



def callback_mensagem(topico, mensagem):
    global led_estado
    topico = topico.decode("utf-8")
    payload = mensagem.decode("utf-8")
    print(f"[MICRO] Recebido em '{topico}': {payload}")
    try:
        dados = json.loads(payload)
        comando = dados.get("comando", "")
        if comando == "led_on":
            led.value(1)
            led_estado = True
            print("[MICRO] LED ligado!")
            publicar_estado()
        elif comando == "led_off":
            led.value(0)
            led_estado = False
            print("[MICRO] LED desligado!")
            publicar_estado()
        elif comando == "status":
            publicar_dados_sensor()
        else:
            print(f"[MICRO] Comando desconhecido: {comando}")
    except Exception as e:
        print(f"[MICRO] Erro ao processar: {e}")



def publicar_estado():
    estado = "ligado" if led_estado else "desligado"
    msg = json.dumps({"led": estado})
    client.publish(TOPICO_PUBLICAR, msg)
    print(f"[MICRO] Publicado: {msg}")



def publicar_dados_sensor():
    dados = {
        "temperatura": round(20 + random.random() * 15, 1),
        "umidade": round(40 + random.random() * 40, 1),
        "led": "ligado" if led_estado else "desligado"
    }
    msg = json.dumps(dados)
    client.publish(TOPICO_PUBLICAR, msg)
    print(f"[MICRO] Dados publicados: {msg}")



# ---- Inicio ----
if not conectar_wifi():
    print("Abortando: sem Wi-Fi.")
    raise SystemExit

print("[MICRO] Conectando ao broker MQTT...")
client = MQTTClient(CLIENT_ID, BROKER, port=PORTA)
client.set_callback(callback_mensagem)
client.connect()
print(f"[MICRO] Conectado a {BROKER}")
client.subscribe(TOPICO_ASSINAR)
print(f"[MICRO] Inscrito em: {TOPICO_ASSINAR}")
print("[MICRO] Aguardando comandos...\n")

contador = 0
try:
    while True:
        client.check_msg()
        contador += 1
        if contador >= 30:
            publicar_dados_sensor()
            contador = 0
        time.sleep(1)
except KeyboardInterrupt:
    print("\n[MICRO] Interrompido.")
finally:
    client.disconnect()
    print("[MICRO] Desconectado.")