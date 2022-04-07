# Acknoledgement: Referenced from https://pyimagesearch.com/2015/05/25/basic-motion-detection-and-tracking-with-python-and-opencv/ 

import cv2
import time
import datetime
import imutils

def motion_detection():
    video_capture = cv2.VideoCapture(0)
    video_capture.set(int(5),1)

    if not (video_capture.isOpened()):
        print('camera not open')

    time.sleep(2)

    first_frame = None

    while video_capture.isOpened():
        frame = video_capture.read()[1]

        text = 'Unoccupied'

        greyscale_frame = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
        
        gaussian_frame = cv2.GaussianBlur(greyscale_frame, (21,21),0)

        blur_frame = cv2.blur(gaussian_frame, (5,5)) 

        greyscale_image = blur_frame 
    
        if first_frame is None:
            first_frame = greyscale_image 
        else:
            pass


        frame = imutils.resize(frame, width=500)
        frame_delta = cv2.absdiff(first_frame, greyscale_image) 
        
        thresh = cv2.threshold(frame_delta, 100, 255, cv2.THRESH_BINARY)[1]
        
        dilate_image = cv2.dilate(thresh, None, iterations=2)
        
        cnt = cv2.findContours(dilate_image.copy(), cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)

        if cnt is None:
            pass
        else:
            for c in cnt[-2]:
                if cv2.contourArea(c) > 800:
                    text = "Occupied"
                    break
                else:
                    pass
                
        print(text)
        if text is "Occupied":
            break



if __name__=='__main__':    
    motion_detection()
