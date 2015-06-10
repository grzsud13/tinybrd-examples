#define PHOTO_SENSOR  A0
#define PWR_PIN 0

void light_setup(){
  pinMode(PWR_PIN,OUTPUT);
  digitalWrite(PWR_PIN,LOW);
}

int light_read() {
  int ret;
  digitalWrite(PWR_PIN,HIGH);
  delay(1);
  ret = analogRead(PHOTO_SENSOR);
  digitalWrite(PWR_PIN,LOW);
  return ret;
}

