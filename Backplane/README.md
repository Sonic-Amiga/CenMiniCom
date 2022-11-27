# Backplane board replica

# Modifications list.

1. TBP18S42N ROM is a complete ubobtanium, so i found a russian КР556РТ5 (KR556RT5)
one-time fuse ROM. A cross-reference site gave "3605" as a western analog for the
chip, so let it be so.

2. PCB-mounted edge slots are also a complete unobtanium here, i only found ones for
soldering wires, they are called SLM-72:
https://www.arcadepartsandrepair.com/store/pinball-kits-parts/pinball-parts/72-pin-edge-connector-w-solder-eyelet-leads-ec1007/
Therefore this PCB is a shortened version, only containing boot ROM and LED buffers.
If you have access to the PCB-mounted connectors, please feel free to extend the project.
I will be happy to host the full version in the repository.

3. Real-time clock reference generator has been omitted. Modern PSUs don't output any low
voltage AC, and it's much easier to just generate the frequency needed. Since the signal
comes into the CPU from front panel side, front panel board takes care of it.

Russian characters in this file are using UTF-8 character set.

# Assembly notes

|Original       |Replacement            |
|---------------|-----------------------|
|3604		|К556РТ5		|
|74LS04         |К555ЛН1
|74LS20		|К555ЛА1		|
|74LS38		|К555ЛА13		|

# Contacts

Please direct all questions to pavel_fedin@mail.ru
