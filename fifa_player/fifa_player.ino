const int trigger1 = 7; //Trigger pin of 1st Sesnor
const int echo1 = 6; //Echo pin of 1st Sesnor
const int trigger2 = 3;
const int echo2 = 2;
const int trigger3 = 3; //Change
const int echo3 = 2; //Change
const int ledL = 10;
const int ledR = 9;
const int ledM = 9; //Change
const int grd1 = 11;
const int grd2 = 12;
const int stMove = 15; //Change
const int maxDistL = 35; //Change
const int maxDistR = 35; //Change
const int passDist = 15; //Change
int distL,distR, distM;
long time_taken;

void setup() {
  Serial.begin(9600); 
  pinMode(4,OUTPUT);
  pinMode(trigger1, OUTPUT); 
  pinMode(echo1, INPUT);
  pinMode(trigger2, OUTPUT); 
  pinMode(echo2, INPUT);
  pinMode(trigger3, OUTPUT); 
  pinMode(echo3, INPUT);
  pinMode(ledL, OUTPUT);
  pinMode(ledR, OUTPUT);
  pinMode(grd1, OUTPUT);
  pinMode(grd2, OUTPUT);
  Serial.println("hello ram ram");
}
int calculate_distance(int trigger, int echo)
{
  digitalWrite(trigger, LOW);
  delayMicroseconds(2);
  digitalWrite(trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger, LOW);
  
  time_taken = pulseIn(echo, HIGH);
  int dist= time_taken*0.034/2;
  
  return dist;
}

void ledBlink(int led1,int led2)
{
  int bs = 0;
  for(int x=1;x<=5;x++)
  {
    if(bs == 0)
    {
      digitalWrite(led1,HIGH);
      digitalWrite(led2,HIGH);
      bs = 1;
    }
    else
    {
      digitalWrite(led1,LOW);
      digitalWrite(led2,LOW);
      bs = 0;
    }
    delay(80);
  }
}

void ledStop()
{
  digitalWrite(ledL, LOW);
  digitalWrite(ledR, LOW);
}

void loop()
{
  digitalWrite(4,HIGH);
  digitalWrite(grd1, LOW);
  digitalWrite(grd2, LOW);
  
  distL = calculate_distance(trigger1,echo1);
  distR = calculate_distance(trigger2,echo2);
  distM = calculate_distance(trigger3,echo3);
  
  Serial.print(distL);
  Serial.print("  ");
  Serial.print(distM);
  Serial.print("  ");
  Serial.println(distR);
  
  //User Not present - will never be true
  if(distM > 80)
  {
    Serial.println("userabsent");
    delay(500);
  }
  else if(distM < passDist)
  {
    if(distL < maxDistL)
    {
      ledBlink(ledL, ledM);
    }
    else if(distR <= maxDistR)
    {
      ledBlink(ledR, ledM);
    }
    else
    {
      ledBlink(ledM, ledM);
    }
    Serial.println("pass");
    delay(500);
  }
  else if(distL <= stMove)
  {
    if(distR <= stMove)
    {
      Serial.println("moveUp");
    }
    else if(distR <= maxDistR)
    {
      Serial.println("moveLeftUp");
    }
    else
    {
      Serial.println("moveLeft");
    }
  }
  else if(distL <= maxDistL)
  {
    if(distR <= stMove)
    {
      Serial.println("moveRightUp");
    }
    else if(distR <= maxDistR)
    {
      Serial.println("moveDown");
    }
    else
    {
      Serial.println("moveLeftDown");
    }
  }
  else
  {
    if(distR <= stMove)
    {
      Serial.println("moveRight");
    }
    else if(distR <= maxDistR)
    {
      Serial.println("moveRightDown");
    }
    else
    {
      Serial.println("No gesture recognized");
    }
  }
}
