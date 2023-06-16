//------------------------------------------------------------------------------
#include "GTN.h"
//------------------------------------------------------------------------------
#if defined ( GTN_USE_HARDWARESERIAL )
#if defined ( ESP8266 )
GTN::GTN(HardwareSerial& serial, long baud, int config, bool swapuart) : gtnSer(serial) {
  this->_baud = baud;
  this->_config = config;
  this->_swapuart = swapuart;
}
#elif defined ( ESP32 )
GTN::GTN(HardwareSerial& serial, long baud, int config, int8_t rx_pin, int8_t tx_pin) : gtnSer(serial) {
  this->_baud = baud;
  this->_config = config;
  this->_rx_pin = rx_pin;
  this->_tx_pin = tx_pin;
}
#else
GTN::GTN(HardwareSerial& serial, long baud,  int config) : gtnSer(serial) {
  this->_baud = baud;
  this->_config = config;
}
#endif
#else
#if defined ( ESP8266 ) || defined ( ESP32 )
GTN::GTN(SoftwareSerial& serial, long baud, int config, int8_t rx_pin, int8_t tx_pin) : gtnSer(serial) {
  this->_baud = baud;
  this->_config = config;
  this->_rx_pin = rx_pin;
  this->_tx_pin = tx_pin;
}
#else
GTN::GTN(SoftwareSerial& serial, long baud) : gtnSer(serial) {
  this->_baud = baud;
}
#endif
#endif

GTN::~GTN() {
}

void GTN::begin(void) {
#if defined ( GTN_USE_HARDWARESERIAL )
#if defined ( ESP8266 )
  gtnSer.begin(_baud, (SerialConfig)_config);
#elif defined ( ESP32 )
  gtnSer.begin(_baud, _config, _rx_pin, _tx_pin);
#else
  gtnSer.begin(_baud, _config);
#endif
#else
#if defined ( ESP8266 ) || defined ( ESP32 )
  gtnSer.begin(_baud, (EspSoftwareSerial::Config)_config, _rx_pin, _tx_pin);
#else
  gtnSer.begin(_baud);
#endif
#endif

#if defined ( GTN_USE_HARDWARESERIAL ) && defined ( ESP8266 )
  if (_swapuart)
    gtnSer.swap();
#endif

}

void GTN::loop(void) {
  unsigned long now = millis();
  if ( now - _last > GTN_SENT_MS ) {
    sendPower();
    _last = now;
  }
}

void GTN::setPower(uint16_t power) {
  uint16_t temp = power;
  
  if (temp > MAX_POWER) {
    temp = MAX_POWER;
  }
  if (temp < 0) {
    temp = 0;
  }
  _power = temp;

}
void GTN::sendPower(void) {

  byte frame[GTN_FRAMESIZE];

  frame[0] = GTN_B_00;        
  frame[1] = GTN_B_01;
  frame[2] = GTN_B_02;
  frame[3] = GTN_B_03;
  frame[4] = _power >> 8;
  frame[5] = _power >> 0;
  frame[6] = GTN_B_06;
  frame[7] = 264 - frame[4] - frame[5]; // Checksum

  gtnSer.write( frame , GTN_FRAMESIZE );
}