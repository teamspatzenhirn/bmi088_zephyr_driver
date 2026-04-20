# BMI088 Zephyr Driver Module

## Usage

This is a west module. You can integrate it in your application by adding the project to your west manifest or by specifying it in your `EXTRA_ZEPHYR_MODULES`.

Gyro and accelerometer are handled separately, since that's how the sensor is built.
It would be possible to use just one of the sensors, but it's currently not possible to
completely deactivate half of the driver, just because we usually need both sensors.

Enable the sensor by defining its location and properties in the devicetree (overlay).
For sensor configuration the gyro provides the `bandwidth` devicetree setting, the
accelerometer provides oversampling rate `osr` and output data rate `odr`, see the
datasheet for valid values.

```c
&lpspi4 {
    my_gyro: bmi088_gyr@0 {
        compatible = "bosch,bmi088-gyr";
        reg = <0>;
        spi-max-frequency = <10000000>;
        // datasheet page 39
        bandwidth = <0x06>; // corner-frequency at 64 Hz
        status = "okay";
    };

    my_acc: bmi088_acc@1 {
        compatible = "bosch,bmi088-acc";
        reg = <1>;
        spi-max-frequency = <10000000>;
        // datasheet page 16 and 29
        // corner-frequency at 80 Hz
        odr = <0x0B>; // 800 Hz
        osr = <0x08>; // 4 times oversampled
        status = "okay";
    };
};
```

## Example

A full working example for reading sensor values on a Teensy 4.1 can be found [here](samples/sensor/bmi088/).

## Writing Out-Of-Tree Drivers

Since this was kind of a pain to figure out, here are a few helpful links if you want to do this:

* https://interrupt.memfault.com/blog/building-drivers-on-zephyr
* https://blog.golioth.io/adding-an-out-of-tree-sensor-driver-to-zephyr/
* https://jonasotto.com/posts/zephyr_out_of_tree_driver/
