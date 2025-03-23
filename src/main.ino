#include <config.hpp>
#include <state_indicator.hpp>
#include <night_light.hpp>
#include <wasserwaage.hpp>

int last_state = 0;
int state = 0;
bool state_indicated = false;
bool doublePressDetected = false;

volatile unsigned long lastPressTime = 0;
volatile int pressCount = 0;

void setup()
{

  Serial.begin(9600);
  delay(1000);
  Config();
  attachInterrupt(digitalPinToInterrupt(BTN_PIN), buttonISR, FALLING);
}

void loop()
{

  if (not state_indicated)
  {
    print_instruction(state);
    State_Reset();
    state_indicated = true;
    State_Indicator_Run(state);
  }

  switch (state)
  {
  case 0:

    break;
  case 1:
    NightLight_Run();
    break;
  case 2:
    Wasserwaage_Run();
    break;

  default:
    break;
  }
}

void buttonISR()
{
  unsigned long currentTime = millis();

  if (currentTime - lastPressTime < TIMEOUT)
  {
    pressCount++;
  }
  else
  {
    pressCount = 1; // Reset if too much time has passed
  }

  lastPressTime = currentTime;

  if (pressCount == 2)
  {
    triggerDoublePressAction();
  }
}

// Action triggered on double press
void triggerDoublePressAction()
{
  state = (state + 1) % NUM_STATE;
  state_indicated = false;
}

void State_Reset()
{
  last_state = abs(state - 1);

  switch (last_state)
  {
  case 0:
    NightLight_Reset();
    break;
  case 1:
    NightLight_Reset();
    break;
  case 2:
    Wasserwaage_Reset();
    break;

  default:
    break;
  }
}

void print_instruction(int state)
{
  switch (state)
  {
  case 0:
    clearSerialMonitor();
    Serial.println(".----------------------------------------------------.");
    Serial.println("|                     Chế độ chờ                     |");
    Serial.println("`----------------------------------------------------´");
    Serial.println("|                                                    |");
    Serial.println("|     Rất tiếc, không có gì ở đây cả  ┑(￣Д ￣)┍     |");
    Serial.println("|                                                    |");
    Serial.println("`----------------------------------------------------´");
    Serial.println();
    break;
  case 1:
    clearSerialMonitor();
    Serial.println(".----------------------------------------------------.");
    Serial.println("|                       Đèn đêm                      |");
    Serial.println("`----------------------------------------------------´");
    Serial.println("|                                                    |");
    Serial.println("|  Chờ trời tối và lắc, đèn sẽ sáng...  乁( ◔ ౪◔)「  |");
    Serial.println("|                                                    |");
    Serial.println("`----------------------------------------------------´");
    Serial.println();
    Serial.println("> Bấm nút một lần để đổi màu");
    break;
  case 2:
    clearSerialMonitor();
    Serial.println(".----------------------------------------------------.");
    Serial.println("|                    Wasserwaage                     |");
    Serial.println("`----------------------------------------------------´");
    Serial.println("|                                                    |");
    Serial.println("|    Thiết bị chứng mình trái đất phẳng  ミ●﹏☉ミ    |");
    Serial.println("|                                                    |");
    Serial.println("`----------------------------------------------------´");
    Serial.println();
    Serial.println("> Bấm nút một lần để đổi cách hiển thị");
    break;

  case 3:
    clearSerialMonitor();
    Serial.println(".----------------------------------------------------.");
    Serial.println("|                      ò e í e                       |");
    Serial.println("`----------------------------------------------------´");
    Serial.println("|                                                    |");
    Serial.println("|                    (づ｡◕‿‿◕｡)づ                    |");
    Serial.println("|                                                    |");
    Serial.println("`----------------------------------------------------´");
    Serial.println();
    break;

  default:
    break;
  }

  Serial.println("> Bấm nút hai lần để chuyển sang chế độ típ theo -->");
}

void clearSerialMonitor()
{
  for (int i = 0; i < 50; i++)
  {
    Serial.println();
  }
}