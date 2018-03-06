#include <Fsm.h>
#include <MFRC522.h>
#include <LiquidCrystal_I2C.h> // Using version 1.3.5
#include <DallasTemperature.h>
#include <OneWire.h>
#include <CountDown.h>
#include "Tea.h"

//Version printed in splashscreen
const String vers = "v0.10";

//general pins
#define BUTTON_PIN_1 4
#define BUTTON_PIN_2 3
#define BUZZER_PIN 7

//pins for temp sensor
#define ONE_WIRE_BUS 2

//pins for rfid reader
#define RST_PIN 9
#define SS_PIN 10

// Create MFRC522 instance
MFRC522 mfrc522(SS_PIN, RST_PIN);

//Create instance for temp sensors
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

// The LCD constructor - address shown is 0x27 - may or may not be correct for yours
// Also based on YWRobot LCM1602 IIC V1
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

//Create Countdown
CountDown CD(CountDown::SECONDS);

#define NUMBER_OF_TEAS 7 // Configurable, see typical pin layout above
Tea teas[NUMBER_OF_TEAS];
Tea currentTea = Tea();

//Events for state machine transitions
#define TEA_SELECTED_EVENT 0
#define WATER_RECOGNIZED_EVENT 1
#define TEA_DONE_EVENT 2
#define RESTART_EVENT 3

/* state_wait_for_tea_selection: Wait till user selects type of tea. Eighter via buttons or rfid reader
   state_wait_for_water:         Wait till water is in pot.(Temperature bigger than x)
   state_in_progress:            Wait till time is over
   state_done                    Wait till pot is empty and show current temperature.
*/
State state_wait_for_tea_selection(&state_wait_for_tea_selection_enter, &state_wait_for_tea_selection_exit, NULL);
State state_wait_for_water(&state_wait_for_water_enter, &state_wait_for_water_exit, NULL);
State state_in_progress(&state_in_progress_enter, &state_in_progress_exit, NULL);
State state_done(&state_done_enter, &state_done_exit, NULL);
Fsm fsm(&state_wait_for_tea_selection);

//Global variables
int counter = 0;
bool teaSelected = false;
int button1Old = HIGH;
int button2Old = HIGH;
void setup()
{
  //Inizialize LCD Display
  lcd.begin(16, 2); // sixteen characters across - 2 lines
  lcd.backlight();

  //Show splashscreen  on startup
  showSplashScreen(vers);

  //Initialize serial communication
  Serial.begin(9600);

  //Setup pins of buttons and buzzer
  pinMode(BUTTON_PIN_1, INPUT_PULLUP);
  pinMode(BUTTON_PIN_2, INPUT_PULLUP);
  pinMode(BUZZER_PIN, OUTPUT); // Set buzzer - pin 9 as an output

  //Initialize temp sensor
  sensors.begin();

  //Initialize RFID reader
  SPI.begin();
  mfrc522.PCD_Init();

  //Initialize Teas
    Tea blackTea = Tea("Black",300,95,-1);
    Tea greenTea = Tea("Green",240,80,-1);
    Tea oolongTea = Tea("Oolong",60,85,-1);
    Tea yellowTea = Tea("Yellow",180,75,-1);
    Tea whiteTea = Tea("White",240,70,-1);
    Tea herbalTea = Tea("Herbal",420,95,10035);
    Tea fruitTea = Tea("Fruit",480,95,4294957801);
  //Tea blackTea = Tea("Black", 10, 95, 4294957801);
  //Tea greenTea = Tea("Green", 11, 80, 10035);
  //Tea oolongTea = Tea("Oolong", 5, 85, -1);
  //Tea yellowTea = Tea("Yellow", 6, 75, -1);
  //Tea whiteTea = Tea("White", 7, 70, -1);
  //Tea herbalTea = Tea("Herbal", 8, 95, -1);
  //Tea fruitTea = Tea("Fruit", 9, 95, -1);

  teas[0] = blackTea;
  teas[1] = greenTea;
  teas[2] = oolongTea;
  teas[3] = yellowTea;
  teas[4] = whiteTea;
  teas[5] = herbalTea;
  teas[6] = fruitTea;

  currentTea = teas[0];

  //Init transitions
  fsm.add_transition(&state_wait_for_tea_selection, &state_wait_for_water, TEA_SELECTED_EVENT, NULL);
  fsm.add_transition(&state_wait_for_water, &state_in_progress, WATER_RECOGNIZED_EVENT, NULL);
  fsm.add_transition(&state_in_progress, &state_done, TEA_DONE_EVENT, NULL);
  fsm.add_transition(&state_done, &state_wait_for_tea_selection, RESTART_EVENT, NULL);


  //Delay so splashscrren stays for some time
  delay(2000);

}

