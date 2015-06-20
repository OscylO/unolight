Arduino project controlling up to <b>5 RGB</b> TV backlights (on all supported Arduinos).

Works great with VideoLAN Client (VLC) and Atmolight plugin, <a href='http://blogger.xs4all.nl/loosen/articles/408218.aspx'>Boblight</a> and Amblone.

Needs Arduino with ATmega328p, ATmega168, ATmega1280 or ATmega2560 like Arduino UNO, NANO  or Mega.

Supports 10-bit PWM (1024 light levels) for up to 15 outputs (5 RGB LEDs).


To see source code use this link <a href='http://code.google.com/p/unolight/source/browse/#svn%2Ftrunk%2Funolight'>source code</a>.
If you want to see what is transmitted over serial you can use <a href='http://www.serialmon.com'>SerialMon</a>.


To find out how to use <a href='http://www.videolan.org/vlc/'>VLC</a> with Atmolight plugin click <a href='http://www.vdr-wiki.de/wiki/index.php/AtmoWin'>here</a>.

<b>UnoLight v0.20 Beta 1 now available <a href='http://unolight.googlecode.com/files/UnoLight%20v0.20%20Beta%201.zip'>here</a>.</b> Needs to be compiled with Arduino 1.0 RC1 or later version.

Most important changes since v0.10:

Doubled LED frequency (488 Hz)


Added Amblone protocol support (to enable set COMMUNICATION\_PROTOCOL to AMBLONE\_PROTOCOL)


5 RGB leds support


Smoothing of color transitions


Storing settings in EEPROM


Added support of Arduinos with ATmega 2560 and 1280 works but not fully tested

If you build something using my software please send me a video or photos and I will put it on this site.

<b>UnoLight in action:</b>

Software: UnoLight running on Arduino Uno (commands send from VLC with Atmolight plugin) 

&lt;BR&gt;


Hardware: 2 RGB Power Leds mounted to 32 inch Samsung LCD TV

&lt;BR&gt;


Distance between LEDs and wall is about 30 cm (12 inches).
<br>
You can find video <a href='http://youtu.be/fJl9OlcRKOU'>here</a> (in real life there is no pulsing effect like in video).<br>
<br>
<br>
<BR><br>
<br>
<br>
<a href='http://oscylo.site50.net/unolight/photos/unolight_simplest_board.jpg'>Simple board used in this video but with Arduino NANO instead of UNO.</a>

<img src='http://oscylo.site50.net/unolight/photos/unolight_photo1.jpg'>
<img src='http://oscylo.site50.net/unolight/photos/unolight_photo2.jpg'>
<img src='http://oscylo.site50.net/unolight/photos/unolight_photo3.jpg'>
<img src='http://oscylo.site50.net/unolight/photos/unolight_photo4.jpg'>
<img src='http://oscylo.site50.net/unolight/photos/unolight_photo5.jpg'>