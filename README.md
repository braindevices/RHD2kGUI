RHD2kGUI LW edition
========
the RHD20002kGUI is the Interface software for intantech RHD2000 evaluation system.

This edition enhanced the original RHD2kGUI program, by allowing Electrochemical Impedance Spectroscopy (EIS) on each individial electrode. It also allow user to save and load all settings, which can be very convienent when run several different experiments in parallel.

## EIS scanning
If the `AtuoRunEIS` is checked then it starts the EIS scanning on each enabled channel when recording started.

In the `Impedance` panel, now we can input a list of desired frequencies. The actual frequencies used in the program are calculated and displayed below. The filename can be automatically generated based on the basefilename.

One can still start the impedance scanning manually, with the `Run impedance measurement`.

![eisdiag](doc/EISfeatures.png)


## Change the fonts
It is very common, that one find the default font does not work under their OS/Display settings. For example: ![beforefontchange](doc/before_changefont.png) We can see the font is too big making the text unreadable in both left and right panels. 
In standard edition, we have to change the system fonts to sovle this issue which is very annoying.

Now in this edition, we can simple use the font menu to change them: ![fontmenu](doc/changefontsv0.png)

After I change left side font to 10 and right side font to 9, the text looks good: ![afterfontchange](doc/after_changefont.png)

## Save and load your experiment settings
In standard edition, the settings are automatically saved when closing the GUI and loaded when starting it. However, I often run experiments with different settings in parallel. I found it is very annoying to keep changing those settings manually. Thus I added this save/load function to quickly switch from one config to another.
![configsaveload](doc/saveandloadsettings.png)

