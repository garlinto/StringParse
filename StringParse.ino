#include <LiquidCrystal_I2C.h>
#include <XBee.h>

XBee xbee = XBee();
ZBRxResponse rx = ZBRxResponse();
#define HWSERIAL Serial1

// string delimiters
String CLIMATE_DELIMITER = "#";
String GD_DELIMITER = "&";
String PARAM_SEPERATOR = ",";
String VALUE_SEPERATOR = ":";

String climate_str, gd_str;
uint8_t* _data;

LiquidCrystal_I2C  lcd(0x3f, 16, 2);

/**
 * Parse received data as strings.
 * Uses delimiters to find the relevant string
 *  within the data.
 * 
 * @param   String  str
 * @return  void
 */
void parseString(String str) {
  
  if ( str.startsWith(CLIMATE_DELIMITER) ) {
    if (-1 != str.indexOf(CLIMATE_DELIMITER, 1)) {
      climate_str = str.substring(1, str.indexOf(CLIMATE_DELIMITER, 1) );
      Serial.println(climate_str); 
      return;
    }
  }

  if (str.startsWith(GD_DELIMITER)) {
    if (-1 != str.indexOf(GD_DELIMITER, 1)) {
      gd_str = str.substring(1, str.indexOf(GD_DELIMITER, 1));
      Serial.println(gd_str);
      return;
    }
  }

  // string is unknown or badly formatted
  Serial.println("Unidentified data.\n");
  return;
}

/**
 * Capture incoming xbee data
 * Called every loop() tick
 *
 * @param   void
 * @return  void
 */
void captureZbRXResponse() {
  xbee.readPacket();
  if (xbee.getResponse().isAvailable()) {
    if (xbee.getResponse().getApiId() == ZB_RX_RESPONSE) {
      xbee.getResponse().getZBRxResponse(rx);

      _data = rx.getData();
      parseString(String((char*)_data));

      // reset rx_data array
      memset(_data, 0, rx.getDataLength());
    }
  }
}

/**
 * SETUP
 */
void setup() {
  Serial.begin(9600);
  while (!Serial && (millis() <= 5000));

  HWSERIAL.begin(9600);
  xbee.setSerial(HWSERIAL);

  Serial.println("Running: StringParse.ino\nInitializing LCD display");

  // initialize LCD passing LCD characters per line and number of lines (16 x 2)
  lcd.begin();
  lcd.backlight();
  lcd.print("StringParse.ino");

  Serial.println("Ready!");
}

/*
 * LOOP
 */
void loop() {
  
  // check for xbee data
  captureZbRXResponse();

}
