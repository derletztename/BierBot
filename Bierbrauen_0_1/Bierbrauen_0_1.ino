#include <math.h>
#include <LiquidCrystal.h>
LiquidCrystal lcd(32, 30, 28, 26, 24, 22);
float temperatur = 0; //Gemessene Temperatur
float Solltemp = 0; //Temperatur Sollwert
float Dauer = 0; //Dauer für die jeweilige Rast festlegen

void setup()
{
Serial.begin (9600); 
lcd.begin(16, 2);

lcd.setCursor(0, 1);
lcd.print("Temperatur:");
pinMode(A0,OUTPUT); //Pin für Motor
digitalWrite(A0, HIGH); //Motor einschalten
}

int TemperaturLesen(){
  temperatur = temp(analogRead(A3));
  return temperatur;
}

float temp(int rawadc)
// Hilfsfunktion zur Umrechnung auf Grad Celsius
{
int r1 = 22000; // Wert des Festen Wiederstandes des sabbungsteiler
int r2 = 22000; // Wiederstand des Thermristors bei 25grad
int b = 3950; // Fixwert aus Datenblatt
float r_akt; // Aktueller Wiederstand
float temp; //Temporäre Variable
float ergebnis; //
float tn = 25; //Basistemperatur in Grad Celsius
// Wiederstand Therm ausrechnen
//Widerstand auf Temperatur umrechnen
tn = tn+273.15; // Basitemperatur auf Kelvin umrechnen
r_akt = ((4.64/(4.64/1023*rawadc))*r1)-r2; //Aktuellen Widerstand ermitteln
temp = b*tn/(b+log10((r_akt/r2))*tn);
temp = temp - 273.15; //Ergebnis in Grad Celsius umwandeln
ergebnis =temp;
return ergebnis;
}

int Heizen(){
  digitalWrite(A0, HIGH);
  //Hier muss der PID Quatsch rein
}  

void Rast()
{
  int k;
  for (int i=0; i <= Dauer; i++){
      k = TemperaturLesen();
      lcd.setCursor(15, 1);
      lcd.print(k);   // aktuelle Temperatur ausgeben
      if ((k > Solltemp-2) && (k < Solltemp+2)) 
      { 
       Heizen();
      }
  }   
}

void loop()
{
  Solltemp = 53;
  Dauer = 120000;
  Rast;
  Solltemp = 63;
  Dauer = 270000;
  Rast;
  Solltemp = 75;
  Dauer = 180000;
  Rast;
  Solltemp = 78;
  Dauer = 120000;
  Rast;
  digitalWrite(A0, LOW);
  delay(600000); //Damit wir auf jedenfall das rechtzeitige Ausschalten schaffen
}
