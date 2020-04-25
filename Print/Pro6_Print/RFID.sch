EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 4 10
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Text Label 9725 3700 2    50   ~ 0
RX0
Entry Wire Line
	9175 3600 9275 3700
Wire Wire Line
	9275 3700 9725 3700
Wire Wire Line
	6100 3575 6550 3575
Entry Wire Line
	6000 3575 6100 3675
Wire Wire Line
	1125 5525 1000 5525
$Comp
L Pro6_Print-rescue:B8B-XH-A_LF__SN_-SamacSys_Parts J5
U 1 1 5E734013
P 1125 5525
F 0 "J5" H 1753 5221 50  0000 L CNN
F 1 "B8B-XH-A_LF__SN_" H 1753 5130 50  0000 L CNN
F 2 "HDRV8W64P0X250_1X8_2240X575X700P" H 1775 5625 50  0001 L CNN
F 3 "http://docs-emea.rs-online.com/webdocs/1357/0900766b81357f2f.pdf" H 1775 5525 50  0001 L CNN
F 4 "XH-2.5mm Header top entry 8 way JST XH Series, Series Number B8B, 2.5mm Pitch 8 Way 1 Row Straight PCB Header, Solder Termination, 3A" H 1775 5425 50  0001 L CNN "Description"
F 5 "7" H 1775 5325 50  0001 L CNN "Height"
F 6 "JST (JAPAN SOLDERLESS TERMINALS)" H 1775 5225 50  0001 L CNN "Manufacturer_Name"
F 7 "B8B-XH-A(LF)(SN)" H 1775 5125 50  0001 L CNN "Manufacturer_Part_Number"
F 8 "" H 1775 5025 50  0001 L CNN "Mouser Part Number"
F 9 "" H 1775 4925 50  0001 L CNN "Mouser Price/Stock"
F 10 "8201576P" H 1775 4825 50  0001 L CNN "RS Part Number"
F 11 "http://uk.rs-online.com/web/p/products/8201576P" H 1775 4725 50  0001 L CNN "RS Price/Stock"
	1    1125 5525
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR037
U 1 1 5E750183
P 775 5525
F 0 "#PWR037" H 775 5375 50  0001 C CNN
F 1 "+3.3V" H 790 5698 50  0000 C CNN
F 2 "" H 775 5525 50  0001 C CNN
F 3 "" H 775 5525 50  0001 C CNN
	1    775  5525
	1    0    0    -1  
$EndComp
Text Label 900  5625 0    50   ~ 0
RESET
Wire Wire Line
	900  5625 1125 5625
Wire Wire Line
	900  5825 1125 5825
Wire Wire Line
	900  5925 1125 5925
Text Label 900  6125 0    50   ~ 0
SPILV2
Wire Wire Line
	900  6025 1125 6025
Wire Wire Line
	900  6125 1125 6125
Text Label 900  5825 0    50   ~ 0
IRQ
Wire Wire Line
	900  6225 1125 6225
$Comp
L power:GND #PWR038
U 1 1 5E77DD7F
P 775 5725
F 0 "#PWR038" H 775 5475 50  0001 C CNN
F 1 "GND" H 780 5552 50  0000 C CNN
F 2 "" H 775 5725 50  0001 C CNN
F 3 "" H 775 5725 50  0001 C CNN
	1    775  5725
	1    0    0    -1  
$EndComp
Text Notes 550  5175 0    197  ~ 39
Verbindung\nDev Kit
Text Label -1125 7300 0    50   ~ 0
SPI[0..7]
Wire Bus Line
	-1125 7300 -825 7300
Text HLabel -1175 7325 0    50   Input ~ 0
SPI[0..7]
Text Label -3300 8100 2    50   ~ 0
SPI6
Wire Wire Line
	-3750 8100 -3300 8100
Entry Wire Line
	-3850 8000 -3750 8100
Text Label -3300 8000 2    50   ~ 0
SPI5
Wire Wire Line
	-3750 8000 -3300 8000
Entry Wire Line
	-3850 7900 -3750 8000
Text Notes -3200 7950 0    50   ~ 0
SPI0 (SPI - Dipswitch) = SPI MOSI\nSPI1 (SPI - Dipswitch) = SPI MISO\nSPI2 (SPI - Dipswitch) = SPI SCK\nSPI3 (FOC - Dipswitch) = SPI CS TMC4671\nSPI4 (uC - EEPROM) = SPI CS AT2512\nSPI5 (uC - Gatedriver) = SPI CS TMC6200
Text Label -3300 7900 2    50   ~ 0
SPI4
Wire Wire Line
	-3750 7900 -3300 7900
Entry Wire Line
	-3850 7800 -3750 7900
Wire Wire Line
	-3750 7800 -3300 7800
Wire Wire Line
	-3750 7700 -3300 7700
Wire Wire Line
	-3750 7600 -3300 7600
Wire Wire Line
	-3750 7500 -3300 7500
Entry Wire Line
	-3850 7700 -3750 7800
Entry Wire Line
	-3850 7600 -3750 7700
Entry Wire Line
	-3850 7500 -3750 7600
Entry Wire Line
	-3850 7400 -3750 7500
Text Label -3300 7700 2    50   ~ 0
SPI2
Text Label -3850 8000 1    50   ~ 0
SPI[0..7]
Text Label -3300 7600 2    50   ~ 0
SPI1
Text Label -3300 7500 2    50   ~ 0
SPI0
Text Label -3300 7800 2    50   ~ 0
SPI3
$Comp
L Pro6_Print-rescue:74HC4050D-SamacSys_Parts IC?
U 1 1 5EA35100
P 6725 5400
AR Path="/5E4D7F26/5EA35100" Ref="IC?"  Part="1" 
AR Path="/5E4D4518/5EA35100" Ref="IC?"  Part="1" 
AR Path="/5E5D5A26/5EA35100" Ref="IC?"  Part="1" 
AR Path="/5E562C99/5EA35100" Ref="IC4"  Part="1" 
F 0 "IC4" V 7321 4572 50  0000 R CNN
F 1 "74HC4050D" V 7230 4572 50  0000 R CNN
F 2 "SOIC127P600X175-16N" H 7675 5500 50  0001 L CNN
F 3 "https://componentsearchengine.com/Datasheets/1/74HC4050D.pdf" H 7675 5400 50  0001 L CNN
F 4 "74HC4050D, 6-Bit Buffer, Converter, HC, Non-Inverting 2 to 6V 16-Pin SOIC" H 7675 5300 50  0001 L CNN "Description"
F 5 "1.75" H 7675 5200 50  0001 L CNN "Height"
F 6 "771-74HC4050D" H 7675 5100 50  0001 L CNN "Mouser Part Number"
F 7 "https://www.mouser.com/Search/Refine.aspx?Keyword=771-74HC4050D" H 7675 5000 50  0001 L CNN "Mouser Price/Stock"
F 8 "Nexperia" H 7675 4900 50  0001 L CNN "Manufacturer_Name"
F 9 "74HC4050D" H 7675 4800 50  0001 L CNN "Manufacturer_Part_Number"
	1    6725 5400
	1    0    0    -1  
$EndComp
Wire Wire Line
	6675 5400 6675 5150
Text Label 6325 5800 0    50   ~ 0
SPI2
$Comp
L power:GND #PWR?
U 1 1 5EA3510A
P 6650 6100
AR Path="/5E4D7F26/5EA3510A" Ref="#PWR?"  Part="1" 
AR Path="/5E4D4518/5EA3510A" Ref="#PWR?"  Part="1" 
AR Path="/5E5D5A26/5EA3510A" Ref="#PWR?"  Part="1" 
AR Path="/5E562C99/5EA3510A" Ref="#PWR047"  Part="1" 
F 0 "#PWR047" H 6650 5850 50  0001 C CNN
F 1 "GND" H 6655 5927 50  0000 C CNN
F 2 "" H 6650 6100 50  0001 C CNN
F 3 "" H 6650 6100 50  0001 C CNN
	1    6650 6100
	0    1    1    0   
$EndComp
Wire Wire Line
	6650 6100 6725 6100
