// === 腳位定義 ===
#define LED_PIN   0   // PB0: 板載 LED
#define MOS_PIN   1   // PB1: 控制 MOSFET
#define BTN_PIN   2   // PB2: 手動按鈕

// === 時間設定 (毫秒) ===
// 範例：充 1 小時 (3600000), 休 3 小時 (10800000)
// 為了測試，建議先改短一點，例如 充5秒 休5秒
unsigned long CHARGE_TIME = 3600000; 
unsigned long REST_TIME   = 10800000;

// === 變數 ===
bool isCharging = false;       // 目前狀態
unsigned long lastSwitchTime = 0; // 上次切換時間
int lastBtnState = HIGH;       // 按鈕上一次狀態 (去彈跳用)

void setup() {
  pinMode(LED_PIN, OUTPUT);
  pinMode(MOS_PIN, OUTPUT);
  pinMode(BTN_PIN, INPUT_PULLUP); // 開啟 P2 的內建上拉電阻

  // 預設開機先開始充電
  startCharging();
}

void loop() {
  unsigned long currentTime = millis();

  // --- 1. 檢查按鈕 (手動控制) ---
  int btnState = digitalRead(BTN_PIN);
  
  // 偵測按下的瞬間 (LOW 代表按下，因為有上拉)
  if (btnState == LOW && lastBtnState == HIGH) {
    // 簡單的去彈跳 (Delay)
    delay(50); 
    if(digitalRead(BTN_PIN) == LOW) {
      // 切換狀態
      if (isCharging) {
        stopCharging();
      } else {
        startCharging();
      }
    }
  }
  lastBtnState = btnState;

  // --- 2. 自動定時檢查 ---
  if (isCharging) {
    // 如果充電時間到了 -> 休息
    if (currentTime - lastSwitchTime >= CHARGE_TIME) {
      stopCharging();
    }
  } else {
    // 如果休息時間到了 -> 充電
    if (currentTime - lastSwitchTime >= REST_TIME) {
      startCharging();
    }
  }
}

// === 動作函式 ===
void startCharging() {
  isCharging = true;
  lastSwitchTime = millis();
  
  // 邏輯：充電 -> PMOS 導通 (LOW) / LED 亮 (HIGH)
  digitalWrite(MOS_PIN, LOW);  
  digitalWrite(LED_PIN, HIGH); 
}

void stopCharging() {
  isCharging = false;
  lastSwitchTime = millis();
  
  // 邏輯：斷電 -> PMOS 關閉 (HIGH) / LED 滅 (LOW)
  digitalWrite(MOS_PIN, HIGH); 
  digitalWrite(LED_PIN, LOW);  
}