/*

Simple Libary to Control SoyoSource GTN 1200 

Use gtn_user_config.h to set your Pins

*/
#ifndef GTN_h
#define GTN_h

#include <Arduino.h>
#include "gtn_user_config.h"


#if defined ( GTN_USE_HARDWARESERIAL )
  #include <HardwareSerial.h>
#else
  #include <SoftwareSerial.h>
#endif

//DEFAULT CONFIG (DO NOT CHANGE ANYTHING!!! for changes use GTN_Config_User.h):

#if !defined ( GTN_UART_BAUD )
  #define GTN_UART_BAUD                               4800                      //  default baudrate
#endif

#if defined ( GTN_USE_HARDWARESERIAL )

  #if !defined ( GTN_UART_CONFIG )
    #define GTN_UART_CONFIG                           SERIAL_8N1                //  default hardware uart config
  #endif

  #if defined ( ESP8266 ) && !defined ( SWAPHWSERIAL )
    #define SWAPHWSERIAL                              0                         //  (only esp8266) when hwserial used, then swap uart pins from 3/1 to 13/15 (default not swap)
  #endif

  #if defined ( ESP32 )
    #if !defined ( GTN_RX_PIN )
      #define GTN_RX_PIN                              -1                        //  use default rx pin for selected port
    #endif
    #if !defined ( GTN_TX_PIN )
      #define GTN_TX_PIN                              -1                        //  use default tx pin for selected port
    #endif
  #endif

#else

  #if defined ( ESP8266 ) || defined ( ESP32 )
    #if !defined ( GTN_UART_CONFIG )
      #define GTN_UART_CONFIG                         SWSERIAL_8N1              //  default softwareware uart config for esp8266/esp32
    #endif
  #endif


  #if !defined ( GTN_RX_PIN )
    #define GTN_RX_PIN                                -1
  #endif
  #if !defined ( GTN_TX_PIN )
    #define GTN_TX_PIN                                -1
  #endif

#endif

#define MAX_POWER                                     700

#define GTN_FRAMESIZE                                 8                         //  size of out/in array

#define GTN_B_00                                      0x24                      //  BYTE 0 
#define GTN_B_01                                      0x56                      //  BYTE 1 
#define GTN_B_02                                      0x00                      //  BYTE 2
#define GTN_B_03                                      0x21                      //  BYTE 3
#define GTN_B_06                                      0x80                      //  BYTE 6

#define GTN_SENT_MS                                   1000                      // alle 1000ms senden

class GTN {
  public:
#if defined ( GTN_USE_HARDWARESERIAL )                                              //  hardware serial
  #if defined ( ESP8266 )                                                       //  on esp8266
    GTN(HardwareSerial& serial, long baud = GTN_UART_BAUD, int config = GTN_UART_CONFIG, bool swapuart = SWAPHWSERIAL);
  #elif defined ( ESP32 )                                                       //  on esp32
    GTN(HardwareSerial& serial, long baud = GTN_UART_BAUD, int config = GTN_UART_CONFIG, int8_t rx_pin = GTN_RX_PIN, int8_t tx_pin = GTN_TX_PIN);
  #else                                                                         //  on avr
    GTN(HardwareSerial& serial, long baud = GTN_UART_BAUD, int config = GTN_UART_CONFIG);
  #endif
#else                                                                           //  software serial
  #if defined ( ESP8266 ) || defined ( ESP32 )                                  //  on esp8266/esp32
    GTN(SoftwareSerial& serial, long baud = GTN_UART_BAUD, int config = GTN_UART_CONFIG, int8_t rx_pin = GTN_RX_PIN, int8_t tx_pin = GTN_TX_PIN);
  #else                                                                         //  on avr
    GTN(SoftwareSerial& serial, long baud = GTN_UART_BAUD);
  #endif
#endif
    virtual ~GTN();

    void begin(void);
    void loop(void);
    void setPower(uint16_t power);                       //  read value from register = reg and from deviceId = node

  private:
    void sendPower(void);
#if defined ( GTN_USE_HARDWARESERIAL )
    HardwareSerial& gtnSer;
#else
    SoftwareSerial& gtnSer;
#endif

#if defined ( GTN_USE_HARDWARESERIAL )
    int _config = GTN_UART_CONFIG;
  #if defined ( ESP8266 )
    bool _swapuart = SWAPHWSERIAL;
  #elif defined ( ESP32 )
    int8_t _rx_pin = -1;
    int8_t _tx_pin = -1;
  #endif
#else
  #if defined ( ESP8266 ) || defined ( ESP32 )
    int _config = GTN_UART_CONFIG;
  #endif
    int8_t _rx_pin = -1;
    int8_t _tx_pin = -1; 
#endif
    long _baud = GTN_UART_BAUD;
    uint16_t _power;
    unsigned long _last;

};
#endif // GTN_h