void loop()
{
  // Call fsm run
  fsm.run_machine();
  delay(50);
}

//Functions called from state machine when new state is entered or exited
void state_wait_for_tea_selection_enter()
{
  //Initial state: reset all global variables
  counter = 0;
  teaSelected = false;
  currentTea = teas[0];
  button1Old = HIGH;
  button2Old = HIGH;

  Serial.println("state_initial_enter");
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Select your");
  // 8th character - 2nd line
  lcd.setCursor(0, 1);
  lcd.print("type of tea.");
  lcd.display();
}

void state_wait_for_tea_selection_exit()
{
  Serial.println("state_wait_for_tea_selection_exit");

  //read the pushbutton value into a variable
  int button1State = digitalRead(BUTTON_PIN_1);
  int button2State = digitalRead(BUTTON_PIN_2);
  //print out the value of the pushbutton

  //Select Button
  if (button1State != button1Old) {
    button1Old = LOW;
    if (button1State == LOW) {
      Serial.println("Button pressed!");
    }
    else {
      Serial.println("Button released!");
      if (counter == NUMBER_OF_TEAS) {
        counter = 0;
      }
      currentTea = teas[counter];
      teaSelected = true;
      counter = counter + 1;
      printTeaInfo(currentTea);
      button1Old = HIGH;
    }
  }

  //Enter Button
  if (button2State != button2Old) {
    button2Old = LOW;
    if (button2State == LOW) {
      Serial.println("Button2 pressed!");
    }
    else {
      Serial.println("Button2 released!");
      button2Old = HIGH;
      Serial.println(teaSelected);
      if (teaSelected == true) {
        fsm.trigger(TEA_SELECTED_EVENT);
      }
      else {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Select tea first!");
        lcd.display();
      }
    }
  }

  //RFID Cards
  if (mfrc522.PICC_IsNewCardPresent()) {
    unsigned long uid = getID();
    if (uid != -1) {
      Serial.print("Card detected, UID: ");
      Serial.println(uid);
      for (int i = 0; i < NUMBER_OF_TEAS; i = i + 1) {
        Serial.println(teas[i].getUid());
        if (uid == teas[i].getUid()) {
          currentTea = teas[i];
          teaSelected = true;
          printTeaInfo(currentTea);
          tone(BUZZER_PIN, 1000);
          delay(500);
          noTone(BUZZER_PIN);
          fsm.trigger(TEA_SELECTED_EVENT);
          break;
        }
      }
    }
  }
}

void state_wait_for_water_enter()
{
  Serial.println("state_wait_for_water_enter");
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(currentTea.getName());
  lcd.setCursor(8, 0);
  lcd.print(currentTea.getTempC());
  lcd.print((char)223);
  lcd.print("C");

  lcd.setCursor(0, 1);
  lcd.print("Fill with water.");
  lcd.display();
}

void state_wait_for_water_exit()
{
  Serial.println("state_wait_for_water_exit");
  if (getTemperature() >= 65.0) {
    fsm.trigger(WATER_RECOGNIZED_EVENT);
  }
  /* Possible improvement: What if water is to cold or to hot?
    //If water temperature is under recommendet temperature, start immediately
    if (getTemperature() <= currentTea.getTempC()) {
      fsm.trigger(WATER_RECOGNIZED_EVENT);
    }
    //If water temperature is higher, wait till it cools down
    if(getTemperature()> currentTea.getTempC()){
      //Notification: Water to hot.
    }*/
}

