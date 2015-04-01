from __future__ import division
from xbox_read import event_stream
import sys
import serial
import time


USAGE = """\
Usage: python drive_teleop.py

.

Drives the car using an xbox controller
"""

active_throttle = 0

jerry_radio = '/dev/ttyUSB1'
jerry = serial.Serial(jerry_radio, 57600, timeout=0)

tom_radio = '/dev/ttyUSB0'
tom = serial.Serial(tom_radio, 57600, timeout=0)




time_stamps = open('timestamps.csv','w')
originalTime = time.time()


def main():
    set_pid(jerry)
    set_pid(tom)
    global active_throttle

    
    get_position_both()


    while(1):
        #now collect 2 positional informations...
        inputs = event_stream(4000)
        for event in inputs:
            get_position_both()
            if event.key == "X2":
                spd = round(event.value / 32768 * 600)
                print(spd)
                drive_at(jerry,spd)
        get_position_both()


def current_time_milli():
    return int(round(time.time() * 1000))

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

def get_position_both():
    time_stamps.write(str( round(time.time() - originalTime,3)) + '\n')
    tom.write('l')
    jerry.write('l')


if __name__ == '__main__':
    if len(sys.argv) != 1:
        print USAGE
        sys.exit(1)
    main()
