#define p1 30
#define p2 31 
#define p3 32 
#define p4 33 

#define v1 34 
#define v2 35 
#define v3 36 
#define v4 37 
#define v5 38 
#define v6 39
#define v7 40
#define v8 41

#define buz 10

const int pH_Sensor_Pin = A0;

int count = 0;

const int waterLevelPin1 = 3;
const int waterLevelPin2 = 4;
const int waterLevelPin3 = 5;
const int waterLevelPin4 = 6;
const int waterLevelPin5 = 2;

void setup() {
  Serial.begin(9600);

  pinMode(p1, OUTPUT); 
  pinMode(p2, OUTPUT);
  pinMode(p3, OUTPUT);
  pinMode(p4, OUTPUT);
  pinMode(v1, OUTPUT);
  pinMode(v2, OUTPUT);
  pinMode(v3, OUTPUT);
  pinMode(v4, OUTPUT);
  pinMode(v5, OUTPUT);
  pinMode(v6, OUTPUT);
  pinMode(v7, OUTPUT); 
  pinMode(v8, OUTPUT);
  pinMode(buz, OUTPUT);    

  digitalWrite(p1, HIGH);   
  digitalWrite(p2, HIGH);
  digitalWrite(p3, HIGH);
  digitalWrite(p4, HIGH);
  digitalWrite(v1, HIGH);
  digitalWrite(v2, HIGH);
  digitalWrite(v3, HIGH);
  digitalWrite(v4, HIGH);
  digitalWrite(v5, HIGH);
  digitalWrite(v6, HIGH);
  digitalWrite(v7, HIGH);
  digitalWrite(v8, HIGH);
  digitalWrite(buz, HIGH);

  pinMode(waterLevelPin1, INPUT_PULLUP);
  pinMode(waterLevelPin2, INPUT_PULLUP);
  pinMode(waterLevelPin3, INPUT_PULLUP);
  pinMode(waterLevelPin4, INPUT_PULLUP);  
  pinMode(waterLevelPin5, INPUT_PULLUP); 
}

void loop() {

  int pHValue = analogRead(pH_Sensor_Pin);
  float voltage = pHValue * (5.0 / 1024.0);
  float pH = -5.70 * voltage + 21.34;

  int tandon1 = digitalRead(waterLevelPin1);
  int tandon2 = digitalRead(waterLevelPin2);
  int tandon3 = digitalRead(waterLevelPin3);
  int tandon4 = digitalRead(waterLevelPin4);
  int tandon5 = digitalRead(waterLevelPin5);   

  Serial.print("pH Value: ");
  Serial.println(pH);

  Serial.print("tandon5:");
  Serial.println(tandon5); 

  delay(1000);

  if (Serial.available() > 0) {
    char command = Serial.read();
    if (command == '1') {
      count = 0;
    }
    if (command == '0'){
      count = 16;
    }
    if (command == '2'){
      count = 12;
    }
    if (command == '3'){
      count = 15;
    }
  }

    if(count == 0){
      digitalWrite(v8, LOW);
      if(tandon1 == HIGH){
        count = 1;
      }
    }

    if(count == 1){
      digitalWrite(v8, HIGH);
      //kimia
      digitalWrite(v7, LOW);
      delay(5000);
      digitalWrite(v7, HIGH);
      digitalWrite(v6, LOW);
      delay(500000);
      digitalWrite(v6, HIGH);
      count = 2;
    }

    if(count == 2){
      digitalWrite(p2, LOW);
      if(tandon3 == HIGH){
        count = 3;
      }
    }

    if(count == 3){
      digitalWrite(p2, HIGH);
      count = 4;
    }

    if(count == 4){
      digitalWrite(p3, LOW);      
        if(tandon4 == HIGH){
        count = 5;        
      }
    }

    if(count == 5){
      digitalWrite(p3, HIGH);
      digitalWrite(p2, LOW);
      if(tandon3 == HIGH){
        count = 6;
      }
    }

    if(count == 6){
      digitalWrite(p2, HIGH);
      digitalWrite(p4, LOW);
      if(tandon2 == HIGH){
        count = 7;
      }
    }

    if(count == 7){
      digitalWrite(p4, HIGH);
      count = 8;
    } 

    if(count == 8){
      digitalWrite(p3, LOW);
      if(tandon4 == HIGH){
        count = 9; 
      }
    }

    if(count == 9){
      digitalWrite(p3, HIGH);
      if(pH > 7.00){
        digitalWrite(p1, LOW);
        digitalWrite(v2, LOW);
        digitalWrite(v5, LOW);
        if(tandon3 == HIGH){
          count = 10;
        }
      }
      if(pH < 7.00){
        count = 11;
      }
    }

    if(count == 10){
      digitalWrite(p1, HIGH);
      digitalWrite(v2, HIGH);
      digitalWrite(v5, HIGH);
      digitalWrite(p4, LOW);
      if(tandon2 == HIGH){
        count = 7;
      }
    }

    if(count == 11){
      digitalWrite(buz, LOW);
      delay(5000);
     }
     
      if(count == 12){
        digitalWrite(buz, HIGH);
        digitalWrite(p4, LOW);
        digitalWrite(p1, LOW);
        digitalWrite(v1, LOW);
        digitalWrite(v3, LOW);
        if(tandon1 == HIGH){
          count = 13;
        }
      }

    if(count == 13){
      digitalWrite(p4, HIGH);
      digitalWrite(p1, HIGH);
      digitalWrite(v1, HIGH);
      digitalWrite(v3, HIGH);
      count = 1;
    }
  
  if(count == 15){
    digitalWrite(p4, LOW);
    digitalWrite(p1, LOW);
    digitalWrite(v1, LOW);
    digitalWrite(v3, LOW);
  }
                    
  if(count == 16){
      digitalWrite(p1, HIGH);
      digitalWrite(p2, HIGH);
      digitalWrite(p3, HIGH);
      digitalWrite(p4, HIGH);
      digitalWrite(v1, HIGH);
      digitalWrite(v2, HIGH);
      digitalWrite(v3, HIGH);
      digitalWrite(v4, HIGH);
      digitalWrite(v5, HIGH);
      digitalWrite(v6, HIGH);
      digitalWrite(v7, HIGH);
      digitalWrite(v8, HIGH);
  }
}
