#!/bin/bash

if [ "$EUID" -ne 0 ]
  then echo "Please run as root"
  exit
fi

tar -xvf simpleCalc*.tar.gz > /dev/null
mkdir -p /etc/simpleCalc
mv simpleCalc /usr/bin
mv calc.ico /usr/share/pixmaps
mv simple_calculator.desktop /usr/share/applications
mv window_main.glade /etc/simpleCalc
echo "Installed Successfully"
