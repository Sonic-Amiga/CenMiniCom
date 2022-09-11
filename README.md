# Schematics for the Centurion Minicomputer replica

This is my work in progress repository, documenting an attempt to build a replica of a
Centurion minicomputer. The repository is a fork of Meisaka's reverse engineering project
(https://github.com/Meisaka/CenMiniCom.git) and contains some modifications.

#### IMPORTANT: Schematics are originally reverse engineered from multiple hi-res images of the various cards, so they may contain mistakes or errors.

# Modifications list.

1. 256x8 opcode table ROM is replaced by 2x256x4

2. Some old and hard-to-find chips are replaced with easier to find analogs.
Since i live in Russia some or these replacements are Soviet/Russian clones of
original chips (see table below)

3. AM2911 is replaced by a third am2909

4. Some of line twisting, present in the original schematics, redone for easier layout.

See git log for more verbose history

Russian characters in this file are using UTF-8 character set.

|Original       |Replacement            |Notes
|---------------|-----------------------|---------------------------------------|
|AM2901		|1804ВС1		|					|
|AM2907		|1804ВУ1		|					|
|93427C		|КР556РТ11		|					|
|AM2907		|1804BA2		|Not a precise analog; actually AM2908	|
|AM93l422	|КМ185РУ7А		|					|
|74LS669	|74LS169, К555ИЕ17	|					|
|74LS379	|КМ555ТМ10		|					|
|74LS37		|К555ЛА2		|					|
|74LS38		|К555ЛА13		|					|
|74LS240	|К555АП3		|					|

# Assembly notes

Current layout is done for 2 layers only. Since the board is very dense, some power nets have to be
completed using wire jumpers. Pads on the bottom side of the board are provided for that. Connect
all of them together in horisontal lines. A picture will be provided later, after i build the board
myself.

# Contacts

Please direct all questions to pavel_fedin@mail.ru
