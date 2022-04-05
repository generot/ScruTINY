#include "secret.h" 

#include <WiFiEsp.h>
#include <SoftwareSerial.h>

#define DEFAULT_BAUD_RATE 9600
#define BEEPS 3

#define SERVER_ROUTE "scrutiny-online.herokuapp.com"
#define PORT 80

#define __SCR_DEBUG__

#ifdef __SCR_DEBUG__
# define PRINT_DEBUG(x) Serial.println((x))
#else
# define PRINT_DEBUG(x) ;
#endif

enum pin_config {
  USOUND_ECHO_PIN = 6,
  USOUND_TRIG_PIN = 7,
  SND_SENSOR_PIN = 5,
  WIFI_RX_PIN = 9,
  WIFI_TX_PIN = 8,
  BUZZER_PIN = 3
};

///VARIABLES///
SoftwareSerial wifi_module(WIFI_RX_PIN, WIFI_TX_PIN);
WiFiEspClient server_conn;

const char net_ssid[] PROGMEM = NET_SSID;
const char net_pass[] PROGMEM = NET_PASS;
const char scr_server[] PROGMEM = SERVER_ROUTE;

unsigned long last_detection = 0;

unsigned long mot_duration = -1;
float trig_dist = -1;

int net_status = WL_IDLE_STATUS;
int server_conn_status = 0;
int snd_res = 0;

bool motion_res = false;
bool begin_awaiting = false;
bool is_wave_back = false;
///VARIABLES///

void setup() {
  Serial.begin(DEFAULT_BAUD_RATE);
  wifi_module.begin(DEFAULT_BAUD_RATE);

  WiFi.init(&wifi_module);

  if(net_status != WL_CONNECTED) {
    net_status = WiFi.begin(net_ssid, net_pass);
  }

  if(net_status == WL_CONNECTED) {
    PRINT_DEBUG("Connection established...");
    
    PRINT_DEBUG(WiFi.SSID());
    PRINT_DEBUG(WiFi.localIP());
  }
  
  pinMode(BUZZER_PIN, OUTPUT);

  //Uses pins 4 and 2
  motion_setup();

  //Uses pin 5;
  //sound_setup();
}

int post_request(const char* server_url, String route, String data) {
  if(net_status != WL_CONNECTED) {
    return 1;
  }
  
  server_conn.stop();
  
  server_conn_status = server_conn.connect(server_url, 80);
  
  if(server_conn_status) {
    //POST request form
    server_conn.print("POST " + route + " HTTP/1.0\r\n");
    server_conn.print("Host: " + String(server_url) + "\r\n");
    server_conn.print("Connection: close\r\n");
    server_conn.print("Content-Length: " + String(data.length()) + "\r\n");
    server_conn.print("\r\n");
    server_conn.print(data);
    server_conn.print("\r\n\r\n");
  } else {
#ifdef __SCR_DEBUG__
    Serial.println("Connection could not be established...");
#endif
    return -1;
  }

  return 0;
}

void action(float motion_trig_dist) {
  PRINT_DEBUG(">>> Called action() <<<");
  PRINT_DEBUG("Dist: " + String(motion_trig_dist));

  String msg = "Disturbance detected: " + String(motion_trig_dist) + " cm away from sensor";

  for(int i = 0; i < BEEPS; i++) {
    tone(BUZZER_PIN, 1440);
    delay(300);
    noTone(BUZZER_PIN);
  }

  post_request(scr_server, "/postData", msg);
  last_detection = millis();
}


void loop() {
  float trig_dist2 = -1;
  
  motion_res = check_for_motion(&trig_dist2);

  if(motion_res && millis() - last_detection > 500) {
    PRINT_DEBUG("Time: " + String(millis() - last_detection));
    
    action(trig_dist2);
  }
}
