#include <Keypad.h>
#include <SoftwareSerial.h>
#include <DFRobotDFPlayerMini.h>
#include <LiquidCrystal_I2C.h>
#include <avr/pgmspace.h>
#include <ctype.h>

// MP3 player setup
SoftwareSerial mp3Serial(10, 11);  // RX, TX
DFRobotDFPlayerMini mp3;

// LCD setup
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Keypad Setup
const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
byte rowPins[ROWS] = {2, 3, 4, 5};
byte colPins[COLS] = {6, 7, 8, 9};
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

// T9 Mapping
const char* t9Mapping[10] = {
  " ",    // 0
  "1",    // 1
  "ABC_", // 2
  "DEF",  // 3
  "GHI",  // 4
  "JKL",  // 5
  "MNO",  // 6
  "PQRS", // 7
  "TUV",  // 8
  "WXYZ"  // 9
};

// Sentences stored in PROGMEM
const char s0[] PROGMEM = "HELLO_HOW_ARE_YOU";
const char s1[] PROGMEM = "GOOD_MORNING";
const char s2[] PROGMEM = "GOOD_AFTERNOON";
const char s3[] PROGMEM = "GOOD_EVENING";
const char s4[] PROGMEM = "WHAT_IS_YOUR_NAME";
const char s5[] PROGMEM = "MY_NAME_IS_VIJAY";
const char s6[] PROGMEM = "NICE_TO_MEET_YOU";
const char s7[] PROGMEM = "HOW_OLD_ARE_YOU";
const char s8[] PROGMEM = "WHERE_ARE_YOU_FROM";
const char s9[] PROGMEM = "I_AM_FROM_INDIA";
const char s10[] PROGMEM = "SEE_YOU_LATER";
const char s11[] PROGMEM = "HAVE_A_NICE_DAY";
const char s12[] PROGMEM = "TAKE_CARE";
const char s13[] PROGMEM = "WELCOME_BACK";
const char s14[] PROGMEM = "HOW_WAS_YOUR_DAY";
const char s15[] PROGMEM = "GOOD_NIGHT";
const char s16[] PROGMEM = "ITS_NICE_TO_MEET_YOU";
const char s17[] PROGMEM = "WHAT_DO_YOU_DO";
const char s18[] PROGMEM = "I_AM_A_STUDENT";
const char s19[] PROGMEM = "CAN_WE_BE_FRIENDS";
const char s20[] PROGMEM = "WHATS_GOING_ON";
const char s21[] PROGMEM = "NOTHING_MUCH";
const char s22[] PROGMEM = "WHATS_NEW";
const char s23[] PROGMEM = "HOWS_IT_GOING";
const char s24[] PROGMEM = "I_AM_FINE_THANK_YOU";
const char s25[] PROGMEM = "LONG_TIME_NO_SEE";
const char s26[] PROGMEM = "WHAT_ARE_YOU_DOING";
const char s27[] PROGMEM = "I_AM_STUDYING";
const char s28[] PROGMEM = "I_AM_WORKING";
const char s29[] PROGMEM = "I_AM_RELAXING";
const char s30[] PROGMEM = "THATS_GREAT";
const char s31[] PROGMEM = "I_DONT_UNDERSTAND";
const char s32[] PROGMEM = "CAN_YOU_HELP_ME";
const char s33[] PROGMEM = "PLEASE_REPEAT_IT";
const char s34[] PROGMEM = "SPEAK_SLOWLY_PLEASE";
const char s35[] PROGMEM = "WHAT_DOES_IT_MEAN";
const char s36[] PROGMEM = "HOW_DO_YOU_SAY_THIS_IN_ENGLISH";
const char s37[] PROGMEM = "WHAT_TIME_IS_IT";
const char s38[] PROGMEM = "ITS_FIVE_OCLOCK";
const char s39[] PROGMEM = "WHERE_ARE_YOU_GOING";
const char s40[] PROGMEM = "WHERE_IS_THE_STATION";
const char s41[] PROGMEM = "ITS_OVER_THERE";
const char s42[] PROGMEM = "GO_STRAIGHT";
const char s43[] PROGMEM = "TURN_LEFT";
const char s44[] PROGMEM = "TURN_RIGHT";
const char s45[] PROGMEM = "ITS_NEARBY";
const char s46[] PROGMEM = "ITS_FAR_FROM_HERE";
const char s47[] PROGMEM = "HOW_CAN_I_GET_TO_THE_MARKET";
const char s48[] PROGMEM = "IS_IT_NEAR";
const char s49[] PROGMEM = "CAN_YOU_SHOW_ME_THE_WAY";
const char s50[] PROGMEM = "HOW_MUCH_IS_THIS";
const char s51[] PROGMEM = "ITS_TOO_EXPENSIVE";
const char s52[] PROGMEM = "DO_YOU_HAVE_A_DISCOUNT";
const char s53[] PROGMEM = "ILL_TAKE_IT";
const char s54[] PROGMEM = "I_DONT_WANT_IT";
const char s55[] PROGMEM = "CAN_I_PAY_BY_CARD";
const char s56[] PROGMEM = "HERES_THE_MONEY";
const char s57[] PROGMEM = "KEEP_THE_CHANGE";
const char s58[] PROGMEM = "CAN_I_HAVE_A_BAG";
const char s59[] PROGMEM = "WHATS_THE_TOTAL";
const char s60[] PROGMEM = "PODA_HEYNA";

