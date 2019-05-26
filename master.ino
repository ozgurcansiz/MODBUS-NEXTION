

#include <ModbusMaster232.h>
ModbusMaster232 node(1); //  ModbusMaster object as slave ID 1
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
NexNumber n0 = NexNumber(0, 1, "n0");
NexNumber n1 = NexNumber(0, 2, "n1");
NexNumber n2 = NexNumber(0, 3, "n2");
NexNumber n3 = NexNumber(0, 4, "n3");
NexNumber n4 = NexNumber(0, 5, "n4");
NexNumber n5 = NexNumber(0, 6, "n5");

NexTouch *nex_listen_list[] =
{
  &n0, &n1, &n2, &n3, &n4, &n5,

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



//***************************************************************
const int trigPin = 49;
const int echoPin = 48;
long duration;
int distance;
//*******************************************************************
#define DHTPIN 51          // what digital pin we're connected to
#define DHTTYPE DHT11     // DHT11
DHT dht(DHTPIN, DHTTYPE);
//*****************************************************************
int sensorPin = A0;    // select the input pin for the potentiometer
int sensorPin1 = A1;    // select the input pin for the potentiometer
int sensorValue = 0;  // variable to store the value coming from the sensor
int sensorValue1 = 0;  // variable to store the value coming from the sensor
//*******************************************************************

void setup()
{
  Serial.begin(9600);
  node.begin(9600);  // Modbus RTU
  //***********************************************************
  nexInit();
  n0.attachPop(n0PopCallback);
  n1.attachPop(n1PopCallback);
  n2.attachPop(n2PopCallback);
  n3.attachPop(n3PopCallback);
  n4.attachPop(n4PopCallback);
  n5.attachPop(n5PopCallback);


  //*************************************************************
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  //**************************************************************
  dht.begin();
  //*************************************************************
  pinMode(6, OUTPUT);

}


void loop()
{
  sensorValue = analogRead(sensorPin);
  sensorValue1 = analogRead(sensorPin1);
  //nexLoop(nex_listen_list);

  //**********************************************************
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;
  //****************DHT-11*****************************************
  float humi = dht.readHumidity();
  float tempC = dht.readTemperature();
  float tempF = dht.readTemperature(true);

  if (isnan(humi) || isnan(tempC) || isnan(tempF))
  {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  //*************************************************************
  //*********************************************************
  ISI0 = tempC;
  ISI1 = humi;
  ISI2 = tempF;
  ISI3 = distance;
  ISI4 = sensorValue;
  ISI5 = sensorValue1;

  //n0.setValue(ISI0);
  //n1.setValue(ISI1);
  n2.setValue(ISI2);
  n3.setValue(ISI3);
  n4.setValue(ISI4);
  n5.setValue(ISI5);

  int Mdelay = 15;   // microdelay
  /*
    node.readHoldingRegisters(1, 1);
    Serial.print("[0] ");
    Serial.print(node.getResponseBuffer(0));
    /*
      if (node.getResponseBuffer(0)==1)
      {
      Serial.print(" gol ");
      }
      else{  Serial.print(" nahhhh ");
      }

    delay(Mdelay);
    node.clearResponseBuffer();


    Serial.print("  ");

    node.readHoldingRegisters(2, 1);
    Serial.print("[1] ");
    Serial.print(node.getResponseBuffer(0));
    delay(Mdelay);
    node.clearResponseBuffer();


    Serial.print("  ");

    node.readHoldingRegisters(4, 1);
    Serial.print("[2] ");
    Serial.print(node.getResponseBuffer(0));
    delay(Mdelay);
    node.clearResponseBuffer();


    Serial.print("  ");

    node.readHoldingRegisters(5, 1);
    Serial.print("[3] ");
    Serial.print(node.getResponseBuffer(0));
    delay(Mdelay);
    node.clearResponseBuffer();

  */
  Serial.print("  ");

  node.readHoldingRegisters(14 , 1);
  int a =node.getResponseBuffer(0);
  n0.setValue(node.getResponseBuffer(0));
  if ( a<= 500)
   {
    digitalWrite(6, HIGH);  
   }
   else
   {  digitalWrite(6, LOW);  

   }
  Serial.print("[4] ");
  Serial.print(node.getResponseBuffer(0));
  delay(Mdelay);
  node.clearResponseBuffer();


  Serial.print("  ");

  node.readHoldingRegisters(1, 1);
  n1.setValue(node.getResponseBuffer(0));

  Serial.print("[5] ");
  Serial.print(node.getResponseBuffer(0));
  delay(Mdelay);
  node.clearResponseBuffer();


  Serial.print("  ");

  node.readHoldingRegisters(2, 1);
  Serial.print("[6] ");
  Serial.print(node.getResponseBuffer(0));
  delay(Mdelay);
  node.clearResponseBuffer();


  Serial.print("  ");

  node.readHoldingRegisters(107, 1);
  Serial.print("[7] ");
  Serial.print(node.getResponseBuffer(0));
  delay(Mdelay);
  node.clearResponseBuffer();


  Serial.print("  ");

  node.readHoldingRegisters(108, 1);
  Serial.print("[8] ");
  Serial.print(node.getResponseBuffer(0));
  delay(Mdelay);
  node.clearResponseBuffer();


  Serial.print("  ");

  node.readHoldingRegisters(109, 1);
  Serial.print("[9] ");
  Serial.println(node.getResponseBuffer(0));
  delay(Mdelay);
  node.clearResponseBuffer();



  ///////// Holding Register [10]  A [19]  =  10 Holding  Registers Lectura
  /////     Holding Register [10] A [19]   =  10 Holding Registers Reading

  node.writeSingleRegister(0, tempC);//40001
  node.writeSingleRegister(1, humi);//40002
  node.writeSingleRegister(2, tempF);//40003
  node.writeSingleRegister(3, distance);//40004
  node.writeSingleRegister(4, sensorValue);//40005
  node.writeSingleRegister(5, sensorValue1);//40006

  node.writeSingleRegister(6,  6 );
  node.writeSingleRegister(7, 7 );
  node.writeSingleRegister(8, 8 );
  node.writeSingleRegister(9, 9 );
  node.writeSingleRegister(10,  10 );
  node.writeSingleRegister(11,  1000 );
  node.writeSingleRegister(12,  5000 );
  node.writeSingleRegister(13, random(1, 1000 ));
  node.writeSingleRegister(171, random(1, 1000 ));

}
