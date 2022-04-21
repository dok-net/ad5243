# AD5243

## Arduino library to control the AD5243 family of digital potentiometers / rheostats

### Notes
The datasheet mentions typical wiper resistance at 160 ohms. The specimens that we were able to test, of the 2K5 variant,
showed 70 ohms resistance at data == 0. In staying true to the datasheet's use of two times wiper resistance in the supplied
formulas, the constructor argument expects half the measured resistance at data == 0 to be specified. 