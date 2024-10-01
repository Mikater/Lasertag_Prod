from kivymd.app import MDApp
from kivy.core.window import Window
from kivy.lang import Builder
from kivymd.uix.screen import MDScreen
from kivy.uix.screenmanager import ScreenManager
from kivymd.uix.behaviors import FakeRectangularElevationBehavior
from kivymd.uix.floatlayout import MDFloatLayout

Window.size = (460, 900)
id_next_base = 0


class BaseCard(FakeRectangularElevationBehavior, MDFloatLayout):
    def change_team(self, color):
        if self.circle.md_bg_color == color:
            self.circle.md_bg_color = (200/255, 200/255, 200/255, 1)
        else:
            self.circle.md_bg_color = color


class LTApp(MDApp):

    def build(self):
        global screen_manager
        screen_manager = ScreenManager()
        self.theme_cls.theme_style = "Light"
        self.theme_cls.primary_palette = "Teal"  # "Purple", "Red"
        screen_manager.add_widget(Builder.load_file("BaseScreen.kv"))
        return screen_manager

    def on_start(self):
        for i in range(4):
            self.add1base()

    def add1base(self):
        card = BaseCard()
        global id_next_base
        id = id_next_base
        card.name_base.text = f"Base {id}"
        id_next_base += 1
        card.circle.md_bg_color = (200/255, 200/255, 200/255, 1)
        screen_manager.get_screen("Screen1").obj_bar.add_widget(card)





LTApp().run()


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
