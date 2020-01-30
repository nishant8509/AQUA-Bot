/**********************************************************************************                     
     * Project Name:   AQUABOT
     * Author List:     NISHANT MISHRA, MAYANK BANSAL                     
     * Filename:            code(AQUA-BOT)              
     * Functions:           setup,loop,sendthingspeak                 
     * Global Variables:   ssid,server,pass,moisturePin,motorPin,interval,previousmillis                        
   ***********************************************************************************                         
  */
#include <DHT.h>
#include <ESP8266WiFi.h>
String apiKey = "0SJXI3LHCEXPCOL7";     //  farmer's thingspak Write API key here
const char* server = "api.thingspeak.com";
const char *ssid =  "JS-JioPhone-9452";     // farmer's WiFi Name
const char *pass =  "nishubabu1"; // farmer's WiFi Password
#define DHTPIN D3          // GPIO Pin where the dht11 is connected
DHT dht(DHTPIN, DHT22);
WiFiClient client;

const int moisturePin = A0;             // moisture sensor pin
const int motorPin = D0;
unsigned long interval = 10000;
unsigned long previousMillis = 0;
unsigned long interval1 = 1000;
unsigned long previousMillis1 = 0;
float moisturePercentage;              //moisture reading
float h;                  // humidity reading
float t;                  //temperature reading
/* *******************************************************************************************************************
 * Function Name: Setup
 * Input:     none
 * Output:        Prints Whether the Wifi is connected or not
 * Logic:         The Function is used to connect the Node Mcu with the app TO perform the Moving,Digging etc Functions
 * Example Call:  Called Automatically By the App
 ********************************************************************************************************************** 
*/
void setup()
{
  Serial.begin(115200);
  delay(10);
  pinMode(motorPin, OUTPUT);
  digitalWrite(motorPin, LOW); // Keep motor off initally
  dht.begin();
  Serial.println("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");              // print ... till not connected
  }
  Serial.println("");
  Serial.println("WiFi connected");
}

/* *******************************************************************************************************************
 * Function Name: Loop
 * Input:     Inputs are determined by the sensors
 * Output:        It pass the values determined To THINGSPEAK server
 * Logic:         The Function is used to Get the readings such as Temperature, Humidity, Moisture From the respective Sensors
 * Example Call:  Called Automatically By the App
 ********************************************************************************************************************** 
*/
void loop()
{
  unsigned long currentMillis = millis(); // grab current time

  h = dht.readHumidity();     // read humiduty
  t = dht.readTemperature();     // read temperature

  if (isnan(h) || isnan(t))
  {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  moisturePercentage = ( 100.00 - ( (analogRead(moisturePin) / 1023.00) * 100.00 ) );

  if ((unsigned long)(currentMillis - previousMillis1) >= interval1) {
    Serial.print("Soil Moisture is  = ");
    Serial.print(moisturePercentage);
    Serial.println("%");
    previousMillis1 = millis();
  }


if ((unsigned long)(currentMillis - previousMillis) >= interval) {

  sendThingspeak();           //send data to thing speak
  previousMillis = millis();
  client.stop();
}

}
/* *******************************************************************************************************************
 * Function Name: sendThingspeak()
 * Input:     Sensor Readings
 * Output:        The update Values Of Sensors Reading
 * Logic:         The Function is used to Update the values such as Temperature, Humidity, Moisture 
 * Example Call:  Called Automatically By the Thingspeak Server
 ********************************************************************************************************************** 
*/
void sendThingspeak() {
  if (client.connect(server, 80))
  {
    String postStr = apiKey;              // add api key in the postStr string
    postStr += "&field1=";
    postStr += String(moisturePercentage);    // add mositure readin
    postStr += "&field2=";
    postStr += String(t);                 // add temperature reading
    postStr += "&field3=";
    postStr += String(h);                  // add humidity reading
    postStr += "\r\n\r\n";

    client.print("POST /update HTTP/1.1\n");
    client.print("Host: api.thingspeak.com\n");
    client.print("Connection: close\n");
    client.print("X-THINGSPEAKAPIKEY: " + apiKey + "\n");
    client.print("Content-Type: application/x-www-form-urlencoded\n");
    client.print("Content-Length: ");
    client.print(postStr.length());           //send length of the string
    client.print("\n\n");
    client.print(postStr);                      // send complete string
    Serial.print("Moisture Percentage: ");
    Serial.print(moisturePercentage);
    Serial.print("%. Temperature: ");
    Serial.print(t);
    Serial.print(" C, Humidity: ");
    Serial.print(h);
    Serial.println("%. Sent to Thingspeak.");
  }
}
