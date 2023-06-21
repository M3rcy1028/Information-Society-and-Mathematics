#pragma once

class Parity
{
private:
	char* original_frame;
	char* coded_frame;
	char* recieved_frame;
	char* reconstructed_frame;
	char ParityNum;

	int bitlen;
	int chance;

	bool method; //false : even, true : odd
	bool error;

	void Sender();
	void Transmission_Channel();
	void Reciever();

public:
	Parity();
	Parity(char* data, bool method);
	~Parity();
	void VRC();

	char* Get_CodedFrame();
	char* Get_RecivedFrame();
	char* Get_ReconstructedFrame();
	char Get_Parity();
	bool IsError();
};