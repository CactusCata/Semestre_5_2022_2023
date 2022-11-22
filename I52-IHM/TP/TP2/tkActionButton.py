from tkinter import Frame, Button, Toplevel, Label

class TkActionButton:

    def __init__(self, root, text, command):
        self.windowsAction = Toplevel(root, 200, 50)
        self.command = command

        # Add text
        frameText = Frame(self.windowsAction)
        labelText = Label(frameText, text)
        labelText.pack()
        frameText.pack(side="top", expend=True)

        # Add buttons
        frameButton = Frame(windowsAction)
        buttonConfirmButton = Button(frameButton, label="Confirmer", func=lambda: self.confirm())
        buttonCancelButton = Button(frameButton, label="Annuler", func=lambda: self.cancel())

        root.wait_visibility(windowsAction) # attente active
        windowsAction.grab_set() # fenetre bloquante

    def confirm(self):
        self.command()
        self.destroyTopLevel()

    def cancel(self):
        self.destroyTopLevel()

    def destroyTopLevel(self):
        self.windowsAction.destroy()
        self.windowsAction.update()
