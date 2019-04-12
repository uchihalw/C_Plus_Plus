#include "fix2ix.h"
int num_min = 0, num_max = 0;
// convert float data to int 
int_16 float2int_len16(float x)
{

	if (x >= 8.0) x = TRUNCATE;
	if (x <= -8.0) x = -8.0; //TRUNCATE * (-1.0);

	return FX2IX(x, DATA_Q_16);
}

int_32 float2int_len32(float x)
{
	return FX2IX(x, DATA_Q_32);
}

// convert int data to float .
float  int2float_len16(int_16 x)
{
	return IX2FX(x, DATA_Q_16);
}

float  int2float_len32(int_32 x)
{
	return IX2FX(x, DATA_Q_32);
}

// int data multi operation
int_32 int16_multi_len32(int_16 x, int_16 y)
{
	if ((x >> 15) & 0x1 == 0x1)
		x |= 0xffff0000;
	if ((y >> 15) & 0x1 == 0x1)
		y |= 0xffff0000;

	return x*y;
	/*
	int ix;
	int tmp;
	int exp;


	if(((x & 0x8000) >> 31) == 1)
	x = x | 0xffff0000;
	if(((y & 0x8000) >> 31) == 1)
	y = y | 0xffff0000;

	tmp = x * y;
	exp = tmp >> 2*DATA_Q_16;
	//	printf("int 16: x: 0x%x, y:0x%x \n", x, y);
	//	printf("exp: %d // 0x%x\t,max:%d,\tmin:%d\n",exp, exp, max,min);

	//Attention: (DATA_Q_16*2 - DATA_Q_32) maybe less than 0 !!!
	tmp = (exp << DATA_Q_32) | ((tmp & MULMASK) >> (DATA_Q_16*2 - DATA_Q_32));

	//ix = tmp >> DATA_Q_32;

	return tmp;
	*/
}


int_32 int16_add_len32(int_16 x, int_16 y)
{
	return x + y;
	/*
	int tmp = x + y;
	int exp = tmp >> DATA_Q_16;

	//printf("exp:%d\t,max:%d,\tmin:%d\n",exp, max,min);
	//printf("+ Musk:0x%x\n",ADDMASK);

	//Attention: (DATA_Q_16*2 - DATA_Q_32) maybe less than 0 !!!
	tmp = (exp << DATA_Q_32) | ((tmp & ADDMASK) << (DATA_Q_32 - DATA_Q_16));
	//	printf("exp:0x%x\t,max:%d,\tmin:%d\n",exp, max,min);

	return tmp;
	*/
}

int_32 int32_add_len32(int_32 x, int_32 y)
{
	int tmp = x + y;
	/*
	int exp = tmp >> DATA_Q_32;

	int max = (1 <<(32 - 1 - DATA_Q_32)) - 1;
	int min = - (1 <<(32 - 1 - DATA_Q_32)) + 1;
	//printf("exp:%d\t,max:%d,\tmin:%d\n",exp, max,min);
	//printf("+ Musk:0x%x\n",ADDMASK);
	if(exp > max)
	{
	printf("************int_add_len16****************max:%d\n", max);
	exp = max;
	}else if(exp < min){
	printf("************int_add_len16****************max:%d\n", max);
	exp = min;
	}

	//tmp = (exp << DATA_Q) | (tmp & ADDMASK) ;
	tmp = (exp << DATA_Q_32) | (tmp & 0xfffff);
	*/
	return tmp;
}

// int data subduction operation
int_32 int_sub_len16(int_16 x, int_16 y)
{
	int tmp = x - y;
	int exp = tmp >> DATA_Q_16;

	if (exp > LEN16_MAX)
	{
		exp = LEN16_MAX;
	}
	else if (exp < LEN16_MIN) {
		exp = LEN16_MIN;
	}

	tmp = (exp << DATA_Q_16) | (tmp & ADDMASK);

	return tmp;
}

