const int In1 = 7;//左前馬達˙
const int In2 = 6;
const int In3 = 5;//左後馬達
const int In4 = 4;
const int in1 = 14;//右前馬達
const int in2 = 15;
const int in3 = 16;//右後馬達
const int in4 = 17;

const int pin_gate_LFU = 22;//左前上 開關機光閘
const int pin_gate_RFU = 30;//右前上
const int pin_gate_LBU = 24;//左後上
const int pin_gate_RBU = 32;//右後上


const int pin_gate_LFD = 26;//左前下 下極限
const int pin_gate_RFD = 34;//右前下
const int pin_gate_LBD = 28;//左後下
const int pin_gate_RBD = 36;//右後下


int val_gate_LFU = 0;//左前上 光閘值
int val_gate_RFU = 0;//右前上
int val_gate_LBU = 0;//左後上
int val_gate_RBU = 0;//右後上


int val_gate_LFD = 0;//左前下
int val_gate_RFD = 0;//右前下
int val_gate_LBD = 0;//左後下
int val_gate_RBD = 0;//右後下



int RELAYpin1 = 11;
int RELAYpin2 = 12;

const int xiaomi_state = 8;// 小米腳位
int xiaomi = 0;


void mstopLF()//左前腳柱馬達 停止動作///////////////////////////////////////左前
{
  digitalWrite(In1, LOW);
  digitalWrite(In2, LOW);  
}
void mfrontLF()//左前腳柱馬達 往下
{
  digitalWrite(In1, HIGH);
  digitalWrite(In2, LOW);
}
void mbackLF()//左前腳柱馬達 往上
{
  digitalWrite(In1, LOW);
  digitalWrite(In2, HIGH);
}


void mstopLB()//左後腳柱馬達 停止動作///////////////////////////////////////左後
{
  digitalWrite(In3, LOW);
  digitalWrite(In4, LOW);
}
void mfrontLB()//左後腳柱馬達 往下
{
  digitalWrite(In3, HIGH);
  digitalWrite(In4, LOW);
}
void mbackLB()//左後腳柱馬達 往上
{
  digitalWrite(In3, LOW);
  digitalWrite(In4, HIGH);
}


void mstopRF()//右前腳柱馬達 停止動作///////////////////////////////////////右前
{
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
}
void mfrontRF()//右前腳柱馬達 往下
{
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
}
void mbackRF()//右前腳柱馬達 往上
{
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
}


void mstopRB()//右前腳柱馬達 停止動作//////////////////////////////////////右後
{
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}
void mfrontRB()//右前腳柱馬達 往下
{
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}
void mbackRB()//右前腳柱馬達 往上
{
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
}


void mstopSet(){/////////////////////////////////////馬達組合
  digitalWrite(In1, LOW);
  digitalWrite(In2, LOW);
  digitalWrite(In3, LOW);
  digitalWrite(In4, LOW);
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}
void mfrontSet(){
  digitalWrite(In1, HIGH);
  digitalWrite(In2, LOW);
  digitalWrite(In3, HIGH);
  digitalWrite(In4, LOW);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}
void mbackSet(){
  digitalWrite(In1, LOW);
  digitalWrite(In2, HIGH);
  digitalWrite(In3, LOW);
  digitalWrite(In4, HIGH);
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
}




