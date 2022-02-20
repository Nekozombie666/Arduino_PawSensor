#ifndef SENSOR_H_
#define SENSOR_H_

class PawSensor {
  public:
    static void InitPawSensor();
    static void PawRead();

    //private:

};

typedef enum {
  CHARGE_1,
  READ_1,
  CHARGE_2,
  READ_2,
} t_paw_state;




#endif /* SENSOR_H_ */
