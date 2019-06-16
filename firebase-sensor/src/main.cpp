
/*
 * Libraries FirebaseESP8266 and universal-thermistor created by K. Suwatchai (Mobizt) and by Paul Cowan
 * Examples modfied by Thiago Fontes
*/

//This example shows how to set and push timestamp (server time) which is the server variable that suopported by Firebase

//FirebaseESP8266.h must be included before ESP8266WiFi.h
#include "FirebaseESP8266.h"
#include "thermistor.h"

Thermistor *thermistor;


#define FIREBASE_HOST "Your firebase path"
#define FIREBASE_AUTH "Your firebase auth Token"
#define WIFI_SSID "Sua rede"
#define WIFI_PASSWORD "Sua senha"

//Define Firebase Data object
FirebaseData firebaseData;
uint16_t temp;

void push_temp_c( double tempC, String path ) {
  //Plus 5 to calibrate the sensor that I'm using
  if (Firebase.pushDouble(firebaseData, path + "/Log/TempC", tempC + 5.0))
  {
    Serial.println("PASSED");
    Serial.println("PATH: " + firebaseData.dataPath());
    Serial.print("PUSH NAME: ");
    Serial.println(firebaseData.pushName());
    Serial.println("ETag: " + Firebase.getETag(firebaseData, path + "/Push/Timestamp/" + firebaseData.pushName()));
    Serial.println("------------------------------------");
    Serial.println();
  }
  else
  {
    Serial.println("FAILED");
    Serial.println("REASON: " + firebaseData.errorReason());
    Serial.println("------------------------------------");
    Serial.println();
  }
}

void set_temp_c(double tempC, String path ) {
  if (Firebase.setDouble(firebaseData, path + "/Current/TempC", tempC + 5.0))
    {
      Serial.println("PASSED");
      Serial.println("PATH: " + firebaseData.dataPath());
      Serial.println("TYPE: " + firebaseData.dataType());
      Serial.print("TIMESTAMP: ");
      Serial.println(firebaseData.intData());
      Serial.println("ETag: " + Firebase.getETag(firebaseData, path + "/Current/TempC"));
      Serial.println("------------------------------------");
      Serial.println();
    }
    else
    {
      Serial.println("FAILED");
      Serial.println("REASON: " + firebaseData.errorReason());
      Serial.println("------------------------------------");
      Serial.println();
    }
}


void setup() {

  Serial.begin(115200);
  Serial.println();
  Serial.println();

  /*
   * arg 1: pin: Analog pin
   * arg 2: vcc: Input voltage
   * arg 3: analogReference: reference voltage. Typically the same as vcc, but not always (ie ESP8266=1.0)
   * arg 4: adcMax: The maximum analog-to-digital convert value returned by analogRead (1023 or 4095)
   * arg 5: seriesResistor: The ohms value of the fixed resistor (based on your hardware setup, usually 10k)
   * arg 6: thermistorNominal: Resistance at nominal temperature (will be documented with the thermistor, usually 10k)
   * arg 7: temperatureNominal: Temperature for nominal resistance in celcius (will be documented with the thermistor, assume 25 if not stated)
   * arg 8: bCoef: Beta coefficient (or constant) of the thermistor (will be documented with the thermistor, typically 3380, 3435, or 3950)
   * arg 9: samples: Number of analog samples to average (for smoothing)
   * arg 10: sampleDelay: Milliseconds between samples (for smoothing)
 */

  thermistor = new Thermistor(A0, 3.3, 3.3, 1023, 50, 50, 25, 3950, 5, 20);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);

  /*
  This option allows get and delete functions (PUT and DELETE HTTP requests) works for device connected behind the
  Firewall that allows only GET and POST requests.

  Firebase.enableClassicRequest(firebaseData, true);
  */
}

void loop() {
  String path = "ESP8266-TEMP";
  //Temperature in fahrenheit
  double tempF = thermistor->readTempF();
  Serial.println("tempF=" + String(tempF));

  //Temperature in celcius
  double tempC = thermistor->readTempC();
  Serial.println("tempC=" + String(tempC));

  //Sending temperature values to firebase
  set_temp_c(tempC, path);
  push_temp_c(tempC, path);

  //Delay 900000 milliseconds, 15 minutes
  delay(900000);
}
