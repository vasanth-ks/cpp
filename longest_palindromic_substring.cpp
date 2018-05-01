#include <iostream>
#include <string>

using namespace std;

/* Function to check the result of longestPalindrome function*/
bool isPlaindrome (string str, int start, int end)
{
    bool palindrome = true;

    if (start == end) {
        return true;
    } else if ((end - start) == 1) {
        return (str[start] == str[end]);
    } else if (start > end) {
        return false;
    }

    if (str[start] == str[end]) {
        palindrome &= isPlaindrome(str, (start+1), (end-1));
    } else {
        palindrome = false;
    }

    return palindrome;
}

/* Function to find the longest palindrome substring present in a given string */
string longestPalindrome (string s)
{
    int i = 0, j = 0, k = 0, table[s.size()][s.size()], resultSize = 0;
        int strSize = 0, start = 0, end = 0;
        bool equal = false;
        string result;

        if (s.size() <= 1) {
            return s;
        }

        for (j = (i+1); j < s.size(); ++j) {
            equal = (s[i] == s[j]);
            if ((j - i) > 2) {
                table[i][j] = table[i+1][j-1] & equal;
            } else {
                table[i][j] = equal;
            }
            if (table[i][j]) {
                strSize = ((j - i) + 1);
                if (strSize > resultSize) {
                    resultSize = strSize;
                    start = i;
                    end = j;
                }
            }
            for (k = (i+1); k < j; ++k) {
                equal = (s[k] == s[j]);
                if ((j - k) > 2) {
                    table[k][j] = equal & table[k+1][j-1];
                } else {
                    table[k][j] = equal;
                }
                if (table[k][j]) {
                    strSize = ((j - k) + 1);
                    if (strSize > resultSize) {
                        resultSize = strSize;
                        start = k;
                        end = j;
                    }
                }
            }
        }
        if (resultSize == 0) {
            start = 0;
            resultSize = 1;
        }
        result.append(s, start, resultSize);

        return result;
}

int main()
{
    string str, outStr;
    printf("Enter the string: ");
    cin >> str;

    outStr = longestPalindrome(str);
    printf("Longest palindrom in the string %s is %s\n", str.c_str(), outStr.c_str());
    printf("%s is palindrome: %d\n", outStr.c_str(), isPlaindrome(outStr, 0, (outStr.size() - 1)));

    return 0;
}
