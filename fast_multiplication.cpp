#include <iostream>
#include <string>
#include <math.h>

using namespace std;

/* 
 * Helper function similar to pow(10, n).
 * Just append n zeroes to the string.
 */

string power_of_10 (string a, unsigned long n)
{
    unsigned long i;

    for (i = 0; i < n; ++i) {
        a.append("0");
    }
    return a;
}

string make_equal (string a, unsigned long n)
{
    unsigned long i;
    string out;

    for (i = 0; i < n; ++i) {
        out.append("0");
    }
    out += a;
    return out;
}

void find_max (string &a, string &b)
{
    size_t a_size = a.length(), b_size = b.length();
    string tmp;

    if (a_size == b_size) {
        for (int i = 0; i < a_size; ++i) {
            if (a[i] > b[i]) {
                break;
            } else if (b[i] > a[i]) {
                tmp = a;
                a = b;
                b = tmp;
                break;
            }
        }
    } else {
        cout << "Strings are not of equal size\n";
    }
    return;
}

string strip_string(string s)
{
    size_t pos = s.find_first_not_of('0', 0);

    if (pos > 0 && pos < s.length()) {
        s.erase(0, pos);
    } else if (pos > s.length()) {
        s.erase(0, (s.length() - 1));
    }

    return s;
}

string subtract (string a, string b)
{
    string out;
    int a_size = a.length(), b_size = b.length(), borrow = 0, diff = 0;
    size_t pos;

    if (a_size > b_size) {
        b = make_equal(b, (a_size - b_size));
    } else if (b_size > a_size) {
        a = make_equal(a, (b_size - a_size));
    }
    size_t size = a.size();
    char out_str[size];

    find_max(a, b);

    for (int i = (size - 1); i >= 0; --i) {
        diff = (a[i] - '0') - (b[i] - '0') - borrow;
        if (diff < 0) {
            borrow = 1;
            diff = 10 + diff;
        } else {
            borrow = 0;
        }
        out_str[i] = (diff + '0');
    }
    out_str[size] = '\0';

    return out_str;
}
string add (string a, string b)
{
    unsigned int sum = 0, carry = 0;
    int a_size, b_size, size;
    string out;

    a_size = a.length();
    b_size = b.length();
    if (a_size < b_size) {
        a = make_equal(a, (b_size - a_size));
    } else if (b_size < a_size) {
        b = make_equal(b, (a_size - b_size));
    }
    size = (a_size > b_size ? a_size : b_size);

    char out_str[size];

    for (int i = size-1; i >= 0; --i) {
        sum = ((a[i] - '0') + (b[i] - '0') + carry);
        carry = sum / 10;
        sum %= 10;
        out_str[i] = (char)(sum + '0');
    }
    out_str[size] = '\0';
    if (carry > 0) {
        out += to_string(carry) + out_str;
    } else {
        out = out_str;
    }
    return out;
}

string recursive_multiplication (string op1, string op2)
{
    unsigned long n1;
    string a, b, c, d, res, ad_bc, ac, ad, bc, bd;

    if (op1 == "0" || op2 == "0") {
        return "0";
    }
    if (op1.length() < op2.length()) {
        op1 = make_equal(op1, (op2.length() - op1.length()));
    } else if (op2.length() < op1.length()) {
        op2 = make_equal(op2, (op1.length() - op2.length()));
    }

    if (op1.length() == 1) {
        return to_string((op1[0] - '0') * (op2[0] - '0'));
    }

    size_t n = op1.length();
    if (n % 2 == 0) {
        n1 = n / 2;
    } else if (n != 1) {
        n1 = (n + 1) / 2;
    }

    a = op1.substr(0, n1);
    c = op2.substr(0, n1);
    b = op1.substr(n1);
    d = op2.substr(n1);

    ac = recursive_multiplication(a, c);
    bd = recursive_multiplication(b, d);
    ad = recursive_multiplication(a, d);
    bc = recursive_multiplication(b, c);
    ad_bc = add(ad, bc);

    if (n % 2 == 0) {
        ac = power_of_10(ac, n); 
        ad_bc = power_of_10(ad_bc, n1);
    } else {
        ac = power_of_10(ac, (n - 1)); 
        ad_bc = power_of_10(ad_bc, (n / 2));
    }

    res = add(ac, ad_bc);
    res = add(res, bd);
    res = strip_string(res);

    return res;
}

string karatsuba_multiplication (string op1, string op2)
{
    unsigned long n1;
    string a, b, c, d, res, ad_bc, ac, ad, bc, bd, a_b, c_d, p3;

    if (op1 == "0" || op2 == "0") {
        return to_string(0);
    }
    if (op1.length() < op2.length()) {
        op1 = make_equal(op1, (op2.length() - op1.length()));
    } else if (op2.length() < op1.length()) {
        op2 = make_equal(op2, (op1.length() - op2.length()));
    }

    if (op1.length() == 1) {
        return to_string((op1[0] - '0') * (op2[0] - '0'));
    }

    size_t n = op1.length();

    if (n % 2 == 0) {
        n1 = n / 2;
    } else if (n != 1) {
        n1 = (n + 1) / 2;
    }

    a = op1.substr(0, n1);
    c = op2.substr(0, n1);
    b = op1.substr(n1);
    d = op2.substr(n1);

    ac = karatsuba_multiplication(a, c);
    bd = karatsuba_multiplication(b, d);
    a_b = add(a, b);
    c_d = add(c, d);
    p3 = karatsuba_multiplication(a_b, c_d);
    p3 = subtract(p3, ac);
    p3 = subtract(p3, bd);

    if (n % 2 == 0) {
        ac = power_of_10(ac, n); 
        ad_bc = power_of_10(p3, n1);
    } else {
        ac = power_of_10(ac, (n - 1)); 
        ad_bc = power_of_10(p3, (n / 2));
    }

    res = add(ac, ad_bc);
    res = add(res, bd);
    res = strip_string(res);
    return res;
}

int main()
{
    string op1, op2;
    char in;
    
    do {
        cin >> op1;
        cin >> op2;
        cout << recursive_multiplication(op1, op2) << endl;
        cout << karatsuba_multiplication(op1, op2) << endl;
        cin >> in;
    } while (in != 'q') ;
    return 0;
}
