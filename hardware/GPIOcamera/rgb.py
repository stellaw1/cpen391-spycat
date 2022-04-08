import numpy as np
import cv2
width=640
height=480
channels=3 
color_bg=(0,0,0) 
imgdim = (height + 1, width + 1, channels) 
blank_image = np.full(imgdim, color_bg, np.uint8)
before_image = np.full(imgdim, color_bg, np.uint8)

file= open("output.txt")
lines = file.readlines()

for i in range(len(lines)):
    r, g, b, x = lines[i].split(",")
    
    blank_image[i // width, i % width] = (b,g,r)
    
# file= open("1.txt")
# lines = file.readlines()

# for i in range(height*width):
#     r, g, b, x = lines[i].split(",")
#     before_image[i // width, i % width] = (b,g,r)

# cv2.imshow("before", before_image)
cv2.imshow("after", blank_image)
cv2.waitKey(0)


