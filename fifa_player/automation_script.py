import serial #Serial imported for Serial communication
import time #Required to use delay functions
import pyautogui
from text_to_voice import Text

ser = serial.Serial('/dev/ttyUSB0',9600) #Create Serial port object called arduinoSerialData
time.sleep(2) #wait for 2 seconds for the communication to get established
print (ser.readline())
while True:
    incoming = str (ser.readline()) #read the serial data and print it as line
    print (incoming)
    
    if 'pass' in incoming:
        pyautogui.typewrite('d')
        time.sleep(1)

    if 'moveUp' in incoming:
        pyautogui.press('up')  

    if 'moveDown' in incoming:
        pyautogui.press('down')

    if 'moveLeft' in incoming:
        pyautogui.press('left')
        
    if 'moveRight' in incoming:
        pyautogui.press('right')
        
    if 'moveLeftUp' in incoming:
        pyautogui.hotkey('left', 'up')
        
    if 'moveRightUp' in incoming:
        pyautogui.hotkey('right', 'up')
        
    if 'moveLeftDown' in incoming:
        pyautogui.hotkey('left', 'down')
        
    if 'moveRightDown' in incoming:
        pyautogui.hotkey('right', 'down')

    if ' userabsent' in incoming:
    	pass

    incoming = ""
