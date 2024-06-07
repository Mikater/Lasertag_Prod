import customtkinter

customtkinter.set_appearance_mode("Dark")   # Dark Lite System
customtkinter.set_default_color_theme("blue")

root = customtkinter.CTk()

root.title("MyApp")
root.geometry('1000x700')


def hello():
    my1label.configure(text="Hi Retard...")
    my2label.configure(text=my1button.cget("text"))
    my1button.configure(state="disabled", fg_color="blue")


my1button = customtkinter.CTkButton(root,
                                    text="Hi Bot",
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
my1label = customtkinter.CTkLabel(root, text="Hello world!")
my1label.pack(pady=20)
my2label = customtkinter.CTkLabel(root, text="")
my2label.pack(pady=20)

root.mainloop()
