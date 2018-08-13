#define MAX_DEG 420
#define azimuthInputPin  A0  
#define elevationInputPin A1
#define UpPin  8       
#define DownPin  9      
#define ccwPin  2      
#define cwPin  3
#define sateliteMode 4
#define turnAround 5

//azimutfaktor: (5*360)/(1023*3.3)
#define azimutfaktor ((double(5) * double(360))/(double(1023) * double(4.3)))

#define elevationfaktor 10
#define azi_toleranz 1
#define ele_toleranz 1
#define start_toleranz 5

#define bufflength 60
char buff[bufflength];
uint8_t bcnt=0;
int16_t azi=112;
int8_t ele=21;
int16_t azis=112;
int8_t eles=21;
uint8_t azimove=0;
uint8_t elemove=0;
uint8_t active=1;
uint8_t azi_moving = 0;
uint8_t ele_moving = 0;
uint8_t turnaround_state = 0;

#include <Wire.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>
  LiquidCrystal_I2C lcd(0x3F,2,1,0,4,5,6,7);


  
void setup()
{
   // initialize rotor control pins as outputs
   analogReference(INTERNAL);
   pinMode(UpPin, OUTPUT);
   pinMode(DownPin, OUTPUT);
   pinMode(ccwPin, OUTPUT);
   pinMode(cwPin, OUTPUT);

   pinMode(sateliteMode, INPUT_PULLUP);
   pinMode(turnAround, INPUT_PULLUP);
   
   // set all the rotor control outputs low
   digitalWrite(UpPin, LOW);
   digitalWrite(DownPin, LOW);
   digitalWrite(ccwPin, LOW);
   digitalWrite(cwPin, LOW);
    
    // initialize serial ports:
    Serial.begin(9600);  // control
    lcd.begin (20,4); 
   
    
	lcd.setBacklightPin(3,POSITIVE);
	lcd.home (); 


 
	

	lcd.setCursor (0,0);  
	lcd.print("Vielen Dank an"); 
 lcd.setCursor (0,1);  
 lcd.print("Andreas (SWL)"); 
  lcd.setCursor (0,2);  
 lcd.print("Sandra & Dominik"); 
   lcd.setCursor (0,3);  
 lcd.print("Franz (DL6FCD)");
lcd.setBacklight(HIGH);
delay(3000);
 lcd.clear();


  }  

void loop() {
 
   if (Serial.available() > 0)
    {
      decodeCommand(Serial.read()); 
    }



    if(digitalRead(turnAround) == 0)
    {
      while(digitalRead(turnAround) == 0)  //Taster entprellen und warten, bis losgelassen
      {
        delay(5);
      }
      
      if(azi < int16_t(360))
      {
        if(azi < int16_t(MAX_DEG - 360)) // maximal: 420 ==> 420-360=60
        {
          azis = azi + 360;
          azi_moving = 1;
        }
      }
      else
      {
        azis = azi - 120;
        turnaround_state = 1;
        azi_moving = 1;
      }
    }

    //turnarround states (bei ccw kann man nicht -360 machen; wird wegoptimiert. deshalb drei mal -120)
    switch(turnaround_state)
    {
    case 1 :
      if(azi_moving == 0)
      {
        azis = azi - 120;
        turnaround_state = 2;
        azi_moving = 1;
      }    
      break;

    case 2 :
      if(azi_moving == 0)
      {
        azis = azi - 120;
        turnaround_state = 3;
        azi_moving = 1;
      }    
      break;

    case 3 :
      if(azi_moving == 0)
      {
        turnaround_state = 0;
      }    
      break;
  
      default:
        break;
    }
    
   readValues();
  // if (active)
   react(); 
    disp();
   
}
void disp(){

  
  lcd.home (); 
  lcd.print("AZI  ");
  if(azi<100)
  {
    lcd.print("0");
    if(azi < 10)
    {
      lcd.print("0");
    }
  }
  lcd.print(azi);

  
  if(digitalRead(sateliteMode) == 0)
  {
    lcd.setCursor (13,0);
    lcd.print("sat");
  }
  else
  {
    lcd.setCursor (13,0);
    lcd.print("   ");
  }

  lcd.setCursor (0,1);
  lcd.print("AZIS ");
  if(azis<100)
  {
    lcd.print("0");
    if(azis < 10)
    {
      lcd.print("0");
    }
  }
  lcd.print(azis);

 lcd.setCursor (0,2);

  lcd.print("ELI  ");
  if(ele < 10)
  {
    lcd.print("0");
  }
  lcd.print(ele);
  lcd.setCursor (0,3); 
  lcd.print("ELES ");
  if(eles < 10)
  {
    lcd.print("0");
  }
  lcd.print(eles);
 
  }
void readValues()
{
  azi=int16_t((double(analogRead(azimuthInputPin))*double(azimutfaktor)) + 0.5);
  ele=analogRead(elevationInputPin)/elevationfaktor;
  }
