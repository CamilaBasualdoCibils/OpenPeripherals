#pragma once
#include <boost/describe/enum.hpp>
#include <linux/input.h>
namespace OpenPeripherals::Evdev{
    enum class EvDevCodes {
    // ================================================================
    // EV_SYN
    // ================================================================
    SynReport = SYN_REPORT,
    SynConfig = SYN_CONFIG,
    SynMtReport = SYN_MT_REPORT,
    SynDropped = SYN_DROPPED,

    // ================================================================
    // EV_KEY - keyboard keys
    // ================================================================
    KeyReserved = KEY_RESERVED,
    KeyEsc = KEY_ESC,
    Key1 = KEY_1,
    Key2 = KEY_2,
    Key3 = KEY_3,
    Key4 = KEY_4,
    Key5 = KEY_5,
    Key6 = KEY_6,
    Key7 = KEY_7,
    Key8 = KEY_8,
    Key9 = KEY_9,
    Key0 = KEY_0,
    KeyMinus = KEY_MINUS,
    KeyEqual = KEY_EQUAL,
    KeyBackspace = KEY_BACKSPACE,
    KeyTab = KEY_TAB,

    KeyQ = KEY_Q,
    KeyW = KEY_W,
    KeyE = KEY_E,
    KeyR = KEY_R,
    KeyT = KEY_T,
    KeyY = KEY_Y,
    KeyU = KEY_U,
    KeyI = KEY_I,
    KeyO = KEY_O,
    KeyP = KEY_P,

    KeyLeftBrace = KEY_LEFTBRACE,
    KeyRightBrace = KEY_RIGHTBRACE,
    KeyEnter = KEY_ENTER,
    KeyLeftCtrl = KEY_LEFTCTRL,

    KeyA = KEY_A,
    KeyS = KEY_S,
    KeyD = KEY_D,
    KeyF = KEY_F,
    KeyG = KEY_G,
    KeyH = KEY_H,
    KeyJ = KEY_J,
    KeyK = KEY_K,
    KeyL = KEY_L,

    KeySemicolon = KEY_SEMICOLON,
    KeyApostrophe = KEY_APOSTROPHE,
    KeyGrave = KEY_GRAVE,
    KeyLeftShift = KEY_LEFTSHIFT,
    KeyBackslash = KEY_BACKSLASH,

    KeyZ = KEY_Z,
    KeyX = KEY_X,
    KeyC = KEY_C,
    KeyV = KEY_V,
    KeyB = KEY_B,
    KeyN = KEY_N,
    KeyM = KEY_M,

    KeyComma = KEY_COMMA,
    KeyDot = KEY_DOT,
    KeySlash = KEY_SLASH,
    KeyRightShift = KEY_RIGHTSHIFT,
    KeyKPAsterisk = KEY_KPASTERISK,
    KeyLeftAlt = KEY_LEFTALT,
    KeySpace = KEY_SPACE,
    KeyCapsLock = KEY_CAPSLOCK,

    KeyF1 = KEY_F1,
    KeyF2 = KEY_F2,
    KeyF3 = KEY_F3,
    KeyF4 = KEY_F4,
    KeyF5 = KEY_F5,
    KeyF6 = KEY_F6,
    KeyF7 = KEY_F7,
    KeyF8 = KEY_F8,
    KeyF9 = KEY_F9,
    KeyF10 = KEY_F10,
    KeyF11 = KEY_F11,
    KeyF12 = KEY_F12,

    KeyNumLock = KEY_NUMLOCK,
    KeyScrollLock = KEY_SCROLLLOCK,

    KeyKP7 = KEY_KP7,
    KeyKP8 = KEY_KP8,
    KeyKP9 = KEY_KP9,
    KeyKPMinus = KEY_KPMINUS,
    KeyKP4 = KEY_KP4,
    KeyKP5 = KEY_KP5,
    KeyKP6 = KEY_KP6,
    KeyKPPlus = KEY_KPPLUS,
    KeyKP1 = KEY_KP1,
    KeyKP2 = KEY_KP2,
    KeyKP3 = KEY_KP3,
    KeyKP0 = KEY_KP0,
    KeyKPDot = KEY_KPDOT,

