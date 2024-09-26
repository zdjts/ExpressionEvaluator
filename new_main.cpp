#include <iostream>
#include <stack>
#include <string>
#include <sstream>
#include <cmath>
#include <algorithm>
#include <vector>
#include <random>
#include <set>
using namespace std;
class ExprCalc
{
private:
    char endChar; 
public:
    ExprCalc(char ch = '#', string str = "") : endChar(ch) {}
    double ran(string str)
    {
        str.erase(std::remove(str.begin(), str.end(), ' '), str.end());
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
    double calc(double left, double right, char ch , int jis = 0)
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
            else if(jis == 0)
            {
                return left / right;
            }
            else if(jis != 0) {
                return (int)left/(int)right;
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
    double calcInfix(string str, int jis = 0)
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
        while (true)
        {
            if(ch == ' ' || ch == '\n'){
                //i++;
                continue;
            }
            if (!isNumber(ch))
            {
                if (isp(ops.top()) == icp(ch))
                {
                    char character = ops.top();
                    ops.pop();
                    if (character == '(')
                    {
                        iss >> ch;
                        i++;
                    }
                    if(character == endChar) {
                        break;
                    }
                }
                else if (isp(ops.top()) < icp(ch))
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
                    number = calc(left, right, character,jis);
                    data.push(number);
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
        number = data.top();
        return number;
    }
    bool isString24Point(string str) {
        double number = calcInfix(str, 1);
        return (number == 24);
    }
    vector<int> getNumber() {
        vector<int> card;
        for(int i=1;i <= 13; ++i) {
            for(int j=1; j <= 4; ++j) {
                card.push_back(i);
            }
        }
        set<int> number;
        while(number.size() != 4) {
            number.insert((rand()%52));
        }
        vector<int> aa;
        for(auto i = number.begin();i != number.end();++i) {
            aa.push_back(card[*i]);
        }
        return aa;
    }
    bool is24Point(vector<int>& number , int n, string str) {
       if(n==4) {
            if(isString24Point(str)) {
                cout<<str<<" = 24"<<endl;
                return true;
            }
            else {
                // str.pop_back();
                return false;
            }
        }
        string strNumber[4];
       
        for(int i=0;i<4;++i) {
            strNumber[i] = to_string(number[i]);
        }
        str+=strNumber[n];
        if(3 == n) {           
            return is24Point(number,n+1,str);
        }
        else {
            string ops = "+-*/^";
            for(char op : ops) {
                str+=op;
                if (is24Point(number, n + 1, str)) {
                    return true;
                }
                str.pop_back();
                str = '(' + str + ')';
                str+=op;
                if (is24Point(number, n + 1, str)) {
                    return true;
                }
                str.pop_back();
                str.erase(0, 1);       // 删除开头的括号
                str.erase(str.size() - 1, 1);            
            }
        }
       return false;
    }
    bool pailie(vector<int> number, int start) {
        bool font = false;
        if(start>=number.size()) {
            string str = "";
            if(is24Point(number,0,str)) {
                font = true;
                return true;
            }
        }
        else {
            for (int i = start; i < number.size(); i++) {
            swap(number[start], number[i]); // 交换
            pailie(number, start + 1); // 递归输出所有可能
            
            //输出一种可能后停止
            // if(pailie(number,start+1)) {
            //     return true;
            // }
            // if(pailie(number,start+1)) {
            //     font = true;
            // }
            swap(number[start], number[i]); // 还原交换
            }
        }
        return false;
    }
    bool is24Point(vector<int> number) {
        return pailie(number,0);
    }
};

int main()
{
    srand(time(0));
    int current = 10000;
    int dangqian = 0;
    ExprCalc aa;
    for(int i=0;i<current;++i) {
        if(aa.is24Point(aa.getNumber())) {
            dangqian++;
        }
    }
    cout<<(double)dangqian/(double)current<<endl;
}