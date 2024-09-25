#include <stdio.h>
#include <stdint.h>
#include <unistd.h>

#define BMP280_ADDRESS 0x76
#define TEMP_PRESS_CALIB_DATA_LEN 24
#define PRESSURE_OVERSAMPLING 1
#define TEMPERATURE_OVERSAMPLING 1
#define NORMAL_MODE 3


int32_t t_fine;
int32_t compensate_temperature(int32_t adc_T);
int32_t compensate_pressure(int32_t adc_P);

typedef struct {
    int16_t dig_T1;
    int16_t dig_T2;
    int16_t dig_T3;
    int16_t dig_P1;
    int16_t dig_P2;
    int16_t dig_P3;
    int16_t dig_P4;
    int16_t dig_P5;
    int16_t dig_P6;
    int16_t dig_P7;
    int16_t dig_P8;
    int16_t dig_P9;
} BMP280_CalibData;

void bmp280_init(BMP280_CalibData* calib){

    uint8_t buf[TEMP_PRESS_CALIB_DATA_LEN];
    
    for(int i = 0; i < TEMP_PRESS_CALIB_DATA_LEN; i++){
        buf[i] = bmp280_read(0x88 + i);
    }

    calib->dig_T1 = (buf[1] << 8) | buf[0];
    calib->dig_T2 = (buf[3] << 8) | buf[2];
    calib->dig_T3 = (buf[5] << 8) | buf[4];
    calib->dig_P1 = (buf[7] << 8) | buf[6];
    calib->dig_P2 = (buf[9] << 8) | buf[8];
    calib->dig_P3 = (buf[11] << 8) | buf[10];
    calib->dig_P4 = (buf[13] << 8) | buf[12];
    calib->dig_P5 = (buf[15] << 8) | buf[14];
    calib->dig_P6 = (buf[17] << 8) | buf[16];
    calib->dig_P7 = (buf[19] << 8) | buf[18];
    calib->dig_P8 = (buf[21] << 8) | buf[20];
    calib->dig_P9 = (buf[23] << 8) | buf[22];

    bmp280_write(0xF4,(PRESSURE_OVERSAMPLING<<2)|(TEMPERATURE_OVERSAMPLING<<5)|NORMAL_MODE);
}


int32_t compensate_temperature(int32_t adc_T,BMP280_CalibData* calib){

    int32_t var1; 
    int32_t var2;
    int32_t T;

    var1 = ((((adc_T>>3)-(calib->dig_T1<<1)))*(calib->dig_T2))>>11;
    var2 = (((((adc_T>>4)-(calib->dig_T1))*((adc_T>>4)-(calib->dig_T1)))>>12)*(calib->dig_T3))>>14;

    t_fine = var1+var2;
    T = (t_fine*5+128)>>8;

    return T;
}

int32_t compensate_pressure(int32_t adc_P,BMP280_CalibData* calib){
    int64_t var1,var2,p;

    var1 = ((int64_t)t_fine)-128000;
    var2 = var1*var1*(int64_t)calib->dig_P6;var2 = var2+((var1*(int64_t)calib->dig_P5)<<17);
    var2 = var2+(((int64_t)calib->dig_P4)<<35);

    var1 = ((var1*var1*(int64_t)calib->dig_P3)>>8)+((var1*(int64_t)calib->dig_P2)<<12);

    if(var1==0) 
    {
        return 0;
    }

    p = 1048576-adc_P;
    p = (((p<<31)-var2)*3125)/var1;
    var1 = (((int64_t)calib->dig_P9)*(p>>13)*(p>>13))>>25;
    var2 = (((int64_t)calib->dig_P8)*p)>>19;
    p = ((p+var1+var2)>>8)+(((int64_t)calib->dig_P7)<<4);return (int32_t)p;
}

uint8_t bmp280_read(uint8_t reg){
    uint8_t value = 0; // Dummy read, simula lectura
    printf("Leyendo registro: %x\n", reg);return value;
}

int32_t bmp280_read_raw_temp() {
    return (bmp280_read(0xFA)<<12)|(bmp280_read(0xFB)<<4)|(bmp280_read(0xFC)>>4);
}

void bmp280_write(uint8_t reg,uint8_t value){
    printf("Escribiendo %x en registro: %x\n", value, reg);
}

int32_t bmp280_read_raw_press(){
    return (bmp280_read(0xF7)<<12)|(bmp280_read(0xF8)<<4)|(bmp280_read(0xF9)>>4);
}

