void pulse(byte led, unsigned int time=1000, byte cnt = 1) {
  for (byte i=0;i++;i<cnt) {
    digitalWrite(led,HIGH);
    delay(time/2);
    digitalWrite(led,LOW);
    delay(time/2);
  }
}

void check_for_errors(){
    if (!data.status){
    pulse(LED,500,20);
  }
}
