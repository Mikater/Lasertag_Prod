from kivymd.app import MDApp
from kivy.core.window import Window
from kivy.lang import Builder
from kivymd.uix.screen import MDScreen
from kivymd.uix.behaviors import FakeRectangularElevationBehavior
from kivymd.uix.floatlayout import MDFloatLayout

Window.size = (460, 900)

Screen_STR = """
MDScreen:
    name: "Screen1"
    MDBoxLayout:
        orientation: 'vertical'
        MDScrollView:
            do_scroll_x: False
            MDStackLayout:
                adaptive_height: False
                BaseCard:
                    size_hint_y: "200dp"
                    
                
"""


class BaseCard(FakeRectangularElevationBehavior, MDFloatLayout):
    pass


class LTApp(MDApp):
    def build(self):
        self.theme_cls.theme_style = "Light"
        self.theme_cls.primary_palette = "Teal"  # "Purple", "Red"
        screen = Builder.load_file("BaseScreen.kv")
        return screen


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
