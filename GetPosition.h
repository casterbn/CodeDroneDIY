// Arduino Wire library is required if I2Cdev I2CDEV_ARDUINO_WIRE implementation
// is used in I2Cdev.h
#include "Wire.h"
// I2Cdev and MPU6050 must be installed as libraries, or else the .cpp/.h files
// for both classes must be in the include path of your project
#include "I2Cdev.h"
#include "MPU6050.h"

class GetPosition
{
  public:
    /* /!\ HighPassFilterCoeff is an important coeff for complementary filter /!\
      Too high, position will drift, to low, there will be noise from accelerometer
      14-Jul-2017: loop time = 2.49ms. Gyro does not drift with coef =< 0.999
      timeCste = (coeff*dt)/(1-coeff)
       coeff = timeCste/(dt + timeCste) If we want 0.5sec, coeff = 0.5/(0.003 + 0.5) = 0.994
    */
    float HighPassFilterCoeff = 0.9995;//0.994;

    const float AcceleroSensitivity = 4096; // LSB/g at -+8g sensitivity
    const float GyroSensitivity = 32.8; // LSB/°/s  250=>131 or 500=>65.5 or 1000=>32.8 or 2000=>16.4

    bool offsetComputed = false;
    int16_t offset[6] = {0, 0, 0, 0, 0, 0};

  private:
    void GetCorrectedAccelGyro(MPU6050 _accelgyro, float _accMeasures[], float _gyroMeasures[]);
    void GetCorrectedGyro(MPU6050 _gyro, float _data[]);
    void Normalize( float _acc[] );
    bool IsVectorNormalized( float _acc[], float _epsilon );
    float PercentVectorNormalized( float _acc[]);
  public:
    float GetFilterTimeConstant(float _loopTime);
    bool AreOffsetComputed(void) {
      return offsetComputed;
    }
    void ComputeOffsets(MPU6050 _accelgyro);
    void GetCurrPos(MPU6050 _accelgyro, float _pos[], float _speed[], float _loop_time);
    void GetCurrSpeed(MPU6050 _accelgyro, float speedCurr[]);
};

