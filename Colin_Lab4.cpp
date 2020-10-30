/*This is Colin McClevarts Lab 4 solution for CSC 1501 Fall 2020

In this lab, we will use Python (or C++) to implement a Hamming code (refer to the handout given
in class).
1. Hamming Functions Tester (25 points)
Write a function that displays a menu to test the functions from 2 - 4. You must call the
functions from 2 - 4 and cannot reimplement their functionality in this function. The menu
is displayed as follows:
1) Enter a 4-bit message to encode into a 7-bit Hamming message.
2) Enter a 7-bit Hamming message to transmit through a noisy channel.
3) Enter a 7-bit Hamming message to receive and correct.
4) Quit.
If the user selects 1, the function from Problem 2 is used and so on. All requests for input from
the user should be handled inside of this function, and all output to the screen should also be
handled inside of this function. Use a while loop to implement the quitting mechanism.
2. Hamming Transmitter (25 points)
Write a function that takes as input a 4-bit string of 0’s and 1’s. Output the 7-bit encoded
message. For example, if the passed parameter is 1011, the output should be 0110011.
3. Noisy Channel (25 points)
Write a function that models a noisy channel. It takes as input the original 7-bit hamming
message. Using a random number generator, it randomly selects one of the 7 positions to flip.
For example, if the original message is 0110011, the noisy channel randomly flips bit 3 causing
the new message to become 0100011. As output, the function should return both the flipped
message and the bit that was flipped (3 in this case).
4. Hamming Receiver (25 points)
Write a function that receives a 7-bit Hamming message as input that may or may not have
an error message. If it does, output the corrected message and the location of the bit that
was corrected. For example, the message 0100011 should be corrected to 0110011. In addition
to displaying the corrected message, 3 should also be displayed as the bit location that was
corrected. On the other hand, if the message received is correct (or no error can be detected),
output a 0 to indicate that no bits were corrected.

*/

//Preprocessor Directives
#include <iostream>//For cin and cout
#include <string>//For use of strings
#include <cstdlib>//For rand() and srand()
#include <ctime>//For time which is used to generate a seed for srand()

using namespace std;

//Function prototypes
string hammingTransmitter(string);
string noisyChannel(string, int&);
string hammingReceiver(string, int&);

