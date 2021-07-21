#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_I2CDevice.h>
#include <EEPROM.h>

void menu();
void blesk();
void expozice();
void rada_snim();
void spoust();
void zvuk();
void test();
void nastaveni();
void cas_ms();


#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

int read_old = 0;
int ad0_old = 0;
int ad02old = 0;
float cas_ms_ms = 0;
float cas_ms_m = 0;
float cas_ms_s = 0;
float cas_ms_c = 0;
int cas = 0;
int pocet_snimku = 0;
String tp_text = "";
int treshold = 10;

void setup() {
  // put your setup code here, to run once:
  pinMode(LED_BUILTIN, OUTPUT);

Serial.begin(9600);
Serial.println("zaciname");

// SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { //I2C changed the address //already chill
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
display.setRotation(2);

display.clearDisplay();
display.display();

delay(1000);

display.clearDisplay();
display.setTextColor(WHITE);
display.setTextSize(2);
display.setCursor(0,0);
display.print(F("lightning"));
display.setTextSize(1);
display.setCursor(5,27);
display.print(F("------------------"));
display.setCursor(20,50);
display.print(F("(c) OK5TVR"));
display.display();

  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);

  // put your setup code here, to run once:
digitalWrite(9, HIGH);
digitalWrite(10, HIGH);
delay(100);
digitalWrite(9, LOW);
digitalWrite(10, LOW);

display.clearDisplay();
display.setTextColor(WHITE);
display.setTextSize(2);
display.setCursor(0,0);
display.print(F("Menu"));
display.display();

