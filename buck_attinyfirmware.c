#include <Arduino.h>
#include <ssd1306xled.h>
#include"image.h"
const uint8_t fill[] PROGMEM={0xff};
const uint8_t empty[] PROGMEM ={0x00};
 unsigned long now;
 unsigned long pre=0;
 signed int count=0;
 float kp=4;
 int gauge_1;
 int gauge_2;
 int scale =3;
 int threshold=900;
 int voltage;
 int pre_voltage=0;
 int voltage_diff;
 int value;
void setup(){
  pinMode(PB1,OUTPUT);
  pinMode(PB3,INPUT);
  pinMode(PB4,INPUT);
  SSD1306.ssd1306_init();
   SSD1306.ssd1306_draw_bmp(0, 0, 128, 8, logo);
  }
void loop(){
  
   gauge_1=map(analogRead(A2),0,156,0,55);
   up_down();
   draw_1();
   gauge_2=map(voltage_diff,0,50,0,23);
   draw_2();
   
}
 void draw_1(){ 
  for(int i=0;i<55;i++){
    if(i<gauge_1){
     SSD1306.ssd1306_draw_bmp(42+i, 3, 42+i+1, 4, fill); 
    }
    else{
      SSD1306.ssd1306_draw_bmp(42+i, 3, 42+i+1, 4, empty);
    }
    
    }
    }
    void draw_2(){
   for(int i=0;i<23;i++){
     if(i<gauge_2){
     SSD1306.ssd1306_draw_bmp(6+i, 4, 6+i+1, 5, fill); 
    }
    else{
      SSD1306.ssd1306_draw_bmp(6+i, 4, 6+i+1, 5, empty);
    }
   }
  }

   void up_down(){
    now=millis();
    if(analogRead(PB3)>threshold&&((now-pre)>250)){
       count++;
      updown();
      regulate();
     
      pre=now;
    }
    if((analogRead(PB3)<threshold && analogRead(PB3)>30)&&(now-pre>=250)){
       count--;
      updown();
      regulate();
      pre=now;
    }
    else if(analogRead(PB3)>=0 && analogRead(PB3)<30){
      regulate();
      
    }
   }
   void updown(){
     value=128-(count*scale);
    if(value<0){
      value=0;
    }
    else if(value>255){
      value=255;
    }
    analogWrite(PB1,value);
    delay(100);
   }
   void regulate(){
    voltage=analogRead(A2);
    voltage_diff=voltage-pre_voltage;
    pre_voltage=voltage;
    value=value+(kp*voltage_diff);
   }
   
