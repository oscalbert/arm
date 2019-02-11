PROJECT = blink1

# -----------------------------
# tools
# -----------------------------
CC = arm-none-eabi-gcc
LD = arm-none-eabi-ld
OBJCOPY = arm-none-eabi-objcopy
OBJDUMP = arm-none-eabi-objdump
SIZE = arm-none-eabi-size


# -----------------------------
# external libs
# -----------------------------
ifndef CM3_DIR
  $(error CM3_DIR should point to your libopencm3 directory)
endif


# -----------------------------
# sources
# -----------------------------
SRCS = main.c

# -----------------------------
# compile options
# -----------------------------
CFLAGS = -DSTM32F4
CFLAGS += -mthumb -mcpu=cortex-m4
CFLAGS += -mfloat-abi=hard
CFLAGS += -Os
CGLAGS += -Wall -Wextra -Wundef -Wshadow -Wredundant-decls
CFLAGS += -fno-common -ffunction-sections -fdata-sections
CFLAGS += -I$(CM3_DIR)/include

# -----------------------------
# link options
# -----------------------------
define get_lib_path
    $(shell dirname $(shell $(CC) $(CFLAGS) -print-file-name=$(1)))
endef
LIBS = -lopencm3_stm32f4 -lc -lgcc -lnosys
LIBS += -L $(call get_lib_path,libc.a)
LIBS += -L $(call get_lib_path,libgcc.a)
LIBS += -L $(call get_lib_path,libnosys.a)
LIBS += -L$(CM3_DIR)/lib

LDFLAGS = -Map=$(PROJECT).map --cref
LDFLAGS += --static
LDFLAGS += -T stm32/f4/stm32f405x6.ld


$(PROJECT).hex: $(PROJECT).elf
	$(OBJCOPY) -O ihex $< $@

OBJS = $(subst .c,.o, $(SRCS))


$(PROJECT).elf: $(OBJS)
	$(LD) -o $@ $(OBJS) \
          --start-group $(LIBS) --end-group \
          $(LDFLAGS)
	$(SIZE) $@
	$(OBJDUMP) -S $@ > $(PROJECT).disa


%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@


.PHONY: flash
flash: $(PROJECT).hex
	st-flash --serial /dev/ttyACM0 --format ihex write $<

.PHONY: clean
clean:
	rm -f *.o *.hex *.elf *.map *.disa
