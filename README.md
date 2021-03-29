# Raspberry Pi Status Monitor

## References

- Hardware
  - [Raspberry Pi 4 Model B](https://www.raspberrypi.org/products/raspberry-pi-4-model-b/)
  - [Fan HAT](https://www.waveshare.com/wiki/Fan_HAT)
- GPIO C Library
  - [I²C](https://en.wikipedia.org/wiki/I%C2%B2C)
  - [I2C/SMBus Subsystem — The Linux Kernel documentation](https://www.kernel.org/doc/html/latest/i2c/index.html)
  - [bcm2835](http://www.airspayce.com/mikem/bcm2835/)
- Datasheet
  - [SSD1306](https://cdn-shop.adafruit.com/datasheets/SSD1306.pdf)
  - [PCA9685](https://cdn-shop.adafruit.com/datasheets/PCA9685.pdf)

## Notes in the SSD1306 Datasheet

### 8.1 - MCU Interface selection

```text
+-------------+------------------------------------+------------------------+
|       \Pin  |Data/Command Interface              |Control Signal          |
|Bus     \Name|--+--+--+--+--+--------+-------+----+-+-----+---+-------+----+
|Interface\   |D7|D6|D5|D4|D3|D2      |D1     |D0  |E|R/W# |CS#|D/C#   |RES#|
+-------------+--+--+--+--+--+--------+-------+----+-+-----+---+-------+----+
|3-wire SPI   |Tie LOW       |NC      |SDIN   |SCLK|Tie LOW|CS#|Tie LOW|RES#|
+-------------+--------------+--------+-------+----+-------+---+-------+----+
|4-wire SPI   |Tie LOW       |NC      |SDIN   |SCLK|Tie LOW|CS#|D/C#   |RES#|
+-------------+--------------+--------+-------+----+-------+---+-------+----+
|I2C          |Tie LOW       |SDA(OUT)|SDA(IN)|SCL |Tie LOW    |SA0    |RES#|
+-------------+--------------+--------+-------+----+-----------+-------+----+

         MCU interface assignment under different bus interface mode
```

### 8.1.5.1 - I2C-bus Write data

```text
   0 1 2 3 4 5 6 7   0 1 2 3 4 5 6 7   0 1 2 3 4 5 6 7   0 1 2 3 4 5 6 7   0 1 2 3 4 5 6 7
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
| | | | | | | |S|R|A|C|D|           |A|               |A|C|D|           |A|               |A| |
|S|0|1|1|1|1|0|A|/|C|o|/|           |C|               |C|0|/|           |C|               |C|P|
| | | | | | | |0|W|K| |C|           |K|               |K| |C|           |K|               |K| |
| | | | | | | | |#| | |#|           | |               |#| | |           | |               | | |
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
  |Salve Address|   |Control        | |Data byte      | |Control        | |Data byte      |
  |             |   |byte           | |               | |byte           | |               |

                                     I2C-bus data format
```

- **S**: Start Condition
- **SA0**: Slave address bit
- **R/W#**: Read / Write Selection bit
- **ACK**: Acknowledgement
- **Co**: Continuation bit
- **D/C#**: Data / Command Selection bit
- **P**: Stop Condition

### 8.1.5.2 - Write mode for I2C

1. The master device initiates the data communication by a start condition. **The start condition is established by pulling the SDA from HIGH to LOW while the SCL stays HIGH.**
2. The slave address is following the start condition for recognition use. For the SSD1306, **the slave address is either "b0111100" or "b0111101" by changing the SA0 to LOW or HIGH.**
3. **The write mode is established by setting the R/W# bit to logic "0"**.
4. An acknowledgement signal will be generated after receiving one byte of data, including the slave address and the R/W# bit.
5. A control byte mainly consists of Co and D/C# bits following by six "0".
    1. **If the Co bit is set as logic "0", the transmission of the following information will contain data bytes only.**
    2. **If the D/C# bit is set to logic "0", it defines the following data byte as a command. If the D/C# bit is set to logic "1", it defines the following data byte as a data which will be stored at the GDDRAM (Graphic Display Data RAM).**
6. Acknowledge bit will be generated after receiving each control byte or data byte.
7. The write mode will be finished when a stop condition is applied. **The stop condition is established by pulling the SDA in from LOW to HIGH while the SCL stays HIGH.**

Which means, there are all four possible control bytes in the write mode for I2C:

Co  | D/C# | Hex  | Comment              | Address Increment
--- | ---- | ---- | -------------------- | -----------------
0   | 0    | 0x00 | Write command stream | No
0   | 1    | 0x40 | Write data stream    | Yes
1   | 0    | 0x80 | Write single command | No
1   | 1    | 0xC0 | Write single data    | Yes

### 8.7 - Graphic Display Data RAM (GDDRAM)

The GDDRAM is a bit mapped static RAM holding the bit pattern to be displayed. The size of the RAM is 128 x 64 bits and the RAM is divided into eight pages, from PAGE0 to PAGE7, which are used for monochrome 128x64 dot matrix display.

```text
      +--------------------------------------------------+
PAGE0 |                      Page 0                      |
      +--------------------------------------------------+
PAGE1 |                      Page 1                      |
      +--------------------------------------------------+
PAGE2 |                      Page 2                      |
      +--------------------------------------------------+
PAGE3 |                      Page 3                      |
      +--------------------------------------------------+
PAGE4 |                      Page 4                      |
      +--------------------------------------------------+
PAGE5 |                      Page 5                      |
      +--------------------------------------------------+
PAGE6 |                      Page 6                      |
      +--------------------------------------------------+
PAGE7 |                      Page 7                      |
      +--------------------------------------------------+
         SEG0 ---------------------------------> SEG127

              GDDRAM pages structure of SSD1306
```

When one data byte is written into GDDRAM, all the rows image data of the same page of the current column are filled. Data bit D0 is written into the top row, while data bit D7 is written into bottom row.

```text
                                                                              S S S S S
                                                                              E E E E E
          S S S S S                                                           G G G G G
          E E E E E                                                           1 1 1 1 1
          G G G G G                                                           2 2 2 2 2
          0 1 2 3 4                                                           3 4 5 6 7
         +-+-+-+-+-+.........................................................+-+-+-+-+-+
      D0 | | | | | |                                                         | | | | | |
         +-+-+-+-+-+                                                         +-+-+-+-+-+
      D1 | | | | | |                                                         | | | | | |
         +-+-+-+-+-+                                                         +-+-+-+-+-+
      D2 | | | | | |                                                         | | | | | |
         +-+-+-+-+-+                                                         +-+-+-+-+-+
      D3 | | | | | |                                                         | | | | | |
PAGE0    +-+-+-+-+-+.........................................................+-+-+-+-+-+
      D4 | | | | | |                                                         | | | | | |
         +-+-+-+-+-+                                                         +-+-+-+-+-+
      D5 | | | | | |                                                         | | | | | |
         +-+-+-+-+-+                                                         +-+-+-+-+-+
      D6 | | | | | |                                                         | | | | | |
         +-+-+-+-+-+                                                         +-+-+-+-+-+
      D7 | | | | | |                                                         | | | | | |
         +-+-+-+-+-+.........................................................+-+-+-+-+-+

                                      Enlargement of GDDRAM
```

### 9 - Command Table

#### Fundamental Command Table

Hex              | Command
---------------- | ----------------------------
0x81 + b^^^^^^^^ | Set Contrast Control
0xA4 / 0xA5      | Entire Display (RESET) ON
0xA6 / 0xA7      | Set Normal / Inverse Display
0xAE / 0xAF      | Set Display OFF / ON

#### Addressing Setting Command Table

Hex              | Command
---------------- | --------------
0xB0 ~ 0xB7      | Set Page Start
0x20 + b000000^^ | Set Memory Addressing Mode

#### Hardware Configuration Command Table

Hex              | Command
---------------- | ----------------------------
0x40 ~ 0x7F      | Set Display Start Line
0xA0 / 0xA1      | Set Segment Re-map
0xA8 + b00^^^^^^ | Set Multiplex Ratio
0xC0 / 0xC8      | Set COM Output Scan Direction
0xD3 + b00^^^^^^ | Set Display Offset
0xDA + b00^^0010 | Set COM Pins Hardware Configuration

#### Timing & Driving Scheme Setting Command Table

Hex              | Command
---------------- | -----------------------------------------------------
0xD5 + b^^^^^^^^ | Set Display Clock Divide Ratio / Oscillator Frequency
0xD9 + b^^^^^^^^ | Set Pre-charge Period
0xDB + b0^^^0000 | Set VCOMH Deselect Level

### Software Configuration

#### Charge Bump Setting Command Table

Hex              | Command
---------------- | -------------------
0x8D + b00010^00 | Charge Pump Setting

#### Software Configuration

Below is an example of initialization flow of SSD1306.

```text
                                           +-------------+
                                           |             |
+-------------+                            |       +--------------------+
|Set MUX Ratio|                            |       |Set Contrast Control|
|0xA8 + 0x3F  |                            |       |0x81 + 0x7F         |
+-------------+                            |       +--------------------+
      |                                    |             |
      v                                    |             v
+------------------+                       |       +-------------------------+
|Set Display Offset|                       |       |Disable Entire Display On|
|0xD3 + 0x00       |                       |       |0xA4                     |
+------------------+                       |       +-------------------------+
      |                                    |             |
      v                                    |             v
+----------------------+                   |       +------------------+
|Set Display Start Line|                   |       |Set Normal Display|
|0x40                  |                   |       |0xA6              |
+----------------------+                   |       +------------------+
      |                                    |             |
      v                                    |             v
+------------------+                       |       +-----------------+
|Set Segment re-map|                       |       |Set Osc Frequency|
|0xA0 / 0xA1       |                       |       |0xD5 + 0x80      |
+------------------+                       |       +-----------------+
      |                                    |             |
      v                                    |             v
+-----------------------------+            |       +----------------------------+
|Set COM Output Scan Direction|            |       |Enable charge pump regulator|
|0xC0 / 0xC8                  |            |       |0x8D + 0x14                 |
+-----------------------------+            |       +----------------------------+
      |                                    |             |
      v                                    |             v
+-----------------------------------+      |       +----------+
|Set COM Pins hardware configuration|      |       |Display On|
|0xDA + 0x02                        |      |       |0xAF      |
+-----------------------------------+      |       +----------+
      |                                    |
      +------------------------------------+

                    Software Initialization Flow Chart
```
