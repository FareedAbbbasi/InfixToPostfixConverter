#include <iostream>
#include <stack>
using namespace std;

template <class T>
class Stack {
private:
    struct Node {
        T data;
        Node* next;
        Node(T val, Node* link = 0) : data(val), next(link) {}
    };
    Node* top;

public:
    Stack() : top(0) {}
    const bool empty() { return top == 0; }
    void push(const T& val);
    T pop();
    T peep();
    string display();
};

template <class T>
void Stack<T>::push(const T& val) {
    Node* n = new Node(val);
    n->next = top;
    top = n;
}

template <class T>
T Stack<T>::pop() {
    if (top == 0) {
        cout << "\nStack is empty\n";
        return 0;
    }
    Node* n = top;
    T val = top->data;
    top = n->next;
    delete n;
    return val;
}

template <class T>
T Stack<T>::peep() {
    if (top == 0) {
        cout << "\nStack is empty\n";
        return 0;
    }
    return top->data;
}

template <class T>
string Stack<T>::display() {
    string s;
    for (Node* n = top; n != 0; n = n->next)
        s += n->data;
    return s;
}

const bool isOperator(char s) {
    return s == '+' || s == '-' || s == '*' || s == '/' || s == '^';
}

const int precedence(char s) {
    switch (s) {
    case '+':
    case '-': return 1;
    case '*':
    case '/': return 2;
    case '^': return 3;
    default: return 0;
    }
}

string infixtopostfix(const string infix) {
    cout << "\n========================== Conversion Steps ==========================\n";
    cout << "Symbol\t\tStack\t\tPostfix Expression\n";
    cout << "----------------------------------------------------------------------\n";

    string postfix;
    Stack<char> stack;

    for (int i = 0; i < infix.size(); i++) {
        char symbol = infix[i];

        if (symbol == '(') {
            stack.push(symbol);
        }
        else if (symbol == ')') {
            while (stack.peep() != '(') {
                postfix += stack.pop();
            }
            stack.pop(); // Remove '(' from the stack
        }
        else if (isOperator(symbol)) {
            if (stack.empty() || stack.peep() == '(') {
                stack.push(symbol);
            }
            else {
                while (!stack.empty() && precedence(symbol) <= precedence(stack.peep())) {
                    postfix += stack.pop();
                }
                stack.push(symbol);
            }
        }
        else { // Operand
            postfix += symbol;
        }

        cout << symbol << "\t\t" << stack.display() << "\t\t" << postfix << endl;
    }

    while (!stack.empty()) {
        postfix += stack.pop();
    }

    return postfix;
}

int main() {
    cout << "===========================================================\n";
    cout << "|         Welcome to the Infix to Postfix Converter       |\n";
    cout << "===========================================================\n";
    cout << "\nEnter an infix expression: ";

    string infix;
    cin >> infix;

    try {
        string postfix = infixtopostfix(infix);
        cout << "\n===========================================================\n";
        cout << "|                     Conversion Complete                 |\n";
        cout << "===========================================================\n";
        cout << "Infix Expression  : " << infix << endl;
        cout << "Postfix Expression : " << postfix << endl;
        cout << "===========================================================\n";
    }
    catch (const exception& e) {
        cerr << "\nError: " << e.what() << endl;
    }

    return 0;
}