// using
int_16 int32_to_int16(int_32 x)
{
	int exp = (x >> DATA_Q_32) & 0x3f;
	int fraction = (x >> (DATA_Q_32 - DATA_Q_16)) & 0xfff;
	int flag = (x >> 30) & 0x1;  // refer to HW design

	int res = 0;

	if ((flag == 0x0) && (exp > LEN16_MAX))
	{
		exp = LEN16_MAX; //MAX:7.99999
		fraction = 0xfff;

	}
	else if ((flag != 0x0) && (exp < 0x38)) {
		exp = 0; // MIN: -8.0
		fraction = 0;
	}
	else
		exp &= 0x7;

	if (flag != 0x0)
		flag = 0xffffffff;

	res = (flag << 15) | (exp << DATA_Q_16) | fraction;

	//if(flag != 0x0)
	//printf("## x:0x%x, res:0x%x, exp:0x%x, fraction:0x%x ##\n",x,res, exp, fraction);

	return res;

	/*
	int exp = x >> DATA_Q_32;

	int tmp = (x & 0xfffff) >> (DATA_Q_32 - DATA_Q_16);

	if(exp > LEN16_MAX)
	{
	exp = LEN16_MAX;
	}else if(exp < LEN16_MIN){
	exp = LEN16_MIN ;   /// TODO: ERR!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	tmp = 0x1;    //
	}

	x = (exp << DATA_Q_16)| tmp;
	//printf("exp1: %d / 0x%x\t,max:%d,\tmin:%d, x:0x%d\n", exp,exp, max,min, x);

	return x;
	*/
}


int_16 int32_to_int16_new(int_32 x)
{
	int exp = x >> 2 * DATA_Q_16;

	int flag = 0;
	int tmp = (x & 0xffffff) >> (DATA_Q_16);

	if (exp > LEN16_MAX)
	{
		exp = LEN16_MAX;
	}
	else if (exp < LEN16_MIN) {
		//printf("###### x:0x%x, tmp:0x%x, exp:0x%x\n",x,tmp, exp);
		exp = LEN16_MIN;   /// TODO: ERR!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		tmp = 0;    // 
	}

	x = (exp << DATA_Q_16) | tmp;
	if (0)
		printf("exp1: %d / 0x%x, x:0x%x\t, tmp:0x%d\n", exp, exp, x, tmp);
	printf("####### Not used yet##########\n");
	return x;
}
//exp:0xb
//exp1: 7 / 0x7, x:0x7053 , tmp:0x83

int_32 int16_to_int32(int_16 x)
{
	int exp = x >> DATA_Q_16;

	x = (exp << DATA_Q_32) | ((x & ADDMASK) << (DATA_Q_32 - DATA_Q_16));

	return x;
}

// int data division operation
int int_div_len16(float x, float y)
{
	int mul = 1;
	int ix = FX2IX(x, DATA_Q_16);
	int iy;
	int z;
	float fx;
	if (y < 0.001)
	{
		mul = 10000;
	}
	else if (y >= 0.001 && y <= 0.1)
	{
		mul = 1000;
	}

	iy = FX2IX(y * mul, DATA_Q_16);

	z = (ix << DATA_Q_16) / iy;

	fx = IX2FX(z, DATA_Q_16);

	ix = FX2IX(fx*mul, DATA_Q_16); //定点结果  ix = fx * mul

	return ix;  // 浮点结果
}

// int data division operation
int_32 int_div_len32(int_32 x, int_32 y)
{
	long temp = (long)x;
	int_32 z = (temp << DATA_Q_32) / y;

	return z;  // 浮点结果
}

// int data multi operation
int_32 int32_multi_len32(int_32 x, int_32 y)
{
	/*
	int ix;
	long long int  tmp = x * y;

	int exp = (int)(tmp >> 2*DATA_Q_32) & 0xfff;

	long long int  point = tmp & 0xfffff00000;
	int  res = (int)((point >> DATA_Q_32) & 0xfffff);

	//int max = (1 <<(32 - 1 - DATA_Q_32)) - 1;
	//int min = - (1 <<(32 - 1 - DATA_Q_32)) + 1;


	printf("exp:0x%x\t,points:0x%lx, tmp:0x%lx, res:0x%x\n",exp, point, tmp,res);


	//Attention: (DATA_Q_16*2 - DATA_Q_32) maybe less than 0 !!!
	res = (exp << DATA_Q_32) | res;


	return res;
	*/
	printf("TODO: waiting for fix yet\n");
	return 0;
}


