TARGETARMFIR=rt_fir_arm
OBJSARMFIR=rt_fir_arm.o

TARGETIIR=rt_biquad
OBJSIIR=rt_biquad.o ece486_biquad.o

TARGETARMIIR=rt_biquad_arm
OBJSARMIIR=rt_biquad_arm.o

INSTALLDIR = /usr/local/stmdev/


ARCH = STM32L476xx

CC=arm-none-eabi-gcc
LD=arm-none-eabi-ld
AS=arm-none-eabi-as
OBJCOPY=arm-none-eabi-objcopy

INCDIRS = -I$(INSTALLDIR)/include -I.
LIBDIRS = -L$(INSTALLDIR)/lib

LIBS=  -lece486_$(ARCH) -l$(ARCH) -lcmsis_dsp_$(ARCH)

LINKSCRIPT = $(INSTALLDIR)/lib/$(ARCH)_FLASH.ld

CFLAGS = -mcpu=cortex-m4 -mthumb -O3 -Wall  \
         -fomit-frame-pointer -fno-strict-aliasing -fdata-sections \
         -include stm32l4xx_hal_conf.h -DARM_MATH_CM4 -D$(ARCH) \
         -mfpu=fpv4-sp-d16 -mfloat-abi=softfp $(INCDIRS) \
         -fsingle-precision-constant -ffunction-sections

LDFLAGS = -u _printf_float \
	  -Wl,-T$(LINKSCRIPT) \
	  -static \
          -Wl,--gc-sections $(LIBDIRS)

.PHONY : all flash clean debug
all: $(TARGETARMFIR) $(TARGETARMFIR).bin $(TARGETARMIIR) $(TARGETARMIIR).bin $(TARGETIIR) $(TARGETIIR).bin

debug : CFLAGS += -DDEBUG -g -Og
debug : LDFLAGS += -Wl,-Map,$(TARGET).map

debug : all


$(TARGETIIR): $(OBJSIIR)
	$(CC)  -o $(TARGETIIR) $(CFLAGS) $(LDFLAGS) $(OBJSIIR) $(LIBS)

$(TARGETIIR).bin: $(TARGETIIR)
	$(OBJCOPY) -Obinary $(TARGETIIR) $(TARGETIIR).bin


$(TARGETARMIIR): $(OBJSARMIIR)
	$(CC)  -o $(TARGETARMIIR) $(CFLAGS) $(LDFLAGS) $(OBJSARMIIR) $(LIBS)

$(TARGETARMIIR).bin: $(TARGETARMIIR)
	$(OBJCOPY) -Obinary $(TARGETARMIIR) $(TARGETARMIIR).bin

$(TARGETARMFIR): $(OBJSARMFIR)
	$(CC)  -o $(TARGETARMFIR) $(CFLAGS) $(LDFLAGS) $(OBJSARMFIR) $(LIBS)

$(TARGETARMFIR).bin: $(TARGETARMFIR)
	$(OBJCOPY) -Obinary $(TARGETARMFIR) $(TARGETARMFIR).bin


#####################################################################
## individual make rules
iir: $(TARGETIIR) $(TARGETIIR).bin
$(TARGETIIR): $(OBJSIIR)
	$(CC)  -o $(TARGETIIR) $(CFLAGS) $(LDFLAGS) $(OBJSIIR) $(LIBS)

$(TARGETIIR).bin: $(TARGETIIR)
	$(OBJCOPY) -Obinary $(TARGETIIR) $(TARGETIIR).bin

arm_iir: $(TARGETARMIIR) $(TARGETARMIIR).bin
$(TARGETARMIIR): $(OBJSARMIIR)
	$(CC)  -o $(TARGETARMIIR) $(CFLAGS) $(LDFLAGS) $(OBJSARMIIR) $(LIBS)

$(TARGETARMIIR).bin: $(TARGETARMIIR)
	$(OBJCOPY) -Obinary $(TARGETARMIIR) $(TARGETARMIIR).bin

arm_fir: $(TARGETARMFIR) $(TARGETARMFIR).bin
$(TARGETARMFIR): $(OBJSARMFIR)
	$(CC)  -o $(TARGETARMFIR) $(CFLAGS) $(LDFLAGS) $(OBJSARMFIR) $(LIBS)

$(TARGETARMFIR).bin: $(TARGETARMFIR)
	$(OBJCOPY) -Obinary $(TARGETARMFIR) $(TARGETARMFIR).bin

###################################################################
## flash rules
flash_iir: $(TARGETIIR).bin
	st-flash write $(TARGETIIR).bin 0x08000000

flash_arm_iir: $(TARGETARMIIR).bin
	st-flash write $(TARGETARMIIR).bin 0x08000000

flash_arm_fir: $(TARGETARMFIR).bin
	st-flash write $(TARGETARMFIR).bin 0x08000000

#####################################################################
## clean rules
clean_iir:
	rm -f $(OBJSIIR) $(TARGETIIR).bin $(TARGETIIR).map $(TARGETIIR)

clean_arm_iir:
	rm -f $(OBJSARMIIR) $(TARGETARMIIR).bin $(TARGETARMIIR).map $(TARGETARMIIR)

clean_arm_fir:
	rm -f $(OBJSARMFIR) $(TARGETARMFIR).bin $(TARGETARMFIR).map $(TARGETARMFIR)

clean:
	rm -f $(OBJS) $(TARGET).bin $(TARGET).map $(TARGET)
	rm -f $(OBJSIIR) $(TARGETIIR).bin $(TARGETIIR).map $(TARGETIIR)
	rm -f $(OBJSARMFIR) $(TARGETARMFIR).bin $(TARGETARMFIR).map $(TARGETARMFIR)
