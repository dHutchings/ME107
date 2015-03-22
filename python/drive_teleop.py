from __future__ import division
from xbox_read import event_stream
import sys
import serial
import time


USAGE = """\
Usage: python drive_teleop.py

Assumes 57600 Baud Rate on /dev/ttyUSB0.

Drives the car using an xbox controller
"""

active_throttle = 0

def main():
    global active_throttle

    radio = '/dev/ttyUSB0'
    tom = serial.Serial(radio, 57600, timeout=0)

    set_pid(tom)

    while(1):
        inputs = event_stream(4000)
        for event in inputs:
            if event.key == "X2":
                spd = round(event.value / 32768 * 600)
                print(spd)
                drive_at(tom,spd)
        time.sleep(.1)

def drive_at(port,speed):
    port.write('s')
    time.sleep(0.01)
    port.write(str(speed))
    port.write('x')

def set_pid(port):
    port.write('p')
    time.sleep(0.1)
    port.write('1.0')
    time.sleep(1.5)
    port.write('0.25')
    time.sleep(1.5)
    port.write('0.0')

if __name__ == '__main__':
    if len(sys.argv) != 1:
        print USAGE
        sys.exit(1)
    main()
