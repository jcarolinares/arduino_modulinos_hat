/**
 * Modulino LED Matrix + Sensors + Built-in Nano R4 RTC Hourly Vibration Chime + Buzzer
 */
#include "ArduinoGraphics.h"
#include <Arduino_Modulino.h>
#include "Modulino_LED_Matrix.h"
#include "LEDMatrixGallery.h"
#include "matrix_collection.h"
#include <math.h>

// Built-in RTC Library for Arduino Renesas (Nano R4 / UNO R4)
#include "RTC.h"

// --- RTC TRACKING ---
int lastVibratedHour = -1; 

// --- TASK SCHEDULING TIMERS ---
unsigned long lastScrollTime = 0;
unsigned long lastHeatwaveTime = 0;
unsigned long lastThermoTime = 0;
unsigned long lastRtcCheckTime = 0;

int currentScrollFrame = 0;
int scrollSpeed = 70; 

// --- COUNTDOWN & BLINKING STATE ---
bool isCountdownActive = false;
unsigned long countdownStartTime = 0;
int lastCountdownSecond = -1;

bool isGoBlinkingActive = false;
unsigned long goBlinkStartTime = 0;
bool goIsCurrentlyOn = false;

// --- NON-BLOCKING HOURLY VIBRATION CHIME STATE MACHINE ---
int pendingVibrations = 0;
bool vibroState = false;
unsigned long lastVibroToggleTime = 0;
constexpr unsigned long VIBRO_ON_MS  = 200; // Duration of vibration pulse
constexpr unsigned long VIBRO_OFF_MS = 300; // Pause between pulses

// --- FORCE STRUCT DEFINITIONS TO THE TOP ---
struct MatrixFrame {
    uint32_t data[4];
};

// --- ANIMATION GENERATOR CONFIGURATIONS ---
constexpr int SCROLL_LEN = 19; 
constexpr char SCROLL_STR[] = "   UPV HACKATHON   ";
constexpr int TOTAL_COLS = 12 + (SCROLL_LEN * 6) + 12; 
constexpr int TOTAL_FRAMES = TOTAL_COLS - 11; 

struct ScrollAnimation {
    uint32_t frames[TOTAL_FRAMES][4];
};

constexpr int SCROLL_LEN_K = 19; 
constexpr char SCROLL_STR_K[] = "OPEN SOURCE IS LOVE";
constexpr int TOTAL_COLS_K = 12 + (SCROLL_LEN_K * 6) + 12; 
constexpr int TOTAL_FRAMES_K = TOTAL_COLS_K - 11; 

struct ScrollAnimationK {
    uint32_t frames[TOTAL_FRAMES_K][4];
};

