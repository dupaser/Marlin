#
# custom_board.py
#
# - For build.address replace VECT_TAB_ADDR to relocate the firmware
# - For build.ldscript use one of the linker scripts in buildroot/share/PlatformIO/ldscripts
#
import pioutil
if pioutil.is_pio_build():
<<<<<<< HEAD
	import marlin
	board = marlin.env.BoardConfig()

	address = board.get("build.address", "")
	if address:
		marlin.relocate_firmware(address)

	ldscript = board.get("build.ldscript", "")
	if ldscript:
		marlin.custom_ld_script(ldscript)
=======
    import marlin
    board = pioutil.env.BoardConfig()

    address = board.get("build.address", "")
    if address:
        marlin.relocate_firmware(address)

    ldscript = board.get("build.ldscript", "")
    if ldscript:
        marlin.custom_ld_script(ldscript)
>>>>>>> origin/release-2.1.3-beta2
