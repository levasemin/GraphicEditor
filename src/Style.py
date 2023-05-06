from style_transfer.learn import StyleTransfer
from PIL import Image
import numpy as np


style_transfer = StyleTransfer(lr=1,
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

picture = Image.open("british.png")
picture = np.array(picture)[:300, :300, :]

img = Image.fromarray(picture.astype(np.uint8))
artwork = style_transfer(img, Image.open('Style.jpeg'), 
                area=256, init_random=False, init_img=None, iter=100)
artwork.save('artwork.png')
artwork = artwork.resize((300, 300), Image.Resampling.NEAREST)
picture = np.array(artwork)
print(picture.shape)