// Map ALL uppercase letters (A-Z) and numbers (0-9)
constexpr uint8_t getCharCol(char c, int col) {
    if (col >= 5) return 0x00; 
    if (c >= 'a' && c <= 'z') c -= 32; 
    
    switch (c) {
        case '0': { uint8_t f[] = {0xFF, 0x81, 0x81, 0x81, 0xFF}; return f[col]; }
        case '1': { uint8_t f[] = {0x80, 0x82, 0xFF, 0x80, 0x80}; return f[col]; }
        case '2': { uint8_t f[] = {0xC2, 0xA1, 0x91, 0x89, 0x86}; return f[col]; }
        case '3': { uint8_t f[] = {0x42, 0x81, 0x89, 0x89, 0x76}; return f[col]; }
        case '4': { uint8_t f[] = {0x18, 0x14, 0x12, 0xFF, 0x10}; return f[col]; }
        case '5': { uint8_t f[] = {0x4F, 0x89, 0x89, 0x89, 0x71}; return f[col]; }
        case '6': { uint8_t f[] = {0x7E, 0x89, 0x89, 0x89, 0x70}; return f[col]; }
        case '7': { uint8_t f[] = {0x01, 0x01, 0x01, 0x01, 0xFF}; return f[col]; }
        case '8': { uint8_t f[] = {0x76, 0x89, 0x89, 0x89, 0x76}; return f[col]; }
        case '9': { uint8_t f[] = {0x0E, 0x11, 0x11, 0x11, 0xFF}; return f[col]; }
        case 'A': { uint8_t f[] = {0xFE, 0x09, 0x09, 0x09, 0xFE}; return f[col]; }
        case 'B': { uint8_t f[] = {0xFF, 0x89, 0x89, 0x89, 0x76}; return f[col]; }
        case 'C': { uint8_t f[] = {0x7E, 0x81, 0x81, 0x81, 0x42}; return f[col]; }
        case 'D': { uint8_t f[] = {0xFF, 0x81, 0x81, 0x81, 0x7E}; return f[col]; }
        case 'E': { uint8_t f[] = {0xFF, 0x89, 0x89, 0x89, 0x81}; return f[col]; }
        case 'F': { uint8_t f[] = {0xFF, 0x09, 0x09, 0x09, 0x01}; return f[col]; }
        case 'G': { uint8_t f[] = {0x7E, 0x81, 0x91, 0x91, 0x72}; return f[col]; }
        case 'H': { uint8_t f[] = {0xFF, 0x08, 0x08, 0x08, 0xFF}; return f[col]; }
        case 'I': { uint8_t f[] = {0x81, 0x81, 0xFF, 0x81, 0x81}; return f[col]; }
        case 'J': { uint8_t f[] = {0x60, 0x80, 0x81, 0x7F, 0x00}; return f[col]; }
        case 'K': { uint8_t f[] = {0xFF, 0x08, 0x14, 0x22, 0xC1}; return f[col]; }
        case 'L': { uint8_t f[] = {0xFF, 0x80, 0x80, 0x80, 0x80}; return f[col]; }
        case 'M': { uint8_t f[] = {0xFF, 0x02, 0x04, 0x02, 0xFF}; return f[col]; }
        case 'N': { uint8_t f[] = {0xFF, 0x06, 0x18, 0x60, 0xFF}; return f[col]; }
        case 'O': { uint8_t f[] = {0x7E, 0x81, 0x81, 0x81, 0x7E}; return f[col]; }
        case 'P': { uint8_t f[] = {0xFF, 0x11, 0x11, 0x11, 0x0E}; return f[col]; }
        case 'Q': { uint8_t f[] = {0x7E, 0x81, 0x85, 0x82, 0x7D}; return f[col]; }
        case 'R': { uint8_t f[] = {0xFF, 0x09, 0x19, 0x29, 0x46}; return f[col]; }
        case 'S': { uint8_t f[] = {0x46, 0x89, 0x89, 0x89, 0x72}; return f[col]; }
        case 'T': { uint8_t f[] = {0x01, 0x01, 0xFF, 0x01, 0x01}; return f[col]; }
        case 'U': { uint8_t f[] = {0x7F, 0x80, 0x80, 0x80, 0x7F}; return f[col]; }
        case 'V': { uint8_t f[] = {0x3F, 0x40, 0x80, 0x40, 0x3F}; return f[col]; }
        case 'W': { uint8_t f[] = {0x7F, 0x40, 0x38, 0x40, 0x7F}; return f[col]; }
        case 'X': { uint8_t f[] = {0xE3, 0x14, 0x08, 0x14, 0xE3}; return f[col]; }
        case 'Y': { uint8_t f[] = {0x03, 0x0C, 0xF0, 0x0C, 0x03}; return f[col]; }
        case 'Z': { uint8_t f[] = {0xC1, 0xA1, 0x91, 0x89, 0x87}; return f[col]; }
        case ' ': default: return 0x00;
    }
}

constexpr uint8_t getScrollColumn(int colIndex) {
    if (colIndex < 12) return 0x00; 
    int textCol = colIndex - 12;
    int charIndex = textCol / 6;
    if (charIndex >= SCROLL_LEN) return 0x00; 
    return getCharCol(SCROLL_STR[charIndex], textCol % 6);
}

