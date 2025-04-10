from kivymd.app import MDApp
from kivy.core.window import Window
from kivy.lang import Builder
from kivy.uix.screenmanager import ScreenManager, NoTransition
from kivymd.uix.behaviors import FakeRectangularElevationBehavior
from kivymd.uix.floatlayout import MDFloatLayout
from kivymd.uix.boxlayout import MDBoxLayout
from kivy.clock import Clock
import objects

Window.size = (460, 600)
id_next_base = 0

manager = objects.DeviceManager()


class BotLine(MDFloatLayout):
    # нижня лінія меню
    def change_screen(self, sc):
        screen_manager.current = sc


class TargetLog(MDBoxLayout):
    # Лог мішені
    pass


class BaseCard(FakeRectangularElevationBehavior, MDFloatLayout):
    # Прототип картки з бази
    def change_team(self, color):
        if self.circle.md_bg_color == color:
            self.circle.md_bg_color = (200/255, 200/255, 200/255, 1)
        else:
            self.circle.md_bg_color = color
            # web_controll.find()


class TargetCard(FakeRectangularElevationBehavior, MDFloatLayout):
    # Прототип картки з бази
    pass


class PlayerCard(FakeRectangularElevationBehavior, MDFloatLayout):
    # прототип картки гравця
    Live = True

    def kill_res_player(self):
        if self.Live:
            self.bg.md_bg_color = (200/255, 200/255, 200/255, 1)
            self.Live = False
        else:
            self.bg.md_bg_color = (255 / 255, 0 / 255, 200 / 255, 1)
            self.Live = True


class LTApp(MDApp):
    global screen_manager
    screen_manager = ScreenManager(transition=NoTransition())

    def __init__(self, **kwargs):
        super().__init__(**kwargs)
        self.target_cards = {}

    def build(self):
        self.theme_cls.theme_style = "Light"
        self.theme_cls.primary_palette = "Teal"  # "Purple", "Red"
        screen_manager.add_widget(Builder.load_file("BaseScreen.kv"))
        screen_manager.add_widget(Builder.load_file("PlayersScreen.kv"))
        screen_manager.add_widget(Builder.load_file("TargetsScreen.kv"))

        # Запускаємо оновлення логів кожні 5 секунд
        # Clock.schedule_interval(self.update_targets_logs, 5)
        # Запускаємо оновлення інформації про пристрої кожні 30 секунд
        # Clock.schedule_interval(self.update_targets, 30)

        return screen_manager

    def on_start(self):
        self.update_targets()
        for i in range(1):
            self.add_base()
            # self.add_target(1, "TAR00001")

    def add_base(self):
        card = BaseCard()
        global id_next_base
        id = id_next_base
        card.name_base.text = f"Base {id}"
        id_next_base += 1
        card.circle.md_bg_color = (200/255, 200/255, 200/255, 1)
        screen_manager.get_screen("Screen1").obj_bar.add_widget(card)

    def update_targets(self):
        manager.find_devices()
        all_targets_serials = manager.get_all_targets()
        for i in all_targets_serials:
            if i in self.target_cards:
                pass
            else:
                device = manager.get_device(i)
                self.add_target(str(device.ID), serial=device.serial_nom)
        self.update_targets_logs()

    def update_targets_logs(self):
        all_targets_serials = manager.get_all_targets()
        for i in all_targets_serials:
            manager.add_new_logs_to_target(i)
            card = self.target_cards[i]
            logs_info = manager.get_device(i).get_logs_short_info()
            card.hits_count.text = f'd{logs_info[2]} in {logs_info[0]}'
            card.ids.Red_Hits.text = str(logs_info[1][0])
            card.ids.Blue_Hits.text = str(logs_info[1][1])
            card.ids.Yellow_Hits.text = str(logs_info[1][2])
            card.ids.Green_Hits.text = str(logs_info[1][3])

    def add_target(self, id='00', serial="ERR00000"):
        card = TargetCard()
        card.id_text.text = f"ID {id}"
        card.serial_nomber.text = f"sn: {serial}"
        manager.add_new_logs_to_target(serial)
        logs_info = manager.get_device(serial).get_logs_short_info()
        card.hits_count.text = f'd{logs_info[2]} in {logs_info[0]}'
        card.ids.Red_Hits.text = str(logs_info[1][0])
        card.ids.Blue_Hits.text = str(logs_info[1][1])
        card.ids.Yellow_Hits.text = str(logs_info[1][2])
        card.ids.Green_Hits.text = str(logs_info[1][3])
        screen_manager.get_screen("Screen3").targets_bar.add_widget(card)
        self.target_cards[serial] = card


    def change_screen(self, sc):
        screen_manager.current = sc


LTApp().run()




