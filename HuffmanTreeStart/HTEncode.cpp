#include"HuffmanTree.h"
/*
�޸���־
1. �� 6.18
*/

//�ַ�����������c��Ӧ�����ݿ�����str��Ӧ���ַ����ռ��ֱ�������ļ�������Ϊֹ
void StrCopy(char *str, const char *c)//c��һ��ָ���ַ�������constָ��
{
	char *s = str;
	while (*c != '\0')//c�����ļ�������
		*s++ = *c++;//sָ�����cָ��ġ��Ƚ���*s=*c���ٷֱ��Լ�
	*s = '\0';//��������©���ļ�������
	return;
}

//���ã���l��r����������ΪȨֵ��С����������������
void WeightSelect(HuffmanTree T, int n, int &l, int &r)
//left��right
{
	HuffmanTree p = T + 1;//���
	int a = 0, b = 0, i;
	for (i = 1; i <= n; ++i, ++p)//С��
		//ע����<=n��n=256������ASCII�����n����
	{
	//p��������ôp++
		if (!p->parent)//���p�ǹ�����
		{
			if (!a)//���a��0.���ִֻ��1�Σ����Ǹ�left����ֵ
				//�Ѹ���ֵ���ŵ�ѭ���ڿ��Ա��⸳ֵʱ��l��r���ɲ������Ľ��
				//����һ����֮ǰ�Ķ����о��ܱ��⣬��Щ���һ��
			{
				l = i;
				a = 1;
			}
			else if (!b)//����Ļ����b��0��ͬ����Ǹ�r����ֵ
			{
				r = i;
				b = 1;
			}
			else if (p->weight < (T + l)->weight || p->weight < (T + r)->weight)
				//�������pָ���weightֵ��leftָ���С����
				//��rightָ���С����ô��
			{
				if ((T + l)->weight <= (T + r)->weight)
					r = i;
				else
					l = i;
				//��ǰ��else if�������£�����left��right��weightֵ������һ����p��ʱ
				//���left��weightֵ��right��С�Ļ����Ͱ�right��С
				//right��weightС�Ļ����Ͱ�left��С
				//��֮�����ǰ�ָ��weightֵ��ı�С
			}
		}
	}//�������н��
	return;
}

void HuffmanCoding(HuffmanTree &HT, HuffmanCode &HC, unsigned long *w, int n)
//ʹ��ʱw��weight���飬n��256����������ַ�����
{
	int f, c, start, m1, m2, i, m = 2 * n - 1;
	//m=2n-1�ĺ��壺����m+1���洢�ռ䣬ǰn�������洢��Щ�����ڵ�
	//����������洢Ϊ�˹����������������ӵ��½�㡣
	HuffmanTree p;//p��ָ�����ָ��
	HT = (HuffmanTree)malloc(sizeof(HTNode)*(m + 1));
	if (!HT)//�洢����ʧ��
	{
		printf("�洢����ʧ�ܣ�\n");
		exit(-1);
	}
	for (p = HT + 1, i = 1; i <= n; ++i, ++w, ++p)
		//���forѭ���������һ�ѹ����Ľ���¼Ȩֵ��Ϣ�Ľ�㣬�Ǳ���Ļ���
	{
		p->weight = *w;//���Ϸ���weight���鿴ͳ�Ƶ�ÿ���ַ��ĳ��ִ���
		p->parent = 0;
		p->lchild = 0;
		p->rchild = 0;
	}

	for (i = n + 1; i <= m; ++i, ++p)
		//���forѭ��������n+1 - m�Ľ��ȫ���ÿ�
	{
		p->weight = 0;
		p->parent = 0;
		p->lchild = 0;
		p->rchild = 0;
	}

	for (i = n + 1, p = HT + i; i <= m; ++i, ++p)//i��257��ʼ
		//Ҳ����˵������洢��һ�������ϣ�ǰ��n���ǳ�ʼ��㣬�������n+1��ʼ
		//���ǽ������õ�������㡣
	{
		WeightSelect(HT, i - 1, m1, m2);//Ѱ�ҵ�������С�Ĺ������
		p->weight = (HT + m1)->weight + (HT + m2)->weight;
		//���½ڵ��weightֵ��Ϊ֮ǰ������Сweightֵ֮��
		p->lchild = m1;//������
		p->rchild = m2;//������
		(HT + m1)->parent = i;//��������parent����i��Ҳ�����������
		(HT + m2)->parent = i;
	}
	HC = (HuffmanCode)malloc(sizeof(char*)*(n + 1));
	//����һ���洢����������������������
	//���²������ڸ�HC����������ݡ�
	if (!HC)
	{
		printf("�洢����ʧ�ܣ�");
		exit(-1);
	}
	char *cd = (char*)malloc(sizeof(char)*n);
	//cdΪָ��char���͵�ָ�롣�����������Ǹ����ָ�����n��char���͵Ĵ����ռ�
	//���µĽ����cd�൱��һ����n��Ԫ�ص�char���������������
	cd[n - 1] = '\0';//cd��������һ��Ԫ����Ϊ�ļ�������
	//����������Ա�֤����������˳������.leak.
	for (i = 1; i <= n; ++i)
	{
		start = n - 1;//���������һ����ʼ
		for (f = HT[i].parent, c = i; f != 0; c = f, f = HT[f].parent)
			//��f��Ϊi��˫��ֵ��c��1��ʼ��Ȼ�󽫱���Ϊ˫��ֵ
			//ֻҪ��˫�׾ͼ���ѭ����f���ϵ�����׷��
		{
			if (HT[f].lchild == c)//���������롣��Ϊ0����Ϊ1
				//�����������׷�������ӣ���ô�Ͷ�0
				cd[--start] = '0';
			else
				cd[--start] = '1';
		}
		HC[i] = (char*)malloc(sizeof(char)*(n - start));
		//ע��HC[]�����е�����Ԫ�ض���ָ��char����ָ�������ָ�룬
		//���仰˵��HC�����б�����һ������������Щ�����������������Ϊchar��������
		//����Щchar��������洢������ֻ��0��1���֣����ǵ�i��Ԫ��������Ļ���������
		StrCopy(HC[i], cd + start);
		//������õĻ��������뿽����HC[i]�С�
	}
	free(cd);
	return;
}