constexpr uint8_t getScrollColumnK(int colIndex) {
    if (colIndex < 12) return 0x00; 
    int textCol = colIndex - 12;
    int charIndex = textCol / 6;
    if (charIndex >= SCROLL_LEN_K) return 0x00; 
    return getCharCol(SCROLL_STR_K[charIndex], textCol % 6);
}

constexpr ScrollAnimation generateScroll() {
    ScrollAnimation anim = {};
    for (int f = 0; f < TOTAL_FRAMES; f++) {
        uint8_t c[12] = {0};
        for (int i = 0; i < 12; i++) { c[i] = getScrollColumn(f + i); }
        anim.frames[f][0] = ((uint32_t)c[0] << 24) | ((uint32_t)c[1] << 16) | ((uint32_t)c[2] << 8) | c[3];
        anim.frames[f][1] = ((uint32_t)c[4] << 24) | ((uint32_t)c[5] << 16) | ((uint32_t)c[6] << 8) | c[7];
        anim.frames[f][2] = ((uint32_t)c[8] << 24) | ((uint32_t)c[9] << 16) | ((uint32_t)c[10] << 8) | c[11];
        anim.frames[f][3] = 60; 
    }
    return anim;
}

constexpr ScrollAnimationK generateScrollK() {
    ScrollAnimationK anim = {};
    for (int f = 0; f < TOTAL_FRAMES_K; f++) {
        uint8_t c[12] = {0};
        for (int i = 0; i < 12; i++) { c[i] = getScrollColumnK(f + i); }
        anim.frames[f][0] = ((uint32_t)c[0] << 24) | ((uint32_t)c[1] << 16) | ((uint32_t)c[2] << 8) | c[3];
        anim.frames[f][1] = ((uint32_t)c[4] << 24) | ((uint32_t)c[5] << 16) | ((uint32_t)c[6] << 8) | c[7];
        anim.frames[f][2] = ((uint32_t)c[8] << 24) | ((uint32_t)c[9] << 16) | ((uint32_t)c[10] << 8) | c[11];
        anim.frames[f][3] = 100; 
    }
    return anim;
}

constexpr ScrollAnimation ANIM_ROBOCON = generateScroll();
constexpr ScrollAnimationK ANIM_KARIBU = generateScrollK();

// --- STATIC "GO" GENERATOR ---
constexpr MatrixFrame makeGoFrame() {
    uint8_t cols[12] = {0}; 
    cols[0] = 0x7E; cols[1] = 0x81; cols[2] = 0x91; cols[3] = 0x91; cols[4] = 0x72;
    cols[7] = 0x7E; cols[8] = 0x81; cols[9] = 0x81; cols[10] = 0x81; cols[11] = 0x7E;
    
    MatrixFrame frame = {0, 0, 0, 66}; 
    frame.data[0] = ((uint32_t)cols[0] << 24) | ((uint32_t)cols[1] << 16) | ((uint32_t)cols[2] << 8) | (uint32_t)cols[3];
    frame.data[1] = ((uint32_t)cols[4] << 24) | ((uint32_t)cols[5] << 16) | ((uint32_t)cols[6] << 8) | (uint32_t)cols[7];
    frame.data[2] = ((uint32_t)cols[8] << 24) | ((uint32_t)cols[9] << 16) | ((uint32_t)cols[10] << 8) | (uint32_t)cols[11];
    return frame;
}
constexpr MatrixFrame FRAME_GO = makeGoFrame();


ModulinoLEDMatrix matrix_1;
ModulinoLEDMatrix matrix_2(0x40);
ModulinoLEDMatrix matrix_3(0x41);

ModulinoThermo thermo;
ModulinoLight light;
ModulinoButtons buttons;
ModulinoVibro vibro;
ModulinoBuzzer buzzer;

float celsius = 0;
int matrix2_mode = 0; 

