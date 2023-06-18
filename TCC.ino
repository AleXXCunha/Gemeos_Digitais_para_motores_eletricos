/*
Trabalho de Graduação
Tema: Gêmeos Digitais para Motores Elétricos
Aluno: Alexandre Abrahami Pinto da Cunha
Matrícula: 18/0041169
*/

#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <ModbusRTU.h>
#include <DS18B20.h>

#define SLAVE_ID 1
#define KY038_PIN 4
#define DS18B20_PIN 5

Adafruit_MPU6050 mpu; //Cria um objeto Adafruit_MPU6050 chamado mpu para lidar com o sensor
ModbusRTU mb; 
DS18B20 temp(DS18B20_PIN); //Definindo o pino de entrada do sensor de temperatura DS18B20

unsigned int valor_anl;

void setup(void) {
  pinMode(KY038_PIN, INPUT); //Definindo o pino de entrada do sensor de som KY-038

  Serial.begin(115200, SERIAL_8N1); //Inicializa a comunicação serial com uma taxa de transmissão de 115200
  mb.begin(&Serial); 
  mb.slave(SLAVE_ID); //Definindo o endereço modbus
  mb.addHreg(0, 0);
  mb.addHreg(1, 0);
  mb.addHreg(2, 0);
  mb.addHreg(3, 0);
  mb.addHreg(4, 0);
  mb.addHreg(5, 0);
  mb.addHreg(6, 0);
  mb.addHreg(7, 0);
  mb.addHreg(9, 0);
  mb.addHreg(10, 0);
  mb.addHreg(11, 0);
  mb.addHreg(12, 0);
  mb.addHreg(13, 0);
  mb.addHreg(14, 0);

  mpu.begin(); //Inicializando o sensor MPU-6050
  mpu.setAccelerometerRange(MPU6050_RANGE_2_G); //Definindo a faixa de medição do acelerômetro
  mpu.setGyroRange(MPU6050_RANGE_250_DEG); //Definindo a faixa de medição do giroscópio
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ); //Definindo a largura de banda do filtro 
}

void loop() {

  ///////////////////////////////////////////////////////////////////////Sensor DS18B20////////////////////////////////////////////////////////////////////////////////////
  
  //Lendo o valor da temperatura do sensor DS18B20 e convertendo o resultado em 2 inteiros de 16 bits para enviar via protocolo Modbus
  float temperatura = temp.getTempC();
  uint32_t valor_temp = *((uint32_t*) &temperatura);
  uint16_t reg_temp1 = valor_temp >> 16;
  uint16_t reg_temp2 = valor_temp & reg_temp1;

  ///////////////////////////////////////////////////////////////////////Sensor KY-038////////////////////////////////////////////////////////////////////////////////////
  unsigned long startMillis = millis();                  
  unsigned int sinal_max = 0;                            
  unsigned int sinal_min = 1024;
  float sinal_do_som = 0;                         

  //Coleta informações do sensor por 50 mS
  while (millis() - startMillis < 50) {

    valor_anl = analogRead(KY038_PIN);
    if (valor_anl < 1024) {
      if (valor_anl > sinal_max) {
        sinal_max = valor_anl;                          
      } else if (valor_anl < sinal_min) {
        sinal_min = valor_anl;                           
      }
    }
  }

  sinal_do_som = sinal_max - sinal_min;
  int ruido = map(sinal_do_som, 0, 1023, 0, 90); //Mapeia a faixa de valores obtidos em decibéis    

  //////////////////////////////////////////////////////////////////////Sensor MPU-6050//////////////////////////////////////////////////////////////////////////////////

  //Obtendo novos eventos de sensor com as leituras
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp); 
  
  //Lendo o valor do acelerômetro no eixo x e convertendo o resultado em 2 inteiros de 16 bits para enviar via protocolo Modbus
  float acelerometro_x = a.acceleration.x;
  uint32_t valor_acelerometro_x = *((uint32_t*) &acelerometro_x);
  uint16_t reg_acelerometro_x1 = valor_acelerometro_x >> 16;
  uint16_t reg_acelerometro_x2 = valor_acelerometro_x & reg_acelerometro_x1;

  //Lendo o valor do acelerômetro no eixo y e convertendo o resultado em 2 inteiros de 16 bits
  float acelerometro_y = a.acceleration.y;
  uint32_t valor_acelerometro_y = *((uint32_t*) &acelerometro_y);
  uint16_t reg_acelerometro_y1 = valor_acelerometro_y >> 16;
  uint16_t reg_acelerometro_y2 = valor_acelerometro_y & reg_acelerometro_y1;

  //Lendo o valor do acelerômetro no eixo z e convertendo o resultado em 2 inteiros de 16 bits
  float acelerometro_z = a.acceleration.z;
  uint32_t valor_acelerometro_z = *((uint32_t*) &acelerometro_z);
  uint16_t reg_acelerometro_z1 = valor_acelerometro_z >> 16;
  uint16_t reg_acelerometro_z2 = valor_acelerometro_z & reg_acelerometro_z1;

  //Lendo o valor do giroscópio no eixo x e convertendo o resultado em 2 inteiros de 16 bits
  float gyro_x = g.gyro.x;
  uint32_t valor_gyro_x = *((uint32_t*) &gyro_x);
  uint16_t reg_gyro_x1 = valor_gyro_x >> 16;
  uint16_t reg_gyro_x2 = valor_gyro_x & reg_gyro_x1;

  //Lendo o valor do giroscópio no eixo y e convertendo o resultado em 2 inteiros de 16 bits
  float gyro_y = g.gyro.y;
  uint32_t valor_gyro_y = *((uint32_t*) &gyro_y);
  uint16_t reg_gyro_y1 = valor_gyro_y >> 16;
  uint16_t reg_gyro_y2 = valor_gyro_y & reg_gyro_y1;

  //Lendo o valor do giroscópio no eixo z e convertendo o resultado em 2 inteiros de 16 bits
  float gyro_z = g.gyro.z;
  uint32_t valor_gyro_z = *((uint32_t*) &gyro_z);
  uint16_t reg_gyro_z1 = valor_gyro_z >> 16;
  uint16_t reg_gyro_z2 = valor_gyro_z & reg_gyro_z1;

  //Armazenando o valor das variáveis nos registradores  
  mb.task();
  mb.Hreg(0, reg_acelerometro_x1);
  mb.Hreg(1, reg_acelerometro_x2);
  mb.Hreg(2, reg_acelerometro_y1);
  mb.Hreg(3, reg_acelerometro_y2);
  mb.Hreg(4, reg_acelerometro_z1);
  mb.Hreg(5, reg_acelerometro_z2);
  mb.Hreg(6, reg_gyro_x1);
  mb.Hreg(7, reg_gyro_x2);
  mb.Hreg(8, reg_gyro_y1);
  mb.Hreg(9, reg_gyro_y2);
  mb.Hreg(10, reg_gyro_z1);
  mb.Hreg(11, reg_gyro_z2);
  mb.Hreg(12, ruido);
  mb.Hreg(13, reg_temp1);
  mb.Hreg(14, reg_temp2);
  yield();
}