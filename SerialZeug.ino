void decodeCommand(char c)
{
  if (c==0x0D)
  {
    if (strstr(buff,"C2"))
      command_C2();
      if (strstr(buff,"W"))
      command_W(); 
      //Serial.print("Debug");
      //Serial.print(buff);
    clearBuff();
    bcnt=0;
    }
    else
    {
      *(buff+bcnt)=c;
      bcnt++;
      }
  }
  
  void clearBuff()
  {
    for(uint8_t i=0;i<bufflength;i++)
    {buff[i]=0x00;}
   }

   
   void command_C2()
   {
     
    //Serial.print("AZ=");
     Serial.print("+0");
     if (azi<100) Serial.print('0');
    if (azi<10) Serial.print('0');
    Serial.print(azi);

     Serial.print("+0");
     
        if (ele<100) Serial.print('0');
    if (ele<10) Serial.print('0');
    Serial.print(ele);
  
   Serial.print("\r"); 
    Serial.print("\n");
     }
     
     void command_W()
     {
       buff[4]=0;
       azis=atoi(buff+1);
       buff[8]=0;
       eles=atoi(buff+5);
       Serial.print("\r");

       turnaround_state = 0;

       if(abs(azis-azi) > start_toleranz)
       {
        azi_moving = 1;
       }

       if(abs(eles-ele) > start_toleranz)
       {
        ele_moving = 1;
       }

       }
