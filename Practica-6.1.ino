#include <DallasTemperature.h>
#include <OneWire.h>
#include <Wire.h>
#include <RTClib.h>
#include <LiquidCrystal_I2C.h>
const int pindators = 3;
OneWire oneone(pindators);
DallasTemperature sensor(&oneone);
LiquidCrystal_I2C lcd(0x27, 16, 2);
int bomba = 1;
int buz = 5;
RTC_DS3231 reloj;

void setup() {
  Serial.begin(9600);
  sensor.begin();
  pinMode(bomba,OUTPUT);
  pinMode(buz,OUTPUT);
  lcd.init();
  lcd.backlight();
  lcd.clear();
if (! reloj.begin()) {		
 Serial.println("Modulo RTC no encontrado !");
 while (1);			
 }
 reloj.adjust(DateTime(__DATE__, __TIME__));	
}

void loop() {
  sensor.requestTemperatures();
DateTime fecha = reloj.now();	
tone(buz, 1000);  // Establece una frecuencia de 1000 Hz
  delay(1000);            // Espera un segundo
  noTone(buz);      // Detiene el sonido
  delay(1000);            // Espera un segundo
 Serial.print(" ");				
 Serial.print(fecha.hour());
 Serial.print(":");	
 Serial.print(fecha.minute());
 Serial.print(":");	
 Serial.println(fecha.second()); 
  Serial.print(fecha.day());		
 Serial.print("/");				
 Serial.print(fecha.month());		
 Serial.print("/");				
 Serial.print(fecha.year());
 
 delay(1000);	

 if(fecha.minute() == 37){//se ajusta el minuto en que va a regar agua
   lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("se regara agua");
    lcd.setCursor(0, 1);
  lcd.print(sensor.getTempCByIndex(0));
  delay(1000);
  digitalWrite(bomba,LOW);
 }
if(fecha.minute() < 37 ||fecha.minute() > 37){//se pone el rango para ver a que hora no regara
     lcd.clear();
  lcd.setCursor(0, 0); // X, Y
  lcd.print("no ha empezado");
  digitalWrite(bomba,HIGH);
}
 }		

//configuracion de pines 
/*
lcd conectado al modulo
conectar el modulo a los pines SCL y SDA del aruino
o conectar el SCL al pin A4 y el SDA al pin A5
conectar la alimentacion del modulo VCC y GND
conectar el reloj con las mismas instrucciones del modulo de SCL y SDA
conectar la alimentacion del reloj a VCC y GND
conectar el modulo de rele(dependiendo de cual vayan a usar) al pin 1
conecta la alimentacion del modulo de rele a VCC y GND
*/