void setup() {
  pinMode(In1, OUTPUT);
  pinMode(In2, OUTPUT);
  pinMode(In3, OUTPUT);
  pinMode(In4, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(xiaomi_state, OUTPUT);//小米底盤腳位
  pinMode(RELAYpin1, OUTPUT);
  pinMode(RELAYpin2, OUTPUT);  
  digitalWrite(RELAYpin1, LOW);
  digitalWrite(RELAYpin2, LOW);
  xiaomi = 0; //等待訊號
  Serial.begin(9600);
  delay(10);
}

void loop() {

  
  if(Serial.available())//////////////////////////////////////////////////////////接收訊號
  {
    String  switch_val= Serial.readStringUntil('\n');
    
    
    if(switch_val=="valB")
    {
    
    xiaomi = 1;  
    delay(100);
    }
  
  }
  
  
  while(xiaomi == 1 && digitalRead(xiaomi_state)==0)/////////////////////////////////////開機程序
  {
     //val_gate_LFU = digitalRead(pin_gate_LFU);//讀取左上光閘pin腳數值
     //val_gate_RFU = digitalRead(pin_gate_RFU);//讀取右上光閘pin腳數值
     val_gate_LBU = digitalRead(pin_gate_LBU);//讀取左上光閘pin腳數值
     val_gate_RBU = digitalRead(pin_gate_RBU);//讀取右上光閘pin腳數值
     
//    if (val_gate_LFU == HIGH) //左前上未遮斷光閘 馬達上升
//     {  
//      mbackLF();      
//      delay(10);      
//     }
//     else
//     {
//       mstopLF();
//       delay(10);
//      }
//    
//    if(val_gate_RFU == HIGH)//右前上未遮斷光閘 馬達上升
//    {
//     mbackRF();      
//      delay(10); 
//    }
//    else
//    {
//      mstopRF();
//      delay(10);
//      }

    if (val_gate_LBU == HIGH) //左後上未遮斷光閘 馬達上升
     {  
      mbackLB();      
      delay(10);      
     }
     else
     {
       mstopLB();
       delay(10);
      }
    
    if(val_gate_RBU == HIGH)//右後上未遮斷光閘 馬達上升
    {
     mbackRB();      
      delay(10); 
    }
    else
    {
      mstopRB();
      delay(10);
      }

        
            
    if (val_gate_LBU == LOW && val_gate_RBU == LOW)
     {
      mstopSet();
      delay(100);
      digitalWrite(RELAYpin2, HIGH);  //扭力高電位(扭力低)
      delay(1000);
      digitalWrite(RELAYpin1, HIGH);  //開機
      delay(400);
      digitalWrite(RELAYpin1, LOW);  //斷掉開關
      delay(300);
      digitalWrite(RELAYpin2, LOW);  //光閘低電位(扭力高)
      delay(200);
      xiaomi = 0;
      
      mbackLF();
      mbackRF();
      delay(700);
      mstopSet();
      delay(200);
      
      mbackSet();
      delay(800);
      mstopSet();
      delay(500);
      break;             
    }

  }
  
  
  
  while(xiaomi == 1 && digitalRead(xiaomi_state)==1)/////////////////////////////////////////關機程序
  {
    val_gate_LFU = digitalRead(pin_gate_LFU);//讀取左上光閘pin腳數值
    val_gate_RFU = digitalRead(pin_gate_RFU);//讀取右上光閘pin腳數值
    val_gate_LBU = digitalRead(pin_gate_LBU);//讀取左上光閘pin腳數值
    val_gate_RBU = digitalRead(pin_gate_RBU);//讀取右上光閘pin腳數值
    val_gate_LFD = digitalRead(pin_gate_LFD);//讀取左下光閘pin腳數值
    val_gate_RFD = digitalRead(pin_gate_RFD);//讀取右下光閘pin腳數值
     
    if (val_gate_LFU == HIGH) //左前上未遮斷光閘 馬達下降
     {  
      mfrontLF();      
      delay(10);      
     }
     else
     {
       mstopLF();
       delay(10);
      }
    
    if(val_gate_RFU == HIGH)//右前上未遮斷光閘 馬達下降
    {
     mfrontRF();      
      delay(10); 
    }
    else
    {
      mstopRF();
      delay(10);
      }

    if (val_gate_LBU == HIGH) //左後上未遮斷光閘 馬達下降
     {  
      mfrontLB();      
      delay(10);      
     }
     else
     {
       mstopLB();
       delay(10);
      }
    
    if(val_gate_RBU == HIGH)//右後上未遮斷光閘 馬達下降
    {
     mfrontRB();      
      delay(10); 
    }
    else
    {
      mstopRB();
      delay(10);
      }



    if (val_gate_LFD == HIGH) //左前下未遮斷光閘 馬達下降
     {  
      mfrontLF();      
      delay(10);      
     }
     else
     {
       mstopLF();
       delay(10);
      }
    
    if(val_gate_RFD == HIGH)//右前下未遮斷光閘 馬達下降
    {
     mfrontRF();      
      delay(10); 
    }
    else
    {
      mstopRF();
      delay(10);
      }



      
    if(val_gate_LFD == LOW && val_gate_RFD == LOW && val_gate_LBU == LOW && val_gate_RBU == LOW)
     {
      mstopSet();
      delay(100);
//      mfrontLF();
//      mfrontRF();
//      delay(350);
//      mstopSet();
//      delay(100);
      digitalWrite(RELAYpin2, HIGH);  //扭力高電位(扭力低)
      delay(1000);
      digitalWrite(RELAYpin1, HIGH);  //關機
      delay(200);
      digitalWrite(RELAYpin1, LOW);  //斷掉開關
      delay(300);
      digitalWrite(RELAYpin2, LOW);  //光閘低電位(扭力高)
      delay(200);
      xiaomi = 0;
      mstopSet();
      delay(500);
      while(1)
      {
//      val_gate_LFD = digitalRead(pin_gate_LFD);//讀取左下光閘pin腳數值
//      val_gate_RFD = digitalRead(pin_gate_RFD);//讀取右下光閘pin腳數值
      val_gate_LBD = digitalRead(pin_gate_LBD);//讀取左下光閘pin腳數值
      val_gate_RBD = digitalRead(pin_gate_RBD);//讀取右下光閘pin腳數值
//    if (val_gate_LFD == HIGH) //左前下未遮斷光閘 馬達下降
//     {  
//      mfrontLF();      
//      delay(10);      
//     }
//     else
//     {
//       mstopLF();
//       delay(10);
//      }
//    
//    if(val_gate_RFD == HIGH)//右前下未遮斷光閘 馬達下降
//    {
//     mfrontRF();      
//      delay(10); 
//    }
//    else
//    {
//      mstopRF();
//      delay(10);
//      }

    if (val_gate_LBD == HIGH) //左後下未遮斷光閘 馬達下降
     {  
      mfrontLB();      
      delay(20);      
     }
     else
     {
       mstopLB();
       delay(10);
      }
    
    if(val_gate_RBD == HIGH)//右後下未遮斷光閘 馬達下降
    {
     mfrontRB();      
      delay(20); 
    }
    else
    {
      mstopRB();
      delay(10);
      }
      
      if(val_gate_LFD == LOW && val_gate_RFD == LOW && val_gate_LBD == LOW && val_gate_RBD == LOW)
     {
      mstopSet();
      delay(300);
      break;
     }
    }
    }
}

  delay(10);  

}
