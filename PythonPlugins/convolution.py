import numpy as np


def apply_convolution(array, kernel):
    shape = array.shape
    kernel_size = kernel.shape[0]
    kernel = kernel.reshape(kernel_size, kernel_size, 1)
    left_part  = np.repeat([array[0, 0, :]], kernel_size // 2, axis = 0)
    right_part = np.repeat([array[0, shape[1] - 1, :]], kernel_size // 2, axis = 0)
    row = np.concatenate([left_part, array[0, :, :], right_part], axis = 0)
    row = np.repeat([row], kernel_size // 2 + 1, axis = 0)
    saved_rows = row
    

    for i in range(kernel_size // 2):
        left_part  = np.repeat([array[i, 0, :]], kernel_size // 2, axis = 0)
        right_part = np.repeat([array[i, shape[1] - 1, :]], kernel_size // 2, axis = 0)
        row = np.concatenate([left_part, array[i, :, :], right_part], axis = 0)
        saved_rows = np.concatenate([saved_rows, [row]], axis = 0)


    for y in range(0, shape[0]):
        current_row = saved_rows[0]
        saved_rows = np.delete(saved_rows, 0, axis = 0)
        y_ = y + 3 if y + 4 < shape[0] else shape[0] - 2
        
        left_part  = np.repeat([array[y_, 0, :]], kernel_size // 2, axis = 0)
        right_part = np.repeat([array[y_, shape[1] - 1, :]], kernel_size // 2, axis = 0)
        row = np.concatenate([left_part, array[y_, :, :], right_part], axis = 0)
        
        saved_rows = np.concatenate([saved_rows, [row]], axis = 0)
            
        for x in range(3, shape[1] + 3):
            pic_part = saved_rows[:, x - kernel_size // 2 : x + kernel_size // 2 + 1, :]
            pic_part = pic_part * kernel
            pic_part = pic_part.sum(axis = 0).sum(axis = 0)
            pic_part[0] = pic_part[0] if pic_part[0] > 0 else 0
            pic_part[1] = pic_part[1] if pic_part[1] > 0 else 0
            pic_part[2] = pic_part[2] if pic_part[2] > 0 else 0
            pic_part[3] = pic_part[3] if pic_part[3] > 0 else 0
            array[y, x - 3, :] = pic_part

    array[:, :, 3] = 255
    return array