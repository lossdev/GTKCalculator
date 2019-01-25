#!/bin/bash

if [ "$EUID" -ne 0 ]
  then echo "Please run as root"
  exit
fi

tar -xvf simpleCalc*.tar.gz > /dev/null
mkdir -p /etc/simpleCalc
rm simpleCalc*.tar.gz
chown 0:0 simpleCalc
chown 0:0 calc.ico
chown 0:0 simple_calculator.desktop
chown 0:0 window_main.glade
mv simpleCalc /usr/bin
mv calc.ico /usr/share/pixmaps
mv simple_calculator.desktop /usr/share/applications
mv window_main.glade /etc/simpleCalc
echo "Installed Successfully"
rm install.sh