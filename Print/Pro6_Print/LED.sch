EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 10 10
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Wire Wire Line
	750  4975 1075 4975
Wire Wire Line
	3350 4975 3000 4975
Wire Wire Line
	5700 5000 5350 5000
Text Label 750  4975 0    50   ~ 0
LED0
Text Label 3000 4975 0    50   ~ 0
LED1
Text Label 5350 5000 0    50   ~ 0
LED2
Text Label 7675 5000 0    50   ~ 0
LED3
Text Label 1625 2550 2    50   ~ 0
LED0
Entry Wire Line
	1150 2550 1050 2450
Entry Wire Line
	1150 2650 1050 2550
Entry Wire Line
	1150 2750 1050 2650
Entry Wire Line
	1150 2850 1050 2750
Text HLabel 1185 2250 0    50   Output ~ 0
LED[0..3]
Text Label 1185 2250 0    50   ~ 0
LED[0..3]
Text Label 1050 2790 1    50   ~ 0
LED[0..3]
Wire Bus Line
	1785 2250 1185 2250
Wire Wire Line
	1150 2550 1625 2550
Wire Wire Line
	1150 2650 1625 2650
Wire Wire Line
	1150 2750 1625 2750
Wire Wire Line
	1150 2850 1625 2850
Text Label 1625 2650 2    50   ~ 0
LED1
Text Label 1625 2750 2    50   ~ 0
LED2
Text Label 1625 2850 2    50   ~ 0
LED3
Wire Wire Line
	1775 4975 1825 4975
Wire Wire Line
	4050 4975 4100 4975
Wire Wire Line
	6400 5000 6450 5000
Wire Wire Line
	8725 5000 8775 5000
Wire Wire Line
	9125 6150 9125 6275
$Comp
L power:GND #PWR0162
U 1 1 5E96DE3F
P 9125 6275
F 0 "#PWR0162" H 9125 6025 50  0001 C CNN
F 1 "GND" H 9130 6102 50  0000 C CNN
F 2 "" H 9125 6275 50  0001 C CNN
F 3 "" H 9125 6275 50  0001 C CNN
	1    9125 6275
	1    0    0    -1  
$EndComp
Connection ~ 4450 6150
Wire Wire Line
	4450 6150 6450 6150
Connection ~ 6800 6150
Wire Wire Line
	6800 6150 8775 6150
Connection ~ 9125 6150
Wire Wire Line
	10075 2300 9125 2300
Wire Wire Line
	10075 2200 6800 2200
Wire Wire Line
	4450 2100 10075 2100
Wire Wire Line
	10075 2000 2175 2000
$Comp
L power:+12V #PWR0163
U 1 1 5E977B55
P 9950 1775
F 0 "#PWR0163" H 9950 1625 50  0001 C CNN
F 1 "+12V" H 9965 1948 50  0000 C CNN
F 2 "" H 9950 1775 50  0001 C CNN
F 3 "" H 9950 1775 50  0001 C CNN
	1    9950 1775
	1    0    0    -1  
$EndComp
Wire Wire Line
	9950 1775 9950 1900
Wire Wire Line
	9950 2400 10075 2400
$Comp
L SamacSys_Parts:0805_100nF,50V,5% C102
U 1 1 5E9C9CE6
P 9950 2500
F 0 "C102" V 10154 2628 50  0000 L CNN
F 1 "0805_100nF,50V,5%" V 10245 2628 50  0000 L CNN
F 2 "CAPC2012X88N" H 10300 2550 50  0001 L CNN
F 3 "https://componentsearchengine.com/Datasheets/1/C0805C104J5RACTU.pdf" H 10300 2450 50  0001 L CNN
F 4 "Kemet 100nF +/-5% 50 V dc X7R Dielectric SMD Ceramic Multilayer Capacitor 0805" H 10300 2350 50  0001 L CNN "Description"
F 5 "0.88" H 10300 2250 50  0001 L CNN "Height"
F 6 "80-C0805C104J5R" H 10300 2150 50  0001 L CNN "Mouser Part Number"
F 7 "https://www.mouser.com/Search/Refine.aspx?Keyword=80-C0805C104J5R" H 10300 2050 50  0001 L CNN "Mouser Price/Stock"
F 8 "Kemet" H 10300 1950 50  0001 L CNN "Manufacturer_Name"
F 9 "C0805C104J5RACTU" H 10300 1850 50  0001 L CNN "Manufacturer_Part_Number"
	1    9950 2500
	0    1    1    0   
$EndComp
Wire Wire Line
	9950 2400 9950 2500
Connection ~ 9950 2400
Wire Wire Line
	9950 6150 9125 6150
Wire Wire Line
	9125 2300 9125 4475
Wire Wire Line
	4450 2100 4450 4475
Wire Wire Line
	2625 1900 2625 2875
Connection ~ 9950 1900
Wire Wire Line
	9950 1900 9950 2400