$Comp
L power:+3.3V #PWR?
U 1 1 5EA35111
P 6675 5075
AR Path="/5E4D7F26/5EA35111" Ref="#PWR?"  Part="1" 
AR Path="/5E4D4518/5EA35111" Ref="#PWR?"  Part="1" 
AR Path="/5E5D5A26/5EA35111" Ref="#PWR?"  Part="1" 
AR Path="/5E562C99/5EA35111" Ref="#PWR048"  Part="1" 
F 0 "#PWR048" H 6675 4925 50  0001 C CNN
F 1 "+3.3V" H 6690 5248 50  0000 C CNN
F 2 "" H 6675 5075 50  0001 C CNN
F 3 "" H 6675 5075 50  0001 C CNN
	1    6675 5075
	1    0    0    -1  
$EndComp
Wire Wire Line
	6675 5400 6725 5400
Text Label 6325 5700 0    50   ~ 0
SPILV2
Wire Wire Line
	6725 6000 6325 6000
Wire Wire Line
	6725 5800 6325 5800
NoConn ~ 7825 5400
Wire Wire Line
	6300 5500 6725 5500
NoConn ~ 7825 5500
NoConn ~ 7825 5600
$Comp
L Pro6_Print-rescue:0805_100nF,50V,5%-SamacSys_Parts C24
U 1 1 62F79D38
P 7025 5150
F 0 "C24" H 7275 5415 50  0000 C CNN
F 1 "0805_100nF,50V,5%" H 7275 5324 50  0000 C CNN
F 2 "CAPC2012X88N" H 7375 5200 50  0001 L CNN
F 3 "https://componentsearchengine.com/Datasheets/1/C0805C104J5RACTU.pdf" H 7375 5100 50  0001 L CNN
F 4 "Kemet 100nF +/-5% 50 V dc X7R Dielectric SMD Ceramic Multilayer Capacitor 0805" H 7375 5000 50  0001 L CNN "Description"
F 5 "0.88" H 7375 4900 50  0001 L CNN "Height"
F 6 "80-C0805C104J5R" H 7375 4800 50  0001 L CNN "Mouser Part Number"
F 7 "https://www.mouser.com/Search/Refine.aspx?Keyword=80-C0805C104J5R" H 7375 4700 50  0001 L CNN "Mouser Price/Stock"
F 8 "Kemet" H 7375 4600 50  0001 L CNN "Manufacturer_Name"
F 9 "C0805C104J5RACTU" H 7375 4500 50  0001 L CNN "Manufacturer_Part_Number"
	1    7025 5150
	1    0    0    -1  
$EndComp
Wire Wire Line
	7025 5150 6675 5150
Connection ~ 6675 5150
Wire Wire Line
	6675 5150 6675 5075
$Comp
L power:GND #PWR049
U 1 1 62F81E28
P 8050 5225
F 0 "#PWR049" H 8050 4975 50  0001 C CNN
F 1 "GND" H 8055 5052 50  0000 C CNN
F 2 "" H 8050 5225 50  0001 C CNN
F 3 "" H 8050 5225 50  0001 C CNN
	1    8050 5225
	1    0    0    -1  
$EndComp
Wire Wire Line
	7525 5150 8050 5150
Wire Wire Line
	8050 5150 8050 5225
Text Notes 3000 1175 0    197  ~ 39
RFID-Modul
Text Label 5450 3900 2    50   ~ 0
SDA,RX
Text Label 5450 3800 2    50   ~ 0
MISO,TX
Text Label 6700 4400 0    50   ~ 0
RX3.3V
Text Label 5425 3000 2    50   ~ 0
IRQ
Wire Wire Line
	2125 1225 2450 1225
Wire Wire Line
	2450 2500 3150 2500
Wire Wire Line
	2450 2500 2450 1225
Wire Wire Line
	2125 1875 2400 1875
Wire Wire Line
	2400 2800 3150 2800
Wire Wire Line
	2400 1875 2400 2800
$Comp
L power:GND #PWR041
U 1 1 5E6B60AA
P 2275 1975
F 0 "#PWR041" H 2275 1725 50  0001 C CNN
F 1 "GND" H 2280 1802 50  0000 C CNN
F 2 "" H 2275 1975 50  0001 C CNN
F 3 "" H 2275 1975 50  0001 C CNN
	1    2275 1975
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR043
U 1 1 5E6B5277
P 2300 1325
F 0 "#PWR043" H 2300 1075 50  0001 C CNN
F 1 "GND" H 2305 1152 50  0000 C CNN
F 2 "" H 2300 1325 50  0001 C CNN
F 3 "" H 2300 1325 50  0001 C CNN
	1    2300 1325
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR040
U 1 1 5E6AA0F3
P 2275 1775
F 0 "#PWR040" H 2275 1625 50  0001 C CNN
F 1 "+3.3V" H 2290 1948 50  0000 C CNN
F 2 "" H 2275 1775 50  0001 C CNN
F 3 "" H 2275 1775 50  0001 C CNN
	1    2275 1775
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR042
U 1 1 5E6A4062
P 2300 1125
F 0 "#PWR042" H 2300 975 50  0001 C CNN
F 1 "+3.3V" H 2315 1298 50  0000 C CNN
F 2 "" H 2300 1125 50  0001 C CNN
F 3 "" H 2300 1125 50  0001 C CNN
	1    2300 1125
	1    0    0    -1  
$EndComp
Wire Wire Line
	2300 1125 2125 1125
Wire Wire Line
	2125 1775 2275 1775
Wire Wire Line
	2300 1325 2125 1325
Wire Wire Line
	2275 1975 2125 1975
$Comp
L Pro6_Print-rescue:22-28-4033-SamacSys_Parts J7
U 1 1 5E684CC3
P 2125 1975
F 0 "J7" H 2753 1921 50  0000 L CNN
F 1 "22-28-4033" H 2753 1830 50  0000 L CNN
F 2 "HDRV3W66P0X254_1X3_762X249X838P" H 2775 2075 50  0001 L CNN
F 3 "https://componentsearchengine.com/Datasheets/1/22-28-4033.pdf" H 2775 1975 50  0001 L CNN
F 4 "MOLEX - 22-28-4033 - CONNECTOR, HEADER, 3POS, 1ROW, 2.54MM" H 2775 1875 50  0001 L CNN "Description"
F 5 "8.38" H 2775 1775 50  0001 L CNN "Height"
F 6 "538-22-28-4033" H 2775 1675 50  0001 L CNN "Mouser Part Number"
F 7 "https://www.mouser.com/Search/Refine.aspx?Keyword=538-22-28-4033" H 2775 1575 50  0001 L CNN "Mouser Price/Stock"
F 8 "Molex" H 2775 1475 50  0001 L CNN "Manufacturer_Name"
F 9 "22-28-4033" H 2775 1375 50  0001 L CNN "Manufacturer_Part_Number"
	1    2125 1975
	-1   0    0    1   
$EndComp
$Comp
L Pro6_Print-rescue:22-28-4033-SamacSys_Parts J6
U 1 1 5E684CB7
P 2125 1325
F 0 "J6" H 2753 1271 50  0000 L CNN
F 1 "22-28-4033" H 2753 1180 50  0000 L CNN
F 2 "HDRV3W66P0X254_1X3_762X249X838P" H 2775 1425 50  0001 L CNN
F 3 "https://componentsearchengine.com/Datasheets/1/22-28-4033.pdf" H 2775 1325 50  0001 L CNN
F 4 "MOLEX - 22-28-4033 - CONNECTOR, HEADER, 3POS, 1ROW, 2.54MM" H 2775 1225 50  0001 L CNN "Description"
F 5 "8.38" H 2775 1125 50  0001 L CNN "Height"
F 6 "538-22-28-4033" H 2775 1025 50  0001 L CNN "Mouser Part Number"
F 7 "https://www.mouser.com/Search/Refine.aspx?Keyword=538-22-28-4033" H 2775 925 50  0001 L CNN "Mouser Price/Stock"
F 8 "Molex" H 2775 825 50  0001 L CNN "Manufacturer_Name"
F 9 "22-28-4033" H 2775 725 50  0001 L CNN "Manufacturer_Part_Number"
	1    2125 1325
	-1   0    0    1   
