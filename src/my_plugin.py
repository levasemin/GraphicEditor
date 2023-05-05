from pyplug import *
import numpy as np
from PIL import Image
from style_transfer.learn import StyleTransfer
import torch 
import gc

run_once = True

class mytool:
    def __init__(self):
        print("__init__() called!")
        torch.cuda.empty_cache()
        gc.collect()
        print(torch.cuda.is_available())
        # self.style_transfer = StyleTransfer(lr=1,
        #                        content_weight=1, 
        #                        style_weight=1e3,
        #                        content_weights="{'relu_4_2':1}", 
        #                        style_weights="{'relu_1_1':1,'relu_2_1':1,'relu_3_1':1,'relu_4_1':1,'relu_5_1':1}",
        #                        avg_pool=False, 
        #                        feature_norm=True, 
        #                            weights='original',
        #                        preserve_color='style', 
        #                        device='auto',
        #                        use_amp=False,
        #                        adam=False, 
        #                        optim_cpu=False, 
        #                        logging=50)
                               
    def apply(self, image, event):
        if event.type == EventType.ButtonClicked:
            print("Process starts")
            picture = image.getPicture(100, 100, 300, 300)
            alpha = picture[:, :, 0]
            picture = picture[:, :, 1:]

            picture = picture[:, :, ::-1]
            picture = picture[::-1]
            print(alpha.shape)
            picture = np.zeros([300, 300, 4], dtype=np.uint8)
            print(picture.shape)
            # picture = numpy.concatenate([alpha.T.reshape(300, 300, 1), picture], axis=2)
            image.setPicture(100, 100, picture)
            print("HUINYAAAAAAAAAAAAAA")
            # print(picture)
            # img = Image.fromarray(picture.astype(numpy.uint8))
            # img.save("hui.png")
            # artwork = self.style_transfer(img, Image.open('Style.jpeg'), 
                        #  area=256, init_random=False, init_img=None, iter=500)
            # artwork.save('artwork.png')

    def getTexture(self):
        print("getTexture() called!")
        return "some_texture.png"
    def buildSetupWidget(self):
        createButton(100, 100, 100, 100, "Start")
        print("build_setup_widget called!")


def init_module():
    setToolbarSize(300, 300)
    addTool(mytool())