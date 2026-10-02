// constexpr const uint32_t* matrixIcon[] = {
//   LEDMATRIX_BLUETOOTH,
//   LEDMATRIX_BOOTLOADER_ON,
//   LEDMATRIX_CHIP,
//   LEDMATRIX_CLOUD_WIFI,
//   LEDMATRIX_DANGER,
//   LEDMATRIX_EMOJI_BASIC,
//   LEDMATRIX_EMOJI_HAPPY,
//   LEDMATRIX_EMOJI_SAD,
//   LEDMATRIX_HEART_BIG,
//   LEDMATRIX_HEART_SMALL,
//   LEDMATRIX_LIKE,
//   LEDMATRIX_MUSIC_NOTE,
//   LEDMATRIX_RESISTOR,
//   LEDMATRIX_UNO
// };

// constexpr const uint32_t (*matrixAnimation[])[4] = {
//   LEDMATRIX_ANIMATION_STARTUP,
//   LEDMATRIX_ANIMATION_TETRIS_INTRO,
//   LEDMATRIX_ANIMATION_ATMEGA,
//   LEDMATRIX_ANIMATION_LED_BLINK_HORIZONTAL,
//   LEDMATRIX_ANIMATION_LED_BLINK_VERTICAL,
//   LEDMATRIX_ANIMATION_ARROWS_COMPASS,
//   LEDMATRIX_ANIMATION_AUDIO_WAVEFORM,
//   LEDMATRIX_ANIMATION_BATTERY,
//   LEDMATRIX_ANIMATION_BOUNCING_BALL,
//   LEDMATRIX_ANIMATION_BUG,
//   LEDMATRIX_ANIMATION_CHECK,
//   LEDMATRIX_ANIMATION_CLOUD,
//   LEDMATRIX_ANIMATION_DOWNLOAD,
//   LEDMATRIX_ANIMATION_DVD,
//   LEDMATRIX_ANIMATION_HEARTBEAT_LINE,
//   LEDMATRIX_ANIMATION_HEARTBEAT,
//   LEDMATRIX_ANIMATION_INFINITY_LOOP_LOADER,
//   LEDMATRIX_ANIMATION_LOAD_CLOCK,
//   LEDMATRIX_ANIMATION_LOAD,
//   LEDMATRIX_ANIMATION_LOCK,
//   LEDMATRIX_ANIMATION_NOTIFICATION,
//   LEDMATRIX_ANIMATION_OPENSOURCE,
//   LEDMATRIX_ANIMATION_SPINNING_COIN,
//   LEDMATRIX_ANIMATION_TETRIS,
//   LEDMATRIX_ANIMATION_WIFI_SEARCH,
//   LEDMATRIX_ANIMATION_HOURGLASS
// };


constexpr uint32_t LEDMATRIX_ARDUINO_LOOP[3] = { 0x3c424242, 0x24181824, 0x4242423c };

constexpr const char* const matrixText[] = {
  "   VIETNAM ARDUINO DAYS   ",
  "   THIS IS THE NEW MODULINO MATRIX   ",
  "   Xin chao!!!   "
};

constexpr const char* const matrixTextRoboconKenya[] = {
  "   Robocon Kenya 2026   ",
  "   Welcome to the event!   ",
  "   Karibu!   "
};



const uint8_t bottle_frame [] = {
  0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 1, 1, 0, 1, 1, 0, 0, 0, 0,
  0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0,
  0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0,
  0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0,
  0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0,
  0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0
};

