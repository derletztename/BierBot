#include <math.h>
#include <LiquidCrystal.h>
LiquidCrystal lcd(32, 30, 28, 26, 24, 22);
float temperatur =0;

void setup()
{
Serial.begin (9600); 
lcd.begin(16, 2);
lcd.print("Zuckerraststufe");
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

/*int Heizen(){
  digitalWrite(A0, HIGH);
  delay(250);
}  
*/

void loop()
{
int k;
k = TemperaturLesen();
 Serial.println(k); // Temperatur auch am Rechner lesbar machen
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
 lcd.setCursor(15, 1);
 lcd.print(k);   // aktuelle Temperatur ausgeben
 //Motor steuern
 
 //Heizen
/*if ((k > 25) && (k < 30)) 
 { 
  Heizen();
 }
*/
// delay(500);
}
