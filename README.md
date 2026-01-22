The serial communication function is **still to be developed**. The current code will loop 30min enable / 2hrs disable power delivery by default. You'll need to edit and upload the .ino code by yourself to modify the duration.

## A little USB addon that can switch VCC automatically by time based on CH552 or ATtiny85

With loopback output checking feature to detect if the MOSFET's breaking.

If the LED starts blinking, it means your MOSFET is likely failing and may completely die within 36 hours. This self-diagnostic feature was added based on some expensive lessons. Don't ask how I know. 💸

### BOM:

| **Part name**             | **Suggested Model**                                                                                                                                            | **Amount**                                              | **Notes**                                                                                                             |
| ------------------------- | -------------------------------------------------------------------------------------------------------------------------------------------------------------- | ------------------------------------------------------- | --------------------------------------------------------------------------------------------------------------------- |
| **Board**                 | **[CH552](#the-way-to-start-using-ch552)**, **[ESP32C3 SuperMini](#the-way-to-start-using-esp32c3-supermini)** or **Digispark [ATtiny85](#the-way-to-flash-bootloader-to-an-attiny85)**             | 1                                                       | It would be better if it comes with pin header.                                                                       |
| **Board Socket**          | **CH552:** DIP-20 IC socket or 1×10 female header<br/>**ESP32C3 SuperMini:** DIP-16 IC socket or 1×8 female header<br/>**ATtiny85:** 1×6 and 1×3 female header | IC socket: 1<br/>Female header: 2 (each 1 for ATtiny85) | Prevent board wasting from wiring false or possible heat damaging                                                     |
| **P-Channel MOSFET**      | **AO3401**                                                                                                                                                     | 1                                                       | Toggling VCC                                                                                                          |
| **N-Channel MOSFET**      | **To be decide**<br/>Not always needed                                                                                                                         | 1                                                       | **ONLY needed if you're using a ESP32C3 SuperMini**<br/>Shifting 3V3 logic to 5V in order to control PMOS             |
| **SMD-THT convert board** | **SOT-23 to DIP**                                                                                                                                              | 1                                                       | Make AO3401 be able to use on a perfboard                                                                             |
| **MOSFET Connector**      | **1×3 pin header**                                                                                                                                             | 1                                                       | To connect AO3401 to perfboard<br/>I'm using 90° one, and the perfboard wiring is based on self-bended 90° pin header |
| **Resistor**              | **220Ω, 10kΩ**                                                                                                                                                 | 1, 1                                                    | 1/4W. 220Ω for protection, 10kΩ for pull up.                                                                          |
| **USB convert board**     | **USB Type-A Male and Female to DIP**                                                                                                                          | 1, 1                                                    | Buy a DIP ones for the best usability.                                                                                |
| **Button Switch**         | **A simple button**                                                                                                                                            | 1                                                       | I use a 2 pin one to make everything easier                                                                           |
| **Capacitor**             | **0.1μF**                                                                                                                                                      | 1                                                       | Hardware debounce                                                                                                     |
| **Circuit board**         | **Single sided Perfboard**                                                                                                                                     | 1                                                       | **3x7cm** suggested, although I'm use the one I had in my hand.                                                       |

MOSFET is to simulate the function of a relay.

If you're using ATtiny85, the time will be few minutes off per day, so if you really want make it turn on and off on accurate time, using other development boards like Arduino Nano, Micro or Raspberry Pi Pico, Zero etc. and make some change in the code  would be suggested.

### The way to start using CH552

This section is based on [this tutorial](https://imuslab.com/wordpress/2022/04/25/arduino-%E7%94%A8%E5%9C%A8%E7%94%A2%E5%93%81%E4%B8%8A%E5%A4%AA%E8%B2%B4%EF%BC%9F%E6%9C%89%E8%81%BD%E9%81%8E-ch552g-%E5%97%8E%EF%BC%9F/) (in Traditional Chinese) but Translated by me.

#### Add third-party board definition

Add `https://raw.githubusercontent.com/DeqingSun/ch55xduino/ch55xduino/package_ch55xduino_mcs51_index.json` to your Arduino board definition from `Prefrence`, and search for CH55x board in `Board Manager`

#### Install driver

1. Download [Zadig](https://zadig.akeo.ie/)

2. Press PROG or Download button before you connect your board to your computer

3. Connect your CH552 to your computer via USB cable **WITH the button STILL be pressed**

4. **After** the board appear as "undefined device" (不明裝置) in `Device Manager` (裝置管理員), release the button
   
   1. Open Zadig, choose `Unknown Device 1`, click `Install Driver` or `Replace Driver`

5. Wait for up to 3~5 minutes

6. Reconnect the board **after** it's done

7. There should be a `COMX` in your Device Manager (裝置管理員) (for example, `COM7`)

#### Flash bootloader

In Arduino IDE, `Tool` > `Board` > `CH55x Boards` > `CH552 Board`

Arduino should flash the correct bootloader when you upload your code. You can try writing a code to blink the onboard LED which is mostly on pin `30`. Simply write `digitalWrite(30, HIGH)` can turn on the LED.

#### How should I determine what pin number should I write while using CH552?

**If your board label your pin as something like `30 31 32`,** write the number as you see. The code in the last step is an example.

**If your board label your pin as something like `P3.0 P3.1 P3.2`,** ignore 'P' and '.', only write the number. For example:

| Label | Pin number in Arduino | Label | Pin number in Arduino |
| ----- | --------------------- | ----- | --------------------- |
| P3.0  | `30`                  | P1.1  | `11`                  |
| P3.1  | `31`                  | P1.3  | `13`                  |
| P3.2  | `32`                  | P2.0  | `20`                  |

### The way to start using ESP32C3 SuperMini

The perfboard wiring picture is compatible with ESP32C3 SuperMini by offset the board  placement lower a row.

**Caution:** You'll need to change the pin definition of the .ino code

Basically the same as an ESP32 <!-- TODO: put ESP32C3 SuperMini tutorial here-->

### The way to flash bootloader to an ATtiny85

#### Caution: the perfboard wiring picture is not compatible with ATtiny85 by offseting anything

You'll have to wire everything on your own according to the [schematic](./Schematic.svg). You'll need to change the pin definition of the .ino code, too.

#### Raw ATtiny85 IC

See [this](https://www.digikey.tw/zh/maker/tutorials/2022/how-to-flash-the-arduino-bootloader-to-an-attiny85-ic). You can use some USB converters like CH340 to use serial function.

I'll suggest you to add some female header / pin socket for pins that's needed for flashing, or find a way to solder your USB converter on your perfboard and connect to your ATtiny85, or take the IC from the device to your motherboard every time you want to flash your change.

#### ATtiny85 board with built-in USB, no matter if you're using the USB type-A one or Micro USB

The step here is basically tested in Arduino IDE v2 (2.3.6).

First, follow the instruction [here](https://medium.com/@akila1001/programming-attiny85-with-arduino-as-isp-attinycore-c0d2b3ad01ba), but when you move on to the last screenshot, which is just on the top of the "Wiring" section, please select the board to `ATtiny85 (Micronucleus / DigiSpark)`, and the clock to 16MHz or 16.5MHz in order to use your ATtiny85 with your USB port.

For the programmer part, the modern version may no longer have `Arduino as ISP (ATTinyCore)` anymore, if so, select `Arduino as ISP` instead.

For wiring, let me add something here to complete the instruction:

| Connect this pin on UNO / Nano | to this pin on your ATtiny85 |
| ------------------------------ | ---------------------------- |
| D10                            | P5                           |
| D11                            | P0                           |
| D12                            | P1                           |
| D13                            | P2                           |
| 5V                             | 5V                           |
| GND                            | GND                          |

Also, connect a **10μF capacitor** between **Reset** (RST) pin and **GND** for **Arduino**. The **long pin** to **Reset**, the **short pin** to **GND**.

Now to the last step: click the `Burn Bootloader` button in `Tools` that's just below the `Programmer` selection.

You should now successfully burnt your Bootloader. If the board still doesn't work, that's because you haven't install the USB driver for ATtiny85. Unlike flashing bootloader, the tutorial of this is commonly spread on the internet. You can simply search that online.

### TODOS IN THE FUTURE <!-- TODO -->

#### To do recently

Upload perfboard wiring picture

#### Stage 1

Add serial communication and develop controlling app on Windows and Linux (maybe use Qt or some kind of webapp like ZMK Studio like [this](https://codelabs.developers.google.com/codelabs/web-serial?hl=zh-tw#0) to make user able to custom their own schedule.  

For example:  
`[1, 3, 1]` = 1 on/off loop, on for 3 hours, off for 1 hour, loop  
`[3, 1, 3, 2, 4, 3, 5]` = 3 on/off loop. On for 1 hour, off for 3 hour, on for 2 hours, off for 4 hours, on for 3 hours, off for 5 hours, loop

Needs to calculate the maximum of milis() function to estimate the suggested and theoretic max hour for a single on or off

#### Stage 2

Able to input minutes and hour decimal point (decimal point and hour can convert to minutes in controlling app, but need to see if the maximum minute (because variable type or processor bit) can handle the theoretic max hour)

#### Out of stage

Shorting two pins on the right to turn on light detecting mode.
Have a photoresistor to detect if the lighting is over a threshold.
If over a threshold, start the loop. If below a threshold, keep disable power delivery.
The threshold can be set in real life by shorting another pin by clipper or wire.

This is the pin configure of the mode switching pin and threshold adjusting pin:

```
Pin:
A      B      C
|      |      |
mode   LOW    threshold toggle
swchŋ  consistent output
```

Soldering A-B together: enable the mode
Touching B-C: record current analog input of the photoresistor pin

Rough codes about the analog pin:

```cpp
uint8_t photoRth = 128;
void setup()
{
    // ...
    if(EEPROM.read(254) == 1) photoRth = EEPROM.read(255);
    // ...
}
```

```cpp
void thresholdUpd(int Dpin, int Apin)
{
    if(digitalRead(Dpin) == LOW)
    {
        while(digitalRead(Dpin) == LOW);
        uint8_t rec = analogRead(Apin);
        if(rec == 255) rec--;
        EEPROM.record(rec, 255);
        EEPROM.record(1, 254); // checking byte to confirm the validation of the data
        photoRth = EEPROM.read(255);
    }
}
```

```cpp
    if(analogRead(photoRpin) > photoRth)
    {
        // the loop code, but make sure start with enable power delivery
    }
    else
    {
        digitalWrite(gate, LOW);
        toggle = true; // disable power delivery and record current state
    }
```
