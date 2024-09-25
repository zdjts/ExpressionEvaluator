#include <iostream>
#include <stack>
#include <string>
#include <sstream>
#include <cmath>
using namespace std;
class ExprCalc
{
private:
    char endChar; 
public:
    ExprCalc(char ch = '#', string str = "") : endChar(ch) {}
    double ran(string str)
    {
        return calcInfix(str);
    }
    bool isNumber(char ch)
    {
        if (ch >= '0' && ch <= '9')
        {
            return true;
        }
        return false;
    }
    int icp(char ch)
    {
        switch (ch)
        {
        case '(':
            return 6;
        case '+':
        case '-':
            return 2;
        case '*':
        case '/':
        case '%':
        case '^':
            return 4;
        case ')':
            return 1;
        }
        return 0;
    }
    int isp(char ch)
    {
        switch (ch)
        {
        case '(':
            return 1;
        case '+':
        case '-':
            return 3;
        case '*':
        case '/':
        case '%':
        case '^':
            return 5;
        case ')':
            return 6;
        }
        return 0;
    }
    double calc(double left, double right, char ch)
    {
        switch (ch)
        {
        case '+':
            return left + right;
        case '-':
            return left - right;
        case '*':
            return left * right;
        case '/':
            if (right == 0)
            {
                return 0;
            }
            else
            {
                return left / right;
            }
        case '%':
            return (fmod(left, right));
        case '^':
            return pow(left,right);
        }
        return 0;
    }
    double toDouble(string str)
    {
        stringstream iss(str);
        double number = 0;
        char ch;
        iss >> ch;
        while (isNumber(ch))
        {
            number *= 10;
            number += (ch - '0');
            iss >> ch;
        }
        int i = 0;
        double number_xiao = 0;
        if (ch == '.')
        {
            iss >> ch;
            while (isNumber(ch))
            {
                i++;
                number_xiao *= 10;
                number_xiao += (ch - '0');
                iss >> ch;
            }
        }
        while (i != 0)
        {
            number_xiao /= 10;
            i--;
        }
        number += number_xiao;
        return number;
    }
    double calcInfix(string str)
    {
        stack<double> data;
        stack<char> ops;
        ops.push(endChar);
        str += endChar;
        char ch;
        double number;
        int i = 0; // 字符出现位置
        stringstream iss(str);
        iss >> ch;
        while (ch != endChar)
        {
            if(ch == ' '){
                continue;
            }
            if (!isNumber(ch))
            {
                if (isp(ops.top()) < icp(ch))
                {
                    ops.push(ch);
                    iss >> ch;
                    i++;
                }
                else if (isp(ops.top()) > icp(ch))
                {
                    double left, right;
                    right = data.top();
                    data.pop();
                    left = data.top();
                    data.pop();
                    char character = ops.top();
                    ops.pop();
                    number = calc(left, right, character);
                    data.push(number);
                }
                else if (isp(ops.top()) == icp(ch))
                {
                    char character = ops.top();
                    ops.pop();
                    if (character == '(')
                    {
                        iss >> ch;
                        i++;
                    }
                }
            }
            else
            {
                number = toDouble(str.substr(i));
                data.push(number);
                while (isNumber(ch) || ch == '.')
                {
                    iss >> ch;
                    i++;
                }
            }
        }
        double left, right;
        right = data.top();
        data.pop();
        left = data.top();
        data.pop();
        char character = ops.top();
        number = calc(left, right, character);
        return number;
    }
};

int main()
{
    while (true)
    {
        string str;
        cin >> str;
        ExprCalc ed('#');
        cout << (ed.ran(str)) << endl;
    }
    return 0;
}