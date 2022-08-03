/*
 * Copyright (c) 2020 Nanjing Xiaoxiongpai Intelligent Technology Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "ohos_init.h"
#include "cmsis_os2.h"
#include "E53_IA1.h"

//2

#include <stdio.h>
#include <unistd.h>

#include "ohos_init.h"
#include "cmsis_os2.h"

#include "wifi_device.h"
#include "lwip/netifapi.h"
#include "lwip/api_shell.h"
#include <netdb.h>
#include <string.h>
#include <stdlib.h>
#include "lwip/sockets.h"
#include "wifi_connect.h"
#include <string.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>

//4
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>


//1



#define TASK_STACK_SIZE 1024 * 8
#define TASK_PRIO 25

//2

#define _PROT_ 9527

#define STATE_SIZE 8
#define KEY_SIZE 10

//在sock_fd 进行监听，在 new_fd 接收新的链接
int sock_fd;

int addr_length;
//static const char *send_data = "Hello! I'm BearPi-HM_Nano TCP Client!\r\n";
//4
#define MAX 500 //运算中的最高可能位数
#define NUMP 2 //已提供的素数个数
#define NUMG 50 //随机数g的位数
//#define swap1(x,y) x^=y^=x^=y
char p_set[NUMP][110] ={{"3383489120380959248493525538580021146558530486980451874557556432721233835930146323754645777760514961"},
{"3383489120380959248493525538580021146558530486980451874557556432721233835930146323754645777760514963"}};

void swap1(char* a, char* b){
	char temp = *a;
	*a = *b;
	*b = temp;
}


int get_n(char* a)
{
    int i = MAX - 1;
    while (i >= 0 && !a[i])i--;
    return i + 1;
}
int get_mul(char* a, char* b)
{
    int na, nb, i, j, n = 0;
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
    char * addr_a;
    char * addr_b;
    for(i=0; i<n/2; i++){
    	addr_a = &a[i];
    	addr_b = &a[n-1-i];
    	swap1(addr_a,addr_b);
	}
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
    g[0] = '0';
    g[1] = 'a';

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




//3
unsigned short S[10][16] = { {14,9,15,0,13,4,10,11,1,2,8,3,7,6,12,5},
{4,11,14,9,15,13,0,10,7,12,5,6,2,8,1,3},
{1,14,7,12,15,13,0,6,11,5,9,3,2,4,8,10},
                                {7,6,8,11,0,15,3,14,9,10,12,13,5,2,4,1},
                                {14,5,15,0,7,2,12,13,1,8,4,9,11,10,6,3},
                                {2,13,11,12,15,14,0,9,7,10,6,3,1,8,4,5},
                                {11,9,4,14,0,15,10,13,6,12,5,7,3,8,1,2},
                                {13,10,15,0,14,4,9,11,2,1,8,3,7,5,12,6},
                                {8,7,14,5,15,13,0,6,11,12,9,10,2,4,1,3},
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

void put_key_in(unsigned int k[5],char bk[512]){
    int temp1 = 0, temp2 = 0;
    for(int i = 0; i < 4; i++){
        temp1 += bk[i]-'0';
        temp1 *= 10;
    }
    k[0] += temp2;
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

void encrypt_LBLOCK(unsigned int* left, unsigned int* right, unsigned int rk[32]) {
    unsigned int i;
    for (i = 0; i < rounds; i++) {
        (*right) = ((*right) << 8) ^ ((*right) >> 24);
        (*right) ^= F((*left), rk[i]);
        swap(left, right);
    }
    swap(left, right);
}

void decrypt_LBLOCK(unsigned int* left, unsigned int* right, unsigned int rk[32]) {
    for (int i = 31; i >= 0; i--) {
        (*right) ^= F((*left), rk[i]);
        (*right) = ((*right) >> 8) ^ ((*right) << 24);
        swap(left, right);
    }
    swap(left, right);
}

E53_IA1_Data_TypeDef E53_IA1_Data;


static void Example_Task(void)
{
    E53_IA1_Init();


    struct sockaddr_in send_addr;
    socklen_t addr_length = sizeof(send_addr);
    char recvBuf[512];

    //连接Wifi
    WifiConnect("TP-LINK_FF55", "214214214");

    //创建socket
    if ((sock_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror("create socket failed!\r\n");
        exit(1);
    }

    //初始化预连接的服务端地址
    send_addr.sin_family = AF_INET;
    send_addr.sin_port = htons(_PROT_);
    send_addr.sin_addr.s_addr = inet_addr("10.131.149.111");
    addr_length = sizeof(send_addr);

    int r = connect(sock_fd, (struct sockaddr *)&send_addr, addr_length);
    if(r == -1){
        printf("大失败大失败大失败！");
    }

    bzero(recvBuf, sizeof(recvBuf));
        char p[512], g[512], sa[512],sb[512], bk[512];
        recv(sock_fd, recvBuf, sizeof(recvBuf), 0);
        for(int h = 0; h < 512; h++){
            p[h] = recvBuf[h];
        }

        recv(sock_fd, recvBuf, sizeof(recvBuf), 0);
        for(int h = 0; h < 512; h++){
            g[h] = recvBuf[h];
        }

        recv(sock_fd, recvBuf, sizeof(recvBuf), 0);
        for(int h = 0; h < 512; h++){
            sa[h] = recvBuf[h];
        }


        int b = rand()%50+50;
        rec(b, p, g, sb);   //B收到后用收到的p,g计算出sb=p^b get_mod g，并将结果返回给A

        usleep(1000000);
        send(sock_fd, sb, 512, 0);

        get_key(b, sa, p, g, bk);   //B得到的密钥为bk=sa^b get_mod g

        send(sock_fd, bk, 512, 0);

    while (1)
    {

        E53_IA1_Read_Data();

        //printf("\r\n******************************Lux Value is  %.2f\r\n", E53_IA1_Data.Lux);
        //printf("\r\n******************************Humidity is  %.2f\r\n", E53_IA1_Data.Humidity);
        //printf("\r\n******************************Temperature is  %.2f\r\n", E53_IA1_Data.Temperature);

        bzero(recvBuf, sizeof(recvBuf));
        time_t current = time(NULL);
        struct tm *timer = localtime(&current); 
        //printf("时间为%d:%d:%d", timer -> tm_hour, timer -> tm_min, timer -> tm_sec);
        


        //发送数据到服务远端
        //send(sock_fd, send_data, strlen(send_data), 0);
        float Lux, Hum, Tem;
        unsigned int  *Lux_addr, *Hum_addr, *Tem_addr;
        Lux = E53_IA1_Data.Lux;
        Hum = E53_IA1_Data.Humidity;
        Tem = E53_IA1_Data.Temperature;
        Lux_addr = (unsigned int*)&Lux;
        Hum_addr = (unsigned int*)&Hum;
        Tem_addr = (unsigned int*)&Tem;

        unsigned int code_id_1 = timer -> tm_hour,*code_id_addr_1;
        unsigned int code_id_2 = timer -> tm_min,*code_id_addr_2;
        unsigned int code_id_3 =  timer -> tm_sec,*code_id_addr_3;
        code_id_addr_1 = &code_id_1;
        code_id_addr_2 = &code_id_2;
        code_id_addr_3 = &code_id_3;

        
        unsigned int k1[5] = {0x0,0x0,0x0,0x0,0x0};//初始化
        put_key_in(k1, bk);//取密钥
        unsigned int rk1[32];
        roundkey(k1, rk1);//密钥更新

        encrypt_LBLOCK(code_id_addr_1, code_id_addr_2, rk1);
        encrypt_LBLOCK(code_id_addr_3, Lux_addr, rk1);
        encrypt_LBLOCK(Hum_addr, Tem_addr, rk1);

        unsigned int send_list[7];
        send_list[0] = 1;
        send_list[1] = *code_id_addr_1;
        send_list[2] = *code_id_addr_2;
        send_list[3] = *code_id_addr_3;
        send_list[4] = *Lux_addr;
        send_list[5] = *Hum_addr;
        send_list[6] = *Tem_addr;

        printf("\r\n******************************Lux Value is  %.2f\r\n", E53_IA1_Data.Lux);
        printf("\r\n******************************Humidity is  %.2f\r\n", E53_IA1_Data.Humidity);
        printf("\r\n******************************Temperature is  %.2f\r\n", E53_IA1_Data.Temperature);


        send(sock_fd, send_list, 28, 0);


        if (E53_IA1_Data.Lux < 20)
        {
            Light_StatusSet(ON);
        }
        else
        {
            Light_StatusSet(OFF);
        }

        if ((E53_IA1_Data.Humidity > 70) | (E53_IA1_Data.Temperature > 35))
        {
            Motor_StatusSet(ON);
        }
        else
        {
            Motor_StatusSet(OFF);
        }

        usleep(1000000000);
    }
    //关闭这个 socket
    closesocket(sock_fd);
}

static void ExampleEntry(void)
{
    osThreadAttr_t attr;

    attr.name = "Example_Task";
    attr.attr_bits = 0U;
    attr.cb_mem = NULL;
    attr.cb_size = 0U;
    attr.stack_mem = NULL;
    attr.stack_size = TASK_STACK_SIZE;
    attr.priority = TASK_PRIO;

    if (osThreadNew((osThreadFunc_t)Example_Task, NULL, &attr) == NULL)
    {
        printf("Falied to create Example_Task!\n");
    }
}

APP_FEATURE_INIT(ExampleEntry);