$EndComp
Text Label 5450 3600 2    50   ~ 0
SPILV2
Text Label 5450 3700 2    50   ~ 0
SPILV0
Wire Wire Line
	6625 3925 6875 3925
Wire Wire Line
	6875 4025 6725 4025
Text Label 6700 4600 0    50   ~ 0
SPILV6
Text Label 6725 4025 0    50   ~ 0
SPI1
Wire Wire Line
	6725 3825 6875 3825
$Comp
L Pro6_Print-rescue:22-28-4033-SamacSys_Parts J8
U 1 1 5E631965
P 6875 3825
F 0 "J8" H 7503 3771 50  0000 L CNN
F 1 "22-28-4033" H 7503 3680 50  0000 L CNN
F 2 "HDRV3W66P0X254_1X3_762X249X838P" H 7525 3925 50  0001 L CNN
F 3 "https://componentsearchengine.com/Datasheets/1/22-28-4033.pdf" H 7525 3825 50  0001 L CNN
F 4 "MOLEX - 22-28-4033 - CONNECTOR, HEADER, 3POS, 1ROW, 2.54MM" H 7525 3725 50  0001 L CNN "Description"
F 5 "8.38" H 7525 3625 50  0001 L CNN "Height"
F 6 "538-22-28-4033" H 7525 3525 50  0001 L CNN "Mouser Part Number"
F 7 "https://www.mouser.com/Search/Refine.aspx?Keyword=538-22-28-4033" H 7525 3425 50  0001 L CNN "Mouser Price/Stock"
F 8 "Molex" H 7525 3325 50  0001 L CNN "Manufacturer_Name"
F 9 "22-28-4033" H 7525 3225 50  0001 L CNN "Manufacturer_Part_Number"
	1    6875 3825
	1    0    0    -1  
$EndComp
$Comp
L Pro6_Print-rescue:22-28-4033-SamacSys_Parts J9
U 1 1 5E628134
P 6875 4400
F 0 "J9" H 7503 4346 50  0000 L CNN
F 1 "22-28-4033" H 7503 4255 50  0000 L CNN
F 2 "HDRV3W66P0X254_1X3_762X249X838P" H 7525 4500 50  0001 L CNN
F 3 "https://componentsearchengine.com/Datasheets/1/22-28-4033.pdf" H 7525 4400 50  0001 L CNN
F 4 "MOLEX - 22-28-4033 - CONNECTOR, HEADER, 3POS, 1ROW, 2.54MM" H 7525 4300 50  0001 L CNN "Description"
F 5 "8.38" H 7525 4200 50  0001 L CNN "Height"
F 6 "538-22-28-4033" H 7525 4100 50  0001 L CNN "Mouser Part Number"
F 7 "https://www.mouser.com/Search/Refine.aspx?Keyword=538-22-28-4033" H 7525 4000 50  0001 L CNN "Mouser Price/Stock"
F 8 "Molex" H 7525 3900 50  0001 L CNN "Manufacturer_Name"
F 9 "22-28-4033" H 7525 3800 50  0001 L CNN "Manufacturer_Part_Number"
	1    6875 4400
	1    0    0    -1  
$EndComp
Text Label 5325 2200 2    50   ~ 0
VMID
Wire Wire Line
	1400 3950 1400 2600
Connection ~ 1400 3950
Wire Wire Line
	1625 3950 1400 3950
Wire Wire Line
	1400 2600 1625 2600
Wire Wire Line
	1400 4175 1400 3950
$Comp
L power:GND #PWR039
U 1 1 5E699F22
P 1400 4175
F 0 "#PWR039" H 1400 3925 50  0001 C CNN
F 1 "GND" H 1405 4002 50  0000 C CNN
F 2 "" H 1400 4175 50  0001 C CNN
F 3 "" H 1400 4175 50  0001 C CNN
	1    1400 4175
	1    0    0    -1  
$EndComp
Wire Wire Line
	2350 3300 2250 3300
Connection ~ 2350 3300
Wire Wire Line
	2350 3950 2125 3950
Wire Wire Line
	2350 3300 2350 3950
Wire Wire Line
	2350 3200 3150 3200
Connection ~ 2350 3200
Wire Wire Line
	2350 2600 2350 3200
Wire Wire Line
	2125 2600 2350 2600
$Comp
L Pro6_Print-rescue:0805_10pF,16V,5%-SamacSys_Parts C16
U 1 1 5E695390
P 1625 3950
F 0 "C16" H 1875 4215 50  0000 C CNN
F 1 "0805_10pF,16V,5%" H 1875 4124 50  0000 C CNN
F 2 "CAPC2012X70N" H 1975 4000 50  0001 L CNN
F 3 "https://componentsearchengine.com/Datasheets/1/885012007010.pdf" H 1975 3900 50  0001 L CNN
F 4 "Multilayer Ceramic Chip Capacitor WCAP-CSGP Series 0805 10pF NP00805100J016DFCT10000" H 1975 3800 50  0001 L CNN "Description"
F 5 "0.7" H 1975 3700 50  0001 L CNN "Height"
F 6 "710-885012007010" H 1975 3600 50  0001 L CNN "Mouser Part Number"
F 7 "https://www.mouser.com/Search/Refine.aspx?Keyword=710-885012007010" H 1975 3500 50  0001 L CNN "Mouser Price/Stock"
F 8 "Wurth Elektronik" H 1975 3400 50  0001 L CNN "Manufacturer_Name"
F 9 "885012007010" H 1975 3300 50  0001 L CNN "Manufacturer_Part_Number"
	1    1625 3950
	1    0    0    -1  
$EndComp
$Comp
L Pro6_Print-rescue:0805_10pF,16V,5%-SamacSys_Parts C15
U 1 1 5E6949C9
P 1625 2600
F 0 "C15" H 1875 2865 50  0000 C CNN
F 1 "0805_10pF,16V,5%" H 1875 2774 50  0000 C CNN
F 2 "CAPC2012X70N" H 1975 2650 50  0001 L CNN
F 3 "https://componentsearchengine.com/Datasheets/1/885012007010.pdf" H 1975 2550 50  0001 L CNN
F 4 "Multilayer Ceramic Chip Capacitor WCAP-CSGP Series 0805 10pF NP00805100J016DFCT10000" H 1975 2450 50  0001 L CNN "Description"
F 5 "0.7" H 1975 2350 50  0001 L CNN "Height"
F 6 "710-885012007010" H 1975 2250 50  0001 L CNN "Mouser Part Number"
F 7 "https://www.mouser.com/Search/Refine.aspx?Keyword=710-885012007010" H 1975 2150 50  0001 L CNN "Mouser Price/Stock"
F 8 "Wurth Elektronik" H 1975 2050 50  0001 L CNN "Manufacturer_Name"
F 9 "885012007010" H 1975 1950 50  0001 L CNN "Manufacturer_Part_Number"
	1    1625 2600
	1    0    0    -1  
$EndComp
Wire Wire Line
	3150 3300 2350 3300
Wire Wire Line
	2250 3200 2350 3200
$Comp
L Pro6_Print-rescue:LFXTAL014948Bulk-SamacSys_Parts Y1
U 1 1 5E68A09B
P 2250 3300
F 0 "Y1" H 2542 2935 50  0000 C CNN
F 1 "LFXTAL014948Bulk" H 2542 3026 50  0000 C CNN
F 2 "LFXTAL014948Bulk" H 2900 3400 50  0001 L CNN
F 3 "https://componentsearchengine.com/Datasheets/1/LFXTAL014948Bulk.pdf" H 2900 3300 50  0001 L CNN
F 4 "Crystals 27.12MHz Series -10C 60C" H 2900 3200 50  0001 L CNN "Description"
F 5 "4.1" H 2900 3100 50  0001 L CNN "Height"
F 6 "449-LFXTAL014948BULK" H 2900 3000 50  0001 L CNN "Mouser Part Number"
F 7 "https://www.mouser.com/Search/Refine.aspx?Keyword=449-LFXTAL014948BULK" H 2900 2900 50  0001 L CNN "Mouser Price/Stock"
F 8 "IQD" H 2900 2800 50  0001 L CNN "Manufacturer_Name"
F 9 "LFXTAL014948Bulk" H 2900 2700 50  0001 L CNN "Manufacturer_Part_Number"
	1    2250 3300
	-1   0    0    1   