    KeyZenkakuHankaku = KEY_ZENKAKUHANKAKU,
    Key102nd = KEY_102ND,
    KeyRo = KEY_RO,
    KeyKatakana = KEY_KATAKANA,
    KeyHiragana = KEY_HIRAGANA,
    KeyHenkan = KEY_HENKAN,
    KeyKatakanaHiragana = KEY_KATAKANAHIRAGANA,
    KeyMuhenkan = KEY_MUHENKAN,
    KeyKPJpComma = KEY_KPJPCOMMA,

    KeyKPEnter = KEY_KPENTER,
    KeyRightCtrl = KEY_RIGHTCTRL,
    KeyKPSlash = KEY_KPSLASH,
    KeySysRq = KEY_SYSRQ,
    KeyRightAlt = KEY_RIGHTALT,
    KeyLineFeed = KEY_LINEFEED,
    KeyHome = KEY_HOME,
    KeyUp = KEY_UP,
    KeyPageUp = KEY_PAGEUP,
    KeyLeft = KEY_LEFT,
    KeyRight = KEY_RIGHT,
    KeyEnd = KEY_END,
    KeyDown = KEY_DOWN,
    KeyPageDown = KEY_PAGEDOWN,
    KeyInsert = KEY_INSERT,
    KeyDelete = KEY_DELETE,

    KeyMute = KEY_MUTE,
    KeyVolumeDown = KEY_VOLUMEDOWN,
    KeyVolumeUp = KEY_VOLUMEUP,
    KeyPower = KEY_POWER,
    KeyKPEqual = KEY_KPEQUAL,
    KeyPause = KEY_PAUSE,

    KeyLeftMeta = KEY_LEFTMETA,
    KeyRightMeta = KEY_RIGHTMETA,
    KeyCompose = KEY_COMPOSE,

    KeyStop = KEY_STOP,
    KeyAgain = KEY_AGAIN,
    KeyProps = KEY_PROPS,
    KeyUndo = KEY_UNDO,
    KeyFront = KEY_FRONT,
    KeyCopy = KEY_COPY,
    KeyOpen = KEY_OPEN,
    KeyPaste = KEY_PASTE,
    KeyFind = KEY_FIND,
    KeyCut = KEY_CUT,
    KeyHelp = KEY_HELP,
    KeyMenu = KEY_MENU,
    KeyCalc = KEY_CALC,
    KeySetup = KEY_SETUP,
    KeySleep = KEY_SLEEP,
    KeyWakeUp = KEY_WAKEUP,
    KeyFile = KEY_FILE,
    KeySendFile = KEY_SENDFILE,
    KeyDeleteFile = KEY_DELETEFILE,
    KeyXfer = KEY_XFER,
    KeyProg1 = KEY_PROG1,
    KeyProg2 = KEY_PROG2,
    KeyWWW = KEY_WWW,
    KeyMSDOS = KEY_MSDOS,
    KeyCoffee = KEY_COFFEE,
    KeyRotateDisplay = KEY_ROTATE_DISPLAY,
    KeyCycleWindows = KEY_CYCLEWINDOWS,
    KeyMail = KEY_MAIL,
    KeyBookmarks = KEY_BOOKMARKS,
    KeyComputer = KEY_COMPUTER,
    KeyBack = KEY_BACK,
    KeyForward = KEY_FORWARD,
    KeyCloseCD = KEY_CLOSECD,
    KeyEjectCD = KEY_EJECTCD,
    KeyNextSong = KEY_NEXTSONG,
    KeyPlayPause = KEY_PLAYPAUSE,
    KeyPreviousSong = KEY_PREVIOUSSONG,
    KeyStopCD = KEY_STOPCD,
    KeyRecord = KEY_RECORD,
    KeyRewind = KEY_REWIND,
    KeyPhone = KEY_PHONE,
    KeyConfig = KEY_CONFIG,
    KeyHomePage = KEY_HOMEPAGE,
    KeyRefresh = KEY_REFRESH,
    KeyExit = KEY_EXIT,

    // ================================================================
    // EV_KEY - buttons
    // ================================================================
    BtnMisc = BTN_MISC,
    Btn0 = BTN_0,
    Btn1 = BTN_1,
    Btn2 = BTN_2,
    Btn3 = BTN_3,
    Btn4 = BTN_4,
    Btn5 = BTN_5,
    Btn6 = BTN_6,
    Btn7 = BTN_7,
    Btn8 = BTN_8,
    Btn9 = BTN_9,

