from tkinter import Tk, Label, Entry, Button, messagebox
from screenSpaceTk import ScreenSpaceTk

class EuclidianConfigTk():

    def __init__(self, x_min, y_min, x_max, y_max) -> None:

        self.root = Tk()
        self.root.geometry(f"{300}x{500}")

        self.screenSpaces = []

        label_min_x = Label(self.root, text="x min:")
        label_min_x.pack()
        self.entry_min_x = Entry(self.root)
        self.entry_min_x.insert(0, str(x_min))
        self.entry_min_x.pack()

        label_min_y = Label(self.root, text="y min:")
        label_min_y.pack()
        self.entry_min_y = Entry(self.root)
        self.entry_min_y.insert(0, str(y_min))
        self.entry_min_y.pack()

        label_max_x = Label(self.root, text="max x:")
        label_max_x.pack()
        self.entry_max_x = Entry(self.root)
        self.entry_max_x.insert(0, str(x_max))
        self.entry_max_x.pack()

        label_max_y = Label(self.root, text="max y:")
        label_max_y.pack()
        self.entry_max_y = Entry(self.root)
        self.entry_max_y.insert(0, str(y_max))
        self.entry_max_y.pack()

        label_function = Label(self.root, text="Fonction")
        label_function.pack()
        self.entry_function = Entry(self.root)
        self.entry_function.pack()

        button_apply_changes = Button(self.root, text="Appliquer les changements", command=self.applyChanges)
        button_apply_changes.pack()

        self.root.bind("a", lambda event: self.addScreenSpaceTk())

    def addScreenSpaceTk(self):
        """
        Ajoute un espace ecran dans une autre fenetre
        """
        screenSpaceTk = ScreenSpaceTk(self)
        screenSpaceTk.set_window(50, 50, 150, 100)
        self.screenSpaces.append(screenSpaceTk)
        screenSpaceTk.start()

    def removeAScreenSpaceTk(self, screenSpaceTk):
        """
        Supprime un espace ecran
        """
        self.screenSpaces.remove(screenSpaceTk)

    def start(self):
        self.root.mainloop()

    def getRoot(self):
        return self.root

    def getCoefList(self) -> list:
        coefs = []

        function_text = self.entry_function.get()
        coefs_str = function_text.split("+")
        for coef_str in coefs_str:
            coefs.append(int(coef_str))
        return coefs

    def applyChanges(self):
        if (self.entry_function.get() == ""):
            messagebox.showerror(title="Erreur equation", message="Veuillez entrer une équation")
            return


        min_x = int(self.entry_min_x.get())
        min_y = int(self.entry_min_y.get())
        max_x = int(self.entry_max_x.get())
        max_y = int(self.entry_max_y.get())
        function_coefs = self.getCoefList()

        for screenSpaceTk in self.screenSpaces:
            screenSpaceTk.draw_function(min_x, min_y, max_x, max_y, function_coefs)