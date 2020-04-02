EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A3 16535 11693
encoding utf-8
Sheet 8 10
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Text Label 1690 3850 2    50   ~ 0
SPI3
Text Label 1690 3550 2    50   ~ 0
SPI0
Text Label 1690 3650 2    50   ~ 0
SPI1
Text Label 1140 3850 1    50   ~ 0
SPI[0..7]
Text Label 1690 3750 2    50   ~ 0
SPI2
Entry Wire Line
	1140 3450 1240 3550
Entry Wire Line
	1140 3550 1240 3650
Entry Wire Line
	1140 3650 1240 3750
Entry Wire Line
	1140 3750 1240 3850
Entry Wire Line
	1140 3850 1240 3950
Text Label 1690 3950 2    50   ~ 0
SPI4
Entry Wire Line
	1140 3950 1240 4050
Text Label 1690 4050 2    50   ~ 0
SPI5
Text Notes -1935 4650 0    50   ~ 0
DIGITAL0 = (TMC - uC) STATUS\nDIGITAL1 = (TMC - uC) BRAKE\nDIGITAL2 = (TMC - uc - Button) nRST\nDIGITAL3 = (TMC4671 - TMC6200) ENO\nDIGITAL4 = (TMC6200 - uC) FAULT\nDIGITAL5 = (uC - Opamp) REF
$Comp
L power:+12V #PWR0121
U 1 1 5E23AA29
P 3075 9550
F 0 "#PWR0121" H 3075 9400 50  0001 C CNN
F 1 "+12V" H 3090 9723 50  0000 C CNN
F 2 "" H 3075 9550 50  0001 C CNN
F 3 "" H 3075 9550 50  0001 C CNN
	1    3075 9550
	1    0    0    -1  
$EndComp
Text Notes 4100 9350 0    197  ~ 39
Gate-Treiber
$Comp
L Pro6_Print-rescue:0805_22ohm,150V,125mW,1%-SamacSys_Parts R84
U 1 1 5E171463
P 6025 7100
F 0 "R84" H 6375 7325 50  0000 C CNN
F 1 "0805_22ohm,150V,125mW,1%" H 6375 7234 50  0000 C CNN
F 2 "RESC2012X70N" H 6575 7150 50  0001 L CNN
F 3 "https://componentsearchengine.com/Datasheets/1/ERJ-6ENF22R0V.pdf" H 6575 7050 50  0001 L CNN
F 4 "Thick Film Resistors - SMD 0805 22.0ohms 1% AEC-Q200" H 6575 6950 50  0001 L CNN "Description"
F 5 "0.7" H 6575 6850 50  0001 L CNN "Height"
F 6 "667-ERJ-6ENF22R0V" H 6575 6750 50  0001 L CNN "Mouser Part Number"
F 7 "https://www.mouser.com/Search/Refine.aspx?Keyword=667-ERJ-6ENF22R0V" H 6575 6650 50  0001 L CNN "Mouser Price/Stock"
F 8 "Panasonic" H 6575 6550 50  0001 L CNN "Manufacturer_Name"
F 9 "ERJ-6ENF22R0V" H 6575 6450 50  0001 L CNN "Manufacturer_Part_Number"
	1    6025 7100
	1    0    0    -1  
$EndComp
$Comp
L Pro6_Print-rescue:0805_22ohm,150V,125mW,1%-SamacSys_Parts R81
U 1 1 5E12171B
P 5250 6925
F 0 "R81" H 5600 7150 50  0000 C CNN
F 1 "0805_22ohm,150V,125mW,1%" H 5600 7059 50  0000 C CNN
F 2 "RESC2012X70N" H 5800 6975 50  0001 L CNN
F 3 "https://componentsearchengine.com/Datasheets/1/ERJ-6ENF22R0V.pdf" H 5800 6875 50  0001 L CNN
F 4 "Thick Film Resistors - SMD 0805 22.0ohms 1% AEC-Q200" H 5800 6775 50  0001 L CNN "Description"
F 5 "0.7" H 5800 6675 50  0001 L CNN "Height"
F 6 "667-ERJ-6ENF22R0V" H 5800 6575 50  0001 L CNN "Mouser Part Number"
F 7 "https://www.mouser.com/Search/Refine.aspx?Keyword=667-ERJ-6ENF22R0V" H 5800 6475 50  0001 L CNN "Mouser Price/Stock"
F 8 "Panasonic" H 5800 6375 50  0001 L CNN "Manufacturer_Name"
F 9 "ERJ-6ENF22R0V" H 5800 6275 50  0001 L CNN "Manufacturer_Part_Number"
	1    5250 6925
	1    0    0    -1  
$EndComp
$Comp
L Pro6_Print-rescue:0805_22ohm,150V,125mW,1%-SamacSys_Parts R80
U 1 1 5E11511D
P 4475 6750
F 0 "R80" H 4825 6975 50  0000 C CNN
F 1 "0805_22ohm,150V,125mW,1%" H 4825 6884 50  0000 C CNN
F 2 "RESC2012X70N" H 5025 6800 50  0001 L CNN
F 3 "https://componentsearchengine.com/Datasheets/1/ERJ-6ENF22R0V.pdf" H 5025 6700 50  0001 L CNN
F 4 "Thick Film Resistors - SMD 0805 22.0ohms 1% AEC-Q200" H 5025 6600 50  0001 L CNN "Description"
F 5 "0.7" H 5025 6500 50  0001 L CNN "Height"
F 6 "667-ERJ-6ENF22R0V" H 5025 6400 50  0001 L CNN "Mouser Part Number"
F 7 "https://www.mouser.com/Search/Refine.aspx?Keyword=667-ERJ-6ENF22R0V" H 5025 6300 50  0001 L CNN "Mouser Price/Stock"
F 8 "Panasonic" H 5025 6200 50  0001 L CNN "Manufacturer_Name"
F 9 "ERJ-6ENF22R0V" H 5025 6100 50  0001 L CNN "Manufacturer_Part_Number"
	1    4475 6750
	1    0    0    -1  
$EndComp
Text Label 2750 7200 0    50   ~ 0
Shunt0
Text Label 2750 7300 0    50   ~ 0
Shunt1
Text Label 2750 7400 0    50   ~ 0
Shunt2
Text Label 8100 8200 2    50   ~ 0
GATE2_L
Text Label 8100 8025 2    50   ~ 0
GATE1_L
Text Label 8100 7850 2    50   ~ 0
GATE0_L
Text Label 8100 8725 2    50   ~ 0
GATE2_H
Text Label 8100 8550 2    50   ~ 0
GATE1_H
Text Label 8100 8375 2    50   ~ 0
GATE0_H
$Comp
L Pro6_Print-rescue:0805_2.2Ohm,150V,1%,125mW-SamacSys_Parts R87
U 1 1 5DF0150A
P 6850 8200
F 0 "R87" H 7200 8425 50  0000 C CNN
F 1 "0805_2.2Ohm,150V,1%,125mW" H 7200 8334 50  0000 C CNN
F 2 "RESC2012X50N" H 7400 8250 50  0001 L CNN
F 3 "https://componentsearchengine.com/Datasheets/1/CRCW08052R20FKEA.pdf" H 7400 8150 50  0001 L CNN
F 4 "VISHAY - CRCW08052R20FKEA - RES, 2R2, 1%, 0.125W, 0805" H 7400 8050 50  0001 L CNN "Description"
F 5 "0.5" H 7400 7950 50  0001 L CNN "Height"
F 6 "71-CRCW08052R20FKEA" H 7400 7850 50  0001 L CNN "Mouser Part Number"
F 7 "https://www.mouser.com/Search/Refine.aspx?Keyword=71-CRCW08052R20FKEA" H 7400 7750 50  0001 L CNN "Mouser Price/Stock"
F 8 "Vishay" H 7400 7650 50  0001 L CNN "Manufacturer_Name"
F 9 "CRCW08052R20FKEA" H 7400 7550 50  0001 L CNN "Manufacturer_Part_Number"
	1    6850 8200
	1    0    0    -1  
$EndComp
$Comp
L Pro6_Print-rescue:0805_2.2Ohm,150V,1%,125mW-SamacSys_Parts R85
U 1 1 5DF014FE
P 6050 8025
F 0 "R85" H 6400 8250 50  0000 C CNN
F 1 "0805_2.2Ohm,150V,1%,125mW" H 6400 8159 50  0000 C CNN
F 2 "RESC2012X50N" H 6600 8075 50  0001 L CNN
F 3 "https://componentsearchengine.com/Datasheets/1/CRCW08052R20FKEA.pdf" H 6600 7975 50  0001 L CNN
F 4 "VISHAY - CRCW08052R20FKEA - RES, 2R2, 1%, 0.125W, 0805" H 6600 7875 50  0001 L CNN "Description"
F 5 "0.5" H 6600 7775 50  0001 L CNN "Height"
F 6 "71-CRCW08052R20FKEA" H 6600 7675 50  0001 L CNN "Mouser Part Number"
F 7 "https://www.mouser.com/Search/Refine.aspx?Keyword=71-CRCW08052R20FKEA" H 6600 7575 50  0001 L CNN "Mouser Price/Stock"
F 8 "Vishay" H 6600 7475 50  0001 L CNN "Manufacturer_Name"
F 9 "CRCW08052R20FKEA" H 6600 7375 50  0001 L CNN "Manufacturer_Part_Number"
	1    6050 8025
	1    0    0    -1  
$EndComp
$Comp
L Pro6_Print-rescue:0805_2.2Ohm,150V,1%,125mW-SamacSys_Parts R82
U 1 1 5DF014F2
P 5250 7850
F 0 "R82" H 5600 8075 50  0000 C CNN
F 1 "0805_2.2Ohm,150V,1%,125mW" H 5600 7984 50  0000 C CNN
F 2 "RESC2012X50N" H 5800 7900 50  0001 L CNN
F 3 "https://componentsearchengine.com/Datasheets/1/CRCW08052R20FKEA.pdf" H 5800 7800 50  0001 L CNN
F 4 "VISHAY - CRCW08052R20FKEA - RES, 2R2, 1%, 0.125W, 0805" H 5800 7700 50  0001 L CNN "Description"
F 5 "0.5" H 5800 7600 50  0001 L CNN "Height"
F 6 "71-CRCW08052R20FKEA" H 5800 7500 50  0001 L CNN "Mouser Part Number"
F 7 "https://www.mouser.com/Search/Refine.aspx?Keyword=71-CRCW08052R20FKEA" H 5800 7400 50  0001 L CNN "Mouser Price/Stock"
F 8 "Vishay" H 5800 7300 50  0001 L CNN "Manufacturer_Name"
F 9 "CRCW08052R20FKEA" H 5800 7200 50  0001 L CNN "Manufacturer_Part_Number"
	1    5250 7850
	1    0    0    -1  
$EndComp
$Comp
L Pro6_Print-rescue:0805_2.2Ohm,150V,1%,125mW-SamacSys_Parts R86
U 1 1 5DEDB265
P 6050 8550
F 0 "R86" H 6400 8775 50  0000 C CNN
F 1 "0805_2.2Ohm,150V,1%,125mW" H 6400 8684 50  0000 C CNN
F 2 "RESC2012X50N" H 6600 8600 50  0001 L CNN
F 3 "https://componentsearchengine.com/Datasheets/1/CRCW08052R20FKEA.pdf" H 6600 8500 50  0001 L CNN
F 4 "VISHAY - CRCW08052R20FKEA - RES, 2R2, 1%, 0.125W, 0805" H 6600 8400 50  0001 L CNN "Description"
F 5 "0.5" H 6600 8300 50  0001 L CNN "Height"
F 6 "71-CRCW08052R20FKEA" H 6600 8200 50  0001 L CNN "Mouser Part Number"
F 7 "https://www.mouser.com/Search/Refine.aspx?Keyword=71-CRCW08052R20FKEA" H 6600 8100 50  0001 L CNN "Mouser Price/Stock"
F 8 "Vishay" H 6600 8000 50  0001 L CNN "Manufacturer_Name"
F 9 "CRCW08052R20FKEA" H 6600 7900 50  0001 L CNN "Manufacturer_Part_Number"
	1    6050 8550
	1    0    0    -1  
