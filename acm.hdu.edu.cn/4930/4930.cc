#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <algorithm>
using namespace std;
 
int x[20], y[20];
 
int Win(int n)
{
    if(n == 4 || n == 6) //炸弹带 
    {
        for(int i = 17; i >= 3; i--)
        {
            if(x[i] == 4) return 1;
        }
    }
    if(n == 5) //3带2 
    {
        int Tri = 0, Dou = 0;
        for(int i = 17; i >= 3; i--)
        {
            if(x[i] == 3) Tri = 1;
            if(x[i] == 2) Dou = 1;
        }
        if(Tri && Dou) return 1;
    }
    if(n == 4) //3带1 
    {
        for(int i = 17; i >= 3; i--)
        {
            if(x[i] == 3) return 1;
        }
    }
    if(n == 3) //三个 
    {
        for(int i = 17; i >= 3; i--)
        {
            if(x[i] == 3) return 1;
        }
    }
    if(n == 2) //Double 
    {
        for(int i = 17; i >= 3; i--)
        {
            if(x[i] == 2) return 1;
        }
    }
    if(n == 1) return 1; //一个 
     
    return 0;
}
 
int main()
{
    int T;
    for(scanf("%d", &T); T > 0; T--)
    {
        char s[20];
        scanf("%s", s);
         
        memset(x, 0, sizeof(x));
        memset(y, 0, sizeof(y));
         
        for(int i = 0; s[i]; i++)
        {
            int t;
            if(s[i] == 'T') t = 10;
            else if(s[i] == 'J') t = 11;
            else if(s[i] == 'Q') t = 12;
            else if(s[i] == 'K') t = 13;
            else if(s[i] == 'A') t = 14;
            else if(s[i] == '2') t = 15;
            else if(s[i] == 'X') t = 16;
            else if(s[i] == 'Y') t = 17;
            else t = s[i]-'0';
            x[t]++;
        }
         
        int len = strlen(s);
        scanf("%s", s);
        for(int i = 0; s[i]; i++)
        {
            int t;
            if(s[i] == 'T') t = 10;
            else if(s[i] == 'J') t = 11;
            else if(s[i] == 'Q') t = 12;
            else if(s[i] == 'K') t = 13;
            else if(s[i] == 'A') t = 14;
            else if(s[i] == '2') t = 15;
            else if(s[i] == 'X') t = 16;
            else if(s[i] == 'Y') t = 17;
            else t = s[i]-'0';
            y[t]++;
        }
         
        if(x[16] == 1 && x[17] == 1) //有大小王 
        {
            printf("Yes\n");
            continue;
        }
         
        if(Win(len)) { printf("Yes\n"); continue ; } //出完的情况 
         
        if(y[16] == 1 && y[17] == 1) //有大小王 
        {
            printf("No\n");
            continue;
        }
         
         
        int bomb = -1, p;
        for(int i = 17; i >= 3; i--) //炸弹 
        {
            if(x[i] == 4)
            {
                bomb = 1;
                p = i;
                break;
            }
        }
         
        int win = 1;
        if(bomb == 1)
        {
            for(int i = 17; i > p; i--)
            {
                if(y[i] == 4)
                {
                    win = 0; break;
                }
            }
        }
         
        if(bomb == 1 && win) { printf("Yes\n"); continue; } //有炸弹且最大 
        else if(!win) { printf("No\n"); continue ;} //有炸弹，但输了。 
         
        for(int i = 3; i <= 17; i++) if(y[i] == 4) { bomb = 2; break; }
        if(bomb == 2) { printf("No\n"); continue ; } //对手有炸弹，我没有。
         
         
        win = 1;
        int Tri = -1;
        for(int i = 17; i >= 3; i--) //三个 
        {
            if(x[i] == 3)
            {
                Tri = 1;
                p = i;
                break;
            }
        }
         
        if(Tri == 1)
        {
            for(int i = 17; i > p; i--)
            {
                if(y[i] == 3)
                {
                    Tri = 0;
                    break;
                }
            }
        }
         
        if(Tri == 1) { printf("Yes\n"); continue ;}
        else if(Tri == 0) win = 0;
         
         
        int Dou = -1;
        for(int i = 17; i >= 3; i--) //两个 
        {
            if(x[i] == 2)
            {
                Dou = 1;
                p = i;
                break;
            }
        }
         
        if(Dou == 1)
        {
            for(int i = 17; i > p; i--)
            {
                if(y[i] == 2 || y[i] == 3)
                {
                    Dou = 0;
                    break;
                }
            }
        }
         
        if(Dou == 1) { printf("Yes\n"); continue ; }
        else if(Dou == 0) win = 0;
         
        int solo = -1;
        for(int i = 17; i >= 3; i--) //一个 
        {
            if(x[i] == 1)
            {
                solo = 1;
                p = i; 
                break;
            }
        }
         
        if(solo == 1)
        {
            if(win == 0) win = 1;
            for(int i = 17; i > p; i--)
            {
                if(y[i] == 1 || y[i] == 2 || y[i] == 3) { win = 0; break; }
            }
        }
         
        if(win == 1) printf("Yes\n");
        else if(win == 0) printf("No\n");
    }
    return 0;
}
