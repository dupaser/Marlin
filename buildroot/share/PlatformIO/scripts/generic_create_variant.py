#
# generic_create_variant.py
#
# Copy one of the variants from buildroot/platformio/variants into
# the appropriate framework variants folder, so that its contents
# will be picked up by PlatformIO just like any other variant.
#
<<<<<<< HEAD
import pioutil
if pioutil.is_pio_build():
	import os,shutil,marlin
	from SCons.Script import DefaultEnvironment
	from platformio import util

	env = DefaultEnvironment()

	#
	# Get the platform name from the 'platform_packages' option,
	# or look it up by the platform.class.name.
	#
	platform = env.PioPlatform()

	from platformio.package.meta import PackageSpec
	platform_packages = env.GetProjectOption('platform_packages')

	# Remove all tool items from platform_packages
	platform_packages = [x for x in platform_packages if not x.startswith("platformio/tool-")]

	if len(platform_packages) == 0:
		framewords = {
			"Ststm32Platform": "framework-arduinoststm32",
			"AtmelavrPlatform": "framework-arduino-avr"
		}
		platform_name = framewords[platform.__class__.__name__]
	else:
		platform_name = PackageSpec(platform_packages[0]).name

	if platform_name in [ "usb-host-msc", "usb-host-msc-cdc-msc", "usb-host-msc-cdc-msc-2", "usb-host-msc-cdc-msc-3", "tool-stm32duino", "biqu-bx-workaround", "main" ]:
		platform_name = "framework-arduinoststm32"

	FRAMEWORK_DIR = platform.get_package_dir(platform_name)
	assert os.path.isdir(FRAMEWORK_DIR)

	board = env.BoardConfig()

	#mcu_type = board.get("build.mcu")[:-2]
	variant = board.get("build.variant")
	#series = mcu_type[:7].upper() + "xx"

	# Prepare a new empty folder at the destination
	variant_dir = os.path.join(FRAMEWORK_DIR, "variants", variant)
	if os.path.isdir(variant_dir):
		shutil.rmtree(variant_dir)
	if not os.path.isdir(variant_dir):
		os.mkdir(variant_dir)

	# Source dir is a local variant sub-folder
	source_dir = os.path.join("buildroot/share/PlatformIO/variants", variant)
	assert os.path.isdir(source_dir)

	marlin.copytree(source_dir, variant_dir)
=======
import pioutil, re

marlin_variant_pattern = re.compile("marlin_.*")
if pioutil.is_pio_build():
    import shutil, marlin
    from pathlib import Path

    #
    # Get the platform name from the 'platform_packages' option,
    # or look it up by the platform.class.name.
    #
    env = pioutil.env
    platform = env.PioPlatform()

    from platformio.package.meta import PackageSpec
    platform_packages = env.GetProjectOption('platform_packages')

    # Remove all tool items from platform_packages
    platform_packages = [x for x in platform_packages if not x.startswith("platformio/tool-")]

    if len(platform_packages) == 0:
        framewords = {
            "Ststm32Platform": "framework-arduinoststm32",
            "AtmelavrPlatform": "framework-arduino-avr"
        }
        platform_name = framewords[platform.__class__.__name__]
    else:
        spec = PackageSpec(platform_packages[0])
        if spec.uri and '@' in spec.uri:
            platform_name = re.sub(r'@.+', '', spec.uri)
        else:
            platform_name = spec.name

    FRAMEWORK_DIR = Path(platform.get_package_dir(platform_name))
    assert FRAMEWORK_DIR.is_dir()

    #
    # Point variants_dir to our variant folder when board_build.variant
    # is provided and the variant name begins with "marlin_".
    #
    board = env.BoardConfig()
    variant = board.get("build.variant")
    #mcu_type = board.get("build.mcu")[:-2]
    #series = mcu_type[:7].upper() + "xx"

    # Make sure the local variant sub-folder exists
    if marlin_variant_pattern.match(str(variant).lower()):
        here = Path.cwd()
        variants_dir = here / 'buildroot' / 'share' / 'PlatformIO' / 'variants'
        source_dir = variants_dir / variant
        assert source_dir.is_dir()
        board.update("build.variants_dir", str(variants_dir))
>>>>>>> origin/release-2.1.3-beta2
