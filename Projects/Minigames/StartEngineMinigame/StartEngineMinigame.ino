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

int ledOrder[] = {
  -1,
  -1,
  -1,
  -1
};

void setup() {
  randomSeed(analogRead(5));

  // put your setup code here, to run once:
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);

  //pinMode(switch1,INPUT); //dangit

  Serial.begin(9600);
  // Randomize the led

  rled = random(8, 12);
  for (int i = 0; i < 4; i++) {
    while ( find_index(ledOrder, 3, rled) == true ) {
      rled = random(8, 12);
    }
    Serial.println("Setting array " + String(i) + " to " + String(rled));
    ledOrder[i] = rled;
  }

  Serial.println("Random pattern chosen!");
  // digitalWrite(13,HIGH);
}

boolean find_index(int a[], int maxn, int value)
{
  int i;

  for (i = 0; i < maxn; i++)
  {
    if (a[i] == value)
    {
      return (true);
    }
  }
  Serial.println(String(value) + " not found");
  return (false);

}

void nextmode() {
  mode++;
  rled = ledOrder[mode - 1];
}

void loop() {
  if (mode == 0) {
    digitalWrite(led1, HIGH);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, HIGH);
    digitalWrite(led4, HIGH);

    // select a random LED to light up
    mode = 1;
    rled = ledOrder[mode - 1];


  }

  if (analogRead(switch1) > 1020  && rled == led1) {
    nextmode();
  }
  if (analogRead(switch2) > 1020  && rled == led2) {
    nextmode();
  }
  if (analogRead(switch3) > 1020  && rled == led3) {
    nextmode();
  }
  if (analogRead(switch4) > 1020  && rled == led4) {
    nextmode();
  }


  if (mode >= 1 && mode <= 4) {
    digitalWrite(rled, HIGH);
    delay(500);
    digitalWrite(rled, LOW);
    delay(500);
  }

  if (mode == 5) {
    Serial.println("SWITCH_MINIGAME_COMPLETE");
    for (int i = 8; i < 12; i++) {
      digitalWrite(i, HIGH);
    }
    delay(400);
    for (int i = 8; i < 12; i++) {
      digitalWrite(i, LOW);
    }
    delay(400);
  }

}