$EndComp
$Comp
L Pro6_Print-rescue:0805_2.2Ohm,150V,1%,125mW-SamacSys_Parts R83
U 1 1 5DED60DC
P 5250 8375
F 0 "R83" H 5600 8600 50  0000 C CNN
F 1 "0805_2.2Ohm,150V,1%,125mW" H 5600 8509 50  0000 C CNN
F 2 "RESC2012X50N" H 5800 8425 50  0001 L CNN
F 3 "https://componentsearchengine.com/Datasheets/1/CRCW08052R20FKEA.pdf" H 5800 8325 50  0001 L CNN
F 4 "VISHAY - CRCW08052R20FKEA - RES, 2R2, 1%, 0.125W, 0805" H 5800 8225 50  0001 L CNN "Description"
F 5 "0.5" H 5800 8125 50  0001 L CNN "Height"
F 6 "71-CRCW08052R20FKEA" H 5800 8025 50  0001 L CNN "Mouser Part Number"
F 7 "https://www.mouser.com/Search/Refine.aspx?Keyword=71-CRCW08052R20FKEA" H 5800 7925 50  0001 L CNN "Mouser Price/Stock"
F 8 "Vishay" H 5800 7825 50  0001 L CNN "Manufacturer_Name"
F 9 "CRCW08052R20FKEA" H 5800 7725 50  0001 L CNN "Manufacturer_Part_Number"
	1    5250 8375
	1    0    0    -1  
$EndComp
$Comp
L Pro6_Print-rescue:0805_100nF,100V,5%-SamacSys_Parts C?
U 1 1 5EEB6E31
P 2850 10050
AR Path="/5EEB6E31" Ref="C?"  Part="1" 
AR Path="/5E4D7F26/5EEB6E31" Ref="C74"  Part="1" 
F 0 "C74" H 3100 9785 50  0000 C CNN
F 1 "0805_100nF,100V,5%" H 3100 9876 50  0000 C CNN
F 2 "CAPC2012X140N" H 3200 10100 50  0001 L CNN
F 3 "https://componentsearchengine.com/Datasheets/1/08051C104JAT2A.pdf" H 3200 10000 50  0001 L CNN
F 4 "AVX 100nF Multilayer Ceramic Capacitor MLCC 100V dc +/-5% X7R Dielectric 0805 SMD, Max. Temp. +125C" H 3200 9900 50  0001 L CNN "Description"
F 5 "1.4" H 3200 9800 50  0001 L CNN "Height"
F 6 "581-08051C104JAT2A" H 3200 9700 50  0001 L CNN "Mouser Part Number"
F 7 "https://www.mouser.com/Search/Refine.aspx?Keyword=581-08051C104JAT2A" H 3200 9600 50  0001 L CNN "Mouser Price/Stock"
F 8 "AVX" H 3200 9500 50  0001 L CNN "Manufacturer_Name"
F 9 "08051C104JAT2A" H 3200 9400 50  0001 L CNN "Manufacturer_Part_Number"
	1    2850 10050
	-1   0    0    1   
$EndComp
Text Label 8100 6325 2    50   ~ 0
Shunt2
Text Label 8100 6100 2    50   ~ 0
Shunt1
Text Label 8100 5875 2    50   ~ 0
Shunt0
Text Label 2750 7600 0    50   ~ 0
DIGITAL1
Text Label 2750 7800 0    50   ~ 0
ADCI1
Text Label 2750 7700 0    50   ~ 0
ADCI0
$Comp
L Pro6_Print-rescue:0805_100nF,50V,5%-SamacSys_Parts C72
U 1 1 6008EF86
P 2850 9125
F 0 "C72" H 3200 8825 50  0000 R CNN
F 1 "0805_100nF,50V,5%" H 3500 8925 50  0000 R CNN
F 2 "CAPC2012X88N" H 3200 9175 50  0001 L CNN
F 3 "https://componentsearchengine.com/Datasheets/1/C0805C104J5RACTU.pdf" H 3200 9075 50  0001 L CNN
F 4 "Kemet 100nF +/-5% 50 V dc X7R Dielectric SMD Ceramic Multilayer Capacitor 0805" H 3200 8975 50  0001 L CNN "Description"
F 5 "0.88" H 3200 8875 50  0001 L CNN "Height"
F 6 "80-C0805C104J5R" H 3200 8775 50  0001 L CNN "Mouser Part Number"
F 7 "https://www.mouser.com/Search/Refine.aspx?Keyword=80-C0805C104J5R" H 3200 8675 50  0001 L CNN "Mouser Price/Stock"
F 8 "Kemet" H 3200 8575 50  0001 L CNN "Manufacturer_Name"
F 9 "C0805C104J5RACTU" H 3200 8475 50  0001 L CNN "Manufacturer_Part_Number"
	1    2850 9125
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR0114
U 1 1 6006C7F7
P 1700 6825
F 0 "#PWR0114" H 1700 6575 50  0001 C CNN
F 1 "GND" H 1705 6652 50  0000 C CNN
F 2 "" H 1700 6825 50  0001 C CNN
F 3 "" H 1700 6825 50  0001 C CNN
	1    1700 6825
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR0116
U 1 1 600289FB
P 2525 7450
F 0 "#PWR0116" H 2525 7300 50  0001 C CNN
F 1 "+5V" H 2540 7623 50  0000 C CNN
F 2 "" H 2525 7450 50  0001 C CNN
F 3 "" H 2525 7450 50  0001 C CNN
	1    2525 7450
	1    0    0    -1  
$EndComp
Text Label 4875 7400 2    50   ~ 0
PWM2
Text Label 4875 7700 2    50   ~ 0
PWM3
Text Label 4875 7600 2    50   ~ 0
PWM5
Text Label 4875 7300 2    50   ~ 0
PWM4
Text Label 4875 7200 2    50   ~ 0
PWM6
Text Label 4875 7500 2    50   ~ 0
PWM7
$Comp
L Pro6_Print-rescue:0805_100nF,100V,5%-SamacSys_Parts C?
U 1 1 5EFFF6DB
P 2850 9600
AR Path="/5EFFF6DB" Ref="C?"  Part="1" 
AR Path="/5E4D7F26/5EFFF6DB" Ref="C73"  Part="1" 
F 0 "C73" H 3100 9300 50  0000 C CNN
F 1 "0805_100nF,100V,5%" H 3100 9426 50  0000 C CNN
F 2 "CAPC2012X140N" H 3200 9650 50  0001 L CNN
F 3 "https://componentsearchengine.com/Datasheets/1/08051C104JAT2A.pdf" H 3200 9550 50  0001 L CNN
F 4 "AVX 100nF Multilayer Ceramic Capacitor MLCC 100V dc +/-5% X7R Dielectric 0805 SMD, Max. Temp. +125C" H 3200 9450 50  0001 L CNN "Description"
F 5 "1.4" H 3200 9350 50  0001 L CNN "Height"
F 6 "581-08051C104JAT2A" H 3200 9250 50  0001 L CNN "Mouser Part Number"
F 7 "https://www.mouser.com/Search/Refine.aspx?Keyword=581-08051C104JAT2A" H 3200 9150 50  0001 L CNN "Mouser Price/Stock"
F 8 "AVX" H 3200 9050 50  0001 L CNN "Manufacturer_Name"
F 9 "08051C104JAT2A" H 3200 8950 50  0001 L CNN "Manufacturer_Part_Number"
	1    2850 9600
	-1   0    0    1   
$EndComp
$Comp
L power:+48V #PWR0117
U 1 1 5ED8E1B9
P 2625 6175
F 0 "#PWR0117" H 2625 6025 50  0001 C CNN
F 1 "+48V" H 2640 6348 50  0000 C CNN
F 2 "" H 2625 6175 50  0001 C CNN
F 3 "" H 2625 6175 50  0001 C CNN
	1    2625 6175
	1    0    0    -1  
$EndComp
Text Label 2750 6600 0    50   ~ 0
DIGITAL0
$Comp
L power:GND #PWR0115
U 1 1 5E8CDCDD
P 2200 10400
F 0 "#PWR0115" H 2200 10150 50  0001 C CNN
F 1 "GND" H 2205 10227 50  0000 C CNN
F 2 "" H 2200 10400 50  0001 C CNN
F 3 "" H 2200 10400 50  0001 C CNN
	1    2200 10400
	1    0    0    -1  
$EndComp
$Comp
L Pro6_Print-rescue:0805_2.2uF,50V,20%-SamacSys_Parts C69
U 1 1 5E8A7D5C
P 2350 8650
F 0 "C69" H 2600 8915 50  0000 C CNN
F 1 "0805_2.2uF,50V,20%" H 2600 8824 50  0000 C CNN
F 2 "CAPC2012X95N" H 2700 8700 50  0001 L CNN
F 3 "https://componentsearchengine.com/Datasheets/1/UMK212BB7225MG-T.pdf" H 2700 8600 50  0001 L CNN
F 4 "Multilayer Ceramic Capacitors MLCC - SMD/SMT 0805 50V 2.2uF 20% X7R" H 2700 8500 50  0001 L CNN "Description"
F 5 "0.95" H 2700 8400 50  0001 L CNN "Height"
F 6 "963-UMK212BB7225MG-T" H 2700 8300 50  0001 L CNN "Mouser Part Number"
F 7 "https://www.mouser.com/Search/Refine.aspx?Keyword=963-UMK212BB7225MG-T" H 2700 8200 50  0001 L CNN "Mouser Price/Stock"
F 8 "TAIYO YUDEN" H 2700 8100 50  0001 L CNN "Manufacturer_Name"
F 9 "UMK212BB7225MG-T" H 2700 8000 50  0001 L CNN "Manufacturer_Part_Number"
	1    2350 8650
	1    0    0    -1  
$EndComp
$Comp
L power:+48V #PWR0122
U 1 1 5E68EF8D
P 3075 10000
F 0 "#PWR0122" H 3075 9850 50  0001 C CNN
F 1 "+48V" H 3090 10173 50  0000 C CNN
F 2 "" H 3075 10000 50  0001 C CNN
F 3 "" H 3075 10000 50  0001 C CNN
	1    3075 10000
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR0120
U 1 1 5E5CE111
P 3075 9075
F 0 "#PWR0120" H 3075 8925 50  0001 C CNN
F 1 "+5V" H 3090 9248 50  0000 C CNN
F 2 "" H 3075 9075 50  0001 C CNN
F 3 "" H 3075 9075 50  0001 C CNN
	1    3075 9075
	1    0    0    -1  
$EndComp
Text Label 2750 7100 0    50   ~ 0
SPI4
Text Label 2750 7000 0    50   ~ 0
SPI2
Text Label 2750 6900 0    50   ~ 0
SPI_GD_OUT
Text Label 2750 6800 0    50   ~ 0
SPI0
NoConn ~ 3100 8000
NoConn ~ 3100 7900
$Comp
L Pro6_Print-rescue:TMC6200-TA-SamacSys_Parts U?
U 1 1 5E5A61F8
P 3700 7450
AR Path="/5E5A61F8" Ref="U?"  Part="1" 
AR Path="/5E4D7F26/5E5A61F8" Ref="U4"  Part="1" 
F 0 "U4" H 3700 8631 50  0000 C CNN
F 1 "TMC6200-TA" H 3700 8540 50  0000 C CNN
F 2 "Package_QFP:TQFP-48-1EP_7x7mm_P0.5mm_EP5x5mm_ThermalVias" H 3700 6350 50  0001 C CNN
F 3 "https://www.trinamic.com/fileadmin/assets/Products/ICs_Documents/TMC2100_datasheet_Rev1.08.pdf" H 2550 8500 50  0001 C CNN
	1    3700 7450
	1    0    0    -1  
$EndComp
$Comp
L Pro6_Print-rescue:0805_22nF,100V,10%-SamacSys_Parts C75
U 1 1 5E1EE7E3
P 3350 5875
F 0 "C75" H 3600 6140 50  0000 C CNN
F 1 "0805_22nF,100V,10%" H 3600 6049 50  0000 C CNN
F 2 "CAPC2012X145N" H 3700 5925 50  0001 L CNN
F 3 "https://componentsearchengine.com/Datasheets/1/C2012X7R2A223K125AA.pdf" H 3700 5825 50  0001 L CNN
F 4 "TDK C2012 C 22nF Ceramic Multilayer Capacitor, 100 V dc, +125C, X7R Dielectric, +/-10% SMD" H 3700 5725 50  0001 L CNN "Description"
F 5 "1.45" H 3700 5625 50  0001 L CNN "Height"
F 6 "810-C2012X7R2A223K" H 3700 5525 50  0001 L CNN "Mouser Part Number"
F 7 "https://www.mouser.com/Search/Refine.aspx?Keyword=810-C2012X7R2A223K" H 3700 5425 50  0001 L CNN "Mouser Price/Stock"
F 8 "TDK" H 3700 5325 50  0001 L CNN "Manufacturer_Name"
F 9 "C2012X7R2A223K125AA" H 3700 5225 50  0001 L CNN "Manufacturer_Part_Number"
	1    3350 5875
	1    0    0    -1  
$EndComp
Entry Wire Line
	4875 7200 4975 7300
Entry Wire Line
	4875 7300 4975 7400
