#include <M5Stack.h>
#include <WiFiClient.h>
#include <PubSubClient.h>
#include <WiFi.h>

//extern const unsigned char image_logo[]; 
// Wi-Fi SSID
const char* ssid = "90324BD2A4C4-2G";
// Wi-Fi PASSWORD
const char* password = "2215004356863";
 
//-------- Customise these values -----------
// 接続先のIBM Watson IoT Platform
#define ORG "g5ayqu"
// デバイスタイプはm5stackで
#define DEVICE_TYPE "RASPI3"
// デバイスIDは以下で
#define DEVICE_ID "0002"
// quickstartでは使わないが宣言はしておく
#define TOKEN "123123123"
//-------- Customise the above values --------
 
// 実際の接続するための設定群
char server[] = ORG ".messaging.internetofthings.ibmcloud.com";
char topic[] = "iot-2/evt/status/fmt/json";
char authMethod[] = "use-token-auth";
char token[] = TOKEN;
char clientId[] = "d:" ORG ":" DEVICE_TYPE ":" DEVICE_ID;
 
// WiFiClient準備
WiFiClient wifiClient;
 
// 入力の状態記録
int sensorValueState = LOW;
 
// ポート番号
const int port = 1883;
 
// 今回センサーがつながったピン番号 D2
int PIN = 2;
 
// MQTT接続のための準備
// QuickStartのため server , port だけ。あとはwifiClient紐付け。
PubSubClient client(server, port, wifiClient);
 
void setup() {
    // initialize the M5Stack object
    M5.begin();
    //M5.Lcd.drawBitmap(0, 0, 320, 240, (uint16_t *)image_logo);
    delay(500);
   
    M5.Lcd.fillScreen(BLACK);
   
    // M5.Lcd.setCursor(10, 10);
    M5.Lcd.setTextColor(WHITE);
    M5.Lcd.setTextSize(3);
    M5.Lcd.println("Send IBM Watson");
    M5.Lcd.println("IoT Platform!!!");
    M5.Lcd.println("");
     
    pinMode(PIN,INPUT);
    Serial.begin(115200);
   
    Serial.println("Connecting to ");
    Serial.println(ssid);
    Serial.println();
    if (strcmp (WiFi.SSID().c_str(), ssid) != 0) {
      WiFi.begin(ssid, password);
    }
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
    } 
    Serial.println("");
    Serial.print("WiFi connected, IP address: ");
    Serial.println(WiFi.localIP());
     
    // WiFi Connected
    Serial.println("\nWiFi Connected.");
    M5.Lcd.println("WiFi Connected.");
    M5.Lcd.println("");
 
    // INFO
    M5.Lcd.setTextSize(2);
    M5.Lcd.printf("ORG: ");
    M5.Lcd.println(ORG);
    M5.Lcd.printf("DEVICE_TYPE: ");
    M5.Lcd.println(DEVICE_TYPE);
    M5.Lcd.printf("DEVICE_ID: ");
    M5.Lcd.println(DEVICE_ID);
}
 
void loop() {
 
  String payload;
 
  // Serial.print(".");
 
  // MQTT再接続処理
  if (!!!client.connected()) {
    Serial.print("Reconnecting client to "); Serial.println(server);
    while (!!!client.connect(clientId, authMethod, token)) {
      Serial.print(".");
      delay(500);
    }
    Serial.println();
  }
 
  if(M5.BtnA.wasPressed()) {
    Serial.printf("wasPressed A \r\n");
 
    M5.Lcd.setCursor(10, 100);
    M5.Lcd.fillScreen(RED);
    M5.Lcd.setTextColor(YELLOW);
    M5.Lcd.setTextSize(3);
    M5.Lcd.printf("Pressed  ");
    M5.Lcd.setTextSize(10);
    M5.Lcd.printf("A");
 
    payload = "{ \"d\" : {\"flag\":1} }";
     
    // データ送信
    Serial.print("Sending payload: ");
    Serial.println(payload);
    if (client.publish(topic, (char*) payload.c_str())) {
      Serial.println("Publish ok");
    } else {
      Serial.println("Publish failed");
    }
 
    delay(1000);
  }
 
  if(M5.BtnB.wasPressed()) {
 
    Serial.printf("wasPressed B \r\n");
 
    M5.Lcd.setCursor(10, 100);
    M5.Lcd.fillScreen(BLUE);
    M5.Lcd.setTextColor(WHITE);
    M5.Lcd.setTextSize(3);
    M5.Lcd.printf("Pressed  ");
    M5.Lcd.setTextSize(10);
    M5.Lcd.printf("B");
 
    payload = "{ \"d\" : {\"flag\":2} }";
     
    // データ送信
    Serial.print("Sending payload: ");
    Serial.println(payload);
    if (client.publish(topic, (char*) payload.c_str())) {
      Serial.println("Publish ok");
    } else {
      Serial.println("Publish failed");
    }
 
    delay(1000);
  }
 
  if(M5.BtnC.wasPressed()) {
     
    Serial.printf("wasPressed C \r\n");
 
    M5.Lcd.setCursor(10, 100);
    M5.Lcd.fillScreen(GREEN);
    M5.Lcd.setTextColor(BLACK);
    M5.Lcd.setTextSize(3);
    M5.Lcd.printf("Pressed  ");
    M5.Lcd.setTextSize(10);
    M5.Lcd.printf("C");
     
    payload = "{ \"d\" : {\"flag\":3} }";
 
    // データ送信
    Serial.print("Sending payload: ");
    Serial.println(payload);
    if (client.publish(topic, (char*) payload.c_str())) {
      Serial.println("Publish ok");
    } else {
      Serial.println("Publish failed");
    }
 
    delay(1000);
  }
   
  M5.update();
   
   
}
