from pyplug import *
import numpy as np
from PIL import Image
from style_transfer.learn import StyleTransfer
import torch 
import gc

run_once = True

class mytool:
    def __init__(self):
        torch.cuda.empty_cache()
        gc.collect()
        print("Cuda available: ", torch.cuda.is_available())
        self.style_transfer = StyleTransfer(lr=1,
                               content_weight=1, 
                               style_weight=1e3,
                               content_weights="{'relu_4_2':1}", 
                               style_weights="{'relu_1_1':1,'relu_2_1':1,'relu_3_1':1,'relu_4_1':1,'relu_5_1':1}",
                               avg_pool=False, 
                               feature_norm=True, 
                                   weights='original',
                               preserve_color='style', 
                               device='auto',
                               use_amp=False,
                               adam=False, 
                               optim_cpu=False, 
                               logging=50)
        self.style_image_path = ""

    def apply(self, image, event):
        if event.type == EventType.ButtonClicked:
            print("Process starts")
            picture = image.getPicture(100, 100, 500, 500)
            alpha = picture[:, :, 3]
            picture = picture[:, :, :3]

            img = Image.fromarray(picture.astype(np.uint8))
            artwork = self.style_transfer(img, Image.open(self.style_image_path), 
                            area=256, init_random=False, init_img=None, iter=300)
            artwork = self.style_transfer(img, Image.open(self.style_image_path), 
                            area=512, init_random=False, init_img=artwork, iter=200)
            artwork.save('artwork.png')
            artwork = artwork.resize((500, 500), Image.Resampling.NEAREST)
            picture = np.array(artwork)
            picture = np.concatenate([picture, alpha.T.reshape(500, 500, 1)], axis=2)
            image.setPicture(100, 100, picture)
        
        if event.type == EventType.TextEvent:
            self.style_image_path = event.text
            print(text)

    def getTexture(self):
        return "some_texture.png"

    def buildSetupWidget(self):
        self.start_button = createButton(100, 100, 50, 50, "Start")
        self.style_editor = createEditor(50, 50, 100, 30)
        self.state_label  = createLabel(200, 200, 100, 50, "")
        print("build_setup_widget called!")


def init_module():
    setToolbarSize(300, 300)
    addTool(mytool())