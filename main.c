//����ͷ�ļ�
#include <reg51.h>//51��Ƭ��ͷ�ļ�
#include <absacc.h>//51��Ƭ���Ĵ���ͷ�ļ�


//�������
//������һ��8λ�����ݴ洢�������ڴ洢������ֵ
unsigned char code SEG[8] = 
{0x80,0x40,0x20,0x10,0x08,0x04,0x02,0x01};

//������һ��16��Ԫ�ص����飬���ڴ洢16���ַ��Ķ���
unsigned char code duan[16] =
{0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,
0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71};

//������һ��16��Ԫ�ص����飬���ڴ洢16���ַ��ļ���
unsigned char code change[16] = 
{0x11,0x21,0x41,0x81,0x12,0x22,0x42,0x82,
0x14,0x24,0x44,0x84,0x18,0x28,0x48,0x88
};

//������һ��8λ�����ݴ洢�������ڴ洢��ѧ�ţ�
int stu[8] = {2,4,4,1,1,5,4,6};


//���庯��
//��ʱ������������count����ʱ��ʱ�䣬����ֵ���ޣ����ܣ���ʱһ��ʱ��
void delay(int count)
{
	int i;
	for(i=1;i<=count;i++);
}

//��ʾ������������duan_num������ı�ţ�wei_num��λ��ı�ţ�����ֵ���ޣ����ܣ���ʾ�����λ��
void show(unsigned char duan_num, unsigned char wei_num)
{
	//�������
	XBYTE[0x8000] = wei_num;

	//��ʾ����
	XBYTE[0x9000] = duan[duan_num];

	//��ʱһ��ʱ��
	delay(20);

	//����
	XBYTE[0x9000] = 0x00;
}

//��ȡ�����������������ޣ�����ֵ�������ļ��룬���ܣ���ȡ�����ļ���
int	getkeycode(void)
{
	//�������
	unsigned char col = 0x00;
	unsigned char line = 0x00;
	unsigned char scancode = 0x01;
	unsigned char keycode;
	int	i;
	
	//��ȡ�����ļ���
	XBYTE[0x8000] = 0xff;

	//��ȡ����������
	col = XBYTE[0x8000]&0x0f;

	if(col == 0x00) return 16;
	else
	{
		while((scancode&0x0f) != 0)
		{
			line = scancode;
			XBYTE[0x8000] = scancode;
			if((XBYTE[0x8000]&0x0f) == col)
				break;
			scancode = scancode << 1;
		}
		col = col << 4;
		keycode = col|line;
	}
	for(i=0;i<16;i++)
	{
		if(keycode == change[i])
		{
			return i;
		}
	}
}
/*
//����������ˮ��
void	main(void)
{
	//�������
	int		j;
	int		i;
	unsigned char	num;
	//��ʾ����
	while(1)
	{
			for(j=0;j<8;j++)
			{
				num = getkeycode();
				if(num != 16)
					for(i=0;i<1200;i++)
						show(num, SEG[j]);
			}
	}
}
*/
/*
//��������ȫ����ʾ
void	main(void)
{
	//�������
	int		i;
	int		j;
	int		k = 0;
	unsigned char	num;
	//��ʾ����
	while(1)
	{
		for(i=0;i<250;i++)
		{
			num = getkeycode();
			for(j=0;j<1200;j++)
				show(num, SEG[j]);
		}
	}
}
*/

//����������ˮ����ʾѧ��
void	main(void)
{
	//�������
	int		i;
	int		j;
	int		k = 0;
	//��ʾ����
	while(1)
	{
		for(i=0;i<250;i++)
		{
			for(j=0;j<8;j++)
				show(stu[j], SEG[(j+k)%10]);
		}
		k++;
	}
}
//sdpd