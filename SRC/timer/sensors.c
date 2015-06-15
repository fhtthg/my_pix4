#include "sensors.h"



extern MPU_report   MPU_report1;
extern LSM303D_ACC_report  LSM303D_ACC_report1;
extern LSM303D_MAG_report  LSM303D_MAG_report1;


void Sensors_process(void)
{

    // ACC和gyro同更新 mag慢很多  故以acc为参考
    if(MPU_report1.flag == 1) // 如果ACC更新
    {


    }


}


struct sensors_report {

    uint64_t timestamp_acc_gyro;
	float acc_x;	// m/s^2   body
	float acc_y;
	float acc_z;
	float temperature_acc_gyro;	// 摄氏温度
    float gyro_x;	// 度/s   body
	float gyro_y;
	float gyro_z;


    uint64_t timestamp_mag;
    float mag_x;   // 度/s   body
    float mag_y;
    float mag_z;
    float temperature_mag;
};



