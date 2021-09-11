/*******************************************************
This program was created by the
CodeWizardAVR V3.14 Advanced
Automatic Program Generator
© Copyright 1998-2014 Pavel Haiduc, HP InfoTech s.r.l.
http://www.hpinfotech.com

Project : 
Version : 
Date    : 8/10/2021
Author  : 
Company : 
Comments: 


Chip type               : ATmega16A
Program type            : Application
AVR Core Clock frequency: 8.000000 MHz
Memory model            : Small
External RAM size       : 0
Data Stack size         : 256
*******************************************************/

#include <mega16a.h>
#include <i2c.h>
#include <ds1307.h>
#include <alcd.h>
#include <delay.h>
#include <stdio.h>

#define R1 PORTA.0
#define R2 PORTA.1
#define R3 PORTA.2
#define R4 PORTA.3

#define C1 PINA.4
#define C2 PINA.5
#define C3 PINA.6
#define C4 PINA.7

#define KEYPAD_PORT PORTA
#define KEYPAD_DIR  DDRA
#define KEYPAD_PIN  PINA

     
       unsigned char enter=0;
       unsigned  char stop =1;
      
       unsigned char year_kypad;
      unsigned char day_kypad;
      unsigned char mounth_kypad;
      unsigned char add_tbdil;
      char READ_DATA;

      char nayesh_menu[20];
      char namayesh_menu[20];
      char digit_array[20] = {0};

      char h,m,s;

      char counter_regule =0;

      unsigned char kp = 0; 

      unsigned char year_usart=0;
      unsigned char day_usart=0;
      unsigned char mounth_usart=0;
      unsigned char year;
      unsigned char month;
      unsigned char day;
      unsigned char week_day;
      char COUNTER=0;
      unsigned char COUNTER_keypad=0;
      unsigned char hour_usart=0;
      unsigned char minutes_usart=0;
      unsigned char secend_usart=0;
      unsigned char hour_kypad=0;
      unsigned char minutes_kypad=0;
      unsigned char secend_kypad=0; 

     void off_enrx(void);
      void start_enrx(void);
     void usart_sendbyte(char);
     void usart_sendstring(char*); 
     void usart_initial(void);
     char conversion_character_int(void);
     void keypad_init(void);
     char keypad_read(void);
     void namyaesh_lcd(void);
     void vaziat_klid(unsigned char);
   
     interrupt[USART_RXC] void uassart_interupt (void)
 {    
     
  
      COUNTER = COUNTER+1;
      READ_DATA = UDR;
      add_tbdil=conversion_character_int(); 
     if(COUNTER==1)
     { 
       hour_usart = add_tbdil;
       hour_usart =hour_usart*10; 
       rtc_set_time(hour_usart,m,s);
    } 
    if(COUNTER==2)
    {
      hour_usart =(hour_usart)+(add_tbdil);
      
       
          if(hour_usart<25)
          {  
            rtc_set_time(hour_usart,m,s);
            usart_sendstring("\r\n enter the miniets = \r\n ");
          }
          else
          {
            COUNTER = 0;
             usart_sendstring("\r\n Unauthorized number try again = \r\n ");
          }
      
        
    }

    if(COUNTER==3)
    {        
        minutes_usart = add_tbdil;
        minutes_usart = minutes_usart*10;
        rtc_set_time(h,minutes_usart,s);
        
    }                               
     if(COUNTER==4)
     {
       
       minutes_usart = (minutes_usart)+(add_tbdil); 
        if(minutes_usart<60)
          {
            rtc_set_time(h,minutes_usart,s);
            usart_sendstring("\r\n enter the secend = \r\n ");
          }
          else
          {
            COUNTER = 2;
             usart_sendstring("\r\n Unauthorized number try again = \r\n ");
          }
       
       
     
     
       
     }
    if(COUNTER==5)
    {
        secend_usart = add_tbdil;
        secend_usart = secend_usart*10;
        rtc_set_time(h,m,secend_usart);
    } 
    if(COUNTER==6)
    {  
       secend_usart = (secend_usart)+(add_tbdil);
       if(secend_usart<60)
          {
              rtc_set_time(h,m,secend_usart);
              usart_sendstring("\r\n enter the year = \r\n ");
          }
          else
          {
            COUNTER = 4;
             usart_sendstring("\r\n Unauthorized number try again = \r\n ");
          }
      
    }
    if(COUNTER==7) 
    {
        year_usart = add_tbdil;
        year_usart = year_usart*10;
         rtc_set_date(week_day,day, month,year_usart); 
        } 
        if(COUNTER==8) 
    {
        year_usart =  (year_usart) + (add_tbdil);
         rtc_set_date(week_day,day, month,year_usart);
          usart_sendstring("\r\n enter the month = \r\n ");
          
        } 
          if(COUNTER==9) 
    {
        mounth_usart = add_tbdil;
        mounth_usart = mounth_usart*10;
         rtc_set_date(week_day,day, mounth_usart,year); 
         
        } 
      if(COUNTER==10) 
    {
        mounth_usart =  (mounth_usart) + (add_tbdil);
         if(mounth_usart<13)
          {
              rtc_set_date(week_day,day, mounth_usart,year);
               usart_sendstring("\r\n enter the  day = \r\n ");      
                   }
          else
          {
            COUNTER = 8;
             usart_sendstring("\r\n Unauthorized number try again = \r\n ");
          }
        
          
          
        } 
    if(COUNTER==11) 
    {
        day_usart = add_tbdil;
        day_usart = day_usart*10;
         rtc_set_date(week_day,day_usart, month,year); 
         
        } 
     if(COUNTER==12) 
    {
        day_usart =  (day_usart) + (add_tbdil); 
         if(day_usart<30)
          {
                rtc_set_date(week_day,day_usart, month,year);
                 usart_sendstring("\r\n press Enter at the end = \r\n ");  
                   }
          else
          {
            COUNTER = 10;
             usart_sendstring("\r\n Unauthorized number try again = \r\n ");
          }
        
          
          
        } 
        
    
    

    if(add_tbdil==13)
    {
      
     
        usart_sendstring("\r\n  thanks  = \r\n ");
        counter_regule =0; 
        stop=1;
        enter=0;
        COUNTER=0-1; 
        off_enrx();

     
    }
  
 } 
 
    

