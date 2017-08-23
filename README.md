RHD2kGUI LW edition
========
the RHD20002kGUI is the Interface software for intantech RHD2000 evaluation system.

This edition enhanced the original RHD2kGUI program, by allowing Electrochemical Impedance Spectroscopy (EIS) on each individial electrode. It also allow user to save and load all settings, which can be very convienent when run several different experiments in parallel.

## EIS scanning
### Interface
If the `AtuoRunEIS` is checked then it starts the EIS scanning on each enabled channel when recording started.

In the `Impedance` panel, now we can input a list of desired frequencies. The actual frequencies used in the program are calculated and displayed below. The filename can be automatically generated based on the basefilename.

One can still start the impedance scanning manually, with the `Run impedance measurement`.

![eisdiag](doc/EISfeatures.png)

### example EIS data
The data are saved as csv
The EIS csv file is like this:
```
Channel Number,Channel Name,Port,Enabled,Impedance Magnitude at  300.000000, 600.000000, 1000.000000, 2000.000000, 3750.000000, Hz (ohms),Impedance Phase (degrees),Series RC equivalent R (Ohms),Series RC equivalent C (Farads)
A-000,A-000,Port A,1,3.000000e+02,4.657420e+06,-72.9,1.371045e+06,9.535137e-12
A-000,A-000,Port A,1,6.000000e+02,3.075658e+06,-83.5,3.461604e+05,1.388734e-11
```
The first line is some comments which can be ignored. Then it comes with data rows, which have following columns: 
```
    Channel Number,Channel Name,Port,Enabled,Hz,Impedance (ohms), Phase (degrees),Series RC equivalent R (Ohms),Series RC equivalent C (Farads)
```

If the scanning frequencies are: 300, 600, 1k, 2k, and 3.75k, then the loaded data is like this:

| Channel Number | Channel Name | Port   | Enabled | Hz           | Impedance (ohms) | Phase (degrees) | Series RC equivalent R (Ohms) | Series RC equivalent C (Farads) |
|----------------|--------------|--------|---------|--------------|------------------|-----------------|-------------------------------|---------------------------------|
| A-000          | A-000        | Port A | 1       | 3.000000e+02 | 4.657420e+06     | -72.9           | 1.371045e+06                  | 9.535137e-12                    |
| A-000          | A-000        | Port A | 1       | 6.000000e+02 | 3.075658e+06     | -83.5           | 3.461604e+05                  | 1.388734e-11                    |
| A-000          | A-000        | Port A | 1       | 1.000000e+03 | 1.837914e+06     | -87.4           | 8.377171e+04                  | 2.311613e-11                    |
| A-000          | A-000        | Port A | 1       | 2.000000e+03 | 8.718171e+05     | -97.8           | -1.186152e+05                 | 4.913837e-11                    |
| A-000          | A-000        | Port A | 1       | 3.750000e+03 | 4.466400e+05     | -109.0          | -1.454549e+05                 | 1.005024e-10                    |
| A-001          | A-001        | Port A | 1       | 3.000000e+02 | 1.435662e+06     | -95.0           | -1.254829e+05                 | 2.967577e-11                    |
| A-001          | A-001        | Port A | 1       | 6.000000e+02 | 7.301232e+05     | -93.3           | -4.203666e+04                 | 5.822557e-11                    |
| A-001          | A-001        | Port A | 1       | 1.000000e+03 | 4.378847e+05     | -94.4           | -3.384901e+04                 | 9.721438e-11                    |
| A-001          | A-001        | Port A | 1       | 2.000000e+03 | 2.117935e+05     | -96.8           | -2.496076e+04                 | 2.017964e-10                    |
| A-001          | A-001        | Port A | 1       | 3.750000e+03 | 1.053514e+05     | -96.2           | -1.130027e+04                 | 4.051925e-10                    |
| A-002          | A-002        | Port A | 1       | 3.000000e+02 | 8.124212e+06     | -91.6           | -2.254001e+05                 | 5.226065e-12                    |

## Change the fonts
It is very common, that one find the default font does not work under their OS/Display settings. For example: ![beforefontchange](doc/before_changefont.png) We can see the font is too big making the text unreadable in both left and right panels. 
In standard edition, we have to change the system fonts to sovle this issue which is very annoying.

Now in this edition, we can simple use the font menu to change them: ![fontmenu](doc/changefontsv0.png)

After I change left side font to 10 and right side font to 9, the text looks good: ![afterfontchange](doc/after_changefont.png)

## Save and load your experiment settings
In standard edition, the settings are automatically saved when closing the GUI and loaded when starting it. However, I often run experiments with different settings in parallel. I found it is very annoying to keep changing those settings manually. Thus I added this save/load function to quickly switch from one config to another.
![configsaveload](doc/saveandloadsettings.png)

