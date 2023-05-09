from pyplug import *
import numpy as np
from PIL import Image
from style_transfer.learn import StyleTransfer
import torch 
import gc

run_once = True

class Interpolator:
    def Interpolate(self, t, point_0, point_1, point_2, point_3):
        point = [0.0, 0.0]
        coeff_0 = -t * pow(1.0 - t, 2.0);
        coeff_1 = (2.0 - 5.0*pow(t, 2.0) + 3.0*pow(t, 3.0));
        coeff_2 = t * (1.0 + 4.0*t - 3.0*pow(t, 2.0));
        coeff_3 = pow(t, 2.0) * (1.0 - t);

        point[0] = int(0.5 * (coeff_0 * point_0[0] + coeff_1 * point_1[0] + coeff_2 * point_2[0] - coeff_3 * point_3[0]))
        point[1] = int(0.5 * (coeff_0 * point_0[1] + coeff_1 * point_1[1] + coeff_2 * point_2[1] - coeff_3 * point_3[1]))

        return point

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
        self.clicked   = False

        self.interpolator = Interpolator()

        self.previous_points = []
        self.fields = []

        self.hidden_array = []

    def fill_ray(self, hidden_layer, position):

        left_pos  = [0, position[1]];
        right_pos = [hidden_layer.shape[1] - 1, position[1]]

        for x in range(int(position[0]), -1, -1):
            im_color = hidden_layer[position[1]][x]
            image_color = im_color;

            if image_color[3] == 0:
                hidden_layer[position[1]][x] = [100, 100, 100, 100]
            else:
                left_pos[0] = x + 1
                break

        for x in range(int(position[0]) + 1, int(hidden_layer.shape[1]), 1):
        
            im_color = hidden_layer[int(position[1])][x];
            image_color = im_color

            if image_color[3] == 0:
                hidden_layer[position[1]][x] = [100, 100, 100, 100]

            else:
                right_pos[0] = x - 1;
                break
        
        return [left_pos, right_pos]


    def fill_part(self, hidden_layer, position):
        zatr_pixels = []
        zatr_pixels.append(position);

        left_up_corner  = list(hidden_layer.shape)
        right_down_corner = [0, 0]

        while len(zatr_pixels) > 0:   
            position = list(zatr_pixels[-1])
            zatr_pixels.pop(len(zatr_pixels) - 1)
                        
            result = self.fill_ray(hidden_layer, position)
            left_position = result[0];
            right_position = result[1];

            left_up_corner[0]    = left_position[0]  if left_position[0]  < left_up_corner[0]    else left_up_corner[0]
            left_up_corner[1]    = left_position[1]  if left_position[1]  < left_up_corner[1]    else left_up_corner[1]
            right_down_corner[0] = right_position[0] if right_position[0] > right_down_corner[0] else right_down_corner[0]
            right_down_corner[1] = right_position[1] if right_position[1] > right_down_corner[1] else right_down_corner[1]

            x = int(left_position[0])
            while x <= int(right_position[0]):
                im_color = hidden_layer[int(position[1]) + 1][x];
                pixel_color = im_color;

                if pixel_color[3] == 0:
                    while pixel_color[3] == 0 and x < int(hidden_layer.shape[1]):
                        pixel_color = hidden_layer[int(position[1]) + 1][x]
                        x += 1
                    
                    if int(position[1]) + 2 < hidden_layer.shape[0]:
                        zatr_pixels.append([x - 2, position[1] + 1])
                x += 1
            
            x = int(left_position[0])
            while x <= int(right_position[0]):
                im_color = hidden_layer[int(position[1]) - 1][x]
                pixel_color = im_color;

                if pixel_color[3] == 0:     
                    while pixel_color[3] == 0 and x < hidden_layer.shape[1]:
                        pixel_color = hidden_layer[int(position[1]) - 1][x];
                        x += 1
                    
                    if position[1] > 1:
                        zatr_pixels.append([x - 2, position[1] - 1]);
                x += 1
        return [left_up_corner, right_down_corner]

        
    def apply(self, image, event):
        position = [int(event.x), int(event.y)]
        if event.type == EventType.MousePressed and event.button == MouseButton.Right:
            hidden_layer = image.getHiddenLayer()
            self.hidden_array = image.getHiddenLayer().getPicture(0, 0, hidden_layer.getW(), hidden_layer.getH())

            self.fields.append(self.fill_part(self.hidden_array, position))
            hidden_layer.setPicture(0, 0, self.hidden_array)

        if event.type == EventType.MousePressed and event.button == MouseButton.Left:
            self.previous_points = [position for i in range(4)]
            self.clicked = True

        if event.type == EventType.MouseReleased:
            self.clicked = False
            self.previous_points = []

        if event.type == EventType.MouseMoved and self.clicked :
            hidden_layer = image.getHiddenLayer()
            color = Color(0)
            color.r = 0
            color.g = 0
            color.b = 0
            color.a = 100

            self.previous_points = self.previous_points[1:]
            self.previous_points.append(position)

            for t in range(0, 11):
                t = float(t) / 10.0
                new_point = self.interpolator.Interpolate(t, self.previous_points[0], self.previous_points[1], self.previous_points[2], self.previous_points[3]);
                hidden_layer.setPixel(new_point[0], new_point[1], color)

        if event.type == EventType.ButtonClicked:
            try:
                style_img = Image.open(self.style_image_path)
            except:
                setTextLabel(self.state_label, "Invalid path")
                return 
                
            if event.id == self.start_button:
                setTextLabel(self.state_label, "Processing...")
                hidden_layer = image.getHiddenLayer()
                hidden_layer.setPicture(0, 0, np.zeros((hidden_layer.getH(), hidden_layer.getW(), 4)))
                for left_up_corner, right_down_corner in self.fields:
                    shape = [right_down_corner[0] - left_up_corner[0], right_down_corner[1] - left_up_corner[1]]
                    picture = image.getPicture(left_up_corner[0], left_up_corner[1], shape[0], shape[1])
                    alpha   = picture[:, :, 3]
                    picture = picture[:, :, :3]

                    img = Image.fromarray(picture.astype(np.uint8))
                    artwork = self.style_transfer(img, style_img, 
                                    area=256, init_random=False, init_img=None, iter=200)
                    if shape[0] > 256 or shape[1] > 256:
                        artwork = self.style_transfer(img, style_img, 
                                        area=512, init_random=False, init_img=artwork, iter=200)

                    artwork = artwork.resize((shape[0], shape[1]), Image.Resampling.NEAREST)
                    picture = np.array(artwork)
                    picture = np.concatenate([picture, alpha.T.reshape(shape[1], shape[0], 1)], axis=2)
                    
                    picture[:, :, 3] = picture[:, :, 3] * (self.hidden_array[left_up_corner[1]:right_down_corner[1], left_up_corner[0]:right_down_corner[0], 3] / 100) 
                    image.setPicture(left_up_corner[0], left_up_corner[1], picture)



        if event.type == EventType.TextEvent:
            self.style_image_path = event.text

    def getTexture(self):
        return "some_texture.png"

    def buildSetupWidget(self):
        self.start_button  = createButton(100, 100, 70, 25, "Start")
        self.select_button = createButton(100, 200, 70, 25, "Select") 
        self.style_editor  = createEditor(50, 50, 100, 30)
        self.state_label   = createLabel(200, 200, 100, 50, "")
        print("build_setup_widget called!")


def init_module():
    setToolbarSize(300, 300)
    addTool(mytool())