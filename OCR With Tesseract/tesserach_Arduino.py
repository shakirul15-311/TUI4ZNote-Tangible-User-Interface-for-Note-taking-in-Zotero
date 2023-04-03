#!/usr/bin/env python
# coding: utf-8

# In[ ]:


import cv2
from PIL import Image
from pytesseract import pytesseract
import datetime

camera = cv2.VideoCapture(0)

while True:
    _,image=camera.read()
    cv2.imshow('Text detection',image)
    if cv2.waitKey(1) & 0xFF==ord('s'):
        now = datetime.datetime.now()
        #filename = 'Tangible Interface_' + now.strftime('%Y-%m-%d_%H-%M-%S') + '.txt'
        filename = 'Haptic Feedback_' + now.strftime('%Y-%m-%d_%H-%M-%S') + '.txt'
        cv2.imwrite('test1.jpg',image)
        break
camera.release()
cv2.destroyAllWindows()

def tesseract():
    path_to_tesseract=r"C:\Program Files\Tesseract-OCR\tesseract.exe"
    image_path='test1.jpg'
    pytesseract.tesseract_cmd=path_to_tesseract
    text = pytesseract.image_to_string(Image.open(image_path))
    with open(filename, 'w') as f:
        f.write(text)
    print(text)
    
tesseract()

