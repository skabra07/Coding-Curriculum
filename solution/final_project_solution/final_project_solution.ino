/**

This is the solution for the final problem. Please do not see the solution
unless you have tried to solve the problem first.


*/

#include <EngduinoLEDs.h>
#include <EngduinoAccelerometer.h>
#include <Wire.h>

//set number of levels until the player has won
#define LEVELS 5

int i, j;
int action[LEVELS];
int mode;

float xyz[3];

void setup()
{
  EngduinoLEDs.begin();
  EngduinoAccelerometer.begin();
  randomSeed(analogRead(0));
  j=0;
}


void loop()
{ 
  //choose a random colour
  action[j] = random(1,5);
  
  //blink colour sequence
  for(i=0;i<=j;i++)
  {
    blinkColor(action[i]);
    delay(500);
  }
   
  // Read the player actions
    for(i=0; i<=j; i++)
    {
      
      //reset sensing player action
      mode = 1;
      while(mode==1)
      {
        EngduinoAccelerometer.xyz(xyz);
        if(getAction(xyz) == action[i])
        {
          blinkColor(action[i]);
          mode = 0;
        }
        else if(getAction(xyz) == 0){}
        else
        {
          while(1)
          {
              playerLost();
          }
        }
      }  
    }
    j++;
    if(j==LEVELS)
    {
      while(1)
      {
        playerWon();
      }
    }
    delay(500);
}

int getAction(float *xyz)
{
    if (xyz[0] > 0.2 && xyz[0] < 1 && xyz[2] >-0.95 && xyz[2]<0) { // UP
       //red
       return 1;
   }
  else if (xyz[1] > 0.2&& xyz[1] < 1 && xyz[2] > -0.95 && xyz[2]<0) { //RIGHT
       //blue
       return 2;
   }
  else if (xyz[0] > -1 && xyz[0] < -0.2&& xyz[2] >-0.95 && xyz[2]<0) { //DOWN
      //green
      return 3;
    
  }
  else if (xyz[1] > -1 && xyz[1] < -0.2 && xyz[2] >-0.95 && xyz[2]<0) { //LEFT
      //blue
      return 4;    
  }
  else
    return 0;
}

void blinkColor(int x)
{
  switch (x)
  {
    case 1: 
      EngduinoLEDs.setLED(9, RED);
      EngduinoLEDs.setLED(10, RED);
      EngduinoLEDs.setLED(11, RED);
      EngduinoLEDs.setLED(12, RED);
      EngduinoLEDs.setLED(13, RED);
      break;
    case 2: 
      EngduinoLEDs.setLED(6, BLUE);
      EngduinoLEDs.setLED(7, BLUE);
      EngduinoLEDs.setLED(8, BLUE);
      EngduinoLEDs.setLED(9, BLUE);
      break;
    case 3: 
      EngduinoLEDs.setLED(1, GREEN);
      EngduinoLEDs.setLED(2, GREEN);
      EngduinoLEDs.setLED(3, GREEN);
      EngduinoLEDs.setLED(4, GREEN);
      EngduinoLEDs.setLED(5, GREEN);
      break;
    case 4: 
      EngduinoLEDs.setLED(0, YELLOW);
      EngduinoLEDs.setLED(15, YELLOW);
      EngduinoLEDs.setLED(14, YELLOW);
      EngduinoLEDs.setLED(13, YELLOW);
      break;
    default: 
      break;
  }
  delay(1000);
  EngduinoLEDs.setAll(OFF);
}

void playerWon()
{
    EngduinoLEDs.setAll(GREEN);
    delay(100);
    EngduinoLEDs.setAll(OFF);
    delay(100);
}

void playerLost()
{
    EngduinoLEDs.setAll(RED);
    delay(100);
    EngduinoLEDs.setAll(OFF);
    delay(100);
}


