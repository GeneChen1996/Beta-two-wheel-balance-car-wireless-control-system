#include <RHReliableDatagram.h>
#include <RH_RF95.h>
#include <SPI.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);  //設定LCD位置0x27,設定LCD大小為16*2

#define CLIENT_ADDRESS 1
#define SERVER_ADDRESS 2



#define RH_ASK_ARDUINO_USE_TIMER2
#define RFM95_CS 10
#define RFM95_RST 9
#define RFM95_INT 2
#define RF95_FREQ 915.0
RH_RF95 rf95(RFM95_CS, RFM95_INT);
RHReliableDatagram manager(rf95, SERVER_ADDRESS);

uint8_t buf[RH_RF95_MAX_MESSAGE_LEN];
uint8_t Xnew;
uint8_t Xold = 128;

uint8_t Ynew;
uint8_t Yold = 128;
unsigned long recv_s_count = 0;
unsigned int recv_f_count = 0;
int x_axis=0;
int y_axis=0;
int z_axis=0;

void setup() 
{

  pinMode(RFM95_RST, OUTPUT); //設定LORA pin腳
  digitalWrite(RFM95_RST, HIGH);

  Serial.begin(9600);
  while (!Serial) ; // Wait for serial port to be available
  if (!manager.init())
    Serial.println("init failed");

  Serial.println("Arduino LoRa TX Test!");
  
  // manual reset
  digitalWrite(RFM95_RST, LOW);
  delay(10);
  digitalWrite(RFM95_RST, HIGH);
  delay(10);

  while (!rf95.init()) { //如果初始設定失敗
    Serial.println("LoRa radio init failed");
    
  
    while (1);
  }
  Serial.println("LoRa radio init OK!");

  if (!rf95.setFrequency(RF95_FREQ)) { //如果設定頻率失敗 
    Serial.println("setFrequency failed");
    while (1);
  }
  Serial.print("Set Freq to: "); 
  Serial.println(RF95_FREQ);
  
  rf95.setTxPower(23, false); //更改TX傳輸功率 5-23
  rf95.setSpreadingFactor(7);
  rf95.setSignalBandwidth(250000);
  rf95.setCodingRate4(5);
  
}



void loop()
{
  
     uint8_t buf[RH_RF95_MAX_MESSAGE_LEN]; //暫存讀取值
     uint8_t len = sizeof(buf);
 
  if (rf95.waitAvailableTimeout(1000))
    {    
      if (rf95.recv(buf, &len))//當lora接收時
       {
       if (buf[0] == 66)//機台確認
       { 
         
         if (buf[1] == 1)//ASM
          { 
            Serial.println("ASM");
                  if(buf[2] == 1)
                  {
                  Xnew = buf[3];
                  if(Xnew != Xold )
                     {
                        Serial.print(" X = ");
                        Serial.println(Xnew);  
                        Xold = Xnew;          
                     }                                                       
                  }                  
          }
 
          
         if (buf[1] == 2)//遙控模式
          {      
            Serial.println("LoRa");  
                  if(buf[2] == 1)//系統編碼 質量塊移動 = 1
                  {
                  Xnew = buf[3];
                  if(Xnew != Xold )
                     {  
                        Serial.print(" X = ");
                        Serial.println(Xnew);  
                        Xold = Xnew;          
                     } 
                  Ynew = buf[4];
                  if(Ynew != Yold )
                     {
                        Serial.print(" Y = ");
                        Serial.println(Ynew);  
                        Yold = Ynew;          
                     }                                                                              
                  }
          
                  if(buf[2] == 2)//系統編碼 Beta停機腳柱程序 = 2 ,
                  {
          
                  Serial.println(" valB +1 ");
                                                                                                  
                  }
          }

          if (buf[1] == 3)//mode3
          { 
           Serial.println("mode3");
           if(buf[2] == 1)
                  {
                  Xnew = buf[3];
                  if(Xnew != Xold )
                     {
                        Serial.print(" X = ");
                        Serial.println(Xnew);  
                        Xold = Xnew;          
                     }                                                       
                  } 
//                  if(buf[2] == 1)
//                  {
//                   x_1=buf[3];
//                   y_1=buf[4];
//                   z_1=buf[5];
//                   if(y_1>168){
//                    Serial.println("YMR -1");
//                    }
//                    if(y_1<88){
//                    Serial.println("YMR 1");
//                    }
//                    if(z_1>168){
//                    Serial.println("ZMR -1");
//                    }
//                    if(z_1<88){
//                    Serial.println("ZMR 1");
//                    }
//                    
//                    if(x_1>168){
//                    Serial.println("XMR 1");
//                    }
//                    if(x_1<88){
//                     Serial.println("XMR -1");
//                    }                                                                             
//                 }                  
          }        
      }
       
    }

    }
     else
    {  
  
      Serial.println("stop");
      Serial.println(" X = 128");      
      Serial.println(" Y = 128");
  
    }

}
