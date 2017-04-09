/*
 * Problem:
 * Xsquare got bored playing with the arrays all the time. Therefore, he has
 * decided to play with the strings. Xsquare called a string P a "double string"
 * if string P is not empty and can be broken into two strings A and B such that
 * A + B = P and A = B. for eg : strings like "baba" , "blabla" , "lolo" are all
 * double strings whereas strings like "hacker" , "abc" , "earth" are not double
 * strings at all.
 *
 * Today, Xsquare has a special string S consisting of lower case English
 * letters. He can remove as many characters ( possibly zero ) as he wants from
 * his special string S. Xsquare wants to know , if its possible to convert his
 * string S to a double string or not.
 *
 * Help him in accomplishing this task.
 *
 * Note :
 *
 * Order of the characters left in the string is preserved even after deletion
 * of some characters.
 */

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

int main()
{
    unsigned int left_map[26], right_map[26], n_test = 5, i = 0, j = 0, mid = 0, n = 0;
    char in[100];
    bool double_string = false;
    //memset(left_map, 0, sizeof(left_map));
    //memset(right_map, 0, sizeof(right_map));
    scanf("%u", &n_test);
    for (n = 0; n < n_test; ++n) {
        scanf("%s", in);
        double_string = false;
        memset(left_map, 0, sizeof(left_map));
        //memset(right_map, 0, sizeof(right_map));
        for (j = 0; j < strlen(in); ++j) {
            left_map[in[j] - 'a']++;
        }
        for (i = 0; i < 26; ++i) {
            if (left_map[i] > 1) {
                double_string = true;
                break;
            }
        }
        if (double_string) {
            printf("Yes\n");
        } else {
            printf("No\n");
        }
    }
    return 0;
}
