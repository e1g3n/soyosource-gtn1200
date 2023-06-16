
/*
*  GTN USER CONFIG:
*/

/*
*  define or undefine USE_HARDWARESERIAL (uncomment only one or none)
*/
//#undef GTN_USE_HARDWARESERIAL
//#define GTN_USE_HARDWARESERIAL

/*
*  define user baudrate
*/
//#define GTN_UART_BAUD                       4800

/*
*  define user GTN_RX_PIN and GTN_TX_PIN for esp/avr Software Serial option
*  or ESP32 with Hardware Serial if default core pins are not suitable
*/
#if defined ( GTN_USE_HARDWARESERIAL )
  #if defined ( ESP32 )
    #define GTN_RX_PIN                        13
    #define GTN_TX_PIN                        15
  #endif
#else
  #if defined ( ESP8266 ) || defined ( ESP32 )
    #define GTN_RX_PIN                        18
    #define GTN_TX_PIN                        19
  #else
    #define GTN_RX_PIN                        10
    #define GTN_TX_PIN                        11
  #endif
#endif

#if defined ( GTN_USE_HARDWARESERIAL )

  /*
  *  define user GTN_UART_CONFIG for hardware serial
  */
  //#define GTN_UART_CONFIG                   SERIAL_8N1

  /*
  *  define user SWAPHWSERIAL, if true(1) then swap uart pins from 3/1 to 13/15 (only ESP8266)
  */
  //#define SWAPHWSERIAL                      0

#else

  /*
  *  define user GTN_UART_CONFIG for software serial
  */
  //#define GTN_UART_CONFIG                   SWSERIAL_8N1

#endif
