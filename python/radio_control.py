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

filename = '/dev/ttyUSB0'

dev = serial.Serial(filename, 115200, timeout=0)

@atexit.register
def stop_motor():
    print('Ending test.')
    dev.write('s') #set speed to...
    time.sleep(0.1)
    dev.write('0.0') #speed is zero.
    time.sleep(1)

def current_time_milli():
    return int(round(time.time() * 1000))

def set_pid():
    dev.write('p')
    time.sleep(0.1)
    dev.write('1.0')
    time.sleep(1.5)
    dev.write('0.25')
    time.sleep(1.5)
    dev.write('0.0')

#note: doesn't set back to zero, watch out!
def drive_for(tim,speed):
    dev.write('s')
    time.sleep(0.1)
    dev.write(speed)
    time.sleep(1)
    time.sleep(tim)

def drive_print(tim,speed):
    dev.write('s')
    time.sleep(0.1)
    dev.write(speed)
    time.sleep(1) #now should be running
    timeToEnd = current_time_milli() + (1000*tim)
    while current_time_milli() < timeToEnd:
        dev.write('l') #get location
        time.sleep(.05) #at 20 Hz.

print('Starting Test')
set_pid()
drive_print(5,'300.0')
drive_print(3,'200.0')
#automatically stops motor and end of test

