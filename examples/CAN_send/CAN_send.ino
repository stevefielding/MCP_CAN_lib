// CAN Send Example
//

#include <mcp_can.h>
#include <SPI.h>

MCP_CAN CAN0(PIN_SPI_SS);     // Set CS to pin 10

#define POD_LED 22
#define RS485_TX_EN 6
#define SOL2_12V_EN 7
#define SOL1_12V_EN 3

void setup()
{
  pinMode(POD_LED, OUTPUT);
  pinMode(RS485_TX_EN, OUTPUT);
  digitalWrite(RS485_TX_EN, HIGH);
  pinMode(SOL1_12V_EN, OUTPUT);
  pinMode(SOL2_12V_EN, OUTPUT);
  digitalWrite(SOL1_12V_EN, LOW);
  digitalWrite(SOL2_12V_EN, LOW);

  Serial.begin(115200);

  // Initialize MCP2515 running at 16MHz with a baudrate of 500kb/s and the masks and filters disabled.
  if(CAN0.begin(MCP_ANY, CAN_500KBPS, MCP_16MHZ) == CAN_OK) Serial.println("MCP2515 Initialized Successfully!");
  else Serial.println("Error Initializing MCP2515...");

  CAN0.setMode(MCP_NORMAL);   // Change to normal mode to allow messages to be transmitted
}

byte data[8] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07};

void loop()
{
  // send data:  ID = 0x100, Standard CAN Frame, Data length = 8 bytes, 'data' = array of data bytes to send
  byte sndStat = CAN0.sendMsgBuf(0x100, 0, 8, data);
  if(sndStat == CAN_OK){
    Serial.println("Message Sent Successfully!");
  } else {
    Serial.println("Error Sending Message...");
  }
  delay(100);
  digitalWrite(POD_LED, HIGH);
  delay(100);   // send data per 100ms
  digitalWrite(POD_LED, LOW);
}

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
