#include<stdio.h>
#include<windows.h>
#include <stdlib.h>
#include<time.h>
#include<string.h>

#define MAX 512 //运算中的最高可能位数
#define NUMP 2 //已提供的素数个数
#define NUMG 50 //随机数g的位数
#define swap1(x,y) x^=y^=x^=y


static const char p_set[NUMP][110] =
{
    {"3383489120380959248493525538580021146558530486980451874557556432721233835930146323754645777760514961"},
    {"3383489120380959248493525538580021146558530486980451874557556432721233835930146323754645777760514963"}
};

int get_n(char* a)
{
    int i = MAX - 2;
    while (i >= 0 && !a[i]) {
        i--;
    }
    return i + 1;
}
int get_mul(char* a, char* b)
{
    int na, nb, i, j, n;
    char c[MAX], d[MAX];
    for (i = 0; i < MAX; i++)c[i] = a[i], d[i] = b[i], a[i] = 0;
    na = get_n(c);
    nb = get_n(d);
    for (i = 0; i < nb; i++)for (j = 0; j < na; j++)
    {
        a[i + j] += d[i] * c[j];
        if (a[i + j] > 9)a[i + 1 + j] += a[i + j] / 10, a[i + j] %= 10;
    }
    for (i = 0; i < MAX && i < (na + nb); i++)
    {
        if (a[i])n = i + 1;
        if (a[i] > 9)a[i + 1] += a[i] / 10, a[i] %= 10;
    }
    return n;
}
int get_mod(char* a, char* b)
{
    int na, nb, i, u, f = 0, n = 0;
    na = get_n(a);
    nb = get_n(b);
    u = na - nb;
    if (u < 0)return 0;
    while (u + 1)
    {
        for (i = na - 1, f = 0; i >= u; i--)
        {
            //printf("%c", b[0]);
            if (a[i] > b[i - u])
            {
                f = 1;
                break;
            }
            if (a[i] < b[i - u])
            {
                f = -1;
                break;
            }
        }
        if (!f)
        {
            for (i = na - 1; i >= u; i--)a[i] = 0;
            u -= nb;
            if (u < 0)break;
            continue;
        }
        if (f == -1)u--;
        if (f == 1)
        {
            for (i = u; i < na; i++)
            {
                a[i] -= b[i - u];
                if (a[i] < 0)a[i + 1]--, a[i] += 10;
            }
        }
    }
    for (i = 0; i < na; i++)if (a[i])n = i + 1;

    return n;
}
void reverse(char* a)
{
    int i, n;
    n = get_n(a);
    for (i = 0; i < n / 2; i++)swap1(a[i], a[n - 1 - i]);
}
void get_a(char* a)
{
    int i = 0;
    while (a[i])a[i++] -= '0';
}
void get_g(char* a)
{
    int i, r, j = 0;;
    srand(time(0));
    while (1)
    {
        r = rand() % 10000;
        for (i = 0; i < 4; i++)
        {
            a[j++] = r % 10;
            r /= 10;
            if (j == NUMG)return;
        }
    }
}
void get_p(char* a, int n)
{
    int i;
    for (i = 0; i < 100; i++)a[i] = p_set[n][i];
}
void display(char* a)
{
    int n, i;
    n = get_n(a);
    reverse(a);
    for (i = 0; i < n; i++)printf("%d", a[i]);
    printf("\n");
    reverse(a);
}
void sent(int a, char* p, char* g, char* ans)
{
    char t[MAX] = { 0 };
    int p_n = 0;
    int i;
    memset(p, 0, MAX * sizeof(p[0]));
    memset(g, 0, MAX * sizeof(g[0]));
    srand(time(0));
    p_n = rand() % NUMP;   //随机得到p_n
    get_g(g);
    get_p(p, p_n);
    get_a(p);
    reverse(p);
    for (i = 0; i < MAX; i++)t[i] = g[i], ans[i] = 0;
    ans[0] = 1;
    for (i = 0; i < 32; i++)
    {
        if (a & 1 << i)
        {
            get_mul(ans, t);
            get_mod(ans, p);
        }
        get_mul(t, t);
        get_mod(t, p);
    }
}
void rec(int b, char* p, char* g, char* ans)
{
    char t[MAX] = { 0 };
    int i;
    for (i = 0; i < MAX; i++)t[i] = g[i], ans[i] = 0;
    ans[0] = 1;
    for (i = 0; i < 32; i++)
    {
        if (b & 1 << i)
        {
            get_mul(ans, t);
            get_mod(ans, p);
        }
        get_mul(t, t);
        get_mod(t, p);
    }
}
void get_key(int b, char* rec, char* p, char* g, char* ans)
{
    char t[MAX] = { 0 };
    int i;

    for (i = 0; i < MAX; i++)t[i] = rec[i], ans[i] = 0;
    ans[0] = 1;
    for (i = 0; i < 32; i++)
    {
        if (b & 1 << i)
        {
            get_mul(ans, t);
            get_mod(ans, p);
        }
        get_mul(t, t);
        get_mod(t, p);
    }
}