//�������������
void HuffmanCodeOutput(HuffmanCode C, int* s, int n)
{
	char *p;
	for (int i = 1; i <= n; ++i)
	{
		printf("Weight:%3d��Code:", s[i - 1]);
		p = C[i];
		while (*p != '\0')
			printf("%c", *p++);
		printf("\n");
	}
	return;
}

void EnCode(const char *s)
{
	FILE *pr, *pw;//read write
	int a, i = 0,  j, n = 256, m = 2 * n - 1,h;
	//��weight�����Ϊunsigned long����,�Ӷ����Ͻ�㶨�岢��ø���Ĵ洢
	unsigned long weight[256] = { 0 };
	HuffmanTree HT;
	HuffmanCode HC, hc;

	char CodedName[NAMESIZE], c = ' ';//NAMESIZE 500 127
	//NAMESIZEָ�ļ������ȣ�
	while (s[i] != '.')//�����ļ���չ��ǰ�� .
		//ѭ����s�����Ϊ�ļ���
	{
		CodedName[i] = s[i];
		i++;
	}
	//������ʱ��s[i]Ϊ'.'
	CodedName[i] = '.';
	CodedName[1 + i] = 'e';
	CodedName[2 + i] = 'n';
	CodedName[3 + i] = 'c';
	CodedName[4 + i] = '\0';//�ļ������ҲҪ���ļ�������

	pr = fopen(s, "rb");//������ֻ��
	if (!pr)
	{
		printf("���ļ�ʧ��\n");
		exit(-1);
	}

	a = fgetc(pr);//��ȡһ���ַ��ҹ�����һ���ֽ�
	while (!feof(pr))//���pr�����ļ�������
	{
		weight[a]++;//��ASCIIweight�����е���Ӧֵ����Ŀ��1
		a = fgetc(pr);//continue...
	}
	fclose(pr);//�ر��ļ�

	//���������ǵ�һ��ѭ���ļ�ͳ������


	HuffmanCoding(HT, HC, weight, 256);//�Լ�¼�����ݽ��б���

	pw = fopen(CodedName, "wb");//��ֻд�������ļ�

	//��д��ԭ��չ����ռ4���ֽڡ�����4���ÿո��롣
	j = 0;
	while (s[++i])//����/0���˳����ս���ѭ��ʱi�Ѿ���1�ˣ��˳�ʱs[i]='\0'
	{
		fwrite(s + i, 1, 1, pw);
		//д��s+iָ��ָ������ݡ��������д��չ����
		//ע�⣬δ����ѭ��ʱs[i]�� . ������ѭ����i��Ϊi+1����s+iָ�������չ����һ����ĸ
		//����ļ�������д�롣
		//д��1���ֽڣ�1��������ܹ�д��1*1=1���ֽ�
		//pw���ļ�ָ�롣
		j++;
	}
	//leak(need?)
	while (j++ < 4)//���j��4С����ôj+1��Ȼ�����ѭ��
		fwrite(&c, 1, 1, pw);

	for (i = n + 1; i <= m; i++)
	{
		fwrite(&((HT + i)->lchild), 2, 1, pw);
		fwrite(&((HT + i)->rchild), 2, 1, pw);
	}
	pr = fopen(s, "rb");//ֻ����ԭ�ļ���
	a = fgetc(pr);
	i = 0;
	int b = 0;
	hc = HC;
	char *p = *(hc + a + 1);//�ҵ���Ӧ�ı���
	//��ʱp��һ��������������洢���Ǳ���
	//leak
	while (!feof(pr) || *p != '\0')
		//�ļ�δ����||p��Ӧ�ı����0
	{
		for (i = 0; i < 8; i++)
		{
			if (*p == '\0')
			{
				a = fgetc(pr);
				//���ļ��ж�ȡһ���ַ���
				if (a >= 0)
					p = hc[a + 1];
				//���a��������ASCIIֵ����ô���ҵ�����Ӧ�ı������飬����������p��ʾ
				else
				{
					h = 1;
					for (j = 0; j < 8 - i; j++)
						h = h * 2;
					b = b * h;
					break;
				}
			}
			h = 1;
			//ɾ��int����
			for (j = 0; j < 7 - i; j++)
				h = h * 2;
			b = b + (*p - 48)*h;//ASCII�е�48Ϊ0
			//�����ȡ��ASCII�ַ�>=0����ô�ұߵ�b=0
			++p;
		}
		//�ڲ�forѭ������
		fwrite(&b, 1, 1, pw);
		b = 0;
	}//whileѭ������
	printf("EnCoding finished!\n");
	fclose(pr);
	fclose(pw);
	return;
}