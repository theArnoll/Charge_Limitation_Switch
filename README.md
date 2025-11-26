### This project is still still in the conceptual stage. It have NOT be tested

A little USB stick that can switch VCC automatically by time based on ATTiny85

### BOM:

| **元件名稱**             | **規格 / 型號建議**                         | **數量** | **備註**                                         |
| -------------------- | ------------------------------------- | ------ | ---------------------------------------------- |
| **核心開發板**            | **Digispark ATTiny85 (Micro USB)**    | 1      | 請確認有附 **排針 (Pin Header)**，方便焊接。                |
| **P-Channel MOSFET** | **IRF9Z24N** (首選) 或 **IRF9540N**      | 1      | 封裝：**TO-220** (黑色方塊長腳)。建議多買一顆備用。               |
| **電阻**               | **220Ω, 10kΩ**                        | 1, 1   | 功率：**1/4W** (0.25W)。220Ω 保護用，10kΩ 上拉用。         |
| **USB 轉接板**          | **USB Type-A Male and Female to DIP** | 1, 1   | **必買 DIP 轉接板型** (2.54mm 孔距)，不要買只有金屬頭的散件。       |
| **按鈕開關**             | **A simple button**                   | 1      | 高度不限，一般的即可。                                    |
| **電路板**              | **洞洞板**                               | 1      | 尺寸建議：**2x8cm** 或 **3x7cm** 長條形，剛好做成 Dongle 形狀。 |

MOSFET is to simulate the function of a relay

Since it's based on ATTiny85, the time will be few minutes off per day, so if you really want make it turn on and off on accurate time, using other development boards like Arduino Nano, Micro or Raspberry Pi Pico, Zero etc. and make some change in the code  would be suggested.

#### TODOS IN THE FUTURE

##### Stage 1

Add serial communication and develop controlling app on Windows and Linux (maybe use Qt or some kind of webapp like ZMK Studio) to make user able to custom their own schedule.

For example:
`[1, 3, 1]` = 1 on/off loop, on for 3 hours, off for 1 hour, loop
`[3, 1, 3, 2, 4, 3, 5]` = 3 on/off loop. On for 1 hour, off for 3 hour, on for 2 hours, off for 4 hours, on for 3 hours, off for 5 hours, loop

Needs to calculate the maximum of milis() func to estimate the suggested and theoretic max hour for a single on or off

##### Stage 2

Able to inpute minutes and hour decimal point (decimal point and hour can convert to minutes in controlling app, but need to see if the maximum minute (because variable type or processor bit) can handle the theoretic max hour)
