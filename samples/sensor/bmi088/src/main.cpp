#include <zephyr/device.h>
#include <zephyr/drivers/sensor.h>

int main(){
    printk("BMI088 sample application\n");

    const device *my_gyro = DEVICE_DT_GET(DT_NODELABEL(my_gyro));

    const device *my_acc = DEVICE_DT_GET(DT_NODELABEL(my_acc));

    if (!device_is_ready(my_gyro)) {
		printk("my_gyro: device not ready.\n");
		return 0;
	}

    if (!device_is_ready(my_acc)) {
		printk("my_acc: device not ready.\n");
		return 0;
	}


    while (true) {        
        sensor_sample_fetch(my_gyro);
        sensor_value gyro[3];
        sensor_channel_get(my_gyro, SENSOR_CHAN_GYRO_XYZ, gyro);
        printk("Gyro x: %f °/s y: %f °/s z: %f °/s",
                sensor_value_to_double(&gyro[0]),
                sensor_value_to_double(&gyro[1]),
                sensor_value_to_double(&gyro[2]));

        sensor_sample_fetch(my_acc);
        sensor_value accel[3];
        sensor_channel_get(my_acc, SENSOR_CHAN_ACCEL_XYZ, accel);
        printk("Accelerometer x: %f m/s2 y: %f m/s2 z: %f m/s2",
                sensor_value_to_double(&accel[0]),
                sensor_value_to_double(&accel[1]),
                sensor_value_to_double(&accel[2]));
    }
}
