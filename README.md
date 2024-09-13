# frequency generator


esp32(DevKitC board) + ssd1306(i2c) + si5351(i2c, 4KHz..160MHz) + TL1838(infrared receiver)


# Файлы пакета:

* sdkconfing	- файл конфигурации проекта

* Makefile	- make файл (файл сценария компиляции проекта)

* version	- файл версии ПО

* README.md	- файл справки

* main/		- папка исходников


Требуемые компоненты:
```
- Cross compiler xtensa-esp32-elf (http://esp-idf-fork.readthedocs.io/en/stable/linux-setup.html#step-0-prerequisites)
- SDK esp-idf (https://github.com/espressif/esp-idf)
- Python2 (https://www.python.org/)
- wsClient - утилита web-socket client (Qt release)
```

# Компиляция и загрузка

make menuconfig - конфигурация проекта

make app	- компиляция проекта

make flash	- запись бинарного кода проекта в dataflash



Connected si5351 to ESP32 : (I2C_NUM_0 on ESP32)

```
I2C_MASTER_SCL_PIN GPIO_NUM_22
I2C_MASTER_SDA_PIN GPIO_NUM_21

Frequence on i2c bus 400000 Hz
````


Connected display ssd1306 to ESP32 : (I2C_NUM_1 on ESP32)

```
SDA_PIN GPIO_NUM_23
SCL_PIN GPIO_NUM_18

Frequence on i2c bus 400000 Hz
```


Add Si5351.pdf datasheet