int main()
{
	int selection;//User picks an option between 1 & 4
	string fourBit, sevenBit, changedSeven;//fourBit holds string for problem 2. sevenBit holds string for problem 2 & 3. changedSeven is used to accept a returned string from problem 4
	int bit = 0;//Used to hold location of bit determined in problem 3 & 4

	//Display Menu
	cout << "Welcome to my Hamming Menu" << endl;
	cout << "Choose an option from 1-4" << endl;
	do
	{
		cout << "1) Enter a 4-bit message to encode into a 7-bit Hamming message." << endl;
		cout << "2) Enter a 7-bit Hamming message to transmit through a noisy channel." << endl;
		cout << "3) Enter a 7-bit Hamming message to receive and correct." << endl;
		cout << "4) Quit." << endl;
		cout << "Selection: ";
		cin >> selection;
		cout << endl;

		if (selection == 1)//4-bit encoding
		{
			cout << "Enter a 4-bit message to encode into a 7-bit Hamming message: ";
			cin >> fourBit;
			cout << fourBit << " encoded into a 7-bit Hamming message: " << hammingTransmitter(fourBit) << endl << endl;
		}
		else if (selection == 2)//Noisy Channel
		{
			cout << "2) Enter a 7-bit Hamming message to transmit through a noisy channel: ";
			cin >> sevenBit;
			cout << sevenBit << " transmitted through a noisy channel produced: " << noisyChannel(sevenBit, bit) << endl;
			cout << "Bit changed: " << bit << endl << endl;
		}
		else if (selection == 3)//Correct 7-bit
		{
			bit = 0;
			cout << "3) Enter a 7-bit Hamming message to receive and correct: ";
			cin >> sevenBit;
			changedSeven = hammingReceiver(sevenBit, bit);
			if (bit == 0)//If 7-bit was determined to have no error bits
			{
				cout << sevenBit << " Hamming message was determined to be correct!" << endl << endl;
			}
			else//If 7-bit had an error
			{
				cout << sevenBit << " Hamming message was determined to be incorrect!" << endl;
				cout << sevenBit << " should be: " << changedSeven << endl;
				cout << "Bit " << bit << " was determined to be the incorrect bit" << endl << endl;
			}

		}
		else if (selection == 4)//Quit
		{
			cout << "Thanks for using this program! Have a ham of a day!" << endl;
			exit(1);
		}
		else
		{
			cout << "You entered an invalid response" << endl;
		}

	} while (selection != 4);//Menu displays until user chooses to quit

	return 0;
}
string hammingTransmitter(string four)
{
	string seven = "0000000";
	//Set the four non parity bits to the four digit number passed
	seven[2] = four[0];
	seven[4] = four[1];
	seven[5] = four[2];
	seven[6] = four[3];
	
	//p1 - p7 are the positions of the bits in the string seven. These are used to calculate the parity bits. Sum is used to keep a total of bit addition
	int p1, p2, p3, p4, p5, p6, p7, sum;

	//Determining what integer each position should hold prior to calculations (using ascii table)
	if (seven[0] == 48)
	{
		p1 = 0;
	}
	else p1 = 1;
	if (seven[1] == 48)
	{
		p2 = 0;
	}
	else p2 = 1;
	if (seven[2] == 48)
	{
		p3 = 0;
	}
	else p3 = 1;
	if (seven[3] == 48)
	{
		p4 = 0;
	}
	else p4 = 1;
	if (seven[3] == 48)
	{
		p5 = 0;
	}
	else p5 = 1;
	if (seven[5] == 48)
	{
		p6 = 0;
	}
	else p6 = 1;
	if (seven[6] == 48)
	{
		p7 = 0;
	}
	else p7 = 1;

	//Now summing up positions to determine if each parity bit should hold a 1 or 0 (looking to determine parity bits in positions 1, 2, 4)
	sum = p1 + p3 + p5 + p7;
	if (sum % 2 == 0)
	{
		seven[0] = '0';
	}else seven[0] = '1';

	sum = p2 + p3 + p6 + p7;
	if (sum % 2 == 0)
	{
		seven[1] = '0';
	}
	else seven[1] = '1';

	sum = p4 + p5 + p6 + p7;
	if (sum % 2 == 0)
	{
		seven[3] = '0';
	}
	else seven[3] = '1';

	return seven;
}
string noisyChannel(string seven, int &b)
{
	//Generating a seed based on the time since January 1, 1970. This ensures different random numbers will be used each time the program runs
	unsigned seed;
	seed = time(0);
	srand(seed);

	b = rand() % 7 + 1;//Randomly selecting a bit to be changed between 1 & 7

	if (seven[b - 1] == '0')//If the location in the 7-bit string is 0 it is flipped to 1. Else the 1 is flipped to 0
	{
		seven[b - 1] = '1';
	}
	else seven[b - 1] = '0';

	return seven;
}
string hammingReceiver(string seven, int &b)
{
	string copy = seven;//Copy will be passed back, either holding a new string or the same as before
	int count = 0;//Holds the amount of incorrect parity bits, if it is zero then the message was sent correctly
	int pos = 0;//Holds the position of the failed bit
	//p1 - p7 are the positions of the bits in the string seven. These are used to calculate the parity bits. Sum is used to keep a total of bit addition
	int p1, p2, p3, p4, p5, p6, p7, sum;
	//Determining what integer each position should hold prior to calculations
	if (seven[0] == 48)
	{
		p1 = 0;
	}
	else p1 = 1;
	if (seven[1] == 48)
	{
		p2 = 0;
	}
	else p2 = 1;
	if (seven[2] == 48)
	{
		p3 = 0;
	}
	else p3 = 1;
	if (seven[3] == 48)
	{
		p4 = 0;
	}
	else p4 = 1;
	if (seven[4] == 48)
	{
		p5 = 0;
	}
	else p5 = 1;
	if (seven[5] == 48)
	{
		p6 = 0;
	}
	else p6 = 1;
	if (seven[6] == 48)
	{
		p7 = 0;
	}
	else p7 = 1;

	//Determining if the parity bits in the passed 7-bit string are holding the values that they should be. If sum is an even number then the parity bits should be holding a 0
	sum = p1 + p3 + p5 + p7;
	if (sum % 2 == 0)
	{
		if (seven[0] == '0')
		{
			count += 0;
		}
	}
	else
	{
		count ++;
		pos += 1;
	}

	sum = p2 + p3 + p6 + p7;
	if (sum % 2 == 0)
	{
		if (seven[1] == '0')
		{
			count += 0;
		}
	}
	else
	{
		count ++;
		pos += 2;
	}

	sum = p4 + p5 + p6 + p7;
	if (sum % 2 == 0 && seven[3] == '0')
	{
		if (seven[3] == '0')
		{
			count += 0;
		}
	}
	else
	{
		count ++;
		pos += 4;
	}

	if (count > 0)//There was an error determined. pos - 1 holds the location of the error bit
	{
		if (copy[pos-1] == '0')
		{
			copy[pos-1] = '1';
		}
		else copy[pos-1] = '0';
		b = pos;
	}
	return copy;
}