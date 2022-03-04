#include<iostream>
#include<string>
#include<fstream>
#include <vector>


const int MAXSIZE = 100;

template< typename T >
class Stack
{
public:
    Stack(int size);
    Stack(const Stack& other);
    ~Stack();
    Stack& operator=(const Stack& other);
    Stack operator+(const Stack& other);
    bool operator==(const Stack& other);
    bool isEmpty();
    void push(T rhs);
    T getTop();
    T pop();
    int getCount();
private:
    T* _stackPtr;
    int _count;
    int _size;
    T _top;
};


template< typename T >
class Queue
{
public:
    Queue(int size);
    Queue(const Queue& other);
    ~Queue();
    Queue& operator=(const Queue& other);
    Queue operator+(const Queue& other);
    bool isEmpty();
    bool operator==(const Queue& other);
    void add(T rhs);
    T drop();
    T getFront();
    int getCount();

private:
    T* _queuePtr;
    int _count;
    int _size;
    T _front;
};


bool isDigit(const char symbol);
int comparePriority(char first, char second);
bool isOperator(char symbol);
bool isFirstPriority(char symbol);
bool isSecondPriority(char symbol);
Queue<char> getPostfixForm(std::string expression);
double calkulatePostfix(Queue<char> postfixForm);
void calkulateStackOperands(Stack<std::string>& stack);
bool isCorrectExpression(std::string expr);

bool stringIsNullorWriteSpace(std::string str)
{
    for (int i = 0; i < static_cast<int>(str.size()); i++)
    {
        if (str[i] != ' ')
        {
            return false;
        }
    }
    return true;
}

int main(int argc, char** argv)
{
    std::string str1 = "";
    std::string path = "";
    if (argc != 1)
    {
        std::cout << "Incorrect argc";
        return -2;
    }
    path = argv[0];
    /* path = "Expr.txt";*/
    if (path == "")
    {
        std::cerr << "no such file\n";
        return -3;
    }
    std::ifstream stream(path);
    Stack<std::string> stackOfExpressions(100);
    Stack<std::string> stackOfExpressions(5000);
    if (stream.is_open())
    {
        while (getline(stream, str1))
        {
            if (stringIsNullorWriteSpace(str1))
            {
                continue;
            }
            stackOfExpressions.push(str1);
        }
        while (!stackOfExpressions.isEmpty())
        {
            std::string tempStr = stackOfExpressions.pop();
            if (isCorrectExpression(str1))
            {
                Queue<char> PostfixForm = getPostfixForm(tempStr);
                if (PostfixForm.isEmpty())
                {
                    std::cerr << "Incorrect expression\n";
                    return -4;
                }
                else
                {
                    std::cout << static_cast<int>(calkulatePostfix(PostfixForm)) << " ";
                }
            }
            else
            {
                std::cerr << "Incorrect expression\n";
                return -4;
            }
        }
        stream.close();
        std::cout << "\n";
    }
    else
    {
        std::cout << "No such file";
        return -5;
    }
    return 0;
}


/// <summary>
///    
///    
/// </summary>
/// <param name="expr"></param>
/// <returns></returns>
bool isCorrectExpression(std::string expr)
{
    int leftBrackets = 0,
        rightBrackets = 0;
    for (char s : expr)
    {
        if (s == '(')
        {
            leftBrackets++;
        }
        else if (s == ')')
        {
            rightBrackets++;
        }
        else if (!isDigit(s))
        {
            if (!isOperator(s))
            {
                if (s != ' ')
                {
                    return false;
                }
            }
        }
    }
    if (leftBrackets != rightBrackets)
    {
        return false;
    }
    return true;
}

