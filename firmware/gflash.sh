#!/bin/sh
openocd -f ./stm32f407g.cfg -c "reset_config trst_only combined" -c "program build/FMRC_FIRMWARE.elf verify reset exit"

