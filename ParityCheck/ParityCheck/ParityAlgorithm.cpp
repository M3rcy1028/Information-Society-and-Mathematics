#include "ParityAlgorithm.h"
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdlib>
#include <string>

using namespace std;

Parity::Parity()
{
	
}

Parity::Parity(char* data, bool method)
{
	this->original_frame = data;
	this->bitlen = strlen(data);
	this->method = method; 
	this->ParityNum = 0;
	this->chance = -1;
	while (chance < 1)
	{
		cout << ">> Input the chance of an error occuring for every single bit(integer) : ";
		cin >> this->chance;
	}
	this->error = false;
	this->coded_frame = new char[bitlen + 2];
	this->recieved_frame = new char[bitlen + 2];
	this->reconstructed_frame = new char[bitlen + 2];
	memset(this->coded_frame, '\0', bitlen + 2);
	memset(this->recieved_frame, '\0', bitlen + 2);
	memset(this->reconstructed_frame, '\0', bitlen + 2);
}

Parity::~Parity()
{
	original_frame = nullptr;
	delete[] coded_frame;
	delete[] recieved_frame;
	delete[] reconstructed_frame;
}

void Parity::VRC()
{
	Sender();
	Transmission_Channel();
	Reciever();
	return;
}

//original_data + Parity -> coded_frame
void Parity::Sender()
{
	int cnt = 0; //the number of 1's
	for (int i = 0; i < bitlen; i++)
	{
		coded_frame[i] = original_frame[i];
		if (original_frame[i] == '1')
			cnt++;
	}
	if (method) //odd
	{
		if (cnt % 2 == 0) //the number of 1's is even
		{
			coded_frame[bitlen] = '1';
			ParityNum = '1';
		}
		else
		{
			coded_frame[bitlen] = '0';
			ParityNum = '0';
		}
	}
	else //even
	{
		if (cnt % 2 == 0) //the number of 1's is even
		{
			coded_frame[bitlen] = '0';
			ParityNum = '0';
		}
		else
		{
			coded_frame[bitlen] = '1';
			ParityNum = '1';
		}
	}
	return;
}

//coded_frame --channel--> recieved_frame
void Parity::Transmission_Channel()
{	
	srand((unsigned int)time(NULL));
	for (int i = 0; i < bitlen + 1; i++)
	{
		if (rand() % 101 > chance)
			recieved_frame[i] = coded_frame[i];
		else
		{
			if (coded_frame[i] == '0')
				recieved_frame[i] = '1';
			else
				recieved_frame[i] = '0';
		}
	}
	return;
}

void Parity::Reciever()
{
	int cnt = 0;
	for (int i = 0; i < bitlen; i++)
	{
		if (recieved_frame[i] == '1')
			cnt++;
	}
	
	if (method) //odd
	{
		if (cnt % 2 == 0)
			error = 1;
	}
	else
	{
		if (cnt % 2 != 0)
			error = 1;
	}
	return;
}

char* Parity::Get_CodedFrame()
{
	return coded_frame;
}

char* Parity::Get_RecivedFrame()
{
	return recieved_frame;
}

char* Parity::Get_ReconstructedFrame()
{
	strncpy(reconstructed_frame, recieved_frame, bitlen);
	reconstructed_frame[bitlen + 1] = '\0';
	return reconstructed_frame;
}

char Parity::Get_Parity()
{
	return ParityNum;
}

bool Parity::IsError()
{
	return error;
}