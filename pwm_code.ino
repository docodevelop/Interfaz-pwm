int pinLed = 9;

//A buffer to store the incoming serial data
String commandBuffer = "";
String valueBuffer = "";
int appendStatus = 0;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(pinLed, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  readBuffer();
}

void readBuffer() {
  if (Serial.available()) {
    char character = Serial.read();
    if (character == '&') {
      executeCommand();
      appendStatus = 1;
    } else if (character == '-') {
      appendStatus = 2;
    } else {
      append2Buffer(character);
    }
  }
}

void  append2Buffer(char val2append) {
  if (appendStatus == 1) {
    commandBuffer += val2append;
  } else if (appendStatus == 2) {
    valueBuffer += val2append;
  }
}

void executeCommand() {
  int command = commandBuffer.toInt();
  int value = valueBuffer.toInt();
  executeCommandImpl(command, value);
  commandBuffer = "";
  valueBuffer = "";
}

void executeCommandImpl(int command, int value) {
  switch (command) {
    case 2:
      setLedVal(value);
      break;
  }
}

void setLedVal(int stat) {
  delay(100);
  analogWrite(pinLed, stat);
  Serial.print("pwm-");
  Serial.print(stat);
  Serial.print("&");
}