$Comp
L Pro6_Print-rescue:AP2012YD_0-SamacSys_Parts LED?
U 1 1 5EA0BBBD
P 2625 4275
AR Path="/5E678FEC/5EA0BBBD" Ref="LED?"  Part="1" 
AR Path="/5E8A8F40/5EA0BBBD" Ref="LED12"  Part="1" 
F 0 "LED12" H 2925 4642 50  0000 C CNN
F 1 "AP2012YD_0" H 2925 4551 50  0000 C CNN
F 2 "AP2012YD" H 3125 4425 50  0001 L BNN
F 3 "https://componentsearchengine.com/Datasheets/1/AP2012YD.pdf" H 3125 4325 50  0001 L BNN
F 4 "Standard LEDs - SMD YELLOW DIFFUSED" H 3125 4225 50  0001 L BNN "Description"
F 5 "1.1" H 3125 4125 50  0001 L BNN "Height"
F 6 "604-AP2012YD" H 3125 4025 50  0001 L BNN "Mouser Part Number"
F 7 "https://www.mouser.com/Search/Refine.aspx?Keyword=604-AP2012YD" H 3125 3925 50  0001 L BNN "Mouser Price/Stock"
F 8 "Kingbright" H 3125 3825 50  0001 L BNN "Manufacturer_Name"
F 9 "AP2012YD" H 3125 3725 50  0001 L BNN "Manufacturer_Part_Number"
	1    2625 4275
	0    -1   -1   0   
$EndComp
Wire Wire Line
	2625 3675 2625 3575
$Comp
L Pro6_Print-rescue:CRCW0805330RFKEAC-SamacSys_Parts R?
U 1 1 5EA0BBCA
P 2625 3575
AR Path="/5E678FEC/5EA0BBCA" Ref="R?"  Part="1" 
AR Path="/5E8A8F40/5EA0BBCA" Ref="R94"  Part="1" 
F 0 "R94" V 2929 3663 50  0000 L CNN
F 1 "CRCW0805330RFKEAC" V 3020 3663 50  0000 L CNN
F 2 "RESC2012X60N" H 3175 3625 50  0001 L CNN
F 3 "https://componentsearchengine.com/Datasheets/1/CRCW0805330RFKEAC.pdf" H 3175 3525 50  0001 L CNN
F 4 "Thick Film Resistors - SMD 1/8Watt 330ohms 1% Commercial Use" H 3175 3425 50  0001 L CNN "Description"
F 5 "0.6" H 3175 3325 50  0001 L CNN "Height"
F 6 "71-CRCW0805330RFKEAC" H 3175 3225 50  0001 L CNN "Mouser Part Number"
F 7 "https://www.mouser.com/Search/Refine.aspx?Keyword=71-CRCW0805330RFKEAC" H 3175 3125 50  0001 L CNN "Mouser Price/Stock"
F 8 "Vishay" H 3175 3025 50  0001 L CNN "Manufacturer_Name"
F 9 "CRCW0805330RFKEAC" H 3175 2925 50  0001 L CNN "Manufacturer_Part_Number"
	1    2625 3575
	0    -1   -1   0   
$EndComp
Wire Wire Line
	4900 1900 4900 2875
$Comp
L Pro6_Print-rescue:AP2012YD_0-SamacSys_Parts LED?
U 1 1 5EA0DDDA
P 4900 4275
AR Path="/5E678FEC/5EA0DDDA" Ref="LED?"  Part="1" 
AR Path="/5E8A8F40/5EA0DDDA" Ref="LED13"  Part="1" 
F 0 "LED13" H 5200 4642 50  0000 C CNN
F 1 "AP2012YD_0" H 5200 4551 50  0000 C CNN
F 2 "AP2012YD" H 5400 4425 50  0001 L BNN
F 3 "https://componentsearchengine.com/Datasheets/1/AP2012YD.pdf" H 5400 4325 50  0001 L BNN
F 4 "Standard LEDs - SMD YELLOW DIFFUSED" H 5400 4225 50  0001 L BNN "Description"
F 5 "1.1" H 5400 4125 50  0001 L BNN "Height"
F 6 "604-AP2012YD" H 5400 4025 50  0001 L BNN "Mouser Part Number"
F 7 "https://www.mouser.com/Search/Refine.aspx?Keyword=604-AP2012YD" H 5400 3925 50  0001 L BNN "Mouser Price/Stock"
F 8 "Kingbright" H 5400 3825 50  0001 L BNN "Manufacturer_Name"
F 9 "AP2012YD" H 5400 3725 50  0001 L BNN "Manufacturer_Part_Number"
	1    4900 4275
	0    -1   -1   0   
$EndComp
Wire Wire Line
	4900 3675 4900 3575
