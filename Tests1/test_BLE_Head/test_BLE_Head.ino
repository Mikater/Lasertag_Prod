#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>

#define bleServerName "Salo_ESP32"

int saloValue;
unsigned long lastTime = 0;
unsigned long timerDelay = 30000;
bool deviceConnected = false;

#define SERVICE_UUID "91bad492-b950-4226-aa2b-4ede9fa42f59"
#define CHARACTERISTIC_UUID "cba1d466-344c-4be3-ab3f-189f80dd7518"

BLECharacteristic saloCharacteristic(CHARACTERISTIC_UUID, BLECharacteristic::PROPERTY_NOTIFY);
BLEDescriptor saloDescriptor(BLEUUID((uint16_t)0x2902));

class MyServerCallbacks: public BLEServerCallbacks {
  void onConnect(BLEServer* pServer) {
    deviceConnected = true;
  }
  void onDisconnect(BLEServer* pServer) {
    deviceConnected = false;
  }
};

void setup() {
  Serial.begin(115200);

  BLEDevice::init(bleServerName);
  BLEServer *pServer = BLEDevice::createServer();
  pServer->setCallbacks(new MyServerCallbacks());

  BLEService *saloService = pServer->createService(SERVICE_UUID);
  saloService->addCharacteristic(&saloCharacteristic);
  saloDescriptor.setValue("Random Salo Value");
  saloCharacteristic.addDescriptor(&saloDescriptor);

  saloService->start();
  pServer->getAdvertising()->start();
  Serial.println("Waiting for a client connection to notify...");
}

void loop() {
  if (deviceConnected) {
    if ((millis() - lastTime) > timerDelay) {
      saloValue = random(0, 100); // Generate a random integer value for Salo
      saloCharacteristic.setValue(saloValue);
      saloCharacteristic.notify();
      Serial.print("Salo Value: ");
      Serial.println(saloValue);
      lastTime = millis();
    }
  }
}