/// <summary>
///  ,      ,
///  ,    
/// </summary>
/// <param name="expression"></param>
/// <returns>postfixExpression</returns>
Queue<char> getPostfixForm(std::string expression)
{
    Queue<char> inficsQueue(MAXSIZE);
    Stack<char> tempStack(MAXSIZE);
    Queue<char> postficsQueue(MAXSIZE);
    int count = 0;
    for (char x : expression)
    {
        inficsQueue.add(x);
        count++;
    }
    for (int i = 0; i < count; i++)
    {
        char symbol = inficsQueue.drop();
        if (symbol == ' ')
        {
            postficsQueue.add(symbol);
        }
        else if (symbol == '(')
        {
            tempStack.push(symbol);
        }
        else if (symbol == ')')
        {
            if (tempStack.isEmpty())
            {
                return 0;
            }
            char tempStackSymbol = ' ';
            while (tempStackSymbol != '(')
            {
                tempStackSymbol = tempStack.pop();
                if (tempStackSymbol != '(')
                {
                    postficsQueue.add(tempStackSymbol);
                    if (tempStack.isEmpty())
                    {
                        return 0;
                    }
                }
            }
        }
        else if (isDigit(symbol))
        {
            postficsQueue.add(symbol);
        }
        else if (isOperator(symbol))
        {
            if (!tempStack.isEmpty() && tempStack.getTop() != '(')
            {
                while (comparePriority(tempStack.getTop(), symbol) >= 0)
                {
                    postficsQueue.add(tempStack.pop());
                    if (tempStack.isEmpty() || tempStack.getTop() == '(')
                    {
                        break;
                    }
                }
            }
            tempStack.push(symbol);
        }
    }
    while (!tempStack.isEmpty())
    {
        postficsQueue.add(tempStack.pop());
    }
    return postficsQueue;
}
/// <summary>
///      
/// </summary>
/// <param name="postfixForm"></param>
/// <returns>  double</returns>
double calkulatePostfix(Queue<char> postfixForm)
{
    std::string operand = "";
    std::string _operator = "";
    char currentSymbol = ' ';
    Stack<std::string> calkulateStack(MAXSIZE);
    while (!postfixForm.isEmpty())
    {
        currentSymbol = postfixForm.getFront();
        if (isDigit(currentSymbol))
        {
            operand += postfixForm.drop();
        }
        else if (currentSymbol == ' ' && operand != "")
        {
            calkulateStack.push(operand);
            operand = "";
        }
        else if (currentSymbol == ' ' && operand == "")
        {
            postfixForm.drop();
        }
        else if (isOperator(currentSymbol))
        {
            if (operand != "")
            {
                calkulateStack.push(operand);
                operand = "";
            }
            _operator = postfixForm.drop();
            calkulateStack.push(_operator);
            calkulateStackOperands(calkulateStack);
        }
    }
    return std::stod(calkulateStack.pop());
}
/// <summary>
///     
/// </summary>
/// <param name="stack"></param>
void calkulateStackOperands(Stack<std::string>& stack)
{
    double firstOperand = 0.0;
    double secondOperand = 0.0;
    double result = 0.0;
    char _operator = ' ';
    _operator = stack.pop()[0];
    secondOperand = std::stod(stack.pop());
    firstOperand = std::stod(stack.pop());
    switch (_operator)
    {
    case '+':
    {
        result = firstOperand + secondOperand;
        break;
    }
    case '-':
    {
        result = firstOperand - secondOperand;
        break;
    }
    case '*':
    {
        result = firstOperand * secondOperand;
        break;
    }
    case '/':
    {
        result = firstOperand / secondOperand;
        break;
    }
    case '%':
    {
        result = static_cast<int>(firstOperand) % static_cast<int>(secondOperand);
        break;
    }
    default:
        break;
    }
    stack.push(std::to_string(result));
}
/// <summary>
/// ,    
/// </summary>
/// <param name="symbol"></param>
/// <returns></returns>
bool isDigit(const char symbol)
{
    switch (symbol)
    {
    case '0':
    {
        return 1;
    }
    case '1':
    {
        return 1;
    }
    case '2':
    {
        return 1;
    }
    case '3':
    {
        return 1;
    }
    case '4':
    {
        return 1;
    }
    case '5':
    {
        return 1;
    }
    case '6':
    {
        return 1;
    }
    case '7':
    {
        return 1;
    }
    case '8':
    {
        return 1;
    }
    case '9':
    {
        return 1;
    }
    default:
        return 0;
    }
    return false;
}
/// <summary>
/// ,    
/// </summary>
/// <param name="symbol"></param>
/// <returns></returns>
bool isOperator(const char symbol)
{
    switch (symbol)
    {
    case '-':
    {
        return 1;
    }
    case '+':
    {
        return 1;
    }
    case '*':
    {
        return 1;
    }
    case '/':
    {
        return 1;
    }
    case '%':
    {
        return 1;
    }
    default:
        return 0;
    }
}
/// <summary>
///    
/// </summary>
/// <param name="first"></param>
/// <param name="second"></param>
/// <returns></returns>
int comparePriority(char first, char second)
{
    if (isFirstPriority(first) && isSecondPriority(second))
    {
        return 1;
    }
    else if (isFirstPriority(second) && isSecondPriority(first))
    {
        return -1;
    }
    else if (isFirstPriority(first) && isFirstPriority(second))
    {
        return 0;
    }
    else if (isSecondPriority(first) && isSecondPriority(second))
    {
        return 0;
    }
    return -2;
}
/// <summary>
/// ,     
/// </summary>
/// <param name="symbol"></param>
/// <returns></returns>
bool isFirstPriority(char symbol)
{
    if (symbol == '*' || symbol == '%' || symbol == '/')
    {
        return true;
    }
    return false;
}

