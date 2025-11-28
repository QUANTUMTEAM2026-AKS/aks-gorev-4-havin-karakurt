#include <SPI.h>
#include <mcp2515.h>

MCP2515 mcp2515(10);
struct can_frame canMsg;

void setup() {
  Serial.begin(115200);
  SPI.begin();

  mcp2515.reset();
  mcp2515.setBitrate(CAN_500KBPS, MCP_8MHZ);
  mcp2515.setNormalMode();
}

void loop() {
  if (mcp2515.readMessage(&canMsg) == MCP2515::ERROR_OK) {

    if (canMsg.can_id == 0x300) {

      uint16_t packVoltage = (canMsg.data[0] << 8) | canMsg.data[1];
      uint16_t cellMin = (canMsg.data[2] << 8) | canMsg.data[3];
      uint16_t cellMax = (canMsg.data[4] << 8) | canMsg.data[5];
      uint8_t soc = canMsg.data[6];
      uint16_t current = (canMsg.data[8] << 8) | canMsg.data[9];
      uint16_t maxTemp = (canMsg.data[10] << 8) | canMsg.data[11];

      Serial.print("Pack Voltage: ");
      Serial.print(packVoltage);
      Serial.println(" mV");

      Serial.print("Cell Min: ");
      Serial.print(cellMin);
      Serial.println(" mV");

      Serial.print("Cell Max: ");
      Serial.print(cellMax);
      Serial.println(" mV");

      Serial.print("SOC: ");
      Serial.print(soc);
      Serial.println(" %");

      Serial.print("akım : ");
      Serial.print(current);
      Serial.println("A");

      Serial.print("sıcaklık: ");
      Serial.print(maxTemp);
      Serial.println("C");
    }
  }
}



