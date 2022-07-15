# Raspberry-Pi
客户端：

roslaunch teleop_twist_joy teleop.launch

rosrun learning_communication client1

服务端：

sudo chmod 777 /dev/ttyAMA0

sudo chmod 777 /dev/mem

sudo chmod 777 /dev/gpiomem

roscore

rosrun leaning_communication server
