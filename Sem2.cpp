#include <iostream>
#include <stack>

//Задача 1
//Имаме низ състоящ се от английски букви и символа *.
//Всеки път когато видим * трябва да премахнем символът отляво както и самата звезда. 

std::string removeStars(const std::string& str)
{
    std::stack<char> s;

    for (int i = 0; i < str.length(); i++)
    {
        if (str[i] == '*')
        {
            if (s.empty())
                throw std::logic_error("Invalid string!");
            else
                s.pop();
        }
        else
        {
            s.push(str[i]);
        }
    }

    std::string res(s.size(), '\0'); // стринг с размера на стека, в който се съдъража резултатът
    int ind = res.size() - 1;

    while (!s.empty())
    {
        res[ind--] = s.top();
        s.pop();
    }
    return res;
}

// Задача 2
//Вход: Низ състоящ се от отварящи и затварящи скоби.
//Изход : Дали скобите в този низ са балансирани

bool isOpeningBracket(char c)
{
    return (c == '{' || c == '[' || c == '(');
}

bool isClosingBracket(char c)
{
    return (c == '}' || c == ']' || c == ')');
}

bool isOppositeBracket(char c1, char c2)
{
    return (c1 == '}' && c2 == '{') || (c1 == ']' && c2 == '[') || (c1 == ')' && c2 == '(');
}

bool balancedBrackets(const std::string& str)
{
    std::stack<char> s;

    for (int i = 0; i < str.length(); i++)
    {
        if (isOpeningBracket(str[i]))
            s.push(str[i]);
        else if (isClosingBracket(str[i]))
        {
            if (s.empty())
                return false;
            else if(isOppositeBracket(str[i],s.top()))
                s.pop();
        }
    }

    return s.empty();
}

// Задача 3
// Обратен полски запис
// 123+- -> 1-(2+3) -> -4

bool isOperation(char c)
{
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

bool isDigit(char c)
{
    return (c >= '0' && c <= '9');
}

int calcCurr(int n1, int n2, char operation)
{
    if (operation == '+')
        return n1 + n2;
    else if (operation == '-')
        return n1 - n2;
    else if (operation == '*')
        return n1 * n2;
    else if (operation == '/')
        return n1 / n2;
}

int calculate(const std::string& str)
{
    std::stack<int> s;
    for (int i = 0; i < str.length(); i++)
    {
        if (isOperation(str[i]))
        {
            int n1, n2;
            n2 = s.top();
            s.pop();
            n1 = s.top();
            s.pop();
            int res = calcCurr(n1, n2, str[i]);
            s.push(res);
            
        }
        else if(str[i] != ' ')
        {
            int num = 0;
            while (i < str.length() && isDigit(str[i]))
            {
                num *= 10;
                num += str[i] - '0';
                i++;
            }
            s.push(num);
        }
    }

    return s.top();
}

//Бонус задачи

//Да се сортира стек като се използва само един опълнителен 

void sortStack(std::stack<int>& s1)
{
    std::stack<int> s2;

    while (!s1.empty())
    {
        int curr = s1.top(); // изваждаме първия елемент на стека
        s1.pop();

        while (!s2.empty() && curr < s2.top())
        {
            s1.push(s2.top());
            s2.pop();
        }
        s2.push(curr); // ако помощния стек е празен или първият елемент в помощния стек е по-малък от разглеждания
    }

    while (!s2.empty())
    {
        s1.push(s2.top());
        s2.pop();
    }
}

//Да се направи задачата със скобите
//,обаче този път функцията ни казва дали е възможно низът да стане балансиран 
//след най - много едно изтриване на скоба.

bool canBeBalanced(const std::string& str)
{
    std::stack<char> s1;
    std::stack<char> s2;

    for (int i = 0; i < str.length(); i++)
    {
        if (str[i] == '(')
            s1.push(str[i]);
        else if (str[i] == ')')
        {
            if (s1.empty())
            {
            s2.push(str[i]);
            }
           
            else 
                s1.pop();
        }
    }

    return (s1.size() + s2.size() <= 1);

}
