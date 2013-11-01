RaspiLeds Status

This is a simple and basic set of programs intended to be used as Raspberry Pi status signal.
It's built using Hussam Al-Hertani C++ Classes to access GPIO through SO (sysfs). Just made a 
little enhacement on error handling to Hussam's classes.

To monitor basic raspberry pi basic status a couple of standard leds can be used. I used bicolor
5mm led to signal green to "ready" status (meant raspberry pi has finished boot process) and red
for meaning just power.

netifledwatch monitores ethernet status by software (reading sysfs file entries) and depending
on the ethernet carrier status set GPIO pin output high or low.

gpiopinctrl binary is used to turn certain GPIO pin on/off (just output) and it's used to 
indicate ready state.

gpioctrl binary is a more flexible interface to OS API to GPIO and lets you export, unexport,
 turn direction (in/out), write (on/of) or read pin value.

readyled is a SysV init script used to simply actiate "ready" led on, in this case using GPIO
pin 17.

A Raspbian package is include in debian directory.
