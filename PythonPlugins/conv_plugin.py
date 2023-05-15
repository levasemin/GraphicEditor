from pyplug import *
import time 
import numpy as np
from PIL import Image
from style_transfer.learn import StyleTransfer
import Filter
import torch 
import gc

run_once = True


class mytool:
    def __init__(self):
        self.kernel = [[0, 0, 0, 0, 0, 0, 0],
                       [0, 0, 0, 0, 0, 0, 0],
                       [0, 0, 0, 0, 0, 0, 0],
                       [0, 0, 0, 1, 0, 0, 0],
                       [0, 0, 0, 0, 0, 0, 0],
                       [0, 0, 0, 0, 0, 0, 0],
                       [0, 0, 0, 0, 0, 0, 0]]

    def apply(self, image, event):
        position = [int(event.x), int(event.y)]            

        if event.type == EventType.MouseReleased:
            self.clicked = False
            self.previous_points = []
        
        if event.type == EventType.ButtonClicked:
            for y in range(7):
                for x in range(7):
                    try:
                        self.kernel[y][x] = int(getTextEditor(self.editor_array[x][y]))
                    except:
                        setTextEditor(self.editor_array[y][x], "0")

            pic = image.getPicture(0, 0, image.getW(), image.getH())
            pic = Filter.apply_convolution(pic, self.kernel)
            image.setPicture(0, 0, pic)
            
    def getTexture(self):
        return "../PluginIcons/Style.png"

    def buildSetupWidget(self):
        self.editor_array = [[createEditor(y * 30 + 20, x * 30 + 20, 30, 30) for x in range(7)] for y in range(7)]
        for y in range(7):
            for x in range(7):
                setTextEditor(self.editor_array[y][x], "0")

        setTextEditor(self.editor_array[3][3], "1")
        
        self.button = createButton(100, 300, 50, 50, "Do")

def init_module():
    setToolbarSize(300, 300)
    addTool(mytool())