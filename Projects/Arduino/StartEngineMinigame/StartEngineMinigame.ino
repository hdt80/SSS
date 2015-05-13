int led1 = 8;
int led2 = 9;
int led3 = 10;
int led4 = 11;

int switch1 = 0;
int switch2 = 1;
int switch3 = 2;
int switch4 = 3;

int mode = 0;
int rled = 0;

int led1chosen = 0;
int led2chosen = 0;
int led3chosen = 0;
int led4chosen = 0;

void setup() {
  randomSeed(analogRead(5));
  
  // put your setup code here, to run once:
  pinMode(led1,OUTPUT);
  pinMode(led2,OUTPUT);
  pinMode(led3,OUTPUT);
  pinMode(led4,OUTPUT);
  
  //pinMode(switch1,INPUT); //dangit
  
  Serial.begin(9600);
  // digitalWrite(13,HIGH);
}

void loop() {
  if (mode == 0){
    digitalWrite(led1,HIGH);
    digitalWrite(led2,HIGH);
    digitalWrite(led3,HIGH);
    digitalWrite(led4,HIGH);
    
    // select a random LED to light up
    
    rled = random(8, 11);
    
    mode = 1;
  }

  if (analogRead(switch1) > 1020  && rled == led1){
    Serial.println("LED 1 I CHOSE YOU!!!!");
    led1chosen = led1;
    while (rled == led1 && (rled == led1chosen || rled || led2chosen && rled || led3chosen || rled == led4chosen)) { rled = random(8, 11); }
  }
  if (analogRead(switch2) > 1020  && rled == led2){
    led2chosen = led2;
    while (rled == led2 && (rled == led1chosen || rled || led2chosen && rled || led3chosen || rled == led4chosen)) { rled = random(8, 11); }
  }
  if (analogRead(switch3) > 1020  && rled == led3){
    led3chosen = led3;
    while (rled == led3 && (rled == led1chosen || rled || led2chosen && rled || led3chosen || rled == led4chosen)) { rled = random(8, 11); }
  }
  if (analogRead(switch4) > 1020  && rled == led4){
    led4chosen = led4;
    while (rled == led4 && (rled == led1chosen || rled || led2chosen && rled || led3chosen || rled == led4chosen)) { rled = random(8, 11); }
  }
  
  Serial.println(led1chosen);
   Serial.println(led2chosen);
    Serial.println(led3chosen);
     Serial.println(led4chosen);
  
  if (mode == 1){
    digitalWrite(rled,HIGH);
    delay(500);
    digitalWrite(rled,LOW);
    delay(500);
  }
  
}
