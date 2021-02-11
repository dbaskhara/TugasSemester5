#include <SoftwareSerial.h>
#include <DHT.h>
#include <Servo.h>
#define DHTTYPE DHT11

Servo myservo;
int trig = 12;           // membuat varibel trig yang di set ke-pin 3
int echo = 11;           // membuat variabel echo yang di set ke-pin 2
long durasi, jarak;     // membuat variabel durasi dan jarak
SoftwareSerial BTserial(2, 3); // RX | TX
char c = ' ';
const int DHTpin = 4;
DHT dht(DHTpin, DHTTYPE);
int pos = 0; 
float hum;  //Stores humidity value
float temp; //Stores temperature value

void setup(){
    pinMode(trig, OUTPUT);    // set pin trig menjadi OUTPUT
  pinMode(echo, INPUT);     // set pin echo menjadi INPUT
    Serial.begin(9600);
    Serial.println("Arduino is ready");
    dht.begin();
    BTserial.begin(9600);  
    myservo.attach(9);
    
}

void loop(){
  digitalWrite(trig, LOW);
  delayMicroseconds(8);
  digitalWrite(trig, HIGH);
  delayMicroseconds(8);
  digitalWrite(trig, LOW);
  delayMicroseconds(8);

hum = dht.readHumidity();
    temp= dht.readTemperature();
    hum = dht.readHumidity();
  durasi = pulseIn(echo, HIGH); // menerima suara ultrasonic
  jarak = (durasi / 2) / 29.1;  // mengubah durasi menjadi jarak (cm)
  //Serial.println(jarak);        // menampilkan jarak pada Serial Monitor
  //BTserial.println(jarak);
  if(jarak <= 10){
    BTserial.println("tempat sampah penuh");
    
  }
   if (hum >= 20) {
      myservo.write(180); 
    } else {
      myservo.write(0); 
    }
    Serial.println(hum);
  delay(1000);
}