// 2018/10/17
// int data add operation
int_16 int16_add_len16(int_16 x, int_16 y)
{

	if ((x >> 15) & 0x1 == 0x1)
		x |= 0xffff0000;
	if ((y >> 15) & 0x1 == 0x1)
		y |= 0xffff0000;


	int tmp = x + y;

	int exp = tmp >> DATA_Q_16;
	int mant = tmp & ADDMASK;


	//printf("exp:%d\t,max:%d,\tmin:%d\n",exp, LEN16_MAX,LEN16_MIN);
	if (exp > LEN16_MAX)
	{
		exp = LEN16_MAX;
		mant = ADDMASK;
		//num_max ++;
	}
	else if (exp < LEN16_MIN) {
		exp = LEN16_MIN;
		mant = 0;
		//num_min ++ ;
	}

	//printf("##### tmp:0x%x, exp:0x%x, mant:0x%x\n",tmp,exp, mant);

	tmp = (exp << DATA_Q_16) | mant;

	//printf("##### tmp:0x%x, x:0x%x, y:0x%x\n",tmp, x, y);

	return tmp;



}


// int data multi operation
int_16 int16_multi_len16(int_16 x, int_16 y)
{
	int tmp;
	int exp;
	int mant;
	int sign;

	if ((x >> 15) & 0x1 == 0x1)
		x |= 0xffff0000;
	if ((y >> 15) & 0x1 == 0x1)
		y |= 0xffff0000;

	tmp = x * y;
	exp = tmp >> 2 * DATA_Q_16;
	mant = (tmp & MULMASK) >> DATA_Q_16;
	sign = (tmp >> 30) & 0x1;

	//printf("/ Musk:0x%x\n",MULMASK);
	if (exp > LEN16_MAX)
	{
		exp = LEN16_MAX;
		mant = MULMASK >> DATA_Q_16;
	}
	else if (exp <= LEN16_MIN) {
		exp = LEN16_MIN;
		mant = 0x0;
	}
	// printf("mul exp:0x%x\t,max:%d,\tmin:%d\n",exp, LEN16_MAX,LEN16_MIN);

	tmp = (exp << DATA_Q_16) | mant | (sign << 15);

	return tmp;

}

int_16 int32_to_int16_new_new(int_32 x)
{
	int tmp;
	int sign = x >> 31;
	int exp = (x & 0x3f000000) >> 2 * DATA_Q_16;
	int fraction = x & 0x00fff000;

	tmp = exp >> 3;

	fraction = fraction >> DATA_Q_16;

	//	int flag = 0;
	/*	if(x == 0xb053e2e){
	flag =1;
	printf("%s: exp:0x%x,sign:0x%x, tmp:0x%x\n",__FUNCTION__,exp,sign,tmp);
	}*/

	//if((x & 0x80000000) == 0x80000000)
	//	printf("%s: exp:0x%x,sign:0x%x, tmp:0x%x, fraction:0x%x \n",__FUNCTION__,exp,sign,tmp,fraction);


	int res = 0;
	if ((sign == 0x0) && (tmp != 0x0))
	{
		exp = LEN16_MAX;
		fraction = 0xfff;
	}
	else if ((sign != 0x0) && (tmp != 0x7))
	{
		exp = 0x0;
		fraction = 0x0;
	}
	else {
		exp = exp & 0x7;
	}

	res = (((exp << DATA_Q_16) | fraction)) | (sign << 15);

	//if(sign != 0)
	//	printf("## x:0x%x, res:0x%x, exp:0x%x, fraction:0x%x, sign:0x%x ##\n",x,res, exp, fraction, sign);

	printf("####### Not used yet...##########\n");

	return res;

}
