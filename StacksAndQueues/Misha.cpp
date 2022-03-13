#include <cmath>
#include <fstream>
#include <iostream>
#include <limits>
#include <string>

template <class T> class List {
public:
    struct Node {
        T item_;
        Node* prev_ = nullptr;
        Node* next_ = nullptr;

        Node(T item) : item_(item), prev_(nullptr), next_(nullptr) {};
        Node(T item, T* prev, T* next) : item_(item), prev_(prev), next_(next) {};
    };

    List() : tail_(nullptr), head_(nullptr) {}
    List(const List& lst) : tail_(lst.tail()), head_(lst.head()) {};
    List(List&& lst) : tail_(lst.tail()), head_(lst.head()) {
        lst.head_ = nullptr;
        lst.tail_ = nullptr;
    };

    T pop_back() {
        auto tmp = tail_->item_;
        remove(tail_);
        return tmp;
    }

    T pop_front() {
        auto tmp = head_->item_;
        remove(head_);
        return tmp;
    }

    void push_back(Node* psh) {
        if (tail_ != nullptr) {
            psh->next_ = tail_;
            tail_->prev_ = psh;
        }
        if (head_ == nullptr) {
            head_ = psh;
        }

        tail_ = psh;

        tail_->prev_ = nullptr;
    }

    void push_front(Node* psh) {
        if (head_ != nullptr) {
            psh->prev_ = head_;
            head_->next_ = psh;
        }
        if (tail_ == nullptr) {
            tail_ = psh;
        }

        head_ = psh;

        head_->next_ = nullptr;
    }

    void push_back(T psh) { push_back(new Node(psh)); }

    void push_front(T psh) { push_front(new Node(psh)); }

    void reverse() {
        Node* it = tail_;

        while (it != nullptr) {

            std::swap(it->prev_, it->next_);

            it = it->prev_;
        }

        std::swap(tail_, head_);
    }

    T back() const { return tail_->item_; }

    T front() const { return head_->item_; }

    Node* tail() const { return tail_; }

    Node* head() const { return head_; }

    bool isempty() { return tail_ == nullptr || head_ == nullptr; }

    List<T>& operator=(const List& other) {
        List<T> temp(other);

        this->head_ = other.head();
        this->tail_ = other.tail();

        return *this;
    }

    virtual ~List() {
        Node* it = tail_;
        while (it != nullptr) {
            Node* n = it->next_;

            delete it;

            it = n;
        }
    }

    friend std::ostream& operator<<(std::ostream& os, const List<T>& lst) {
        Node* it = lst.tail();
        while (it != nullptr) {
            os << it->item_ << ' ';
            it = it->next_;
        }

        return os;
    }

private:
    Node* tail_ = nullptr;
    Node* head_ = nullptr;

    void remove(Node* item) {
        Node* next = item->next_;
        Node* prev = item->prev_;

        delete item;

        if (next != nullptr)
            next->prev_ = prev;
        if (next == nullptr)
            head_ = prev;

        if (prev != nullptr)
            prev->next_ = next;
        if (prev == nullptr)
            tail_ = next;
    }
};

template <class T> class Queue : public List<T> {
public:
    using List<T>::push_back;
    using List<T>::front;
    using List<T>::pop_front;

    void push(T rhs) { push_back(rhs); }

    T drop() { return front(); }

    T pop() {
        auto tmp = front();
        pop_front();
        return tmp;
    }
};

template <class T> class Stack : public List<T> {
public:
    using List<T>::push_front;
    using List<T>::front;
    using List<T>::pop_front;

    void push(T rhs) { push_front(rhs); }

    T drop() { return front(); }
    T pop() { return pop_front(); }
};

class Arithmetic {
private:
    struct Atom {
        std::string val = "";

        enum Status {
            digit,
            closeParenthesis,
            openParenthesis,
            operators,
        };

        Status status;

        int idOperator() const {
            switch (val[0]) {
            case '*':
            case '%':
            case '/':
            case '^':
                return 1;
            case '+':
            case '-':
                return 0;
            }
            return -1;
        }

        bool checkDigit() {
            for (char c : val) {
                if (!std::isdigit(c))
                    return false;
            }
            return true;
        }
        bool checkOpenParenthesis() { return '(' == val[0]; }
        bool checkCloseParenthesis() { return ')' == val[0]; }
        bool checkOperators() { return idOperator() != -1; }

        Atom() {}
        Atom(std::string c) {
            val = c;

            if (checkDigit()) {

                status = Status::digit;
                if (checkOverflow() != 0)
                    throw "Input data is overflow";

            }
            else if (checkOpenParenthesis()) {

                status = Status::openParenthesis;

            }
            else if (checkCloseParenthesis()) {

                status = Status::closeParenthesis;
            }

            else if (checkOperators()) {

                status = Status::operators;
            }
        }