$EndComp
Text Label 6725 3825 0    50   ~ 0
TX3
$Comp
L Pro6_Print-rescue:0805_68nF,50V,10%-SamacSys_Parts C23
U 1 1 5E66BB65
P 6525 825
F 0 "C23" V 6729 953 50  0000 L CNN
F 1 "0805_68nF,50V,10%" V 6820 953 50  0000 L CNN
F 2 "CAPC2012X90N" H 6875 875 50  0001 L CNN
F 3 "https://componentsearchengine.com/Datasheets/1/885012207097.pdf" H 6875 775 50  0001 L CNN
F 4 "Multilayer Ceramic Chip Capacitor WCAP-CSGP Series 0805 68000pF X7R0805683K050DFCT10000" H 6875 675 50  0001 L CNN "Description"
F 5 "0.9" H 6875 575 50  0001 L CNN "Height"
F 6 "710-885012207097" H 6875 475 50  0001 L CNN "Mouser Part Number"
F 7 "https://www.mouser.com/Search/Refine.aspx?Keyword=710-885012207097" H 6875 375 50  0001 L CNN "Mouser Price/Stock"
F 8 "Wurth Elektronik" H 6875 275 50  0001 L CNN "Manufacturer_Name"
F 9 "885012207097" H 6875 175 50  0001 L CNN "Manufacturer_Part_Number"
	1    6525 825 
	0    1    1    0   
$EndComp
Text Label 2775 2700 0    50   ~ 0
RX_RC522
NoConn ~ 2775 3600
NoConn ~ 2775 3700
NoConn ~ 2775 3800
NoConn ~ 2775 3900
Wire Wire Line
	3150 3900 2775 3900
Wire Wire Line
	3150 3800 2775 3800
Wire Wire Line
	3150 3700 2775 3700
Wire Wire Line
	3150 3600 2775 3600
Text Label 2875 2400 0    50   ~ 0
RESET
Wire Wire Line
	3150 2400 2875 2400
NoConn ~ 5425 2500
NoConn ~ 5425 2400
Wire Wire Line
	5150 2500 5425 2500
Wire Wire Line
	5150 2400 5425 2400
Wire Wire Line
	5150 3000 5425 3000
NoConn ~ 5425 3300
NoConn ~ 5425 3200
Wire Wire Line
	5150 3200 5425 3200
Wire Wire Line
	5150 3300 5425 3300
Wire Wire Line
	5450 4500 5450 4675
Connection ~ 5450 4500
Wire Wire Line
	5450 4400 5450 4500
Wire Wire Line
	5150 4500 5450 4500
Connection ~ 5450 4400
Wire Wire Line
	5150 4400 5450 4400
Wire Wire Line
	5450 4300 5450 4400
Connection ~ 5450 4300
Wire Wire Line
	5450 4200 5450 4300
Wire Wire Line
	5150 4300 5450 4300
Connection ~ 5450 4200
Wire Wire Line
	5450 4100 5450 4200
Wire Wire Line
	5150 4100 5450 4100
Wire Wire Line
	5450 4200 5150 4200
$Comp
L power:GND #PWR045
U 1 1 5E5652BF
P 5450 4675
F 0 "#PWR045" H 5450 4425 50  0001 C CNN
F 1 "GND" H 5455 4502 50  0000 C CNN
F 2 "" H 5450 4675 50  0001 C CNN
F 3 "" H 5450 4675 50  0001 C CNN
	1    5450 4675
	1    0    0    -1  
$EndComp
$Comp
L Pro6_Print-rescue:MFRC522-MFRC522 U2
U 1 1 5E562DF8
P 4150 3100
F 0 "U2" H 4150 4767 50  0000 C CNN
F 1 "MFRC522" H 4150 4676 50  0000 C CNN
F 2 "QFN50P500X500X100-33N" H 4150 3100 50  0001 L BNN
F 3 "3.9" H 4150 3100 50  0001 L BNN
F 4 "NXP" H 4150 3100 50  0001 L BNN "Feld4"
F 5 "IPC-7351B" H 4150 3100 50  0001 L BNN "Feld5"
F 6 "1.0 mm" H 4150 3100 50  0001 L BNN "Feld6"
	1    4150 3100
	1    0    0    -1  
$EndComp
Text Notes -25  1625 0    197  ~ 39
UART/SPI
Text Notes 7625 4400 0    197  ~ 39
UART/SPI
Wire Wire Line
	6625 3800 6625 3925
Wire Wire Line
	5150 3800 6625 3800
Wire Wire Line
	6525 3900 6525 4500
Wire Wire Line
	5150 3900 6525 3900
Wire Wire Line
	6525 4500 6875 4500
Wire Wire Line
	6725 3675 6725 3825
Wire Wire Line
	6100 3675 6725 3675
Wire Wire Line
	5575 5500 5575 3700
Wire Wire Line
	5150 3700 5575 3700
Wire Wire Line
	5675 5700 5675 3600
Wire Wire Line
	5150 3600 5675 3600
Wire Wire Line
	5775 4600 5775 5900
Wire Wire Line
	5775 4600 6875 4600
$Comp
L power:GND #PWR046
U 1 1 5F8B4039
P 6175 825
F 0 "#PWR046" H 6175 575 50  0001 C CNN
F 1 "GND" H 6180 652 50  0000 C CNN
F 2 "" H 6175 825 50  0001 C CNN
F 3 "" H 6175 825 50  0001 C CNN
	1    6175 825 
	1    0    0    -1  
$EndComp
Wire Wire Line
	6175 825  6175 750 
Wire Wire Line
	6175 750  6300 750 
Wire Wire Line
	6525 750  6525 825 
Wire Wire Line
	2650 2700 3150 2700
Text Label 900  5925 0    50   ~ 0
SPI1
Text Label 900  6025 0    50   ~ 0
SPILV0
Text Label 6300 5500 0    50   ~ 0
RX3.3V
Text Label 6325 6000 0    50   ~ 0
SPI0
Text Label 6300 5600 0    50   ~ 0
RX3
Text Label 6325 5900 0    50   ~ 0
SPILV0
Text Label 5875 5700 0    50   ~ 0
SPILV2
Text Label 5850 5900 0    50   ~ 0
SPILV6
Text Label 5875 5500 0    50   ~ 0
SPILV0
Wire Wire Line
	6325 5900 6725 5900
Wire Wire Line
	6325 5700 6725 5700
Wire Wire Line
	5575 5500 5875 5500
Wire Wire Line
	5675 5700 5875 5700
Wire Wire Line
	5775 5900 5850 5900
Wire Wire Line
	8250 6100 7825 6100
Wire Wire Line
	8250 6000 7825 6000
Text Label 8250 6100 2    50   ~ 0
SPILV6
Text Label 8250 6000 2    50   ~ 0
SPI6
Text Label 900  6225 0    50   ~ 0
SPILV6
Text Label -3300 8200 2    50   ~ 0
SPI7
Wire Wire Line
	-3750 8200 -3300 8200
Entry Wire Line
	-3850 8100 -3750 8200
NoConn ~ 7825 5800
NoConn ~ 7825 5900
$Comp
L Pro6_Print-rescue:0805_100nF,50V,5%-SamacSys_Parts C17
U 1 1 5E7A473D
P 2725 5600
F 0 "C17" H 2975 5865 50  0000 C CNN
F 1 "0805_100nF,50V,5%" H 2975 5774 50  0000 C CNN
F 2 "CAPC2012X88N" H 3075 5650 50  0001 L CNN
F 3 "https://componentsearchengine.com/Datasheets/1/C0805C104J5RACTU.pdf" H 3075 5550 50  0001 L CNN
F 4 "Kemet 100nF +/-5% 50 V dc X7R Dielectric SMD Ceramic Multilayer Capacitor 0805" H 3075 5450 50  0001 L CNN "Description"
F 5 "0.88" H 3075 5350 50  0001 L CNN "Height"
F 6 "80-C0805C104J5R" H 3075 5250 50  0001 L CNN "Mouser Part Number"
F 7 "https://www.mouser.com/Search/Refine.aspx?Keyword=80-C0805C104J5R" H 3075 5150 50  0001 L CNN "Mouser Price/Stock"
F 8 "Kemet" H 3075 5050 50  0001 L CNN "Manufacturer_Name"
F 9 "C0805C104J5RACTU" H 3075 4950 50  0001 L CNN "Manufacturer_Part_Number"
	1    2725 5600
	0    1    1    0   