unsigned short S[10][16] = { {14,9,15,0,13,4,10,11,1,2,8,3,7,6,12,5},{4,11,14,9,15,13,0,10,7,12,5,6,2,8,1,3},{1,14,7,12,15,13,0,6,11,5,9,3,2,4,8,10},
                                {7,6,8,11,0,15,3,14,9,10,12,13,5,2,4,1},{14,5,15,0,7,2,12,13,1,8,4,9,11,10,6,3},{2,13,11,12,15,14,0,9,7,10,6,3,1,8,4,5},
                                {11,9,4,14,0,15,10,13,6,12,5,7,3,8,1,2},{13,10,15,0,14,4,9,11,2,1,8,3,7,5,12,6},{8,7,14,5,15,13,0,6,11,12,9,10,2,4,1,3},
                                {11,5,15,0,7,2,9,13,4,8,1,12,14,10,3,6} };


unsigned short P[8] = { 1,3,0,2,5,7,4,6 };

const unsigned int rounds = 32;
void roundkey(unsigned int k[5], unsigned int rk[32]) {
    unsigned int i, t1, t2, t3, t4, t0, c1, c2;
    rk[0] = (k[0] << 16) ^ k[1];
    for (i = 1; i < rounds; i++) {
        // 32 left shift (then 3 right shift)
        t1 = k[0]; t2 = k[1];
        k[0] = k[2];  k[1] = k[3]; k[2] = k[4]; k[3] = t1; k[4] = t2;
        //3 right shift
        t0 = (k[0] & 0x7);              t1 = (k[1] & 0x7);              t2 = (k[2] & 0x7);
        t3 = (k[3] & 0x7);              t4 = (k[4] & 0x7);
        k[4] = (k[4] >> 3) ^ (t3 << 13);
        k[3] = (k[3] >> 3) ^ (t2 << 13);
        k[2] = (k[2] >> 3) ^ (t1 << 13);
        k[1] = (k[1] >> 3) ^ (t0 << 13);
        k[0] = (k[0] >> 3) ^ (t4 << 13);
        //s-box
        t1 = (k[0] >> 12) & 0xF;
        t2 = (k[0] >> 8) & 0xF;
        t1 = S[9][t1];
        t2 = S[8][t2];
        k[0] = (t1 << 12) ^ (t2 << 8) ^ (k[0] & 0x00FF);
        //counter
        c1 = i & 0x3; c2 = i >> 2;
        k[2] ^= c1 << 14; k[1] ^= c2;
        //get roundkey
        rk[i] = (k[0] << 16) ^ k[1];
    }
}

unsigned int S_Layer(unsigned int x) {
    unsigned int temp = 0x0;
    int i;
    for (i = 0; i < 7; i++) {
        temp ^= S[7 - i][(x >> (28 - 4 * i)) & 0xF];
        temp <<= 4;
    }
    temp ^= S[7 - i][x & 0xF];
    return temp;
}
void get__key(int b, char* rec, char* p, char* g, char* ans) {
}
unsigned int P_Layer(unsigned int x) {
    unsigned short temp[8], i;
    unsigned int t = 0x0;

    for (i = 0; i < 8; i++)
        temp[i] = (x >> (28 - (4 * i))) & 0xF;

    for (i = 0; i < 7; i++) {
        t ^= temp[P[i]];
        t <<= 4;
    }
    t ^= temp[P[i]];

    return t;
}

unsigned int F(unsigned int x, unsigned int k) {
    x ^= k;
    x = S_Layer(x);
    x = P_Layer(x);
    return x;
}
void swap(unsigned int* left, unsigned int* right) {
    unsigned int temp;
    temp = (*left);
    (*left) = (*right);
    (*right) = temp;
}
void put_key_in(unsigned int k1[5], char ak[512]) {
}

void encrypt(unsigned int* left, unsigned int* right, unsigned int rk[32]) {
    unsigned int i;
    for (i = 0; i < rounds; i++) {
        (*right) = ((*right) << 8) ^ ((*right) >> 24);
        (*right) ^= F((*left), rk[i]);
        swap(left, right);
    }
    swap(left, right);
}

