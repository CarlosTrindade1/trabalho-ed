#include <iostream>
#define MAX 20

using namespace std;

bool compareStrings(char str1[MAX], char str2[MAX]);

int main() {
    char str[MAX];

    cin >> str;

    int i;

    for (i = 0; str[i]; i++);

    cout << i << endl;

    return 0;
}

bool compareStrings(char str1[MAX], char str2[MAX]) {
    bool isEquals = true;

    if (sizeof(str1) != sizeof(str2)) {
        isEquals = false;
    } else {
        for (int i = 0; i < sizeof(str1); i++) {
            if (str1[i] != str2[i]) {
                isEquals = false;
                return isEquals;
            }
        }
    }

    return isEquals;
}