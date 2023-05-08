from tkinter import Frame, Button, Toplevel, Label, messagebox

class TkPerformer:

    def __init__(self, root, title, text, command):
        confirm = messagebox.askyesnocancel(
            title,
            text,
            default=messagebox.YES,
            parent=root
        )

        if confirm:
            command()

        root.focus_set()
