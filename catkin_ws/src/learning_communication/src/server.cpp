/**
 * AddTwoInts Server
 */
 
#include "ros/ros.h"
#include "485_send.h"
#include <string.h>
#include <Python.h>
#include <iostream>
#include "learning_communication/AddTwoInts.h"

static RS485 motor1;
//static PWMEngine pwm1;

    int res;
    int b=3;
    PyObject *pModule,*pFuncInit,*pFunc;
    PyObject *pArgs, *pValue;
    PyObject *pName = NULL;
    char *st;
    char *str;
    
    float last1;
    float last2;
    int flag=0;
    std::string stt;
    
    int leftpwm =500;
    int rightpwm = 500;
    
    int speedclass = 1;


int pwm_function_from_python(int a, int leftright) {

    //int res;
    //PyObject *pModule,*pFunc;
    //PyObject *pArgs, *pValue;
    //PyObject *pName = NULL;
    
    
    
    sprintf(str, "%d", a);
    if(leftright == 1)
    {stt = "pi.set_servo_pulsewidth(26,";}
    else
    {stt = "pi.set_servo_pulsewidth(16,";} 
    stt = stt + str + ")";
    strcpy(str,stt.c_str());
    
    if(b ==3){
    b=4;
    
    PyRun_SimpleString("import sys");
    PyRun_SimpleString("import os");

    
    PyRun_SimpleString("sys.path.append('/home/ubuntu/wsh/catkin_ws/src/learning_communication')");//若python文件在c++工程下
    PyRun_SimpleString("sys.path.append('./')");
    //PyRun_SimpleString("print(sys.path)");
    PyErr_Print();
    /* import */
    PyRun_SimpleString("import sys");
    PyRun_SimpleString("import pigpio");
    PyRun_SimpleString("import time");
    PyRun_SimpleString("pi = pigpio.pi() ");
    //PyRun_SimpleString("pi.set_servo_pulsewidth(26, 1400)");
    PyRun_SimpleString(str);

    //pName = PyUnicode_FromString("PWM");
    ////pModule = PyImport_ImportModule(pName);
    //pModule = PyImport_Import(pName);
    //if (pModule == NULL) {
        //PyErr_Print();
        //printf("Can not open python file!\n");
        ////return -1;
    //}

    /* great_module.great_function */
    //pFunc = PyObject_GetAttrString(pModule, "pwm_function");
    //PyErr_Print();
    //pFuncInit = PyObject_GetAttrString(pModule, "Init_function");
    //PyErr_Print();
    ////PyRun_SimpleString("pi = pigpio.pi() ");
    /* build args */
    //pArgs = PyTuple_New(1);
    ////PyTuple_SET_ITEM(pArgs,0, PyLong_FromLong(a));
    
    /* call */
    ////pValue = PyObject_CallObject(pFuncInit, pArgs);
    //PyErr_Print();
    //res = PyLong_AsLong(pValue);
    }
    if(b != 3)
    {PyRun_SimpleString(str);} 

    return a;
}

// service回调函数，输入参数req，输出参数res
bool add(learning_communication::AddTwoInts::Request  &req,
         learning_communication::AddTwoInts::Response &res)
{
  // 将输入参数中的请求数据相加，结果放到应答变量中
  res.sum = req.a + req.b;
  ROS_INFO("request: x=%ld, y=%ld, c=%ld", (long int)req.a, (long int)req.b, (long int)req.c[1]);
  ROS_INFO("sending back response: [%ld]", (long int)res.sum);
  
  if(req.c[3] == 1){speedclass=1;}
  if(req.c[2] == 1){speedclass=2;}
  if(req.c[1] == 1){speedclass=3;}
  if(req.c[0] == 1){speedclass=4;}
  if(req.c[6] == 1){motor1.Send(0,3);}
  else {
  flag = 0;
if(req.d[1] != last1){
  last1 = req.d[1];flag=1;
  if(req.d[1] > 0.5){motor1.Send(speedclass,1);
  }
  else if(req.d[1] <-0.5){motor1.Send(-1*speedclass,1);
  }
        else {motor1.Send(0,1);
        ROS_INFO("req.d[1]: [%f]", req.d[1]);}
 }   
 if(flag == 0 && req.d[4] != last2){    
    last2 = req.d[4];flag=0;
  if(req.d[4] > 0.5){motor1.Send(speedclass,2);
  }
  else if(req.d[4] <-0.5){motor1.Send(-1*speedclass,2);
  }
        else {motor1.Send(0,2);
        ROS_INFO("req.d: [%f]", req.d[4]);}
 } 
 } 
  if(req.c[4] == 1)
  {//motor1.Send(1);
  //pwm1.SetPWM(25);
  if(leftpwm < 1479)
  {leftpwm = leftpwm + 20;}
  ROS_INFO("pwm1: x=%d",pwm_function_from_python(leftpwm,1));
  PyErr_Print();
  }
  else if(req.d[2] == -1)
  {//motor1.Send(-1);
  //pwm1.SetPWM(16);
  if(leftpwm > 521)
  {leftpwm = leftpwm - 20;}
  ROS_INFO("pwm1: x=%d",pwm_function_from_python(leftpwm,1));
  PyErr_Print();
  }
  
    if(req.c[5] == 1)
  {
  if(rightpwm < 2479)
  {rightpwm = rightpwm + 20;}
  ROS_INFO("pwm2: x=%d",pwm_function_from_python(rightpwm,2));
  PyErr_Print();
  }
  else if(req.d[5] == -1)
  {
  if(rightpwm > 521)
  {rightpwm = rightpwm - 20;}
  ROS_INFO("pwm2: x=%d",pwm_function_from_python(rightpwm,2));
  PyErr_Print();
  }
  
  return true;
}




int main(int argc, char **argv)
{
  // ROS节点初始化
  ros::init(argc, argv, "add_two_ints_server");
  
  // 创建节点句柄
  ros::NodeHandle n;

  // 创建一个名为add_two_ints的server，注册回调函数add()
  ros::ServiceServer service = n.advertiseService("add_two_ints", add);

  
  motor1.InitRS485();
  //motor1.Send(1,1);
  //pwm1.InitPWM();
  //pwm1.SetPWM(16);
  
  stt = "pi.set_servo_pulsewidth(26, 1400)";
  st = (char *)malloc(100*sizeof(char));
  strcpy(st,stt.c_str());
  str = (char *)malloc(100*sizeof(char));
  Py_Initialize();
  //ROS_INFO("pwm: x=%d",pwm_function_from_python(1400));
  //pwm_function_from_python(2);
  //Py_Finalize();
  // 循环等待回调函数
  ROS_INFO("Ready to add two ints.");
  ros::spin();

  return 0;
}
