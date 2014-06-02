#include <math.h>
#include <LiquidCrystal.h>
LiquidCrystal lcd(32, 30, 28, 26, 24, 22);
float temperatur = 0; //Gemessene Temperatur
float Solltemp = 0; //Temperatur Sollwert
float Dauer = 0; //Dauer für die jeweilige Rast festlegen
int led_gruen = 13; //Pin grüne LED
int led_rot = 11; //Pin rote LED

long timer1 = 0; //Timer für die verschiedenen Stufen
long timer2 = 0;
long timer3 = 0;
long timer4 = 0;
long timer5 =0;
long startTime = 0;

void setup()
{
Serial.begin (9600); //Baudrate für Kommunikation mit Rechner
lcd.begin(16, 2);
lcd.setCursor(0, 1);
lcd.print("Temperatur:");
pinMode(A0,OUTPUT); //Pin für Motor
pinMode(led_gruen, OUTPUT); //Pin grüne LED als Output
pinMode(led_rot, OUTPUT); //Pin rote LED als Output
digitalWrite(A0, HIGH); //Motor einschalten
}

int TemperaturLesen(){ //Funktion zum Temperatur auslesen
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

int Heizen(){ //Funktion zum Heizen
  digitalWrite(A0, HIGH);
  //Hier muss der PID Quatsch rein
  digitalWrite(led_rot, HIGH);
  }  

void Rast() //Funktion für die jeweiligen Raststufen
{
  int k; //Variable zum reinspeichern
  for (int i=0; i <= Dauer; i++){ //Schleife mit IF-Abfrage
      k = TemperaturLesen();
      lcd.setCursor(15, 1);
      lcd.print(k);   // aktuelle Temperatur ausgeben
      if ((k < Solltemp)) //&& (k < Solltemp+2)) 
      { 
       Heizen();
       delay(500);
      } 
      else {
      digitalWrite(A0, LOW);
      digitalWrite(led_rot, LOW);
      }
  }   
}


void loop() //HauptSchleife
{
while (timer1 < 120000)  //schleife für die erste Stufe
(
  Solltemp=53; //aktuelle Solltemperatur
  iw=temp; //aktuelle Temperatur
  diff=sw-iw; //differenz zwischen sollwert und istwert

  if (diff <0)
    {
    startTime= millis(); // aktuelle Zeit merken
    }
    
//jetzt Stellgröße berechnen mit dem PID.....kommt noch

Timer1 = millis() - startTime ; // aktuelle SchleifenZeit
// solange timer1 kleiner als 120000 ist wird diese Schleife durchlaufen
//wenn die Zeit erreicht ist, dann wird die nächste Raststufe gestartet mit einer neuen Schleife
// test anna


)


  Solltemp = 53; //Temperatur setzen
  Dauer = 120000; //Dauer setzen
  
  Rast; //Proteaserast
  Solltemp = 63;
  Dauer = 270000;
  Rast; //Maltoserast
  Solltemp = 75;
  Dauer = 180000;
  Rast; //Verzuckerungsrast
  Solltemp = 78;
  Dauer = 120000;
  Rast; //Abmaischen
  digitalWrite(A0, LOW);
  digitalWrite(led_gruen, HIGH);
  delay(600000); //Damit wir auf jedenfall das rechtzeitige Ausschalten schaffen
}
