
#define azimuthInputPin  A0  
#define elevationInputPin A1
#define UpPin  8       
#define DownPin  9      
#define ccwPin  2      
#define cwPin  3
#define sateliteMode 4

//azimutfaktor: (5*360)/(1023*3.3)
#define azimutfaktor ((double(5) * double(360))/(double(1023) * double(4.3)))

#define elevationfaktor 10
#define toleranz 1

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

#include <Wire.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>
  LiquidCrystal_I2C lcd(0x3F,2,1,0,4,5,6,7);
  LiquidCrystal_I2C lcd1(0x3E,2,1,0,4,5,6,7);

  
void setup()
{
   // initialize rotor control pins as outputs
   analogReference(INTERNAL);
   pinMode(UpPin, OUTPUT);
   pinMode(DownPin, OUTPUT);
   pinMode(ccwPin, OUTPUT);
   pinMode(cwPin, OUTPUT);

   pinMode(sateliteMode, INPUT_PULLUP);
   
   // set all the rotor control outputs low
   digitalWrite(UpPin, LOW);
   digitalWrite(DownPin, LOW);
   digitalWrite(ccwPin, LOW);
   digitalWrite(cwPin, LOW);
    
    // initialize serial ports:
    Serial.begin(9600);  // control
    lcd.begin (16,2); 
    lcd1.begin (16,2); 
    
	lcd.setBacklightPin(3,POSITIVE);
	lcd.home (); 

 lcd1.setBacklightPin(3,POSITIVE);
 lcd1.home (); 
 
	lcd.print("Test"); 
 lcd1.print("Test"); 
	lcd.setCursor (0,1);  
	lcd.print("FGAletsee"); 
	lcd.setBacklight(HIGH);
lcd1.setBacklight(HIGH);
 lcd.clear();
 lcd1.clear();

  }  

void loop() {
 
   if (Serial.available() > 0)
    {
      decodeCommand(Serial.read()); 
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

 // lcd1.clear();
  lcd1.home (); 

  lcd1.print("ELI  ");
  if(ele < 10)
  {
    lcd1.print("0");
  }
  lcd1.print(ele);
  lcd1.setCursor (0,1); 
  lcd1.print("ELES ");
  if(eles < 10)
  {
    lcd1.print("0");
  }
  lcd1.print(eles);
 
  }
void readValues()
{
  azi=int16_t((double(analogRead(azimuthInputPin))*double(azimutfaktor)) + 0.5);
  ele=analogRead(elevationInputPin)/elevationfaktor;
  }
