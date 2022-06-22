#!/usr/bin/env python3

import pigpio
import time
pi = pigpio.pi()          # 初始化
if not pi.connected:      # 检查是否连接成功 
   exit()
user_gpio = 26
pulsewidth = 0         # 可以设置500至1500，这是电平为1的时间，单位是微秒
'''
为伺服电机产生PWM信号，设置频宽为1500 us，该信号频率默认为50Hz
''' 
pi.set_servo_pulsewidth(user_gpio, pulsewidth)
time.sleep(10)            # 延迟10秒
pi.wave_tx_stop() 
pi.wave_clear()
pi.stop()
