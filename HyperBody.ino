const int HR_RX = 10;
const int VIBRATION = 9;
const int BUZZ = 12;
const int LED = 13;
byte oldSample, sample;
long pulseTime, lastPulseTime;
int BPM;
int lowThreashold = 100;
int highThreashold = 120;


volatile int diff1 = 0;
volatile int diff2 = 0;
volatile int diff3 = 0;
volatile int diff4 = 0;
volatile int diff5 = 0;
volatile int diff6 = 0;
volatile int diff7 = 0;
volatile int diff8 = 0;
volatile int diff9 = 0;
volatile int diff10 = 0;

void setup() {
  Serial.begin(9600);

  pinMode (HR_RX, INPUT);  //Signal pin to input
  pinMode(VIBRATION, OUTPUT); 
  pinMode(BUZZ,OUTPUT);
  pinMode(LED,OUTPUT);

}

void loop() {
   
  sample = digitalRead(HR_RX);  //Store signal output 

  if (sample && (oldSample != sample)) {
    //Serial.println("Beat");
    Serial.println("Beat:");
    Serial.println(BPM);
    HRpulse();
   
  }

  if(BPM >= lowThreashold && BPM < highThreashold){
      enableMotorTrigger();
      disableBuzzTrigger();
    }else if(BPM >= highThreashold){
      enableBuzzTrigger();
      enableMotorTrigger();
    }else if(BPM <lowThreashold){
      disableMotorTrigger();
      disableBuzzTrigger();
    }
    delay(10);
  oldSample = sample;       
}


void HRpulse()
{
  pulseTime = millis();
  rollBuffer();
  diff1 = pulseTime - lastPulseTime;
  if (diff10 != 0) {
    BPM = 60000 / ((diff1 + diff2 + diff3 + diff4 + diff5 + diff6 + diff7 + diff8 + diff9 + diff10)/10);
  }
  lastPulseTime = pulseTime;
}

void enableMotorTrigger(){
  digitalWrite(VIBRATION,1);
}

void enableBuzzTrigger(){
   //CircuitPlayground.playTone(1000,100);
   tone(BUZZ,1000);
}

void disableMotorTrigger(){
  digitalWrite(VIBRATION,0);
}

void disableBuzzTrigger(){
  noTone(BUZZ);
}

void rollBuffer()
{
  diff10 = diff9;
  diff9 = diff8;
  diff8 = diff7;
  diff7 = diff6;
  diff6 = diff5;
  diff5 = diff4;
  diff4 = diff3;
  diff3 = diff2;
  diff2 = diff1;
  diff1 = 0;
}
