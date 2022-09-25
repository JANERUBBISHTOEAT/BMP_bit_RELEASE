#include <cstdio>
#include <cmath>
#include <cstring>
#include <cstdlib>
#include <cctype>
using namespace std;
bool a[1500][1500];//2d map
bool ans[1500*1500];//2d -> 1d
char fin[1500*1500];//input
unsigned char ttemp[7];




void itoh(int x)//turn x into hex & sort to small-.
{
	ttemp[0] = (x & 0x00ff);
	ttemp[1] = (x & 0xff00) >> 8;
	ttemp[2] = (x & 0x00ff0000) >> 16;
	ttemp[3] = (x & 0xff000000) >> 24;
}

int main() 
{
	freopen ("in.txt", "r", stdin);
//	FILE *fp = fopen("in.txt", "rb");
	char tmp;
	int cnt = 0;
	int val = 0;
	int size = 0;
	int x, y = 0;
	int pad = 0;
	
	while ((fin[size++] = getchar()) != EOF);//read all
	size--; // to remove the -1\377(EOF), which is not inluded when to_BIN
	
	
	for (int i = 0; i < size; i++)//write
	{
		val = (int)(fin[i]);
		cnt = cnt + 8;
		for (int j = 1; j <= 8; j++)// int to bin
		{
			ans[cnt - j] = val % 2;
			val = val / 2;
		}//putchar (' ');
	}
	putchar ('\n');

	FILE *fp = fopen("OUT.BMP", "wb");
	
	

	x = y = ceil(sqrt(size*8));
	size = x * y;
	printf ("size = %6d\n%4d x %4d\n\n", size, x, y);
		pad = (ceil(y * 3 / 4.0) * 4);
		size = x * pad;
	printf ("size = %6d (real)\n%4d*3 x %4d (byte)\n\n", size, x, pad);


	//write bmp file head
	
	
	
	unsigned char head[60] = {0x42,0x4D,0xE8,0xE5,0x00,0x00,0x00,0x00,0x00,0x00,0x36,0x00,0x00,0x00};//1-D.


	head[14] = 0x28;
	head[15] = 0x00;
	head[16] = 0x00;
	head[17] = 0x00;



	itoh(x);
	printf ("Height:\n");
	for (int i = 0; i < 4; i++) printf ("%4d -> %02X \n", ttemp[i],ttemp[i]);
	putchar ('\n');
	for (int i = 4; i < 8; i++)
	{
		head[18+i] = /*(unsigned char)*/ttemp[i-4];
	}
	
	
	itoh(y);
	printf ("Width:\n");
	for (int i = 0; i < 4; i++) printf ("%4d -> %02X \n", ttemp[i],ttemp[i]);
	putchar ('\n');
	for (int i = 0; i < 4; i++)
	{
		head[18+i] = /*(unsigned char)*/ttemp[i];
	}
	
	
	unsigned char trtmp[30] = {0x01,0x00,/*0100 ==> 0001, 1A-1B.*/	0x00,0x00,/*0018=24,color. 1C-1D.*/0x00,0x00,0x00,0x00,/*0. no zip. 1E-21.*/0xB2,0xE5,/*???*/0x00,0x00,0x00,0x00,/*. no use. 22-25.*/0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,/*0. null. 26-2D.*/0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};//0. null. 2E-35.
	for (int i = 0; i < 28; i++)
	{
		head[26+i] = trtmp[i];
	}
//	strcat (head, trtmp);
//	memset (temp, 0x00, sizeof (temp));

	itoh (x * pad);
	printf ("BYTEs: %d\n\n", x*pad);
	for (int i = 0; i < 4; i++)//Bitmap Data Size
	{
		head[34+i] = ttemp[i];
	}
	
	head[28] = 0x18;//bits per pixel9
	itoh (x * pad + 54);
	for (int i = 0; i < 4; i++)//File Size
	{
		head[2+i] = ttemp[i];
	}
	printf ("File size: %d\n\n", x*pad+54);
//	puts ((char)*head);
	
//	printf ("%s", head);

//	fclose (fp);
	printf ("Head:\n");
	for (int i = 0; i < 54; i++)
		printf ("%2X ", head[i]);
	putchar ('\n');
	for (int i = 0; i < 54; i++)
		printf ("%2X ", i);
//	freopen ("OUT.BMP", "w", stdout);//FAILED 'cause there was no fclose...
//	puts (head);
//	printf ("%s", head);//------------------------------------WRONG
//	for (int i = 0; i < 54; i++)
//	{
////		printf ("%c", head[i]);
//		fprintf (fp, "%", head[i]);
//	}
	fwrite (head, 1, 54, fp);
	putchar('\n');
//	for (int i = 0; i < 54; i++)
//		printf ("%2X ", head[i]);
//	fclose (stdout);//wrong!
//	freopen("CON", "w", stdout);//file-->console
//	fp = fopen("OUT.BMP", "w");
	putchar ('\n');
	putchar ('\n');

	for (int i  = 0; i < x; i++)
	{
		for (int j = 0; j < y; j++)
		{
			a[i][j] = ans[i*x+j];
//			printf ("%d", ans[i*x+j]);
		}//putchar ('\n');
	}

//	putchar ('\n');
//	putchar ('\n');
	printf ("BITMAP:\n");

	int _debugging = 0; // if print debug info

	fpos_t position;
	_debugging ? fgetpos(fp, &position) : 0;

	// printf ("This version cancelled the \'BITMAP Print\' function due to large file input");
	for (int i  = x-1; i > -1; i--)//read
	{
		for (int j = 0; j < y; j++)
		{
//			fprintf (fp, "%c", a[i][j] ? 0xff : 0x00);
			unsigned char value = (a[i][j]) ? 0xff : 0x00;
			fwrite (&value, 1, 1, fp);
			fwrite (&value, 1, 1, fp);
			fwrite (&value, 1, 1, fp);
			_debugging ? fgetpos(fp, &position) : 0;
			_debugging ? printf ("%d", value ? 1 : 0) : 0;
		}
		for (int k = y * 3; k < pad; k++)
		{
			unsigned char value = 0x00; // 0xAA is gray
   			fwrite (&value, 1, 1, fp);
			_debugging ? fgetpos(fp, &position) : 0;
			_debugging ? printf ("X") : 0;
		}

		_debugging ? fgetpos(fp, &position) : 0;
		_debugging ? putchar ('\n') : 0;
	}
	// Get pos
	_debugging ? fgetpos(fp, &position) : 0;

	fclose (fp);


	fp = fopen("OUT.BMP", "r");
	fseek(fp, 54, SEEK_SET);
	
	// 4 bytes align
	double y_double = (double)y;
	int y_real = ceil(24 * y_double / 32) * 4;
	int y_delta = y_real - y * 3;

	for (int i  = x-1; i > -1; i--)//read checked OK
	{
		_debugging ? fgetpos(fp, &position) : 0;
		for (int j = 0; j < y; j++)
		{	
			fread(&tmp, 1, 1, fp);
			fread(&tmp, 1, 1, fp);
			fread(&tmp, 1, 1, fp);
			printf ("%d", tmp ? 1 : 0);
			_debugging ? fgetpos(fp, &position) : 0;
		}
		// 4 bytes align
		for (int k = 0; k < y_delta; k++)
		{
			fread(&tmp, 1, 1, fp);
			printf ("X");
		} putchar ('\n');
		_debugging ? fgetpos(fp, &position) : 0;
	} fclose (fp);
	return 0;
}