    BtnMouse = BTN_MOUSE,
    BtnLeft = BTN_LEFT,
    BtnRight = BTN_RIGHT,
    BtnMiddle = BTN_MIDDLE,
    BtnSide = BTN_SIDE,
    BtnExtra = BTN_EXTRA,
    BtnForward = BTN_FORWARD,
    BtnBack = BTN_BACK,
    BtnTask = BTN_TASK,

    BtnJoystick = BTN_JOYSTICK,
    BtnTrigger = BTN_TRIGGER,
    BtnThumb = BTN_THUMB,
    BtnThumb2 = BTN_THUMB2,
    BtnTop = BTN_TOP,
    BtnTop2 = BTN_TOP2,
    BtnPinkie = BTN_PINKIE,
    BtnBase = BTN_BASE,
    BtnBase2 = BTN_BASE2,
    BtnBase3 = BTN_BASE3,
    BtnBase4 = BTN_BASE4,
    BtnBase5 = BTN_BASE5,
    BtnBase6 = BTN_BASE6,
    BtnDead = BTN_DEAD,

    BtnGamepad = BTN_GAMEPAD,
    BtnSouth = BTN_SOUTH,
    BtnEast = BTN_EAST,
    BtnC = BTN_C,
    BtnNorth = BTN_NORTH,
    BtnWest = BTN_WEST,
    BtnZ = BTN_Z,
    BtnTL = BTN_TL,
    BtnTR = BTN_TR,
    BtnTL2 = BTN_TL2,
    BtnTR2 = BTN_TR2,
    BtnSelect = BTN_SELECT,
    BtnStart = BTN_START,
    BtnMode = BTN_MODE,
    BtnThumbL = BTN_THUMBL,
    BtnThumbR = BTN_THUMBR,

    BtnDigi = BTN_DIGI,
    BtnToolPen = BTN_TOOL_PEN,
    BtnToolRubber = BTN_TOOL_RUBBER,
    BtnToolBrush = BTN_TOOL_BRUSH,
    BtnToolPencil = BTN_TOOL_PENCIL,
    BtnToolAirbrush = BTN_TOOL_AIRBRUSH,
    BtnToolFinger = BTN_TOOL_FINGER,
    BtnToolMouse = BTN_TOOL_MOUSE,
    BtnToolLens = BTN_TOOL_LENS,
    BtnTouch = BTN_TOUCH,
    BtnStylus = BTN_STYLUS,
    BtnStylus2 = BTN_STYLUS2,

    BtnWheel = BTN_WHEEL,
    BtnGearDown = BTN_GEAR_DOWN,
    BtnGearUp = BTN_GEAR_UP,

    // ================================================================
    // EV_REL
    // ================================================================
    RelX = REL_X,
    RelY = REL_Y,
    RelZ = REL_Z,
    RelRX = REL_RX,
    RelRY = REL_RY,
    RelRZ = REL_RZ,
    RelHWheel = REL_HWHEEL,
    RelDial = REL_DIAL,
    RelWheel = REL_WHEEL,
    RelMisc = REL_MISC,
    RelReserved = REL_RESERVED,
    RelWheelHiRes = REL_WHEEL_HI_RES,
    RelHWheelHiRes = REL_HWHEEL_HI_RES,

    // ================================================================
    // EV_ABS
    // ================================================================
    AbsX = ABS_X,
    AbsY = ABS_Y,
    AbsZ = ABS_Z,
    AbsRX = ABS_RX,
    AbsRY = ABS_RY,
    AbsRZ = ABS_RZ,
    AbsThrottle = ABS_THROTTLE,
    AbsRudder = ABS_RUDDER,
    AbsWheel = ABS_WHEEL,
    AbsGas = ABS_GAS,
    AbsBrake = ABS_BRAKE,

    AbsHat0X = ABS_HAT0X,
    AbsHat0Y = ABS_HAT0Y,
    AbsHat1X = ABS_HAT1X,
    AbsHat1Y = ABS_HAT1Y,
    AbsHat2X = ABS_HAT2X,
    AbsHat2Y = ABS_HAT2Y,
    AbsHat3X = ABS_HAT3X,
    AbsHat3Y = ABS_HAT3Y,