void main(void)
{

  
    keypad_init();

// Bit-Banged I2C Bus initialization
// I2C Port: PORTC
// I2C SDA bit: 1
// I2C SCL bit: 0
// Bit Rate: 100 kHz
// Note: I2C settings are specified in the
// Project|Configure|C Compiler|Libraries|I2C menu.
i2c_init();

// DS1307 Real Time Clock initialization
// Square wave output on pin SQW/OUT: Off
// SQW/OUT pin state: 0
rtc_init(0,0,0);

// Alphanumeric LCD initialization
// Connections are specified in the
// Project|Configure|C Compiler|Libraries|Alphanumeric LCD menu:
// RS - PORTB Bit 0
// RD - PORTB Bit 1
// EN - PORTB Bit 2
// D4 - PORTB Bit 3
// D5 - PORTB Bit 4
// D6 - PORTB Bit 5
// D7 - PORTB Bit 6
// Characters/line: 16
lcd_init(16);

  usart_initial();
  #asm("sei")
//rtc_set_date(weekday,day,mounth,year);
// rtc_set_time(hh,mm,ss);
 lcd_gotoxy(0,0);
 lcd_puts("creator by Ali.B"); 
 lcd_gotoxy(0,1);
 lcd_puts("version=1.0.0");
 delay_ms(2000);
 lcd_clear(); 
 

while (1)
      {     
//                sprintf(nayesh_menu," kp =%02d ",kp);
//                lcd_clear(); 
//                lcd_gotoxy(0,0);
//                lcd_puts(nayesh_menu);
//                delay_ms(20);
          kp = keypad_read();
          vaziat_klid(kp); 
          namyaesh_lcd();


      }
      
      }

void keypad_init(void)
{
    KEYPAD_DIR = 0x0F;
    KEYPAD_PORT = 0xFF;
}

char keypad_read(void)
{
unsigned char number = 16;

    R1 = 0; R2 = 1; R3 = 1; R4 = 1;
    if (C1 == 0){while (C1 == 0){} number = 1;}
    if (C2 == 0){while (C2 == 0){} number =2;}
    if (C3 == 0){while (C3 == 0){} number = 3;}
    if (C4 == 0){while (C4 == 0){} number = 10;}
        
    R1 = 1; R2 = 0; R3 = 1; R4 = 1;
    if (C1 == 0){while (C1 == 0){} number = 4;}
    if (C2 == 0){while (C2 == 0){} number = 5;}
    if (C3 == 0){while (C3 == 0){} number = 6;}
    if (C4 == 0){while (C4 == 0){} number = 11;}
        
    R1 = 1; R2 = 1; R3 = 0; R4 = 1;
    if (C1 == 0){while (C1 == 0){} number = 7;}
    if (C2 == 0){while (C2 == 0){} number = 8;}
    if (C3 == 0){while (C3 == 0){} number = 9;}
    if (C4 == 0){while (C4 == 0){} number = 12;}
        
    R1 = 1; R2 = 1; R3 = 1; R4 = 0;
    if (C1 == 0){while (C1 == 0){} number = 14;}
    if (C2 == 0){while (C2 == 0){} number = 0;}
    if (C3 == 0){while (C3 == 0){} number = 15;}
    if (C4 == 0){while (C4 == 0){} number = 13;}
   
               
//                      if(COUNTER_keypad==1)
//                { 
//                        
//                      }
//                      if(COUNTER_keypad==2)
//                      {
//                             hour_kypad = hour_kypad+number;
//                               
//                              
//                      } 
//                      if(COUNTER_keypad==3)
//                      {   
//                         minutes_kypad = number*10; 
//                        
//                      } 
//                      if(COUNTER_keypad==4)
//                      {  
//                              minutes_kypad = minutes_kypad+number;
//                       
//                        
//                      }
//                     
//                      if(COUNTER_keypad==5)
//                      {
//                          secend_kypad =number*10; 
//
//                        
//                      }
//                      if(COUNTER_keypad==6)
//                      {
//                            secend_kypad = secend_kypad+number;
//                              
//                      }

            
    return number;
}

