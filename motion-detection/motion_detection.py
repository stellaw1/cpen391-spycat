import cv2
import time
import datetime
import imutils


def motion_detection():
    video_capture = cv2.VideoCapture(0)

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
                    (x, y, w, h) = cv2.boundingRect(c)

                    cv2.rectangle(frame, (x,y), (x+w, y+h), (0, 255, 0), 2)

                    text = 'Occupied'
                else:
                    pass


        ''' now draw text and timestamp on security feed '''
        font = cv2.FONT_HERSHEY_SIMPLEX 

        cv2.putText(frame, '{+} Room Status: %s' % (text), 
            (10,20), cv2.FONT_HERSHEY_SIMPLEX , 0.5, (0, 0, 255), 2)


        cv2.putText(frame, datetime.datetime.now().strftime('%A %d %B %Y %I:%M:%S%p'), 
            (10, frame.shape[0] - 10), cv2.FONT_HERSHEY_SIMPLEX , 0.35, (0, 0, 255),1)

        cv2.imshow('Security Feed', frame)
        cv2.imshow('Threshold(foreground mask)', dilate_image)
        cv2.imshow('Frame_delta', frame_delta)

        key = cv2.waitKey(1) & 0xFF
        if key == ord('q'):
            cv2.destroyAllWindows()
            break
                


if __name__=='__main__':    
    motion_detection()
