//The output pins. 
byte outIDS[] = {
 2,
 3,
 4 
};

//The pins that light up when the respective wire is correctly wired (outIDS[0] wired correctly lights up lightsIDS[0]);
byte lightIDS[] = {
 5,
 6,
 7 
};

//The pins that wires will be plugged into.
byte inIDS[] = {
 8,
 10,
 12 
};

//Placeholder array, filled when randomizing which wire each pin is connected to.
byte connectIDS[] = {
 8,
 9,
 10 
};

//Magically randomizes the pin assignments.
void rewire(){
 randomSeed(analogRead(0));
  randomSeed(analogRead(0));
  
  boolean usedUP[] = {
    false,
    false,
    false 
  };
  byte ran = 0;
  
  while(!(usedUP[0] && usedUP[1] && usedUP[2])){
   byte randomInt = random(3);
   if(usedUP[randomInt]) continue;
   usedUP[randomInt] = true;
   connectIDS[randomInt] = inIDS[ran];
   ++ran; 
   String toPrint = "Wired " + String(inIDS[ran - 1]) + " to " + String(outIDS[randomInt]);
  } 
}

boolean checkWire(byte wire){
    for(int i = 0; i < 3; i ++){
       digitalWrite(outIDS[i], LOW); 
    }
    delay(200);
    digitalWrite(outIDS[wire], HIGH);
    delay(200);
    if(digitalRead(connectIDS[wire]) == HIGH){
       return true;
    }
    return false;
}

void setup(){
  Serial.begin(9600);
  Serial.write(0);
  for(int i = 0; i < 3; i ++){
       pinMode(outIDS[i], OUTPUT);
       pinMode(lightIDS[i], OUTPUT);
  }
   for(int i = 0; i < 3; i ++){
       pinMode(inIDS[i], INPUT);
  }
    
  rewire();
  
}

void loop(){
  if(checkWire(0) && checkWire(1) && checkWire(2)){
    Serial.write(1);
  }
  
  if(checkWire(0)){
    digitalWrite(lightIDS[0], HIGH);
  } else {
    digitalWrite(lightIDS[0], LOW);
  }
  if(checkWire(1)){
    digitalWrite(lightIDS[1], HIGH);
  } else {
     digitalWrite(lightIDS[1], LOW); 
  }
  if(checkWire(2)){
    digitalWrite(lightIDS[2], HIGH);
  } else {
     digitalWrite(lightIDS[2], LOW); 
  }
}
