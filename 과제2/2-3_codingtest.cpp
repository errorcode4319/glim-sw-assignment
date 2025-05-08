#include <string>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

int solution(int a, int b, int c, int d) {
    
    int answer = 0;
    
    struct Data {
        int num;
        int count;
    };
    
    std::vector<Data> v;
    
    for (int i=0;i<=6;i++)
        v.push_back({.num=i, .count=0,});
    
    v[a].count++;
    v[b].count++;
    v[c].count++;
    v[d].count++;
    
    std::sort(v.begin(), v.end(), [](const auto& a, const auto& b) {
        return a.count > b.count;
    });
    
    if (v[0].count == 4) {
        answer = 1111 * v[0].num;
    }
    else if (v[0].count == 3) {
        answer = 10 * v[0].num + v[1].num;
        answer *= answer;
    }
    else if (v[0].count == 2) {
        if (v[1].count == 2) {
           answer = (v[0].num + v[1].num) * std::abs(v[1].num - v[0].num);
        }
        else if (v[1].count == 1) {
            answer = v[1].num * v[2].num;
        }
    }
    else {
        std::sort(v.begin(), v.end(), [](const auto& a, const auto& b) {
            if (a.count != b.count) 
                return a.count > b.count;
            return a.num < b.num;
        });
        answer = v[0].num;
    }
    
    return answer;
}