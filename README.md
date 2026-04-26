# The Zeta-bot

![alt tag](topview.jpg)

What is the Zeta-Bot?

The Zeta-Bot is an open-source robot platform that uses the:

 - Raspberry PI 5,
 - [Parallax's Continuous Rotation Servo Motors](https://www.parallax.com/product/parallax-continuous-rotation-servo/),
 - [C1 LIDAR](https://www.slamtec.com/en/c1),
 - two [Raspberry PI V2 cameras](https://www.raspberrypi.com/products/camera-module-v2/) for stereo vision, and
 - [a standard mobile phone 1700mAh power bank](https://uk.rs-online.com/web/p/power-banks/2498449).

It's based on years and years of making single PCB Raspberry PI based
robots. Every part has been chosen because of extensive lab use
proving its reliability over the years and because of its solid hard-
and software support of the individual parts. 

## Hardware

The KiCad design files are in [hardware](hardware).

## Software

 - The motor control libraries are in [wheeleddrive](wheeleddrive).
 - The cameras driver is in https://github.com/berndporr/libcamera2opencv and there is a QT6 based stereo viewer and disparity detector in [stereo](stereo).
 - The LIDAR driver is in https://github.com/berndporr/c1lidar

## Credits

 - (c) 2026, Bernd Porr, mail@berndporr.me.uk
 - (c) 2025, Saleh AlMulla
 - (c) 2025, Yixuan Zha
