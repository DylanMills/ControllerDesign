// int RedButton1 = 0;

int Vert = 0;
int Hori = 0;
int temp = 0;

#define R1 2
#define R2 3
#define G1 4
#define G2 5
#define B1 6
#define B2 7
#define Y1 8
#define Y2 9
#define HRZ A0
#define VRT A1
String names[] {"0","1","RED1","RED2","GREEN1","GREEN2","BLUE1","BLUE2","YELLOW1","YELLOW2"};

void setup() {
  // put your setup code here, to run once:
  Serial.begin(5200);
  //Axis
  pinMode(HRZ, INPUT);
  pinMode(VRT, INPUT);

  //RED PUSH BUTTONS
  pinMode(R1, INPUT);
  pinMode(R2, INPUT);

  //GREEN BUTTONS
  pinMode(G1, INPUT);
  pinMode(G2, INPUT);
  //BLUE BUTTONS
  pinMode(B1, INPUT);
  pinMode(B2, INPUT);  
  
  //YELLOW BUTTONS
  pinMode(Y1, INPUT);
  pinMode(Y2, INPUT);
  //OUTPUTS

  pinMode(10, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
}

int ReadAxis(int axis) {
  // int n = analogRead(axis)/506-1;
  // n=n/506-1;
  return analogRead(axis) / 506 - 1;
}

void loop() {
  // put your main code here, to run repeatedly:
  // int value = analogRead(HRZ);

  // // int inverted = invertAxis(value);  // using 0-1023
  // int inverted = invertAxis(value, AnalogMin, AnalogMax);


  //  delay(100);
  // if (digitalRead(2) == LOW) {
  //   digitalWrite(4, HIGH);
  //     Serial.println(digitalRead(3)==!0);
  // } else {
  //   digitalWrite(4, LOW);
  // }
  for(int i =2;i <10;i++){
    if(digitalRead(i)!=0){
Serial.println(names[i]);
    }
  }

  temp = Vert;
  Vert = ReadAxis(VRT);
  if (Vert != temp) {

    Serial.print("VERTICAL: ");
    Serial.println(Vert);
  }
  //  delay(20);
  temp = Hori;
  Hori = ReadAxis(HRZ);
  if (Hori != temp) {

    Serial.print("HORIZONTAL: ");
    Serial.println(Hori);
  }
  // delay(200);
  // Serial.println("report");
  // delay(100);
  // if(digitalRead(8))
  // if(Vert <=100){
  //   digitalWrite(13,HIGH);
  //   digitalWrite(12, LOW);
  // }
  // else if(Vert >1000){
  //     digitalWrite(12,HIGH);
  //   digitalWrite(13, LOW);
  // }
  // if ((analogRead(A0)-analogRead(A1))!=0){
  // Serial.print("HORIZONTAL: ");
  // Serial.print(analogRead(A0));
  // Serial.print(" | VERTICAL: ");
  // Serial.println(analogRead(A1));
  // }
  // Serial.println(digitalRead(Vert));
  // analogRead()
  delay(200);
}
