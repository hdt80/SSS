//FYI IT doesn't work yet

byte inIDS[] = {
 0,
 1,
 2 
};

byte outIDS[] = {
 8,
 9,
 10 
};

byte connectIDS[] = {
 8,
 9,
 10 
};

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
   String toPrint = "Wired " + String(inIDS[ran - 1]) + " to " + String(randomInt);
   Serial.println(toPrint);
  } 
}

boolean checkWire(byte wire){
    for(int i = 0; i < 3; i ++){
       analogWrite(outIDS[i], 0); 
    }
    delay(200);
    analogWrite(outIDS[wire], 1023);
    delay(200);
          Serial.println(analogRead(connectIDS[wire]));
    if(analogRead(connectIDS[wire]) > 1000){
       return true;
    }
    return false;
}

void setup(){
  Serial.begin(9600);
  for(int i = 0; i < 3; i ++){
       pinMode(outIDS[i], OUTPUT);
    }
    
  //rewire();
  
}

void loop(){
  if(checkWire(0)){
    Serial.println("Wire 0 is working!");
  }
  if(checkWire(1)){
    Serial.println("Wire 1 is working!");
  }
  if(checkWire(2)){
    Serial.println("Wire 2 is working!");
  }
}
