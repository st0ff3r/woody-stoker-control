PK2CMD = pk2cmd -PPIC18F4620
PROCESSOR = 18f4620
MODEL = pic16
#PROCESSOR = 16f887
#MODEL = pic14
GPSIM_PROCESSOR = pic18f4620
SDCC = /opt/local/bin/sdcc
GPLINK = /opt/local/bin/gplink
GPASM = /opt/local/bin/gpasm
GPSIM =/usr/local/bin/gpsim

all:	test glcd menu_system pillefyrsstyring

test: test.c
	$(SDCC) \
	--verbose \
	-V \
	-m$(MODEL) \
	--use-crt=crt0.o \
	--use-non-free \
	-p$(PROCESSOR) \
	$<


pillefyrsstyring: pillefyrsstyring.c
	$(SDCC) \
	--verbose \
	-V \
	-m$(MODEL) \
	--use-crt=crt0.o \
	--use-non-free \
	-I"./" glcd.o \
	-Wl '-m' \
	-p$(PROCESSOR) \
	$<
#	-Wl '-m -s18f4620.lkr' \
#	-I"./" glcd.o menu_system.o \


glcd: glcd.c
	$(SDCC) \
	--verbose \
	-V \
	-m$(MODEL) \
	--use-non-free \
	-p$(PROCESSOR) \
	-c $<

menu_system: menu_system.c
	$(SDCC) \
	--verbose \
	-V \
	-m$(MODEL) \
	--use-non-free \
	-p$(PROCESSOR) \
	-c $<

pillefyrsstyring.hex: pillefyrsstyring.o
	$(GPLINK) \
	-c \
	-o $@ \
	-m \
	-r \
	-d \
	pillefyrsstyring pillefyrsstyring.o crt0.o \
	$^

pillefyrsstyring.o: pillefyrsstyring.asm
	$(GPASM) \
	--extended \
	-pp$(PROCESSOR) \
	-c $<

pillefyrsstyring.asm: pillefyrsstyring.c
	$(SDCC) \
	-V \
	--verbose \
	-S \
	--debug \
	-m$(MODEL) \
	--use-crt=crt0.o \
	--use-non-free \
	-p$(PROCESSOR) $<

clean:
	rm -f *.adb *.asm *.cod *.cof *.hex *.lst *.map *.o *.sym *.lib

sim:
	$(GPSIM) -p$(GPSIM_PROCESSOR) -c pillefyrsstyring.stc -s pillefyrsstyring.cod
	# && killall -9 X11.bin

flash:
	$(PK2CMD) -F pillefyrsstyring.hex -M

flash_master:
	$(PK2CMD) -F pillefyrsstyring_master.hex -M

on:
	$(PK2CMD) -R -T

off:
	$(PK2CMD) -R

