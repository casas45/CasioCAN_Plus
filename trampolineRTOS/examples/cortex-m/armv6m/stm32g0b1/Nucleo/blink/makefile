goil:
	goil --target=cortex-m/armv6m/stm32g0b1 --templates=../../../../../../goil/templates/ blink.oil

clean:
	rm -rf blink build blink.map blink_exe blink_exe make.py build.py blink_exe.hex

flash:
	openocd -f board/st_nucleo_g0.cfg -c "program blink_exe.hex verify reset" -c shutdown