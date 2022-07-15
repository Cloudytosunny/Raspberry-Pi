    #import pigpio
    #pi = pigpio.pi()          # 初始化
def pwm_function(b):
    pi.set_servo_pulsewidth(26, b)
    return b
    
def Init_function(a):
    print("Init python")
    if not pi.connected:      # 检查是否连接成功 
        exit()
    user_gpio = 26
    pulsewidth = a         # 可以设置500至1500，这是电平为1的时间，单位是微秒
    pi.set_servo_pulsewidth(user_gpio, pulsewidth)
    return a