$Comp
L Pro6_Print-rescue:CRCW0805330RFKEAC-SamacSys_Parts R?
U 1 1 5EA0DDE7
P 4900 3575
AR Path="/5E678FEC/5EA0DDE7" Ref="R?"  Part="1" 
AR Path="/5E8A8F40/5EA0DDE7" Ref="R97"  Part="1" 
F 0 "R97" V 5204 3663 50  0000 L CNN
F 1 "CRCW0805330RFKEAC" V 5295 3663 50  0000 L CNN
F 2 "RESC2012X60N" H 5450 3625 50  0001 L CNN
F 3 "https://componentsearchengine.com/Datasheets/1/CRCW0805330RFKEAC.pdf" H 5450 3525 50  0001 L CNN
F 4 "Thick Film Resistors - SMD 1/8Watt 330ohms 1% Commercial Use" H 5450 3425 50  0001 L CNN "Description"
F 5 "0.6" H 5450 3325 50  0001 L CNN "Height"
F 6 "71-CRCW0805330RFKEAC" H 5450 3225 50  0001 L CNN "Mouser Part Number"
F 7 "https://www.mouser.com/Search/Refine.aspx?Keyword=71-CRCW0805330RFKEAC" H 5450 3125 50  0001 L CNN "Mouser Price/Stock"
F 8 "Vishay" H 5450 3025 50  0001 L CNN "Manufacturer_Name"
F 9 "CRCW0805330RFKEAC" H 5450 2925 50  0001 L CNN "Manufacturer_Part_Number"
	1    4900 3575
	0    -1   -1   0   
$EndComp
Connection ~ 4900 1900
Wire Wire Line
	4900 1900 2625 1900
$Comp
L Pro6_Print-rescue:AP2012YD_0-SamacSys_Parts LED?
U 1 1 5EA10735
P 7250 4275
AR Path="/5E678FEC/5EA10735" Ref="LED?"  Part="1" 
AR Path="/5E8A8F40/5EA10735" Ref="LED14"  Part="1" 
F 0 "LED14" H 7550 4642 50  0000 C CNN
F 1 "AP2012YD_0" H 7550 4551 50  0000 C CNN
F 2 "AP2012YD" H 7750 4425 50  0001 L BNN
F 3 "https://componentsearchengine.com/Datasheets/1/AP2012YD.pdf" H 7750 4325 50  0001 L BNN
F 4 "Standard LEDs - SMD YELLOW DIFFUSED" H 7750 4225 50  0001 L BNN "Description"
F 5 "1.1" H 7750 4125 50  0001 L BNN "Height"
F 6 "604-AP2012YD" H 7750 4025 50  0001 L BNN "Mouser Part Number"
F 7 "https://www.mouser.com/Search/Refine.aspx?Keyword=604-AP2012YD" H 7750 3925 50  0001 L BNN "Mouser Price/Stock"
F 8 "Kingbright" H 7750 3825 50  0001 L BNN "Manufacturer_Name"
F 9 "AP2012YD" H 7750 3725 50  0001 L BNN "Manufacturer_Part_Number"
	1    7250 4275
	0    -1   -1   0   
$EndComp
Wire Wire Line
	7250 3675 7250 3575
$Comp
L Pro6_Print-rescue:CRCW0805330RFKEAC-SamacSys_Parts R?
U 1 1 5EA10742
P 7250 3575
AR Path="/5E678FEC/5EA10742" Ref="R?"  Part="1" 
AR Path="/5E8A8F40/5EA10742" Ref="R100"  Part="1" 
F 0 "R100" V 7554 3663 50  0000 L CNN
F 1 "CRCW0805330RFKEAC" V 7645 3663 50  0000 L CNN
F 2 "RESC2012X60N" H 7800 3625 50  0001 L CNN
F 3 "https://componentsearchengine.com/Datasheets/1/CRCW0805330RFKEAC.pdf" H 7800 3525 50  0001 L CNN
F 4 "Thick Film Resistors - SMD 1/8Watt 330ohms 1% Commercial Use" H 7800 3425 50  0001 L CNN "Description"
F 5 "0.6" H 7800 3325 50  0001 L CNN "Height"
F 6 "71-CRCW0805330RFKEAC" H 7800 3225 50  0001 L CNN "Mouser Part Number"
F 7 "https://www.mouser.com/Search/Refine.aspx?Keyword=71-CRCW0805330RFKEAC" H 7800 3125 50  0001 L CNN "Mouser Price/Stock"
F 8 "Vishay" H 7800 3025 50  0001 L CNN "Manufacturer_Name"
F 9 "CRCW0805330RFKEAC" H 7800 2925 50  0001 L CNN "Manufacturer_Part_Number"
	1    7250 3575
	0    -1   -1   0   
$EndComp
Wire Wire Line
	9950 1900 9575 1900
Wire Wire Line
	7250 1900 7250 2875
Connection ~ 7250 1900
Wire Wire Line
	4900 1900 7250 1900
