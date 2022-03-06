#include <iostream>
#include"List.h"
#include<fstream>
#include<cstring>
#include<climits>
#include<cmath>
#define llint long long int
llint solvePostfixExp(Queue<char>& queue);
int postfixEntry(char const* in, Queue<char>& queue);
/////////////////////////////////////////////////////////////

llint solvePostfixExp(Queue<char>& queue)
{
    Stack<llint> st;
    llint num = 0;
    bool numEntered = 0;
    llint a, b;
    while (queue.count())
    {
        char sym = queue.pop();
        if (sym >= '0' and sym <= '9') {
            if (num * 10 > LLONG_MAX - (sym - '0')) {
                throw "Error: Int owerflow";
            }
            num = num * 10 + (sym - '0');//warning
            numEntered = 1;
        }
        else
        {
            if (numEntered) {
                st.push(num);
            }
            num = 0;
            numEntered = 0;
            switch (sym)
            {
            case '+':
                b = st.pop();
                a = st.pop();
                if (((b > 0) && (a > (LLONG_MAX - b))) ||
                    ((b < 0) && (a < (LLONG_MIN - b)))) {
                    throw "Error: Sum: Int owerflow";
                }
                st.push(a + b);
                break;
            case '-':
                b = st.pop();
                a = st.pop();
                if ((b > 0 && a < LLONG_MIN + b) ||
                    (b < 0 && a > LLONG_MAX + b)) {
                    throw "Error: Minus: Int owerflow";
                }
                st.push(a - b);
                break;
            case '*':
                b = st.pop();
                a = st.pop();
                if (a > 0) {  /* a is positive */
                    if (b > 0) {  /* a and b are positive */
                        if (a > (LLONG_MAX / b)) {
                            throw "Error: Multiply: oveflow";
                        }
                    }
                    else { /* a positive, b nonpositive */
                        if (b < (LLONG_MIN / a)) {
                            throw "Error: Multiply: oveflow";
                        }
                    } /* a positive, b nonpositive */
                }
                else { /* a is nonpositive */
                    if (b > 0) { /* a is nonpositive, b is positive */
                        if (a < (LLONG_MIN / b)) {
                            throw "Error: Multiply: oveflow";
                        }
                    }
                    else { /* a and b are nonpositive */
                        if ((a != 0) && (b < (LLONG_MAX / a))) {
                            throw "Error: Multiply: oveflow";
                        }
                    } /* End if a and b are nonpositive */
                } /* End if a is nonpositive */

                st.push(a * b);
                break;
            case '/':
                b = st.pop();
                a = st.pop();
                if ((b == 0) || ((a == LLONG_MIN) && (b == -1))) {
                    throw "Error: Divide: Can't divide!";
                }
                st.push(a / b);
                break;
            case '%':
                b = st.pop();
                a = st.pop();
                if ((b == 0) || ((a == LLONG_MIN) && (b == -1))) {
                    throw "Error: Mod: Can't divide!";
                }
                if (abs(a) < abs(b)) {       //special for negative numbers
                    st.push(abs(a));
                }
                else {
                    a = a % b;
                    if (a < 0) {      //and this too
                        a += b;
                    }
                    st.push(a);
                }
                break;
            default://pass all spaces
                break;
            }
        }
    }
    if (numEntered) {
        st.push(num);
    }
    return st.pop();
}


bool isNumber(const char& str)
{
    return (str >= '0' and str <= '9');
}

int priority(char symbol)
{
    struct symbols
    {
        char sym;
        short int priority;
    };
    symbols priorities[7] = { '+',3,'-',3,'*',1,'/',1,'%',2,'(',4,')',4 };
    for (auto a : priorities) {
        if (a.sym == symbol) {
            return a.priority;
        }
    }
    throw "Error: Unexpected symbol";
    return 0;
}

int postfixEntry(char const* in, Queue<char>& queue)
{
    Stack<char> st;
    int i = 0;
    do
    {
        if (isNumber(in[i])) {
            queue.push(in[i]);
        }
        else
        {
            char c;
            switch (in[i])
            {
            case '(':
                st.push('(');
                break;
            case ')':
                c = st.pop();
                while (c != '(')
                {
                    queue.push(c);
                    if (st.count() == 0) {
                        throw "Error: Check the quantity of of brackets!";
                    }
                    c = st.pop();
                }
                break;
            case ' '://pass
                break;
            default:
                queue.push(' ');
                if (!priority(in[i])) {
                    return 2;
                }
                while (st.count() > 0 and priority(in[i]) >= priority(st.peek())) //if the priority of the operation in the stack is not less then
                {
                    queue.push(st.pop());                                           //drag from the stack to the queue
                }
                st.push(in[i]);
            }
        }
        i++;
    } while (in[i] != '\0');
    while (st.count()) {
        if (st.peek() == '(') {
            throw "Error: Check the quantity of of brackets!";
        }
        queue.push(st.pop());
    }
    return 0;
}


/////////////////////////////////////////////////////////////////////////////////



int main(int argc, char* argv[])
{
    using std::cout;
    using std::endl;
    try
    {
        char str[256];
        Stack<llint> answers;
        std::istream* in;
        std::ifstream file;
        if (argc == 2)
        {
            file.open(argv[1]/*"C:/Users/Fasci/source/repos/s1/Debug/in.txt"*/);
            if (!file.is_open()) {
                throw "Error: Can't open file";
            }
            in = &file;
        }
        else if (argc == 1)
        {
            in = &std::cin;
        }
        else {
            throw "Error: incorrect number of values entered";
        }

        while (!in->eof())
        {
            in->getline(str, 255, '\n');
            Queue<char> qu;
            if (strlen(str))
            {
                postfixEntry(str, qu);
                //qu.print();
                if (qu.count())
                {
                    answers.push(solvePostfixExp(qu));
                }
            }
        }

        if (argc == 2) {
            file.close();

        }

        while (answers.count())
        {
            cout << answers.pop();
            if (answers.count())
                cout << ' ';
        }
        cout << endl;
    }
    catch (const char* err)
    {
        std::cerr << err << endl;
        return 1;
    }
    return 0;
}