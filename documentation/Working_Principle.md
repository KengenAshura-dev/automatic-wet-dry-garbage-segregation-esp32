# Working Principle

1. A waste item is presented to the sensing area.
2. The moisture sensor responds to the moisture condition of the item and provides an analog voltage.
3. The ESP32 reads multiple ADC samples and calculates their average.
4. Firmware compares the averaged raw ADC value with a calibrated threshold.
5. A configurable polarity setting determines whether readings below or above the threshold represent the wet category.
6. The servo moves the flap to the configured wet or dry position.
7. After the transfer delay, the servo returns to its neutral position.

## Calibration is essential

The sensor output depends on sensor technology, supply voltage, contact, placement, and material. The threshold and wet/dry polarity in the example firmware are placeholders. Record readings for representative known samples and choose a threshold only if the measured groups are distinguishable.

## Important distinction

This is moisture-based sorting, not comprehensive material recognition. A wet plastic item may be classified as wet, and a dry organic item may be classified as dry. Mixed or borderline items can be misclassified.
