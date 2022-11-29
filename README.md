# BMI088 Zephyr Driver Module

## Usage

This is a west module.
You can integrate it in your application by adding the project to your west manifest:

```yaml
manifest:
  remotes:
    - name: teamspatzenhirn
      url-base: https://github.com/teamspatzenhirn
  projects:
    - name: bmi088_zephyr_driver
      remote: teamspatzenhirn
      revision: <current commit hash>
      path: modules/bmi088
```

Enable the sensor by defining its location and properties in the devicetree (overlay).
Gyro and accelerometer are handled separately, since that's how the sensor is built.
It would be possible to use just one of the sensors, but it's currently not possible to
completely deactivate half of the driver, just because we usually need both sensors.

For sensor configuration the gyro provides the `bandwidth` devicetree setting, the
accelerometer provides oversampling rate `osr` and output data rate `odr`, see the
datasheet for valid values.

```c
&lpspi4 {
    gyro: bmi088_gyr@0 {
        compatible = "bosch,bmi088-gyr";
        reg = <0>;
        spi-max-frequency = <10000000>;
        // datasheet page 39
        bandwidth = <0x06>; // corner-frequency at 64 Hz
        status = "okay";
    };

    acc: bmi088_acc@1 {
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

Example of reading sensor values:

```c++
#define GYRO_NODE DT_NODELABEL(gyro)
constexpr const device *gyro_sensor_dev = DEVICE_DT_GET(GYRO_NODE);

#define ACCELEROMETER_NODE DT_NODELABEL(gyro)
constexpr const device *accel_sensor_dev = DEVICE_DT_GET(ACCELEROMETER_NODE);

void sensor_readout() {
    sensor_sample_fetch(gyro_sensor_dev);
    sensor_value gyro[3];
    sensor_channel_get(gyro_sensor_dev, SENSOR_CHAN_GYRO_XYZ, gyro);
    LOG_INF("Gyro x: %f °/s y: %f °/s z: %f °/s",
            sensor_value_to_double(gyro[0]),
            sensor_value_to_double(gyro[1]),
            sensor_value_to_double(gyro[2]));

    sensor_sample_fetch(accel_sensor_dev);
    sensor_value accel[3];
    sensor_channel_get(accel_sensor_dev, SENSOR_CHAN_ACCEL_XYZ, accel);
    LOG_INF("Accelerometer x: %f m/s2 y: %f m/s2 z: %f m/s2",
            sensor_value_to_double(accel[0]),
            sensor_value_to_double(accel[1]),
            sensor_value_to_double(accel[2]));
}
```

## Git history

This driver has been extracted from our Zephyr fork.
For the full git history of the driver, refer to this commit in out fork,
which is the last version before moving the driver here:
https://github.com/teamspatzenhirn/zephyr/tree/858548919eb664fc364dad0226e3dcf71586292b/drivers/sensor/bmi088

## Writing Out-Of-Tree Drivers

Since this was kind of a pain to figure out, here are a few helpful links if you want to do this:

* https://jdelaney.me/posts/zephyr-oot-modules/
* https://interrupt.memfault.com/blog/building-drivers-on-zephyr
* https://blog.golioth.io/adding-an-out-of-tree-sensor-driver-to-zephyr/
* https://github.com/zephyrproject-rtos/zephyr/tree/main/samples/application_development/out_of_tree_driver
* https://jonasotto.com/posts/zephyr_out_of_tree_driver/
