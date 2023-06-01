int INA = 9;  
int INB = 8;

void setup() { 
  pinMode(INA,OUTPUT); 
  pinMode(INB,OUTPUT); 
} 

void loop() { 
  analogWrite(9, 255);
  analogWrite(10, 0);
  delay(3000);

  analogWrite(9, 100);
  analogWrite(10, 0);
  delay(3000);

  analogWrite(9, 0);
  analogWrite(10, 0);
  delay(3000);

} 