constexpr uint8_t FONT_5x8[10][5] = {
    { 0xFF, 0x81, 0x81, 0x81, 0xFF }, { 0x80, 0x82, 0xFF, 0x80, 0x80 },
    { 0xC2, 0xA1, 0x91, 0x89, 0x86 }, { 0x42, 0x81, 0x89, 0x89, 0x76 },
    { 0x18, 0x14, 0x12, 0xFF, 0x10 }, { 0x4F, 0x89, 0x89, 0x89, 0x71 },
    { 0x7E, 0x89, 0x89, 0x89, 0x70 }, { 0x01, 0x01, 0x01, 0x01, 0xFF },
    { 0x76, 0x89, 0x89, 0x89, 0x76 }, { 0x0E, 0x11, 0x11, 0x11, 0xFF } 
};

constexpr MatrixFrame makeNumberFrame(int num) {
    uint8_t cols[12] = {0}; 
    if (num < 10) {
        cols[3] = FONT_5x8[num][0]; cols[4] = FONT_5x8[num][1]; cols[5] = FONT_5x8[num][2]; cols[6] = FONT_5x8[num][3]; cols[7] = FONT_5x8[num][4];
    } else {
        int d1 = num / 10; int d2 = num % 10;
        cols[0] = FONT_5x8[d1][0]; cols[1] = FONT_5x8[d1][1]; cols[2] = FONT_5x8[d1][2]; cols[3] = FONT_5x8[d1][3]; cols[4] = FONT_5x8[d1][4];
        cols[7] = FONT_5x8[d2][0]; cols[8] = FONT_5x8[d2][1]; cols[9] = FONT_5x8[d2][2]; cols[10] = FONT_5x8[d2][3]; cols[11] = FONT_5x8[d2][4];
    }
    MatrixFrame frame = {0, 0, 0, 66}; 
    frame.data[0] = ((uint32_t)cols[0] << 24) | ((uint32_t)cols[1] << 16) | ((uint32_t)cols[2] << 8) | (uint32_t)cols[3];
    frame.data[1] = ((uint32_t)cols[4] << 24) | ((uint32_t)cols[5] << 16) | ((uint32_t)cols[6] << 8) | (uint32_t)cols[7];
    frame.data[2] = ((uint32_t)cols[8] << 24) | ((uint32_t)cols[9] << 16) | ((uint32_t)cols[10] << 8) | (uint32_t)cols[11];
    return frame;
}

#define GEN_FRAME(n) { makeNumberFrame(n).data[0], makeNumberFrame(n).data[1], makeNumberFrame(n).data[2], makeNumberFrame(n).data[3] }

constexpr uint32_t NUMBERS_0_TO_50[51][4] = {
    GEN_FRAME(0),  GEN_FRAME(1),  GEN_FRAME(2),  GEN_FRAME(3),  GEN_FRAME(4),  GEN_FRAME(5),  GEN_FRAME(6),  GEN_FRAME(7),  GEN_FRAME(8),  GEN_FRAME(9),
    GEN_FRAME(10), GEN_FRAME(11), GEN_FRAME(12), GEN_FRAME(13), GEN_FRAME(14), GEN_FRAME(15), GEN_FRAME(16), GEN_FRAME(17), GEN_FRAME(18), GEN_FRAME(19),
    GEN_FRAME(20), GEN_FRAME(21), GEN_FRAME(22), GEN_FRAME(23), GEN_FRAME(24), GEN_FRAME(25), GEN_FRAME(26), GEN_FRAME(27), GEN_FRAME(28), GEN_FRAME(29),
    GEN_FRAME(30), GEN_FRAME(31), GEN_FRAME(32), GEN_FRAME(33), GEN_FRAME(34), GEN_FRAME(35), GEN_FRAME(36), GEN_FRAME(37), GEN_FRAME(38), GEN_FRAME(39),
    GEN_FRAME(40), GEN_FRAME(41), GEN_FRAME(42), GEN_FRAME(43), GEN_FRAME(44), GEN_FRAME(45), GEN_FRAME(46), GEN_FRAME(47), GEN_FRAME(48), GEN_FRAME(49), GEN_FRAME(50)
};