$EndComp
Wire Wire Line
	1000 5525 1000 5275
Wire Wire Line
	1000 5275 2725 5275
Wire Wire Line
	2725 5275 2725 5600
Connection ~ 1000 5525
Wire Wire Line
	1000 5525 775  5525
Wire Wire Line
	2725 6100 2725 6500
Wire Wire Line
	2725 6500 625  6500
Wire Wire Line
	625  6500 625  5725
Wire Wire Line
	625  5725 775  5725
Connection ~ 775  5725
Wire Wire Line
	775  5725 1125 5725
Text Notes 11050 2575 0    197  ~ 39
external antenna
Wire Wire Line
	8775 1725 9000 1725
Wire Wire Line
	7450 1425 7450 1625
Wire Wire Line
	7375 1425 7450 1425
Wire Wire Line
	6675 1725 8775 1725
Wire Wire Line
	6675 2175 6675 1725
Wire Wire Line
	6775 2175 6675 2175
Wire Wire Line
	6575 2275 6775 2275
Wire Wire Line
	6575 2275 6575 2700
Connection ~ 9750 3125
Wire Wire Line
	10275 1725 10275 2300
$Comp
L Pro6_Print-rescue:0805_68nF,50V,10%-SamacSys_Parts C25
U 1 1 5E66335D
P 7525 1425
F 0 "C25" H 7775 1690 50  0000 C CNN
F 1 "0805_68nF,50V,10%" H 7775 1599 50  0000 C CNN
F 2 "CAPC2012X90N" H 7875 1475 50  0001 L CNN
F 3 "https://componentsearchengine.com/Datasheets/1/885012207097.pdf" H 7875 1375 50  0001 L CNN
F 4 "Multilayer Ceramic Chip Capacitor WCAP-CSGP Series 0805 68000pF X7R0805683K050DFCT10000" H 7875 1275 50  0001 L CNN "Description"
F 5 "0.9" H 7875 1175 50  0001 L CNN "Height"
F 6 "710-885012207097" H 7875 1075 50  0001 L CNN "Mouser Part Number"
F 7 "https://www.mouser.com/Search/Refine.aspx?Keyword=710-885012207097" H 7875 975 50  0001 L CNN "Mouser Price/Stock"
F 8 "Wurth Elektronik" H 7875 875 50  0001 L CNN "Manufacturer_Name"
F 9 "885012207097" H 7875 775 50  0001 L CNN "Manufacturer_Part_Number"
	1    7525 1425
	1    0    0    -1  
$EndComp
$Comp
L Pro6_Print-rescue:0805_560Ohm,150V,1%,125mW-SamacSys_Parts R27
U 1 1 5E655EDF
P 8300 1425
F 0 "R27" H 8650 1650 50  0000 C CNN
F 1 "0805_560Ohm,150V,1%,125mW" H 8650 1559 50  0000 C CNN
F 2 "RESC2012X50N" H 8850 1475 50  0001 L CNN
F 3 "https://componentsearchengine.com/Datasheets/1/CRCW0805560RFKEA.pdf" H 8850 1375 50  0001 L CNN
F 4 "CRCW0805 Resistor T/R 0.125W,1%,560R Vishay CRCW Series Thick Film Surface Mount Resistor 805 Case 560?? ??1% 0.125W ??100ppm/??C" H 8850 1275 50  0001 L CNN "Description"
F 5 "0.5" H 8850 1175 50  0001 L CNN "Height"
F 6 "71-CRCW0805-560-E3" H 8850 1075 50  0001 L CNN "Mouser Part Number"
F 7 "https://www.mouser.com/Search/Refine.aspx?Keyword=71-CRCW0805-560-E3" H 8850 975 50  0001 L CNN "Mouser Price/Stock"
F 8 "Vishay" H 8850 875 50  0001 L CNN "Manufacturer_Name"
F 9 "CRCW0805560RFKEA" H 8850 775 50  0001 L CNN "Manufacturer_Part_Number"
	1    8300 1425
	1    0    0    -1  
$EndComp
Text Label 6675 1625 0    50   ~ 0
RX_RC522
$Comp
L Pro6_Print-rescue:0805_820Ohm,150V,1%,125mW-SamacSys_Parts R26
U 1 1 5E641D5C
P 6675 1425
F 0 "R26" H 7025 1650 50  0000 C CNN
F 1 "0805_820Ohm,150V,1%,125mW" H 7025 1559 50  0000 C CNN
F 2 "RESC2012X60N" H 7225 1475 50  0001 L CNN
F 3 "https://componentsearchengine.com/Datasheets/1/CR0805-FX-8200ELF.pdf" H 7225 1375 50  0001 L CNN
F 4 "Thick Film Resistors - SMD 820ohm 1%" H 7225 1275 50  0001 L CNN "Description"
F 5 "0.6" H 7225 1175 50  0001 L CNN "Height"
F 6 "652-CR0805FX-8200ELF" H 7225 1075 50  0001 L CNN "Mouser Part Number"
F 7 "https://www.mouser.com/Search/Refine.aspx?Keyword=652-CR0805FX-8200ELF" H 7225 975 50  0001 L CNN "Mouser Price/Stock"
F 8 "Bourns" H 7225 875 50  0001 L CNN "Manufacturer_Name"
F 9 "CR0805-FX-8200ELF" H 7225 775 50  0001 L CNN "Manufacturer_Part_Number"
	1    6675 1425
	1    0    0    -1  
$EndComp
Connection ~ 9750 1725
Wire Wire Line
	9750 1725 10275 1725
Wire Wire Line
	9750 2425 9750 2225
Connection ~ 9750 2425
Wire Wire Line
	9750 2625 9750 2425
Connection ~ 8775 3125
Connection ~ 8775 1725
Wire Wire Line
	8775 2425 9750 2425
Wire Wire Line
	9500 1725 9750 1725
Wire Wire Line
	9500 3125 9750 3125
Wire Wire Line
	9000 3125 8775 3125
Wire Wire Line
	8775 2425 8775 2625
Connection ~ 8775 2425
Wire Wire Line
	8475 2425 8775 2425
Wire Wire Line
	8475 2475 8475 2425
$Comp
L power:GND #PWR050
U 1 1 5E5E3021
P 8475 2475
F 0 "#PWR050" H 8475 2225 50  0001 C CNN
F 1 "GND" H 8480 2302 50  0000 C CNN
F 2 "" H 8475 2475 50  0001 C CNN
F 3 "" H 8475 2475 50  0001 C CNN
	1    8475 2475
	1    0    0    -1  
$EndComp
Wire Wire Line
	8775 2225 8775 2425
Wire Wire Line
	6775 3125 8775 3125
Wire Wire Line
	6775 2900 6775 3125
$Comp
L Pro6_Print-rescue:0805_120pF,50V,5%-SamacSys_Parts C30
U 1 1 5E5A94DD
P 9750 2225
F 0 "C30" H 10000 2490 50  0000 C CNN
F 1 "0805_120pF,50V,5%" H 10000 2399 50  0000 C CNN
F 2 "CAPC2012X70N" H 10100 2275 50  0001 L CNN
F 3 "https://componentsearchengine.com/Datasheets/1/GRM2162C1H121JA01D.pdf" H 10100 2175 50  0001 L CNN
F 4 "Multilayer Ceramic Capacitors MLCC - SMD/SMT 0805 120pF 50volts CH 5%" H 10100 2075 50  0001 L CNN "Description"
F 5 "0.7" H 10100 1975 50  0001 L CNN "Height"
F 6 "81-GRM212C1H121JA01D" H 10100 1875 50  0001 L CNN "Mouser Part Number"
F 7 "https://www.mouser.com/Search/Refine.aspx?Keyword=81-GRM212C1H121JA01D" H 10100 1775 50  0001 L CNN "Mouser Price/Stock"
F 8 "Murata Electronics" H 10100 1675 50  0001 L CNN "Manufacturer_Name"
F 9 "GRM2162C1H121JA01D" H 10100 1575 50  0001 L CNN "Manufacturer_Part_Number"
	1    9750 2225
	0    1    -1   0   
