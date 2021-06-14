#include<Wire.h>
#include <SoftwareSerial.h>
#define Addr 0x4A

//komunikasi serial
SoftwareSerial espSerial(5, 6);
String str;
float luminance;
int analogPin = A0; // pin arduino yang terhubung dengan pin S modul sensor tegangan
 
float Vmodul = 0.0; 
float hasil = 0.0;
float R1 = 30000.0; //30k
float R2 = 7500.0; //7500 ohm resistor, 
int value = 0;


 //=====Variabel SENSOR ARUS========
 const int pinADC = A1;
  int sensitivitas = 185; //tegantung sensor arus yang digunakan, yang ini 5A
  int nilaiadc= 00;
  int teganganoffset = 2500; //nilai pembacaan offset saat tidak ada arus yang lewat
  double tegangan = 00;
  double nilaiarus = 00;
  //===============================================//
 
void setup()
{
   pinMode(analogPin, INPUT);
   Serial.begin(9600);
   espSerial.begin(115200);
   Wire.begin();
   Wire.beginTransmission(Addr);
   Wire.write(0x02);
   Wire.write(0x40);
   Wire.endTransmission();
   Serial.println("Galih Arya Jaya");
  }


void data_olah(){
  nilaiadc = analogRead(pinADC);
  tegangan = (nilaiadc / 1024.0) * 5000;
  nilaiarus = ((tegangan - teganganoffset) / sensitivitas);

  Serial.print("Nilai ADC yang terbaca = " );
  Serial.print(nilaiadc);
 
  Serial.print("\t tegangan (mV) = ");
  Serial.print(tegangan,3);
 
  Serial.print("\t Arus = ");
  Serial.println(nilaiarus,3);
}

    void fungsi_tegangan(){
        //================SENSOR TEGANGAN========================
       //arduino moco sensor tegangan
       value = analogRead(analogPin);
    
       //rumus pembacaan sensor
       Vmodul = (value * 5.0) / 1024.0;
       // hasil nilai 
       hasil = Vmodul / (R2/(R1+R2));
     
      Serial.print("Tegangan keluaran modul = ");
      Serial.print(Vmodul,2);
      Serial.print("volt");
      Serial.print(", Hasil pengukuran = ");
      // hasil pembacaan sensor 
      Serial.print(hasil,2);
      Serial.println("volt");
      delay(500);
      //=========================================================//
 
    }

    void lux(){
        //==========SENSOR MX 44009 ==================
  unsigned int data[2];
  Wire.beginTransmission(Addr);
  Wire.write(0x03);
  Wire.endTransmission();

  // Request 2 bytes of data
  Wire.requestFrom(Addr, 2);

  if (Wire.available() == 2)
  {
    data[0] = Wire.read();
    data[1] = Wire.read();
  }

  // Convert the data to lux
    int exponent = (data[0] & 0xF0) >> 4;
    int mantissa = ((data[0] & 0x0F) << 4) | (data[1] & 0x0F);
     luminance = pow(2, exponent) * mantissa * 0.045;

    Serial.print("Ambient Light luminance :");
    Serial.print(luminance);
    Serial.println(" lux");
    delay(500);

    //=============================================//

    }

 
void loop()
{ 

    //sensor arus
      data_olah();
    //sensor tegangan
      fungsi_tegangan();
    //sensor lux
      lux();    
      //kirim ke nodemcu
      str =String("*")+String(hasil)+String(",")+String(nilaiarus)+String(",")+String(luminance)+String("#");
      espSerial.println(str);

}
