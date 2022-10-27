#include <iostream>
#include <queue>
#include <string>
#include <array>
#include <vector>

//Да се напише функция, която генерира всички двоични числа от 1 до n, използвайки опашка.
//1 -> 10 11
//10 -> 100 101
//11 -> 110 111
//...

void printAllBinaryNumbers(int n)
{
    std::queue<std::string> q;
    q.push("1");

    while (n)
    {
        std::string front = q.front();
        q.pop();

        std::cout << front << " ";
        q.push(front + "0");
        q.push(front + "1");

        n--;
    }
}

//Конче стои върху шахматна дъска NxN.
//За начална и крайна позиция да се изведе с колко най - малко хода можем да стигнем от началната до крайната.

const int BOARD_SIZE = 4;
class MinMoves {
private:
    using position = std::pair<int, int>;
    using positionAndSteps = std::pair<position, int>;
    using board = std::array<std::array<bool, BOARD_SIZE>, BOARD_SIZE>;

    board playground;

    void cleanPlayground()
    {
        for (int i = 0; i < BOARD_SIZE; i++)
        {
            for (int j = 0; j < BOARD_SIZE; j++)
            {
                playground[i][j] = false;
            }
        }
    }

    bool isValidPos(const position& pos)
    {
        return pos.first >= 0 && pos.first < BOARD_SIZE && pos.second >= 0 && pos.second < BOARD_SIZE;
    }

    bool equalPos(const position& fpos, const position& spos)
    {
        return fpos.first == spos.first && fpos.second == spos.second;
    }

    void markPos(const position& pos)
    {
        playground[pos.first][pos.second] = true;
    }

    bool isMarked(const position& pos) const
    {
        return playground[pos.first][pos.second] == true;
    }

    void pushIfIsValid(std::queue<positionAndSteps>& q,const position& pos, int moves)
    {
        if (isValidPos(pos) && !isMarked(pos))
        {
            q.push({ pos,moves });
            markPos(pos);
        }
    }

    int process(const position& start, const position& end)
    {
        std::queue<positionAndSteps> q;
        q.push({ start,0 });
        markPos(start);

        while (!q.empty())
        {
            positionAndSteps curr = q.front();
            q.pop();
            //std::cout << '[' << curr.first.first << ' ' << curr.first.second << ']' << std::endl;

            if (equalPos(curr.first, end))
            {
                return curr.second;
            }

            int x = curr.first.first;
            int y = curr.first.second;
            int moves = curr.second + 1;

            pushIfIsValid(q, { x + 1, y + 2 }, moves);
            pushIfIsValid(q, { x + 1, y - 2 }, moves);
            pushIfIsValid(q, { x - 1, y + 2 }, moves);
            pushIfIsValid(q, { x - 1, y - 2 }, moves);
            pushIfIsValid(q, { x + 2, y + 1 }, moves);
            pushIfIsValid(q, { x + 2, y - 1 }, moves);
            pushIfIsValid(q, { x - 2, y + 1 }, moves);
            pushIfIsValid(q, { x - 2, y - 1 }, moves);
        }
        return -1;
    }

public:
    MinMoves()
    {
        cleanPlayground();
    }

    int getMinMoves(const position& start, const position& end)
    {
        cleanPlayground();
        return process(start, end);
    }
};


//Даден е масив от цели числа. 
//Представяме си, че имаме прозорец с дължина k който се движи отляво надясно. 
//Единственото което можем да видим са числата в прозореца. Да се изведе максимумът на всеки такъв прозорец.

std::vector<int> maxWindow(const std::vector<int>& v, int k)
{
    std::vector<int> res;
    std::deque<int> window;

    for (int i = 0; i < k; i++)
    {
        while(!window.empty() && window.back() < v[i])
        {
            window.pop_back();
        }
        window.push_back(v[i]);
    }

    //най-големият елемент от текущия прозорец е винаги първия елемент от дек-а
    res.push_back(window.front());

    for (int i = k; i < v.size(); i++)
    {
        //ако най-големият елемент в предходния прозорец съпада с неговия първи елемент,
        //то когато разглеждаме нов прозорец, той трябва да отпадне, защото не влиза в него
        if (window.front() == v[i - k])
        {
            window.pop_front();
        }

        while (!window.empty() && window.back() < v[i]) {
            window.pop_back();
        }

        window.push_back(v[i]);
        res.push_back(window.front());
    }
    return res;
}

int main()
{
    //printAllBinaryNumbers(10);

    //MinMoves m;
    //std::cout << m.getMinMoves({ 0, 0 }, { 3, 3 }) << std::endl;
    
     std::vector<int> example = { 1, 3, -1, -3, 5, 3, 6, 7 };

    std::vector<int> result = maxWindow(example, 3);

    for (auto elem : result)
        std::cout << elem << " ";
}

