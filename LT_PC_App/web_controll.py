import requests
from concurrent.futures import ThreadPoolExecutor  # Для паралельної перевірки
import json

ips_arr = []


def get_target_logs(ip, port=80, endpoint="/info"):
    url = f"http://{ip}:{port}{endpoint}"  # Формуємо URL
    try:
        response = requests.get(url, timeout=5)  # Відправляємо GET-запит
        if response.status_code == 200:  # Перевіряємо статус-код
            try:
                data = response.json()  # Парсимо JSON
                if data["count"] > 0:
                    print(f"Дані отримано з {url}: {data}")
                    return data
            except json.JSONDecodeError as e:
                print(f"Помилка парсингу JSON з {url}: {e}")
                print(f"Відповідь сервера: {response.text}")  # Виводимо відповідь для аналізу
            except ValueError as e:
                print(f"Помилка значення JSON з {url}: {e}")
        else:
            print(f"Помилка: сервер {url} повернув статус {response.status_code}")
    except requests.exceptions.RequestException as e:
        print(f"Помилка при запиті до {url}: {e}")
    return None  # Повертаємо None у разі помилки


def get_static_info(ip, port=80, endpoint="/"):
    url = f"http://{ip}:{port}{endpoint}"  # Формуємо URL
    try:
        response = requests.get(url, timeout=5)  # Відправляємо GET-запит
        if response.status_code == 200:  # Перевіряємо статус-код
            try:
                data = response.json()  # Парсимо JSON
                print(f"Дані отримано з {url}: {data}")
                return data
            except json.JSONDecodeError as e:
                print(f"Помилка парсингу JSON з {url}: {e}")
                print(f"Відповідь сервера: {response.text}")  # Виводимо відповідь для аналізу
            except ValueError as e:
                print(f"Помилка значення JSON з {url}: {e}")
        else:
            print(f"Помилка: сервер {url} повернув статус {response.status_code}")
    except requests.exceptions.RequestException as e:
        print(f"Помилка при запиті до {url}: {e}")
    return None  # Повертаємо None у разі помилки


# Функція для перевірки доступності IP
def check_ip(ip, port=80, timeout=2):
    url = f"http://{ip}:{port}"  # Формуємо URL
    try:
        response = requests.get(url, timeout=timeout)  # Відправляємо GET-запит
        if response.status_code == 200:  # Перевіряємо статус-код
            try:
                data = response.json()  # Парсимо JSON
                data["ip"] = ip
                print(f"Дані отримано з {url}: {data}")
                return data
            except json.JSONDecodeError as e:
                print(f"Помилка парсингу JSON з {url}: {e}")
                # print(f"Відповідь сервера: {response.text}")  # Виводимо відповідь для аналізу
            except ValueError as e:
                print(f"Помилка значення JSON з {url}: {e}")
    except requests.exceptions.RequestException as e:
        # Якщо виникла помилка (наприклад, тайм-аут або відсутність підключення)
        pass
    return None


# Функція для сканування діапазону IP
def scan_network(base_ip="192.168.1", start=1, end=55, port=80):
    find_devices = []
    with ThreadPoolExecutor(max_workers=50) as executor:  # Використовуємо потоки для паралельної перевірки
        futures = [
            executor.submit(check_ip, f"{base_ip}.{i}", port)
            for i in range(start, end + 1)
        ]
        for future in futures:
            result = future.result()
            if result:
                find_devices.append(result)
    return find_devices


