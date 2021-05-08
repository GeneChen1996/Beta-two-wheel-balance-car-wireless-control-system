#include <RHReliableDatagram.h>
#include <RH_RF95.h>
#include <SPI.h>

#define CLIENT_ADDRESS 1
#define SERVER_ADDRESS 2
#define SlidePot_PIN     0
#define JoyStick_Y_PIN     1 
#define JoyStick_X_PIN     2

#define RFM95_CS 10
#define RFM95_RST 9
#define RFM95_INT 2
#define RF95_FREQ 915.0
RH_RF95 rf95(RFM95_CS, RFM95_INT);


RHReliableDatagram manager(rf95, CLIENT_ADDRESS);
uint8_t joystick[5];
uint8_t Beta_shutdown[4];
uint8_t Robotic_arm[4];
uint8_t ASM[4];  


// Dont put this on the stack:
uint8_t buf[RH_RF95_MAX_MESSAGE_LEN];


int tact_switch = 0;

int c1=8; //ASM
int c2=7; //LoRa遙控模式
int c3=6; //Robotic arm

void setup() 
{

  pinMode(c1, INPUT_PULLUP);
  pinMode(c2, INPUT_PULLUP);
  pinMode(c3, INPUT_PULLUP);//撥動開關 程序控制
  
  pinMode(4, INPUT_PULLUP);//按鈕腳位

  pinMode(RFM95_RST, OUTPUT); //設定LORA pin腳
  digitalWrite(RFM95_RST, HIGH);


  Serial.begin(9600);
  while (!Serial) ; 
  if (!manager.init()){
    Serial.println("init failed");
  }
    


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
  int pg1 = digitalRead(c1); //ASM
  int pg2 = digitalRead(c2); //LoRa遙控模式
  int pg3 = digitalRead(c3); //Robotic arm
  
/////////////////////////////////////////////LoRa遙控
  if(pg2 == LOW)
  {  
  int sensorVal = digitalRead(4);
  if(sensorVal == LOW)
  {
  
  sensorVal = digitalRead(4);
  tact_switch =+ 1;
  Serial.println("觸動開關按下");
  
  Beta_shutdown[0]=66;//機台編號 beta = 66
  Beta_shutdown[1]=2;//控制模式 轉彎辨識 = 1,  遙控模式 = 2, 磁帶感應 = 3, 主機搜尋 = 4
  Beta_shutdown[2]=2;//系統編碼 遙控模式「質量塊移動 = 1, Beta停機腳柱程序 = 2」, 磁帶導引「一般模式＝1」, 轉彎辨識「一般模式＝1」,  
  Beta_shutdown[3]=1;//Beta停機腳柱程序 valB 1  開關切換 = 1

  
  rf95.send(Beta_shutdown, sizeof(Beta_shutdown));
  rf95.waitPacketSent();

  
  while (tact_switch==1) 
  {
    sensorVal = digitalRead(4);
    
    if(sensorVal == HIGH)
    {
      Serial.println("觸動開關放開");
      
      delay(300);
      Serial.println("-----------");
      tact_switch = 0;
      break;
      
    }
    
  }

 }
 
 else{ 
 // Serial.println("Reading joystick values ");
  
  // Read Joystick values and map to values of 0 - 255
  joystick[0] = 66; //機台編號 beta = 66
  joystick[1] = 2; //控制模式 ASM ＝ 1,  遙控模式＝ 2, 機械手臂 ＝ 3,
  joystick[2] = 1; //系統編碼 質量塊移動 = 1, Beta停機腳柱程序 = 2 ,
  joystick[3] = map(analogRead(SlidePot_PIN), 0, 1023, 0, 255);
  joystick[4] = map(analogRead(JoyStick_X_PIN), 0, 1023, 0, 255);

 
 
  //Display the joystick values in the serial monitor.
  Serial.println("-----------");
  Serial.println("LoRa遙控模式");
  Serial.print("x:");
  Serial.println(joystick[3]);
  Serial.print("y:");
  Serial.println(joystick[4]);
  //Serial.println("Sending to rf95_reliable_datagram_server");
    
  // Send a message to manager_server
  
  rf95.send(joystick, sizeof(joystick));            
  rf95.waitPacketSent();

 }
 }



 if(pg1 == LOW)///////////////////////////////ASM
  {
    Serial.println("ASM");
    ASM[0] = 66;
    ASM[1] = 1;//控制模式 ASM ＝ 1,  遙控模式＝ 2, 機械手臂 ＝ 3,
    ASM[2] = 1;//系統編碼 正常模式 
    ASM[3] = map(analogRead(SlidePot_PIN), 0, 1023, 0, 255);
    
    rf95.send(ASM, sizeof(ASM));
    rf95.waitPacketSent();

  }

 if(pg3 == LOW)///////////////////////////////mode3
  {
    Serial.println("Robotic arm");
    Robotic_arm[0] = 66;
    Robotic_arm[1] = 3;//控制模式 ASM ＝ 1,  遙控模式＝ 2, 機械手臂 ＝ 3,
    Robotic_arm[2] = 1;//系統編碼 正常模式 
    Robotic_arm[3] = map(analogRead(SlidePot_PIN), 0, 1023, 0, 255);
    
//    Robotic_arm[0] = 66;
//    Robotic_arm[1] = 3;//控制模式 ASM ＝ 1,  遙控模式＝ 2, 機械手臂 ＝ 3,
//    Robotic_arm[2] = 1;//系統編碼 正常模式 
//    Robotic_arm[3] = map(analogRead(JoyStick_X_PIN), 0, 1023, 0, 255);
//    Robotic_arm[4] = map(analogRead(JoyStick_Y_PIN), 0, 1023, 0, 255);
//    Robotic_arm[5] = map(analogRead(SlidePot_PIN), 0, 1023, 0, 255);
    
    
    
    rf95.send(Robotic_arm, sizeof(Robotic_arm));
    rf95.waitPacketSent();
    
  }

  delay(30);
}
