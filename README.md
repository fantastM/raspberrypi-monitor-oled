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

## SSD1306 Datasheet

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
```

- **S**: Start Condition
- **SA0**: Slave address bit
- **R/W#**: Read / Write Selection bit
- **ACK**: Acknowledgement
- **Co**: Continuation bit
- **D/C#**: Data / Command Selection bit
- **P**: Stop Condition

### 8.1.5.2 - Write mode for I2C