menu();

}
void loop() {
display.clearDisplay();
display.setTextColor(WHITE);
display.setTextSize(2);
display.setCursor(0,0);
display.print(F("exit"));
display.display();

delay (1000);
menu();

}
void menu()
{

display.clearDisplay();
display.setTextColor(WHITE);
display.setTextSize(2);
display.setCursor(0,0);
display.print(F("Menu"));
display.display();

int polozka = 0;

int val_up = HIGH;
int val_down = HIGH;
int val_ok = LOW;


do
{
val_up = digitalRead(3);
val_down = digitalRead(4);
val_ok = digitalRead(2);


delay(100);

if (val_up == LOW) 
{
  polozka = polozka + 1;
  if (polozka == 8 ) polozka = 0;
}

if (val_down == LOW) 
{
  polozka = polozka - 1;
  if (polozka == 0 ) polozka = 8;
}

switch (polozka) {
  case 1:
display.clearDisplay();
display.setTextColor(WHITE);
display.setTextSize(2);
display.setCursor(0,0);
display.print(F("Blesk"));
display.display();
    break;
  case 2:
display.clearDisplay();
display.setTextColor(WHITE);
display.setTextSize(2);
display.setCursor(0,0);
display.print(F("Expozice"));
display.display();
    break;
  case 3:
display.clearDisplay();
display.setTextColor(WHITE);
display.setTextSize(2);
display.setCursor(0,0);
display.print(F("Sekvence"));
display.display();
    break;
  case 4:
display.clearDisplay();
display.setTextColor(WHITE);
display.setTextSize(2);
display.setCursor(0,0);
display.print(F("Spoust"));
display.display();
    break;
  case 5:
display.clearDisplay();
display.setTextColor(WHITE);
display.setTextSize(2);
display.setCursor(0,0);
display.print(F("Zvuk"));
display.display();
    break;
    case 6:
display.clearDisplay();
display.setTextColor(WHITE);
display.setTextSize(2);
display.setCursor(0,0);
display.print(F("Test"));
display.display();
    break;
    case 7:
display.clearDisplay();
display.setTextColor(WHITE);
display.setTextSize(2);
display.setCursor(0,0);
display.print(F("Nastaveni"));
display.display();
    break;
}
} while (val_ok == HIGH);

switch (polozka) {
  case 1:
    blesk();
    break;
  case 3:
    rada_snim();
    break;
  case 2:
    expozice();
    break;
  case 4:
    spoust();
    break;
  case 5:
    zvuk();
  break;
    case 6:
    test();
  break;
    case 7:
    nastaveni();
  break;
}
}
void test()
{
do {
  int ad0 = 0;
  int ad2 = 0;


  ad0 = analogRead(A0);
  ad2 = analogRead(A2);

display.clearDisplay();
display.setTextColor(WHITE);
display.setTextSize(2);
display.setCursor(0,0);
display.print(F("TEST"));
display.setTextSize(1);
display.setCursor(5,20);
display.print(F("AD0      AD2"));
display.setCursor(5,30);
display.print(abs(ad0_old - ad0));
display.setCursor(5,40);
display.print(abs(ad02old - ad2));
display.setCursor(5,55);
display.setTextSize(1);
display.print("exit --> OK");
display.display();

ad0_old = ad0;
ad02old = ad2;
} while (digitalRead(2) == HIGH);
}
void blesk ()
{
display.clearDisplay();
display.setTextColor(WHITE);
display.setTextSize(2);
display.setCursor(0,0);
display.print(F("BLESK"));
display.setCursor(5,55);
display.setTextSize(1);
display.print(F("exit --> OK"));
display.display();

do
{
  int sensorValue = analogRead(A0);
  //read_old = sensorValue;
  //Serial.println(rozdil);

  if (abs(sensorValue - read_old) > 19) {
  digitalWrite(10, HIGH);
  digitalWrite(9, HIGH);  // sets the digital pin 13 off
        // waits for a second
  delay(10);
  digitalWrite(10, LOW); // sets the digital pin 13 on
  digitalWrite(9, LOW);  // sets the digital pin 13 off
  delay(100);
  
  }
  read_old = sensorValue;
  // put your main code here, to run repeatedly: 
} while (digitalRead(2) == HIGH);
}
void zvuk ()
{
EEPROM.get(100,treshold);

display.clearDisplay();
display.setTextColor(WHITE);
display.setTextSize(2);
display.setCursor(0,0);
display.print(F("ZVUK"));
display.setTextSize(1);
display.setCursor(5,40);
display.print(treshold);
display.setCursor(5,55);
display.print(F("exit --> OK"));
display.display();

do
{
  int sensorValue = analogRead(A2);
  //read_old = sensorValue;
  //Serial.println(rozdil);

  if (abs(sensorValue - read_old) > treshold) {
  digitalWrite(10, HIGH);
  digitalWrite(9, HIGH);  // sets the digital pin 13 off
        // waits for a second
  delay(10);
  digitalWrite(10, LOW); // sets the digital pin 13 on
  digitalWrite(9, LOW);  // sets the digital pin 13 off
  delay(100);
  
  }
  read_old = sensorValue;
  // put your main code here, to run repeatedly: 
} while (digitalRead(2) == HIGH);
}
void rada_snim() 
{
display.clearDisplay();
display.setTextColor(WHITE);
display.setTextSize(2);
display.setCursor(0,0);
display.print(F("Sekvence"));
display.setCursor(5,25);
display.setTextSize(1);
display.print(F("pocet snimku"));
display.setCursor(5,40);
display.print(F("nastavit"));
display.display();
delay (1000);
do
{
if (digitalRead(3)==LOW) pocet_snimku = pocet_snimku + 1;
if (digitalRead(4)==LOW) pocet_snimku = pocet_snimku - 1;
if (pocet_snimku < 0) pocet_snimku = 0;
display.clearDisplay();
display.setCursor(5,40);
display.print(F("pocet snimku"));
display.setCursor(5,55);
display.print(pocet_snimku);
display.display();
delay(100);
} while (digitalRead(2) == HIGH);

tp_text = "int. mezi s.";
cas_ms();
delay(1000);

String cas_st = "";
cas_st = cas_st + int(cas_ms_m);
cas_st = cas_st +   ":";
cas_st = cas_st + int(cas_ms_s);
cas_st = cas_st + ":";
cas_st = cas_st + int(cas_ms_ms);

display.clearDisplay();
display.setTextColor(WHITE);
display.setTextSize(2);
display.setCursor(0,0);
display.print(F("Sekvence"));
display.setCursor(5,25);
display.setTextSize(1);
display.print(F("m:s:ms"));
display.setCursor(5,40);
display.print(cas_st);
display.setCursor(5,50);
display.print(F("Start -> OK"));
display.display();

do
{
digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(100);                       // wait for a second
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  delay(100);                       // wait for a second
} while (digitalRead(2) == HIGH);

 int pocet_s_old = pocet_snimku;

do
{
 
  digitalWrite(9, HIGH);
  digitalWrite(10, HIGH);  // sets the digital pin 13 off
  delay(10);
  digitalWrite(9, LOW); // sets the digital pin 13 on
  digitalWrite(10, LOW);  // sets the digital pin 13 off
 
  pocet_snimku = pocet_snimku - 1;

  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(2);
  display.setCursor(0,0);
  display.print(F("Sekvence"));
  display.setCursor(5,25);
  display.setTextSize(1);
  display.print(F("pocet snimku:"));
 display.setCursor(85,25);
 display.print(pocet_s_old);
  display.setCursor(5,40);
   display.print(F("zbyva:"));
    display.setCursor(85,40);
   display.print(pocet_snimku);
  display.display();

  if (pocet_snimku <= 0) goto konec1;
  delay(cas_ms_c);
 
} while (digitalRead(2) == HIGH);

konec1:;
display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(2);
  display.setCursor(0,0);
  display.print(F("Sekvence"));
  display.setCursor(5,25);
  display.setTextSize(1);
  display.print(F("Zopakovat UP"));
  display.setCursor(5,40);
  display.print(F("Exit --> OK"));
  display.display();
do
{
  if (digitalRead(4)==LOW) rada_snim();
} while (digitalRead(2) == HIGH);

}
void expozice()
{

display.clearDisplay();
display.setTextColor(WHITE);
display.setTextSize(2);
display.setCursor(0,0);
display.print(F("Expozice"));
display.setCursor(5,25);
display.setTextSize(1);
display.print(F("delka expozice"));
display.setCursor(5,40);
display.print(F("nastavit"));
display.display();
delay (1000);
tp_text = "delka expozice";
cas_ms();
ad0_old = int(cas_ms_c);
display.clearDisplay();
display.setTextColor(WHITE);
display.setTextSize(2);
display.setCursor(0,0);
display.print(F("Expozice"));
display.setCursor(5,25);
display.setTextSize(1);
display.print(F("cekani"));
display.setCursor(5,40);
display.print(F("nastavit"));
display.display();
delay (1000);
tp_text = "delka cekani";
cas_ms();
ad02old = int(cas_ms_c); 

do
{
display.clearDisplay();
display.setTextColor(WHITE);
display.setTextSize(2);
display.setCursor(0,0);
display.print(F("EXPOZICE"));
display.setCursor(0,20);
display.print(F("ON"));
display.setTextSize(1);
display.setCursor(5,50);
display.print(F("START --> OK"));
display.display();
} while ((digitalRead(2)==HIGH));

display.clearDisplay();
display.setTextColor(WHITE);
display.setTextSize(2);
display.setCursor(0,0);
display.print(F("EXPOZICE"));
display.setTextSize(1);
display.setCursor(5,50);
display.print(F("exit --> OK"));
display.display();

do
{
digitalWrite(9, HIGH);
digitalWrite(10, HIGH);
delay(ad0_old);
digitalWrite(9, LOW);
digitalWrite(10, LOW);
delay(ad02old);

} while (digitalRead(2) == HIGH);


}
void spoust ()
{
do
{
display.clearDisplay();
display.setTextColor(WHITE);
display.setTextSize(2);
display.setCursor(0,0);
display.print("SPOUST");
display.setCursor(0,20);
display.print("start UP");
display.setTextSize(1);
display.setCursor(5,50);
display.print(F("exit --> OK"));
display.display();

if (digitalRead(4)==LOW) {
do
{
digitalWrite(9, HIGH);
digitalWrite(10, HIGH);
display.clearDisplay();
display.setTextColor(WHITE);
display.setTextSize(2);
display.setCursor(0,0);
display.print(F("SPOUST"));
display.setCursor(0,20);
display.print("END DOWN");
display.setTextSize(1);
display.setCursor(5,50);
display.print(F("exit --> OK"));
display.display();
if (digitalRead(3)==LOW) goto konec2;
} while (digitalRead(2) == HIGH);

}
konec2:;
digitalWrite(9, LOW);
digitalWrite(10, LOW);
delay(200);
} while (digitalRead(2) == HIGH);
}
void cas_ms() { // ------------------nastaveni casu univerzatni ------------
display.clearDisplay();
display.setTextColor(WHITE);
display.setTextSize(2);
display.setCursor(0,0);
display.print("");
display.setCursor(5,25);
display.setTextSize(1);
display.print(tp_text);
display.setCursor(5,40);
display.print("nastavit minut");
display.display();
delay (1000);
do
{
  if (digitalRead(3)==LOW) cas = cas + 1;
  if (digitalRead(4)==LOW) cas = cas - 1;
  if (cas < 1) cas = 0;
  if (cas > 60) cas = 60;
display.clearDisplay();
display.setCursor(5,40);
display.print("minut");
display.setCursor(5,55);
display.print(cas);
display.display();
delay(100);
} while (digitalRead(2) == HIGH);
cas_ms_m = cas * 60 * 1000;
cas = 0;

display.clearDisplay();
display.setTextColor(WHITE);
display.setTextSize(2);
display.setCursor(0,0);
display.print("");
display.setCursor(5,25);
display.setTextSize(1);
display.print(tp_text);
display.setCursor(5,40);
display.print("nastavit sekund");
display.display();
delay (1000);
do
{
  if (digitalRead(3)==LOW) cas = cas + 1;
  if (digitalRead(4)==LOW) cas = cas - 1;
  if (cas >= 60) cas = 60;
  if (cas < 1) cas = 0;
display.clearDisplay();
display.setCursor(5,40);
display.print("sekund");
display.setCursor(5,55);
display.print(cas);
display.display();
delay(100);
} while (digitalRead(2) == HIGH);
cas_ms_s = cas * 1000;
cas = 0;

display.clearDisplay();
display.setTextColor(WHITE);
display.setTextSize(2);
display.setCursor(0,0);
display.print("");
display.setCursor(5,25);
display.setTextSize(1);
display.print(tp_text);
display.setCursor(5,40);
display.print("nastavit milisekund");
display.display();
delay (1000);
do
{
  if (digitalRead(3)==LOW) cas = cas + 1;
  if (digitalRead(4)==LOW) cas = cas - 1;
  if (cas == 1000) cas = 0;
  if (cas < 0) cas = 0;
display.clearDisplay();
display.setCursor(5,40);
display.print("milisekund");
display.setCursor(5,55);
display.print(cas);
display.display();
delay(100);
} while (digitalRead(2) == HIGH);
cas_ms_ms = cas;
cas = 0;

cas_ms_c = cas_ms_ms + cas_ms_m + cas_ms_s;
cas_ms_ms = cas_ms_ms;
cas_ms_m = cas_ms_m / 60000;
cas_ms_s = cas_ms_s / 1000;

return;
}
void nastaveni ()
{
display.clearDisplay();
display.setTextColor(WHITE);
display.setTextSize(2);
display.setCursor(0,0);
display.print(F("Nastaveni"));
display.setCursor(5,25);
display.setTextSize(1);
display.print(F("treshold"));
display.setCursor(5,40);
display.print(F("nastavit"));
display.display();
delay (1000);
do
{
if (digitalRead(3)==LOW) pocet_snimku = pocet_snimku + 1;
if (digitalRead(4)==LOW) pocet_snimku = pocet_snimku - 1;
if (pocet_snimku < 0) pocet_snimku = 0;
display.clearDisplay();
display.setCursor(5,40);
display.print(F("treshold"));
display.setCursor(5,55);
display.print(pocet_snimku);
display.display();
delay(100);
} while (digitalRead(2) == HIGH);
treshold = pocet_snimku;
EEPROM.put(100,treshold);
}