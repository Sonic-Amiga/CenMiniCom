# CPU-6 board replica

# Modifications list.

1. 256x8 opcode table ROM is replaced by 2x256x4

2. Some old and hard-to-find chips are replaced with easier to find analogs.
Since i live in Russia some or these replacements are Soviet/Russian clones of
original chips (see table below)

3. AM2911 is replaced by a third am2909

4. Some diagnostics-only connectors and lines removed

5. Some of line twisting, present in the original schematics, redone for easier layout.

See git log for more verbose history

Russian characters in this file are using UTF-8 character set.

|Original       |Replacement            |Notes					|
|---------------|-----------------------|---------------------------------------|
|AM2901		|1804ВС1		|					|
|AM2907		|1804ВУ1		|					|
|93427C		|КР556РТ11		|					|
|AM2907		|1804BA2		|Not a precise analog; actually AM2908	|
|AM93l422	|КМ185РУ7А		|					|
|74LS00		|К555ЛА3		|					|
|74LS02		|К555ЛЕ1		|					|
|74LS10		|К555ЛА4		|					|
|74LS20		|К555ЛА1		|					|
|74LS30		|К555ЛА2		|					|
|74LS37		|К555ЛА12		|					|
|74LS38		|К555ЛА13		|					|
|74LS74		|К555ТМ2		|					|
|74LS138	|К555ИД7		|					|
|74LS151	|К555КП7		|					|
|74LS153	|К555КП2		|					|
|74LS157	|К555КП16		|					|
|74LS174	|К555ТМ9		|					|
|74LS240	|К555АП3		|					|
|74LS377	|К555ИР27		|					|
|74LS379	|КМ555ТМ10		|					|
|74LS669	|74LS169, К555ИЕ17	|					|

# Assembly notes

1. Power lines

Current layout is done for 2 layers only. Since the board is very dense, power distribution tracks 
are rather narrow (1.5 mm wide). A considerable effort has been put in routing redundant tracks,
but stability issues are still possible. For this case pads on the bottom side of the board are
provided; it's possible to "strenghten" power traces by running extra wires in horisontal
direction. Note this is a very experimental build; a need for such wires will be clarified during
the process of building and debugging.

2. R2, R3 resistors and crystal.

This part of the schematic is very sensitive to any changes. In my build i am using a russian
К555ЛА12 chip as U_M10. I have tried two different crystal types (HC-49U and HC-49S packaging),
and HC-49U works with resistors value of 510 ohm. HC-49S failed to start up completely, i tried
resistors up to 2K.

But your mileage may vary.

# Revision history.

04.11.2022 - rev 1.0

* Erratum E001: Incorrect DIP chip width is used for AM93l422 SRAM
* Erratum E002: A connection is missing between U_M10 pins 4 and 5, this renders clock generator nonfunctional.

# Contacts

Please direct all questions to pavel_fedin@mail.ru