Entry Wire Line
	4875 7400 4975 7500
Entry Wire Line
	4875 7500 4975 7600
Entry Wire Line
	4875 7600 4975 7700
Entry Wire Line
	4875 7700 4975 7800
$Comp
L Pro6_Print-rescue:0805_2.2Ohm,150V,1%,125mW-SamacSys_Parts R88
U 1 1 5DEE4CFE
P 6850 8725
F 0 "R88" H 7200 8950 50  0000 C CNN
F 1 "0805_2.2Ohm,150V,1%,125mW" H 7200 8859 50  0000 C CNN
F 2 "RESC2012X50N" H 7400 8775 50  0001 L CNN
F 3 "https://componentsearchengine.com/Datasheets/1/CRCW08052R20FKEA.pdf" H 7400 8675 50  0001 L CNN
F 4 "VISHAY - CRCW08052R20FKEA - RES, 2R2, 1%, 0.125W, 0805" H 7400 8575 50  0001 L CNN "Description"
F 5 "0.5" H 7400 8475 50  0001 L CNN "Height"
F 6 "71-CRCW08052R20FKEA" H 7400 8375 50  0001 L CNN "Mouser Part Number"
F 7 "https://www.mouser.com/Search/Refine.aspx?Keyword=71-CRCW08052R20FKEA" H 7400 8275 50  0001 L CNN "Mouser Price/Stock"
F 8 "Vishay" H 7400 8175 50  0001 L CNN "Manufacturer_Name"
F 9 "CRCW08052R20FKEA" H 7400 8075 50  0001 L CNN "Manufacturer_Part_Number"
	1    6850 8725
	1    0    0    -1  
$EndComp
Text Label 8100 6925 2    50   ~ 0
MOTOR1
Text Label 8100 6750 2    50   ~ 0
MOTOR0
Text Label 8100 7100 2    50   ~ 0
MOTOR2
Text HLabel 1060 4150 0    50   Output ~ 0
SPI[0..7]
Entry Wire Line
	2650 7800 2750 7700
Entry Wire Line
	2650 7900 2750 7800
NoConn ~ 7950 3525
NoConn ~ 7950 3450
Entry Wire Line
	6100 3400 6200 3300
Entry Wire Line
	6100 3325 6200 3225
Entry Wire Line
	8125 3375 8225 3275
Entry Wire Line
	8125 3300 8225 3200
Entry Wire Line
	8125 3225 8225 3125
Entry Wire Line
	8125 3150 8225 3050
Entry Wire Line
	8125 3075 8225 2975
Entry Wire Line
	8125 3000 8225 2900
Text Label 6000 2850 0    50   ~ 0
SPI1
$Comp
L power:GND #PWR0126
U 1 1 5EA51F44
P 6950 3825
F 0 "#PWR0126" H 6950 3575 50  0001 C CNN
F 1 "GND" H 6955 3652 50  0000 C CNN
F 2 "" H 6950 3825 50  0001 C CNN
F 3 "" H 6950 3825 50  0001 C CNN
	1    6950 3825
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR0135
U 1 1 5E9C0E4A
P 13800 2100
F 0 "#PWR0135" H 13800 1950 50  0001 C CNN
F 1 "+5V" H 13815 2273 50  0000 C CNN
F 2 "" H 13800 2100 50  0001 C CNN
F 3 "" H 13800 2100 50  0001 C CNN
	1    13800 2100
	1    0    0    -1  
$EndComp
$Comp
L Pro6_Print-rescue:22-28-4050-SamacSys_Parts J46
U 1 1 5E906DA8
P 14650 2175
F 0 "J46" H 15278 2021 50  0000 L CNN
F 1 "22-28-4050" H 15278 1930 50  0000 L CNN
F 2 "HDRV5W66P0X254_1X5_1270X249X838P" H 15300 2275 50  0001 L CNN
F 3 "https://componentsearchengine.com/Datasheets/1/22-28-4050.pdf" H 15300 2175 50  0001 L CNN
F 4 "MOLEX - 22-28-4050 - CONNECTOR, HEADER, 5POS, 1ROW, 2.54MM" H 15300 2075 50  0001 L CNN "Description"
F 5 "8.38" H 15300 1975 50  0001 L CNN "Height"
F 6 "538-22-28-4050" H 15300 1875 50  0001 L CNN "Mouser Part Number"
F 7 "https://www.mouser.com/Search/Refine.aspx?Keyword=538-22-28-4050" H 15300 1775 50  0001 L CNN "Mouser Price/Stock"
F 8 "Molex" H 15300 1675 50  0001 L CNN "Manufacturer_Name"
F 9 "22-28-4050" H 15300 1575 50  0001 L CNN "Manufacturer_Part_Number"
	1    14650 2175
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0137
U 1 1 5E8CA339
P 15400 1950
F 0 "#PWR0137" H 15400 1700 50  0001 C CNN
F 1 "GND" H 15405 1777 50  0000 C CNN
F 2 "" H 15400 1950 50  0001 C CNN
F 3 "" H 15400 1950 50  0001 C CNN
	1    15400 1950
	1    0    0    -1  
$EndComp
$Comp
L Pro6_Print-rescue:0805_100nF,100V,5%-SamacSys_Parts C81
U 1 1 5E88DBA6
P 7625 1775
F 0 "C81" H 7875 2040 50  0000 C CNN
F 1 "0805_100nF,100V,5%" H 7875 1949 50  0000 C CNN
F 2 "CAPC2012X140N" H 7975 1825 50  0001 L CNN
F 3 "https://componentsearchengine.com/Datasheets/1/08051C104JAT2A.pdf" H 7975 1725 50  0001 L CNN
F 4 "AVX 100nF Multilayer Ceramic Capacitor MLCC 100V dc +/-5% X7R Dielectric 0805 SMD, Max. Temp. +125C" H 7975 1625 50  0001 L CNN "Description"
F 5 "1.4" H 7975 1525 50  0001 L CNN "Height"
F 6 "581-08051C104JAT2A" H 7975 1425 50  0001 L CNN "Mouser Part Number"
F 7 "https://www.mouser.com/Search/Refine.aspx?Keyword=581-08051C104JAT2A" H 7975 1325 50  0001 L CNN "Mouser Price/Stock"
F 8 "AVX" H 7975 1225 50  0001 L CNN "Manufacturer_Name"
F 9 "08051C104JAT2A" H 7975 1125 50  0001 L CNN "Manufacturer_Part_Number"
	1    7625 1775
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0123
U 1 1 5E866C4B
P 5325 1825
F 0 "#PWR0123" H 5325 1575 50  0001 C CNN
F 1 "GND" H 5330 1652 50  0000 C CNN
F 2 "" H 5325 1825 50  0001 C CNN
F 3 "" H 5325 1825 50  0001 C CNN
	1    5325 1825
	1    0    0    -1  
$EndComp
$Comp
L Pro6_Print-rescue:0805_100nF,50V,5%-SamacSys_Parts C80
U 1 1 5E7E3431
P 5675 2225
F 0 "C80" H 5925 2490 50  0000 C CNN
F 1 "0805_100nF,50V,5%" H 5925 2399 50  0000 C CNN
F 2 "CAPC2012X88N" H 6025 2275 50  0001 L CNN
F 3 "https://componentsearchengine.com/Datasheets/1/C0805C104J5RACTU.pdf" H 6025 2175 50  0001 L CNN
F 4 "Kemet 100nF +/-5% 50 V dc X7R Dielectric SMD Ceramic Multilayer Capacitor 0805" H 6025 2075 50  0001 L CNN "Description"
F 5 "0.88" H 6025 1975 50  0001 L CNN "Height"
F 6 "80-C0805C104J5R" H 6025 1875 50  0001 L CNN "Mouser Part Number"
F 7 "https://www.mouser.com/Search/Refine.aspx?Keyword=80-C0805C104J5R" H 6025 1775 50  0001 L CNN "Mouser Price/Stock"
F 8 "Kemet" H 6025 1675 50  0001 L CNN "Manufacturer_Name"
F 9 "C0805C104J5RACTU" H 6025 1575 50  0001 L CNN "Manufacturer_Part_Number"
	1    5675 2225
	1    0    0    -1  
$EndComp
$Comp
L Pro6_Print-rescue:0805_100nF,50V,5%-SamacSys_Parts C79
U 1 1 5E7DFE0D
P 5675 1775
F 0 "C79" H 5925 2040 50  0000 C CNN
F 1 "0805_100nF,50V,5%" H 5925 1949 50  0000 C CNN
F 2 "CAPC2012X88N" H 6025 1825 50  0001 L CNN
F 3 "https://componentsearchengine.com/Datasheets/1/C0805C104J5RACTU.pdf" H 6025 1725 50  0001 L CNN
F 4 "Kemet 100nF +/-5% 50 V dc X7R Dielectric SMD Ceramic Multilayer Capacitor 0805" H 6025 1625 50  0001 L CNN "Description"
F 5 "0.88" H 6025 1525 50  0001 L CNN "Height"
F 6 "80-C0805C104J5R" H 6025 1425 50  0001 L CNN "Mouser Part Number"
F 7 "https://www.mouser.com/Search/Refine.aspx?Keyword=80-C0805C104J5R" H 6025 1325 50  0001 L CNN "Mouser Price/Stock"
F 8 "Kemet" H 6025 1225 50  0001 L CNN "Manufacturer_Name"
F 9 "C0805C104J5RACTU" H 6025 1125 50  0001 L CNN "Manufacturer_Part_Number"
	1    5675 1775
	1    0    0    -1  
$EndComp
$Comp
L power:+48V #PWR0127
U 1 1 5E89D269
P 7350 1725
F 0 "#PWR0127" H 7350 1575 50  0001 C CNN
F 1 "+48V" H 7365 1898 50  0000 C CNN
F 2 "" H 7350 1725 50  0001 C CNN
F 3 "" H 7350 1725 50  0001 C CNN
	1    7350 1725
	1    0    0    -1  
$EndComp
$Comp
L Pro6_Print-rescue:TMC4671-BOB-trinamic U?
U 1 1 5E643524
P 6950 2975
AR Path="/5E509610/5E643524" Ref="U?"  Part="1" 
AR Path="/5DB5D066/5E643524" Ref="U?"  Part="1" 
AR Path="/5E4D7F26/5E643524" Ref="U5"  Part="1" 
AR Path="/5E643524" Ref="U?"  Part="1" 
F 0 "U5" H 6950 4025 40  0000 C CNN
F 1 "TMC4671-BOB" H 6950 3950 40  0000 C CNN
F 2 "trinamic-footprints:32pin1,5x1,6-BOB" H 7800 3175 40  0001 L CNN
F 3 "https://www.trinamic.com/fileadmin/assets/Products/Eval_Documents/TMC4671-BOB_datasheet_Rev1.0.pdf" H 7800 3275 40  0001 L CNN
F 4 "1460-1317-ND" H 7800 3375 60  0001 L CNN "Digi-Key_PN"
F 5 "TMC4671-BOB" H 7800 3475 60  0001 L CNN "MPN"
F 6 "Development Boards, Kits, Programmers" H 7800 3575 60  0001 L CNN "Category"
F 7 "Evaluation and Demonstration Boards and Kits" H 7800 3675 60  0001 L CNN "Family"
F 8 "https://www.trinamic.com/fileadmin/assets/Products/Eval_Documents/TMC4671-BOB_datasheet_Rev1.0.pdf" H 7800 3775 60  0001 L CNN "DK_Datasheet_Link"
F 9 "/product-detail/en/trinamic-motion-control-gmbh/TMC4671-BOB/1460-1317-ND/9491138" H 7800 3875 60  0001 L CNN "DK_Detail_Page"
F 10 "BREAKOUTBOARD FOR TMC4671" H 7800 3975 60  0001 L CNN "Description"
F 11 "Trinamic Motion Control GmbH" H 7800 4075 60  0001 L CNN "Manufacturer"
F 12 "Active" H 7800 4175 60  0001 L CNN "Status"
	1    6950 2975
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR0124
U 1 1 5E87EEEA
P 6400 2175
F 0 "#PWR0124" H 6400 2025 50  0001 C CNN
F 1 "+5V" H 6415 2348 50  0000 C CNN
F 2 "" H 6400 2175 50  0001 C CNN
F 3 "" H 6400 2175 50  0001 C CNN
	1    6400 2175
	1    0    0    -1  
