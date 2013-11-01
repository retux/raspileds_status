Build:

make or make all target will built netifledwatch gpiopinctrl gpioctrl.

There's no install target, so just copy binaries to their destination:

/usr/local/bin for netifledwatch, gpiopinctrl, gpioctrl.

And:

/etc/init.d/ for raspiledsts SysV init script.

If don't want to build yourself, theres a .deb package included.


Usage notes:

gpiopinctrl turn direction of a given GPIO pin to "out" and turn the pin on or off (1/0) using sysfs.

For Raspberry Pi Server GPIO pin 4 was chosen to network state led (Amber), and GPIO pin 17 for Ready LED (Green).

Debian naming convention:

 <foo>_<VersionNumber>-<DebianRevisionNumber>_<DebianArchitecture>.deb

Dependencies:

raspi-copies-and-fills	(>= 0.4)
libstdc++6:armhf	(>= 4.7)
libc6:armhf		(>= 2.13)
libgcc1:armhf		(>= 1.4)