        /// @return 0 == , 1 this > other, 2 this < other else -1
        int cmpParenthesis(const Atom& other) const {
            if (other.status == status)
                return 0;

            if (status == Status::openParenthesis &&
                other.status == Status::closeParenthesis)
                return 1;

            if (status == Status::closeParenthesis &&
                other.status == Status::openParenthesis)
                return 2;

            return -1;
        }

        /// @return 0 == , 1 a > b, 2 a < b
        int cmpStringDigit(const std::string& a, const std::string& b) const {
            if (a.size() > b.size())
                return 1;
            if (a.size() < b.size())
                return 2;
            for (size_t i = 0; i < a.size(); i++) {
                if (a[i] > b[i])
                    return 1;
                if (a[i] < b[i])
                    return 2;
            }

            return 0;
        }

        /// @return 0 == , 1 this > other, 2 this < other
        bool cmpDigit(const Atom& other) const {
            return cmpStringDigit(val, std::string(other));
        }

        /// @return 0 == , 1 this > other, 2 this < other else -1
        bool cmpOperators(const Atom& other) const {
            auto thisIdOp = this->idOperator();
            auto otherIdOp = other.idOperator();
            if (thisIdOp == otherIdOp)
                return 0;
            if (thisIdOp > otherIdOp)
                return 1;
            if (thisIdOp < otherIdOp)
                return 2;
            return -1;
        }

        /// @return 0 == , 1 this > other, 2 this < other else -1
        int cmp(const Atom& other) const {
            if (status != other.status)
                throw "Not a correct comparison";

            if (status == Status::openParenthesis ||
                status == Status::closeParenthesis)
                return cmpParenthesis(other);

            if (status == Status::operators)
                return cmpOperators(other);

            return cmpDigit(other);
        }

        /// return 0 if no error, 0 else
        int checkOverflow(long long a, long long b, char oper) const {
            switch (oper) {
            case '+':
                return checkOverflow_plus(a, b);
            case '-':
                return checkOverflow_minus(a, b);
            case '*':
                return checkOverflow_multiply(a, b);
            case '/':
                return checkOverflow_devide(a, b);
            case '%':
                return checkOverflow_remainder(a, b);
            }

            return 0;
        }
        int checkOverflow(std::string str) const {
            std::string max = std::to_string(std::numeric_limits<long long>::max());
            if (str[0] == '-')
                str.erase(0, 1);

            if (cmpStringDigit(str, max) == 1)
                return 1;

            return 0;
        }
        int checkOverflow() const { return checkOverflow(val); }

        int checkOverflow_plus(long long a, long long b) const {
            constexpr long long MAX = std::numeric_limits<long long>::max();
            constexpr long long MIN = std::numeric_limits<long long>::min();

            if (a >= 0 && b >= 0 && (a > MAX - b)) {
                return -1;
            }
            else if (a < 0 && b < 0 && (a < MIN - b)) {
                return -1;
            }

            return 0;
        }
        int checkOverflow_minus(long long a, long long b) const {
            return checkOverflow_plus(a, -b);
        }
        int checkOverflow_multiply(long long a, long long b) const {
            long long x = a * b;
            return (a != 0 && x / a != b);
        }
        int checkOverflow_devide(long long a, long long b) const {
            if (b == 0)
                return a;

            return 0;
        }
        int checkOverflow_remainder(long long a, long long b) const {
            if (b == 1)
                return a;

            return 0;
        }

        long long calc(long long a, long long b) {
            long long c = 0;

            switch (val[0]) {
            case '+':
                c = a + b;
                break;
            case '-':
                c = a - b;
                break;
            case '*':
                c = a * b;
                break;
            case '/':
                c = a / b;
                break;
            case '%':
                c = a % b;
                break;
            }

            if (checkOverflow(a, b, val[0]) != 0)
                throw "calculate is overflow";

            return c;
        }

        bool operator<(const Atom& other) { return cmp(other) == 2; }
        bool operator>(const Atom& other) { return cmp(other) == 1; }
        bool operator==(const Atom& other) { return cmp(other) == 0; }
        bool operator<=(const Atom& other) {
            return cmp(other) == 2 || cmp(other) == 0;
        }
        bool operator>=(const Atom& other) {
            return cmp(other) == 1 || cmp(other) == 0;
        }

        explicit operator std::string() const { return val; }
        explicit operator long long() const {
            if (status != Status::digit)
                throw "Not correct transform";

            if (checkOverflow() != 0)
                throw "Input data is overflow";

            long long out = 0;

            for (char c : val)
                out = out * 10 + (c - '0');

            return out;
        }

        friend std::ostream& operator<<(std::ostream& os, const Atom& a) {
            os << a.val;
            return os;
        }
    };

    std::string unproc_;
    Stack<Atom> input_;
    Stack<Atom> output_;
    Stack<Atom> buffer_;

    std::string operatorPriority = "+-%*/";

    /// @return 1 is open , 2 - close, else 0
    bool isOperator(char c) {
        return operatorPriority.find(c) != std::string::npos;
    }
    bool isDigit(char c) { return '0' <= c && '9' >= c; }