$EndComp
NoConn ~ 7500 2700
NoConn ~ 7500 2775
NoConn ~ 7500 2850
Text Label 6000 2625 0    50   ~ 0
SPILV3
Text Label 6000 2775 0    50   ~ 0
SPILV0
Text Label 6000 2700 0    50   ~ 0
SPILV2
NoConn ~ 6400 2475
NoConn ~ 6400 2400
NoConn ~ 6400 3075
Text Notes 5980 1285 0    197  ~ 39
FOC-Treiber
$Comp
L power:+3.3V #PWR?
U 1 1 5E64353E
P 6525 1725
AR Path="/5E509610/5E64353E" Ref="#PWR?"  Part="1" 
AR Path="/5DB5D066/5E64353E" Ref="#PWR?"  Part="1" 
AR Path="/5E4D7F26/5E64353E" Ref="#PWR0125"  Part="1" 
F 0 "#PWR0125" H 6525 1575 50  0001 C CNN
F 1 "+3.3V" H 6540 1898 50  0000 C CNN
F 2 "" H 6525 1725 50  0001 C CNN
F 3 "" H 6525 1725 50  0001 C CNN
	1    6525 1725
	1    0    0    -1  
$EndComp
Text Label 6215 3300 0    50   ~ 0
ADCI1
Text Label 6215 3225 0    50   ~ 0
ADCI0
Text Label 7800 3225 2    50   ~ 0
PWM4
Text Label 7800 3150 2    50   ~ 0
PWM5
Text Label 7800 3000 2    50   ~ 0
PWM7
Text Label 7800 3075 2    50   ~ 0
PWM6
Text Label 7800 3375 2    50   ~ 0
PWM2
Text Label 7800 3300 2    50   ~ 0
PWM3
Text Label 7800 3525 2    50   ~ 0
PWM0
Text Label 7800 3450 2    50   ~ 0
PWM1
NoConn ~ 6400 3000
$Comp
L Pro6_Print-rescue:100nF,50V,10%-SamacSys_Parts C70
U 1 1 5E6FFA27
P 2475 2925
F 0 "C70" H 2725 3190 50  0000 C CNN
F 1 "100nF,50V,10%-SamacSys_Parts" H 2725 3099 50  0000 C CNN
F 2 "CAPC1608X95N" H 2825 2975 50  0001 L CNN
F 3 "http://www.farnell.com/datasheets/2205446.pdf" H 2825 2875 50  0001 L CNN
F 4 "Capacitor Ceramic X7R 0603 50V 100nF KEMET 100nF Multilayer Ceramic Capacitor (MLCC) 50 V +/-10% X7R dielectric C SMD max op. temp. +125C" H 2825 2775 50  0001 L CNN "Description"
F 5 "0.95" H 2825 2675 50  0001 L CNN "Height"
F 6 "Kemet" H 2825 2575 50  0001 L CNN "Manufacturer_Name"
F 7 "C0603C104K5RACTU" H 2825 2475 50  0001 L CNN "Manufacturer_Part_Number"
F 8 "80-C0603C104K5R" H 2825 2375 50  0001 L CNN "Mouser Part Number"
F 9 "https://www.mouser.com/Search/Refine.aspx?Keyword=80-C0603C104K5R" H 2825 2275 50  0001 L CNN "Mouser Price/Stock"
F 10 "8015347" H 2825 2175 50  0001 L CNN "RS Part Number"
F 11 "http://uk.rs-online.com/web/p/products/8015347" H 2825 2075 50  0001 L CNN "RS Price/Stock"
F 12 "70096969" H 2825 1975 50  0001 L CNN "Allied_Number"
F 13 "https://www.alliedelec.com/kemet-c0603c104k5ractu/70096969/" H 2825 1875 50  0001 L CNN "Allied Price/Stock"
	1    2475 2925
	0    1    -1   0   
$EndComp
Text Notes 2080 1410 0    197  ~ 39
Level-Shifter
NoConn ~ 2900 2500
NoConn ~ 2900 2600
NoConn ~ 2900 2800
NoConn ~ 2900 2900
NoConn ~ 2900 3000
Text Label 4400 2800 2    50   ~ 0
SPI0
Text Label 4425 2500 2    50   ~ 0
SPILV3
Text Label 4400 2700 2    50   ~ 0
SPILV2
Text Label 4400 2900 2    50   ~ 0
SPILV0
$Comp
L power:+3.3V #PWR0119
U 1 1 5EB1E9C8
P 2850 3325
AR Path="/5E4D7F26/5EB1E9C8" Ref="#PWR0119"  Part="1" 
AR Path="/5E4D4518/5EB1E9C8" Ref="#PWR?"  Part="1" 
AR Path="/5E5D5A26/5EB1E9C8" Ref="#PWR?"  Part="1" 
AR Path="/5E562C99/5EB1E9C8" Ref="#PWR?"  Part="1" 
F 0 "#PWR0119" H 2850 3175 50  0001 C CNN
F 1 "+3.3V" H 2865 3498 50  0000 C CNN
F 2 "" H 2850 3325 50  0001 C CNN
F 3 "" H 2850 3325 50  0001 C CNN
	1    2850 3325
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0118
U 1 1 5EB1E9C1
P 2850 2075
AR Path="/5E4D7F26/5EB1E9C1" Ref="#PWR0118"  Part="1" 
AR Path="/5E4D4518/5EB1E9C1" Ref="#PWR?"  Part="1" 
AR Path="/5E5D5A26/5EB1E9C1" Ref="#PWR?"  Part="1" 
AR Path="/5E562C99/5EB1E9C1" Ref="#PWR?"  Part="1" 
F 0 "#PWR0118" H 2850 1825 50  0001 C CNN
F 1 "GND" H 2855 1902 50  0000 C CNN
F 2 "" H 2850 2075 50  0001 C CNN
F 3 "" H 2850 2075 50  0001 C CNN
	1    2850 2075
	1    0    0    -1  
$EndComp
Text Label 4425 2400 2    50   ~ 0
SPI3
Text Label 4400 2600 2    50   ~ 0
SPI2
$Comp
L Pro6_Print-rescue:74HC4050D-SamacSys_Parts IC9
U 1 1 5EB1E9B8
P 4000 3000
AR Path="/5E4D7F26/5EB1E9B8" Ref="IC9"  Part="1" 
AR Path="/5E4D4518/5EB1E9B8" Ref="IC?"  Part="1" 
AR Path="/5E5D5A26/5EB1E9B8" Ref="IC?"  Part="1" 
AR Path="/5E562C99/5EB1E9B8" Ref="IC?"  Part="1" 
F 0 "IC9" V 4596 2172 50  0000 R CNN
F 1 "74HC4050D" V 4505 2172 50  0000 R CNN
F 2 "SOIC127P600X175-16N" H 4950 3100 50  0001 L CNN
F 3 "https://componentsearchengine.com/Datasheets/1/74HC4050D.pdf" H 4950 3000 50  0001 L CNN
F 4 "74HC4050D, 6-Bit Buffer, Converter, HC, Non-Inverting 2 to 6V 16-Pin SOIC" H 4950 2900 50  0001 L CNN "Description"
F 5 "1.75" H 4950 2800 50  0001 L CNN "Height"
F 6 "771-74HC4050D" H 4950 2700 50  0001 L CNN "Mouser Part Number"
F 7 "https://www.mouser.com/Search/Refine.aspx?Keyword=771-74HC4050D" H 4950 2600 50  0001 L CNN "Mouser Price/Stock"
F 8 "Nexperia" H 4950 2500 50  0001 L CNN "Manufacturer_Name"
F 9 "74HC4050D" H 4950 2400 50  0001 L CNN "Manufacturer_Part_Number"
	1    4000 3000
	-1   0    0    1   
$EndComp
Text Notes -1935 4025 0    50   ~ 0
SPI0 (SPI - Dipswitch) = SPI MOSI\nSPI1 (SPI - Dipswitch) = SPI MISO\nSPI2 (SPI - Dipswitch) = SPI SCK\nSPI3 (FOC - Dipswitch) = SPI CS TMC4671\nSPI4 (uC - EEPROM) = SPI CS AT2512\nSPI5 (uC - Gatedriver) = SPI CS TMC6200
Text Label 9475 9050 1    50   ~ 0
GATE0_L
$Comp
L Pro6_Print-rescue:BSC030N08NS5ATMA1-SamacSys_Parts Q17
U 1 1 5EDBFFCB
P 9175 8750
F 0 "Q17" H 9675 9015 50  0000 C CNN
F 1 "BSC030N08NS5ATMA1" H 9675 8924 50  0000 C CNN
F 2 "PG-TDSON-8-5" H 10025 8850 50  0001 L CNN
F 3 "https://componentsearchengine.com/Datasheets/1/BSC030N08NS5ATMA1.pdf" H 10025 8750 50  0001 L CNN
F 4 "BSC030N08NS5ATMA1 N-Channel MOSFET, 100 A, 80 V BSC030N08NS5, 8-Pin TDSON Infineon" H 10025 8650 50  0001 L CNN "Description"
F 5 "" H 10025 8550 50  0001 L CNN "Height"
F 6 "726-BSC030N08NS5ATMA" H 10025 8450 50  0001 L CNN "Mouser Part Number"
F 7 "https://www.mouser.com/Search/Refine.aspx?Keyword=726-BSC030N08NS5ATMA" H 10025 8350 50  0001 L CNN "Mouser Price/Stock"
F 8 "Infineon" H 10025 8250 50  0001 L CNN "Manufacturer_Name"
F 9 "BSC030N08NS5ATMA1" H 10025 8150 50  0001 L CNN "Manufacturer_Part_Number"
	1    9175 8750
	0    -1   -1   0   
$EndComp
Text Label 10875 9050 1    50   ~ 0
GATE1_L
$Comp
L Pro6_Print-rescue:BSC030N08NS5ATMA1-SamacSys_Parts Q19
U 1 1 5F212E90
P 10575 8750
F 0 "Q19" H 11075 9015 50  0000 C CNN
F 1 "BSC030N08NS5ATMA1" H 11075 8924 50  0000 C CNN
F 2 "PG-TDSON-8-5" H 11425 8850 50  0001 L CNN
F 3 "https://componentsearchengine.com/Datasheets/1/BSC030N08NS5ATMA1.pdf" H 11425 8750 50  0001 L CNN
F 4 "BSC030N08NS5ATMA1 N-Channel MOSFET, 100 A, 80 V BSC030N08NS5, 8-Pin TDSON Infineon" H 11425 8650 50  0001 L CNN "Description"
F 5 "" H 11425 8550 50  0001 L CNN "Height"
F 6 "726-BSC030N08NS5ATMA" H 11425 8450 50  0001 L CNN "Mouser Part Number"
F 7 "https://www.mouser.com/Search/Refine.aspx?Keyword=726-BSC030N08NS5ATMA" H 11425 8350 50  0001 L CNN "Mouser Price/Stock"
F 8 "Infineon" H 11425 8250 50  0001 L CNN "Manufacturer_Name"
F 9 "BSC030N08NS5ATMA1" H 11425 8150 50  0001 L CNN "Manufacturer_Part_Number"
	1    10575 8750
	0    -1   -1   0   
$EndComp
Text Label 12325 9050 1    50   ~ 0
GATE2_L
$Comp
L Pro6_Print-rescue:BSC030N08NS5ATMA1-SamacSys_Parts Q21
U 1 1 5F22F92D
P 12025 8750
F 0 "Q21" H 12525 9015 50  0000 C CNN
F 1 "BSC030N08NS5ATMA1" H 12525 8924 50  0000 C CNN
F 2 "PG-TDSON-8-5" H 12875 8850 50  0001 L CNN
F 3 "https://componentsearchengine.com/Datasheets/1/BSC030N08NS5ATMA1.pdf" H 12875 8750 50  0001 L CNN
F 4 "BSC030N08NS5ATMA1 N-Channel MOSFET, 100 A, 80 V BSC030N08NS5, 8-Pin TDSON Infineon" H 12875 8650 50  0001 L CNN "Description"
F 5 "" H 12875 8550 50  0001 L CNN "Height"
F 6 "726-BSC030N08NS5ATMA" H 12875 8450 50  0001 L CNN "Mouser Part Number"
F 7 "https://www.mouser.com/Search/Refine.aspx?Keyword=726-BSC030N08NS5ATMA" H 12875 8350 50  0001 L CNN "Mouser Price/Stock"
F 8 "Infineon" H 12875 8250 50  0001 L CNN "Manufacturer_Name"
F 9 "BSC030N08NS5ATMA1" H 12875 8150 50  0001 L CNN "Manufacturer_Part_Number"
	1    12025 8750
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR0133
U 1 1 5F4DE269
P 12975 9350
F 0 "#PWR0133" H 12975 9100 50  0001 C CNN
F 1 "GND" H 12980 9177 50  0000 C CNN
F 2 "" H 12975 9350 50  0001 C CNN
F 3 "" H 12975 9350 50  0001 C CNN
	1    12975 9350
	1    0    0    -1  
