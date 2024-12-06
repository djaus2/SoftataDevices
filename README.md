## SoftataDevices

A refeactoring of the repository [djaus2/Soft-ata](https://gitshub.com/Softata) such that ```<repo>/code/Softata/src``` directory is separated to here.

This refactored version of that folder so that it is a separate Arduino library.

It can be installed from an Arduino sketch by downloading the zip file (press to green Clone button) and installing it as a zip file librray.

Previously this folder st below the root of the Arduino softata sketch folder. It is confiured as a hierachy of classes so that a device class inherits methods from defined in the parent and so that all classes antecendant from the same parent have the same methods, but with device specific implementations. For example, all displays implement the ```Clear()``` method. Also, all displays implement a ```Misc()``` method that has methods specific to the display type. For example, the bargraph has a misc.floww() method that turns on every odd segenment. 

Methods that do not return a value (such as with a sensor read), return a tristate enum value which is normally ```_ok```. If there is an error in the method, ```_nok``` is returned. If a method is not implemneted then ```notimplemneted``` is returned which at a higher level is meant to be interpretteed is OK but can be used otherwise. ```_nan_``` is alos a return option for data reads.
