#include <IRCom.h>
#include <SoftwareSerial.h>

#include <SPI.h>
#include <SD.h>

# define rxPin 2
# define txPin 3

SoftwareSerial ir(rxPin,txPin);

char buffer_str[10];

File myFile;
int count=0;
void setup(){
  setIRpin(9);
 
  ir.begin(2400);
  //Serial.begin(9600);//band_1
  Serial.begin(115200);//band_2
  get_user();
  
}

void loop(){
    if(ir.available()>0) {
    receiverIR();
   }   
   else {   
    transmitIR();
   }
   delay(10);
}

void receiverIR(){
     char val = ir.read();
     if(val>0){
     Serial.print(val); 
    }
}

void transmitIR(){
  int j=0;
  do{
  ir.print(buffer_str[j]);
  j++;
  }while(j<10);
  ir.println();
}
   
int get_user(){
  int i=0;
  if (!SD.begin(4)) {
  }
  myFile = SD.open("test.txt");
  if (myFile) {
    while (myFile.available()) {
     buffer_str[i]=(char)myFile.read();
     i++;  
  }
     myFile.close();
  } 
}

