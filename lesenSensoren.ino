void lesenSensoren() {
  
  float fH, fH1; // anlegen lokaler Variablen für die Berechnung der Taupunkte 
  
  //AUSSENSENSOR
  fFeuchteAussen = dht1.readHumidity(); // lesen Luftfeuchte Aussensensor
  fTempAussen = dht1.readTemperature(); // lesen Temperatur Aussensensor
 
  while (isnan(fFeuchteAussen) || isnan(fTempAussen)) {
     // sollte der Sensor keine Daten liefern, wird in der While Schleife solange gelesen bis gültige Daten erhalten werden.
    fFeuchteAussen = dht1.readHumidity();
    fTempAussen = dht1.readTemperature();
    delay(2000);
    
  }
  // Berechnung der Taupunkttemperatur für den Aussensensor
  fH = (log10(fFeuchteAussen) - 2) / 0.4343 + (17.62 * fTempAussen) / (243.12 + fTempAussen);
  fTPktAussen = 243.12 * fH / (17.62 - fH);


  //INNENSENSOR
  fFeuchteInnen = dht2.readHumidity(); 
  fTempInnen = dht2.readTemperature(); 
  
  while (isnan(fFeuchteInnen) || isnan(fTempInnen)) {
    fFeuchteInnen = dht2.readHumidity();
    fTempInnen = dht2.readTemperature();
    delay(2000);
  }
  // Berechnung der Taupunkttemperatur für den Innensensor
  fH1 = (log10(fFeuchteInnen) - 2) / 0.4343 + (17.62 * fTempInnen) / (243.12 + fTempInnen);
  fTPktInnen = 243.12 * fH1 / (17.62 - fH1);


  fTPktDS = (fTPktInnen) / 1; // Durchschnittsberechnung: Diese Formel müsste angepasst werden wenn mehrere InnenSensoren eingebaut werden( bei 2 -> / 2..)
  
  return;
}

