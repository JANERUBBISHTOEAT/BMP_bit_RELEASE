#include <cstdio>
#include <stdlib.h>
#include <cmath>

// For Debugging
bool a[150][150];//2d map
bool ans[150*150];//2d -> 1d
char fin[150*150];//output 

// bool a[1500][1500];//2d map
// bool ans[1500*1500];//2d -> 1d
// char fin[1500*1500];//output 

char booltochar(bool *bridge) {
	// Original Code
	char c = (int)0;
	int i;
	for (i = 128; i; i /= 2) {
		if (*bridge) {
			c += (char)i;
		} bridge++;
	}
	return (char) c;
}
int htoi(unsigned char num[]) {//8C 00 00 00 ->  0x8C
	int res = 0;
	res += num[0];
	res += num[1] << 8;
	res += num[2] << 16;
	res += num[3] << 24;
	return res;
}


int main() 
{
	freopen ("in.bmp", "rb", stdin);
	FILE *fp = fopen("in.bmp", "rb");
	unsigned char tmp;
//	unsigned char temp[] = {};
	int cnt = 0;
	int x, y, size;//x:height, y:width
	int bit_per = -1;
	unsigned char head[60], temp[60];
//	unsigned char *temp = (unsigned char*)malloc(60);
//	unsigned char temp[] = {140,0,0,0};
//	printf ("%d", htoi (temp));
	for (int i = 0; i < 54; i++)//get head
	{
		head[i] = getchar();
	}
	
	for (int i = 0; i < 4; i++) temp[i] = head[28+i]; 
	bit_per = htoi(temp) / 8;//bits / 8 = BYTEs
	
	for (int i = 0; i < 4; i++) temp[i] = head[18+i];
	y = htoi (temp);//width
	for (int i = 0; i < 4; i++) temp[i] = head[22+i];
	x = htoi (temp);//higeht
	printf ("%d x %d\n", x, y);
	
	
	
	
	
	for (int i = 0; i < 4; i++)
	{
		temp[i] = head[10+i];
//		printf ("\n%d: %d\n", i, x);
	}
	
	
	
	fseek(fp, htoi (temp), 0);//Bitmap Data Offset
	
	// 4 byte align
	double y_double = (double)y;
	int y_real = ceil(24 * y_double / 32) * 4;
	int y_delta = y_real - y * 3;

	for (int i  = x-1; i > -1; i--)
	{
		for (int j = 0; j < y; j++)
		{
			// fread(&tmp, 1, 1, fp);
			// fread(&tmp, 1, 1, fp);
			fread(temp, bit_per, 1, fp);//unexpected change of 'x' occured!!!!-------------------------
			a[i][j] = (int)temp[0];
//			printf ("(%d,%d)=%d ", i, j, a[i][j]);
		}
		// 4 byte align
		for (int j = 0; j < y_delta; j++)
		{
			fread(&tmp, 1, 1, fp);
		}
	}
	cnt = 0;
	for (int i  = 0; i < x; i++)
	{
		for (int j = 0; j < y; j++)
		{
			ans[i*x+j] = a[i][j];
			printf ("%d", a[i][j]);
		} putchar ('\n');
	}
	freopen ("OUT.TXT", "w", stdout);
	
	for (int i = 0; i < x * y / 8/*19600/8*/; i++)
	{
		fin[i*8] = booltochar(&ans[i*8]);
		printf ("%c", fin[i*8]);
	}
	
	return 0;
}
