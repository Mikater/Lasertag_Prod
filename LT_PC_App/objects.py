import web_controll


class Target:
    def __init__(self, id, serial_nom, ip):
        self.ID = id
        self.serial_nom = serial_nom
        self.IP = ip
        self.logs = []

    def add_log(self, log):
        self.logs.append(log)

    def get_logs(self):
        return self.logs

    def get_logs_range(self):
        a = 0
        for i in self.logs:
            a += 1
        return a

    def get_logs_short_info(self):
        teams_hits = [0, 0, 0, 0]
        count = 0
        damage_gived = 0
        for log in self.logs:
            teams_hits[log[1]] += 1
            count += 1
            damage_gived += log[2]
        info = [count, teams_hits, damage_gived]
        return info


class DeviceManager:
    def __init__(self):
        self.targets = {}

    def find_devices(self):
        active_devices = web_controll.scan_network()
        # active_devices.remove('192.168.1.1')  # Видаляємо IP-адресу шлюзу (якщо потрібно)
        for i in active_devices:
            self.add_device(i.get('ID'), i.get('serial_nomer'), i.get('ip'))

    def add_device(self, device_id, device_serial_nom, device_ip):
        if device_serial_nom not in self.targets:
            self.targets[device_serial_nom] = Target(device_id, device_serial_nom, device_ip)
            print("Додано нову мішень.")

    def get_device(self, device_serial_nom):
        return self.targets.get(device_serial_nom)

    def get_new_logs_from_target(self, device_serial_nom):
        device = self.get_device(device_serial_nom)
        ip = device.IP
        data = web_controll.get_target_logs(ip)
        for log in data:
            self.add_log_to_device(device_serial_nom,
                                   [log['ID'], log['Team'], log['Damage'], log['Time']])

    def add_log_to_device(self, device_serial_nom, log):
        device = self.get_device(device_serial_nom)
        if device:
            device.add_log(log)

    def get_logs_for_device(self, device_serial_nom):
        self.get_new_logs_from_target(device_serial_nom)
        device = self.get_device(device_serial_nom)
        if device:
            return device.get_logs()

    def get_all_targets(self):
        return list(self.targets.keys())  # Повертає список усіх


class Base:
    # Паттерн прототип бази команди
    def __init__(self):
        self.name = "База команди"
        self.ID = 0
        self.team = 1
        self.mode = "Restarter"
        self.isBroke = False
        self.HP = 100
        self.time_to_restart = 0

    def broke(self):
        self.isBroke = True
        self.HP = 0
        self.time_to_restart = 100