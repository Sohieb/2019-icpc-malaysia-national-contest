#include <iostream>
using namespace std;

int main() 
{
	int caseNr;
	cin >> caseNr;

	for (int caseCount = 1; caseCount <= caseNr; caseCount++)
	{
		int n,k;
		cin>> n >> k;
		int mx = -2*1e9, x, y;
		
		while(n--)
		{
			cin >> x >> y;
			if(y > k)
				mx = max(mx, x-y+k);
			else 
				mx = max(mx, x);
		}
		cout << "Case #" << caseCount << ": " << mx << endl;
	}
	return 0;
}