$EndComp
$Comp
L power:+48V #PWR0129
U 1 1 5DB760C2
P 9375 5450
F 0 "#PWR0129" H 9375 5300 50  0001 C CNN
F 1 "+48V" H 9390 5623 50  0000 C CNN
F 2 "" H 9375 5450 50  0001 C CNN
F 3 "" H 9375 5450 50  0001 C CNN
	1    9375 5450
	1    0    0    -1  
$EndComp
Text Label 14350 7500 0    50   ~ 0
MOTOR0
Text Notes 10125 5450 0    197  ~ 39
H-Brücke
Text Label 10575 7200 3    50   ~ 0
Shunt1
$Comp
L Pro6_Print-rescue:BSC030N08NS5ATMA1-SamacSys_Parts Q16
U 1 1 5EC534EA
P 9175 6700
F 0 "Q16" H 9675 6965 50  0000 C CNN
F 1 "BSC030N08NS5ATMA1" H 9675 6874 50  0000 C CNN
F 2 "PG-TDSON-8-5" H 10025 6800 50  0001 L CNN
F 3 "https://componentsearchengine.com/Datasheets/1/BSC030N08NS5ATMA1.pdf" H 10025 6700 50  0001 L CNN
F 4 "BSC030N08NS5ATMA1 N-Channel MOSFET, 100 A, 80 V BSC030N08NS5, 8-Pin TDSON Infineon" H 10025 6600 50  0001 L CNN "Description"
F 5 "" H 10025 6500 50  0001 L CNN "Height"
F 6 "726-BSC030N08NS5ATMA" H 10025 6400 50  0001 L CNN "Mouser Part Number"
F 7 "https://www.mouser.com/Search/Refine.aspx?Keyword=726-BSC030N08NS5ATMA" H 10025 6300 50  0001 L CNN "Mouser Price/Stock"
F 8 "Infineon" H 10025 6200 50  0001 L CNN "Manufacturer_Name"
F 9 "BSC030N08NS5ATMA1" H 10025 6100 50  0001 L CNN "Manufacturer_Part_Number"
	1    9175 6700
	0    -1   -1   0   
$EndComp
Text Label 9475 7000 1    50   ~ 0
GATE0_H
$Comp
L Pro6_Print-rescue:BSC030N08NS5ATMA1-SamacSys_Parts Q18
U 1 1 5F212E78
P 10575 6700
F 0 "Q18" H 11075 6965 50  0000 C CNN
F 1 "BSC030N08NS5ATMA1" H 11075 6874 50  0000 C CNN
F 2 "PG-TDSON-8-5" H 11425 6800 50  0001 L CNN
F 3 "https://componentsearchengine.com/Datasheets/1/BSC030N08NS5ATMA1.pdf" H 11425 6700 50  0001 L CNN
F 4 "BSC030N08NS5ATMA1 N-Channel MOSFET, 100 A, 80 V BSC030N08NS5, 8-Pin TDSON Infineon" H 11425 6600 50  0001 L CNN "Description"
F 5 "" H 11425 6500 50  0001 L CNN "Height"
F 6 "726-BSC030N08NS5ATMA" H 11425 6400 50  0001 L CNN "Mouser Part Number"
F 7 "https://www.mouser.com/Search/Refine.aspx?Keyword=726-BSC030N08NS5ATMA" H 11425 6300 50  0001 L CNN "Mouser Price/Stock"
F 8 "Infineon" H 11425 6200 50  0001 L CNN "Manufacturer_Name"
F 9 "BSC030N08NS5ATMA1" H 11425 6100 50  0001 L CNN "Manufacturer_Part_Number"
	1    10575 6700
	0    -1   -1   0   
$EndComp
Text Label 10875 7000 1    50   ~ 0
GATE1_H
Text Label 14350 7300 0    50   ~ 0
MOTOR2
$Comp
L Pro6_Print-rescue:BSC030N08NS5ATMA1-SamacSys_Parts Q20
U 1 1 5F22F915
P 12025 6700
F 0 "Q20" H 12525 6965 50  0000 C CNN
F 1 "BSC030N08NS5ATMA1" H 12525 6874 50  0000 C CNN
F 2 "PG-TDSON-8-5" H 12875 6800 50  0001 L CNN
F 3 "https://componentsearchengine.com/Datasheets/1/BSC030N08NS5ATMA1.pdf" H 12875 6700 50  0001 L CNN
F 4 "BSC030N08NS5ATMA1 N-Channel MOSFET, 100 A, 80 V BSC030N08NS5, 8-Pin TDSON Infineon" H 12875 6600 50  0001 L CNN "Description"
F 5 "" H 12875 6500 50  0001 L CNN "Height"
F 6 "726-BSC030N08NS5ATMA" H 12875 6400 50  0001 L CNN "Mouser Part Number"
F 7 "https://www.mouser.com/Search/Refine.aspx?Keyword=726-BSC030N08NS5ATMA" H 12875 6300 50  0001 L CNN "Mouser Price/Stock"
F 8 "Infineon" H 12875 6200 50  0001 L CNN "Manufacturer_Name"
F 9 "BSC030N08NS5ATMA1" H 12875 6100 50  0001 L CNN "Manufacturer_Part_Number"
	1    12025 6700
	0    -1   -1   0   
$EndComp
Text Label 12325 7000 1    50   ~ 0
GATE2_H
Text Label 12025 7450 1    50   ~ 0
Shunt2
$Comp
L power:PWR_FLAG #FLG05
U 1 1 5E1B32C3
P 9175 5700
F 0 "#FLG05" H 9175 5775 50  0001 C CNN
F 1 "PWR_FLAG" H 9175 5873 50  0000 C CNN
F 2 "" H 9175 5700 50  0001 C CNN
F 3 "~" H 9175 5700 50  0001 C CNN
	1    9175 5700
	1    0    0    -1  
$EndComp
Text Label 9175 7200 3    50   ~ 0
Shunt0
Text Label 14350 7400 0    50   ~ 0
MOTOR1
$Comp
L power:GND #PWR0134
U 1 1 60732ECB
P 13625 5700
F 0 "#PWR0134" H 13625 5450 50  0001 C CNN
F 1 "GND" H 13630 5527 50  0000 C CNN
F 2 "" H 13625 5700 50  0001 C CNN
F 3 "" H 13625 5700 50  0001 C CNN
	1    13625 5700
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0130
U 1 1 5E16573A
P 9925 6550
F 0 "#PWR0130" H 9925 6300 50  0001 C CNN
F 1 "GND" H 9930 6377 50  0000 C CNN
F 2 "" H 9925 6550 50  0001 C CNN
F 3 "" H 9925 6550 50  0001 C CNN
	1    9925 6550
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0131
U 1 1 5E1725A6
P 11375 6550
F 0 "#PWR0131" H 11375 6300 50  0001 C CNN
F 1 "GND" H 11380 6377 50  0000 C CNN
F 2 "" H 11375 6550 50  0001 C CNN
F 3 "" H 11375 6550 50  0001 C CNN
	1    11375 6550
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0132
U 1 1 5E17D300
P 12825 6550
F 0 "#PWR0132" H 12825 6300 50  0001 C CNN
F 1 "GND" H 12830 6377 50  0000 C CNN
F 2 "" H 12825 6550 50  0001 C CNN
F 3 "" H 12825 6550 50  0001 C CNN
	1    12825 6550
	1    0    0    -1  
$EndComp
$Comp
L Pro6_Print-rescue:EEU-FS2A221-SamacSys_Parts C86
U 1 1 5E2B03A8
P 13025 6100
F 0 "C86" H 13275 6367 50  0000 C CNN
F 1 "EEU-FS2A221" H 13275 6276 50  0000 C CNN
F 2 "CAPPRD500W65D1250H2700" H 13375 6150 50  0001 L CNN
F 3 "https://componentsearchengine.com/Datasheets/1/EEU-FS2A221.pdf" H 13375 6050 50  0001 L CNN
F 4 "Aluminum Electrolytic Capacitors - Radial Leaded 100VDC 220uF 1800mA Polar" H 13375 5950 50  0001 L CNN "Description"
F 5 "27" H 13375 5850 50  0001 L CNN "Height"
F 6 "667-EEU-FS2A221" H 13375 5750 50  0001 L CNN "Mouser Part Number"
F 7 "https://www.mouser.com/Search/Refine.aspx?Keyword=667-EEU-FS2A221" H 13375 5650 50  0001 L CNN "Mouser Price/Stock"
F 8 "Panasonic" H 13375 5550 50  0001 L CNN "Manufacturer_Name"
F 9 "EEU-FS2A221" H 13375 5450 50  0001 L CNN "Manufacturer_Part_Number"
	1    13025 6100
	1    0    0    -1  
$EndComp
$Comp
L Pro6_Print-rescue:EEU-FS2A221-SamacSys_Parts C87
U 1 1 5E2B25E3
P 13025 6500
F 0 "C87" H 13275 6767 50  0000 C CNN
F 1 "EEU-FS2A221" H 13275 6676 50  0000 C CNN
F 2 "CAPPRD500W65D1250H2700" H 13375 6550 50  0001 L CNN
F 3 "https://componentsearchengine.com/Datasheets/1/EEU-FS2A221.pdf" H 13375 6450 50  0001 L CNN
F 4 "Aluminum Electrolytic Capacitors - Radial Leaded 100VDC 220uF 1800mA Polar" H 13375 6350 50  0001 L CNN "Description"
F 5 "27" H 13375 6250 50  0001 L CNN "Height"
F 6 "667-EEU-FS2A221" H 13375 6150 50  0001 L CNN "Mouser Part Number"
F 7 "https://www.mouser.com/Search/Refine.aspx?Keyword=667-EEU-FS2A221" H 13375 6050 50  0001 L CNN "Mouser Price/Stock"
F 8 "Panasonic" H 13375 5950 50  0001 L CNN "Manufacturer_Name"
F 9 "EEU-FS2A221" H 13375 5850 50  0001 L CNN "Manufacturer_Part_Number"
	1    13025 6500
	1    0    0    -1  
$EndComp
$Comp
L Pro6_Print-rescue:EEU-FS2A221-SamacSys_Parts C88
U 1 1 5E2E8F5B
P 13025 6900
F 0 "C88" H 13275 7167 50  0000 C CNN
F 1 "EEU-FS2A221" H 13275 7076 50  0000 C CNN
F 2 "CAPPRD500W65D1250H2700" H 13375 6950 50  0001 L CNN
F 3 "https://componentsearchengine.com/Datasheets/1/EEU-FS2A221.pdf" H 13375 6850 50  0001 L CNN
F 4 "Aluminum Electrolytic Capacitors - Radial Leaded 100VDC 220uF 1800mA Polar" H 13375 6750 50  0001 L CNN "Description"
F 5 "27" H 13375 6650 50  0001 L CNN "Height"
F 6 "667-EEU-FS2A221" H 13375 6550 50  0001 L CNN "Mouser Part Number"
F 7 "https://www.mouser.com/Search/Refine.aspx?Keyword=667-EEU-FS2A221" H 13375 6450 50  0001 L CNN "Mouser Price/Stock"
F 8 "Panasonic" H 13375 6350 50  0001 L CNN "Manufacturer_Name"
F 9 "EEU-FS2A221" H 13375 6250 50  0001 L CNN "Manufacturer_Part_Number"
	1    13025 6900
	1    0    0    -1  
$EndComp
$Comp
L power:Earth #PWR0136
U 1 1 5F99D767
P 14300 7075
F 0 "#PWR0136" H 14300 6825 50  0001 C CNN
F 1 "Earth" H 14300 6925 50  0001 C CNN
F 2 "" H 14300 7075 50  0001 C CNN
F 3 "~" H 14300 7075 50  0001 C CNN
	1    14300 7075
	1    0    0    -1  
$EndComp
$Comp
L Pro6_Print-rescue:1792889-SamacSys_Parts J47
U 1 1 5F977446
P 14650 7200
F 0 "J47" H 15278 7096 50  0000 L CNN
F 1 "1792889" H 15278 7005 50  0000 L CNN
F 2 "SHDR4W100P0X500_1X4_2000X1050X1360P" H 15300 7300 50  0001 L CNN
F 3 "https://www.phoenixcontact.com/online/portal/us?uri=pxc-oc-itemdetail:pid=1792889" H 15300 7200 50  0001 L CNN
F 4 "Spring PCB terminal block 4 way 12A" H 15300 7100 50  0001 L CNN "Description"
F 5 "13.6" H 15300 7000 50  0001 L CNN "Height"
F 6 "651-1792889" H 15300 6900 50  0001 L CNN "Mouser Part Number"
F 7 "https://www.mouser.com/Search/Refine.aspx?Keyword=651-1792889" H 15300 6800 50  0001 L CNN "Mouser Price/Stock"
F 8 "Phoenix Contact" H 15300 6700 50  0001 L CNN "Manufacturer_Name"
F 9 "1792889" H 15300 6600 50  0001 L CNN "Manufacturer_Part_Number"
	1    14650 7200
	1    0    0    -1  