void namyaesh_lcd(void)
 {

    if(stop==1)
     {   
         
         //play watch
          rtc_get_date(&week_day,&day,&month,&year);
          rtc_get_time(&h,&m,&s);
          lcd_clear();  
          sprintf(digit_array,"%02d:%02d:%02d",h,m,s);
          sprintf(nayesh_menu,"%02d/%02d/%02d",day,month,year);
          lcd_gotoxy(4,0);
          lcd_puts(digit_array);
          lcd_gotoxy(4,1);
          lcd_puts(nayesh_menu);
         
          
          delay_ms(10);
      
     }
  
    if(stop==0)
     {
             
   
         //vaghti klid f1 zade shode 
           if(counter_regule==0 )
           {
             sprintf(nayesh_menu," set by usart ");
             sprintf(namayesh_menu," set by keypad ");
             lcd_clear(); 
             lcd_gotoxy(1,0);
             lcd_puts(nayesh_menu);
             lcd_gotoxy(1,1);
             lcd_puts(namayesh_menu);
             delay_ms(10);
             
             }
             if(counter_regule==1 )
             {     
                 
                //vaghti klid f2 zade shode 
               if(enter==0) 
               {
                    sprintf(nayesh_menu," set by usart ");
                    sprintf(namayesh_menu," set by keypad ");
                    lcd_clear();
                     lcd_gotoxy(0,0);
                     lcd_puts("*");
                    lcd_gotoxy(1,0);
                    lcd_puts(nayesh_menu);
                    lcd_gotoxy(1,1);
                    lcd_puts(namayesh_menu);
                    delay_ms(10);

                }
                 if(enter==1)
                 {  
                     start_enrx();
                    if(COUNTER==0)
                    {
                            rtc_get_time(&h,&m,&s);
                            sprintf(nayesh_menu," set houre  ");
                            sprintf(namayesh_menu,"  :%02d:%02d ",m,s);
                            sprintf(digit_array,"%02d:%02d:%02d",h,m,s); 
                            lcd_clear();
                            lcd_gotoxy(4,0);          
                            lcd_puts(digit_array);
                            lcd_gotoxy(3,1);
                            lcd_puts(nayesh_menu);
                            delay_ms(100); 
                            lcd_clear();
                            lcd_gotoxy(4,0);          
                            lcd_puts(namayesh_menu);
                            lcd_gotoxy(3,1);
                            lcd_puts(nayesh_menu);
                            delay_ms(100); 
                            
                     }
                      if(COUNTER==1)
                    {
                        //vaghti klid f3 zade shode 
                         rtc_get_time(&h,&m,&s);
                            sprintf(nayesh_menu," set houre  ");
                            sprintf(namayesh_menu,"  :%02d:%02d ",m,s);
                            sprintf(digit_array,"%02d:%02d:%02d",h,m,s); 
                            lcd_clear();
                            lcd_gotoxy(4,0);          
                            lcd_puts(digit_array);
                            lcd_gotoxy(3,1);
                            lcd_puts(nayesh_menu);
                            delay_ms(100); 
                            lcd_clear();
                            lcd_gotoxy(4,0);          
                            lcd_puts(namayesh_menu);
                            lcd_gotoxy(3,1);
                            lcd_puts(nayesh_menu);
                            delay_ms(100); 
                     }
                     if(COUNTER==2)
                     {
                            rtc_get_time(&h,&m,&s);
                            sprintf(nayesh_menu," set minute  ");
                            sprintf(namayesh_menu,"%02d:  :%02d ",h,s);
                            sprintf(digit_array,"%02d:%02d:%02d",h,m,s); 
                            lcd_clear();
                            lcd_gotoxy(4,0);          
                            lcd_puts(digit_array);
                            lcd_gotoxy(3,1);
                            lcd_puts(nayesh_menu);
                            delay_ms(100); 
                            lcd_clear();
                            lcd_gotoxy(4,0);          
                            lcd_puts(namayesh_menu);
                            lcd_gotoxy(3,1);
                            lcd_puts(nayesh_menu);
                            delay_ms(100); 
                     }
                      if(COUNTER==3)
                     {
                           rtc_get_time(&h,&m,&s);
                            sprintf(nayesh_menu," set minute  ");
                            sprintf(namayesh_menu,"%02d:  :%02d ",h,s);
                            sprintf(digit_array,"%02d:%02d:%02d",h,m,s); 
                            lcd_clear();
                            lcd_gotoxy(4,0);          
                            lcd_puts(digit_array);
                            lcd_gotoxy(3,1);
                            lcd_puts(nayesh_menu);
                            delay_ms(100); 
                            lcd_clear();
                            lcd_gotoxy(4,0);          
                            lcd_puts(namayesh_menu);
                            lcd_gotoxy(3,1);
                            lcd_puts(nayesh_menu);
                            delay_ms(100); 
                     }
                     if(COUNTER==4)
                     { 
                            rtc_get_time(&h,&m,&s);
                            sprintf(nayesh_menu," set secend  ");
                            sprintf(namayesh_menu,"%02d:%02d:   ",h,m);
                            sprintf(digit_array,"%02d:%02d:%02d",h,m,s); 
                            lcd_clear();
                            lcd_gotoxy(4,0);          
                            lcd_puts(digit_array);
                            lcd_gotoxy(3,1);
                            lcd_puts(nayesh_menu);
                            delay_ms(100); 
                            lcd_clear();
                            lcd_gotoxy(4,0);          
                            lcd_puts(namayesh_menu);
                            lcd_gotoxy(3,1);
                            lcd_puts(nayesh_menu);
                            delay_ms(100); 
                     } 
                     if(COUNTER==5)
                     {
                            rtc_get_time(&h,&m,&s);
                            sprintf(nayesh_menu," set secend  ");
                            sprintf(namayesh_menu,"%02d:%02d:   ",h,m);
                            sprintf(digit_array,"%02d:%02d:%02d",h,m,s); 
                            lcd_clear();
                            lcd_gotoxy(4,0);          
                            lcd_puts(digit_array);
                            lcd_gotoxy(3,1);
                            lcd_puts(nayesh_menu);
                            delay_ms(100); 
                            lcd_clear();
                            lcd_gotoxy(4,0);          
                            lcd_puts(namayesh_menu);
                            lcd_gotoxy(3,1);
                            lcd_puts(nayesh_menu);
                            delay_ms(100); 
                     } 
                     if(COUNTER==6)
                     {
                            rtc_get_time(&h,&m,&s);
                            sprintf(nayesh_menu," set secend  ");
                            sprintf(namayesh_menu,"%02d:%02d:   ",h,m);
                            sprintf(digit_array,"%02d:%02d:%02d",h,m,s); 
                            lcd_clear();
                            lcd_gotoxy(4,0);          
                            lcd_puts(digit_array);
                            lcd_gotoxy(3,1);
                            lcd_puts(nayesh_menu);
                            delay_ms(100); 
                            lcd_clear();
                            lcd_gotoxy(4,0);          
                            lcd_puts(namayesh_menu);
                            lcd_gotoxy(3,1);
                            lcd_puts(nayesh_menu);
                            delay_ms(100); 
                     }
                     if(COUNTER==7)
                      {      
                           rtc_get_date(&week_day,&day,&month,&year);
                           sprintf(nayesh_menu,"%02d/%02d/%02d",day,month,year);
                           sprintf(namayesh_menu,"%02d/%02d/  ",day,month,year);
                           lcd_clear();
                           lcd_gotoxy(4,0);          
                           lcd_puts(nayesh_menu);
                           delay_ms(100); 
                           lcd_clear();
                           lcd_gotoxy(4,0);          
                           lcd_puts(namayesh_menu);
                           delay_ms(100); 
                             
                             
                            
                        
                      }
                      if(COUNTER==8)
                      {      
                           
                            rtc_get_date(&week_day,&day,&month,&year);
                            sprintf(nayesh_menu,"%02d/%02d/%02d",day,month,year);
                            sprintf(namayesh_menu,"%02d/%02d/  ",day,month);
                            lcd_clear();
                            lcd_gotoxy(4,0);          
                            lcd_puts(nayesh_menu);
                            delay_ms(100); 
                            lcd_clear();
                            lcd_gotoxy(4,0);          
                            lcd_puts(namayesh_menu);
                            delay_ms(100);  
                      }
                       if(COUNTER==9)
                      {      
                           
                        
                            rtc_get_date(&week_day,&day,&month,&year);
                            sprintf(nayesh_menu,"%02d/%02d/%02d",day,month,year);
                            sprintf(namayesh_menu,"%02d/  /%02d  ",day,year);
                            lcd_clear();
                            lcd_gotoxy(4,0);          
                            lcd_puts(nayesh_menu);
                            delay_ms(100); 
                            lcd_clear();
                            lcd_gotoxy(4,0);          
                            lcd_puts(namayesh_menu);
                            delay_ms(100); 
                        
                      }
                       if(COUNTER==10)
                      {      
                           
                          
                             rtc_get_date(&week_day,&day,&month,&year);
                             sprintf(nayesh_menu,"%02d/%02d/%02d",day,month,year);
                             sprintf(namayesh_menu,"%02d/  /%02d  ",day,year);
                             lcd_clear();
                            lcd_gotoxy(4,0);          
                            lcd_puts(nayesh_menu);
                            delay_ms(100); 
                            lcd_clear();
                            lcd_gotoxy(4,0);          
                            lcd_puts(namayesh_menu);
                            delay_ms(100); 
                        
                      }
                       if(COUNTER==11)
                      {      
                         rtc_get_date(&week_day,&day,&month,&year);
                             sprintf(nayesh_menu,"%02d/%02d/%02d",day,month,year);
                             sprintf(namayesh_menu,"  /%02d/%02d  ",month,year);
                             lcd_clear();
                            lcd_gotoxy(4,0);          
                            lcd_puts(nayesh_menu);
                            delay_ms(100); 
                            lcd_clear();
                            lcd_gotoxy(4,0);          
                            lcd_puts(namayesh_menu);
                            delay_ms(100); 
                      }
                        if(COUNTER==12)
                      {      
                           
                         
                            rtc_get_date(&week_day,&day,&month,&year);
                             sprintf(nayesh_menu,"%02d/%02d/%02d",day,month,year);
                             sprintf(namayesh_menu,"  /%02d/%02d  ",month,year);
                             lcd_clear();
                            lcd_gotoxy(4,0);          
                            lcd_puts(nayesh_menu);
                            delay_ms(100); 
                            lcd_clear();
                            lcd_gotoxy(4,0);          
                            lcd_puts(namayesh_menu);
                            delay_ms(100); 
                              
                      }
                     
                   
                 } 
                

             }
             
             if(counter_regule==2)
             {  
               
              if(enter==0)
                {
                    //vaghti klid f2  2bar zade shode 
                   sprintf(nayesh_menu," set by usart ");
                   sprintf(namayesh_menu," set by keypad ");
                    lcd_clear(); 
                    lcd_gotoxy(0,0);
                    lcd_puts(nayesh_menu); 
                    lcd_gotoxy(0,1);
                     lcd_puts("*");
                    lcd_gotoxy(1,1);
                    lcd_puts(namayesh_menu);
                    delay_ms(10);
                }
                 
               if(enter==1)
             {      
                
                  
                 if(COUNTER_keypad==0)
                 {
                            rtc_get_time(&h,&m,&s);
                            sprintf(nayesh_menu," set houre  ");
                            sprintf(namayesh_menu,"  :%02d:%02d ",m,s);
                            sprintf(digit_array,"%02d:%02d:%02d",h,m,s); 
                            lcd_clear();
                            lcd_gotoxy(4,0);          
                            lcd_puts(digit_array);
                            lcd_gotoxy(3,1);
                            lcd_puts(nayesh_menu);
                            delay_ms(100); 
                            lcd_clear();
                            lcd_gotoxy(4,0);          
                            lcd_puts(namayesh_menu);
                            lcd_gotoxy(3,1);
                            lcd_puts(nayesh_menu);
                            delay_ms(100);
                            
                  
                      
                      }
                  
                 if(kp<16)
                 {   
                    if(kp<10)
                    {  
                       COUNTER_keypad++; 
                       if(COUNTER_keypad==1)
                           {    hour_kypad = kp*10;  
                                rtc_set_time(hour_kypad,m,s);
                           }
                       if(COUNTER_keypad==2)
                       {
                            hour_kypad = hour_kypad + kp;
                            if(hour_kypad<24)
                            {
                              rtc_set_time(hour_kypad,m,s);
                            } 
                            else 
                            {     
                                 sprintf(nayesh_menu,"Wrong time.        Try again");
                                  lcd_clear();
                               lcd_puts(nayesh_menu);
                               delay_ms(1000); 
                              lcd_clear();
                              COUNTER_keypad=0;
                              
                            }
                       }
                       if(COUNTER_keypad==3)
                       {  
                             
                           minutes_kypad = 10* kp; 
                           rtc_set_time(h,minutes_kypad,s);
                       }
                       if(COUNTER_keypad==4)
                       {
                            minutes_kypad = minutes_kypad + kp ; 
                             if(minutes_kypad<60)
                            {
                              rtc_set_time(h,minutes_kypad,s);
                            } 
                            else 
                            {     
                                 sprintf(nayesh_menu,"Wrong time.        Try again");
                                  lcd_clear();
                               lcd_puts(nayesh_menu);
                               delay_ms(1000); 
                              lcd_clear();
                              COUNTER_keypad=2;
                              
                            }
                       }
                       if(COUNTER_keypad==5)
                       {   

                          secend_kypad = 10* kp; 
                          rtc_set_time(h,m,secend_kypad);
                       }
                       if(COUNTER_keypad==6)
                       {
                           secend_kypad =secend_kypad + kp; 
                            if(secend_kypad<60)
                            {
                                rtc_set_time(h,m,secend_kypad);
                            } 
                            else 
                            {     
                                 sprintf(nayesh_menu,"Wrong time.        Try again");
                                  lcd_clear();
                               lcd_puts(nayesh_menu);
                               delay_ms(1000); 
                              lcd_clear();
                              COUNTER_keypad=4;
                              
                            }
                       }
                     if(COUNTER_keypad==7)
                      {   
                         
                          year_kypad = 10* kp; 
                          rtc_set_date(week_day,day, month,year_kypad);
                      }
                       if(COUNTER_keypad==8)
                       {
                           year_kypad = year_kypad + kp;
                            if(year_kypad<60)
                            {
                                 rtc_set_date(week_day,day, month,year_kypad);                   
                            } 
                            else 
                            {     
                                 sprintf(nayesh_menu,"Wrong time.        Try again");
                                  lcd_clear();
                               lcd_puts(nayesh_menu);
                               delay_ms(1000); 
                              lcd_clear();
                              COUNTER_keypad=6;
                              
                            } 
                          
                        }
                       if(COUNTER_keypad==9)
                       {                
                         
                         mounth_kypad = 10* kp; 
                         rtc_set_date(week_day,day, mounth_kypad,year);
                       }
                       if(COUNTER_keypad==10)
                       {
                            mounth_kypad = mounth_kypad + kp;
                              if(mounth_kypad<13)
                            {
                                rtc_set_date(week_day,day, mounth_kypad,year);   
                            } 
                            else 
                            {     
                                 sprintf(nayesh_menu,"Wrong time.        Try again");
                                  lcd_clear();
                               lcd_puts(nayesh_menu);
                               delay_ms(1000); 
                              lcd_clear();
                              COUNTER_keypad=8;
                              
                            } 
                       }
                       if(COUNTER_keypad==11)
                       {          
                           day_kypad = 10* kp; 
                            rtc_set_date(week_day,day_kypad, month,year); 
                       }
                       if(COUNTER_keypad==12)
                       {
                           day_kypad = day_kypad +  kp; 
                              if(day_kypad<31)
                            {
                                 rtc_set_date(week_day,day_kypad, month,year);   
                            } 
                            else 
                            {     
                                 sprintf(nayesh_menu,"Wrong time.        Try again");
                                  lcd_clear();
                               lcd_puts(nayesh_menu);
                               delay_ms(1000); 
                              lcd_clear();
                              COUNTER_keypad=10;
                              
                            } 
                           
                                              

                       }
                      
                }
               }
               
                    if(COUNTER_keypad==1)
                      {      
            
                            rtc_get_time(&h,&m,&s);
                            sprintf(nayesh_menu," set houre  ");
                            sprintf(namayesh_menu,"  :%02d:%02d ",m,s);
                            sprintf(digit_array,"%02d:%02d:%02d",h,m,s); 
                            lcd_clear();
                            lcd_gotoxy(4,0);          
                            lcd_puts(digit_array);
                            lcd_gotoxy(3,1);
                            lcd_puts(nayesh_menu);
                            delay_ms(100); 
                            lcd_clear();
                            lcd_gotoxy(4,0);          
                            lcd_puts(namayesh_menu);
                            lcd_gotoxy(3,1);
                            lcd_puts(nayesh_menu);
                            delay_ms(100); 
                            
                          
                      }
                      if(COUNTER_keypad==2)
                      {     
                          

                            rtc_get_time(&h,&m,&s);
                            sprintf(nayesh_menu," set minute  ");
                            sprintf(namayesh_menu,"%02d:  :%02d ",h,s);
                            sprintf(digit_array,"%02d:%02d:%02d",h,m,s);  
                            lcd_clear();
                            lcd_gotoxy(4,0);          
                            lcd_puts(digit_array);
                            lcd_gotoxy(3,1);
                            lcd_puts(nayesh_menu);
                            delay_ms(100); 
                            lcd_clear();
                            lcd_gotoxy(4,0);          
                            lcd_puts(namayesh_menu);
                            lcd_gotoxy(3,1);
                            lcd_puts(nayesh_menu);
                            delay_ms(200); 
                            

                             
                      } 
                      if(COUNTER_keypad==3)
                      {   
                         
                            rtc_get_time(&h,&m,&s);
                            sprintf(nayesh_menu," set minute  ");
                            sprintf(namayesh_menu,"%02d:  :%02d ",h,s);
                            sprintf(digit_array,"%02d:%02d:%02d",h,m,s); 
                            lcd_clear();
                            lcd_gotoxy(4,0);          
                            lcd_puts(digit_array);
                            lcd_gotoxy(3,1);
                            lcd_puts(nayesh_menu);
                            delay_ms(100); 
                            lcd_clear();
                            lcd_gotoxy(4,0);          
                            lcd_puts(namayesh_menu);
                            lcd_gotoxy(3,1);
                            lcd_puts(nayesh_menu);
                            delay_ms(100); 
                        
                      } 
                      if(COUNTER_keypad==4)
                      {  
                            
                              
                            rtc_get_time(&h,&m,&s);
                            sprintf(nayesh_menu," set secend  ");
                            sprintf(namayesh_menu,"%02d:%02d:   ",h,m);
                            sprintf(digit_array,"%02d:%02d:%02d",h,m,s); 
                            lcd_clear();
                            lcd_gotoxy(4,0);          
                            lcd_puts(digit_array);
                            lcd_gotoxy(3,1);
                            lcd_puts(nayesh_menu);
                            delay_ms(100); 
                            lcd_clear();
                            lcd_gotoxy(4,0);          
                            lcd_puts(namayesh_menu);
                            lcd_gotoxy(3,1);
                            lcd_puts(nayesh_menu);
                            delay_ms(100); 
                        
                               
                           
                                         
                      }
                     
                      if(COUNTER_keypad==5)
                      {      
                           
                           
                           
                            rtc_get_time(&h,&m,&s);
                            sprintf(nayesh_menu," set secend  ");
                            sprintf(namayesh_menu,"%02d:%02d:   ",h,m);
                            sprintf(digit_array,"%02d:%02d:%02d",h,m,s); 
                            lcd_clear();
                            lcd_gotoxy(4,0);          
                            lcd_puts(digit_array);
                            lcd_gotoxy(3,1);
                            lcd_puts(nayesh_menu);
                            delay_ms(100); 
                            lcd_clear();
                            lcd_gotoxy(4,0);          
                            lcd_puts(namayesh_menu);
                            lcd_gotoxy(3,1);
                            lcd_puts(nayesh_menu);
                            delay_ms(100); 
                        
                      }
                      if(COUNTER_keypad==6)
                      {        
                           

                          rtc_get_date(&week_day,&day,&month,&year);
                           sprintf(nayesh_menu,"%02d/%02d/%02d",day,month,year);
                           sprintf(namayesh_menu,"%02d/%02d/  ",day,month,year);
                           lcd_clear();
                           lcd_gotoxy(4,0);          
                           lcd_puts(nayesh_menu);
                           delay_ms(100); 
                           lcd_clear();
                           lcd_gotoxy(4,0);          
                           lcd_puts(namayesh_menu);
                           delay_ms(100); 
                              
                      } 
                       if(COUNTER_keypad==7)
                      {      
                           rtc_get_date(&week_day,&day,&month,&year);
                           sprintf(nayesh_menu,"%02d/%02d/%02d",day,month,year);
                           sprintf(namayesh_menu,"%02d/%02d/  ",day,month,year);
                           lcd_clear();
                           lcd_gotoxy(4,0);          
                           lcd_puts(nayesh_menu);
                           delay_ms(100); 
                           lcd_clear();
                           lcd_gotoxy(4,0);          
                           lcd_puts(namayesh_menu);
                           delay_ms(100); 
                             
                             
                            
                        
                      }
                      if(COUNTER_keypad==8)
                      {      
                           
                             rtc_get_date(&week_day,&day,&month,&year);
                            sprintf(nayesh_menu,"%02d/%02d/%02d",day,month,year);
                            sprintf(namayesh_menu,"%02d/  /%02d  ",day,year);
                            lcd_clear();
                            lcd_gotoxy(4,0);          
                            lcd_puts(nayesh_menu);
                            delay_ms(100); 
                            lcd_clear();
                            lcd_gotoxy(4,0);          
                            lcd_puts(namayesh_menu);
                            delay_ms(100);  
                      }
                       if(COUNTER_keypad==9)
                      {      
                           
                        
                            rtc_get_date(&week_day,&day,&month,&year);
                            sprintf(nayesh_menu,"%02d/%02d/%02d",day,month,year);
                            sprintf(namayesh_menu,"%02d/  /%02d  ",day,year);
                            lcd_clear();
                            lcd_gotoxy(4,0);          
                            lcd_puts(nayesh_menu);
                            delay_ms(100); 
                            lcd_clear();
                            lcd_gotoxy(4,0);          
                            lcd_puts(namayesh_menu);
                            delay_ms(100); 
                        
                      }
                       if(COUNTER_keypad==10)
                            {      

                          
                            rtc_get_date(&week_day,&day,&month,&year);
                            sprintf(nayesh_menu,"%02d/%02d/%02d",day,month,year);
                            sprintf(namayesh_menu,"  /%02d/%02d  ",month,year);
                            lcd_clear();
                            lcd_gotoxy(4,0);          
                            lcd_puts(nayesh_menu);
                            delay_ms(100); 
                            lcd_clear();
                            lcd_gotoxy(4,0);          
                            lcd_puts(namayesh_menu);
                            delay_ms(100);  
                        
                      }
                       if(COUNTER_keypad==11)
                      {    
                             
                           rtc_get_date(&week_day,&day,&month,&year);
                           sprintf(nayesh_menu,"%02d/%02d/%02d",day,month,year);
                           sprintf(namayesh_menu,"  /%02d/%02d  ",month,year);
                           lcd_clear();
                           lcd_gotoxy(4,0);          
                           lcd_puts(nayesh_menu);
                           delay_ms(100); 
                           lcd_clear();
                           lcd_gotoxy(4,0);          
                           lcd_puts(namayesh_menu);
                           delay_ms(100); 
                      }
                       if(COUNTER_keypad==12)
                      
                          {       
                             rtc_get_date(&week_day,&day,&month,&year);
                             sprintf(nayesh_menu,"%02d/%02d/%02d",day,month,year);
                             sprintf(namayesh_menu,"  /%02d/%02d  ",month,year);
                             lcd_clear();
                             lcd_gotoxy(4,0);          
                             lcd_puts(nayesh_menu);
                             delay_ms(100); 
                             lcd_clear();
                             lcd_gotoxy(4,0);          
                             lcd_puts(namayesh_menu);
                             delay_ms(100); 
                             
                             COUNTER_keypad=0;
                             enter=0;
                             counter_regule=0; 
                             stop=1; 
                              
                      }
               
             }  

      } 
    
    if(counter_regule==3)
      { 
         counter_regule=1;
      }     

    
}

  } 
  
