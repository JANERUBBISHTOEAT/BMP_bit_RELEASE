#include <cstdio>
#include <cmath>
#include <cstring>
#include <cstdlib>
#include <cctype>
using namespace std;
bool a[1500][1500];//2d map
bool ans[1500*1500];//2d -> 1d
char fin[1500*1500];//input
unsigned char ttemp[8];
//void ChtoHex(byte Val, char* dest)
//{
//    // 辗转相除法，倒序看得到结果
// 
//    byte tmp = Val % 16;
//    if (tmp >= 0 && tmp <= 9)
//    {
//        dest[1] = '0' + tmp;
//    }
//    else if (tmp >= 10 && tmp <= 15)
//    {
//        dest[1] = 'A' + tmp - 10;
//    }
// 
//    tmp = (Val/16) % 16;
//    if (tmp >= 0 && tmp <= 9)
//    {
//        dest[0] = '0' + tmp;
//    }
//    else if (tmp >= 10 && tmp <= 15)
//    {
//        dest[0] = 'A' + tmp - 10;
//    }
// 
//    // 设置'\0'
//    dest[2] = '\0';
//}


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
	putchar ('\n');
	putchar ('\n');

	FILE *fp = fopen("OUT.BMP", "w");
	
	
	
	x = y = ceil(sqrt(size*8));
	if (x % 2)
	{
		x = y= (ceil(x / 2.0) * 2);
		size = x * y;
	}


	printf ("size = %6d\n%4d x %4d\n\n", size, x, y);
	//write bmp file head
	
	
	
	unsigned char head[60] = {0x42,0x4D,0xE8,0xE5,0x00,0x00,0x00,0x00,0x00,0x00,0x36,0x00,0x00,0x00};//1-D.
	char temp[] = {0x28,0x00,0x00,0x00};//E-11.
//	strcat (head, temp); memset (temp, 0x00, sizeof (temp));
	head[14] = 0x28;
	head[15] = 0x00;
	head[16] = 0x00;
	head[17] = 0x00;
//	
//	_itoa(x, temp, 16);
//	int len = strlen(temp);
	
//	unsigned char ttemp[8];
//	for (int i = 0; i < len; i+=2)//--------------------------------------
//	{
//		if (isdigit(temp[len-i-2])) 
//		{
//			ttemp[i] = temp[len-i-2] - '0';
//		}
//		else ttemp[i] = temp[len-i-2]-'a'+10;
//	}
//	for (int i = 1; i <= len; i+=2)//--------------------------------------
//	{
//		if (isdigit(temp[len-i])) 
//		{
//			ttemp[i] = temp[len-i] - '0';
//		}
//		else ttemp[i] = temp[len-i]-'a'+10;
//	}
//	for (int i = 0; i < 4; i++)//transform '8''c' --> 0x8c
//	{
//		ttemp[i] = (ttemp[i*2] << 4) + (ttemp[i*2+1]);
//	}
	memset (temp, 0x00, sizeof (temp));
	itoh(x);
	for (int i = 0; i < 4; i++) printf ("%4d -> %02X \n", ttemp[i],ttemp[i]);
	putchar ('\n');
//	strcat (head, ttemp);//12-15.
//	strcat (head, ttemp);//16-19.
	for (int i = 0; i < 4; i++)
	{
		head[18+i] = /*(unsigned char)*/ttemp[i];
	}
	for (int i = 4; i < 8; i++)
	{
		head[18+i] = /*(unsigned char)*/ttemp[i-4];
	}
	memset (temp, 0x00, sizeof (temp));
//	temp[] = {0x00,0x01,0x00,0x00,/*0100 ==> 0001, 1A-1B.*/	0x18,0x00,/*0018=24,color. 1C-1D.*/0x00,0x00,0x00,0x00,/*0. no zip. iE-21.*/0x00,0x00,0x00,0x00,/*. no use. 22-25.*/0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,/*0. null. 26-2D.*/0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};//0. null. 2E-35.
	unsigned char trtmp[] = {0x01,0x00,/*0100 ==> 0001, 1A-1B.*/	0x00,0x00,/*0018=24,color. 1C-1D.*/0x00,0x00,0x00,0x00,/*0. no zip. 1E-21.*/0xB2,0xE5,/*???*/0x00,0x00,0x00,0x00,/*. no use. 22-25.*/0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,/*0. null. 26-2D.*/0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};//0. null. 2E-35.
	for (int i = 0; i < 28; i++)
	{
		head[26+i] = trtmp[i];
	}
//	strcat (head, trtmp);
	memset (temp, 0x00, sizeof (temp));
	itoh (x * x);
	printf ("BYTEs: %d\n\n", x * x);
	for (int i = 0; i < 4; i++)
	{
		head[34+i] = ttemp[i];
	}
//	head[38] = 0x12;
//	head[39] = 0x0B;
//	head[42] = 0x12;
//	head[43] = 0x0B;
	
	head[28] = 0x01;//bits per dist. Seems that isnt working....
	itoh (x * x + 53);
	for (int i = 0; i < 4; i++)
	{
		head[2+i] = ttemp[i];
	}//	head[46] = 1;
//	puts ((char)*head);
	
//	printf ("%s", head);

//	fclose (fp);
	printf ("Head:\n");
	for (int i = 0; i < 54; i++)
	{
		printf ("%c", head[i]);
	}
	freopen ("OUT.BMP", "w", stdout);
//	puts (head);
//	printf ("%s", head);//------------------------------------WRONG
	for (int i = 0; i < 54; i++)
	{
		printf ("%c", head[i]);
		fprintf (fp, "%c", head[i]);
	}
//	fclose (stdout);//wrong!
	freopen("CON", "w", stdout);//file-->console
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
	for (int i  = x-1; i > -1; i--)//read
	{
		for (int j = 0; j < y; j++)
		{
//			printf("%d", a[i][j]);
			fprintf (fp, "%c", a[i][j] ? 0xff : 0x00);
//			fprintf (fp, "%c", a[i][j] ? 0xff : 0x00);
//			fprintf (fp, "%c", a[i][j] ? 0xff : 0x00);
			printf ("%d", a[i][j] ? 1 : 0);
//			fwrite(&a[i][j], 1, 3, fp);// ( const void * ptr, size_t size, size_t count, FILE * stream );
		} putchar ('\n');
	}
//			putchar ('\n');putchar ('\n');putchar ('\n');
//			fclose(fp);
//			fp = fopen("OUT.BMP", "r");

//	for (int i  = x-1; i > -1; i--)//read checked OK
//	{
//		for (int j = 0; j < y; j++)
//		{
//			fread(&tmp, 1, 3, fp);
//			printf ("%d", (int)tmp);
//		}putchar ('\n');
//	}
	
	
	fclose (fp);
	return 0;
}
