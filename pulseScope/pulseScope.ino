/**
 * Catching a pulse at input 0
 * 
 **/

//includes
#if (ARDUINO >= 100)
 #include <Arduino.h>
#else
 #include <WProgram.h>
#endif
#include <ros.h>
#include <std_msgs/Float32.h>

//ROS variables
ros::NodeHandle nh;
std_msgs::Float32 float_msg;
ros::Publisher p("pulse", &float_msg);

//other variables
unsigned int tail_counter = 0;
bool publish_flag;

//setup 
void setup()
{ 
    //ROS init
    nh.initNode();
    nh.advertise(p);
}

//Averaging the analog reading to elminate some of the noise
int averageAnalog(int pin){
  int v=0;
  for(int i=0; i<4; i++) v+= analogRead(pin);
  return v/4;
}

//long adc_timer;

void loop()
{

    //getting input
    float_msg.data = (float)averageAnalog(0) * 5.0/1023.0; //convert ADC level to volts
    
    
    //check pulse and publish if it exists
    if (float_msg.data > 0.05) //greater than 50mV
    {
        publish_flag = true;
        tail_counter = 0;
    }
    if (tail_counter < 10)
    {
        publish_flag = true;
        tail_counter ++;
    }
    
    //publish message
    if (publish_flag)
    {
        p.publish(&float_msg);
        publish_flag = false;
    }

    //spin (ros sync and attend callbacks, if any ...)
    nh.spinOnce();
}