/// <summary>
/// ,     
/// </summary>
/// <param name="symbol"></param>
/// <returns></returns>
bool isSecondPriority(char symbol)
{
    if (symbol == '+' || symbol == '-')
    {
        return true;
    }
    return false;
}

/// <summary>
///
/// </summary>
/// <typeparam name="T"></typeparam>
/// <returns> </returns>
template< typename T >
T Stack<T>::getTop()
{
    return _top;
}
template< typename T >
Stack<T>::Stack(int size)
{
    _stackPtr = new T[size];
    _size = size;
    _count = 0;
}
template< typename T >
Stack<T>::Stack(const Stack& other)
{
    if (other._stackPtr != nullptr)
    {
        _size = other._size;
        _stackPtr = new T[_size];
        _count = other._count;
        for (int i = 0; i < _count; i++)
        {
            _stackPtr[i] = other._stackPtr[i];
        }
        _top = other._top;
    }
    else
    {
        throw;
    }
}
template< typename T >
bool Stack<T>::isEmpty()
{
    if (_count == 0)
    {
        return true;
    }
    return false;
}
template< typename T >
Stack<T>::~Stack()
{
    if (_stackPtr != nullptr)
    {
        delete[] _stackPtr;
        _stackPtr = nullptr;
    }
}
template< typename T >
Stack<T>& Stack<T>::operator=(const Stack& other)
{
    if (other._stackPtr != nullptr)
    {
        if (this->_stackPtr != nullptr)
        {
            delete[] this->_stackPtr;
            _stackPtr = nullptr;


            this->_size = other._size;
            this->_stackPtr = new T[_size];
            this->_count = other._count;
            for (int i = 0; i < _count; i++)
            {
                this->_stackPtr[i] = other._stackPtr[i];
            }
            this->_top = other._top;
        }
    }
    else
    {
        throw;
    }
    return *this;
}
template< typename T >
Stack<T> Stack<T>::operator+(const Stack& other)
{
    int newSize = this->_size + other._size;

    Stack newStack(newSize);
    int i = 0;
    for (; i < this->_count; i++)
    {
        newStack._stackPtr[i] = this->_stackPtr[i];
    }
    for (int j = 0; j < other._count; j++, i++)
    {
        newStack._stackPtr[i] = other._stackPtr[j];
    }
    int newCount = this->_count + other._count;
    newStack._count = newCount;
    newStack._top = newStack._stackPtr[newCount - 1];
    return newStack;
}
template< typename T >
bool Stack<T>::operator==(const Stack& other)
{
    if (this->_count == other._count)
    {
        for (int i = 0; i < this->_count; i++)
        {
            if (this->_stackPtr[i] != other._stackPtr[i])
            {
                return false;
            }
        }
        return true;
    }
    return false;
}
/// <summary>
///     
/// </summary>
/// <typeparam name="T"></typeparam>
/// <param name="rhs"></param>
template< typename T >
void Stack<T>::push(T rhs)
{
    if (this->_count == this->_size)
    {
        std::cout << "Stack overflow\n";
    }
    else
    {
        this->_stackPtr[_count] = rhs;
        this->_count++;
        this->_top = rhs;
    }
}
/// <summary>
///     
/// </summary>
/// <typeparam name="T"></typeparam>
/// <returns> </returns>
template < typename T >
T Stack<T>::pop()
{
    T top = this->_top;
    _count--;
    if (_count != 0)
    {
        this->_top = this->_stackPtr[_count - 1];
    }
    return top;
}
template < typename T >
int Stack<T>::getCount()
{
    return this->_count;
}

