# MCU name
MCU = RP2040

# Bootloader selection
BOOTLOADER = rp2040
CONVERT_TO = rp2040_ce

# Regular settings
MOUSEKEY_ENABLE = yes    # Mouse keys
CONSOLE_ENABLE = no         # Console for debug
COMMAND_ENABLE = no  # Commands for debug and configuration
COMBO_ENABLE = yes
LEADER_ENABLE = yes
LTO_ENABLE = yes

# HW settings
RGBLIGHT_ENABLE = no
RGB_MATRIX_ENABLE = yes
WS2812_DRIVER = vendor
OLED_ENABLE     = no
# POINTING_DEVICE_ENABLE = yes
# POINTING_DEVICE_DRIVER = azoteq_iqs5xx

DEFAULT_FOLDER = crkbd/rev1
# EXTRAFLAGS        += -flto
