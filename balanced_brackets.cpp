#include <iostream>
#include <stack>

using namespace std;

bool is_balanced(string expression)
{
    stack <char> openBrackets;
    char c;
    int i = 0;
    
    for (i = 0; i < expression.length(); ++i) {
        if (expression[i] == '(' || expression[i] == '[' ||
            expression[i] == '{') {
            openBrackets.push(expression[i]);
        } else {
            /* Closed bracket. Check for matching open bracket */
            if (!openBrackets.empty()) {
                c = openBrackets.top();
                openBrackets.pop();
                switch (c) {
                case '(':
                    if (expression[i] != ')') {
                        return false;
                    }
                    break;
                case '{':
                    if (expression[i] != '}') {
                        return false;
                    }
                    break;
                case '[':
                    if (expression[i] != ']') {
                        return false;
                    }
                    break;
                default:
                    /* 
                     * Not possbile unless the characters in the input itself 
                     * is invalid
                     */
                    return false;
                }
            } else {
                return false;
            }
        }
    }
    if (!openBrackets.empty()) {
        /* Some open brackets do not have matching closed ones. */
        return false;
    }
    return true;
}

int main()
{
    int t;
    cin >> t;
    for (int a0 = 0; a0 < t; a0++) {
        string expression;
        cin >> expression;
        bool answer = is_balanced(expression);
        if (answer) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }

    }
    return 0;
}
