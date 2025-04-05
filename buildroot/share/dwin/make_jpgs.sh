#!/usr/bin/env bash

<<<<<<< HEAD
mkdir -p icons-3

convert -size 48x36 -background "#080808" -quality 100 -sampling-factor 4:4:4 ./icons-svg/hotend_off.svg            ./icons-3/001-ICON_HotendOff.jpg
convert -size 48x36 -background "#080808" -quality 100 -sampling-factor 4:4:4 ./icons-svg/hotend_on.svg             ./icons-3/002-ICON_HotendOn.jpg

convert -size 48x36 -background "#080808" -quality 100 -sampling-factor 4:4:4 ./icons-svg/bed_off.svg               ./icons-3/003-ICON_BedOff.jpg
convert -size 48x36 -background "#080808" -quality 100 -sampling-factor 4:4:4 ./icons-svg/bed_on.svg                ./icons-3/004-ICON_BedOn.jpg

convert -size 48x48 -background "#080808" -quality 100 -sampling-factor 4:4:4 ./icons-svg/fan.svg                   ./icons-3/005-ICON_Fan0.jpg
convert -size 48x48 -background "#080808" -quality 100 -sampling-factor 4:4:4 -distort SRT 22.5 ./icons-svg/fan.svg ./icons-3/006-ICON_Fan1.jpg
convert -size 48x48 -background "#080808" -quality 100 -sampling-factor 4:4:4 -distort SRT 45 ./icons-svg/fan.svg   ./icons-3/007-ICON_Fan2.jpg
convert -size 48x48 -background "#080808" -quality 100 -sampling-factor 4:4:4 -distort SRT 67.5 ./icons-svg/fan.svg ./icons-3/008-ICON_Fan3.jpg

convert -size 96x96 -background "#333e44" -quality 100 -sampling-factor 4:4:4 ./icons-svg/halted.svg                ./icons-3/009-ICON_Halted.jpg
convert -size 96x96 -background "#333e44" -quality 100 -sampling-factor 4:4:4 ./icons-svg/question.svg              ./icons-3/010-ICON_Question.jpg
convert -size 96x96 -background "#333e44" -quality 100 -sampling-factor 4:4:4 ./icons-svg/alert.svg                 ./icons-3/011-ICON_Alert.jpg

convert -size 48x48 -background "#080808" -quality 100 -sampling-factor 4:4:4 ./icons-svg/rotate_cw.svg             ./icons-3/012-ICON_RotateCW.jpg
convert -size 48x48 -background "#080808" -quality 100 -sampling-factor 4:4:4 ./icons-svg/rotate_ccw.svg            ./icons-3/013-ICON_RotateCCW.jpg
convert -size 48x48 -background "#080808" -quality 100 -sampling-factor 4:4:4 ./icons-svg/up_arrow.svg              ./icons-3/014-ICON_UpArrow.jpg
convert -size 48x48 -background "#080808" -quality 100 -sampling-factor 4:4:4 ./icons-svg/down_arrow.svg            ./icons-3/015-ICON_DownArrow.jpg

convert -size 48x8  -background "#080808" -quality 100 -sampling-factor 4:4:4 ./icons-svg/bedline.svg               ./icons-3/016-ICON_Bedline.jpg

convert -size 48x36 -background "#080808" -quality 100 -sampling-factor 4:4:4 ./icons-svg/bed_leveled_off.svg       ./icons-3/017-ICON_BedLeveledOff.jpg
convert -size 48x36 -background "#080808" -quality 100 -sampling-factor 4:4:4 ./icons-svg/bed_leveled_on.svg        ./icons-3/018-ICON_BedLeveledOn.jpg

rm 3.ICO
./bin/makeIco.py icons-3 3.ICO
=======
mkdir -p icons-4

convert -size 48x36 -background "#080808" -quality 100 -sampling-factor 4:4:4 ./icons-svg/hotend_off.svg            ./icons-4/001-ICON_HotendOff.jpg
convert -size 48x36 -background "#080808" -quality 100 -sampling-factor 4:4:4 ./icons-svg/hotend_on.svg             ./icons-4/002-ICON_HotendOn.jpg

convert -size 48x36 -background "#080808" -quality 100 -sampling-factor 4:4:4 ./icons-svg/bed_off.svg               ./icons-4/003-ICON_BedOff.jpg
convert -size 48x36 -background "#080808" -quality 100 -sampling-factor 4:4:4 ./icons-svg/bed_on.svg                ./icons-4/004-ICON_BedOn.jpg

convert -size 48x48 -background "#080808" -quality 100 -sampling-factor 4:4:4 ./icons-svg/fan.svg                   ./icons-4/005-ICON_Fan0.jpg
convert -size 48x48 -background "#080808" -quality 100 -sampling-factor 4:4:4 -distort SRT 22.5 ./icons-svg/fan.svg ./icons-4/006-ICON_Fan1.jpg
convert -size 48x48 -background "#080808" -quality 100 -sampling-factor 4:4:4 -distort SRT 45 ./icons-svg/fan.svg   ./icons-4/007-ICON_Fan2.jpg
convert -size 48x48 -background "#080808" -quality 100 -sampling-factor 4:4:4 -distort SRT 67.5 ./icons-svg/fan.svg ./icons-4/008-ICON_Fan3.jpg

convert -size 96x96 -background "#333e44" -quality 100 -sampling-factor 4:4:4 ./icons-svg/halted.svg                ./icons-4/009-ICON_Halted.jpg
convert -size 96x96 -background "#333e44" -quality 100 -sampling-factor 4:4:4 ./icons-svg/question.svg              ./icons-4/010-ICON_Question.jpg
convert -size 96x96 -background "#333e44" -quality 100 -sampling-factor 4:4:4 ./icons-svg/alert.svg                 ./icons-4/011-ICON_Alert.jpg

convert -size 48x48 -background "#080808" -quality 100 -sampling-factor 4:4:4 ./icons-svg/rotate_cw.svg             ./icons-4/012-ICON_RotateCW.jpg
convert -size 48x48 -background "#080808" -quality 100 -sampling-factor 4:4:4 ./icons-svg/rotate_ccw.svg            ./icons-4/013-ICON_RotateCCW.jpg
convert -size 48x48 -background "#080808" -quality 100 -sampling-factor 4:4:4 ./icons-svg/up_arrow.svg              ./icons-4/014-ICON_UpArrow.jpg
convert -size 48x48 -background "#080808" -quality 100 -sampling-factor 4:4:4 ./icons-svg/down_arrow.svg            ./icons-4/015-ICON_DownArrow.jpg

convert -size 48x8  -background "#080808" -quality 100 -sampling-factor 4:4:4 ./icons-svg/bedline.svg               ./icons-4/016-ICON_Bedline.jpg

convert -size 48x36 -background "#080808" -quality 100 -sampling-factor 4:4:4 ./icons-svg/bed_leveled_off.svg       ./icons-4/017-ICON_BedLeveledOff.jpg
convert -size 48x36 -background "#080808" -quality 100 -sampling-factor 4:4:4 ./icons-svg/bed_leveled_on.svg        ./icons-4/018-ICON_BedLeveledOn.jpg

rm -f 4.ICO
./bin/makeIco.py icons-4 4.ICO
>>>>>>> origin/release-2.1.3-beta2
