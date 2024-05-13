#include <iostream>
#include <vector>
using namespace std;
int main(){
	vector<vector<char>> plansza;
	int S, K, GW, GB;
	cin >> S >> K >> GW >> GB;
	int WR, BR;
	char who_starts;
	cin >> WR >> BR >> who_starts;
	int diagonal = 2*S - 1;
	for (int i = 0; i < diagonal; i++) {
		for (int j = 0; j < diagonal; j++){
			char c = getchar();
			if (c != '\n')
				plansza[i][j] = c;
		}
	}
	for (int i = 0; i < diagonal; i++) {
		for (int j = 0; j < diagonal; j++) {
			cout << plansza[i][j];
		}
		cout << endl;
	}
}