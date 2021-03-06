#define SAMPLING_FREQUENCY 5 // in Hz
#define T1 1 // in s
#define T2 60 // in s

int SWITCH_PIN = 2;
int TRIGGER_PIN = 3;
int BATTERY_PIN = 3;
int RESISTOR_PIN = 1;
int valB, valR;
int count;
double res_voltage, bat_voltage;
const double CORRECTION_FACTOR = 2;//1.80806;

void setup() {
  // put your setup code here, to run once:
  pinMode(SWITCH_PIN, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(TRIGGER_PIN, OUTPUT);
  Serial.begin(9600);
}


void loop() {
  // put your main code here, to run repeatedly:
  if(digitalRead(SWITCH_PIN) == HIGH) {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(200);
    digitalWrite(LED_BUILTIN, LOW);    

    digitalWrite(TRIGGER_PIN, HIGH);
    delay(200);
    digitalWrite(TRIGGER_PIN, LOW);    

    Serial.println("START");

    for (int i = 0; i < T1 * SAMPLING_FREQUENCY; i++) {
      valB = analogRead(BATTERY_PIN);
      valR = analogRead(RESISTOR_PIN);
      bat_voltage = valB * .0049; //((double)valB / (double)1023) * 5.0; 
      res_voltage = valR * .0049; //((double)valR / (double)1023) * 5.0; 
      double current = (bat_voltage - res_voltage) * CORRECTION_FACTOR;
      Serial.println(valB);//(bat_voltage * CORRECTION_FACTOR);
      Serial.println(valR);//((current) / .527778);
      delay(1000 / SAMPLING_FREQUENCY);
    }

    for (int i = 0; i < T2 * SAMPLING_FREQUENCY; i++) {
      valB = analogRead(BATTERY_PIN);
      valR = analogRead(RESISTOR_PIN);
      bat_voltage = valB * .0049; //((double)valB / (double)1023) * 5.0;
      res_voltage = valR * .0049; //((double)valR / (double)1023) * 5.0;
      double current = (res_voltage - bat_voltage) * CORRECTION_FACTOR;
      //Serial.println(bat_voltage * CORRECTION_FACTOR);
      //Serial.println((current) / .527778);
      Serial.println(valB);
      Serial.println(valR);
      delay(1000 / SAMPLING_FREQUENCY);
    }
        Serial.println("DONE");

  }
}
