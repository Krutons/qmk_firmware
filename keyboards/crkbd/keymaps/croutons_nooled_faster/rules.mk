MCU = atmega32u4

# Bootloader selection
BOOTLOADER = caterina

BOOTMAGIC_ENABLE = yes      # Enable Bootmagic Lite
MOUSEKEY_ENABLE = yes    # Mouse keys
EXTRAKEY_ENABLE = yes       # Audio control and System control
CONSOLE_ENABLE = no         # Console for debug
COMMAND_ENABLE   = no  # Commands for debug and configuration
NKRO_ENABLE = yes           # Enable N-Key Rollover
RGBLIGHT_ENABLE = yes   # Enable WS2812 RGB underlight
AUDIO_ENABLE = no           # Audio output
RGB_MATRIX_ENABLE = yes
RGB_MATRIX_DRIVER = ws2812
OLED_ENABLE     = no
OLED_DRIVER     = SSD1306
LTO_ENABLE      = no
COMBO_ENABLE = yes
LEADER_ENABLE = yes
UNICODE_ENABLE   = no  # Unicode
SWAP_HANDS_ENABLE= no  # Allow swapping hands of keyboard
REPEAT_KEY_ENABLE = no
DEFAULT_FOLDER = crkbd/rev1
SRC += babblePaste.c babl_windows.c babl_mac.c
EXTRAFLAGS        += -flto
