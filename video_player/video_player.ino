const int trigger1 = 7; //Trigger pin of 1st Sesnor
const int echo1 = 6; //Echo pin of 1st Sesnor
const int trigger2 = 3;
const int echo2 = 2;
const int ledL = 10;
const int ledR = 9;
const int grd1 = 11;
const int grd2 = 12;
const int maxRecoDist = 35;
int distL,distR;
long time_taken;

void setup() {
  Serial.begin(9600); 
  pinMode(4,OUTPUT);
  pinMode(trigger1, OUTPUT); 
  pinMode(echo1, INPUT);
  pinMode(trigger2, OUTPUT); 
  pinMode(echo2, INPUT);
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
  /*if (dist>60)
    {dist = 60;
    }*/
  
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
    delay(100);
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
  
  Serial.print(distL);
  Serial.print("  ");
  Serial.println(distR);
  
  //User Not present - will never be true
  if(distL>110 && distR>110)
  {
    Serial.println("userabsent");
    delay(500);
  }
  else if(distL > 10 && distR > 10 && distL < maxRecoDist && distR < maxRecoDist)
  {
    ledBlink(ledL, ledR);
    Serial.println("Play/Pause gesture recognizing ...");
    int Play_Pause = 0;
    int constantDistL = distL;
    int constantDistR = distR;
    for(int x=1;x<=10;x++)
    {
      delay(40);
      distL = calculate_distance(trigger1,echo1);
      distR = calculate_distance(trigger2,echo2);
      if(!(distL < constantDistL-5 || distL > constantDistL+5 || distR < constantDistR-5 || distR > constantDistR+5))
      {
        Play_Pause++;
      }
    }
    if(Play_Pause > 6)
    {
      Serial.println("Play/Pause");
      delay(5000);
    }
    else
    {
      Serial.println("NOT Play/Pause");
    }
    ledStop();
  }
  else if(distL > 5 && distL < maxRecoDist && distR > 40)
  {
    int volumeUp = 0;
    int volumeDown = 0;
    ledBlink(ledL, ledL);
    Serial.println("Right Hand gesture recognizing ...");
    Serial.print("distL");
    for(int x=1;x<=10;x++)
    {
      delay(40);
      int prevDist = distL;
      distL = calculate_distance(trigger1,echo1);
      
      Serial.print("  ");
      Serial.print(distL);
      if(distL > prevDist)
      {
        volumeDown++;
      }
      else if(distL < prevDist)
      {
        volumeUp++;
      }
    }
    Serial.println();
    if(volumeUp > 5)
    {
      Serial.println("Vup");
      delay(500);
    }
    else if(volumeDown > 5)
    {
      Serial.println("Vdown");
      delay(500);
    }
    else
    {
      Serial.println("No Right Hand gesture recognized");
    }
    ledStop();
  }
  else if(distR > 5 && distR < maxRecoDist && distL > 40)
  {
    int fow = 0;
    int rew = 0;
    ledBlink(ledR, ledR);
    Serial.println("Left Hand gesture recognizing ...");
    Serial.print("distR");
    for(int x=1;x<=10;x++)
    {
      delay(40);
      int prevDist = distR;
      distR = calculate_distance(trigger2,echo2);
      
      Serial.print("  ");
      Serial.print(distR);
      if(distR > prevDist)
      {
        rew++;
      }
      else if(distR < prevDist)
      {
        fow++;
      }
    }
    Serial.println();
    if(fow > 5)
    {
      Serial.println("Forward");
      delay(500);
    }
    else if(rew > 5)
    {
      Serial.println("Rewind");
      delay(500);
    }
    else
    {
      Serial.println("No Left Hand gesture recognized");
    }
    ledStop();
  }
  else
  {
    Serial.println("No gesture recognized");
    delay(500);
  }

}
