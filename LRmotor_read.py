import time
import os
import serial
import sys
import RPi.GPIO as GPIO
import re
import time

GPIO.setmode(GPIO.BCM)
STEPPER_PINS = [17,18,27,22]
for pin in STEPPER_PINS:
  GPIO.setup(pin,GPIO.OUT)
  GPIO.output(pin, GPIO.LOW)
  
GPIO.setup(27, GPIO.OUT) 





y_STEPS= 0
motor_steps = 640
buf = 0
contR = 0
contL = 0


count = 0;

while True:
    start=time.time()
    try:
        f = open('LRmotor_mode.txt','r+')
        modelswitch = int(f.readline())
        f.close()
    except:
        pass

    if modelswitch ==1:
        file='LRmotor_lora.txt'
    elif modelswitch ==2:
        file='ASM.txt'
    elif modelswitch ==3:
        file='LRmotor_always_left.txt'
    else:
        print("wrong")


    f = open(file,'r+')
    data = f.readline()
    print(data)
    if data == "":
        pass
    else:
       # ~ datalist = data.split(',') #找尋,並分割資料
        datalist = data
        f.close()



        # ~ y_STEPS = ''.join([y_STEPS for y_STEPS in datalist[1] if y_STEPS.isdigit()]) #找尋數字
        y_STEPS = ''.join([y_STEPS for y_STEPS in datalist if y_STEPS.isdigit()]) #找尋數字        
        y_STEPS = int(y_STEPS)
        y_STEPS= y_STEPS*5
        #print(y_STEPS)


        
        if motor_steps < y_STEPS:              # y_STEPS_CW右轉
                if contL == 1:
                        time.sleep(0.001)
                for i in range(5):
                  GPIO.output(17, 1)   
                  time.sleep(0.00008)    
                  GPIO.output(17, 0)    
                  time.sleep(0.00008)
                  motor_steps += 1;
                contR = 1
                contL = 0
        
        
        if motor_steps > y_STEPS:              # y_STEP_CCW左轉
                if contR == 1:
                        time.sleep(0.001)
                for i in range(5):
                  GPIO.output(27, 1)   
                  time.sleep(0.00008)    
                  GPIO.output(27, 0)    
                  time.sleep(0.00008)
                  motor_steps -= 1;
                contL = 1
                contR = 0
        time.sleep(0.00001)
    end=time.time()
    FPS=round(1/(end-start),2)
    print('FPS:',FPS)

    
            

