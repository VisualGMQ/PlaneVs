#!/usr/bin/python3

import os
import sys

def ShowHelp():
    print("mp3 to ogg")
    print("please give your mp3 filename.This application will convert it to ogg")

argv = sys.argv

if len(argv) != 2:
    ShowHelp()
else:
    mp3_filename = argv[1]
    ogg_filename = mp3_filename[:mp3_filename.rfind('.')] + ".ogg"
    ret = os.system("ffmpeg -y -i {} -acodec libvorbis -ab 128k {}".format(mp3_filename, ogg_filename))
    if ret != 0:
        print("error occur, exit with ", ret)
    else:
        print("convert OK")
