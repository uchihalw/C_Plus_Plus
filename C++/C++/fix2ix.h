#pragma once
#ifndef FLOAT_TO_FIX_H
#define FLOAT_TO_FIX_H

//#pragma once

#define DATA_Q_16 12 //定标 16bit: 1/3/12
#define DATA_Q_32 2*DATA_Q_16 //     32bit: 1/11/20

typedef int int_16;
typedef int int_32;

#define FX2IX(X,Y)  (int)(X * (2 << (Y-1))) // 浮转定

#define IX2FX(X,Y)  (((float)X) * (1/((2 << (Y-1))*1.0))) //定转浮

#define MULMASK      0xffffff //(0xffffffff >> (32 - 2*DATA_Q_16) )

#define ADDMASK      0xfff //(0xffffffff >> (32 - DATA_Q_16) )

#define APPROXI 0  //是否对input、weights、bias小数点后的进行四舍五入
#define DIVISOR 10000 // bits to remain

#define LEN16_MAX  (1 <<(16 - 1 - DATA_Q_16)) - 1
#define LEN16_MIN  - (1 <<(16 - 1 - DATA_Q_16))



// truncate only with float
#define TRUNC_OUTPUT 0
#define TRUNC_WEIGHT 0
#define TRUNC_BIAS 0
#define TRUNCATE 7.9999 // truncate range




#define PRECISION 0.005  //weights precison


#define MULITI  1
#define BUTTON  0 // if button equal 0, program multi the MULITI for every layer of network

// convert float data to int 
int  float2int_len16(float x);

int_32 float2int_len32(float x);

// convert int data to float 
float  int2float_len16(int x);

float  int2float_len32(int_32 x);

// int16 data multi operation
int_32 int16_multi_len32(int_16 x, int_16 y);


// int32 data multi operation
int_32 int32_multi_len32(int_32 x, int_32 y);

// int16 data add operation
int_32 int16_add_len32(int_16 x, int_16 y);

// int32 data add operation
int_32 int32_add_len32(int_32 x, int_32 y);

// int32 to int16 operation
int_16 int32_to_int16(int_32 x);
int_16 int32_to_int16_new(int_32 x);

// int16 to int32 operation
int_32 int16_to_int32(int_16 x);

// int data division operation
int int_div_len16(float x, float y);

int_32 int_div_len32(int_32 x, int y);

// 2018/10/17
// int data multi operation
int_16 int16_multi_len16(int_16 x, int_16 y);

// int data add operation
int_16 int16_add_len16(int_16 x, int_16 y);


int_16 int32_to_int16_new_new(int_32 x);

#endif
