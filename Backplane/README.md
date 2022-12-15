# Backplane board replica

# Modifications list.

1. TBP18S42N ROM is a complete ubobtanium, so i found a russian КР556РТ5 (KR556RT5)
one-time fuse ROM. A cross-reference site gave "3605" as a western analog for the
chip, so let it be so.

2. PCB-mounted edge slots are also a complete unobtanium here, i only found ones for
soldering wires, they are called SLM-72:
https://www.arcadepartsandrepair.com/store/pinball-kits-parts/pinball-parts/72-pin-edge-connector-w-solder-eyelet-leads-ec1007/
Therefore this PCB is a shortened version, only containing boot ROM and LED buffers, but
the design is modular and can be extended, see assembly notes.
Connection to the bus is made using a 50-pin connector, you may use IDC type with a flat
ribbon cable. 
If you have access to the PCB-mounted connectors, please feel free to extend the project.
I will be happy to host the full version in the repository.

3. Real-time clock reference generator has been omitted. Modern PSUs don't output any low
voltage AC, and it's much easier to just generate the frequency needed. Since the signal
comes into the CPU from front panel side, front panel board takes care of it.

Russian characters in this file are using UTF-8 character set.

# Assembly notes

Possible chip replacements:

|Original       |Replacement            |
|---------------|-----------------------|
|3604		|К556РТ5		|
|74LS04         |К555ЛН1
|74LS20		|К555ЛА1		|
|74LS38		|К555ЛА13		|

As noticed above, this backplane design is modular, and can be used with both wired and PCB backplane
design. For the purpose, the J2 connector is designed as a horisontal 2x25 pins row. It is possible
to attach a second board, containing edge slots, directly to it, thus producing a full-sized backplane.
Alternatively, an IDC-50 connector can be installed with a flat ribbon cable, going to a wired backplane
(this will be my implementation). Sorry, due to a lack of time i don't have a design for the second PCB,
but i would be happy if someone contributes.

# Revision history.

28.11.2022 - rev 1.0

* Erratum E001: Incorrect DIP chip width is used for 3604

# Contacts

Please direct all questions to pavel_fedin@mail.ru
