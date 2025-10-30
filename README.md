## About
Resistor Value Calculator is a program that calculates resistance values of SMD and THT resistors.
It is a C++ adaptation of [so1der's SMD Resistor Calculator](https://github.com/so1der/smd-resistors-calc)

<img src="https://github.com/emirunlusoftware/Resistor-Value-Calculator/blob/main/assets/image1_main.png">

## SMD calculator
You can calculate 3-digits, 4-digits, EIA-96 types of SMD resistors. R-digits type is also supported.

<img src="https://github.com/emirunlusoftware/Resistor-Value-Calculator/blob/main/assets/image2_smd.png">


## THT Calculator
Just enter your THT resistor's color bands and find its resistance value. Between four and six band are supported.

NOTE: If you have a 3-band resistor and want to calculate its resistance value by using this program, just click on "4 bands" and enter the color bands.
Then don't care the tolerance part because 3-band resistors don't have a tolerance band but have a fixed tolerance value (±20%).
You can find the standard IEC values of resistance/tolerance/temperature coefficient from [this link](https://www.sis.se/api/document/preview/8021442/) (Page 9, Table 1 – Code colour prescriptions)

<img src="https://github.com/emirunlusoftware/Resistor-Value-Calculator/blob/main/assets/image3_tht.png">
