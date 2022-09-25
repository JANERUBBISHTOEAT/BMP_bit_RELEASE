#include <cstdio>
bool a[150][150];//2d map
bool ans[150*150];//2d -> 1d
char fin[150*150];//output 
char booltochar(bool *bridge) {
	char c = (int)0;
	int i;
	for (i = 128; i; i /= 2) {
		if (*bridge) {
			c += (char)i;
		} bridge++;
	}
	return c;
}
int main() 
{
//	freopen ("in.bmp", "r", stdin);
	FILE *fp = fopen("in.bmp", "rb");
	char tmp;
	int cnt = 0;
	
	fseek(fp, 54, 0);
	for (int i  = 139; i > -1; i--)
	{
		for (int j = 0; j < 140; j++)
		{
//			fread(&tmp, 1, 1, fp);
//			fread(&tmp, 1, 1, fp);
			fread(&tmp, 1, 3, fp);
			a[i][j] = (int)tmp;
//			printf ("(%d,%d)=%d ", i, j, a[i][j]);
		}
	}
	cnt = 0;
	for (int i  = 0; i < 140; i++)
	{
		for (int j = 0; j < 140; j++)
		{
			ans[i*140+j] = a[i][j];
			printf ("%d", a[i][j]);
		}putchar ('\n');
	}
	freopen ("OUT.TXT", "w", stdout);
	for (int i = 0; i < 19600/8; i++)
	{
		fin[i*8] = booltochar(&ans[i*8]);
		printf ("%c", fin[i*8]);
	}
	
	return 0;
}