    AbsPressure = ABS_PRESSURE,
    AbsDistance = ABS_DISTANCE,
    AbsTiltX = ABS_TILT_X,
    AbsTiltY = ABS_TILT_Y,
    AbsToolWidth = ABS_TOOL_WIDTH,
    AbsVolume = ABS_VOLUME,
    AbsProfile = ABS_PROFILE,
    AbsMisc = ABS_MISC,

    AbsMtSlot = ABS_MT_SLOT,
    AbsMtTouchMajor = ABS_MT_TOUCH_MAJOR,
    AbsMtTouchMinor = ABS_MT_TOUCH_MINOR,
    AbsMtWidthMajor = ABS_MT_WIDTH_MAJOR,
    AbsMtWidthMinor = ABS_MT_WIDTH_MINOR,
    AbsMtOrientation = ABS_MT_ORIENTATION,
    AbsMtPositionX = ABS_MT_POSITION_X,
    AbsMtPositionY = ABS_MT_POSITION_Y,
    AbsMtToolType = ABS_MT_TOOL_TYPE,
    AbsMtBlobId = ABS_MT_BLOB_ID,
    AbsMtTrackingId = ABS_MT_TRACKING_ID,
    AbsMtPressure = ABS_MT_PRESSURE,
    AbsMtDistance = ABS_MT_DISTANCE,
    AbsMtToolX = ABS_MT_TOOL_X,
    AbsMtToolY = ABS_MT_TOOL_Y,

    // ================================================================
    // EV_SW
    // ================================================================
    SwLid = SW_LID,
    SwTabletMode = SW_TABLET_MODE,
    SwHeadphoneInsert = SW_HEADPHONE_INSERT,
    SwRfkillAll = SW_RFKILL_ALL,
    SwMicrophoneInsert = SW_MICROPHONE_INSERT,
    SwDock = SW_DOCK,
    SwLineoutInsert = SW_LINEOUT_INSERT,
    SwJackPhysicalInsert = SW_JACK_PHYSICAL_INSERT,
    SwVideoOutInsert = SW_VIDEOOUT_INSERT,
    SwCameraLensCover = SW_CAMERA_LENS_COVER,
    SwKeypadSlide = SW_KEYPAD_SLIDE,
    SwFrontProximity = SW_FRONT_PROXIMITY,
    SwRotateLock = SW_ROTATE_LOCK,
    SwLineinInsert = SW_LINEIN_INSERT,
    SwMuteDevice = SW_MUTE_DEVICE,
    SwPenInserted = SW_PEN_INSERTED,
    SwMachineCover = SW_MACHINE_COVER,

    // ================================================================
    // EV_LED
    // ================================================================
    LedNumLock = LED_NUML,
    LedCapsLock = LED_CAPSL,
    LedScrollLock = LED_SCROLLL,
    LedCompose = LED_COMPOSE,
    LedKana = LED_KANA,
    LedSleep = LED_SLEEP,
    LedSuspend = LED_SUSPEND,
    LedMute = LED_MUTE,
    LedMisc = LED_MISC,
    LedMail = LED_MAIL,
    LedCharging = LED_CHARGING,

    // ================================================================
    // EV_SND
    // ================================================================
    SndClick = SND_CLICK,
    SndBell = SND_BELL,
    SndTone = SND_TONE,

    // ================================================================
    // EV_REP
    // ================================================================
    RepDelay = REP_DELAY,
    RepPeriod = REP_PERIOD,

    // ================================================================
    // EV_MSC
    // ================================================================
    MscSerial = MSC_SERIAL,
    MscPulseLed = MSC_PULSELED,
    MscGesture = MSC_GESTURE,
    MscRaw = MSC_RAW,
    MscScan = MSC_SCAN,
    MscTimestamp = MSC_TIMESTAMP,

    // ================================================================
    // EV_FF
    // ================================================================
    FfRumble = FF_RUMBLE,
    FfPeriodic = FF_PERIODIC,
    FfConstant = FF_CONSTANT,
    FfSpring = FF_SPRING,
    FfFriction = FF_FRICTION,
    FfDamper = FF_DAMPER,
    FfInertia = FF_INERTIA,
    FfRamp = FF_RAMP,

    FfSquare = FF_SQUARE,
    FfTriangle = FF_TRIANGLE,
    FfSine = FF_SINE,
    FfSawUp = FF_SAW_UP,
    FfSawDown = FF_SAW_DOWN,
    FfCustom = FF_CUSTOM,