$EndComp
$Comp
L Pro6_Print-rescue:0805_120pF,50V,5%-SamacSys_Parts C31
U 1 1 5E5A6F9E
P 9750 2625
F 0 "C31" H 10000 2890 50  0000 C CNN
F 1 "0805_120pF,50V,5%" H 10000 2799 50  0000 C CNN
F 2 "CAPC2012X70N" H 10100 2675 50  0001 L CNN
F 3 "https://componentsearchengine.com/Datasheets/1/GRM2162C1H121JA01D.pdf" H 10100 2575 50  0001 L CNN
F 4 "Multilayer Ceramic Capacitors MLCC - SMD/SMT 0805 120pF 50volts CH 5%" H 10100 2475 50  0001 L CNN "Description"
F 5 "0.7" H 10100 2375 50  0001 L CNN "Height"
F 6 "81-GRM212C1H121JA01D" H 10100 2275 50  0001 L CNN "Mouser Part Number"
F 7 "https://www.mouser.com/Search/Refine.aspx?Keyword=81-GRM212C1H121JA01D" H 10100 2175 50  0001 L CNN "Mouser Price/Stock"
F 8 "Murata Electronics" H 10100 2075 50  0001 L CNN "Manufacturer_Name"
F 9 "GRM2162C1H121JA01D" H 10100 1975 50  0001 L CNN "Manufacturer_Part_Number"
	1    9750 2625
	0    1    1    0   
$EndComp
$Comp
L Pro6_Print-rescue:0805_47pF,50V,5%-SamacSys_Parts C29
U 1 1 5E5A4F82
P 9500 3125
F 0 "C29" H 9750 2860 50  0000 C CNN
F 1 "0805_47pF,50V,5%" H 9750 2951 50  0000 C CNN
F 2 "CAPC2013X88N" H 9850 3175 50  0001 L CNN
F 3 "https://componentsearchengine.com/Datasheets/1/C0805C470J5GACTU.pdf" H 9850 3075 50  0001 L CNN
F 4 "Kemet 0805 47pF Ceramic Multilayer Capacitor, 50V dc, 125C, C0G Dielectric, +/-5% SMD" H 9850 2975 50  0001 L CNN "Description"
F 5 "80-C0805C470J5G" H 9850 2775 50  0001 L CNN "Mouser Part Number"
F 6 "https://www.mouser.com/Search/Refine.aspx?Keyword=80-C0805C470J5G" H 9850 2675 50  0001 L CNN "Mouser Price/Stock"
F 7 "Kemet" H 9850 2575 50  0001 L CNN "Manufacturer_Name"
F 8 "C0805C470J5GACTU" H 9850 2475 50  0001 L CNN "Manufacturer_Part_Number"
	1    9500 3125
	-1   0    0    -1  
$EndComp
$Comp
L Pro6_Print-rescue:0805_47pF,50V,5%-SamacSys_Parts C28
U 1 1 5E5A2B13
P 9500 1725
F 0 "C28" H 9750 1460 50  0000 C CNN
F 1 "0805_47pF,50V,5%" H 9750 1551 50  0000 C CNN
F 2 "CAPC2013X88N" H 9850 1775 50  0001 L CNN
F 3 "https://componentsearchengine.com/Datasheets/1/C0805C470J5GACTU.pdf" H 9850 1675 50  0001 L CNN
F 4 "Kemet 0805 47pF Ceramic Multilayer Capacitor, 50V dc, 125C, C0G Dielectric, +/-5% SMD" H 9850 1575 50  0001 L CNN "Description"
F 5 "80-C0805C470J5G" H 9850 1375 50  0001 L CNN "Mouser Part Number"
F 6 "https://www.mouser.com/Search/Refine.aspx?Keyword=80-C0805C470J5G" H 9850 1275 50  0001 L CNN "Mouser Price/Stock"
F 7 "Kemet" H 9850 1175 50  0001 L CNN "Manufacturer_Name"
F 8 "C0805C470J5GACTU" H 9850 1075 50  0001 L CNN "Manufacturer_Part_Number"
	1    9500 1725
	-1   0    0    1   
$EndComp
$Comp
L Pro6_Print-rescue:0805_47pF,50V,5%-SamacSys_Parts C27
U 1 1 5E59EDC3
P 8775 2625
F 0 "C27" V 8979 2497 50  0000 R CNN
F 1 "0805_47pF,50V,5%" V 9070 2497 50  0000 R CNN
F 2 "CAPC2013X88N" H 9125 2675 50  0001 L CNN
F 3 "https://componentsearchengine.com/Datasheets/1/C0805C470J5GACTU.pdf" H 9125 2575 50  0001 L CNN
F 4 "Kemet 0805 47pF Ceramic Multilayer Capacitor, 50V dc, 125C, C0G Dielectric, +/-5% SMD" H 9125 2475 50  0001 L CNN "Description"
F 5 "80-C0805C470J5G" H 9125 2275 50  0001 L CNN "Mouser Part Number"
F 6 "https://www.mouser.com/Search/Refine.aspx?Keyword=80-C0805C470J5G" H 9125 2175 50  0001 L CNN "Mouser Price/Stock"
F 7 "Kemet" H 9125 2075 50  0001 L CNN "Manufacturer_Name"
F 8 "C0805C470J5GACTU" H 9125 1975 50  0001 L CNN "Manufacturer_Part_Number"
	1    8775 2625
	0    1    1    0   
$EndComp
$Comp
L Pro6_Print-rescue:0805_47pF,50V,5%-SamacSys_Parts C26
U 1 1 5E599A55
P 8775 2225
F 0 "C26" V 8979 2353 50  0000 L CNN
F 1 "0805_47pF,50V,5%" V 9070 2353 50  0000 L CNN
F 2 "CAPC2013X88N" H 9125 2275 50  0001 L CNN
F 3 "https://componentsearchengine.com/Datasheets/1/C0805C470J5GACTU.pdf" H 9125 2175 50  0001 L CNN
F 4 "Kemet 0805 47pF Ceramic Multilayer Capacitor, 50V dc, 125C, C0G Dielectric, +/-5% SMD" H 9125 2075 50  0001 L CNN "Description"
F 5 "80-C0805C470J5G" H 9125 1875 50  0001 L CNN "Mouser Part Number"
F 6 "https://www.mouser.com/Search/Refine.aspx?Keyword=80-C0805C470J5G" H 9125 1775 50  0001 L CNN "Mouser Price/Stock"
F 7 "Kemet" H 9125 1675 50  0001 L CNN "Manufacturer_Name"
F 8 "C0805C470J5GACTU" H 9125 1575 50  0001 L CNN "Manufacturer_Part_Number"
	1    8775 2225
	0    -1   -1   0   
$EndComp
$Comp
L Pro6_Print-rescue:0805_2.2uH,XYV,20%-SamacSys_Parts L2
U 1 1 5E582222
P 6775 2800
F 0 "L2" H 7403 2796 50  0000 L CNN
F 1 "0805_2.2uH,XYV,20%" H 7403 2705 50  0000 L CNN
F 2 "INDC2012X105N" H 7425 2900 50  0001 L CNN
F 3 "https://componentsearchengine.com/Datasheets/1/MLZ2012A2R2WT000.pdf" H 7425 2800 50  0001 L CNN
F 4 "Fixed Inductors" H 7425 2700 50  0001 L CNN "Description"
F 5 "1.05" H 7425 2600 50  0001 L CNN "Height"
F 6 "810-MLZ2012A2R2WT000" H 7425 2500 50  0001 L CNN "Mouser Part Number"
F 7 "https://www.mouser.com/Search/Refine.aspx?Keyword=810-MLZ2012A2R2WT000" H 7425 2400 50  0001 L CNN "Mouser Price/Stock"
F 8 "TDK" H 7425 2300 50  0001 L CNN "Manufacturer_Name"
F 9 "MLZ2012A2R2WT000" H 7425 2200 50  0001 L CNN "Manufacturer_Part_Number"
	1    6775 2800
	1    0    0    -1  
