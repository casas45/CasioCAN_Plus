goil:
	goil --target=cortex-m/armv6m/stm32g0b1 --templates=../../../../../../goil/templates/ readbutton_isr.oil

clean:
	rm -rf readbutton_isr build readbutton_isr.map readbutton_isr_exe make.py build.py readbutton_isr_exe.hex

flash:
	openocd -f board/st_nucleo_g0.cfg -c "program readbutton_isr_exe.hex verify reset" -c shutdown

#---open a debug server conection------------------------------------------------------------------
open :
	openocd -f board/st_nucleo_g0.cfg
#	JLinkGDBServer -if SWD -device stm32g0b1re -nogui

#---launch a debug session, NOTE: is mandatory to previously open a debug server session-----------
debug :
	arm-none-eabi-gdb readbutton_isr_exe.elf -iex "add-auto-load-safe-path /home/ld_casas/Workspace/TemplateTrampoline/trampolineRTOS/examples/cortex-m/armv6m/stm32g0b1/Nucleo/readbutton_isr/.gdbinit"