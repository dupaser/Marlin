#
# Set upload_command
#
#  Windows: bossac.exe
#  Other: leave unchanged
#
import pioutil
if pioutil.is_pio_build():
<<<<<<< HEAD
	import platform
	current_OS = platform.system()

	if current_OS == 'Windows':

		Import("env")

		# Use bossac.exe on Windows
		env.Replace(
			UPLOADCMD="bossac --info --unlock --write --verify --reset --erase -U false --boot $SOURCE"
		)
=======
    import platform
    current_OS = platform.system()

    if current_OS == 'Windows':

        env = pioutil.env

        # Use bossac.exe on Windows
        env.Replace(
            UPLOADCMD="bossac --info --unlock --write --verify --reset --erase -U false --boot $SOURCE"
        )
>>>>>>> origin/release-2.1.3-beta2
