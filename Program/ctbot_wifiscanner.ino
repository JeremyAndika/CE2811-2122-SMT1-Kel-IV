#include "CTBot.h"
#include "ESP8266WiFi.h"
#include <WiFiClient.h> 
CTBot myBot;

String r = "Mencari Sinyal WiFi...";
String s = "Jaringan tidak ditemukan.";
String t = "  jaringan ditemukan.";
String u = "";
String za = "\n";

TBMessage tMessage;
String ssid = "new2";     // Sesuikan dengan nama wifi anda
String pass = "agung1234"; // sesuaikan password wifi
String token = "5649925801:AAGGN057W8mBW8rTdoJV-vUgmBMXB7KAHb8"; // token bot telegram yang telah dibuat

String data;
char c;

void setup() {
	Serial.begin(115200);

	myBot.wifiConnect(ssid, pass);

	myBot.setTelegramToken(token);

	// check if all things are ok
	Serial.println("logging in...");
    while (!myBot.testConnection())
    {
        myBot.setTelegramToken(token);
        delay(1000);
    }
    Serial.println("Telegram connection OK!");

}

void loop() {
  

    if (myBot.getNewMessage(tMessage))
    {
        Serial.println(tMessage.text);
        if (tMessage.messageType == CTBotMessageText)
        {
            if (tMessage.text.equalsIgnoreCase("/start"))
            {
                String reply = "";
                reply += "Hello user "+ tMessage.sender.firstName + " ke CTBot Kelompok 5\n";
                reply += "Untuk Scan WIFI gunakan Command: /scan \n";

                myBot.sendMessage(tMessage.sender.id, reply);
            }
            else if (tMessage.text.equalsIgnoreCase("/scan"))
            {
              int n = WiFi.scanNetworks();
            String sn = String(n);
              Serial.println("scan done");
              if (n == 0) {
                  Serial.println("no networks found");
              } else {
                  String a = sn + t + za + za;
              Serial.print(n);
              Serial.println(t);
              
              u = "";
              for (int i = 0; i < n; ++i) {
                int v = i + 1;
                String nv = String(v) + ". ";
                String w = String(WiFi.SSID(i)) + "  ";
                String x = String(WiFi.RSSI(i)) + "dBm";
                String y = nv + w + x + za;
                u = u + y;

                Serial.print("  ");
                Serial.print(nv);
                Serial.print(w);
                Serial.print(x);

                delay(10);
              }
                  String reply = "";
                  String zu = a + u;
                  reply += "Scanning :  \n";
                  reply += zu;
                  u = "";
                  zu = "";
                  
                  

                  myBot.sendMessage(tMessage.sender.id, reply);
              }
              Serial.println("");
              delay(1000);
              WiFi.scanDelete();       
            }
            else
            {
                String reply = "";
                reply += "Hello user "+ tMessage.sender.firstName + " ke CTBot Kelompok 5\n";
                reply += "Command tidak ditemukan silahkan kembali ke dengan command /start .\n";

                myBot.sendMessage(tMessage.sender.id, reply);
            }
        }
    }
}

void connectWifi()
{
    Serial.println("Connecting To Wifi");
    WiFi.begin(ssid.c_str(), pass.c_str());
    while (WiFi.status() != WL_CONNECTED)
    {
        Serial.print(".");
        delay(500);
    }

    Serial.println("Wifi Connected");
    Serial.println(WiFi.SSID());
    Serial.println(WiFi.macAddress());
    Serial.println(WiFi.localIP());
    Serial.println(WiFi.gatewayIP());
    Serial.println(WiFi.dnsIP());
}

void loginTelegram()
{
    
}