$Comp
L Pro6_Print-rescue:AP2012YD_0-SamacSys_Parts LED?
U 1 1 5EA14C7B
P 9575 4275
AR Path="/5E678FEC/5EA14C7B" Ref="LED?"  Part="1" 
AR Path="/5E8A8F40/5EA14C7B" Ref="LED15"  Part="1" 
F 0 "LED15" H 9875 4642 50  0000 C CNN
F 1 "AP2012YD_0" H 9875 4551 50  0000 C CNN
F 2 "AP2012YD" H 10075 4425 50  0001 L BNN
F 3 "https://componentsearchengine.com/Datasheets/1/AP2012YD.pdf" H 10075 4325 50  0001 L BNN
F 4 "Standard LEDs - SMD YELLOW DIFFUSED" H 10075 4225 50  0001 L BNN "Description"
F 5 "1.1" H 10075 4125 50  0001 L BNN "Height"
F 6 "604-AP2012YD" H 10075 4025 50  0001 L BNN "Mouser Part Number"
F 7 "https://www.mouser.com/Search/Refine.aspx?Keyword=604-AP2012YD" H 10075 3925 50  0001 L BNN "Mouser Price/Stock"
F 8 "Kingbright" H 10075 3825 50  0001 L BNN "Manufacturer_Name"
F 9 "AP2012YD" H 10075 3725 50  0001 L BNN "Manufacturer_Part_Number"
	1    9575 4275
	0    -1   -1   0   
$EndComp
Wire Wire Line
	9575 3675 9575 3575
$Comp
L Pro6_Print-rescue:CRCW0805330RFKEAC-SamacSys_Parts R?
U 1 1 5EA14C88
P 9575 3575
AR Path="/5E678FEC/5EA14C88" Ref="R?"  Part="1" 
AR Path="/5E8A8F40/5EA14C88" Ref="R103"  Part="1" 
F 0 "R103" V 9879 3663 50  0000 L CNN
F 1 "CRCW0805330RFKEAC" V 9970 3663 50  0000 L CNN
F 2 "RESC2012X60N" H 10125 3625 50  0001 L CNN
F 3 "https://componentsearchengine.com/Datasheets/1/CRCW0805330RFKEAC.pdf" H 10125 3525 50  0001 L CNN
F 4 "Thick Film Resistors - SMD 1/8Watt 330ohms 1% Commercial Use" H 10125 3425 50  0001 L CNN "Description"
F 5 "0.6" H 10125 3325 50  0001 L CNN "Height"
F 6 "71-CRCW0805330RFKEAC" H 10125 3225 50  0001 L CNN "Mouser Part Number"
F 7 "https://www.mouser.com/Search/Refine.aspx?Keyword=71-CRCW0805330RFKEAC" H 10125 3125 50  0001 L CNN "Mouser Price/Stock"
F 8 "Vishay" H 10125 3025 50  0001 L CNN "Manufacturer_Name"
F 9 "CRCW0805330RFKEAC" H 10125 2925 50  0001 L CNN "Manufacturer_Part_Number"
	1    9575 3575
	0    -1   -1   0   
$EndComp
Wire Wire Line
	9575 1900 9575 2875
Connection ~ 9575 1900
Wire Wire Line
	7250 1900 9575 1900
Wire Wire Line
	9575 4275 9575 4475
Wire Wire Line
	9575 4475 9125 4475
Wire Wire Line
	7250 4475 6800 4475
Wire Wire Line
	4900 4475 4450 4475
Wire Wire Line
	2625 4275 2625 4475
Wire Wire Line
	2625 4475 2175 4475
Wire Wire Line
	7250 4275 7250 4475
Wire Wire Line
	6800 2200 6800 4475
$Comp
L Pro6_Print-rescue:1944628-SamacSys_Parts J60
U 1 1 5E8435C5
P 10075 2000
F 0 "J60" H 10703 1846 50  0000 L CNN
F 1 "1944628" H 10703 1755 50  0000 L CNN
F 2 "SHDR5W103P0X500_1X5_2700X857X1215P" H 10725 2100 50  0001 L CNN
F 3 "https://componentsearchengine.com/Datasheets/1/1944628.pdf" H 10725 2000 50  0001 L CNN
F 4 "Phoenix Contact MSTBVA Series, 5mm Pitch 5 Way Base Strip, Solder Termination" H 10725 1900 50  0001 L CNN "Description"
F 5 "12.15" H 10725 1800 50  0001 L CNN "Height"
F 6 "651-1944628" H 10725 1700 50  0001 L CNN "Mouser Part Number"
F 7 "https://www.mouser.com/Search/Refine.aspx?Keyword=651-1944628" H 10725 1600 50  0001 L CNN "Mouser Price/Stock"
F 8 "Phoenix Contact" H 10725 1500 50  0001 L CNN "Manufacturer_Name"
F 9 "1944628" H 10725 1400 50  0001 L CNN "Manufacturer_Part_Number"
	1    10075 2000
	1    0    0    -1  
