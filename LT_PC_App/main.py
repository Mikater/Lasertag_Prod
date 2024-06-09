import customtkinter as ctk
import config

ctk.set_appearance_mode("Dark")   # Dark Lite System
ctk.set_default_color_theme("blue")

root = ctk.CTk()

root.title("MyApp")
root.geometry(config.WINDOW_SIZE)


def hello():
    my1label.configure(text=my1entry.get())
    my2label.configure(text=my1button.cget("text"))
    my1button.configure(state="disabled", fg_color="blue")


my1button = ctk.CTkButton(root, text="Hi Bot",
                          command=hello,
                          height=100,
                          width=200,
                          font=("Helvetica", 30),     # FontName, font size
                          text_color="black",
                          fg_color="cyan",            # Bg color
                          hover_color="blue",          # Mouse on Butt color
                          corner_radius=50,
                          border_width=10, border_color="white",
                          text_color_disabled="gray")
my1button.pack(pady=80)
my1label = ctk.CTkLabel(root, text="Hello world!", font=config.FONT1)
my1label.pack(pady=20)
my2label = ctk.CTkLabel(root, text="")
my2label.pack(pady=20)

my1entry = ctk.CTkEntry(root, placeholder_text='Пиши сюда!',
                        font=config.FONT1,
                        height=60, width=300,
                        corner_radius=20,
                        text_color="white",
                        placeholder_text_color="gray")
my1entry.pack(pady=10)

root.mainloop()
