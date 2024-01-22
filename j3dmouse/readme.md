# jmouse
qmk 0.22.13
```
    make j3dmouse:via
```
```
Flashing example for this keyboard:

    make j3dmouse:via:flash


- waveshare RP2040 zero
- 2 joystick
- 3 key

## Bootloader
Enter the bootloader in 3 ways:
* **Bootmagic reset**: Hold down the upper left key while plugging in USB
* **Physical reset button**: Press the RST button twice, rapidly
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available

```