$EndComp
$Comp
L SamacSys_Parts:IRLR8726PBF Q22
U 1 1 5E8614DC
P 1875 4975
F 0 "Q22" H 2313 5121 50  0000 L CNN
F 1 "IRLR8726PBF" H 2313 5030 50  0000 L CNN
F 2 "SamacSys_Parts:D-PAK_TO-252AA__1" H 2325 4925 50  0001 L CNN
F 3 "http://www.mouser.com/ds/2/196/irlr8726pbf-1228011.pdf" H 2325 4825 50  0001 L CNN
F 4 "INFINEON - IRLR8726PBF - MOSFET, N-CH 30V 86A DPAK" H 2325 4725 50  0001 L CNN "Description"
F 5 "Infineon" H 2325 4525 50  0001 L CNN "Manufacturer_Name"
F 6 "IRLR8726PBF" H 2325 4425 50  0001 L CNN "Manufacturer_Part_Number"
F 7 "942-IRLR8726PBF" H 2325 4325 50  0001 L CNN "Mouser Part Number"
F 8 "https://www.mouser.com/Search/Refine.aspx?Keyword=942-IRLR8726PBF" H 2325 4225 50  0001 L CNN "Mouser Price/Stock"
F 9 "6887244" H 2325 4125 50  0001 L CNN "RS Part Number"
F 10 "http://uk.rs-online.com/web/p/products/6887244" H 2325 4025 50  0001 L CNN "RS Price/Stock"
F 11 "70019880" H 2325 3925 50  0001 L CNN "Allied_Number"
F 12 "https://www.alliedelec.com/infineon-irlr8726pbf/70019880/" H 2325 3825 50  0001 L CNN "Allied Price/Stock"
	1    1875 4975
	1    0    0    -1  
$EndComp
Wire Wire Line
	2175 2000 2175 4475
Connection ~ 2175 4475
Wire Wire Line
	2175 4475 2175 4575
$Comp
L SamacSys_Parts:IRLR8726PBF Q23
U 1 1 5E874471
P 4150 4975
F 0 "Q23" H 4588 5121 50  0000 L CNN
F 1 "IRLR8726PBF" H 4588 5030 50  0000 L CNN
F 2 "SamacSys_Parts:D-PAK_TO-252AA__1" H 4600 4925 50  0001 L CNN
F 3 "http://www.mouser.com/ds/2/196/irlr8726pbf-1228011.pdf" H 4600 4825 50  0001 L CNN
F 4 "INFINEON - IRLR8726PBF - MOSFET, N-CH 30V 86A DPAK" H 4600 4725 50  0001 L CNN "Description"
F 5 "Infineon" H 4600 4525 50  0001 L CNN "Manufacturer_Name"
F 6 "IRLR8726PBF" H 4600 4425 50  0001 L CNN "Manufacturer_Part_Number"
F 7 "942-IRLR8726PBF" H 4600 4325 50  0001 L CNN "Mouser Part Number"
F 8 "https://www.mouser.com/Search/Refine.aspx?Keyword=942-IRLR8726PBF" H 4600 4225 50  0001 L CNN "Mouser Price/Stock"
F 9 "6887244" H 4600 4125 50  0001 L CNN "RS Part Number"
F 10 "http://uk.rs-online.com/web/p/products/6887244" H 4600 4025 50  0001 L CNN "RS Price/Stock"
F 11 "70019880" H 4600 3925 50  0001 L CNN "Allied_Number"
F 12 "https://www.alliedelec.com/infineon-irlr8726pbf/70019880/" H 4600 3825 50  0001 L CNN "Allied Price/Stock"
	1    4150 4975
	1    0    0    -1  
$EndComp
$Comp
L SamacSys_Parts:IRLR8726PBF Q24
U 1 1 5E87657A
P 6500 5000
F 0 "Q24" H 6938 5146 50  0000 L CNN
F 1 "IRLR8726PBF" H 6938 5055 50  0000 L CNN
F 2 "SamacSys_Parts:D-PAK_TO-252AA__1" H 6950 4950 50  0001 L CNN
F 3 "http://www.mouser.com/ds/2/196/irlr8726pbf-1228011.pdf" H 6950 4850 50  0001 L CNN
F 4 "INFINEON - IRLR8726PBF - MOSFET, N-CH 30V 86A DPAK" H 6950 4750 50  0001 L CNN "Description"
F 5 "Infineon" H 6950 4550 50  0001 L CNN "Manufacturer_Name"
F 6 "IRLR8726PBF" H 6950 4450 50  0001 L CNN "Manufacturer_Part_Number"
F 7 "942-IRLR8726PBF" H 6950 4350 50  0001 L CNN "Mouser Part Number"
F 8 "https://www.mouser.com/Search/Refine.aspx?Keyword=942-IRLR8726PBF" H 6950 4250 50  0001 L CNN "Mouser Price/Stock"
F 9 "6887244" H 6950 4150 50  0001 L CNN "RS Part Number"
F 10 "http://uk.rs-online.com/web/p/products/6887244" H 6950 4050 50  0001 L CNN "RS Price/Stock"
F 11 "70019880" H 6950 3950 50  0001 L CNN "Allied_Number"
F 12 "https://www.alliedelec.com/infineon-irlr8726pbf/70019880/" H 6950 3850 50  0001 L CNN "Allied Price/Stock"
	1    6500 5000
	1    0    0    -1  
