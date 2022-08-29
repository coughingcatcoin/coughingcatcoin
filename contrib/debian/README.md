
Debian
====================
This directory contains files used to package coughingcatcoind/coughingcatcoin-qt
for Debian-based Linux systems. If you compile coughingcatcoind/coughingcatcoin-qt yourself, there are some useful files here.

## coughingcatcoin: URI support ##


coughingcatcoin-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install coughingcatcoin-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your coughingcatcoin-qt binary to `/usr/bin`
and the `../../share/pixmaps/coughingcatcoin128.png` to `/usr/share/pixmaps`

coughingcatcoin-qt.protocol (KDE)

