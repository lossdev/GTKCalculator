#!/bin/bash

if [ "$EUID" -ne 0 ]
  then echo "Please run as root"
  exit
fi

rm /usr/share/applications/simple_calculator.desktop
rm /usr/bin/simpleCalc
rm /usr/share/pixmaps/calc.ico
rm -r /etc/simpleCalc
echo "Uninstalled Successfully"
