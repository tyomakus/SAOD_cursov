#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <string>
#include <algorithm>
#include <fstream>
#include <cmath>
#include <cstring>
#include <conio.h>

using namespace std;

void QuickSort(char Symbols[], float Prob[], int n, int L, int R) {
	while (L < R) {
		int mid = (L + R) / 2;
		float x = Prob[mid];
		int i = L;
		int j = R;
		while (i <= j) {
			while (Prob[i] > x) {
				i++;
			}
			while (Prob[j] < x) {
				j--;
			}
			if (i <= j) {
				float temp = Prob[i];
				Prob[i] = Prob[j];
				Prob[j] = temp;
				char temp_2 = Symbols[i];
				Symbols[i] = Symbols[j];
				Symbols[j] = temp_2;
				i++;
				j--;
			}
		}
		if (j - L < R - i) {
			QuickSort(Symbols, Prob, n, L, j);
			L = i;
		}
		else {
			QuickSort(Symbols, Prob, n, i, R);
			R = j;
		}
	}
}


float enthropy(int uniqueSymbols, float* textProb) {
	float enthr = 0;
	for (int i = 1; i <= uniqueSymbols; i++) {
		enthr += (textProb[i] * log2(textProb[i]));
	}
	return -enthr;
}

float averageWordLength(int uniqueSymbols, int* lengthWords, float* textProb) {
	float length = 0;
	for (int i = 1; i <= uniqueSymbols; i++) {
		length += lengthWords[i] * textProb[i];
	}
	return length;
}

int getFileSize() {
	ifstream ftext("testBase2.dat", ios::binary);
	if (!ftext.is_open()) {
		cout << "WRONG open file" << endl;
		exit(1);
	}
	int fileSize = 0;
	char ch;
	while ((ch = ftext.get()) != EOF)
		fileSize++;
	return fileSize;
}

int getProb(int asciiProb[]) {
	ifstream ftext("testBase2.dat", ios::binary);
	if (!ftext.is_open()) {
		cout << "WRONG open file" << endl;
		exit(1);
	}
	int Symbols = 0;
	char ch;
	while ((ch = ftext.get()) != EOF) {
		if (asciiProb[(int)ch + 128] == 0) {
			Symbols++;
		}
		asciiProb[(int)ch + 128]++;
	}
	return Symbols;
}


void codeShennon(int uniqueSymbols, float* textProb, int* lengthWords, float* qiMas, char** codeTable) {
	qiMas[0] = 0;
	textProb[0] = 0;
	for (int i = 1; i <= uniqueSymbols; i++) {
		qiMas[i] = qiMas[i - 1] + textProb[i];
		lengthWords[i] = ceil(-log2(textProb[i]));
	}
	for (int i = 1, j = 0; i <= uniqueSymbols; i++, j = 0) {
		for (; j < lengthWords[i]; j++) {
			qiMas[i - 1] = qiMas[i - 1] * 2;
			codeTable[i][j] = (char)(floor(qiMas[i - 1]) + 48);
			if (qiMas[i - 1] > 1) {
				qiMas[i - 1] = qiMas[i - 1] - 1;
			}
		}
		codeTable[i][j] = '\0';
	}
}



int main() {
	setlocale(LC_ALL, "Russian");
	int fileSize = getFileSize();

	int* asciiProb = new int[256];

	for (int i = 0; i < 256; i++)
		asciiProb[i] = 0;

	int* uniqueSymbols = new int;
	*uniqueSymbols = getProb(asciiProb);
	char* textSymbols = new char[*uniqueSymbols + 1];
	float* textProb = new float[*uniqueSymbols + 1];

	int* lengthWords_Shennon = new int[*uniqueSymbols + 1];

	for (int i = 0; i <= *uniqueSymbols; i++) {
		lengthWords_Shennon[i] = 0;

	}

	float* qiMas = new float[*uniqueSymbols + 1];

	char** codeTable_Shennon = new char* [*uniqueSymbols + 1];

	for (int i = 0; i <= *uniqueSymbols; i++) {
		codeTable_Shennon[i] = new char[*uniqueSymbols + 1];
	}

	for (int i = 0, j = 1; i < 256; i++) {
		if (asciiProb[i] != 0) {
			textSymbols[j] = i - 128;
			textProb[j] = (float)asciiProb[i] / fileSize;
			j++;
		}
	}


	QuickSort(textSymbols, textProb, *uniqueSymbols, 1, *uniqueSymbols);

	codeShennon(*uniqueSymbols, textProb, lengthWords_Shennon, qiMas, codeTable_Shennon);

	cout.setf(ios::left);
	cout.width(70);
	cout << setw(10) << "Symbol" << setw(15) << "Chance" << setw(20) << "Code word" << setw(20) << "Length of code" << endl;
	for (int i = 1; i <= *uniqueSymbols; i++) {
		cout << setw(10) << textSymbols[i] << setw(15) << textProb[i] << setw(20) << codeTable_Shennon[i] << setw(20) << lengthWords_Shennon[i] << endl;
	}


	cout << setw(10) << enthropy(*uniqueSymbols, textProb) << endl;
	cout << averageWordLength(*uniqueSymbols, lengthWords_Shennon, textProb);

}

