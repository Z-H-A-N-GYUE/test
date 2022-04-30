#include<iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <windows.h>
#include <windef.h>
#include <math.h>
#include<fstream>
#include<iomanip>
using namespace std;


double nums[100];
char str[100];
int n, Max, flag, q = 1;
int decimal,         ///是否输入小数
brackets,        ///是否输入括号
fst,              ///是否写入文件
pos = 0,         ///pos为 + - * /的位置
pos1 = -1,        ///pos1,pos2为括号位置
pos2 = -1;
ofstream ofile;

void randomNumber()                                   /***********nums保存四则运算中将出现的数字*************************/
{
    flag = rand() % 3 + 2;
    for (int i = 0; i < flag; i++)
    {
        if (decimal)
        {
            nums[i] = (rand() % Max) + (rand() % 100 * 0.01);
        }
        else
        {
            nums[i] = (rand() % Max) + 1;
        }
    }
}

void randomBrackets()                               /**********随机括号的位置****************************************/
{
    pos1 = -1;
    pos2 = -1;
    if (brackets)
    {
        while (1)
        {
            pos1 = rand() % flag;
            pos2 = rand() % flag;
            if (abs(pos1 - pos2))
            {
                pos1 = min(pos1, pos2);
                pos2 = max(pos1, pos2);
                break;
            }
        }
        if (flag == 2)
        {
            pos1 = -1;
            pos2 = -1;
        }
    }
}

void priduction()                                  /************输出算式***********************************/
{
    for (int i = 0; i < flag; i++)
    {
        int k = rand() % pos;                  ///str[i]为随机的符号
        if (i == pos1 && pos1 != pos2)
        {
            cout << "(" << " ";
            fst&& ofile << "(" << " ";
        }
        cout << nums[i] << " ";
        fst&& ofile << nums[i] << " ";
        if (i == pos2 && pos1 != pos2)
        {
            cout << ")" << " ";
            fst&& ofile << ")" << " ";
        }
        if (i != flag - 1)
        {
            cout << str[k] << " ";
            fst&& ofile << str[k] << " ";
        }
    }

}



int main() {
    ofile.open("F:\math.txt");
    cout << "请输入题目数量以及题目中出现的最大数:" << endl;
    cin >> n >> Max;
    cout << "请输入想要的运算符（+-*/）" << endl;
    getchar();
    gets_s(str);
    cout << "是否需要小数？（1/0）";
    cin >> decimal;
    cout << "是否需要括号？（1/0）";
    cin >> brackets;
    cout << "是否写入文件？（1/0）";
    cin >> fst;

    for (int i = 0; i < strlen(str); i++)
    {
        if (str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/')
        {
            str[pos++] = str[i];                       ///str 存四则运算中将出现的符号
        }
    }

    while (n--)
    {
        randomNumber();
        randomBrackets();
        fst&& ofile << "(" << q << ")" << "  ";
        cout << "(" << q++ << ")" << "  ";
        priduction();
        cout << endl;
        fst&& ofile << endl;

    }
    ofile.close();
    return 0;
}
