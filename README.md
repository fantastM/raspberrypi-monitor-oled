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
    2. **If the D/C# bit is set to logic "0", it defines the following data byte as a command. If the D/C# bit is set to logic "1", it defines the following data byte as a data which will be stored at the GDDRAM(Graphic Display Data RAM).**
6. Acknowledge bit will be generated after receiving each control byte or data byte.
7. The write mode will be finished when a stop condition is applied. **The stop condition is established by pulling the SDA in from LOW to HIGH while the SCL stays HIGH.**

Which means, there are all four possible control bytes in the write mode for I2C:

```text
+--+----+----+--------------------+-----------------+
|Co|D/C#|Hex |Comment             |Address Increment|
+--+----+----+--------------------+-----------------+
|0 |0   |0x00|Write command stream|No               |
+--+----+-------------------------+-----------------+
|0 |1   |0x40|Write data stream   |Yes              |
+--+----+----+--------------------+-----------------+
|1 |0   |0x80|Write single command|No               |
+--+----+----+--------------------+-----------------+
|1 |1   |0xC0|Write single data   |Yes              |
+--+----+----+--------------------+-----------------+
```

