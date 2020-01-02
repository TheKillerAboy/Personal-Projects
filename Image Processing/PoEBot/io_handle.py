import pyautogui

class Key:
    def __init__(self, *args):
        if type(args[0]) == Key:
            self.type, self.sym = args[0].type, args[0].sym
        else:
            self.type, self.sym = args

    def __hash__(self):
        return hash(str(self))

    def __str__(self):
        return f'{self.type}-{self.sym}'

    def __eq__(self, other):
        return hash(other) == hash(self)

    def __iter__(self):
        return self.type, self.sym

class Keys:
    def __init__(self, combo = ''):
        self.keys = [Key(t,k) for t,k in map(lambda s: s.split('-'),combo.split('+'))]

    def append(self, *args):
        self.keys.append(Key(*args))

    def remove(self, *args):
        self.keys.remove(Key(*args))

    def __str__(self):
        return '+'.join(map(str,self.keys))

    def __hash__(self):
        return hash(str(self))

    def __eq__(self, other):
        return hash(self) == hash(other)

    def __iter__(self):
        yield from self.keys

    def __reversed__(self):
        yield from reversed(self.keys)

class IOHandle:
    def __init__(self):
        self.hooks = {}

    def press(self, keys):
        if type(keys) == Key:
            keys = Keys(str(keys))
        for key in keys:
            self.hold_down_key(key)
        for key in reversed(keys):
            self.hold_up_key(key)

    def hold_down_key(self, key):
        typ, sym = key
        if typ == 'keyboard':
            pyautogui.keyDown(sym)
        else:
            pyautogui.mouseDown(button=sym)

    def hold_up_key(self, key):
        typ, sym = key
        if typ == 'keyboard':
            pyautogui.keyUp(sym)
        else:
            pyautogui.mouseUp(button=sym)

    def remove_hook(self, flask):
        if flask.typ in self.hooks:
            if flask in self.hooks[flask.typ]:
                self.hooks[flask.typ].remove(flask)

    def add_hook(self, flask, callback):
        if flask.typ not in self.hooks:
            self.hooks[flask.typ] = {}
        self.hooks[flask.typ][flask] = callback