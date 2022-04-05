//Mozhehme da mineme i bez toja fajl.

void sound_setup() {
  pinMode(SND_SENSOR_PIN, INPUT);
}

int check_abnormal_sound() {
  return digitalRead(SND_SENSOR_PIN);
}
