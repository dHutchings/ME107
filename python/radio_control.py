#!/usr/bin/env python

# Licensed to Pioneers in Engineering under one
# or more contributor license agreements.  See the NOTICE file
# distributed with this work for additional information
# regarding copyright ownership.  Pioneers in Engineering licenses
# this file to you under the Apache License, Version 2.0 (the
# "License"); you may not use this file except in compliance
#  with the License.  You may obtain a copy of the License at
#
#    http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing,
# software distributed under the License is distributed on an
# "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
# KIND, either express or implied.  See the License for the
# specific language governing permissions and limitations
# under the License

from __future__ import print_function

import serial
import time
import atexit

tom_radio = '/dev/ttyUSB0'
tom = serial.Serial(tom_radio, 57600, timeout=0)
jerry_radio = '/dev/ttyUSB1'
jerry = serial.Serial(jerry_radio,57600,timeout=0)

time_stamps = open('timestamps.csv','w')



@atexit.register
def stop_motor():
    print('Ending test.')
    tom.write('s') #set speed to...
    jerry.write('s')
    time.sleep(0.1)
    tom.write('0.0') #speed is zero.
    jerry.write('0.0')
    time.sleep(1)

def current_time_milli():
    return int(round(time.time() * 1000))

def set_pid(port):
    port.write('p')
    time.sleep(0.1)
    port.write('1.0')
    time.sleep(1.5)
    port.write('0.25')
    time.sleep(1.5)
    port.write('0.0')

#note: doesn't set back to zero, watch out!
def drive_for(tim,speed):
    tom.write('s')
    time.sleep(0.1)
    tom.write(speed)
    time.sleep(1)
    time.sleep(tim)

def drive_print(port,tim,speed):
    port.write('s')
    time.sleep(0.1)
    port.write(speed)
    time.sleep(1) #now should be running
    timeToEnd = current_time_milli() + (1000*tim)
    while current_time_milli() < timeToEnd:
        time_stamps.write(str(time.time()))
        port.write('l') #get location
        time.sleep(.05) #at 20 Hz.

def drive_print_both(tim,speed):
    tom.write('s')
    jerry.write('s')
    time.sleep(0.1)
    tom.write(speed)
    jerry.write(speed)
    time.sleep(1) #now should be running
    timeToEnd = current_time_milli() + (1000*tim)
    while current_time_milli() < timeToEnd:
        get_position_both()
        time.sleep(.05) #at 20 Hz.

def get_position_both():
	time_stamps.write(str( round(time.time() - originalTime,3)) + '\n')
	tom.write('l')
	jerry.write('l')


print('Starting Test')
set_pid(tom)
set_pid(jerry)
originalTime = time.time()
get_position_both()
drive_print_both(5,'300.0')
#drive_print(jerry,3,'200.0')
#automatically stops motor and end of test