void vaziat_klid(unsigned char kp)

   { 
      if(kp==10)
      { 
        stop=!(stop);
      }
      if(kp==11)
      {
        counter_regule++;
        if(counter_regule==4)
        {
          counter_regule=0;
        }
      }
       if(kp==12)
       { 
         enter=!(enter);
       } 
       if(kp==13)
       {
         if (COUNTER_keypad==0)
         {
         enter=0;
         } 
         
        if (COUNTER_keypad>0)
        { 
          COUNTER_keypad=COUNTER_keypad-1;
        }
       }
       
       

  }

  void usart_sendbyte(char ch)
  {
    UDR=ch;
    while(!(UCSRA&(1<<UDRE)));//WAIT  UNTILL BUFER EMPTY

  }  
  
   void usart_sendstring(char *str)
  { 
    unsigned char i;
    for(i=0;str[i];i++)
    { 
    usart_sendbyte(str[i]);
    }  
   }
   
  
  void usart_initial(void)
  { 
         //USART  Initialization
     //parametrs :8 data bits ,party none,1stop bits
     //baud rate : 9600 bps  
     //enable transmiter 
      UCSRA = 0X00;
      UCSRB = (1<<RXCIE)| (1<<TXEN)| (1<<RXEN) ;//ENABLE USART TRANSMITER AND RECIVERE
      UCSRC =  (1<<URSEL)|(0<<UMSEL)|(1<<UCSZ1)|(1<<UCSZ0);
      UBRRH = 0X00;
      UBRRL = 0X33;  

  } 
 
 void start_enrx(void)
  {
    UCSRB |=(1<<7); 
  }
   
   void off_enrx(void)
   {

      
     UCSRB &=~(1<<7);
    
   }

  
  char conversion_character_int(void)
  {   
       char add;
      if(READ_DATA==40){add =0;}
      if(READ_DATA==49){add =1;}
      if(READ_DATA==50){add =2;}
      if(READ_DATA==51){add =3;}
      if(READ_DATA==52){add =4;}
      if(READ_DATA==53){add =5;}
      if(READ_DATA==54){add =6;}
      if(READ_DATA==55){add =7;}
      if(READ_DATA==56){add =8;}
      if(READ_DATA==57){add =9;}
      if(READ_DATA==13){add =13;}
     
   return add;
  }
