# Simple USB adapter for Sega 6-button joypad
## Bill of materials
* AT91SAM7S (I had [SAM7-H64](https://www.olimex.com/Products/ARM/Atmel/SAM7-H64) evaluation board)
* DB9-Male connector
## Schematics

```
+--------------+---------+                +------+
|   SAM7 CPU   |   GPIO  |                | DB9  |
|              +---------+                +------+
|              |   PA0   |<---------------| 1    |   +5V
|              |   PA2   |<---------------| 2    |    |
|              |   PA4   |<---------------| 3  5 |<---+
|              |   PA6   |<---------------| 4  8 |<---+
|              |   PA8   |<---------------| 6    |    |
|              |   PA10  |--------------->| 7    |   -+-
|              |   PA12  |<---------------| 9    |   GND
|              +---------+                +------+
|              |   PA14  |----[200Ohm]-----[LED>------+
+--------------+---------+                            |
                                                     -+- 
                                                     GND
```                   
