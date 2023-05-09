import numpy
from PIL import Image
from style_transfer.learn import StyleTransfer
import torch 

try:
    Image.open("ko.jpg")
except:
    print("loh")