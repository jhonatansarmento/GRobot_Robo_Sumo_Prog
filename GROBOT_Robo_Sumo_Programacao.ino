//Biblioteca para uso do IR
//#include <IRremote.h>

/* Setup IR
int RECV_PIN = 10;            //Pino 5 infra vermelho
float botao = 0xE17A9C63;     //Substituir pelo hex do botao - Botão de teste (BOTÃO DESLIGA/LIGA Controle Remoto da NET)
float armazena;               //Armazena dados recebidos IR

IRrecv irrecv(RECV_PIN);  
decode_results results;
*/

char data = 0;                //Var Armazena dados recebidos Bluetooth

int porta_rele1 = 7;          //Porta ligada ao pino IN1 do modulo 1
int porta_rele2 = 8;          //Porta ligada ao pino IN2 do modulo 1

int porta_rele3 = 11;         //Porta ligada ao pino IN1 do modulo 2
int porta_rele4 = 12;         //Porta ligada ao pino IN2 do modulo 2

void sstop()
{
   digitalWrite(porta_rele1, LOW);
   digitalWrite(porta_rele2, LOW);
   digitalWrite(porta_rele3, LOW);
   digitalWrite(porta_rele4, LOW); 
}

void setup() 
{
  Serial.begin(9600);
  //irrecv.enableIRIn(); // Inicializa o receptor IR  
  pinMode(porta_rele1, OUTPUT); 
  pinMode(porta_rele2, OUTPUT);
  pinMode(porta_rele3, OUTPUT); 
  pinMode(porta_rele4, OUTPUT);
  sstop();
}

/* Função KILLSWITCH - Retirada do G-Robot 2.0
void kill(int pausa)
{
   digitalWrite(porta_rele1, LOW);
   digitalWrite(porta_rele2, LOW);
   digitalWrite(porta_rele3, LOW);
   digitalWrite(porta_rele4, LOW);
   Serial.println("");
   Serial.println("  PAROU ROBO!!!!!");
   delay(pausa);
   Serial.println("VOLTOU O PROGRAMA");
}
*/

void forward()
{
   digitalWrite(porta_rele1, HIGH);
   digitalWrite(porta_rele2, LOW);

   digitalWrite(porta_rele3, HIGH);
   digitalWrite(porta_rele4, LOW); 
}

void back()
{
   digitalWrite(porta_rele1, LOW);
   digitalWrite(porta_rele2, HIGH);
   
   digitalWrite(porta_rele3, LOW);
   digitalWrite(porta_rele4, HIGH); 
}

void left()
{
   digitalWrite(porta_rele1, LOW);
   digitalWrite(porta_rele2, HIGH);
   
   digitalWrite(porta_rele3, HIGH);
   digitalWrite(porta_rele4, LOW); 
}

void right()
{
   digitalWrite(porta_rele1, HIGH);
   digitalWrite(porta_rele2, LOW);
  
   digitalWrite(porta_rele3, LOW);
   digitalWrite(porta_rele4, HIGH); 
}


void loop()
{
  
/* Função para Ativar IR como KILLSWITCH - Retirada do G-Robot 2.0
  //Ativando INFRA VERMELHO
  if (irrecv.decode(&results))
  {
    Serial.print("Valor lido : ");  
    Serial.println(results.value, HEX);  
    armazena = results.value;

    irrecv.resume(); //Le o próximo valor

    if(armazena == botao)
      kill(10000);
  }
*/
  
  //Ativando BLUETOOTH
  if(Serial.available() > 0)  //Aguarda receber sinal de entrada do BT
  {
    data = Serial.read();     //Lê os dados recebidos bluetooth
  //Serial.print(data);       //Imprime valor para o monitor serial - Debug

    if (data == 'S') 
    {
       //Serial.println("STOP!");              
       sstop();
    }

    if (data == 'F') 
    {
       //Serial.println("foward");              
       forward();
    }
            
    if (data == 'B')
    {
        //Serial.println("back");                
        back();
    }

    if (data == 'L' || data == 'G' || data == 'J')
    { 
        //Serial.println("left");                
        left();
    }

    if (data == 'R' || data == 'I' || data == 'H')
    {
       //Serial.println("right");             
       right();
    }
  }
}