$EndComp
$Comp
L Pro6_Print-rescue:0805_2.2uH,XYV,20%-SamacSys_Parts L1
U 1 1 5E57DB09
P 6775 2175
F 0 "L1" H 7403 2171 50  0000 L CNN
F 1 "0805_2.2uH,XYV,20%" H 7403 2080 50  0000 L CNN
F 2 "INDC2012X105N" H 7425 2275 50  0001 L CNN
F 3 "https://componentsearchengine.com/Datasheets/1/MLZ2012A2R2WT000.pdf" H 7425 2175 50  0001 L CNN
F 4 "Fixed Inductors" H 7425 2075 50  0001 L CNN "Description"
F 5 "1.05" H 7425 1975 50  0001 L CNN "Height"
F 6 "810-MLZ2012A2R2WT000" H 7425 1875 50  0001 L CNN "Mouser Part Number"
F 7 "https://www.mouser.com/Search/Refine.aspx?Keyword=810-MLZ2012A2R2WT000" H 7425 1775 50  0001 L CNN "Mouser Price/Stock"
F 8 "TDK" H 7425 1675 50  0001 L CNN "Manufacturer_Name"
F 9 "MLZ2012A2R2WT000" H 7425 1575 50  0001 L CNN "Manufacturer_Part_Number"
	1    6775 2175
	1    0    0    -1  
$EndComp
Text Notes 7350 1075 0    197  ~ 39
Adjust-Block for antenna
Wire Wire Line
	6675 1625 7450 1625
Wire Wire Line
	8775 3550 8775 3125
$Comp
L Pro6_Print-rescue:5-1814832-1-dk_Coaxial-Connectors-RF J10
U 1 1 5EA8CD88
P 10725 2500
F 0 "J10" V 10750 2588 60  0000 L CNN
F 1 "5-1814832-1" V 10856 2588 60  0000 L CNN
F 2 "digikey-footprints:RF_SMA_Vertical_5-1814832-1" H 10925 2700 60  0001 L CNN
F 3 "https://www.te.com/commerce/DocumentDelivery/DDEController?Action=srchrtrv&DocNm=1814832&DocType=Customer+Drawing&DocLang=English" H 10925 2800 60  0001 L CNN
F 4 "A97594-ND" H 10925 2900 60  0001 L CNN "Digi-Key_PN"
F 5 "5-1814832-1" H 10925 3000 60  0001 L CNN "MPN"
F 6 "Connectors, Interconnects" H 10925 3100 60  0001 L CNN "Category"
F 7 "Coaxial Connectors (RF)" H 10925 3200 60  0001 L CNN "Family"
F 8 "https://www.te.com/commerce/DocumentDelivery/DDEController?Action=srchrtrv&DocNm=1814832&DocType=Customer+Drawing&DocLang=English" H 10925 3300 60  0001 L CNN "DK_Datasheet_Link"
F 9 "/product-detail/en/te-connectivity-amp-connectors/5-1814832-1/A97594-ND/1755982" H 10925 3400 60  0001 L CNN "DK_Detail_Page"
F 10 "CONN SMA JACK STR 50 OHM PCB" H 10925 3500 60  0001 L CNN "Description"
F 11 "TE Connectivity AMP Connectors" H 10925 3600 60  0001 L CNN "Manufacturer"
F 12 "Active" H 10925 3700 60  0001 L CNN "Status"
	1    10725 2500
	0    -1   -1   0   
$EndComp
Wire Wire Line
	10925 3125 10925 2500
Wire Wire Line
	9750 3125 10925 3125
Wire Wire Line
	10275 2300 10725 2300
Wire Wire Line
	7450 1425 7525 1425
Connection ~ 7450 1425
Wire Wire Line
	8025 1425 8300 1425
Wire Wire Line
	9000 1425 11025 1425
Wire Wire Line
	11025 1425 11025 3550
Wire Wire Line
	11025 3550 8775 3550
Text Notes 6600 3475 0    50   ~ 0
UART0 (TMC - uC) = UART_TXD\nUART1 (TMC - uC) = UART_RXD
Text Label 6550 3375 2    50   ~ 0
TX0
Text Label 6550 3475 2    50   ~ 0
TX1
Entry Wire Line
	6000 3375 6100 3475
Entry Wire Line
	6000 3275 6100 3375
Wire Wire Line
	6100 3375 6550 3375
Wire Wire Line
	6100 3475 6550 3475
Text Label 6550 3575 2    50   ~ 0
TX2
Entry Wire Line
	6000 3475 6100 3575
Text HLabel 5985 3275 0    50   Output ~ 0
TX[0..3]
Wire Bus Line
	6000 3275 5975 3275
Wire Wire Line
	6700 4400 6875 4400
Wire Wire Line
	9275 3900 9725 3900
Wire Bus Line
	9175 4000 9150 4000
Entry Wire Line
	9175 3900 9275 4000
Text Label 9725 4000 2    50   ~ 0
RX3
Text HLabel 9160 4000 0    50   Output ~ 0
RX[0..3]
Entry Wire Line
	9175 3800 9275 3900
Text Label 9725 3900 2    50   ~ 0
RX2
Wire Wire Line
	9275 3800 9725 3800
Text Label 9175 3900 1    50   ~ 0
RX[0..3]
Entry Wire Line
	9175 3700 9275 3800
Text Label 9725 3800 2    50   ~ 0
RX1
Text Notes 9775 3800 0    50   ~ 0
UART0 (TMC - uC) = UART_TXD\nUART1 (TMC - uC) = UART_RXD
Wire Wire Line
	9925 4000 9925 4775
Wire Wire Line
	9925 4775 6200 4775
Wire Wire Line
	6200 4775 6200 5600
Wire Wire Line
	6200 5600 6725 5600
Wire Wire Line
	9275 4000 9925 4000
Wire Wire Line
	6525 1325 6525 1425
Wire Wire Line
	5150 2700 6575 2700
Wire Wire Line
	5150 2800 6775 2800
Wire Wire Line
	6525 2200 6525 1425
Connection ~ 6525 1425
Wire Wire Line
	6525 1425 6675 1425
Wire Wire Line
	5150 2200 6525 2200
Wire Wire Line
	5150 2100 5175 2100
Wire Wire Line
	5150 2000 5175 2000
Wire Wire Line
	5150 1900 5175 1900
Wire Wire Line
	5150 1800 5175 1800
Wire Wire Line
	5150 1700 5175 1700
$Comp
L power:+3.3V #PWR044
U 1 1 5E5645A0
P 5225 925
F 0 "#PWR044" H 5225 775 50  0001 C CNN
F 1 "+3.3V" H 5240 1098 50  0000 C CNN
F 2 "" H 5225 925 50  0001 C CNN
F 3 "" H 5225 925 50  0001 C CNN
	1    5225 925 
	1    0    0    -1  
$EndComp
Wire Wire Line
	5175 2100 5175 2075
Connection ~ 5175 2000
Wire Wire Line
	5175 2000 5175 1900
Connection ~ 5175 1900
Wire Wire Line
	5175 1900 5175 1825
Connection ~ 5175 1800
Wire Wire Line
	5175 1800 5175 1700
Wire Wire Line
	5225 925  5225 1075
Connection ~ 6300 750 
Wire Wire Line
	6300 750  6525 750 
Wire Wire Line
	6300 750  6300 1075
Wire Wire Line
	6300 2075 5975 2075
Wire Wire Line
	5975 1825 6300 1825
Connection ~ 6300 1825
Wire Wire Line
	6300 1825 6300 2075
Wire Wire Line
	5975 1575 6300 1575
Connection ~ 6300 1575
Wire Wire Line
	6300 1575 6300 1825
Wire Wire Line
	6300 1325 5975 1325
Connection ~ 6300 1325
Wire Wire Line
	6300 1325 6300 1575
Wire Wire Line
	5975 1075 6300 1075
