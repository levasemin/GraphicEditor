from pyplug import *

class mytool:
    def __init__(self):
        print("__init__() called!")

    def apply(self, image, event):
        print("apply() called!")
        print("fgColor", APPCONTEXT.fgColor)

    def getTexture(self):
        print("getTexture() called!")
        return "some_texture.png"
    def buildSetupWidget(self):
        button = createButton(1, 2, 3, 4, "Button 1")
        print("button", button, "has been created")
        APPCONTEXT.fgColor = 179

class mytool_2:
    def __init__(self):
        print("__init__() for second tool called!")

    def apply(self, image, event):
        print("second tool apply called")
        if (event.type == EventType.NoEvent):
            print("event.type = NoEvent")
        else:
            print("event.type = other")
        APPCONTEXT.fgColor = APPCONTEXT.fgColor + 1

    def getTexture(self):
        print("getTexture() called!")
        return "some_texture_2.png"
    def buildSetupWidget(self):
        button = createButton(1, 2, 3, 4, "Button 2")
        print("button", button, "has been created")
        APPCONTEXT.fgColor = 179

class mytool_3:
    def __init__(self):
        print("__init__() for third tool called!")

    def apply(self, image, event):
        print("third tool apply called")
        # arr = image.getPicture(0, 0, 3, 6)
        # arr[2][5] = 179
        # image.setPicture(0, 0, arr)

    def getTexture(self):
        return "some_texture_2.png"
    def buildSetupWidget(self):
        print("buildSetupWidget called!")

def init_module():
    setToolbarSize(300, 300)
    addTool(mytool())
    addTool(mytool_2())
    addTool(mytool_3())