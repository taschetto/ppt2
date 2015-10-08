#!/usr/bin/env python2.7

import bitstring
import time
import serial
import RPi.GPIO as GPIO

def count_press(channel):
  presses[channel] = presses[channel] + 1

presses = { 23: 0, 24: 0, 25: 0 }

try:
  GPIO.setmode(GPIO.BCM) 
  for i in range(23,26): 
    GPIO.setup(i, GPIO.IN, pull_up_down=GPIO.PUD_UP) 
    GPIO.add_event_detect(i, GPIO.RISING, callback=count_press)

  ser = serial.Serial(port = '/dev/ttyAMA0', baudrate = 9600)

  stream = bitstring.BitStream()
  while 1:
    stream.clear()
    input = raw_input("$ ")

    if input == 'exit':
      ser.close()
      exit()
    elif input == 'led 0 on':
      stream.append('0x00')
      stream.append('0x00')
      stream.append('0x01')
    elif input == 'led 0 off':
      stream.append('0x00')
      stream.append('0x00')
      stream.append('0x00') 
    elif input == 'led 1 on':
      stream.append('0x00')
      stream.append('0x01')
      stream.append('0x01')
    elif input == 'led 1 off':
      stream.append('0x00')
      stream.append('0x01')
      stream.append('0x00') 
    elif input == 'led 2 on':
      stream.append('0x00')
      stream.append('0x02') 
      stream.append('0x01')
    elif input == 'led 2 off':
      stream.append('0x00')
      stream.append('0x02') 
      stream.append('0x00') 
    elif input == 'led 3 on': 
      stream.append('0x00')
      stream.append('0x03') 
      stream.append('0x01')
    elif input == 'led 3 off': 
      stream.append('0x00')
      stream.append('0x03') 
      stream.append('0x00') 
    elif input == 'botao 1':
      stream.append('0x01')
      stream.append('0x00')
      stream.append("int:8=%s" % presses[23])
    elif input == 'botao 2':
      stream.append('0x01')
      stream.append('0x01')
      stream.append("int:8=%s" % presses[24])
    elif input == 'botao 3':
      stream.append('0x01')
      stream.append('0x02')
      stream.append("int:8=%s" % presses[25])
    elif input == 'show':
      print(presses)
      continue
    else:
      print("Unsupported command.\n")
      continue

    stream.append('0x13')
    print("TX: %s\n" % stream)
    ser.write(stream.bytes)

except KeyboardInterrupt:
  GPIO.cleanup()

GPIO.cleanup() 
