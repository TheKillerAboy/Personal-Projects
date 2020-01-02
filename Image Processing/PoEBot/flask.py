class Flask:
    def __init__(self, typ, key, duration_ms, iohandle):
        self.typ, self.key, self.duration_ms = typ, key, duration_ms
        self.iohandle.add_hook(self, self.click_callback())
        self.iohandle = iohandle

    def click_callback(self):
        def click():
            self.iohandle.press(self.key)
        return click

    def setType(self, typ):
        self.iohandle.remove_hook(self)
        self.typ = typ
        self.iohandle.add_hook(self, self.click_callback())

    def __str__(self):
        return f'{self.typ}{str(self.key)}{self.duration_ms}'

    def __hash__(self):
        return hash(str(self))

    def __eq__(self, other):
        return hash(self) == hash(other)