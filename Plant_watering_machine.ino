
#include <LiquidCrystal.h>
#include <dht.h>

#define DHT_SENSOR_TYPE     DHT_TYPE_11
#define RS                  2
#define EN                  3
#define D4                  4
#define D5                  5
#define D6                  6
#define D7                  7
#define PIN_SENSOR1         A0
#define PIN_SENSOR2         A1
#define PIN_SENSOR3         A2
#define PIN_SENSOR4         A3
#define DHT11_PIN           8


LiquidCrystal lcd(RS,EN,D4,D5,D6,D7);             //set Uno pins that are connected to LCD, 4-bit mode

typedef struct{
  uint16_t s1;    // Sensor 1
  uint16_t s2;    // Sensor 2
  uint16_t s3;    // Sensor 3
  uint16_t s4;    // Sensor 4
  float temp;     // Temperature
  float h;        // Hhumidity
}sensors;


  /*Data structure of existing plants*/
  typedef enum {
    ROSA = 1,
    B_BENJAMIN,
    L_BENJAMIN,
    Basilik,
  }plants_t; 

  dht DHT;
  sensors sensor;
  
void setup() {
  lcd.begin(16,2);    //set 16 columns and 2 rows of 16x2 LCD
  

}

/*Defining the plant name*/
const char* which_plant (uint8_t plant){
    if (plant == 1) {return ("Rosa");}
    else if (plant == 2) {return "Big Benjamin";}
    else if (plant == 3) {return "Little Benjamin";}
    else if (plant == 4) {return "Basilicum";}
    else {return "Error_Plant_Naming";}               // Returns Error if the wrong name is given
  }

/*Printing plant info to LCD Display*/
void print_to_LCD_plant(uint16_t value, uint8_t plant){
  if (value < 400){
    lcd.print("Enough water");
    lcd.setCursor(0,1);
    lcd.print(which_plant(plant));
  }
  else if ((value >= 400) && (value < 600)){
    lcd.print("Please water: ");
    lcd.setCursor(0,1);
    lcd.print(which_plant(plant));
  }
  else{
    lcd.print("The soil is dry!");
    lcd.setCursor(0,1);
    lcd.print(which_plant(plant));
  }
  delay(5000);                          //delay 5 seconds
  lcd.clear();                          //clear display, sets cursor back to home
}

/*Prinitng Humidity and temperature parameters on LCD*/
void print_to_LCD_T_H(float temp, float h){

  /*Printing Temperature on two lines*/
  lcd.print("Temperature = ");
  lcd.setCursor(0,1);
  lcd.print(temp);
  lcd.print("deg. C");
  delay(5000);
  lcd.clear();

  /*Printing Humidity on two lines*/
  lcd.print("Humidity = ");
  lcd.setCursor(0,1);
  lcd.print(h);
  delay(5000);
  lcd.clear();
}

void loop() {

  sensor.s1 = analogRead(PIN_SENSOR1);
  sensor.s2 = analogRead(PIN_SENSOR2);
  sensor.s3 = analogRead(PIN_SENSOR3);
  sensor.s4 = analogRead(PIN_SENSOR4);
  int chk = DHT.read11(DHT11_PIN);
 
  print_to_LCD_plant(sensor.s1, Basilik);
  print_to_LCD_plant(sensor.s2, B_BENJAMIN);
  print_to_LCD_plant(sensor.s3, ROSA);
  print_to_LCD_plant(sensor.s4, L_BENJAMIN);
  print_to_LCD_T_H(DHT.temperature,DHT.humidity);
   
}
