# Front panel board replica

# Modifications list.

1. Modern PSUs don't output any low voltage AC, and it's much easier to just generate
the frequency needed. For the purpose this board has a 555-based simple adjustable
clock generator instead of the original buffer/phase shifter circuit.

Russian characters in this file are using UTF-8 character set.

# Assembly notes

|Original       |Replacement            |
|---------------|-----------------------|
|74LS38		|К555ЛА13		|
|74LS123	|555АГ3		        |
|NE555		|К1441ВИ1		|

# Revision history.

30.11.2022 - rev 1.0

* Errarum E001: Incorrect ground and power separation

Current - rev 2.0

- Added decoupling capacitors
- Narrowed down while maintaining compatibility with original, mounting holes are kept in the same location
- Adjusted J3 footprint so that MPW-5 connector fits in

# Contacts

Please direct all questions to pavel_fedin@mail.ru