$EndComp
Text Notes 14040 8005 0    197  ~ 39
Motor-Pins\n
Text Notes 13790 3205 0    197  ~ 39
Encoder-Pins
$Comp
L power:GND #PWR0128
U 1 1 60A12D0D
P 8375 1775
F 0 "#PWR0128" H 8375 1525 50  0001 C CNN
F 1 "GND" H 8380 1602 50  0000 C CNN
F 2 "" H 8375 1775 50  0001 C CNN
F 3 "" H 8375 1775 50  0001 C CNN
	1    8375 1775
	1    0    0    -1  
$EndComp
Entry Wire Line
	1140 4050 1240 4150
Text Label 1690 4150 2    50   ~ 0
SPI6
Entry Wire Line
	1150 4650 1250 4750
Text Label 1700 4750 2    50   ~ 0
DIGITAL4
Entry Wire Line
	1150 4550 1250 4650
Text Label 1700 4650 2    50   ~ 0
DIGITAL3
Entry Wire Line
	1150 4450 1250 4550
Text Label 1700 4550 2    50   ~ 0
DIGITAL2
Entry Wire Line
	1150 4350 1250 4450
Entry Wire Line
	1150 4250 1250 4350
Text Label 1700 4350 2    50   ~ 0
DIGITAL0
Text Label 1700 4450 2    50   ~ 0
DIGITAL1
Text HLabel 1085 4750 0    50   Output ~ 0
DIGITAL[0..5]
Wire Wire Line
	1240 4050 1690 4050
Wire Wire Line
	2750 7200 3100 7200
Wire Wire Line
	3100 7300 2750 7300
Wire Wire Line
	2750 7400 3100 7400
Wire Wire Line
	2525 7450 2525 7500
Wire Wire Line
	3100 7800 2750 7800
Wire Wire Line
	2750 7700 3100 7700
Wire Wire Line
	3075 9075 3075 9125
Wire Wire Line
	3750 8450 3850 8450
Wire Wire Line
	3850 5875 3850 6450
Wire Wire Line
	3350 5875 3350 6025
Wire Wire Line
	3350 6025 3750 6025
Wire Wire Line
	3750 6025 3750 6450
Wire Wire Line
	3650 6450 3650 6300
Wire Wire Line
	3650 6300 3350 6300
Wire Wire Line
	2625 6175 2625 6300
Wire Wire Line
	2625 6300 2850 6300
Wire Wire Line
	5500 6325 4150 6325
Wire Wire Line
	4150 6325 4150 6450
Wire Wire Line
	4850 6100 4050 6100
Wire Wire Line
	4050 6100 4050 6450
Wire Wire Line
	4200 5875 3950 5875
Wire Wire Line
	3950 5875 3950 6450
Wire Wire Line
	4300 6900 4400 6900
Wire Wire Line
	4300 7100 6025 7100
Wire Wire Line
	4400 6900 4400 6750
Wire Wire Line
	4400 6750 4475 6750
Wire Wire Line
	6725 7100 8100 7100
Wire Wire Line
	2350 9125 2200 9125
Connection ~ 3075 9125
Wire Wire Line
	3075 9125 3450 9125
Wire Wire Line
	2850 9125 3075 9125
Wire Wire Line
	2350 9600 2200 9600
Wire Wire Line
	2200 9125 2200 9600
Connection ~ 2200 9600
Wire Wire Line
	2850 9600 3075 9600
Connection ~ 3250 9600
Wire Wire Line
	3250 9600 3550 9600
Wire Wire Line
	3075 9550 3075 9600
Connection ~ 3075 9600
Wire Wire Line
	3075 9600 3250 9600
Wire Wire Line
	2350 10050 2200 10050
Wire Wire Line
	2200 9600 2200 10050
Wire Wire Line
	2200 10050 2200 10300
Connection ~ 2200 10050
Wire Wire Line
	2850 10050 3075 10050
Wire Wire Line
	3075 10000 3075 10050
Connection ~ 3075 10050
Wire Wire Line
	3075 10050 3650 10050
Wire Wire Line
	3750 10300 2200 10300
Connection ~ 2200 10300
Wire Wire Line
	2200 10300 2200 10400
Wire Wire Line
	3650 8450 3650 10050
Wire Wire Line
	3550 8450 3550 9600
Wire Wire Line
	3450 8450 3450 9125
Wire Wire Line
	3750 8450 3750 10300
Connection ~ 3750 8450
Wire Wire Line
	3250 8450 3250 9600
Wire Wire Line
	3350 8650 3350 8450
Wire Wire Line
	2200 9125 2200 8650
Connection ~ 2200 9125
Wire Wire Line
	2200 8650 2350 8650
Wire Wire Line
	2850 8650 3350 8650
Wire Wire Line
	2400 6800 2400 3550
Wire Wire Line
	2400 6800 3100 6800
Wire Wire Line
	2300 6900 3100 6900
Wire Wire Line
	2200 7000 2200 3750
Wire Wire Line
	2200 7000 3100 7000
Wire Wire Line
	2100 7100 2100 3950
Wire Wire Line
	2100 7100 3100 7100
Wire Wire Line
	4825 6925 5250 6925
Wire Wire Line
	4300 7000 4825 7000
Wire Wire Line
	4825 7000 4825 6925
Wire Wire Line
	4875 7800 4875 7850
Wire Wire Line
	4875 7850 5250 7850
Wire Wire Line
	4775 7900 4775 8025
Wire Wire Line
	4775 8025 6050 8025
Wire Wire Line
	4675 8000 4675 8200
Wire Wire Line
	4675 8200 6850 8200
Wire Wire Line
	4300 7200 4875 7200
Wire Wire Line
	4300 7300 4875 7300
Wire Wire Line
	4300 7400 4875 7400
Wire Wire Line
	4300 7500 4875 7500
Wire Wire Line
	4300 7600 4875 7600
Wire Wire Line
	4300 7700 4875 7700
Wire Wire Line
	4300 7800 4875 7800
Wire Wire Line
	4300 7900 4775 7900
Wire Wire Line
	4300 8000 4675 8000
Wire Wire Line
	4300 8100 4575 8100
Wire Wire Line
	4300 8200 4475 8200
Wire Wire Line
	4300 8300 4375 8300
Wire Wire Line
	5250 8375 4575 8375
Wire Wire Line
	4575 8100 4575 8375
Wire Wire Line
	4475 8550 6050 8550
Wire Wire Line
	4475 8200 4475 8550
Wire Wire Line
	4375 8725 6850 8725
Wire Wire Line
	4375 8300 4375 8725
Wire Bus Line
	4975 7200 8225 7200
Wire Wire Line
	5950 6925 8100 6925
Wire Wire Line
	5175 6750 8100 6750
Wire Wire Line
	8100 7850 5950 7850
Wire Wire Line
	8100 8025 6750 8025
Wire Wire Line
	8100 8200 7550 8200
Wire Wire Line
	8100 8375 5950 8375
Wire Wire Line
	8100 8550 6750 8550
Wire Wire Line
	8100 8725 7550 8725
Wire Wire Line
	4700 5875 8100 5875
Wire Wire Line
	5350 6100 8100 6100
Wire Wire Line
	6000 6325 8100 6325
Wire Wire Line
	2525 7500 3100 7500
Wire Bus Line
	2000 7700 2650 7700
Wire Wire Line
	7500 3525 7950 3525
Wire Wire Line
	7500 3450 7950 3450
Wire Wire Line
	6200 3300 6400 3300
Wire Wire Line
	6200 3225 6400 3225
Wire Wire Line
	7500 3375 8125 3375
Wire Wire Line
	7500 3300 8125 3300
Wire Wire Line
	7500 3225 8125 3225
Wire Wire Line
	7500 3150 8125 3150
Wire Wire Line
	7500 3075 8125 3075
Wire Wire Line
	7500 3000 8125 3000
Wire Wire Line
	6000 2850 6000 3650
Wire Wire Line
	5925 2775 5925 2900
Wire Wire Line
	6400 2775 5925 2775
Wire Wire Line
	5925 2625 5925 2500
Wire Wire Line
	6400 2625 5925 2625
Wire Wire Line
	5475 1775 5675 1775
Connection ~ 5475 1775
Wire Wire Line
	5325 1775 5475 1775
Wire Wire Line
	5325 1825 5325 1775
Wire Wire Line
	8125 1775 8375 1775
Wire Wire Line
	7350 1775 7350 2225
Connection ~ 7350 1775
Wire Wire Line
	7625 1775 7350 1775
Wire Wire Line
	7350 1725 7350 1775
Wire Wire Line
	6525 1775 6525 2175
Connection ~ 6525 1775
Wire Wire Line
	6175 1775 6525 1775
Connection ~ 6400 2225
Wire Wire Line
	6175 2225 6400 2225
Wire Wire Line
	6525 1725 6525 1775
Wire Wire Line
	6400 2225 6900 2225
Wire Wire Line
	7575 2550 7575 2575
Wire Wire Line
	7500 2550 7575 2550
Wire Wire Line
	7575 2400 7575 2375
Wire Wire Line
	7500 2400 7575 2400
Wire Wire Line
	6950 3775 7000 3775
Connection ~ 6950 3775
Wire Wire Line
	6950 3775 6950 3825
Wire Wire Line
	6900 3775 6950 3775
Connection ~ 7000 3775
Wire Wire Line
	14600 1950 15400 1950
Wire Wire Line
	14650 2175 14600 2175
Wire Wire Line
	5475 2225 5475 1775
Wire Wire Line
	5675 2225 5475 2225
Wire Wire Line
	6525 2175 6950 2175
Connection ~ 6900 3775
Wire Wire Line
	6850 3775 6900 3775
Wire Wire Line
	7000 3775 7050 3775
Wire Wire Line
	6400 2175 6400 2225
Wire Wire Line
	6950 2175 6950 2225
Wire Wire Line
	6000 2850 6400 2850
Wire Wire Line
	7000 2225 7350 2225
Wire Bus Line
	6100 4050 2000 4050
Wire Wire Line
	4000 2700 6400 2700
Wire Wire Line
	4000 2400 4675 2400
Wire Wire Line
	4675 2400 4675 3850
Wire Wire Line
	4000 2600 4550 2600
Wire Wire Line
	4550 2600 4550 3750
Wire Wire Line
	4000 2900 5925 2900
Wire Wire Line
	4000 2500 5925 2500
Wire Wire Line
	4000 2800 4450 2800
Wire Wire Line
	4450 3550 4450 2800
Wire Wire Line
	2850 2025 4050 2025
Connection ~ 2850 2025
Wire Wire Line
	2850 2075 2850 2025
Wire Wire Line
	2850 3325 4050 3325
Connection ~ 2850 3325
Wire Wire Line
	2475 2025 2850 2025
Wire Wire Line
	4050 2300 4050 2025
Wire Wire Line
	2475 2425 2475 2025
Wire Wire Line
	4050 2300 4000 2300
Wire Wire Line
	2475 3325 2850 3325
Wire Wire Line
	2475 2925 2475 3325
Wire Wire Line
	4050 3000 4000 3000
Wire Wire Line
	4050 3000 4050 3325
Wire Wire Line
	9375 5700 9475 5700
Connection ~ 9375 5700
Connection ~ 9475 5700
Connection ~ 9275 5700
Wire Wire Line
	9275 5700 9375 5700
Wire Wire Line
	9375 5450 9375 5700
Wire Wire Line
	9175 7200 9175 7750
Connection ~ 9175 7200
Wire Wire Line
	9425 7200 9175 7200
Wire Wire Line
	9175 6700 9175 7200
Wire Wire Line
	10275 7500 10275 7200
Wire Wire Line
	11675 7400 11675 7200
Wire Wire Line
	13125 7200 13125 7300
Wire Wire Line
	12975 7200 13125 7200
Wire Wire Line
	14575 7000 14575 7200
Connection ~ 12025 7200
Connection ~ 10575 7200
Connection ~ 12025 7750
Connection ~ 10575 7750
Connection ~ 9175 7750
Wire Wire Line
	9475 8750 9475 9050
Wire Wire Line
	9375 7750 9475 7750
Wire Wire Line
	9175 7750 9275 7750
Connection ~ 9275 7750
Wire Wire Line
	9275 7750 9375 7750
Connection ~ 9375 7750
Wire Wire Line
	9375 8750 9275 8750
Connection ~ 9275 8750
Wire Wire Line
	9275 8750 9175 8750
