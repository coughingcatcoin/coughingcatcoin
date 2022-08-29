Coughingcatcoin Core 1.0.0
=====================

Setup
---------------------
[Coughingcatcoin Core](http://coughingcatcoin.com/) is the reference Coughingcatcoin client and it builds the backbone of the network. However, it downloads and stores the entire history of Bitcoin transactions (which is currently several GBs); depending on the speed of your computer and network connection, the synchronization process can take anywhere from a few hours to a day or more.

Running
---------------------
The following are some helpful notes on how to run Coughingcatcoin on your native platform.

### Unix

Unpack the files into a directory and run:

- `bin/coughingcatcoin-qt` (GUI) or
- `bin/coughingcatcoind` (headless)

### Windows

Unpack the files into a directory, and then run coughingcatcoin-qt.exe.

### OS X

Drag Coughingcatcoin-Core to your applications folder, and then run Coughingcatcoin-Core.

Building
---------------------
The following are developer notes on how to build Coughingcatcoin on your native platform. They are not complete guides, but include notes on the necessary libraries, compile flags, etc.

- [OS X Build Notes](build-osx.md)
- [Unix Build Notes](build-unix.md)
- [Windows Build Notes](build-windows.md)
- [OpenBSD Build Notes](build-openbsd.md)

### Miscellaneous
- [Tor Support](tor.md)
- [Init Scripts (systemd/upstart/openrc)](init.md)
- [ZMQ](zmq.md)
