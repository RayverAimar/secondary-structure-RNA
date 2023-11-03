#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

void printMatrix(const vector<vector<int>>& dp, std::string sequence) {

    std::cout << std::setw(3) << " ";
    for (int i = 0; i < sequence.size(); i++)
        std::cout << std::setw(3) << sequence[i];
    std::cout << std::endl;

    for (int i = 0; i < dp.size(); i++)
    {
        for (int j = 0; j < dp.size(); j++)
        {
            if (j == 0)
            {
                std::cout << std::setw(3) << sequence[i];
            }
            std::cout << std::setw(3) << dp[i][j];
        }
        std::cout << std::endl;
    }

}

void traceBack(const vector<vector<int>>& dp, const string& sequence) {
    int n = dp.size();
    int mid = n/2;
    int i = 0;
    int j = n - 1;
    bool paired_before = false;
    bool not_paired_before = false;

    if(n%2 == 1) mid++;

    cout << "Estructura para secuencia: " << sequence << std::endl;

    while (i < mid && j >= mid) {
        
        if (i + 1 < n && j - 1 >= 0 && dp[i][j] == dp[i + 1][j - 1] - 1)
        {
            if (paired_before)
                cout << "  |   |" << std::endl;
            if (not_paired_before)
                cout << " \\     /" << std::endl;
            cout << "  " << sequence[i] << " - " << sequence[j] << " " << std::endl;
            not_paired_before=false;
            paired_before=true;
            i++;
            j--;
        }
        else if (i + 1 < n && dp[i][j] == dp[i + 1][j]) {
            if (paired_before)
                cout << " /     \\" << std::endl;
            if (not_paired_before)
                cout << "|       |" << std::endl;
            cout << sequence[i] << "       " << sequence[j] << std::endl;
            not_paired_before=true;
            paired_before=false;
            i++;
        }
        else if (j - 1 >= 0 && dp[i][j] == dp[i][j - 1]) {
            if (paired_before)
                cout << " /     \\" << std::endl;
            if (not_paired_before)
                cout << "|       |" << std::endl;
            cout << sequence[i] << "       " << sequence[j] << std::endl;
            not_paired_before=true;
            paired_before=false;
            j--;
        }
        else {
            i++;
            j--;
        }
    }
    if (paired_before)
    {
        cout << "  |___|" << std::endl;
    }
    if (not_paired_before)
    {
        cout << "\\_______/" << std::endl;
    }
}

int main() {
    string sequence = "ACUCGAUUCCGAG";
    int n = sequence.length();
    vector<vector<int>> dp(n, vector<int>(n, 0));

    for (int len = 1; len < n; len++) {
        for (int i = 0; i < n - len; i++) {
            int j = i + len;
            // Caso 1: Bases apareadas (A-U, C-G, G-U, ...)
            if ((sequence[i] == 'A' && sequence[j] == 'U') || 
                (sequence[i] == 'U' && sequence[j] == 'A') || 
                (sequence[i] == 'C' && sequence[j] == 'G') || 
                (sequence[i] == 'G' && sequence[j] == 'C') || 
                (sequence[i] == 'G' && sequence[j] == 'U') || 
                (sequence[i] == 'U' && sequence[j] == 'G'))
            {
                dp[i][j] = dp[i + 1][j - 1] - 1;
            }
            else
            {
                // Caso 2: Bases no apareadas
                for (int k = i; k < j; k++)
                {
                    dp[i][j] = min(dp[i][j], dp[i][k] + dp[k + 1][j]);
                }
            }
        }
    }

    //printMatrix(dp, sequence);

    traceBack(dp, sequence);

    return 0;
}

//Realizar el traceback en una matriz