Connection ~ 6300 1075
Wire Wire Line
	6300 1075 6300 1325
Wire Wire Line
	5225 1075 5475 1075
Wire Wire Line
	5175 1700 5175 1575
Wire Wire Line
	5175 1075 5225 1075
Connection ~ 5175 1700
Connection ~ 5225 1075
Wire Wire Line
	5175 1325 5475 1325
Connection ~ 5175 1325
Wire Wire Line
	5175 1325 5175 1075
Wire Wire Line
	5475 1575 5175 1575
Connection ~ 5175 1575
Wire Wire Line
	5175 1575 5175 1325
Wire Wire Line
	5475 1825 5175 1825
Connection ~ 5175 1825
Wire Wire Line
	5175 1825 5175 1800
Wire Wire Line
	5475 2075 5175 2075
Connection ~ 5175 2075
Wire Wire Line
	5175 2075 5175 2000
Wire Notes Line
	13925 1600 13925 2975
Wire Notes Line
	13925 2975 10275 2975
Wire Notes Line
	10275 2975 10275 1600
Wire Notes Line
	10200 1600 13925 1600
$Comp
L Pro6_Print-rescue:0805_100nF,50V,5%-SamacSys_Parts C18
U 1 1 5EB7FB2C
P 5475 1075
F 0 "C18" H 5725 1340 50  0000 C CNN
F 1 "0805_100nF,50V,5%" H 5725 1249 50  0000 C CNN
F 2 "CAPC2012X88N" H 5825 1125 50  0001 L CNN
F 3 "https://componentsearchengine.com/Datasheets/1/C0805C104J5RACTU.pdf" H 5825 1025 50  0001 L CNN
F 4 "Kemet 100nF +/-5% 50 V dc X7R Dielectric SMD Ceramic Multilayer Capacitor 0805" H 5825 925 50  0001 L CNN "Description"
F 5 "0.88" H 5825 825 50  0001 L CNN "Height"
F 6 "80-C0805C104J5R" H 5825 725 50  0001 L CNN "Mouser Part Number"
F 7 "https://www.mouser.com/Search/Refine.aspx?Keyword=80-C0805C104J5R" H 5825 625 50  0001 L CNN "Mouser Price/Stock"
F 8 "Kemet" H 5825 525 50  0001 L CNN "Manufacturer_Name"
F 9 "C0805C104J5RACTU" H 5825 425 50  0001 L CNN "Manufacturer_Part_Number"
	1    5475 1075
	1    0    0    -1  
$EndComp
$Comp
L Pro6_Print-rescue:0805_100nF,50V,5%-SamacSys_Parts C19
U 1 1 5EB89C9F
P 5475 1325
F 0 "C19" H 5725 1590 50  0000 C CNN
F 1 "0805_100nF,50V,5%" H 5725 1499 50  0000 C CNN
F 2 "CAPC2012X88N" H 5825 1375 50  0001 L CNN
F 3 "https://componentsearchengine.com/Datasheets/1/C0805C104J5RACTU.pdf" H 5825 1275 50  0001 L CNN
F 4 "Kemet 100nF +/-5% 50 V dc X7R Dielectric SMD Ceramic Multilayer Capacitor 0805" H 5825 1175 50  0001 L CNN "Description"
F 5 "0.88" H 5825 1075 50  0001 L CNN "Height"
F 6 "80-C0805C104J5R" H 5825 975 50  0001 L CNN "Mouser Part Number"
F 7 "https://www.mouser.com/Search/Refine.aspx?Keyword=80-C0805C104J5R" H 5825 875 50  0001 L CNN "Mouser Price/Stock"
F 8 "Kemet" H 5825 775 50  0001 L CNN "Manufacturer_Name"
F 9 "C0805C104J5RACTU" H 5825 675 50  0001 L CNN "Manufacturer_Part_Number"
	1    5475 1325
	1    0    0    -1  
$EndComp
$Comp
L Pro6_Print-rescue:0805_100nF,50V,5%-SamacSys_Parts C20
U 1 1 5EB93E49
P 5475 1575
F 0 "C20" H 5725 1840 50  0000 C CNN
F 1 "0805_100nF,50V,5%" H 5725 1749 50  0000 C CNN
F 2 "CAPC2012X88N" H 5825 1625 50  0001 L CNN
F 3 "https://componentsearchengine.com/Datasheets/1/C0805C104J5RACTU.pdf" H 5825 1525 50  0001 L CNN
F 4 "Kemet 100nF +/-5% 50 V dc X7R Dielectric SMD Ceramic Multilayer Capacitor 0805" H 5825 1425 50  0001 L CNN "Description"
F 5 "0.88" H 5825 1325 50  0001 L CNN "Height"
F 6 "80-C0805C104J5R" H 5825 1225 50  0001 L CNN "Mouser Part Number"
F 7 "https://www.mouser.com/Search/Refine.aspx?Keyword=80-C0805C104J5R" H 5825 1125 50  0001 L CNN "Mouser Price/Stock"
F 8 "Kemet" H 5825 1025 50  0001 L CNN "Manufacturer_Name"
F 9 "C0805C104J5RACTU" H 5825 925 50  0001 L CNN "Manufacturer_Part_Number"
	1    5475 1575
	1    0    0    -1  
$EndComp
$Comp
L Pro6_Print-rescue:0805_100nF,50V,5%-SamacSys_Parts C21
U 1 1 5EB9DEA9
P 5475 1825
F 0 "C21" H 5725 2090 50  0000 C CNN
F 1 "0805_100nF,50V,5%" H 5725 1999 50  0000 C CNN
F 2 "CAPC2012X88N" H 5825 1875 50  0001 L CNN
F 3 "https://componentsearchengine.com/Datasheets/1/C0805C104J5RACTU.pdf" H 5825 1775 50  0001 L CNN
F 4 "Kemet 100nF +/-5% 50 V dc X7R Dielectric SMD Ceramic Multilayer Capacitor 0805" H 5825 1675 50  0001 L CNN "Description"
F 5 "0.88" H 5825 1575 50  0001 L CNN "Height"
F 6 "80-C0805C104J5R" H 5825 1475 50  0001 L CNN "Mouser Part Number"
F 7 "https://www.mouser.com/Search/Refine.aspx?Keyword=80-C0805C104J5R" H 5825 1375 50  0001 L CNN "Mouser Price/Stock"
F 8 "Kemet" H 5825 1275 50  0001 L CNN "Manufacturer_Name"
F 9 "C0805C104J5RACTU" H 5825 1175 50  0001 L CNN "Manufacturer_Part_Number"
	1    5475 1825
	1    0    0    -1  
$EndComp
$Comp
L Pro6_Print-rescue:0805_100nF,50V,5%-SamacSys_Parts C22
U 1 1 5EBA7EA6
P 5475 2075
F 0 "C22" H 5725 2340 50  0000 C CNN
F 1 "0805_100nF,50V,5%" H 5725 2249 50  0000 C CNN
F 2 "CAPC2012X88N" H 5825 2125 50  0001 L CNN
F 3 "https://componentsearchengine.com/Datasheets/1/C0805C104J5RACTU.pdf" H 5825 2025 50  0001 L CNN
F 4 "Kemet 100nF +/-5% 50 V dc X7R Dielectric SMD Ceramic Multilayer Capacitor 0805" H 5825 1925 50  0001 L CNN "Description"
F 5 "0.88" H 5825 1825 50  0001 L CNN "Height"
F 6 "80-C0805C104J5R" H 5825 1725 50  0001 L CNN "Mouser Part Number"
F 7 "https://www.mouser.com/Search/Refine.aspx?Keyword=80-C0805C104J5R" H 5825 1625 50  0001 L CNN "Mouser Price/Stock"
F 8 "Kemet" H 5825 1525 50  0001 L CNN "Manufacturer_Name"
F 9 "C0805C104J5RACTU" H 5825 1425 50  0001 L CNN "Manufacturer_Part_Number"
	1    5475 2075
	1    0    0    -1  
$EndComp
Wire Bus Line
	9175 3600 9175 4000
Wire Bus Line
	6000 3275 6000 3675
Wire Bus Line
	-3850 7400 -3850 8200
$EndSCHEMATC