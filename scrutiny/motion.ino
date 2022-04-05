////VARIABLES////
unsigned long motion_sig_dur = 0;

float motion_prev_dist = -1;
float motion_dist = 0;
////VARIABLES////

unsigned long to_milis(unsigned long micro_s) {
  return micro_s / 1000;
}

float distance(unsigned long sig_duration) {
  if(sig_duration == -1)
    return -1;
  
  float speed_of_sound = 0.0343; // cm / microsec
  float dist = speed_of_sound * sig_duration;

  return dist / 2;
}

void motion_send_wave() {
  digitalWrite(USOUND_TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(USOUND_TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(USOUND_TRIG_PIN, LOW);
}

bool motion_compare(unsigned long curr_dur, float *dist) {
  motion_prev_dist = motion_dist;
  motion_dist = distance(curr_dur);

  *dist = motion_dist;

  if(motion_prev_dist - motion_dist > 10) {
    return true;
  }

  return false;
}

//Unused function - imame asinhronen algoritum vmesto toja bokluk.
//Nvm, pak ja polzvame.
bool check_for_motion(float *dist) {
  digitalWrite(USOUND_TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(USOUND_TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(USOUND_TRIG_PIN, LOW);

  motion_sig_dur = pulseIn(USOUND_ECHO_PIN, HIGH);

  motion_prev_dist = motion_dist;
  motion_dist = distance(motion_sig_dur);

//  Serial.println("Prev: " + String(motion_prev_dist));
//  Serial.println("Curr: " + String(motion_dist));

  if(dist) {
    *dist = motion_dist;
  }

  if(motion_prev_dist - motion_dist > 10) {
    return true;
  }

  return false;
}

void motion_setup() {
  pinMode(USOUND_ECHO_PIN, INPUT);
  pinMode(USOUND_TRIG_PIN, OUTPUT);

  //check_for_motion(NULL);
}