constexpr uint32_t LEDMATRIX_ANIMATION_OPENSAUCE[][4] = {
    { 0x0, 0x0, 0x0, 66 },
    { 0x0, 0x0, 0x1c, 66 },
    { 0x0, 0x0, 0x1c22, 66 },
    { 0x0, 0x0, 0x1c2222, 66 },
    { 0x0, 0x0, 0x1c22221c, 66 },
    { 0x0, 0x1c, 0x22221c00, 66 },
    { 0x0, 0x1c22, 0x221c003e, 66 },
    { 0x0, 0x1c2222, 0x1c003e0a, 66 },
    { 0x0, 0x1c22221c, 0x3e0a0a, 66 },
    { 0x1c, 0x22221c00, 0x3e0a0a04, 66 },
    { 0x1c22, 0x221c003e, 0xa0a0400, 66 },
    { 0x1c2222, 0x1c003e0a, 0xa04003e, 66 },
    { 0x1c22221c, 0x3e0a0a, 0x4003e2a, 66 },
    { 0x22221c00, 0x3e0a0a04, 0x3e2a2a, 66 },
    { 0x221c003e, 0xa0a0400, 0x3e2a2a22, 66 },
    { 0x1c003e0a, 0xa04003e, 0x2a2a2200, 66 },
    { 0x3e0a0a, 0x4003e2a, 0x2a22003e, 66 },
    { 0x3e0a0a04, 0x3e2a2a, 0x22003e04, 66 },
    { 0xa0a0400, 0x3e2a2a22, 0x3e0408, 66 },
    { 0xa04003e, 0x2a2a2200, 0x3e04083e, 66 },
    { 0x4003e2a, 0x2a22003e, 0x4083e00, 66 },
    { 0x3e2a2a, 0x22003e04, 0x83e0000, 66 },
    { 0x3e2a2a22, 0x3e0408, 0x3e000000, 66 },
    { 0x2a2a2200, 0x3e04083e, 0x0, 66 },
    { 0x2a22003e, 0x4083e00, 0x0, 66 },
    { 0x22003e04, 0x83e0000, 0x24, 66 },
    { 0x3e0408, 0x3e000000, 0x242a, 66 },
    { 0x3e04083e, 0x0, 0x242a2a, 66 },
    { 0x4083e00, 0x0, 0x242a2a12, 66 },
    { 0x83e0000, 0x24, 0x2a2a1200, 66 },
    { 0x3e000000, 0x242a, 0x2a12003c, 66 },
    { 0x0, 0x242a2a, 0x12003c0a, 66 },
    { 0x0, 0x242a2a12, 0x3c0a0a, 66 },
    { 0x24, 0x2a2a1200, 0x3c0a0a3c, 66 },
    { 0x242a, 0x2a12003c, 0xa0a3c00, 66 },
    { 0x242a2a, 0x12003c0a, 0xa3c001e, 66 },
    { 0x242a2a12, 0x3c0a0a, 0x3c001e20, 66 },
    { 0x2a2a1200, 0x3c0a0a3c, 0x1e2020, 66 },
    { 0x2a12003c, 0xa0a3c00, 0x1e20201e, 66 },
    { 0x12003c0a, 0xa3c001e, 0x20201e00, 66 },
    { 0x3c0a0a, 0x3c001e20, 0x201e001c, 66 },
    { 0x3c0a0a3c, 0x1e2020, 0x1e001c22, 66 },
    { 0xa0a3c00, 0x1e20201e, 0x1c2222, 66 },
    { 0xa3c001e, 0x20201e00, 0x1c222222, 66 },
    { 0x3c001e20, 0x201e001c, 0x22222200, 66 },
    { 0x1e2020, 0x1e001c22, 0x2222003e, 66 },
    { 0x1e20201e, 0x1c2222, 0x22003e2a, 66 },
    { 0x20201e00, 0x1c222222, 0x3e2a2a, 66 },
    { 0x201e001c, 0x22222200, 0x3e2a2a22, 66 },
    { 0x1e001c22, 0x2222003e, 0x2a2a2200, 66 },
    { 0x1c2222, 0x22003e2a, 0x2a220000, 66 },
    { 0x1c222222, 0x3e2a2a, 0x22000000, 66 },
    { 0x22222200, 0x3e2a2a22, 0x0, 66 },
    { 0x2222003e, 0x2a2a2200, 0x0, 66 },
    { 0x22003e2a, 0x2a220000, 0x0, 66 },
    { 0x3e2a2a, 0x22000000, 0x22, 66 },
    { 0x3e2a2a22, 0x0, 0x223e, 66 },
    { 0x2a2a2200, 0x0, 0x223e22, 66 },
    { 0x2a220000, 0x0, 0x223e2200, 66 },
    { 0x22000000, 0x22, 0x3e220024, 66 },
    { 0x0, 0x223e, 0x2200242a, 66 },
    { 0x0, 0x223e22, 0x242a2a, 66 },
    { 0x0, 0x223e2200, 0x242a2a12, 66 },
    { 0x22, 0x3e220024, 0x2a2a1200, 66 },
    { 0x223e, 0x2200242a, 0x2a120000, 66 },
    { 0x223e22, 0x242a2a, 0x12000000, 66 },
    { 0x223e2200, 0x242a2a12, 0x0, 66 },
    { 0x3e220024, 0x2a2a1200, 0xc, 66 },
    { 0x2200242a, 0x2a120000, 0xc12, 66 },
    { 0x242a2a, 0x12000000, 0xc1224, 66 },
    { 0x242a2a12, 0x0, 0xc122412, 66 },
    { 0x2a2a1200, 0xc, 0x1224120c, 66 },
    { 0x2a120000, 0xc12, 0x24120c00, 66 },
    { 0x12000000, 0xc1224, 0x120c0000, 66 },
    { 0x0, 0xc122412, 0xc000000, 66 },
    { 0xc, 0x1224120c, 0x0, 66 },
    { 0xc12, 0x24120c00, 0x0, 66 },
    { 0xc1224, 0x120c0000, 0x0, 66 },
    { 0xc122412, 0xc000000, 0x0, 66 },
    { 0x1224120c, 0x0, 0x0, 66 },
    { 0x24120c00, 0x0, 0x0, 66 },
    { 0x120c0000, 0x0, 0x0, 66 },
    { 0xc000000, 0x0, 0x0, 66 },
    { 0x0, 0x0, 0x0, 66 }
};

