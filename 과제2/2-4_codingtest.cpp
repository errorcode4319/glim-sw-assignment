#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int solution(vector<vector<int>> dots) {
    int answer = 0;
    
    static auto compare = [](const vector<int>& a, const vector<int>& b) {
        if (a[0] != b[0]) return a[0] < b[0];
        return a[1] < b[1];
    };
    
    std::sort(dots.begin(), dots.end(), compare);
    
    do {
        
        auto x1 = double(dots[1][0] - dots[0][0]);
        auto y1 = double(dots[1][1] - dots[0][1]);
        auto x2 = double(dots[3][0] - dots[2][0]);
        auto y2 = double(dots[3][1] - dots[2][1]);
        
        auto det = (x1 * y2) - (x2 * y1);
        
        if (det == 0.0)
            answer = 1;
        
    } while(std::next_permutation(dots.begin(), dots.end(), compare));
    
    return answer;
}