/*
 * Problem:
     Little Jhool is back, with his matchmaker friend Dawgie.
 
     Dawgie's logic for approving a girl with a boy or a boy with a girl, is simple:
     if the name of a girl has maximum similar characters to the name of a guy, they
     are definitely not fit for being with each other. For example, a couple
     with Shubhami and Shubham is less ideal than a couple with Shubham and
     Dhinsat. Since Shubhami and Shubham have 6 characters in common while the
     other couple has 3 characters in common, so the other couple is much more
     ideal.
     
     Now our Little Jhool gives the list of all the crushes in his life to Dawgie,
     and asks him to tell the top K numbers of girls out of the list of N girls, he
     gives who'll be a good match for Little Jhool.
     
     Note-1: The case of the letters does NOT matter.
     Note-2: The name of Little Jhool is: "LittleJhool", without the space and
     quotes, where the unique characters present in his name are: [l, i, t, e,
     j,h,o].
     Note-3: In case of a tie, print the names in order of their occurrence.
 */
#include <iostream>
#include <vector>
#include <string>
#include <list>
#include <cmath>
#include <cstring>

using namespace std;

int main()
{
    int n_test = 0, n_names, n_match, diff = 0, i, j;
    int k = 0;
    list <string> out;
    vector <list <string> > diff_vec(26);
    int ref_map[26], match_found = 0, cmp_map[26];
    string ref_str = "littlejhool", in_str = "\0";

    memset(ref_map, 0, sizeof(ref_map));
    
    for (i = 0; i < ref_str.size(); ++i) {
        ref_map[ref_str[i] - 'a']++;
    }
    cin >> n_test;
    for (i = 0; i < n_test; ++i) {
        cin >> n_names >> n_match;
        for (j = 0; j < n_names; ++j) {
            cin >> in_str;
            match_found = 0;
            memset(cmp_map, 0, sizeof(cmp_map));
            for (k = 0; k < in_str.size(); ++k) {
                cmp_map[tolower(in_str[k]) - 'a']++;
            }
            for (k = 0; k < 26; ++k) {
                if (ref_map[k] > 0 && cmp_map[k] > 0) {
                    match_found++;
                }
            }
            diff_vec[match_found].push_back(in_str);
        }
        j = 0;
        for (k = 0; k < 26; ++k) {
            out = diff_vec[k];
            list <string>::iterator it;
            for (it = out.begin(); it != out.end() && j < n_match; ++it) {
                cout << *it << " ";
                ++j;
            }
            diff_vec[k].clear();
        }
        cout << endl;
    }
}
