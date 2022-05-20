unsigned int LoopCounter;

template <typename T>
Print& operator<<(Print& printer, T value)
{
    printer.print(value);
    return printer;
}

void setup() {
  Serial.begin(9600);
  DDRD = B11111111;
}

void loop() {
  LoopCounter++;
  Serial << "Starting loop #" << LoopCounter << '\n';
  PORTD = B11110000; // digital 4~7 HIGH, digital 3~0 LOW
  delay(10000);
  PORTD = B00001111; // digital 4~7 LOW, digital 3~0 HIGH
  delay(10000);

}
