import numpy as np
from PIL import Image


width = 200
height = 200
box_width = 80
box_height = 80
gate_size = 50

wallsize = 4


if __name__ == "__main__":
    im_arr_blank = 255 * np.ones([width + 2 * wallsize, height + 2 * wallsize])
    im_arr = 255 * np.ones([width + 2 * wallsize, height + 2 * wallsize])
    im_arr[0, 0] = 0

    # create outer walls
    im_arr[:wallsize, :] = 0
    im_arr[-wallsize:, :] = 0
    im_arr[:, :wallsize] = 0
    im_arr[:, -wallsize:] = 0

    # Create box
    box_uwall_line1 = wallsize + height // 2 - box_height // 2 - wallsize
    box_uwall_line2 = wallsize + box_uwall_line1
    box_uwall_col1 = wallsize + width // 2 - box_width // 2 - wallsize
    box_uwall_col2 = wallsize + width // 2 + box_width // 2
    im_arr[box_uwall_line1:box_uwall_line2, box_uwall_col1:box_uwall_col2] = 0

    box_lwall_line1 = wallsize + height // 2 - box_height // 2 - wallsize
    box_lwall_line2 = wallsize + height // 2 + box_height // 2 + wallsize
    box_lwall_col1 = wallsize + width // 2 - box_width //2 - wallsize
    box_lwall_col2 = box_lwall_col1 + wallsize
    im_arr[box_lwall_line1:box_lwall_line2, box_lwall_col1:box_lwall_col2] = 0

    box_bwall_line1 = wallsize + height // 2 + box_height // 2
    box_bwall_line2 = box_bwall_line1 + wallsize
    box_bwall_col1 = wallsize + width // 2 - box_width // 2 - wallsize
    box_bwall_col2 = wallsize + width // 2 + box_width // 2
    im_arr[box_bwall_line1:box_bwall_line2, box_bwall_col1:box_bwall_col2] = 0

    box_rwall_line1 = wallsize + height // 2 - box_height // 2 - wallsize
    box_rwall_line2 = wallsize + height // 2 + box_height // 2 + wallsize
    box_rwall_col1 = wallsize + width // 2 + box_width //2
    box_rwall_col2 = box_rwall_col1 + wallsize
    im_arr[box_rwall_line1:box_rwall_line2, box_rwall_col1:box_rwall_col2] = 0

    # Gate
    gate_line1 = box_uwall_line1
    gate_line2 = box_uwall_line2
    gate_col1 = wallsize + width // 2 - gate_size // 2
    gate_col2 = wallsize + width // 2 + gate_size // 2
    im_arr[gate_line1:gate_line2, gate_col1:gate_col2] = 255

    print("gate coord:")
    print((gate_col1, gate_line1))
    print("gate dim:")
    print((gate_size, wallsize))

    im = Image.fromarray(im_arr)
    imblank = Image.fromarray(im_arr_blank)
    if im.mode != 'RGB':
        im = im.convert('RGB')

    if imblank.mode != 'RGB':
        imblank = imblank.convert('RGB')
    im.save("env_environment.bmp")
    imblank.save("env_footprint.bmp")