// Non-blocking handler for async vibration chimes
void updateVibration() {
  if (pendingVibrations <= 0 && !vibroState) return;

  unsigned long now = millis();

  if (vibroState) {
    if (now - lastVibroToggleTime >= VIBRO_ON_MS) {
      vibro.off();
      vibroState = false;
      lastVibroToggleTime = now;
      pendingVibrations--;
    }
  } else {
    if (pendingVibrations > 0 && (now - lastVibroToggleTime >= VIBRO_OFF_MS)) {
      vibro.on(255); // Max power
      vibroState = true;
      lastVibroToggleTime = now;
    }
  }
}

void setup() {
  Modulino.begin();
  Wire.setClock(400000); 

  RTC.begin();

  RTCTime savedTime;
  RTC.getTime(savedTime);
  
  if (!RTC.isRunning()) {
    RTCTime startTime(15, Month::OCTOBER, 2026, 9, 59, 0, DayOfWeek::MONDAY, SaveLight::SAVING_TIME_INACTIVE);
    RTC.setTime(startTime);
  }

  thermo.begin();
  matrix_1.begin();
  matrix_2.begin();
  matrix_3.begin();
  light.begin();
  buttons.begin();
  vibro.begin();
  buzzer.begin();

  matrix_1.clear();
  matrix_2.clear();
  matrix_3.clear();

  matrix2_mode = 0;
  matrix_2.setFrame(LEDMATRIX_ARDUINO_LOOP);
  
  lastThermoTime = millis();
}

