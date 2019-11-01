
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <TM1637Display.h>
//************************* header files***********************************

  #include <Wire.h>
#include "RTClib.h"
RTC_DS1307 RTC;
//******************************** rtc ******************************************************************************

const int CLK = D6; //Set the CLK pin connection to the display
const int DIO = D5; //Set the DIO pin connection to the display

const int clk1=D3;
const int dio1=D4;
int numCounter = 0;
 
TM1637Display display1(CLK, DIO); //set up the 4-Digit Display.
TM1637Display display2(clk1,dio1);
TM1637Display  showDots();
 //******************************  4 digit 7 segment *********************************************************************




// Update these with values suitable for your network.
const char* ssid = "watch1";//put your wifi ssid here
const char* password = "watch1234";//put your wifi password here
const char* mqtt_server = "test.mosquitto.org";



WiFiClient espClient;
PubSubClient client(espClient);

long lastMsg = 0;
char msg[50];
int value = 0;
void setup_wifi() {
      

  // We start by connecting to a WiFi network
    Serial.print("Connecting to ");
    Serial.println(ssid);
    WiFi.begin(ssid, password);
   int k=0;
    while (WiFi.status() != WL_CONNECTED) 
    {
      
      Serial.print(".");
   
      break;
   
    }
  randomSeed(micros());
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}


int state=1;
 uint8_t data[] = { 0xff, 0xff, 0xff, 0xff };
void callback(char* topic, byte* payload, unsigned int length) 
{
  Serial.print("Command from MQTT broker is : [");
  Serial.print(topic);
   Serial.println();
  Serial.print(" publish data is:");
  
       if(payload[0]==0)
        {
             for(int f = 0; f < 4; f++) 
                {
                  display1.setBrightness(7, false);  // Turn off
                  
                  display2.setBrightness(7, false);  // Turn off
                  

                   state=0;
                  return; 
                }
         }

  
  for(int i=0;i<length;i++)
  {
   // display.showNumberDec((char)payload[i],false,4,0); //Display the numCounter value;
    Serial.print(payload[i]);
    //  rtc time adjustment
    if(payload[0]==1)
     {         for(int f = 0; f < 4; f++) {
          display1.setBrightness(7, true);  // Turn off
          
             display2.setBrightness(7,true);  // Turn off
                 

//        delay(TEST_DELAY);
            state=2;
  
  //  delay(TEST_DELAY);  
              }
    
      if(payload[1]==1)
         {
             RTC.adjust(DateTime(2019, 8, 26, payload[2],payload[3] , payload[4]));
          }
          
     }
    
  }
 

} //end callback




void reconnect() {
  // Loop until we're reconnected
 int b=0;
  for(int kj=0;kj<1;kj++)
  {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    //if you MQTT broker has clientID,username and password
    //please change following line to    if (client.connect(clientId,userName,passWord))
    Serial.println("attempting");
   
    if (client.connect(clientId.c_str()))
    {
      Serial.println("connected");
     //once connected to MQTT broker, subscribe command if any
      client.subscribe("OsoyooCommand");
      
    } 
   
  }
} //end reconnect()

void setup() {
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
   display1.setBrightness(0x0f);
  display2.setBrightness(0x0f);
 //********************************************************************** rtc set up**********************************
    Wire.begin();
    RTC.begin();
  if (! RTC.isrunning()) {
    Serial.println("RTC is NOT running!");
    // following line sets the RTC to the date & time this sketch was compiled
    RTC.adjust(DateTime(__DATE__, __TIME__));
  //RTC.adjust(DateTime(2019, 8, 26, 1, , 3));
  
  }
 //RTC.adjust(DateTime(2019, 8, 26, 1, 46, 5));



}
//**********************************************************************************************************
 int colon=1;
int a=0;
int k=1;
int sec;
int p=0;
int o=0;
void loop() { 
 
  if (!client.connected()) {
    reconnect();
      //client.setCallback(callback);

  }
  o++;
  client.setCallback(callback);
  
  if(state==2){
      display1.setBrightness(0x0f);
  
     display1.setBrightness(7, true);  // Turn off
   
    state=1;
  }
  if(state==0){

           for(int f = 0; f < 4; f++) {
    display1.setBrightness(7, false);  // Turn off
    display1.setSegments(data);
     display2.setBrightness(7, false);  // Turn off
    display2.setSegments(data);

  
  continue;
  }
  
  }
  
  client.loop();
   
  
  k=1;
 
  DateTime now = RTC.now(); 
   
    int hour1=now.hour();
    int minute1=now.minute();
    
    
    /*
     *  int num=10;
 for(k=0; k <= 1; k++) {
    display.showNumberDecEx(num, (0x80 >> k), true);
    delay(500);
  
  //  delay(TEST_DELAY);
  }
     * 
     */

     
    numCounter=((hour1*100)+minute1);
 
 
 display1.showNumberDecEx(numCounter, (0x80 >> k), true);
sec=now.second();
   display2.showNumberDecEx(sec*100, (0x80 >> k), true);






}
