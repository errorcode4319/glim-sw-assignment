#include <string>
#include <vector>

using namespace std;

int solution(vector<vector<int>> board, int k) {    
    int answer = 0;
    
    for (int i = 0;i <= k; i++) {
        for (int j = 0;i + j <= k; j++) {
            
            if (i >= board.size()) {
                continue;
            }
            if (j >= board[i].size()) {
                continue;
            }
            
            answer += board[i][j];
        }
    }
    
    return answer;
}