Wire Wire Line
	10875 8750 10875 9050
Wire Wire Line
	10775 7750 10875 7750
Wire Wire Line
	10575 7750 10675 7750
Connection ~ 10675 7750
Wire Wire Line
	10675 7750 10775 7750
Connection ~ 10775 7750
Wire Wire Line
	10775 8750 10675 8750
Connection ~ 10675 8750
Wire Wire Line
	10675 8750 10575 8750
Wire Wire Line
	12325 8750 12325 9050
Wire Wire Line
	12225 7750 12325 7750
Wire Wire Line
	12025 7750 12125 7750
Connection ~ 12125 7750
Wire Wire Line
	12125 7750 12225 7750
Connection ~ 12225 7750
Wire Wire Line
	12225 8750 12125 8750
Connection ~ 12125 8750
Wire Wire Line
	12125 8750 12025 8750
Wire Wire Line
	9175 9150 10575 9150
Wire Wire Line
	9175 8750 9175 9150
Connection ~ 9175 8750
Wire Wire Line
	10575 8750 10575 9150
Connection ~ 10575 8750
Connection ~ 10575 9150
Wire Wire Line
	12025 8750 12025 9150
Wire Wire Line
	10575 9150 12025 9150
Connection ~ 12025 8750
Wire Wire Line
	12975 9150 12975 9350
Wire Wire Line
	12025 9150 12975 9150
Connection ~ 12025 9150
Wire Wire Line
	10575 7200 10575 7750
Wire Wire Line
	12025 7200 12025 7750
Wire Wire Line
	9475 6700 9475 7000
Wire Wire Line
	9175 6700 9275 6700
Connection ~ 9275 6700
Wire Wire Line
	9275 6700 9375 6700
Connection ~ 9175 6700
Wire Wire Line
	9175 5700 9275 5700
Wire Wire Line
	10875 6700 10875 7000
Wire Wire Line
	10575 6700 10675 6700
Connection ~ 10675 6700
Wire Wire Line
	10675 6700 10775 6700
Connection ~ 10575 6700
Connection ~ 10675 5700
Wire Wire Line
	10675 5700 10775 5700
Connection ~ 10775 5700
Wire Wire Line
	10775 5700 10875 5700
Wire Wire Line
	12325 6700 12325 7000
Wire Wire Line
	12025 6700 12125 6700
Connection ~ 12125 6700
Wire Wire Line
	12125 6700 12225 6700
Connection ~ 12025 6700
Wire Wire Line
	12025 5700 12125 5700
Connection ~ 12125 5700
Wire Wire Line
	12125 5700 12225 5700
Connection ~ 12225 5700
Wire Wire Line
	12025 6700 12025 7200
Wire Wire Line
	12025 7200 12275 7200
Wire Wire Line
	10575 6700 10575 7200
Connection ~ 10875 5700
Connection ~ 10575 5700
Wire Wire Line
	10575 5700 10675 5700
Connection ~ 12025 5700
Wire Wire Line
	12225 5700 12325 5700
Connection ~ 9175 5700
Wire Wire Line
	10575 7200 10825 7200
Wire Wire Line
	10875 5700 11375 5700
Wire Wire Line
	9475 5700 9925 5700
Wire Wire Line
	13525 5700 13625 5700
Connection ~ 12325 5700
Wire Wire Line
	10125 7200 10275 7200
Wire Wire Line
	11525 7200 11675 7200
Wire Wire Line
	9925 5900 9925 5700
Connection ~ 9925 5700
Wire Wire Line
	9925 5700 10575 5700
Wire Wire Line
	9925 6400 9925 6550
Wire Wire Line
	11375 6400 11375 6550
Wire Wire Line
	12825 5900 12825 5700
Wire Wire Line
	12825 6400 12825 6550
Wire Wire Line
	12325 5700 12825 5700
Connection ~ 12825 5700
Wire Wire Line
	11375 5700 11375 5900
Connection ~ 11375 5700
Wire Wire Line
	11375 5700 12025 5700
Connection ~ 13025 6100
Wire Wire Line
	13025 6100 13025 5700
Connection ~ 13525 6100
Wire Wire Line
	13525 6100 13525 5700
Wire Wire Line
	13025 6100 13025 6500
Wire Wire Line
	13525 6100 13525 6500
Connection ~ 13025 6500
Connection ~ 13525 6500
Wire Wire Line
	13025 6500 13025 6900
Wire Wire Line
	13525 6500 13525 6900
Wire Wire Line
	14575 7200 14650 7200
Wire Wire Line
	1700 6700 1700 6825
Wire Wire Line
	1900 6600 3100 6600
Wire Bus Line
	2000 4050 2000 7700
Wire Wire Line
	14300 7075 14300 7000
Wire Wire Line
	14300 7000 14575 7000
Wire Wire Line
	13125 7300 14650 7300
Wire Wire Line
	11675 7400 14650 7400
Wire Wire Line
	10275 7500 14650 7500
Wire Wire Line
	14600 1950 14600 2125
Wire Wire Line
	7500 2475 14650 2475
Wire Wire Line
	13800 2100 13800 2125
Wire Wire Line
	7575 2375 14650 2375
Wire Wire Line
	7575 2575 14650 2575
Wire Wire Line
	1240 4150 1690 4150
Wire Wire Line
	1700 4550 1250 4550
Wire Wire Line
	3100 7600 1800 7600
Wire Wire Line
	1700 6700 3100 6700
Wire Notes Line
	2000 1050 4850 1050
Wire Notes Line
	4850 1050 4850 3450
Wire Notes Line
	4850 3450 2000 3450
Wire Notes Line
	2000 3450 2000 1050
Wire Notes Line
	5150 925  8675 925 
Wire Notes Line
	8675 925  8675 4350
Wire Notes Line
	8675 4350 5150 4350
Wire Notes Line
	5150 4350 5150 925 
Wire Notes Line
	13725 1775 15975 1775
Wire Notes Line
	15975 1775 15975 3375
Wire Notes Line
	15975 3375 13725 3375
Wire Notes Line
	13725 3375 13725 1775
Wire Notes Line
	1500 5500 8375 5500
Wire Notes Line
	8375 5500 8375 10850
Wire Notes Line
	8375 10850 1500 10850
Wire Notes Line
	1500 10850 1500 5500
Wire Notes Line
	8725 5000 13800 5000
Wire Notes Line
	13800 5000 13800 9750
Wire Notes Line
	13800 9750 8725 9750
Wire Notes Line
	8725 9750 8725 5000
Wire Notes Line
	13925 6800 15875 6800
Wire Notes Line
	15875 6800 15875 8275
Wire Notes Line
	13925 6800 13925 8275
Wire Notes Line
	13925 8275 15875 8275
Wire Notes Line
	500  3400 1775 3400
Wire Notes Line
	1775 3400 1775 5475
Wire Notes Line
	1775 5475 500  5475
Wire Notes Line
	500  5475 500  3400
Wire Wire Line
	1240 3950 2100 3950
Wire Wire Line
	1240 3850 4675 3850
Connection ~ 2200 3750
Wire Wire Line
	1240 3750 2200 3750
Connection ~ 2400 3550
Wire Wire Line
	2200 3750 4550 3750
Wire Wire Line
	2400 3550 4450 3550
Wire Wire Line
	1240 3550 2400 3550
Wire Bus Line
	1075 4750 1150 4750
Wire Bus Line
	1140 4150 1060 4150
$Comp
L SamacSys_Parts:1206_4.7uF,100V,10% C82
U 1 1 5E8C7ED9
P 9925 5900
F 0 "C82" H 10150 5750 50  0000 L CNN
F 1 "1206_4.7uF,100V,10%" H 9850 6050 50  0000 L CNN
F 2 "CAPC3225X270N" H 10275 5950 50  0001 L CNN
F 3 "https://componentsearchengine.com/Datasheets/1/HMK325C7475KM-PE.pdf" H 10275 5850 50  0001 L CNN
F 4 "Multilayer Ceramic Capacitors MLCC - SMD/SMT 1210 100V 4.7uF 10% X7S" H 10275 5750 50  0001 L CNN "Description"
F 5 "2.7" H 10275 5650 50  0001 L CNN "Height"
F 6 "963-HMK325C7475KM-PE" H 10275 5550 50  0001 L CNN "Mouser Part Number"
F 7 "https://www.mouser.com/Search/Refine.aspx?Keyword=963-HMK325C7475KM-PE" H 10275 5450 50  0001 L CNN "Mouser Price/Stock"
F 8 "TAIYO YUDEN" H 10275 5350 50  0001 L CNN "Manufacturer_Name"
F 9 "HMK325C7475KM-PE" H 10275 5250 50  0001 L CNN "Manufacturer_Part_Number"
	1    9925 5900
	0    1    1    0   
$EndComp
$Comp
L SamacSys_Parts:1206_4.7uF,100V,10% C83
U 1 1 5E8C9C70
P 11375 5900
F 0 "C83" H 11600 5750 50  0000 L CNN
F 1 "1206_4.7uF,100V,10%" H 11300 6050 50  0000 L CNN
F 2 "CAPC3225X270N" H 11725 5950 50  0001 L CNN
F 3 "https://componentsearchengine.com/Datasheets/1/HMK325C7475KM-PE.pdf" H 11725 5850 50  0001 L CNN
F 4 "Multilayer Ceramic Capacitors MLCC - SMD/SMT 1210 100V 4.7uF 10% X7S" H 11725 5750 50  0001 L CNN "Description"
F 5 "2.7" H 11725 5650 50  0001 L CNN "Height"
F 6 "963-HMK325C7475KM-PE" H 11725 5550 50  0001 L CNN "Mouser Part Number"
F 7 "https://www.mouser.com/Search/Refine.aspx?Keyword=963-HMK325C7475KM-PE" H 11725 5450 50  0001 L CNN "Mouser Price/Stock"
F 8 "TAIYO YUDEN" H 11725 5350 50  0001 L CNN "Manufacturer_Name"
F 9 "HMK325C7475KM-PE" H 11725 5250 50  0001 L CNN "Manufacturer_Part_Number"
	1    11375 5900
	0    1    1    0   
$EndComp
$Comp
L SamacSys_Parts:1206_4.7uF,100V,10% C84
U 1 1 5E8DEB8D
P 12825 5900
F 0 "C84" H 13050 5750 50  0000 L CNN
F 1 "1206_4.7uF,100V,10%" H 12750 6050 50  0000 L CNN
F 2 "CAPC3225X270N" H 13175 5950 50  0001 L CNN
F 3 "https://componentsearchengine.com/Datasheets/1/HMK325C7475KM-PE.pdf" H 13175 5850 50  0001 L CNN
F 4 "Multilayer Ceramic Capacitors MLCC - SMD/SMT 1210 100V 4.7uF 10% X7S" H 13175 5750 50  0001 L CNN "Description"
F 5 "2.7" H 13175 5650 50  0001 L CNN "Height"
F 6 "963-HMK325C7475KM-PE" H 13175 5550 50  0001 L CNN "Mouser Part Number"
F 7 "https://www.mouser.com/Search/Refine.aspx?Keyword=963-HMK325C7475KM-PE" H 13175 5450 50  0001 L CNN "Mouser Price/Stock"
F 8 "TAIYO YUDEN" H 13175 5350 50  0001 L CNN "Manufacturer_Name"
F 9 "HMK325C7475KM-PE" H 13175 5250 50  0001 L CNN "Manufacturer_Part_Number"
	1    12825 5900
	0    1    1    0   
$EndComp
$Comp
L SamacSys_Parts:1206_470nF,100V,10% C85
U 1 1 5E921A7A
P 13025 5700
F 0 "C85" H 13275 5965 50  0000 C CNN
F 1 "1206_470nF,100V,10%" H 13275 5874 50  0000 C CNN
F 2 "CAPC3216X175N" H 13375 5750 50  0001 L CNN
F 3 "https://componentsearchengine.com/Datasheets/1/C1206C474K1RACAUTO.pdf" H 13375 5650 50  0001 L CNN
F 4 "KEMET - C1206C474K1RACAUTO - CAPACITOR, MLCC, X7R, 0.47UF, 100V, 1206" H 13375 5550 50  0001 L CNN "Description"
F 5 "1.75" H 13375 5450 50  0001 L CNN "Height"
F 6 "80-C1206C474K1RAUTO" H 13375 5350 50  0001 L CNN "Mouser Part Number"
F 7 "https://www.mouser.com/Search/Refine.aspx?Keyword=80-C1206C474K1RAUTO" H 13375 5250 50  0001 L CNN "Mouser Price/Stock"
F 8 "Kemet" H 13375 5150 50  0001 L CNN "Manufacturer_Name"
F 9 "C1206C474K1RACAUTO" H 13375 5050 50  0001 L CNN "Manufacturer_Part_Number"
	1    13025 5700
	1    0    0    -1  