const char* const sentences[] PROGMEM = {
  s0, s1, s2, s3, s4, s5, s6, s7, s8, s9,
  s10, s11, s12, s13, s14, s15, s16, s17, s18, s19,
  s20, s21, s22, s23, s24, s25, s26, s27, s28, s29,
  s30, s31, s32, s33, s34, s35, s36, s37, s38, s39,
  s40, s41, s42, s43, s44, s45, s46, s47, s48, s49,
  s50, s51, s52, s53, s54, s55, s56, s57, s58, s59,
  s60
};
const int numSentences = sizeof(sentences) / sizeof(sentences[0]);

// Global state
int language = 1; // 1: English, 2: Tamil
char currentInput[100];
int inputIndex = 0;
char lastKey = '\0';
unsigned long lastPressTime = 0;
int pressCount = 0;
const int pressDelay = 500;

void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("System Ready");

  mp3Serial.begin(9600);
  if (!mp3.begin(mp3Serial)) {
    Serial.println("DFPlayer init failed");
    while (1);
  }
  mp3.volume(30);
  delay(1000);
}

void loop() {
  char key = keypad.getKey();
  if (key) {
    unsigned long currentTime = millis();
    if (key == lastKey && (currentTime - lastPressTime) < pressDelay) {
      pressCount++;
    } else {
      pressCount = 0;
    }
    lastPressTime = currentTime;
    lastKey = key;

    if (key == '1') {
      playEmergency(1);
    } else if (key == '0') {
      playEmergency(2);
    } else if (key == 'B') {
      playEmergency(3);
    } else if (key == 'C') {
      language = 2;
      lcd.setCursor(0, 1);
      lcd.print("Language: Tamil ");
    } else if (key == 'D') {
      language = 1;
      lcd.setCursor(0, 1);
      lcd.print("Language: English");
    } else if (key >= '2' && key <= '9' && inputIndex < sizeof(currentInput) - 1) {
      int keyIndex = key - '0';
      int letterCount = strlen(t9Mapping[keyIndex]);
      char selectedLetter = t9Mapping[keyIndex][pressCount % letterCount];
      currentInput[inputIndex] = selectedLetter;
      currentInput[inputIndex + 1] = '\0';

      lcd.setCursor(0, 1);
      lcd.print("                ");
      lcd.setCursor(0, 1);
      lcd.print(currentInput);
    } else if (key == 'A') {
      if (inputIndex < sizeof(currentInput) - 2) {
        inputIndex++;
        currentInput[inputIndex] = '\0';
      }
    } else if (key == '#') {
      playSentence();
      clearInput();
    } else if (key == '*') {
      clearInput();
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("System Ready");
    }
  }
}

void playSentence() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Playing...");
  toUpperCase(currentInput);

  bool found = false;
  char buffer[50];

  for (int i = 0; i < numSentences; i++) {
    strcpy_P(buffer, (char*)pgm_read_word(&(sentences[i])));
    if (strcmp(buffer, currentInput) == 0) {
      mp3.playFolder(language, i + 1);
      found = true;
      break;
    }
  }

  lcd.setCursor(0, 0);
  if (found) {
    lcd.print("Done           ");
  } else {
    lcd.print("Not found      ");
  }
}

void toUpperCase(char* str) {
  while (*str) {
    *str = toupper(*str);
    str++;
  }
}

void clearInput() {
  memset(currentInput, '\0', sizeof(currentInput));
  inputIndex = 0;
  lastKey = '\0';
}

void playEmergency(int trackNumber) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("EMERGENCY ALERT");
  mp3.playFolder(3, trackNumber); // Folder 3 is for emergency clips
  delay(1000);
  lcd.setCursor(0, 1);
  lcd.print("Playing Track ");
  lcd.print(trackNumber);
}