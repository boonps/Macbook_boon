



#include "DHT.h"
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266WiFi.h>






#define DHTPIN D4
#define DHTTYPE DHT22


DHT dht(DHTPIN, DHTTYPE);
ESP8266WiFiMulti WiFiMulti;
//WiFiClient client;



// Connect WiFi
const char* ssid = "ink";
const char* password = "12345678";


//// Soid Moisture
//const int AirValue = 620;   //you need to replace this value with Value_1
//const int WaterValue = 310;  //you need to replace this value with Value_2
//int soilMoistureValue = 0;
//int soilmoisturepercent = 0;


void setup() {
  Serial.begin(115200);
  Serial.println("DHT22 BoonStation");

  WiFi.begin(ssid, password); //ทำการเชื่อมต่อไปยัง AP

  while (WiFi.status() != WL_CONNECTED) { //รอจนกว่าจะเชื่อมต่อสำเร็จ
    Serial.print("."); //แสดง ... ไปเรื่อยๆ จนกว่าจะเชื่อมต่อได้
    delay(500);
  }

  Serial.println("");
  Serial.println(WiFi.localIP()); //แสดง IP ของบอร์ดที่ได้รับแจกจาก APSerial.println("");
  Serial.println("Wi-Fi connected"); //แสดงว่าเชื่อมต่อ Wi-Fi ได้แล้ว
  Serial.print("IP Address : ");
  Serial.println(WiFi.localIP()); //แสดง IP ของบอร์ดที่ได้รับแจกจาก AP
  Serial.print("MAC address: ");
  Serial.println(WiFi.macAddress());
  dht.begin();
}



void loop() {

  HTTPClient http;


  float humidi = dht.readHumidity();

  float tempc = dht.readTemperature();
  
  int ldr = analogRead(A0);
//
//  float f = dht.readTemperature(true);
//
//  float hi = dht.computeHeatIndex(f, h);
//
//  soilMoistureValue = analogRead(A0);  //put Sensor insert into soil
//  Serial.print("soilMoisture:");
//  Serial.println(soilMoistureValue);
//  soilmoisturepercent = map(soilMoistureValue, AirValue, WaterValue, 0, 100);


  //if(soilmoisturepercent > 100)
  //{
  //  Serial.println("100 %");
  //}
  //else if(soilmoisturepercent <0)
  //{
  //  Serial.println("0 %");
  //}
  //else if(soilmoisturepercent >0 && soilmoisturepercent < 100)
  //{
  //  Serial.print(soilmoisturepercent);
  //  Serial.println("%");
  //}



  if ((WiFiMulti.run() == WL_CONNECTED)) {
    float humidi = dht.readHumidity();
    float tempc = dht.readTemperature();
    int ldr = analogRead(A0);
//        Serial.print("humidity = ");
//        Serial.println(humidi);
//        Serial.print("tempc = ");
//        Serial.println(tempc);

    
   String url = "http://192.168.43.19/dht22/configdht22.php?humidi="+String(humidi)+"&tempc="+String(tempc)+"&ldr="+String(ldr);
//                  http://10.58.170.66/dht22/configdht22.php?humidi=25&tempc=22
//หากทดลองใช้โดยจำลอง Server เอง ต้องใชข้ ip เดียวกับ Wifi  hostpot ที่ connect อยูููู่่่
    Serial.println(url);
    http.begin(url); //HTTP
    int httpCode = http.GET();
    if (httpCode > 0) {
    Serial.printf("[HTTP] GET... code: %d\n", httpCode);
    if (httpCode == HTTP_CODE_OK) {
    String payload = http.getString();
    Serial.println(payload);
  }
} else {
Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
}
http.end();
}
delay(5000);

//
//String url = "http://10.58.170.66/dht22/configdht22.php";
//  Serial.println();
//  Serial.println("Get content from " + url);
//  
//  HTTPClient http;
//  http.begin(url);
//  int httpCode = http.POST("humidi=25&tempc=22");
//  if (httpCode == 200) {
//    String content = http.getString();
//    Serial.println("Content ---------");
//    Serial.println(content);
//    Serial.println("-----------------");
//  } else {
//    Serial.println("Fail. error code " + String(httpCode));
//  }
//  Serial.println("END");




    
  }
 // END PROGRAM
