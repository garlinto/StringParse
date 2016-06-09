// program name
const char * programVersion = "StringParse.ino";

// climate data prefixes
const char TO[] = "TO"; // temperature outside
const char TA[] = "TA"; // temperature attic
const char TG[] = "TG"; // temperature garage
const char PO[] = "PO"; // pressure outside
const char RH[] = "RH"; // relative humidity

String climate_outside_t = "Outside temp: ";


// garage door data prefixes
const char GD_STATUS[] = "STATUS";
const char GD_HESA_POS[] = "POS";
const char GD_HESB_POS[] = "SID";

// string delimiters
const char CLIMATE_DELIMITER[] = "#";
const char GD_DELIMITER[] = "&";
const char PARAM_SEPERATOR[] = ",";
const char VALUE_SEPERATOR[] = ":";

char* climate_str = "#TO:97.43,TA:102:23,TG:78.333,PO:1002:223,RH:88.43#";
char* gdstatus_str = "&STATUS:-1&";
char* gdsensor_str = "&SID:A,POS:18&";

/**
 * SETUP
 */
void setup() {
  Serial.begin(115200);
  while (!Serial);

  Serial.print("Running program: ");
  Serial.println(programVersion);
  Serial.println("Ready!");
}

void loop() {
  
  Serial.print("Test string: ");
  Serial.println(climate_str);
  
  char* found_str = strtok(climate_str, CLIMATE_DELIMITER);
  
  // string found, proceed
  if (0 < strlen(found_str)) {
    Serial.print("Found string: ");
    Serial.println(found_str);
    char* ptr;
    ptr = strtok(found_str, PARAM_SEPERATOR);
    while (NULL != ptr) {
      Serial.println(ptr);
      ptr = strtok(NULL, PARAM_SEPERATOR);
    }
  }
  
  Serial.println("Parsing complete.");
  uint32_t t = 0;
  while (1) {
    Serial.print(t);
    delay(1000);
    t++;
  }
}

