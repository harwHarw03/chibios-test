ifeq ($(USE_SMART_BUILD),yes)
ifneq ($(findstring HAL_USE_RTC TRUE,$(HALCONF)),)
PLATFORMSRC += $(CHIBIOS)/os/hal/ports/RP/LLD/RTCv1/hal_rtc_lld.c
endif
else
PLATFORMSRC += $(CHIBIOS)/os/hal/ports/RP/LLD/RTCv1/hal_rtc_lld.c
endif

PLATFORMINC += $(CHIBIOS)/os/hal/ports/RP/LLD/RTCv1
