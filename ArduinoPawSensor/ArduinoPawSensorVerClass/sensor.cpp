#include "arduino.h"
#include <MsTimer2.h>
#include "sensor.h"

t_paw_state pawstat = CHARGE_1;

int led_1 = 2, led_2 = 3; // LED判定
void PawSensor::InitPawSensor() {
  pinMode(led_1, OUTPUT);
  pinMode(led_2, OUTPUT);

  MsTimer2::set(5, PawRead ); // 500msごとにオンオフ
  MsTimer2::start();
}


int paw1, paw2, paw3, paw4;
long int avg_paw1, avg_paw2, avg_paw3, avg_paw4; // 平均値
int ain1_v0, ain2_v0; // 入力値
uint16_t calibration_paw = 512; // キャリブレーション回数
long int fix_paw1, fix_paw2, fix_paw3, fix_paw4; // 修正値
int fix_value = 500; // 修正中央値

static void PawSensor::PawRead() {
  switch (pawstat) {
    case CHARGE_1:
      ain1_v0 = analogRead(A0);
      ain2_v0 = analogRead(A1);
      digitalWrite(led_1, HIGH);
      break;

    case READ_1:
      paw3 = analogRead(A0) - ain1_v0;
      paw4 = analogRead(A1) - ain2_v0;
      digitalWrite(led_1, LOW);
      paw3 -= fix_paw3;
      paw4 -= fix_paw4;
      break;

    case CHARGE_2:
      ain1_v0 = analogRead(A0);
      ain2_v0 = analogRead(A1);
      digitalWrite(led_2, HIGH);
      break;

    case READ_2:
      paw2 = analogRead(A0) - ain1_v0;
      paw1 = analogRead(A1) - ain2_v0;
      digitalWrite(led_2, LOW);
      paw1 -= fix_paw1;
      paw2 -= fix_paw2;
      break;
  }

  switch (pawstat) {
    case CHARGE_1:
      pawstat = READ_1;
      break;
    case READ_1:
      pawstat = CHARGE_2;
      break;
    case CHARGE_2:
      pawstat = READ_2;
      break;
    case READ_2:
      pawstat = CHARGE_1;
      break;
  }


  if (calibration_paw < 513) {
    if (calibration_paw > 0) {
      calibration_paw--;
      if (calibration_paw < 500) {
        avg_paw1 += paw1;
        avg_paw2 += paw2;
        avg_paw3 += paw3;
        avg_paw4 += paw4;
      }
    }
  }

  if (calibration_paw == 0) {
    avg_paw1 /= 500;
    avg_paw2 /= 500;
    avg_paw3 /= 500;
    avg_paw4 /= 500;

    fix_paw1 = avg_paw1 - 500;
    fix_paw2 = avg_paw2 - 500;
    fix_paw3 = avg_paw3 - 500;
    fix_paw4 = avg_paw4 - 500;

    calibration_paw = 513;
  }

  //  paw1 -= fix_paw1;
  //  paw2 -= fix_paw2;
  //  paw3 -= fix_paw3;
  //  paw4 -= fix_paw4;

  Serial.print(paw1);
  Serial.print(",");
  Serial.print(paw2);
  Serial.print(",");
  Serial.print(paw3);
  Serial.print(",");
  Serial.print(paw4);
  Serial.println();

  //debug1
  //    Serial.print(calibration_paw);
  //    Serial.print(",");
  //    Serial.print(avg_paw1);
  //    Serial.print(",");
  //    Serial.print(avg_paw2);
  //    Serial.print(",");
  //    Serial.print(avg_paw3);
  //    Serial.print(",");
  //    Serial.print(avg_paw4);
  //    Serial.print(",");
  //    Serial.println();


  //debug2
  //  Serial.print(fix_paw1);
  //  Serial.print(",");
  //  Serial.print(fix_paw2);
  //  Serial.print(",");
  //  Serial.print(fix_paw3);
  //  Serial.print(",");
  //  Serial.print(fix_paw4);
  //  Serial.print(",");
  //  Serial.println();
}
