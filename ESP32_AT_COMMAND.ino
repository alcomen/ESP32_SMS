
#define TINY_GSM_MODEM_SIM800
#include <TinyGsmClient.h>

const int GSM_BAUD_RATE = 9600;
const int RX_PIN = 4, TX_PIN = 2;

#define numeroComando "+55xxxxxxxx" //numero para validacao e inicio dos comandos.

bool temSMS = false;
String telefoneSMS = "+55xxxxxxxxxx";
String dataHoraSMS;
String mensagemSMS;
String comandoGSM = "";
String ultimoGSM = "";

//void leGSM();
void enviaSMS(String telefone, String mensagem);
void configuraGSM();

HardwareSerial SerialGSM(1);

TinyGsm modemGSM(SerialGSM);

int incomingByte = 0; 

void setup() {
  Serial.begin(115200);
  SerialGSM.begin(GSM_BAUD_RATE, SERIAL_8N1, RX_PIN, TX_PIN, false);
  delay(7000);
  configuraGSM();
  delay(1000);
   enviaSMS(telefoneSMS, "LED ligado!");
/*  SerialGSM.print("AT+CMGF=1\r");
  delay(1000);
  SerialGSM.print("AT+CMGS=\"xxxxxxxx\"\r");
  delay(1000);
  SerialGSM.println("Your message to send");
  SerialGSM.print("\r");
  delay(1000);
  SerialGSM.println((char)26);
  SerialGSM.println();
*/  //SerialGSM.print("\r");

}

void loop() {
  if(SerialGSM.available() > 0)
  {
    incomingByte = SerialGSM.read();
    
    Serial.print((char)incomingByte);
  }

  if(Serial.available() > 0)
  {
    incomingByte = Serial.read();

    if(incomingByte == 'y') SerialGSM.write((char)26);else
    SerialGSM.print((char)incomingByte);
  }
}

/*
 * AT+CMGF=1
 * AT+CMGR=1 { AT+CMGD=1,4 AT+CNMI=2,2,0,0,0 AT+CM
 * AT+CMGS="12981151296"
 */

 void enviaSMS(String telefone, String mensagem) {
  SerialGSM.print("AT+CMGS=\"" + telefone + "\"\n");
  SerialGSM.print(mensagem + "\n");
  SerialGSM.print((char)26); 
}

void configuraGSM() {
   SerialGSM.print("AT+CMGF=1\n;AT+CNMI=2,2,0,0,0\n;ATX4\n;AT+COLP=1\n"); 
}