template< typename T >
T Queue<T>::getFront()
{
    return _front;
}
template< typename T >
Queue<T>::Queue(int size)
{
    _queuePtr = new T[size];
    _size = size;
    _count = 0;
}
template< typename T >
Queue<T>::Queue(const Queue& other)
{
    if (other._queuePtr != nullptr)
    {
        _size = other._size;
        _queuePtr = new T[_size];
        _count = other._count;
        for (int i = 0; i < _count; i++)
        {
            _queuePtr[i] = other._queuePtr[i];
        }
        _front = other._front;
    }
    else
    {
        throw;
    }
}
template< typename T >
bool Queue<T>::isEmpty()
{
    if (_count == 0)
    {
        return true;
    }
    return false;
}
template< typename T >
Queue<T>::~Queue()
{
    if (_queuePtr != nullptr)
    {
        delete[] _queuePtr;
        _queuePtr = nullptr;
    }
}
template< typename T >
Queue<T>& Queue<T>::operator=(const Queue& other)
{
    if (other._queuePtr != nullptr)
    {
        if (this->_queuePtr != nullptr)
        {
            delete[] this->_queuePtr;
            _queuePtr = nullptr;
            this->_size = other._size;
            this->_queuePtr = new T[_size];
            this->_count = other._count;
            for (int i = 0; i < _count; i++)
            {
                this->_queuePtr[i] = other._queuePtr[i];
            }
            this->_front = other._front;
        }
    }
    else
    {
        throw;
    }
    return *this;
}
template< typename T >
Queue<T> Queue<T>::operator+(const Queue& other)
{
    int newSize = this->_size + other._size;
    Queue newQueue(newSize);
    int i = 0;
    for (; i < this->_count; i++)
    {
        newQueue._queuePtr[i] = this->_queuePtr[i];
    }
    for (int j = 0; j < other._count; j++, i++)
    {
        newQueue._queuePtr[i] = other._queuePtr[j];
    }
    int newCount = this->_count + other._count;
    newQueue._count = newCount;
    newQueue._front = newQueue._queuePtr[0];
    return newQueue;
}
template< typename T >
bool Queue<T>::operator==(const Queue& other)
{
    if (this->_count == other._count)
    {
        for (int i = 0; i < this->_count; i++)
        {
            if (this->_queuePtr[i] != other._queuePtr[i])
            {
                return false;
            }
        }
        return true;
    }
    return false;
}
/// <summary>
///     
/// </summary>
/// <typeparam name="T"></typeparam>
/// <param name="rhs"></param>
template< typename T >
void Queue<T>::add(T rhs)
{
    if (this->_count == this->_size)
    {
        std::cout << "Queue overflow\n";
    }
    else
    {
        this->_queuePtr[_count] = rhs;
        this->_count++;
        this->_front = *_queuePtr;
    }
}
/// <summary>
///    
/// </summary>
/// <typeparam name="T"></typeparam>
/// <returns> </returns>
template < typename T >
T Queue<T>::drop()
{
    if (this->_queuePtr != nullptr && _count > 0)
    {
        T front = this->_front;
        _count--;
        for (int i = 0; i < _count; i++)
        {
            _queuePtr[i] = _queuePtr[i + 1];
        }
        if (_count != 0)
        {
            this->_front = this->_queuePtr[0];
        }
        return front;
    }
    std::cout << "Queue is empty\n";
    return -1;
}
template < typename T >
int Queue<T>::getCount()
{
    return this->_count;
}