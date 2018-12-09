
void lcdScreen() {

  int humidity_data_aussen = (int)fFeuchteAussen; // type cast float to int
  int temperature_data_aussen = (int)fTempAussen;

  int humidity_data_innen = (int)fFeuchteInnen;
  int temperature_data_innen = (int)fTempInnen;
  
  lcd.setCursor(0,0); //Ab hier kann das I2C LCD Modul genau wie das einfache LCD Modul programmiert werden.
  lcd.print("A ");
  lcd.print("T:");
  if(temperature_data_aussen < 0){
    lcd.setCursor(4,0);  
  }else{
    lcd.setCursor(5,0);
  }
  lcd.print(temperature_data_aussen); // lcd.print um etwas auf dem Display anzeigen zu lassen
  lcd.print("\337"); 
  lcd.setCursor(8,0);
  lcd.print("C "); 
  lcd.setCursor(11,0);
  lcd.print("F:");
  lcd.print(humidity_data_aussen);
  lcd.print("%");

  lcd.setCursor(0,1); //Ab hier kann das I2C LCD Modul genau wie das einfache LCD Modul programmiert werden.
  lcd.print("I ");
  lcd.print("T:");
  
  if(temperature_data_innen < 0){
    lcd.setCursor(4,1);  
  }else{
    lcd.setCursor(5,1);
  }
  lcd.print(temperature_data_innen); // lcd.print um etwas auf dem Display anzeigen zu lassen
  lcd.print("\337"); 
  lcd.setCursor(8,1);
  lcd.print("C "); 
  lcd.setCursor(11,1);
  lcd.print("F:");
  lcd.print(humidity_data_innen);
  lcd.print("%");
 
 }
