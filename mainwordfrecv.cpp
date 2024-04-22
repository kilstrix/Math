#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <queue>
#include <cctype>
#include <vector>

using namespace std;

ifstream f("frecv.in");

struct comparare_cuvinte {
    bool operator()(pair<string, int> a, pair<string, int> b) {
        if (a.second == b.second)
            return a.first > b.first;
        return a.second < b.second;
    }
};
int main() {
    string input_s, s;
    while (getline(f, input_s))
        s = s + input_s + " ";
    f.close();

    map<string, int> mapafn;

    string de = ", ;?.!";
    string current;
    for (auto i = 0; i < s.size(); i++)
    {
        if (de.find(s[i]) != -1)
        {
            if (!current.empty())
            {
                mapafn[current] = mapafn[current] + 1;
                current.clear();
            }
        }
        else
            current += tolower(s[i]);
    }
    if (!current.empty())
    {
        mapafn[current] = mapafn[current] + 1;
    }

    priority_queue<pair<string, int>, vector<pair<string, int>>, comparare_cuvinte> prio;

    for (auto x : mapafn)
        prio.push(x);

    while (!prio.empty()) {
        auto elem = prio.top();
        prio.pop();
        cout << elem.first << " => " << elem.second << endl;
    }

    return 0;
}