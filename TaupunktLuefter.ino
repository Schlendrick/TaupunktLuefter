/*
  Automatische Kellerentlüftung
  //
  Programmbeschreibung
  Das Programm erlaubt das automatische Entlüften von Räumen mittels eines Arduino UNO und
  den Luftfeuchte/Temperatursensoren Model DHT22
  //
  created 11 Feb 2017
  by Thomas Gemander (DJ9ZZZ) tom@dj9zzz.de
  and Jan Holdstein holdstein1976@googlemail.com
  //
  edit 9 Fec 2018
  Patrick Dörig : Umbau auf zwei DHT22 Sensoren, ohne Lüften , ohne Web anbindung
  //
  Wir übernehmen keine Garantie für die Funktion der Softwar, Nutzung auf eigene Gefahr.
  //
  This example code is in the public domain, unter the Terms off GPLv3.0
*/
#include <DHT.h> // Einbinden der Bibliotheken DHT, Mathematik, oneWire und liquid crystal
#include "math.h"
#include "Wire.h"
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); // Set the LCD address to 0x27 for a 16 chars and 2 line display
#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321

const byte DHTPIN1 = 3; // festlegen DatenPin 3 für den ersten Sensor , dieser ist der Aussensensor
const byte DHTPIN2 = 5; // festlegen DatenPin 5 für den zweiten Sensor , dieser ist der Innenensensor

const byte bLuefter1 = 7; // festlegen AusgangsPin 7 für den Lüfter 1
const byte bLuefter2 = 8; // festlegen AusgangsPin 8 für den Lüfter 2

const float fTauPSchwMax = 2.3; // festlegen der Taupunktschwelle, ist die maximale Differenz zwischen TPunkt innen und aussen
const float fTauPSchwMin = 1.0; // festlegen der Taupunktschwelle, ist die minimale Differenz zwischen TPunkt innen und aussen
const float fTempSchwMax = 30.0; // Raum Temperatur welche nicht überschritten werden darf
const float fTempSchwMin = 4.0; // Raum Temperatur welche nicht unterschritten werden darf


boolean boLuefterAnAus1 = true; // festlegen Schaltvariable zum Ein-, Ausschalten des Lüfters im Partykeller
boolean boLuefterAnAus2 = true; // festlegen Schaltvariable zum Ein-, Ausschalten des Lüfters im Waschkeller

float fTPktAussen, fTPktInnen, fTPktDS; // fTPktAussen = Taupunkt Aussen, fTPktInnen = Taupunkt Innen, fTpkDS = Taupunkt Durchschnitt (wenn weitere Sensoren verwendet werden)
float fTempAussen, fTempInnen; // fTempAussen = Temperatur Aussen, fTempInnen = Temperatur Innen
float fFeuchteAussen, fFeuchteInnen; // fFeuchteAussen = Luftfeuchtigkeit Aussen, fFeuchte Innen = Luftfeuchtigkeit Innen

DHT dht1(DHTPIN1, DHTTYPE); // Objektnamenszuweisung der DHT22 Sensoren dht1 bis dht2
DHT dht2(DHTPIN2, DHTTYPE);

void setup() {
  
  lcd.begin(); // initialize the LCD
  lcd.backlight(); // Turn on the blacklight and print a message.
  
  dht1.begin(); // Initialisierung der Sensoren dht1, dht2
  dht2.begin();
 
  pinMode(bLuefter1, OUTPUT); // Lüfterpins für Lüfter 1, 2
  pinMode(bLuefter2, OUTPUT);
  
  digitalWrite(bLuefter1, HIGH); // die Relaisplatine funktioniert mit AKTIV LOW d.h. die Pins müssen auf HIGH == LüfterAUS
  digitalWrite(bLuefter2, HIGH); // gesetzt werden.
  
}


void loop(){
 
  lesenSensoren();  // Aufruf Unterroutine Sensoren lesen

  
  if ((fTempInnen >= fTempSchwMin) && (fTempInnen <= fTempSchwMax)){
    // Prüfen ob die Raumtemperatur innerhalb der eingestelten Schwelle liegt, ausserhalb wird nicht gelüftet
    //
    // prüfen ob der Taupunkt Aussen + eingestellte maxSchwelle kleiner als der Taupunktdurchschnitt der drei Innensensoren ist
    // wenn der Durchschnitt der Innensensoren diesen Wert überschreitet werden mit luefterAN() Routine alle drei Lüfter eingeschalten
    // alle drei Lüfter deshalb, weil sonst Strömungswirbel in den Räumen entstehen.
    if ((fTPktAussen + fTauPSchwMax) <= fTPktDS) {
      //
      luefterAN();
      //
    }

    // Ausschalten aller Lüfter wenn der Taupunkt Aussen + die minSchwelle größer werden als der Taupunktdurchschnitt in den Räumen
    // dadurch werden, alle Räume auf ein gleiches Niveau der Luftfeuchte gebracht.
    if ((fTPktAussen + fTauPSchwMin) >= fTPktDS) {
      luefterAUS(); // aufrufen der Unterroutine luefterAUS
      delay(500);
    }
    
  }else{
    // Sinkt die Durschnittstemperatur im Partykeller unter die Temperaturschwelle werden die
    // Lüfter ausgeschalten, damit der Keller nicht unnötig auskühlt. (besonders im Winter)
    luefterAUS();

  }
}
