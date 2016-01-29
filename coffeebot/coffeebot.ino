int photoresistor = A0;
int power = A5;
int analogvalue;
bool brewStarted;

void setup() {
    pinMode(photoresistor,INPUT);
    pinMode(power,OUTPUT);
    digitalWrite(power,HIGH);
    brewStarted = false;
    Spark.variable("analogvalue", &analogvalue, INT);
}

void loop() {
    analogvalue = analogRead(photoresistor);
    if(analogvalue < 100 && brewStarted) {
      delay(3000);
      if(analogRead(photoresistor) < 100 ){
        Spark.publish("slack-push", String("Kaffet är klart!"));
        brewStarted = false;
      }

    } else if (analogvalue >= 100 && !brewStarted){
      delay(3000);
      if(analogRead(photoresistor) >= 100){
        Spark.publish("slack-push", String("Kaffet är nu under bryggning!"));
        brewStarted = true;
      }

    }
}
