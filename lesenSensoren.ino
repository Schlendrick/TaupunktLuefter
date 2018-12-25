void lesenSensoren() {
  
  //AUSSENSENSOR
  fFeuchteAussen = dht1.readHumidity(); // lesen Luftfeuchte Aussensensor
  fTempAussen = dht1.readTemperature(); // lesen Temperatur Aussensensor
 
  while (isnan(fFeuchteAussen) || isnan(fTempAussen)) {
     // sollte der Sensor keine Daten liefern, wird in der While Schleife solange gelesen bis gültige Daten erhalten werden.
    fFeuchteAussen = dht1.readHumidity(); // lesen Luftfeuchte Aussensensor
    fTempAussen = dht1.readTemperature();
    displayNoValues(0);
    luefterAUS();
    delay(2000);
    
  }
  // Anzeige Temperatur und Feuchte auf Display
  displayValues(0, fTempAussen, fFeuchteAussen);
  
  // Berechnung der Taupunkttemperatur für den Aussensensor
  fTPktAussen = CalcDewPoint(fTempAussen, fFeuchteAussen);


  //INNENSENSOR
  fFeuchteInnen = dht2.readHumidity(); 
  fTempInnen = dht2.readTemperature(); 
  
  while (isnan(fFeuchteInnen) || isnan(fTempInnen)) {
    fFeuchteInnen = dht2.readHumidity();
    fTempInnen = dht2.readTemperature();
    displayNoValues(1);
    luefterAUS();
    delay(2000);
  }
 // Anzeige Temperatur und Feuchte auf Display
 displayValues(1, fTempInnen, fFeuchteInnen);
  
 // Berechnung der Taupunkttemperatur für den Innensensor
 fTPktInnen = CalcDewPoint(fTempInnen, fFeuchteInnen);

  fTPktDS = (fTPktInnen) / 1; // Durchschnittsberechnung: Diese Formel müsste angepasst werden wenn mehrere InnenSensoren eingebaut werden( bei 2 -> / 2..)
  
  return;
}


float CalcDewPoint(float t, float h){
  // Berechnung für den Taupunkt
  // t = Temperatur [°C], h = Humidity [%]
  float a = 17.271;
  float b = 237.7;
  float taupunktTemp = (a * t) / (b + t) + log(h/100);
  return (b * taupunktTemp) / (a - taupunktTemp);
 
}


void displayValues(int n, float t, float h){
  // Anzeige der Temperatur und der Feuchte auf LCD
  // Cursor ändern falls Temperatur unter 0°C fällt
  lcd.setCursor(0,n); //Ab hier kann das I2C LCD Modul genau wie das einfache LCD Modul programmiert werden.
  if(n == 0){
    lcd.print("A T:");
  }else{
    lcd.print("I T:");
  }
  
  if(t < 0){
    lcd.setCursor(4,n);  
  }else{
    lcd.setCursor(5,n);
  }
  lcd.print(t, 0); // lcd.print um etwas auf dem Display anzeigen zu lassen
  lcd.print("\337"); 
  lcd.setCursor(8,n);
  lcd.print("C "); 
  lcd.setCursor(11,n);
  lcd.print("F:");
  if(h > 99){
    h = 99; // 100 Kann nicht auf Display angezeigt werden  
  }
  lcd.print(h, 0);
  lcd.print("%");
  
}

void displayNoValues(int n){
  //Zeige _ _ an wen keine gueltigen Werte von Sensor vorhanden
  lcd.setCursor(0,n); 
  if(n == 0){
    lcd.print("A ");
  }else{
     lcd.print("I ");
  }
  lcd.print("T:");
  lcd.print(" __"); 
  lcd.print("\337"); 
  lcd.setCursor(8,n);
  lcd.print("C "); 
  lcd.setCursor(11,n);
  lcd.print("F:");
  lcd.print("__");
  lcd.print("%");

  
}

