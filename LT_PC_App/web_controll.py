import requests

ESP32_IP = "192.168.1.14"


def call():
    url = f"http://{ESP32_IP}/callBipStart"
    response = requests.get(url)
    if response.status_code == 200:
        print("Юху! Перемога буде!!!")
    else:
        print("Зрадонька якась(")

def find():
    url = f"http://{ESP32_IP}/"
    response = requests.get(url)
    if response.status_code == 200:
        print("Юху! Перемога буде!!!")
    else:
        print("Зрадонька якась(")
