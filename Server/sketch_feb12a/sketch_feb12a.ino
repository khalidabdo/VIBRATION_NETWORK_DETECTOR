#define NUMBER_OF_NODES (127)
#define MESSAGE_FIELDS_NUMBER (12)

char BUFFER[MESSAGE_FIELDS_NUMBER] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};

void setup() {
  // put your setup code here, to run once:
  // initialize both serial ports:

  Serial.begin(9600);

  Serial2.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:

    //for(int MESSAGE_FIELD = 0; MESSAGE_FIELD <= NUMBER_OF_NODES; MESSAGE_FIELD++)
    //{
        Serial2.write(0x3F);
        Serial.write(0x3F);
        Serial2.setTimeout(1000);
        Serial2.readBytes(BUFFER, MESSAGE_FIELDS_NUMBER);
        
        Serial.write(BUFFER,MESSAGE_FIELDS_NUMBER);
    //}
    delay(1000); 
}
