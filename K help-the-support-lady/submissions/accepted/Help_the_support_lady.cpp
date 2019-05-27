#include<iostream>
#include<algorithm>
using namespace std;



int main()
{
	int caseNr;
	cin >> caseNr;

	for (int caseCount = 1; caseCount <= caseNr; caseCount++)
	{
		int s = 0, k = 0, i = 0, n = 0, a[100005];
		cin >> n;

		while( i < n)
		{
		cin >> a[i]; 
		i++;
		}

		i = 1;

		sort( a, a+n);
		k = a[0];

		while( i < n )
		{
			if( k <= a[i] )
			{
				k = k + a[i];
				s++;
			}
			i++;
		}

		cout << "Case #" << caseCount << ": " << s+1 << endl;
	}
	return 0;
}