    FfGain = FF_GAIN,
    FfAutocenter = FF_AUTOCENTER,

    // ================================================================
    // EV_FF_STATUS
    // ================================================================
    FfStatusStopped = FF_STATUS_STOPPED,
    FfStatusPlaying = FF_STATUS_PLAYING,
};

// Keep this explicit list in sync with EvDevCodes. The convenient
// BOOST_DESCRIBE_ENUM macro is limited to 64 enumerators.
BOOST_DESCRIBE_ENUM_BEGIN(EvDevCodes)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, SynReport)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, SynConfig)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, SynMtReport)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, SynDropped)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, KeyReserved)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, KeyEsc)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, Key1)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, Key2)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, Key3)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, Key4)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, Key5)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, Key6)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, Key7)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, Key8)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, Key9)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, Key0)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, KeyMinus)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, KeyEqual)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, KeyBackspace)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, KeyTab)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, KeyQ)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, KeyW)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, KeyE)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, KeyR)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, KeyT)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, KeyY)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, KeyU)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, KeyI)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, KeyO)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, KeyP)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, KeyLeftBrace)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, KeyRightBrace)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, KeyEnter)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, KeyLeftCtrl)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, KeyA)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, KeyS)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, KeyD)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, KeyF)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, KeyG)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, KeyH)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, KeyJ)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, KeyK)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, KeyL)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, KeySemicolon)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, KeyApostrophe)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, KeyGrave)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, KeyLeftShift)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, KeyBackslash)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, KeyZ)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, KeyX)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, KeyC)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, KeyV)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, KeyB)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, KeyN)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, KeyM)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, KeyComma)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, KeyDot)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, KeySlash)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, KeyRightShift)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, KeyKPAsterisk)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, KeyLeftAlt)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, KeySpace)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, KeyCapsLock)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, KeyF1)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, KeyF2)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, KeyF3)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, KeyF4)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, KeyF5)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, KeyF6)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, KeyF7)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, KeyF8)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, KeyF9)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, KeyF10)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, KeyF11)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, KeyF12)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, KeyNumLock)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, KeyScrollLock)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, KeyKP7)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, KeyKP8)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, KeyKP9)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, KeyKPMinus)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, KeyKP4)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, KeyKP5)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, KeyKP6)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, KeyKPPlus)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, KeyKP1)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, KeyKP2)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, KeyKP3)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, KeyKP0)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, KeyKPDot)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, KeyZenkakuHankaku)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, Key102nd)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, KeyRo)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, KeyKatakana)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, KeyHiragana)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, KeyHenkan)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, KeyKatakanaHiragana)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, KeyMuhenkan)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, KeyKPJpComma)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, KeyKPEnter)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, KeyRightCtrl)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, KeyKPSlash)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, KeySysRq)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, KeyRightAlt)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, KeyLineFeed)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, KeyHome)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, KeyUp)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, KeyPageUp)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, KeyLeft)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, KeyRight)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, KeyEnd)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, KeyDown)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, KeyPageDown)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, KeyInsert)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, KeyDelete)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, KeyMute)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, KeyVolumeDown)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, KeyVolumeUp)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, KeyPower)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, KeyKPEqual)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, KeyPause)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, KeyLeftMeta)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, KeyRightMeta)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, KeyCompose)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, KeyStop)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, KeyAgain)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, KeyProps)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, KeyUndo)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, KeyFront)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, KeyCopy)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, KeyOpen)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, KeyPaste)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, KeyFind)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, KeyCut)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, KeyHelp)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, KeyMenu)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, KeyCalc)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, KeySetup)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, KeySleep)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, KeyWakeUp)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, KeyFile)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, KeySendFile)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, KeyDeleteFile)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, KeyXfer)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, KeyProg1)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, KeyProg2)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, KeyWWW)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, KeyMSDOS)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, KeyCoffee)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, KeyRotateDisplay)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, KeyCycleWindows)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, KeyMail)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, KeyBookmarks)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, KeyComputer)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, KeyBack)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, KeyForward)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, KeyCloseCD)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, KeyEjectCD)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, KeyNextSong)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, KeyPlayPause)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, KeyPreviousSong)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, KeyStopCD)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, KeyRecord)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, KeyRewind)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, KeyPhone)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, KeyConfig)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, KeyHomePage)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, KeyRefresh)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, KeyExit)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, BtnMisc)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, Btn0)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, Btn1)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, Btn2)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, Btn3)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, Btn4)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, Btn5)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, Btn6)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, Btn7)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, Btn8)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, Btn9)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, BtnMouse)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, BtnLeft)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, BtnRight)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, BtnMiddle)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, BtnSide)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, BtnExtra)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, BtnForward)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, BtnBack)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, BtnTask)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, BtnJoystick)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, BtnTrigger)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, BtnThumb)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, BtnThumb2)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, BtnTop)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, BtnTop2)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, BtnPinkie)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, BtnBase)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, BtnBase2)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, BtnBase3)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, BtnBase4)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, BtnBase5)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, BtnBase6)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, BtnDead)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, BtnGamepad)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, BtnSouth)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, BtnEast)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, BtnC)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, BtnNorth)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, BtnWest)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, BtnZ)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, BtnTL)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, BtnTR)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, BtnTL2)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, BtnTR2)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, BtnSelect)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, BtnStart)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, BtnMode)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, BtnThumbL)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, BtnThumbR)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, BtnDigi)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, BtnToolPen)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, BtnToolRubber)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, BtnToolBrush)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, BtnToolPencil)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, BtnToolAirbrush)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, BtnToolFinger)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, BtnToolMouse)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, BtnToolLens)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, BtnTouch)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, BtnStylus)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, BtnStylus2)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, BtnWheel)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, BtnGearDown)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, BtnGearUp)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, RelX)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, RelY)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, RelZ)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, RelRX)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, RelRY)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, RelRZ)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, RelHWheel)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, RelDial)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, RelWheel)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, RelMisc)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, RelReserved)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, RelWheelHiRes)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, RelHWheelHiRes)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, AbsX)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, AbsY)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, AbsZ)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, AbsRX)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, AbsRY)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, AbsRZ)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, AbsThrottle)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, AbsRudder)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, AbsWheel)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, AbsGas)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, AbsBrake)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, AbsHat0X)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, AbsHat0Y)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, AbsHat1X)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, AbsHat1Y)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, AbsHat2X)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, AbsHat2Y)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, AbsHat3X)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, AbsHat3Y)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, AbsPressure)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, AbsDistance)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, AbsTiltX)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, AbsTiltY)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, AbsToolWidth)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, AbsVolume)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, AbsProfile)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, AbsMisc)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, AbsMtSlot)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, AbsMtTouchMajor)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, AbsMtTouchMinor)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, AbsMtWidthMajor)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, AbsMtWidthMinor)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, AbsMtOrientation)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, AbsMtPositionX)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, AbsMtPositionY)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, AbsMtToolType)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, AbsMtBlobId)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, AbsMtTrackingId)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, AbsMtPressure)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, AbsMtDistance)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, AbsMtToolX)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, AbsMtToolY)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, SwLid)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, SwTabletMode)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, SwHeadphoneInsert)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, SwRfkillAll)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, SwMicrophoneInsert)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, SwDock)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, SwLineoutInsert)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, SwJackPhysicalInsert)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, SwVideoOutInsert)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, SwCameraLensCover)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, SwKeypadSlide)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, SwFrontProximity)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, SwRotateLock)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, SwLineinInsert)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, SwMuteDevice)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, SwPenInserted)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, SwMachineCover)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, LedNumLock)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, LedCapsLock)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, LedScrollLock)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, LedCompose)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, LedKana)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, LedSleep)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, LedSuspend)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, LedMute)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, LedMisc)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, LedMail)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, LedCharging)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, SndClick)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, SndBell)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, SndTone)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, RepDelay)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, RepPeriod)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, MscSerial)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, MscPulseLed)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, MscGesture)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, MscRaw)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, MscScan)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, MscTimestamp)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, FfRumble)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, FfPeriodic)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, FfConstant)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, FfSpring)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, FfFriction)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, FfDamper)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, FfInertia)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, FfRamp)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, FfSquare)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, FfTriangle)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, FfSine)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, FfSawUp)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, FfSawDown)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, FfCustom)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, FfGain)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, FfAutocenter)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, FfStatusStopped)
BOOST_DESCRIBE_ENUM_ENTRY(EvDevCodes, FfStatusPlaying)
BOOST_DESCRIBE_ENUM_END(EvDevCodes)

}
