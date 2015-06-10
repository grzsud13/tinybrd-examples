void pulse(byte led, unsigned int time=1000, byte cnt = 1) {
  for (byte i=0;i++;i<cnt) {
    digitalWrite(led,HIGH);
    delay(time/2);
    digitalWrite(led,LOW);
    delay(time/2);
  }
}