$EndComp
$Comp
L SamacSys_Parts:IRLR8726PBF Q25
U 1 1 5E877D77
P 8825 5000
F 0 "Q25" H 9263 5146 50  0000 L CNN
F 1 "IRLR8726PBF" H 9263 5055 50  0000 L CNN
F 2 "SamacSys_Parts:D-PAK_TO-252AA__1" H 9275 4950 50  0001 L CNN
F 3 "http://www.mouser.com/ds/2/196/irlr8726pbf-1228011.pdf" H 9275 4850 50  0001 L CNN
F 4 "INFINEON - IRLR8726PBF - MOSFET, N-CH 30V 86A DPAK" H 9275 4750 50  0001 L CNN "Description"
F 5 "Infineon" H 9275 4550 50  0001 L CNN "Manufacturer_Name"
F 6 "IRLR8726PBF" H 9275 4450 50  0001 L CNN "Manufacturer_Part_Number"
F 7 "942-IRLR8726PBF" H 9275 4350 50  0001 L CNN "Mouser Part Number"
F 8 "https://www.mouser.com/Search/Refine.aspx?Keyword=942-IRLR8726PBF" H 9275 4250 50  0001 L CNN "Mouser Price/Stock"
F 9 "6887244" H 9275 4150 50  0001 L CNN "RS Part Number"
F 10 "http://uk.rs-online.com/web/p/products/6887244" H 9275 4050 50  0001 L CNN "RS Price/Stock"
F 11 "70019880" H 9275 3950 50  0001 L CNN "Allied_Number"
F 12 "https://www.alliedelec.com/infineon-irlr8726pbf/70019880/" H 9275 3850 50  0001 L CNN "Allied Price/Stock"
	1    8825 5000
	1    0    0    -1  
$EndComp
Wire Wire Line
	8025 5000 7675 5000
Wire Wire Line
	9125 4475 9125 4600
Connection ~ 9125 4475
Wire Wire Line
	6800 4475 6800 4600
Connection ~ 6800 4475
Wire Wire Line
	4450 4475 4450 4575
Connection ~ 4450 4475
Wire Wire Line
	4900 4275 4900 4475
$Comp
L SamacSys_Parts:0805_10Ohm,150V,5%,125mW R92
U 1 1 5E899D59
P 1075 4975
F 0 "R92" H 1425 5200 50  0000 C CNN
F 1 "0805_10Ohm,150V,5%,125mW" H 1425 5109 50  0000 C CNN
F 2 "RESC2012X60N" H 1625 5025 50  0001 L CNN
F 3 "https://componentsearchengine.com/Datasheets/1/RC0805JR-1010RL.pdf" H 1625 4925 50  0001 L CNN
F 4 "Thick Film Resistors - SMD 10 ohm 5% 150V General Purpose" H 1625 4825 50  0001 L CNN "Description"
F 5 "0.6" H 1625 4725 50  0001 L CNN "Height"
F 6 "603-RC0805JR-1010RL" H 1625 4625 50  0001 L CNN "Mouser Part Number"
F 7 "https://www.mouser.com/Search/Refine.aspx?Keyword=603-RC0805JR-1010RL" H 1625 4525 50  0001 L CNN "Mouser Price/Stock"
F 8 "YAGEO (PHYCOMP)" H 1625 4425 50  0001 L CNN "Manufacturer_Name"
F 9 "RC0805JR-1010RL" H 1625 4325 50  0001 L CNN "Manufacturer_Part_Number"
	1    1075 4975
	1    0    0    -1  
$EndComp
$Comp
L SamacSys_Parts:0805_10Ohm,150V,5%,125mW R95
U 1 1 5E89AE58
P 3350 4975
F 0 "R95" H 3700 5200 50  0000 C CNN
F 1 "0805_10Ohm,150V,5%,125mW" H 3700 5109 50  0000 C CNN
F 2 "RESC2012X60N" H 3900 5025 50  0001 L CNN
F 3 "https://componentsearchengine.com/Datasheets/1/RC0805JR-1010RL.pdf" H 3900 4925 50  0001 L CNN
F 4 "Thick Film Resistors - SMD 10 ohm 5% 150V General Purpose" H 3900 4825 50  0001 L CNN "Description"
F 5 "0.6" H 3900 4725 50  0001 L CNN "Height"
F 6 "603-RC0805JR-1010RL" H 3900 4625 50  0001 L CNN "Mouser Part Number"
F 7 "https://www.mouser.com/Search/Refine.aspx?Keyword=603-RC0805JR-1010RL" H 3900 4525 50  0001 L CNN "Mouser Price/Stock"
F 8 "YAGEO (PHYCOMP)" H 3900 4425 50  0001 L CNN "Manufacturer_Name"
F 9 "RC0805JR-1010RL" H 3900 4325 50  0001 L CNN "Manufacturer_Part_Number"
	1    3350 4975
	1    0    0    -1  