// Numbers 0 to 9 in 3x32-bit format (for vertical 12x8 layout)
constexpr uint32_t NUM_0[3] = { 0x00182424, 0x24242424, 0x24180000 };
constexpr uint32_t NUM_1[3] = { 0x00081828, 0x08080808, 0x083C0000 };
constexpr uint32_t NUM_2[3] = { 0x00182404, 0x04081020, 0x203C0000 };
constexpr uint32_t NUM_3[3] = { 0x00182404, 0x08180404, 0x24180000 };
constexpr uint32_t NUM_4[3] = { 0x00081828, 0x487C0808, 0x08080000 };
constexpr uint32_t NUM_5[3] = { 0x003C2020, 0x38040404, 0x24180000 };
constexpr uint32_t NUM_6[3] = { 0x00182420, 0x38242424, 0x24180000 };
constexpr uint32_t NUM_7[3] = { 0x003C0404, 0x08081010, 0x20200000 };
constexpr uint32_t NUM_8[3] = { 0x00182424, 0x18242424, 0x24180000 };
constexpr uint32_t NUM_9[3] = { 0x00182424, 0x241C0404, 0x24180000 };

// BIG Numbers 0 to 9 in 3x32-bit format (Full 12x8 vertical utilization)
constexpr uint32_t BIG_NUM_0[3] = { 0x3C666666, 0x66666666, 0x6666663C };
constexpr uint32_t BIG_NUM_1[3] = { 0x18387818, 0x18181818, 0x1818187E };
constexpr uint32_t BIG_NUM_2[3] = { 0x3C666606, 0x0C183060, 0x60607E7E };
constexpr uint32_t BIG_NUM_3[3] = { 0x3C660606, 0x3E3E0606, 0x0666663C };
constexpr uint32_t BIG_NUM_4[3] = { 0x0C1C3C6C, 0x6C6C7E7E, 0x0C0C0C0C };
constexpr uint32_t BIG_NUM_5[3] = { 0x7E7E6060, 0x7C7E0606, 0x0666663C };
constexpr uint32_t BIG_NUM_6[3] = { 0x3C666060, 0x7C7E6666, 0x6666663C };
constexpr uint32_t BIG_NUM_7[3] = { 0x7E7E0606, 0x0C0C1818, 0x30303030 };
constexpr uint32_t BIG_NUM_8[3] = { 0x3C666666, 0x3C3C6666, 0x6666663C };
constexpr uint32_t BIG_NUM_9[3] = { 0x3C666666, 0x667E3E06, 0x0606663C };