void decrypt(unsigned int* left, unsigned int* right, unsigned int rk[32]) {
    for (int i = 31; i >= 0; i--) {
        (*right) ^= F((*left), rk[i]);
        (*right) = ((*right) >> 8) ^ ((*right) << 24);
        swap(left, right);
    }
    swap(left, right);
}
int main() {

	WSADATA wsaDATA;
	WSAStartup(MAKEWORD(2, 2), &wsaDATA);
	if (LOBYTE(wsaDATA.wVersion) != 2 || HIBYTE(wsaDATA.wVersion) != 2) {
		printf("确定协议版本失败！\n");
		return -1;
	}
	printf("确认协议版本成功！\n");
	
	//2 创建socket
	SOCKET serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (serverSocket == SOCKET_ERROR) {
		printf("创建SOCKET失败：%d\n", GetLastError());
		//9 清理协议版本信息
		WSACleanup();
		return -1;
	}
	printf("创建SOCKET成功!\n");


	//3 创建协议族
	SOCKADDR_IN addr = { 0 };
	addr.sin_family = AF_INET;
	addr.sin_addr.S_un.S_addr = inet_addr("10.131.149.111");
	addr.sin_port = htons(9527);

	//4 绑定
	int r = bind(serverSocket, (struct sockaddr*)&addr, sizeof addr);
	if (r == SOCKET_ERROR) {
		printf("绑定失败：%d\n", GetLastError());
		//8 关闭socket
		closesocket(serverSocket);
		//9 清理协议版本信息
		WSACleanup();
		return -1;
	}
	printf("绑定成功!\n");

	//6 监听
	r = listen(serverSocket, 10);
	if (r == SOCKET_ERROR) {
		printf("监听失败：%d\n", GetLastError());
		//8 关闭socket
		closesocket(serverSocket);
		//9 清理协议版本信息
		WSACleanup();
		return -1;
	}
	printf("监听成功!\n");

	//7 等待客户端连接
	SOCKADDR_IN cAddr = {0};
	int len = sizeof cAddr;
	SOCKET clientSocket = accept(serverSocket, (sockaddr*) & cAddr, &len);
	if (clientSocket == SOCKET_ERROR) {
		printf("客户端连接失败：%d\n", GetLastError());
		//8 关闭socket
		closesocket(serverSocket);
		//9 清理协议版本信息
		WSACleanup();
		return -1;
	}
	printf("客户端连接成功!\n");


    //unsigned int k1[5] = { 0x1ACF,0x0D25,0x006C,0x121E,0x0B87 };//0x0123,0x4567,0x89ab,0xcdef,0xfedc
    

	//8 通信
	char buff[256];
    int count = 0;


    /// <summary>
    /// 
    /// </summary>
    /// <returns></returns>
    char sa[MAX], sb[MAX], p[MAX], g[MAX], ak[MAX], bk[MAX];
    int a, b;
    a = rand() % 50 + 50;
    sent(a, p, g, sa);   //A将sa=p^a get_mod g和p，g的值发送给B，

    send(clientSocket, p, strlen(p), NULL);
    //printf("p的长度%d\n", strlen(p));
    Sleep(5000);
    send(clientSocket, g, strlen(g), NULL);
    //printf("g的长度%d\n", strlen(g));
    Sleep(5000);
    send(clientSocket, sa, strlen(sa), NULL);
    //printf("sa的长度%d\n", strlen(sa));

    r = recv(clientSocket, buff, 512, NULL);
    if (r > 0) {
        for (int i = 0; i < 512; i++) {
            sb[i] = buff[i];
        }
    }
    //display(p);
    //printf("\n");
    r = recv(clientSocket, buff, 512, NULL);
    if (r > 0) {
        for (int i = 0; i < 512; i++) {
            ak[i] = buff[i];
        }
    }
    unsigned int k1[5] = { 0x0,0x0,0x0,0x0,0x0 };//初始化
    put_key_in(k1, ak);//密钥转化
    unsigned int rk1[32];
    roundkey(k1, rk1);//密钥更新
    

	while (1) {
		r = recv(clientSocket, buff, 1023, NULL);
        count++;
		if (r > 0) {
			buff[r] = 0;
			unsigned int* code_id = (unsigned int*)&buff;
            
			if (*code_id == 1) {//首个数字为1，即为光湿温
                unsigned int a, b, c, d, e, f;
                a = code_id[1], b = code_id[2], c = code_id[3], d = code_id[4],e = code_id[5], 
                f = code_id[6];
                time_t current = time(NULL);  
                struct tm timer;
                localtime_s(&timer ,&current);

                printf("接收到的24个字节大小的密文使用6个无符号数表示%u %u %u %u %u %u\n", a, b, c, d, e, f);
           

                decrypt(&a, &b, rk1);
                decrypt(&c, &d, rk1);
                decrypt(&e, &f, rk1);



                int* hour = (int*)&a;
                int* min = (int*)&b;
                int* sec = (int*)&c;
                float* Lux = (float*)&d;
                float* Hum = (float*)&e;
                float* Tem = (float*)&f;
                
                printf("此时的光照为%f\n", *Lux);
                printf("此时的湿度为%f\n", *Hum);
                printf("此时的温度为%f\n", *Tem);
                printf("采集数据的时间为%d:%d:%d", a, b, c);
                //printf("采集数据的时间为%d:%d:%d.\n",timer.tm_hour, timer.tm_min, timer.tm_sec-1);
                printf("\n");
                
			}
            else if(*code_id == 5) {
                if (count == 10000) {
                    printf("没有丢包");
                }
                else {
                    printf("共获取到%d个数据", count);
                }
            }
		}
	}
	return 0;
}