    void split(char sep = ' ') {
        // Split string by sep
        Stack<std::string> out;

        size_t pos = unproc_.find(sep);
        size_t initialPos = 0;

        while (pos != std::string::npos) {

            out.push(unproc_.substr(initialPos, pos - initialPos));
            initialPos = pos + 1;

            pos = unproc_.find(sep, initialPos);
        }

        out.push(unproc_.substr(initialPos,
            std::min(pos, unproc_.size()) - initialPos + 1));

        auto it = out.head();
        while (it != nullptr) {
            Atom atm(it->item_);
            input_.push(atm);
            it = it->prev_;
        }
    }

    /// @return 0 if success, != not some error
    int check() {
        int status = 0;

        status += checkParenthesis() != 0;
        status += checkAvalibleSymbol() != 0;
        status += checkOperators() != 0;

        return status;
    }

    bool checkParenthesis() {
        std::string out = "";
        for (char c : unproc_) {
            if (c == '(' || c == ')')
                out += c;
        }
        size_t oldSize = out.size();
        size_t newSize = 0;
        while (oldSize != newSize) {
            oldSize = out.size();

            if (out.find("()") != std::string::npos)
                out.replace(out.find("()"), 2, "");

            newSize = out.size();
        }
        return newSize != 0;
    }
    int checkAvalibleSymbol() {
        std::string avalibleSymbol = "0123456789()+-*/% ";
        for (char c : unproc_) {
            if (avalibleSymbol.find(c) == std::string::npos)
                return 1;
        }

        return 0;
    }
    int checkOperators() {
        size_t status = 0;
        if (input_.tail() != nullptr)
            status += input_.tail()->item_.status == Atom::Status::operators;
        if (input_.head() != nullptr)
            status += input_.head()->item_.status == Atom::Status::operators;

        return status;
    }

public:
    Arithmetic(std::string& inp, char sep = ' ') {

        unproc_ = inp;

        split(sep);

        int status = check();
        if (status != 0)
            throw "Incorrect input data";

        translate();
    }

    std::string& unproc() { return unproc_; }
    Stack<Atom>& input() { return input_; }
    Stack<Atom>& output() { return output_; }

    Stack<Atom>& translate() {
        while (!input_.isempty()) {

            Atom now = input_.pop();

            if (now.status == Atom::Status::openParenthesis) {

                buffer_.push(now);

            }
            else if (now.status == Atom::Status::digit) {

                output_.push(now);

            }
            else if (now.status == Atom::Status::operators) {

                if (!buffer_.isempty() &&
                    buffer_.drop().status == Atom::Status::operators &&
                    now <= buffer_.drop())
                    output_.push(buffer_.pop());

                buffer_.push(now);

            }
            else if (now.status == Atom::Status::closeParenthesis) {

                while (!buffer_.isempty()) {

                    if (!buffer_.isempty() &&
                        buffer_.drop().status == Atom::Status::openParenthesis) {
                        buffer_.pop();
                        break;
                    }

                    output_.push(buffer_.pop());
                }
            }
        }

        while (!buffer_.isempty())
            output_.push(buffer_.pop());

        return output_;
    }

    long long calculate() {
        Stack<long long> out;

        output_.reverse();

        while (!output_.isempty()) 
        {
            auto now = output_.pop();

            if (now.status == Atom::Status::digit) {

                long long nowDigit = static_cast<long long>(now);

                out.push(nowDigit);

            }
            else if (now.status == Atom::Status::operators) {

                long long b = out.pop();
                long long a = out.pop();

                if (std::string(now)[0] == '%') { // Science modulo negative number

                    out.push(((a % b) + b) % b);

                }
                else {

                    out.push(now.calc(a, b));
                }
            }
        }
        return out.drop();
    }

    friend std::ostream& operator<<(std::ostream& os, const Arithmetic& ar) {
        os << ar;
        return os;
    }
};

int main(int argc, char* argv[]) {

    std::string data = "";

    std::istream* in;
    std::ifstream ifn;

    if (argc == 1) {
        in = &std::cin;
    }
    else {
        ifn.open(argv[1]);
        in = &ifn;

        if (!ifn.is_open()) {
            std::cerr << "Error open file\n";
            return 1;
        }
    }

    // Example
    // Inp: ( 5 + 15 ) / (4 + 7 - 1 )
    // Out: 5 15 + 4 7 + 1 - /

    Stack<long long> output;
    try {
        while (getline(*in, data)) 
        {
            if (data.empty())
                continue;

            Arithmetic ar(data);
            output.push(ar.calculate());
        }
    }
    catch (const char* e) 
    {
        std::cerr << "Error! " << e << std::endl;
        return 2;
    }

    Stack<long long>::Node* it = output.head();
    while (it != nullptr) {
        std::cout << it->item_;

        it = it->prev_;

        if (it != nullptr)
            std::cout << ' ';
    }
    std::cout << '\n';
}