$EndComp
Wire Wire Line
	12825 5700 13025 5700
Connection ~ 13025 5700
Connection ~ 13525 5700
$Comp
L SamacSys_Parts:1206_1uF,100V,5% C76
U 1 1 5EA47B91
P 4200 5875
F 0 "C76" H 4450 6140 50  0000 C CNN
F 1 "1206_1uF,100V,5%" H 4450 6049 50  0000 C CNN
F 2 "CAPC3316X185N" H 4550 5925 50  0001 L CNN
F 3 "https://componentsearchengine.com/Datasheets/1/C1206X105J1RACTU.pdf" H 4550 5825 50  0001 L CNN
F 4 "Multilayer Ceramic Capacitors MLCC - SMD/SMT 100V 1uF X7R 1206 5%" H 4550 5725 50  0001 L CNN "Description"
F 5 "1.85" H 4550 5625 50  0001 L CNN "Height"
F 6 "80-C1206X105J1R" H 4550 5525 50  0001 L CNN "Mouser Part Number"
F 7 "https://www.mouser.com/Search/Refine.aspx?Keyword=80-C1206X105J1R" H 4550 5425 50  0001 L CNN "Mouser Price/Stock"
F 8 "Kemet" H 4550 5325 50  0001 L CNN "Manufacturer_Name"
F 9 "C1206X105J1RACTU" H 4550 5225 50  0001 L CNN "Manufacturer_Part_Number"
	1    4200 5875
	1    0    0    -1  
$EndComp
$Comp
L SamacSys_Parts:1206_1uF,100V,5% C77
U 1 1 5EA9BFD6
P 4850 6100
F 0 "C77" H 5100 6365 50  0000 C CNN
F 1 "1206_1uF,100V,5%" H 5100 6274 50  0000 C CNN
F 2 "CAPC3316X185N" H 5200 6150 50  0001 L CNN
F 3 "https://componentsearchengine.com/Datasheets/1/C1206X105J1RACTU.pdf" H 5200 6050 50  0001 L CNN
F 4 "Multilayer Ceramic Capacitors MLCC - SMD/SMT 100V 1uF X7R 1206 5%" H 5200 5950 50  0001 L CNN "Description"
F 5 "1.85" H 5200 5850 50  0001 L CNN "Height"
F 6 "80-C1206X105J1R" H 5200 5750 50  0001 L CNN "Mouser Part Number"
F 7 "https://www.mouser.com/Search/Refine.aspx?Keyword=80-C1206X105J1R" H 5200 5650 50  0001 L CNN "Mouser Price/Stock"
F 8 "Kemet" H 5200 5550 50  0001 L CNN "Manufacturer_Name"
F 9 "C1206X105J1RACTU" H 5200 5450 50  0001 L CNN "Manufacturer_Part_Number"
	1    4850 6100
	1    0    0    -1  
$EndComp
$Comp
L SamacSys_Parts:1206_1uF,100V,5% C78
U 1 1 5EAB1220
P 5500 6325
F 0 "C78" H 5750 6590 50  0000 C CNN
F 1 "1206_1uF,100V,5%" H 5750 6499 50  0000 C CNN
F 2 "CAPC3316X185N" H 5850 6375 50  0001 L CNN
F 3 "https://componentsearchengine.com/Datasheets/1/C1206X105J1RACTU.pdf" H 5850 6275 50  0001 L CNN
F 4 "Multilayer Ceramic Capacitors MLCC - SMD/SMT 100V 1uF X7R 1206 5%" H 5850 6175 50  0001 L CNN "Description"
F 5 "1.85" H 5850 6075 50  0001 L CNN "Height"
F 6 "80-C1206X105J1R" H 5850 5975 50  0001 L CNN "Mouser Part Number"
F 7 "https://www.mouser.com/Search/Refine.aspx?Keyword=80-C1206X105J1R" H 5850 5875 50  0001 L CNN "Mouser Price/Stock"
F 8 "Kemet" H 5850 5775 50  0001 L CNN "Manufacturer_Name"
F 9 "C1206X105J1RACTU" H 5850 5675 50  0001 L CNN "Manufacturer_Part_Number"
	1    5500 6325
	1    0    0    -1  
$EndComp
$Comp
L SamacSys_Parts:1206_Shunt,10mOhm,1W,1% R89
U 1 1 5EB60F19
P 9425 7200
F 0 "R89" H 9775 7425 50  0000 C CNN
F 1 "1206_Shunt,10mOhm,1W,1%" H 9775 7334 50  0000 C CNN
F 2 "RESC3216X75N" H 9975 7250 50  0001 L CNN
F 3 "https://componentsearchengine.com/Datasheets/1/ERJ-8CWFR010V.pdf" H 9975 7150 50  0001 L CNN
F 4 "Panasonic ERJ8CW Series Thick Film Fixed Resistor 1206 Case 10m +/-1% 1W +/-50ppm/C" H 9975 7050 50  0001 L CNN "Description"
F 5 "0.75" H 9975 6950 50  0001 L CNN "Height"
F 6 "667-ERJ-8CWFR010V" H 9975 6850 50  0001 L CNN "Mouser Part Number"
F 7 "https://www.mouser.com/Search/Refine.aspx?Keyword=667-ERJ-8CWFR010V" H 9975 6750 50  0001 L CNN "Mouser Price/Stock"
F 8 "Panasonic" H 9975 6650 50  0001 L CNN "Manufacturer_Name"
F 9 "ERJ-8CWFR010V" H 9975 6550 50  0001 L CNN "Manufacturer_Part_Number"
	1    9425 7200
	1    0    0    -1  
$EndComp
$Comp
L SamacSys_Parts:1206_Shunt,10mOhm,1W,1% R90
U 1 1 5EB62197
P 10825 7200
F 0 "R90" H 11175 7425 50  0000 C CNN
F 1 "1206_Shunt,10mOhm,1W,1%" H 11175 7334 50  0000 C CNN
F 2 "RESC3216X75N" H 11375 7250 50  0001 L CNN
F 3 "https://componentsearchengine.com/Datasheets/1/ERJ-8CWFR010V.pdf" H 11375 7150 50  0001 L CNN
F 4 "Panasonic ERJ8CW Series Thick Film Fixed Resistor 1206 Case 10m +/-1% 1W +/-50ppm/C" H 11375 7050 50  0001 L CNN "Description"
F 5 "0.75" H 11375 6950 50  0001 L CNN "Height"
F 6 "667-ERJ-8CWFR010V" H 11375 6850 50  0001 L CNN "Mouser Part Number"
F 7 "https://www.mouser.com/Search/Refine.aspx?Keyword=667-ERJ-8CWFR010V" H 11375 6750 50  0001 L CNN "Mouser Price/Stock"
F 8 "Panasonic" H 11375 6650 50  0001 L CNN "Manufacturer_Name"
F 9 "ERJ-8CWFR010V" H 11375 6550 50  0001 L CNN "Manufacturer_Part_Number"
	1    10825 7200
	1    0    0    -1  
$EndComp
$Comp
L SamacSys_Parts:1206_Shunt,10mOhm,1W,1% R91
U 1 1 5EB77174
P 12275 7200
F 0 "R91" H 12625 7425 50  0000 C CNN
F 1 "1206_Shunt,10mOhm,1W,1%" H 12625 7334 50  0000 C CNN
F 2 "RESC3216X75N" H 12825 7250 50  0001 L CNN
F 3 "https://componentsearchengine.com/Datasheets/1/ERJ-8CWFR010V.pdf" H 12825 7150 50  0001 L CNN
F 4 "Panasonic ERJ8CW Series Thick Film Fixed Resistor 1206 Case 10m +/-1% 1W +/-50ppm/C" H 12825 7050 50  0001 L CNN "Description"
F 5 "0.75" H 12825 6950 50  0001 L CNN "Height"
F 6 "667-ERJ-8CWFR010V" H 12825 6850 50  0001 L CNN "Mouser Part Number"
F 7 "https://www.mouser.com/Search/Refine.aspx?Keyword=667-ERJ-8CWFR010V" H 12825 6750 50  0001 L CNN "Mouser Price/Stock"
F 8 "Panasonic" H 12825 6650 50  0001 L CNN "Manufacturer_Name"
F 9 "ERJ-8CWFR010V" H 12825 6550 50  0001 L CNN "Manufacturer_Part_Number"
	1    12275 7200
	1    0    0    -1  
$EndComp
$Comp
L SamacSys_Parts:0805_100nF,100V,5% C71
U 1 1 5EBA8803
P 2850 6300
F 0 "C71" H 3100 6565 50  0000 C CNN
F 1 "0805_100nF,100V,5%" H 3100 6474 50  0000 C CNN
F 2 "CAPC2012X140N" H 3200 6350 50  0001 L CNN
F 3 "https://componentsearchengine.com/Datasheets/1/08051C104JAT2A.pdf" H 3200 6250 50  0001 L CNN
F 4 "AVX 100nF Multilayer Ceramic Capacitor MLCC 100V dc +/-5% X7R Dielectric 0805 SMD, Max. Temp. +125C" H 3200 6150 50  0001 L CNN "Description"
F 5 "1.4" H 3200 6050 50  0001 L CNN "Height"
F 6 "581-08051C104JAT2A" H 3200 5950 50  0001 L CNN "Mouser Part Number"
F 7 "https://www.mouser.com/Search/Refine.aspx?Keyword=581-08051C104JAT2A" H 3200 5850 50  0001 L CNN "Mouser Price/Stock"
F 8 "AVX" H 3200 5750 50  0001 L CNN "Manufacturer_Name"
F 9 "08051C104JAT2A" H 3200 5650 50  0001 L CNN "Manufacturer_Part_Number"
	1    2850 6300
	1    0    0    -1  
$EndComp
Wire Wire Line
	13800 2275 14650 2275
Wire Wire Line
	13800 2125 13975 2125
Connection ~ 13800 2125
Wire Wire Line
	13800 2125 13800 2275
Wire Wire Line
	14475 2125 14600 2125
Connection ~ 14600 2125
Wire Wire Line
	14600 2125 14600 2175
Wire Wire Line
	1250 4350 1900 4350
Wire Wire Line
	1250 4450 1800 4450
Wire Wire Line
	1900 4350 1900 6600
Wire Wire Line
	1800 4450 1800 7600
Wire Wire Line
	1250 4650 1700 4650
Wire Wire Line
	1250 4750 1700 4750
Wire Wire Line
	2300 3950 2300 6900
Wire Wire Line
	2600 2300 2600 3950
Wire Wire Line
	2600 3950 2300 3950
Wire Wire Line
	2900 2400 2775 2400
Wire Wire Line
	2775 2400 2775 3650
Connection ~ 2775 3650
Wire Wire Line
	2775 3650 6000 3650
Wire Wire Line
	2600 2300 2900 2300
Wire Wire Line
	1240 3650 2775 3650
$Comp
L Pro6_Print-rescue:0805_100nF,100V,5%-SamacSys_Parts C89
U 1 1 5EBF1122
P 13975 2125
F 0 "C89" H 14225 2390 50  0000 C CNN
F 1 "0805_100nF,100V,5%" H 14225 2299 50  0000 C CNN
F 2 "CAPC2012X140N" H 14325 2175 50  0001 L CNN
F 3 "https://componentsearchengine.com/Datasheets/1/08051C104JAT2A.pdf" H 14325 2075 50  0001 L CNN
F 4 "AVX 100nF Multilayer Ceramic Capacitor MLCC 100V dc +/-5% X7R Dielectric 0805 SMD, Max. Temp. +125C" H 14325 1975 50  0001 L CNN "Description"
F 5 "1.4" H 14325 1875 50  0001 L CNN "Height"
F 6 "581-08051C104JAT2A" H 14325 1775 50  0001 L CNN "Mouser Part Number"
F 7 "https://www.mouser.com/Search/Refine.aspx?Keyword=581-08051C104JAT2A" H 14325 1675 50  0001 L CNN "Mouser Price/Stock"
F 8 "AVX" H 14325 1575 50  0001 L CNN "Manufacturer_Name"
F 9 "08051C104JAT2A" H 14325 1475 50  0001 L CNN "Manufacturer_Part_Number"
	1    13975 2125
	1    0    0    -1  
$EndComp
Wire Bus Line
	2650 7700 2650 7900
Wire Bus Line
	6100 3225 6100 4050
Wire Bus Line
	4975 7200 4975 7800
Wire Bus Line
	8225 2875 8225 7200
Wire Bus Line
	1140 3450 1140 4150
Wire Bus Line
	1150 4250 1150 4750
$EndSCHEMATC