void state_in_progress_enter()
{
  Serial.println("state_in_progress_enter");
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Time left: ");

  lcd.setCursor(0, 1);
  lcd.print("Curr.Temp:");
  lcd.setCursor(11, 1);
  lcd.print(getTemperature());
  lcd.display();

  CD.start(currentTea.getTimeSec());
}

long previousMillis = 0;
long interval = 1000;
void state_in_progress_exit()
{
  Serial.println("state_in_progress_exit");
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis > interval) {
    previousMillis = currentMillis;
    Serial.println("Time left:");
    Serial.println(CD.remaining());
    if (CD.remaining() == 0) {
      fsm.trigger(TEA_DONE_EVENT);
    }
    else {
      updateProcessNotification(CD.remaining());
    }
  }
}

void state_done_enter()
{
  Serial.println("state_done_enter");
  teaDone();
  lcd.setCursor(0, 1);
  lcd.print("Cur.Temp: ");
}

void state_done_exit()
{
  Serial.println("state_done_exit");
  lcd.setCursor(11, 1);
  lcd.print(getTemperature());
  lcd.display();
  delay(5000); //Update tea every 5 seconds
  if (getTemperature() < 30.00) {
    fsm.trigger(RESTART_EVENT);
  }
}

void showSplashScreen(String vers)
{
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Welcome to");
  // 8th character - 2nd line
  lcd.setCursor(0, 1);
  lcd.print("SmartKanne " + vers);
  lcd.display();
}

void updateProcessNotification(long time)
{
  lcd.setCursor(11, 0);
  int minutes = (time / 60) % 60;
  int seconds = time % 60;
  if (minutes < 10)
    lcd.print("0");
  lcd.print(minutes);
  lcd.print(":");
  if (seconds < 10)
    lcd.print("0");
  lcd.print(seconds);

  lcd.setCursor(11, 1);
  lcd.print(getTemperature());
  lcd.display();
}

void printTeaInfo(Tea tea)
{
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(tea.getName());
  lcd.setCursor(8, 0);
  lcd.print(tea.getTempC());
  lcd.print((char)223);
  lcd.print("C");

  lcd.setCursor(0, 1);
  lcd.print("Time: ");
  int minutes = (tea.getTimeSec() / 60) % 60;
  int seconds = tea.getTimeSec() % 60;
  if (minutes < 10)
    lcd.print("0");
  lcd.print(minutes);
  lcd.print(":");
  if (seconds < 10)
    lcd.print("0");
  lcd.print(seconds);
}

void teaDone()
{
  lcd.clear();
  lcd.setCursor(2, 0);
  lcd.print("Tea is ready!");
  lcd.setCursor(4, 1);
  lcd.print("Enjoy.");
  lcd.display();

  tone(BUZZER_PIN, 1000);
  delay(1000);
  noTone(BUZZER_PIN);
  delay(1000);
  tone(BUZZER_PIN, 1000);
  delay(1000);
  noTone(BUZZER_PIN);
  delay(1000);
  tone(BUZZER_PIN, 1000);
}

//From https://stackoverflow.com/questions/32839396/how-to-get-the-uid-of-rfid-in-arduino
/**
   mfrc522.PICC_IsNewCardPresent() should be checked before
   @return the card UID
*/
unsigned long getID()
{
  if (!mfrc522.PICC_ReadCardSerial()) { //Since a PICC placed get Serial and continue
    return -1;
  }
  unsigned long hex_num;
  hex_num = mfrc522.uid.uidByte[0] << 24;
  hex_num += mfrc522.uid.uidByte[1] << 16;
  hex_num += mfrc522.uid.uidByte[2] << 8;
  hex_num += mfrc522.uid.uidByte[3];
  mfrc522.PICC_HaltA(); // Stop reading
  return hex_num;
}

float getTemperature()
{
  sensors.requestTemperatures(); // Send the command to get temperature readings
  float temp = sensors.getTempCByIndex(0);
  Serial.println(temp);
  return temp;
}
