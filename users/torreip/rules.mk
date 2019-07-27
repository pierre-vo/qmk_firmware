SRC += torreip.c \
       process_records.c

ifneq ("$(wildcard $(USER_PATH)/secrets.c)","")
  SRC += secrets.c
endif

ifeq ($(strip $(NO_SECRETS)), yes)
    OPT_DEFS += -DNO_SECRETS
endif

ifeq ($(strip $(RGBLIGHT_ENABLE)), yes)
  SRC += rgb_stuff.c
  ifeq ($(strip $(INDICATOR_LIGHTS)), yes)
      OPT_DEFS += -DINDICATOR_LIGHTS
  endif
  ifeq ($(strip $(RGBLIGHT_TWINKLE)), yes)
    OPT_DEFS += -DRGBLIGHT_TWINKLE
  endif
  ifeq ($(strip $(RGBLIGHT_NOEEPROM)), yes)
    OPT_DEFS += -DRGBLIGHT_NOEEPROM
  endif
endif


