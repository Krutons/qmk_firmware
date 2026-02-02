#pragma once
#define MK_3_SPEED
#define MK_MOMENTARY_ACCEL

#ifndef NO_DEBUG
    #define NO_DEBUG
#endif // !NO_DEBUG
#if !defined(NO_PRINT) && !defined(CONSOLE_ENABLE)
    #define NO_PRINT
#endif // !NO_PRINT

#define USE_BABBLEPASTE
#define BABL_WINDOWS
#define BABL_MAC

#define BABL_OSKEYS
#define BABL_APP
#define BABL_MOVE

#define COMBO_COUNT 22
#define TAPPING_TERM 200
#define TAPPING_FORCE_HOLD
#define ONESHOT_TIMEOUT 3000

#define LEADER_TIMEOUT 450
#define LEADER_PER_KEY_TIMING
