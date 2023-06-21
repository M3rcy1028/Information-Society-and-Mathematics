#include "ParityAlgorithm.h"
#include <iostream>
#include <iomanip>
using namespace std;

#define MAX_BUFFER_SIZE 512

/*Vertical Redundancy Check*/

int main()
{
	char buf[MAX_BUFFER_SIZE];
	bool method;
	cout << ">> Parity Check / Even(0), Odd(1) : ";
	cin >> method;
	cout << ">> Data : ";
	cin >> buf;
	Parity p = Parity(buf, method);
	p.VRC();

	cout.setf(ios::left);
	cout << "---------------------------------------------------" << endl;
	cout << "Parity			: " << p.Get_Parity() << endl;
	cout << "Coded Frame		: " << p.Get_CodedFrame() << endl;
	cout << "Recieved Frame		: " << p.Get_RecivedFrame() << endl;
	cout << "Reconstructed data	: " << p.Get_ReconstructedFrame() << endl;
	cout << "---------------------------------------------------" << endl;
	
	if (p.IsError())
		cout << ">> Error Occurs." << endl;
	else
		cout << ">> No Error Occurs." << endl;

	return 0;
}