void loop() {

  updateVibration();

  // --- RTC HOURLY CHECK ---
  if (millis() - lastRtcCheckTime >= 1000) {
    lastRtcCheckTime = millis();
    
    RTCTime currentTime;
    RTC.getTime(currentTime);
    int currentHour = currentTime.getHour(); 

    if (currentHour != lastVibratedHour) {
      lastVibratedHour = currentHour;
      int count = currentHour % 12;
      if (count == 0) count = 12;
      pendingVibrations = count;
    }
  }

  // --- TIER 0: INSTANT ACTIONS ---
  if (buttons.update()) {
    if (buttons.isPressed(0)) {
      pendingVibrations = 1;
      matrix2_mode = 0;
      matrix_2.setFrame(LEDMATRIX_ARDUINO_LOOP);
      
    } else if (buttons.isPressed(1)) {
      pendingVibrations = 2;
      matrix2_mode = 1;
      currentScrollFrame = 0; 
      
    } else if (buttons.isPressed(2)) {
      matrix2_mode = 2;
      currentScrollFrame = 0; 
      
      // --- START THE COUNTDOWN ---
      isCountdownActive = true;
      isGoBlinkingActive = false; 
      countdownStartTime = millis();
      lastCountdownSecond = -1; 
    }
  }
  
  // --- OVERRIDE TIER 1: GLOBAL COUNTDOWN ---
  if (isCountdownActive) {
    unsigned long elapsed = millis() - countdownStartTime;
    
    if (elapsed < 3000) {
      // Calculate which second we are on (3, 2, or 1)
      int currentSecond = 3 - (elapsed / 1000); 
      
      if (currentSecond != lastCountdownSecond) {
        lastCountdownSecond = currentSecond;
        
        matrix_1.setFrame(NUMBERS_0_TO_50[currentSecond]);
        matrix_2.setFrame(NUMBERS_0_TO_50[currentSecond]);
        matrix_3.clear(); 
        matrix_3.setFrame(NUMBERS_0_TO_50[currentSecond]);

        // 1. Trigger haptic pulse!
        vibro.on(255);
        vibroState = true;
        lastVibroToggleTime = millis();
        pendingVibrations = 0; 
        
        // 2. Trigger Mario Kart "Ready" Beep (1047 Hz / C6 for 150ms)
        buzzer.tone(1047, 150); 
      }
    } else {
      // 3 seconds are up! Transition directly to "GO" Blinking
      isCountdownActive = false;
      isGoBlinkingActive = true;
      goBlinkStartTime = millis();
      goIsCurrentlyOn = false; 

      // --- NEW: Trigger ONE continuous 1500ms beep spanning all three "GO" flashes! ---
      buzzer.tone(2093, 1500); 
    }
  } 
  
  // --- OVERRIDE TIER 2: "GO" BLINKING ---
  else if (isGoBlinkingActive) {
    unsigned long elapsed = millis() - goBlinkStartTime;
    
    // We want 3 blinks. Each blink lasts 500ms (300ms ON, 200ms OFF)
    if (elapsed < 1500) {
      bool shouldBeOn = (elapsed % 500) < 300; 
      
      if (shouldBeOn != goIsCurrentlyOn) {
        goIsCurrentlyOn = shouldBeOn;
        
        if (shouldBeOn) {
          // Flash the "GO" frames!
          matrix_1.setFrame(FRAME_GO.data);
          matrix_2.setFrame(FRAME_GO.data);
          matrix_3.clear();
          matrix_3.setFrame(FRAME_GO.data);
          
          // Trigger vibration pulse (buzzer is already ringing continuously in the background!)
          vibro.on(255);
          vibroState = true;
          lastVibroToggleTime = millis();
          pendingVibrations = 0; 
          
        } else {
          // Clear screens during the OFF phase of the blink
          matrix_1.clear();
          matrix_2.clear();
          matrix_3.clear();
        }
      }
    } else {
      // Blinking is finished! Restore normal screens
      isGoBlinkingActive = false;
      
      int tempIdx = int(celsius);
      if (tempIdx >= 0 && tempIdx <= 50) {
        matrix_1.setFrame(NUMBERS_0_TO_50[tempIdx]);
      }
      matrix_3.clear(); 
    }
  }
  
  // --- NORMAL ANIMATION TIERS (Only run if NO countdown or blinking is active) ---
  else {
    
    // --- TIER 1: FAST TIMER (Text Scrolling) ---
    if (millis() - lastScrollTime >= scrollSpeed) {
      lastScrollTime = millis();

      if (matrix2_mode == 1) {
        matrix_2.setFrame(ANIM_ROBOCON.frames[currentScrollFrame]);
        currentScrollFrame += 2; 
        if (currentScrollFrame >= TOTAL_FRAMES) currentScrollFrame = 0; 
        
      } else if (matrix2_mode == 2) {
        matrix_2.setFrame(ANIM_KARIBU.frames[currentScrollFrame]);
        currentScrollFrame += 2; 
        if (currentScrollFrame >= TOTAL_FRAMES_K) currentScrollFrame = 0; 
      }
    }

    // --- TIER 2: MEDIUM TIMER (IR Sensor & Heatwave) ---
    if (millis() - lastHeatwaveTime >= 40) {
      lastHeatwaveTime = millis(); 

      light.update();
      int ir = light.getIR();

      int sensorValue = ir; 
      if (sensorValue > 1023) sensorValue = 1023;
      if (sensorValue < 0) sensorValue = 0;

      float baseHeight = sensorValue * (6.0 / 1023.0);

      matrix_3.clear();
      matrix_3.beginDraw();
      matrix_3.stroke(0xFFFFFF); 

      for (int x = 0; x < 12; x++) {
        float mountainHeight = sin(x * (3.14159 / 11.0)) * 2.0; 
        int totalHeight = round(baseHeight + mountainHeight);
        
        if (totalHeight > 8) totalHeight = 8;
        if (totalHeight < 0) totalHeight = 0;

        if (totalHeight > 0) {
          int startY = 8 - totalHeight;
          matrix_3.line(x, startY, x, 7);
        }
      }
      matrix_3.endDraw(); 
    }
  }

  // --- TIER 3: SLOW TIMER (Thermometer) ---
  if (millis() - lastThermoTime >= 2000) {
    lastThermoTime = millis(); 
    celsius = thermo.getTemperature();
    
    if (!isCountdownActive && !isGoBlinkingActive) {
      int tempIdx = int(celsius);
      if (tempIdx >= 0 && tempIdx <= 50) {
        matrix_1.setFrame(NUMBERS_0_TO_50[tempIdx]);
      }
    }
  }
}