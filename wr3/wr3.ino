#include <SPI.h>
#include <mcp2515.h>

struct can_frame canMsg;
MCP2515 mcp2515(10);  

void setup() {
  Serial.begin(115200);
  SPI.begin();

 
  mcp2515.reset();
  mcp2515.setBitrate(CAN_500KBPS, MCP_8MHZ); 
  mcp2515.setNormalMode();

  Serial.println("BMS CAN verici basladi!");
}

void loop() {
 
  uint16_t packVoltage = 52300;  
  uint16_t maxCellVolt = 4200;  
  uint16_t minCellVolt = 3900;  
  uint8_t soc = 78;
  uint16_t current_mA = 1500; 
  uint16_t maxTemp = 45;             

  // CAN mesajını hazırla
  canMsg.can_id  = 0x300; 
  canMsg.can_dlc = 8;     

  canMsg.data[0] = packVoltage >> 8;
  canMsg.data[1] = packVoltage & 0xFF;

  canMsg.data[2] = maxCellVolt >> 8;
  canMsg.data[3] = maxCellVolt & 0xFF;

  canMsg.data[4] = minCellVolt >> 8;
  canMsg.data[5] = minCellVolt & 0xFF;

  canMsg.data[6] = soc;   
  canMsg.data[7] = 0;  

  canMsg.data[8]= current_mA >> 8;
   canMsg.data[9] = current_mA & 0xFF;

   canMsg.data[10]= maxTemp >> 8;
   canMsg.data[11] = maxTemp & 0xFF;

 
  mcp2515.sendMessage(&canMsg);

  Serial.println("BMS verisi gonderildi!");
  delay(500); 
}







