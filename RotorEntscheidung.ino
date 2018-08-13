

void react()
{
  moveazi();
  moveele();
}


  
void moveazi()
{
  uint8_t dir_cw;
  int16_t diff;
  uint16_t distance;
  int16_t distance2;
  int16_t temp_azis;

  if(digitalRead(sateliteMode) == 0)  //sat aktiv
  {
    if(azis < (90+180))
    {
      temp_azis = azis - (90+180) + 360;
    }
    else
    {
      temp_azis = azis - (90+180);
    }
  }
  else
  {
    temp_azis = azis;
  }

  diff = temp_azis - azi;

  if(diff > 0)
  {
    dir_cw = 1;
    distance = temp_azis - azi;
  }
  else
  {
    dir_cw = 0;
    distance = azi - temp_azis;
  }
  distance2 = azi - (temp_azis + 360);

  if(distance > abs(distance2) && (temp_azis + 360) < MAX_DEG)
  {
    temp_azis += 360;
    if(distance2 >= 0)
    {
      dir_cw = 0;
    }
    else
    {
      dir_cw = 1;
    }

    diff = temp_azis - azi;
    if(diff > 0)
    {
      distance = temp_azis - azi;
    }
    else
    {
      distance = azi - temp_azis;
    }
    
  }

  if( distance > azi_toleranz && azi_moving  != 0)
  {
    if(dir_cw != 0)
    {
      digitalWrite(ccwPin, LOW);
      digitalWrite(cwPin, HIGH); 
      lcd.setCursor (13,1); 
      lcd.print(" cw");
    }
    else
    {
      digitalWrite(cwPin, LOW); 
      digitalWrite(ccwPin, HIGH);
      lcd.setCursor (13,1); 
      lcd.print("ccw");
    }
  }
  else
  {
    azi_moving = 0;
    digitalWrite(ccwPin, LOW);
    digitalWrite(cwPin, LOW);
    lcd.setCursor (13,1); 
    lcd.print(" - ");
  }
  
  
  
/*  if(azis > azi)
  {
    if ((azis-azi) > toleranz && azi_moving != 0)
    {
        digitalWrite(ccwPin, LOW);
        digitalWrite(cwPin, HIGH); 
        lcd.setCursor (15,1); 
        lcd.print("R");
    } 
    else
    {
      azi_moving = 0;
      digitalWrite(ccwPin, LOW);
      digitalWrite(cwPin, LOW);
        lcd.setCursor (15,1); 
        lcd.print("-");
    }    
  }
  else
  {
    if ((azi-azis) > toleranz && azi_moving != 0)
    {
        digitalWrite(cwPin, LOW); 
        digitalWrite(ccwPin, HIGH);
        lcd.setCursor (15,1); 
        lcd.print("L");
            
    } 
    else
    {
      azi_moving = 0;
      digitalWrite(ccwPin, LOW);
      digitalWrite(cwPin, LOW);
              lcd.setCursor (15,1); 
        lcd.print("-");
    }   
    
  }*/

}
  
void moveele()
{
  uint8_t dir_up;
  int16_t diff = eles - ele;
  uint16_t distance;
  
  if(diff > 0)
  {
    dir_up = 1;
    distance = eles - ele;
  }
  else
  {
    dir_up = 0;
    distance = ele - eles;
  }


  if( distance > ele_toleranz && ele_moving  != 0)
  {
    if(dir_up != 0)
    {
      digitalWrite(DownPin, HIGH);
      digitalWrite(UpPin, LOW); 
      lcd.setCursor (14,3); 
      lcd.print("up");
    }
    else
    {
      digitalWrite(UpPin, HIGH); 
      digitalWrite(DownPin, LOW);
      lcd.setCursor (12,3); 
      lcd.print("down");
    }
  }
  else
  {
    ele_moving = 0;
    digitalWrite(UpPin, HIGH);
    digitalWrite(DownPin, HIGH);
    lcd.setCursor (12,3); 
    lcd.print("  - ");
  }






  /*
  if ((ele-eles)*(ele-eles) > toleranz)
  {
    if((eles-ele)<0)
    {
      digitalWrite(UpPin, LOW);
      digitalWrite(DownPin, HIGH);
      lcd.print("D");
    }      
    if((eles-ele)<0)
    {
      digitalWrite(DownPin, LOW);
      digitalWrite(UpPin, HIGH);
      lcd.print("U");
    }
  
  } 
  else
  {
    digitalWrite(UpPin, LOW);
    digitalWrite(DownPin, LOW);
  }*/
}  