// 7-Segment Style Numbers 0 to 9 in 3x32-bit format (12x8 vertical layout)
constexpr uint32_t SEG_NUM_0[3] = { 0x7E7E6666, 0x66666666, 0x66667E7E };
constexpr uint32_t SEG_NUM_1[3] = { 0x06060606, 0x06060606, 0x06060606 };
constexpr uint32_t SEG_NUM_2[3] = { 0x7E7E0606, 0x067E7E60, 0x60607E7E };
constexpr uint32_t SEG_NUM_3[3] = { 0x7E7E0606, 0x067E7E06, 0x06067E7E };
constexpr uint32_t SEG_NUM_4[3] = { 0x66666666, 0x667E7E06, 0x06060606 };
constexpr uint32_t SEG_NUM_5[3] = { 0x7E7E6060, 0x607E7E06, 0x06067E7E };
constexpr uint32_t SEG_NUM_6[3] = { 0x7E7E6060, 0x607E7E66, 0x66667E7E };
constexpr uint32_t SEG_NUM_7[3] = { 0x7E7E0606, 0x06060606, 0x06060606 };
constexpr uint32_t SEG_NUM_8[3] = { 0x7E7E6666, 0x667E7E66, 0x66667E7E };
constexpr uint32_t SEG_NUM_9[3] = { 0x7E7E6666, 0x667E7E06, 0x06067E7E };

// 7-Segment Numbers (4px wide) WITH a colon on the right side
// 7-Segment Numbers (6px wide) WITH a narrow 1px colon on the right edge
// Format: 6 columns for the digit, 1 empty column, 1 column for the colon

constexpr uint32_t COLON_NUM_0[3] = { 0xFCFCCCCD, 0xCDCCCCCD, 0xCDCCFCFC };
constexpr uint32_t COLON_NUM_1[3] = { 0x0C0C0C0D, 0x0D0C0C0D, 0x0D0C0C0C };
constexpr uint32_t COLON_NUM_2[3] = { 0xFCFC0C0D, 0x0DFCFCC1, 0xC1C0FCFC };
constexpr uint32_t COLON_NUM_3[3] = { 0xFCFC0C0D, 0x0DFCFC0D, 0x0D0CFCFC };
constexpr uint32_t COLON_NUM_4[3] = { 0xCCCCCCCD, 0xCDFCFC0D, 0x0D0C0C0C };
constexpr uint32_t COLON_NUM_5[3] = { 0xFCFCC0C1, 0xC1FCFC0D, 0x0D0CFCFC };
constexpr uint32_t COLON_NUM_6[3] = { 0xFCFCC0C1, 0xC1FCFCCD, 0xCDCCFCFC };
constexpr uint32_t COLON_NUM_7[3] = { 0xFCFC0C0D, 0x0D0C0C0D, 0x0D0C0C0C };
constexpr uint32_t COLON_NUM_8[3] = { 0xFCFCCCCD, 0xCDFCFCCD, 0xCDCCFCFC };
constexpr uint32_t COLON_NUM_9[3] = { 0xFCFCCCCD, 0xCDFCFC0D, 0x0D0CFCFC };


// Letters
constexpr uint32_t MENU_M[3] = { 0xC3E7FFDB, 0xC3C3C3C3, 0xC3C3C3C3 };
constexpr uint32_t MENU_E[3] = { 0xFFFFC0C0, 0xC0FCFCC0, 0xC0C0FFFF };
constexpr uint32_t MENU_N[3] = { 0xC3E3E3F3, 0xF3DBDBCF, 0xCFC7C7C3 };
constexpr uint32_t MENU_U[3] = { 0xC3C3C3C3, 0xC3C3C3C3, 0xC3C3FFFF };
constexpr uint32_t MENU_t_lower[3] = { 0x18181818, 0x7E7E1818, 0x18181E1E };
constexpr uint32_t MENU_h_lower[3] = { 0x60606060, 0x7E7E6666, 0x66666666 };
constexpr uint32_t LETTER_F[3] = { 0xFFFFC0C0, 0xC0FCFCC0, 0xC0C0C0C0 };
constexpr uint32_t LETTER_R[3] = { 0xFEFEC3C3, 0xC3FCFCCC, 0xC6C6C3C3 };
constexpr uint32_t LETTER_E[3] = { 0xFFFFC0C0, 0xC0FCFCC0, 0xC0C0FFFF };
constexpr uint32_t LETTER_B[3] = { 0xFEFEC3C3, 0xC3FCFCC3, 0xC3C3FEFE };
constexpr uint32_t LETTER_U[3] = { 0xC3C3C3C3, 0xC3C3C3C3, 0xC3C3FFFF };
constexpr uint32_t LETTER_S[3] = { 0xFFFFC0C0, 0xC0FFFF03, 0x0303FFFF };
constexpr uint32_t LETTER_Y[3] = { 0xC3C3C3C3, 0x663C1818, 0x18181818 };

