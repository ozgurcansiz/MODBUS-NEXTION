#include <modbus.h>
#include <modbusDevice.h>
#include <modbusRegBank.h>
#include <modbusSlave.h>
#include "DHT.h"
#include "NexButton.h"
#include "NexText.h"
#include "NexPicture.h"
#include "NexCrop.h"
#include "NexSlider.h"
#include "Arduino.h"
#include "Nextion.h"

//**************************************************************
void t0PopCallback(void *ptr);
float ISI0;
float ISI1;
float ISI2;
float ISI3;
float ISI4;
float ISI5;
char buffer[10] = {0};

NexNumber n0 = NexNumber(0, 1, "n0");
NexNumber n1 = NexNumber(0, 2, "n1");
NexNumber n2 = NexNumber(0, 3, "n2");
NexNumber n3 = NexNumber(0, 4, "n3");
NexNumber n4 = NexNumber(0, 5, "n4");
NexNumber n5 = NexNumber(0, 6, "n5");
NexNumber n6 = NexNumber(0, 7, "n6");
NexButton b0 = NexButton(0, 8, "b0");
NexButton b1 = NexButton(0, 9, "b1");
int a;


NexTouch *nex_listen_list[] =
{
  &n0, &n1, &n2, &n3, &n4, &n5, &n6,  &b0, &b1,

  NULL
};
void t0PopCallback(void *ptr)
{

}
void n0PopCallback(void *ptr)
{     

}
void n1PopCallback(void *ptr)
{
  

}
void n2PopCallback(void *ptr)
{

}
void n3PopCallback(void *ptr)
{

}
void n4PopCallback(void *ptr)
{

}
void n5PopCallback(void *ptr)
{
}
void n6PopCallback(void *ptr)
{
}
void b0PopCallback(void *ptr)
{
  NexButton *btn = (NexButton *)ptr;
  memset(buffer, 0, sizeof(buffer));
  btn->getText(buffer, sizeof(buffer));
  if (strcmp(buffer, "KAPALI"))
  {
    digitalWrite(6, HIGH);
    strcpy(buffer, "KAPALI");
  }
  else
  {
    digitalWrite(6, LOW);
    strcpy(buffer, "ACIK");
  }
  btn->setText(buffer);

}
void b1PopCallback(void *ptr)
{
  NexButton *btn = (NexButton *)ptr;
  memset(buffer, 0, sizeof(buffer));
  btn->getText(buffer, sizeof(buffer));
  if (strcmp(buffer, "KAPALI"))
  {
    digitalWrite(7, HIGH);
    strcpy(buffer, "KAPALI");
  }
  else
  {
    digitalWrite(7, LOW);
    strcpy(buffer, "ACIK");
  }
  btn->setText(buffer);

}
#define DHTPIN 51          // what digital pin we're connected to
#define DHTTYPE DHT11     // DHT11
DHT dht(DHTPIN, DHTTYPE);

/*
  This example code shows a quick and dirty way to get an
  arduino to talk to a modbus master device with a
  device ID of 1 at 9600 baud.
*/

//Setup the brewtrollers register bank
//All of the data accumulated will be stored here
modbusDevice regBank;
//Create the modbus slave protocol handler
modbusSlave slave;

void setup()
{ dht.begin();

  nexInit();
  n0.attachPop(n0PopCallback);
  n1.attachPop(n1PopCallback);
  n2.attachPop(n2PopCallback);
  n3.attachPop(n3PopCallback);
  n4.attachPop(n4PopCallback);
  n5.attachPop(n5PopCallback);
  n6.attachPop(n6PopCallback);
  b0.attachPop(b0PopCallback);
  b0.attachPop(b0PopCallback, &b0);
  b1.attachPop(b1PopCallback, &b1);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  digitalWrite(6, LOW);
  digitalWrite(7, LOW);
  //Assign the modbus device ID.
  regBank.setId(1);

  /*
    modbus registers follow the following format
    00001-09999  Digital Outputs, A master device can read and write to these registers
    10001-19999  Digital Inputs, A master device can only read the values from these registers
    30001-39999  Analog Inputs, A master device can only read the values from these registers
    40001-49999  Analog Outputs, A master device can read and write to these registers

    Analog values are 16 bit unsigned words stored with a range of 0-32767
    Digital values are stored as bytes, a zero value is OFF and any nonzer value is ON

    It is best to configure registers of like type into contiguous blocks.  this
    allows for more efficient register lookup and and reduces the number of messages
    required by the master to retrieve the data
  */

  //Add Digital Output registers 00001-00016 to the register bank
  regBank.add(1);
  regBank.add(2);
  regBank.add(3);
  regBank.add(4);
  regBank.add(5);
  regBank.add(6);
  regBank.add(7);
  regBank.add(8);
  regBank.add(9);
  regBank.add(10);
  regBank.add(11);
  regBank.add(12);
  regBank.add(13);
  regBank.add(14);
  regBank.add(15);
  regBank.add(16);

  //Add Digital Input registers 10001-10008 to the register bank
  regBank.add(10001);
  regBank.add(10002);
  regBank.add(10003);
  regBank.add(10004);
  regBank.add(10005);
  regBank.add(10006);
  regBank.add(10007);
  regBank.add(10008);

  //Add Analog Input registers 30001-10010 to the register bank
  regBank.add(30001);
  regBank.add(30002);
  regBank.add(30003);
  regBank.add(30004);
  regBank.add(30005);
  regBank.add(30006);
  regBank.add(30007);
  regBank.add(30008);
  regBank.add(30009);
  regBank.add(30010);

  //Add Analog Output registers 40001-40020 to the register bank
  regBank.add(40001);
  regBank.add(40002);
  regBank.add(40003);
  regBank.add(40004);
  regBank.add(40005);
  regBank.add(40006);
  regBank.add(40007);
  regBank.add(40008);
  regBank.add(40009);
  regBank.add(40010);
  regBank.add(40011);
  regBank.add(40012);
  regBank.add(40013);
  regBank.add(40014);
  regBank.add(40015);
  regBank.add(40016);
  regBank.add(40017);
  regBank.add(40018);
  regBank.add(40019);
  regBank.add(40020);

  /*
    Assign the modbus device object to the protocol handler
    This is where the protocol handler will look to read and write
    register data.  Currently, a modbus slave protocol handler may
    only have one device assigned to it.
  */
  slave._device = &regBank;

  // Initialize the serial port for coms at 9600 baud
  slave.setBaud(9600);
}

void loop(void)
{
  

  float humi = dht.readHumidity();
  float tempC = dht.readTemperature();
  float tempF = dht.readTemperature(true);
  ISI0 = tempC;
  ISI1 = humi;
  ISI2 = tempF;


  n0.setValue(ISI0);
  n1.setValue(ISI1);
  n2.setValue(ISI2);


while (1)
  {    
      nexLoop(nex_listen_list);
    //put a random number into registers 1, 10001, 30001 and 40001
    //n3.setValue(regBank.get(40001));
    //n4.setValue(regBank.get(40001));
    //n5.setValue(regBank.get(40003));
    //n6.setValue(regBank.get(40005));
    regBank.set(40015, (word)  random(1, 1000 ));
    slave.run();
  }

}