$EndComp
$Comp
L SamacSys_Parts:0805_10Ohm,150V,5%,125mW R98
U 1 1 5E89C6CC
P 5700 5000
F 0 "R98" H 6050 5225 50  0000 C CNN
F 1 "0805_10Ohm,150V,5%,125mW" H 6050 5134 50  0000 C CNN
F 2 "RESC2012X60N" H 6250 5050 50  0001 L CNN
F 3 "https://componentsearchengine.com/Datasheets/1/RC0805JR-1010RL.pdf" H 6250 4950 50  0001 L CNN
F 4 "Thick Film Resistors - SMD 10 ohm 5% 150V General Purpose" H 6250 4850 50  0001 L CNN "Description"
F 5 "0.6" H 6250 4750 50  0001 L CNN "Height"
F 6 "603-RC0805JR-1010RL" H 6250 4650 50  0001 L CNN "Mouser Part Number"
F 7 "https://www.mouser.com/Search/Refine.aspx?Keyword=603-RC0805JR-1010RL" H 6250 4550 50  0001 L CNN "Mouser Price/Stock"
F 8 "YAGEO (PHYCOMP)" H 6250 4450 50  0001 L CNN "Manufacturer_Name"
F 9 "RC0805JR-1010RL" H 6250 4350 50  0001 L CNN "Manufacturer_Part_Number"
	1    5700 5000
	1    0    0    -1  
$EndComp
$Comp
L SamacSys_Parts:0805_10Ohm,150V,5%,125mW R101
U 1 1 5E89DA87
P 8025 5000
F 0 "R101" H 8375 5225 50  0000 C CNN
F 1 "0805_10Ohm,150V,5%,125mW" H 8375 5134 50  0000 C CNN
F 2 "RESC2012X60N" H 8575 5050 50  0001 L CNN
F 3 "https://componentsearchengine.com/Datasheets/1/RC0805JR-1010RL.pdf" H 8575 4950 50  0001 L CNN
F 4 "Thick Film Resistors - SMD 10 ohm 5% 150V General Purpose" H 8575 4850 50  0001 L CNN "Description"
F 5 "0.6" H 8575 4750 50  0001 L CNN "Height"
F 6 "603-RC0805JR-1010RL" H 8575 4650 50  0001 L CNN "Mouser Part Number"
F 7 "https://www.mouser.com/Search/Refine.aspx?Keyword=603-RC0805JR-1010RL" H 8575 4550 50  0001 L CNN "Mouser Price/Stock"
F 8 "YAGEO (PHYCOMP)" H 8575 4450 50  0001 L CNN "Manufacturer_Name"
F 9 "RC0805JR-1010RL" H 8575 4350 50  0001 L CNN "Manufacturer_Part_Number"
	1    8025 5000
	1    0    0    -1  
$EndComp
$Comp
L Pro6_Print-rescue:0805_100kOhm,150V,125mW,1%-SamacSys_Parts R93
U 1 1 5E8AAC23
P 1825 5100
F 0 "R93" V 2129 5188 50  0000 L CNN
F 1 "0805_100kOhm,150V,125mW,1%-SamacSys_Parts" V 2220 5188 50  0000 L CNN
F 2 "RESC2012X60N" H 2375 5150 50  0001 L CNN
F 3 "https://componentsearchengine.com/Datasheets/1/CRCW0805100KFKEAC.pdf" H 2375 5050 50  0001 L CNN
F 4 "Thick Film Resistors - SMD 1/8Watt 100Kohms 1% Commercial Use" H 2375 4950 50  0001 L CNN "Description"
F 5 "0.6" H 2375 4850 50  0001 L CNN "Height"
F 6 "71-CRCW0805100KFKEAC" H 2375 4750 50  0001 L CNN "Mouser Part Number"
F 7 "https://www.mouser.com/Search/Refine.aspx?Keyword=71-CRCW0805100KFKEAC" H 2375 4650 50  0001 L CNN "Mouser Price/Stock"
F 8 "Vishay" H 2375 4550 50  0001 L CNN "Manufacturer_Name"
F 9 "CRCW0805100KFKEAC" H 2375 4450 50  0001 L CNN "Manufacturer_Part_Number"
	1    1825 5100
	0    1    1    0   
$EndComp
$Comp
L Pro6_Print-rescue:0805_100kOhm,150V,125mW,1%-SamacSys_Parts R96
U 1 1 5E8AC92A
P 4100 5100
F 0 "R96" V 4404 5188 50  0000 L CNN
F 1 "0805_100kOhm,150V,125mW,1%-SamacSys_Parts" V 4495 5188 50  0000 L CNN
F 2 "RESC2012X60N" H 4650 5150 50  0001 L CNN
F 3 "https://componentsearchengine.com/Datasheets/1/CRCW0805100KFKEAC.pdf" H 4650 5050 50  0001 L CNN
F 4 "Thick Film Resistors - SMD 1/8Watt 100Kohms 1% Commercial Use" H 4650 4950 50  0001 L CNN "Description"
F 5 "0.6" H 4650 4850 50  0001 L CNN "Height"
F 6 "71-CRCW0805100KFKEAC" H 4650 4750 50  0001 L CNN "Mouser Part Number"
F 7 "https://www.mouser.com/Search/Refine.aspx?Keyword=71-CRCW0805100KFKEAC" H 4650 4650 50  0001 L CNN "Mouser Price/Stock"
F 8 "Vishay" H 4650 4550 50  0001 L CNN "Manufacturer_Name"
F 9 "CRCW0805100KFKEAC" H 4650 4450 50  0001 L CNN "Manufacturer_Part_Number"
	1    4100 5100
	0    1    1    0   
$EndComp
$Comp
L Pro6_Print-rescue:0805_100kOhm,150V,125mW,1%-SamacSys_Parts R99
U 1 1 5E8ADF1D
P 6450 5100
F 0 "R99" V 6754 5188 50  0000 L CNN
F 1 "0805_100kOhm,150V,125mW,1%-SamacSys_Parts" V 6845 5188 50  0000 L CNN
F 2 "RESC2012X60N" H 7000 5150 50  0001 L CNN
F 3 "https://componentsearchengine.com/Datasheets/1/CRCW0805100KFKEAC.pdf" H 7000 5050 50  0001 L CNN
F 4 "Thick Film Resistors - SMD 1/8Watt 100Kohms 1% Commercial Use" H 7000 4950 50  0001 L CNN "Description"
F 5 "0.6" H 7000 4850 50  0001 L CNN "Height"
F 6 "71-CRCW0805100KFKEAC" H 7000 4750 50  0001 L CNN "Mouser Part Number"
F 7 "https://www.mouser.com/Search/Refine.aspx?Keyword=71-CRCW0805100KFKEAC" H 7000 4650 50  0001 L CNN "Mouser Price/Stock"
F 8 "Vishay" H 7000 4550 50  0001 L CNN "Manufacturer_Name"
F 9 "CRCW0805100KFKEAC" H 7000 4450 50  0001 L CNN "Manufacturer_Part_Number"
	1    6450 5100
	0    1    1    0   
$EndComp
$Comp
L Pro6_Print-rescue:0805_100kOhm,150V,125mW,1%-SamacSys_Parts R102
U 1 1 5E8AF88F
P 8775 5075
F 0 "R102" V 9079 5163 50  0000 L CNN
F 1 "0805_100kOhm,150V,125mW,1%-SamacSys_Parts" V 9170 5163 50  0000 L CNN
F 2 "RESC2012X60N" H 9325 5125 50  0001 L CNN
F 3 "https://componentsearchengine.com/Datasheets/1/CRCW0805100KFKEAC.pdf" H 9325 5025 50  0001 L CNN
F 4 "Thick Film Resistors - SMD 1/8Watt 100Kohms 1% Commercial Use" H 9325 4925 50  0001 L CNN "Description"
F 5 "0.6" H 9325 4825 50  0001 L CNN "Height"
F 6 "71-CRCW0805100KFKEAC" H 9325 4725 50  0001 L CNN "Mouser Part Number"
F 7 "https://www.mouser.com/Search/Refine.aspx?Keyword=71-CRCW0805100KFKEAC" H 9325 4625 50  0001 L CNN "Mouser Price/Stock"
F 8 "Vishay" H 9325 4525 50  0001 L CNN "Manufacturer_Name"
F 9 "CRCW0805100KFKEAC" H 9325 4425 50  0001 L CNN "Manufacturer_Part_Number"
	1    8775 5075
	0    1    1    0   
$EndComp
Wire Wire Line
	1825 4975 1825 5100
Connection ~ 1825 4975
Wire Wire Line
	1825 4975 1875 4975
Wire Wire Line
	2175 5175 2175 6150
Wire Wire Line
	1825 5800 1825 6150
Wire Wire Line
	1825 6150 2175 6150
Connection ~ 2175 6150
Wire Wire Line
	2175 6150 4100 6150
Wire Wire Line
	4100 4975 4100 5100
Connection ~ 4100 4975
Wire Wire Line
	4100 4975 4150 4975
Wire Wire Line
	4100 5800 4100 6150
Connection ~ 4100 6150
Wire Wire Line
	4100 6150 4450 6150
Wire Wire Line
	4450 5175 4450 6150
Wire Wire Line
	6450 5800 6450 6150
Connection ~ 6450 6150
Wire Wire Line
	6450 6150 6800 6150
Wire Wire Line
	6800 5200 6800 6150
Wire Wire Line
	6450 5000 6450 5100
Connection ~ 6450 5000
Wire Wire Line
	6450 5000 6500 5000
Wire Wire Line
	8775 5000 8775 5075
Connection ~ 8775 5000
Wire Wire Line
	8775 5000 8825 5000
Wire Wire Line
	8775 5775 8775 6150
Connection ~ 8775 6150
Wire Wire Line
	8775 6150 9125 6150
Wire Wire Line
	9125 5200 9125 6150
Wire Wire Line
	9950 3000 9950 6150
Wire Bus Line
	1050 2450 1050 3650
$EndSCHEMATC
