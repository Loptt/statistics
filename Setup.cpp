#include <iostream>
#include <string>
#include <cmath>
#include <cstdlib>
#include <time.h>
#include <unistd.h>
using namespace std;

//Japanese ship names
const string sJapaneseCarrier = "Ryujo Carrier";
const string sJapaneseBattleship = "Nagato Battleship";
const string sJapaneseCruiser = "Furutaka Cruiser";
const string sJapaneseSubmarine = "Ro-51 Submarine";
const string sJapaneseDestroyer = "Kamikaze Destroyer";

//American ships names
const string sAmericanCarrier = "USS Princeton Carrier";
const string sAmericanBattleship = "USS Arizona Battleship";
const string sAmericanCruiser = "USS Minneapolis Cruiser";
const string sAmericanSubmarine = "USS Hawkbill Submarine";
const string sAmericanDestroyer = "USS Frankford Destroyer";

/*	
cleanScreen
Function to clean up the screen of any element
Parameters: none
Retrun nothing
*/
void cleanScreen()
{
	for (int iCounter = 0; iCounter < 50; ++iCounter)
	{
		cout << endl;
	}
}

/*
getPlayerName
Function to let the user input a name to use
Paramenters: none
Return: a string with the name
*/
string getPlayerName()
{
	string sName;
	cout << "Enter your name: " << endl;
	cin >> sName;
	return sName;
}

/*
chooseTeam
Function to let the user choose a team through a char
Paramenters: none
Return: a char representing a team
*/
char chooseTeam()
{
	char cTeam;

	cout << "Do you want to play as Japan (J) or the United States (U)?" << endl;
	cin >> cTeam;

	while (cTeam != 'J' && cTeam != 'U' && cTeam != 'j' && cTeam != 'u')
	{
		cout << "Invalid team, please enter a valid letter" << endl;
		cin >> cTeam;
	}

	return cTeam;
}

/*
eraseBoard
Function to fill a board with zeroes (empty board)
Paramenters: a Matrix board
Return: nothing
*/
void eraseBoard(int iMatBoard[10][10])
{
	for (int iRowIndex = 0; iRowIndex < 10; ++iRowIndex)
	{
		for (int iColIndex = 0; iColIndex < 10; ++iColIndex)
		{
			iMatBoard[iRowIndex][iColIndex] = 0;
		}
	}
}

/*
printSetupBoard
Function to print the player or computer board in the console
Parameters: The board to print
Return: nothing
*/
void printSetupBoard(int iMatBoard[10][10])
{
	cout << "\x1b[37m                           YOUR BOARD" << endl << endl;
	cout << "              A   B   C   D   E   F   G   H   I   J" << endl;
	cout << "             _______________________________________ " << endl;

	for (int iRowIndex = 0; iRowIndex < 10; ++iRowIndex)
	{
		cout << "            |   |   |   |   |   |   |   |   |   |   |" << endl;
		cout << "          " << iRowIndex << " ";

		for (int iColIndex = 0; iColIndex < 10; ++iColIndex)
		{
			if (iMatBoard[iRowIndex][iColIndex])
			{
				cout << "|\x1b[0m O \x1b[37m";
			}
			else
			{
				cout << "|\x1b[34m . \x1b[37m";
			}
		}
		cout << "|" << endl;
		cout << "            |___|___|___|___|___|___|___|___|___|___|" << endl;		
	}
	cout << "\x1b[0m" << endl << endl;
}

/*
writeUserInput
Function to write the ship position on the board
Parameters: The board, a boolean to validate the position, the first position, and the second position, and an array to store the location
Return: nothing
*/
void writeUserInput(int iMatBoard[10][10], bool &bIsWrongInput, string sFirstPosition, string sSecondPosition, int iArrShipPosition[],
				int iShipSize)
{
	int iFirstLetterCoordinate = sFirstPosition[0] - 65;
	int iSecondLetterCoordinate = sSecondPosition[0] - 65;
	int iFirstNumberCoordinate = sFirstPosition[1] - 48;
	int iSecondNumberCoordinate = sSecondPosition[1] - 48;

	int iRowIndexStart;
	int iColIndexStart;

	int iColIndexEnd;
	int iRowIndexEnd;

	bIsWrongInput = false;

	//For vertical positioning
	if (iFirstLetterCoordinate == iSecondLetterCoordinate)
	{
        //First value in iArrShipPosition indicates orientation, 1 means horizontal, 0 means vertical
		iArrShipPosition[0] = 0;

		int iColIndex = iFirstLetterCoordinate;

		//Second value in iArrShipPosition indicates the column index
		iArrShipPosition[1] = iColIndex;

		if (iFirstNumberCoordinate > iSecondNumberCoordinate)
		{
			iRowIndexStart = iSecondNumberCoordinate;
			iRowIndexEnd = iFirstNumberCoordinate;
		}
		else
		{
			iRowIndexStart = iFirstNumberCoordinate;
			iRowIndexEnd = iSecondNumberCoordinate;	
		}

		int iLoopInitiator = iRowIndexStart;

		for (iRowIndexStart; iRowIndexStart <= iRowIndexEnd; ++iRowIndexStart)
		{
			if (iMatBoard[iRowIndexStart][iColIndex])
			{	
				cout << "\x1b[31mInvalid coordinates. Space already occupied by another ship\x1b[0m" << endl;
				bIsWrongInput = true;
				break;
			}
		}

		if (!bIsWrongInput)
		{
			int iCounter = 2;
			for (iRowIndexStart = iLoopInitiator; iRowIndexStart <= iRowIndexEnd; ++iRowIndexStart, ++iCounter)
			{
				iArrShipPosition[iCounter] = iRowIndexStart;
				iMatBoard[iRowIndexStart][iColIndex] = 1;
			}
		}
	}

	//For horizontal positioning
	else
	{
		//First value in iArrShipPosition indicates orientation, 1 means horizontal, 0 means vertical
		iArrShipPosition[0] = 1;

		int iRowIndex = iFirstNumberCoordinate;

		//Second value in iArrShipPosition indicates the row index
		iArrShipPosition[1] = iRowIndex;

		if (iFirstLetterCoordinate > iSecondLetterCoordinate)
		{
			iColIndexStart = iSecondLetterCoordinate;
			iColIndexEnd = iFirstLetterCoordinate;
		}
		else
		{
			iColIndexStart = iFirstLetterCoordinate;
			iColIndexEnd = iSecondLetterCoordinate ;
		}

		int iLoopInitiator = iColIndexStart;

		for (iColIndexStart; iColIndexStart <= iColIndexEnd; ++iColIndexStart)
		{
			if (iMatBoard[iRowIndex][iColIndexStart])
			{
				cout << "\x1b[31mInvalid coordinates. Space already occupied by another ship\x1b[0m" << endl;
				bIsWrongInput = true;
				break;
			}
		}

		if (!bIsWrongInput)
		{
			int iCounter = 2;	
			for (iColIndexStart = iLoopInitiator; iColIndexStart <= iColIndexEnd; ++iColIndexStart, ++iCounter)
			{
				iArrShipPosition[iCounter] = iColIndexStart;
				iMatBoard[iRowIndex][iColIndexStart] = 1;
			}
		}
	}
}

/*
readUserPositions
Function to let the user input coordinates
Parameters: The player board, the size of the ship to input, and an array storing the location
Return: nothing
*/
void readUserPositions(int iMatBoard[10][10], int iShipSize, int iArrShipPosition[])
{
	string sFirstPosition;
	string sSecondPosition;

	int iDifference = 0;

	bool bIsWrongInput = true; 

	while (bIsWrongInput)
	{
		cin >> sFirstPosition >> sSecondPosition;

		//Check if the coordinates are two characters long
		if (sFirstPosition.length() != 2 || sSecondPosition.length() != 2)
		{
			cout << "\x1b[31mInvalid coordinates. Please enter two characters per coordinate\x1b[0m" << endl;
		}
		else
		{
			//Check if the first character is a letter in valid range
			if (sFirstPosition[0] < 65 || sFirstPosition[0] > 74)
			{
				cout << "\x1b[31mInvalid coordinates. Please enter letters from A to J capitalized\x1b[0m" << endl;
			}
			else
			{
				//Check if the second character is a number in valid range
				if (sFirstPosition[1] < 48 || sSecondPosition[1] > 57)
				{
					cout << "\x1b[31mInvalid coordinates. Please enter a digit as second parameter\x1b[0m" << endl;
				}
				else
				{
					//Check if the coordinates are valid positions
					if (sFirstPosition[0] != sSecondPosition[0] &&
	      	   			sFirstPosition[1] != sSecondPosition[1])
					{
						cout << "\x1b[31mInvalid coordinates. Please place ships horizontally or vertically\x1b[0m" << endl;
					}
					else
					{
						if (sFirstPosition[0] == sSecondPosition[0])
						{
							iDifference = abs(sFirstPosition[1] - sSecondPosition[1]) + 1; 
						}
						else
						{
							iDifference = abs(sFirstPosition[0] - sSecondPosition[0]) + 1; 
						}

						//Check if the ship is of adequate size
						if (iDifference != iShipSize)
						{
							cout << "\x1b[31mInvalid coordinates. Please make sure the coordinates are for a ship of size ";
							cout << iShipSize << "\x1b[0m" <<endl;
						}
						else
						{
							writeUserInput(iMatBoard, bIsWrongInput, sFirstPosition, sSecondPosition, iArrShipPosition, iShipSize);
						}
					}
				}
			}
		}
	}
}

/*
getPlayerPositions
Function to ask the user for the ship positions 
Parameters: The Player board, the name, the char of the team, and an array for each ship to store location
Retrun nothing
*/
void getPlayerPositions(int iMatPlayerBoard[10][10], string sPlayerName, char cTeam, int iArrPlayerCarrierPosition[7],
                        int iArrPlayerBattleshipPosition[6], int iArrPlayerCruiserPosition[5],
			   			int iArrPlayerSubmarinePosition[5], int iArrPlayerDestroyerPosition[4])
{
	int iShipSize;

	if (cTeam == 'J' || cTeam == 'j')
	{
		printSetupBoard(iMatPlayerBoard);

		//Carrier
		iShipSize = 5;

		cout << "Admiral " << sPlayerName << "-San, enter the starting and ending coordinates of your " << sJapaneseCarrier;
		cout << " (" << iShipSize << " spaces)" << endl;

		readUserPositions(iMatPlayerBoard, iShipSize, iArrPlayerCarrierPosition);

		cleanScreen();

		printSetupBoard(iMatPlayerBoard);

		//Battleship
		iShipSize = 4;

		cout << "Admiral " << sPlayerName << "-San, enter the starting and ending coordinates of your " << sJapaneseBattleship;
		cout << " (" << iShipSize << " spaces)" << endl;

		readUserPositions(iMatPlayerBoard, iShipSize, iArrPlayerBattleshipPosition);	

		cleanScreen();

		printSetupBoard(iMatPlayerBoard);

		//Cruiser
		iShipSize = 3;

		cout << "Admiral " << sPlayerName << "-San, enter the starting and ending coordinates of your " << sJapaneseCruiser;
		cout << " (" << iShipSize << " spaces)" << endl;

		readUserPositions(iMatPlayerBoard, iShipSize, iArrPlayerCruiserPosition);

		cleanScreen();

		printSetupBoard(iMatPlayerBoard);

		//Submarine
		cout << "Admiral " << sPlayerName << "-San, enter the starting and ending coordinates of your " << sJapaneseSubmarine;
		cout << " (" << iShipSize << " spaces)" << endl;

		readUserPositions(iMatPlayerBoard, iShipSize, iArrPlayerSubmarinePosition);

		cleanScreen();

		printSetupBoard(iMatPlayerBoard);

		//Destroyer
		int iShipSize = 2;

		cout << "Admiral " << sPlayerName << "-San, enter the starting and ending coordinates of your " << sJapaneseDestroyer;
		cout << " (" << iShipSize << " spaces)" << endl;

		readUserPositions(iMatPlayerBoard, iShipSize, iArrPlayerDestroyerPosition);

		cleanScreen();

		printSetupBoard(iMatPlayerBoard);

	}
	else
	{
		printSetupBoard(iMatPlayerBoard);

		//Carrier
		iShipSize = 5;

		cout << "Admiral " << sPlayerName << ", enter the starting and ending coordinates of your " << sAmericanCarrier;
		cout << " (" << iShipSize << " spaces)" << endl;

		readUserPositions(iMatPlayerBoard, iShipSize, iArrPlayerCarrierPosition);

		cleanScreen();

		printSetupBoard(iMatPlayerBoard);

		//Battleship
		iShipSize = 4;

		cout << "Admiral " << sPlayerName << ", enter the starting and ending coordinates of your " << sAmericanBattleship;
		cout << " (" << iShipSize << " spaces)" << endl;

		readUserPositions(iMatPlayerBoard, iShipSize, iArrPlayerBattleshipPosition);

		cleanScreen();

		printSetupBoard(iMatPlayerBoard);

		//Cruiser
		iShipSize = 3;

		cout << "Admiral " << sPlayerName << ", enter the starting and ending coordinates of your " << sAmericanCruiser;
		cout << " (" << iShipSize << " spaces)" << endl;

		readUserPositions(iMatPlayerBoard, iShipSize, iArrPlayerCruiserPosition);

		cleanScreen();

		printSetupBoard(iMatPlayerBoard);

		//Submarine
		cout << "Admiral " << sPlayerName << ", enter the starting and ending coordinates of your " << sAmericanSubmarine;
		cout << " (" << iShipSize << " spaces)" << endl;

		readUserPositions(iMatPlayerBoard, iShipSize, iArrPlayerSubmarinePosition);

		cleanScreen();

		printSetupBoard(iMatPlayerBoard);

		//Destroyer
		int iShipSize = 2;

		cout << "Admiral " << sPlayerName << ", enter the starting and ending coordinates of your " << sAmericanDestroyer;
		cout << " (" << iShipSize << " spaces)" << endl;

		readUserPositions(iMatPlayerBoard, iShipSize, iArrPlayerDestroyerPosition);

		cleanScreen();

		printSetupBoard(iMatPlayerBoard);

	}
}

/*
writeComputerInput
Function to write the ship position on the board given random generated data
Parameters: The board, a boolean to validate the position, and the array with the position
Return: nothing
*/
void writeComputerInput(int iMatBoard[10][10], int iArrShipPosition[], int iShipSize, bool &bIsOverlapped)
{
	bIsOverlapped = false;

	//Horizontal positioning
	if (iArrShipPosition[0])
	{
		int iRowIndex = iArrShipPosition[1];

		for (int iColIndex = iArrShipPosition[2]; iColIndex <= iArrShipPosition[iShipSize+1]; ++iColIndex)
		{
			if (iMatBoard[iRowIndex][iColIndex])
			{
				bIsOverlapped = true;
				break;
			}
		}

		if (!bIsOverlapped)
		{
			for (int iColIndex = iArrShipPosition[2]; iColIndex <= iArrShipPosition[iShipSize+1]; ++iColIndex)
			{
				iMatBoard[iRowIndex][iColIndex] = 1;
			}
		}
	}

	//Vertical Positioning
	else
	{
		int iColIndex = iArrShipPosition[1];

		for (int iRowIndex = iArrShipPosition[2]; iRowIndex <= iArrShipPosition[iShipSize+1]; ++iRowIndex)
		{
			if (iMatBoard[iRowIndex][iColIndex])
			{
				bIsOverlapped = true;
				break;
			}
		}

		if (!bIsOverlapped)
		{
			for (int iRowIndex = iArrShipPosition[2]; iRowIndex <= iArrShipPosition[iShipSize+1]; ++iRowIndex)
			{
				iMatBoard[iRowIndex][iColIndex] = 1;
			}
		}
	}
}

/*
writeComputerInput
Function to generate a random ship position, validate it, and to write it in the board
Parameters: The board, the array with the position, and the ship size
Return: nothing
*/
void generateRandomPosition(int iMatBoard[10][10], int iArrShipPosition[], int iShipSize)
{
	srand(time(NULL));

	bool bIsOverlapped = true;

	while(bIsOverlapped)
	{
		iArrShipPosition[0] = rand() % 2;

		iArrShipPosition[1] = rand() % 10;

		iArrShipPosition[2] = rand() % (10-iShipSize);

		int iExternalCounter = 1;

		for (int iCounter = 3; iCounter < iShipSize + 2 ; ++iCounter)
		{
			iArrShipPosition[iCounter] = iArrShipPosition[2] + iExternalCounter++;
		}

		writeComputerInput(iMatBoard, iArrShipPosition, iShipSize, bIsOverlapped);
	}
	
}


/*
getComputerPositions
Function to generate a random board for the computer
Parameters: The board, and a set of arrays for the ship positions
Return: nothing
*/
void getComputerPositions(int iMatBoard[10][10], int iArrComputerCarrierPosition[], int iArrComputerBattleshipPosition[],
			           	  int iArrComputerCruiserPosition[], int iArrComputerSubmarinePosition[], int iArrComputerDestroyerPosition[])
{
	//Computer Carrier
	int iShipSize = 5;
	generateRandomPosition(iMatBoard, iArrComputerCarrierPosition, iShipSize);

	//Computer Battleship
	iShipSize = 4;

	generateRandomPosition(iMatBoard, iArrComputerBattleshipPosition, iShipSize);

	//Computer Cruiser
	iShipSize = 3;

	generateRandomPosition(iMatBoard, iArrComputerCruiserPosition, iShipSize);

	//Computer Submarine
	iShipSize = 3;

	generateRandomPosition(iMatBoard, iArrComputerSubmarinePosition, iShipSize);

	//Computer Destroyer
	iShipSize = 2;

	generateRandomPosition(iMatBoard, iArrComputerDestroyerPosition, iShipSize);
}

/*
setupGame
Function to set the boards and ships for a new game
Paramenters: Player and computer boards, the player name, the team, a set of arrays to store player ship locations
and a set of arrays to store computer ship locations
Return: nothing
*/
void setupGame(int iMatPlayerBoard[10][10], int iMatComputerBoard[10][10], string &sPlayerName, char &cTeam,
               int iArrPlayerCarrierPosition[7], int iArrPlayerBattleshipPosition[6], int iArrPlayerCruiserPosition[5],
			   int iArrPlayerSubmarinePosition[5], int iArrPlayerDestroyerPosition[4], int iArrComputerCarrierPosition[7],
			   int iArrComputerBattleshipPosition[6], int iArrComputerCruiserPosition[5], int iArrComputerSubmarinePosition[5],
			   int iArrComputerDestroyerPosition[4])	
{
	eraseBoard(iMatPlayerBoard);
	eraseBoard(iMatComputerBoard);

	cleanScreen();

	sPlayerName = getPlayerName();

	cleanScreen();

	cTeam = chooseTeam();

	cleanScreen();

	getPlayerPositions(iMatPlayerBoard, sPlayerName, cTeam, iArrPlayerCarrierPosition, iArrPlayerBattleshipPosition,
			           iArrPlayerCruiserPosition, iArrPlayerSubmarinePosition, iArrPlayerDestroyerPosition);

	getComputerPositions(iMatComputerBoard, iArrComputerCarrierPosition, iArrComputerBattleshipPosition, iArrComputerCruiserPosition,
						 iArrComputerSubmarinePosition, iArrComputerDestroyerPosition);
}

int main()
{

	int iMatPlayerBoard[10][10], iMatComputerBoard[10][10];

	int iArrPlayerCarrierPosition[7];
	int iArrPlayerBattleshipPosition[6];
	int iArrPlayerCruiserPosition[5];
	int iArrPlayerSubmarinePosition[5];
	int iArrPlayerDestroyerPosition[4];

	int iArrComputerCarrierPosition[7];
	int iArrComputerBattleshipPosition[6];
	int iArrComputerCruiserPosition[5];
	int iArrComputerSubmarinePosition[5];
	int iArrComputerDestroyerPosition[4];	 

	string sPlayerName;

	char cTeam;

	setupGame(iMatPlayerBoard, iMatComputerBoard, sPlayerName, cTeam, iArrPlayerCarrierPosition, iArrPlayerBattleshipPosition,
			  iArrPlayerCruiserPosition, iArrPlayerSubmarinePosition, iArrPlayerDestroyerPosition, iArrComputerCarrierPosition, 
			  iArrComputerBattleshipPosition, iArrComputerCruiserPosition, iArrComputerSubmarinePosition, iArrComputerDestroyerPosition);


	/*
	TESTING FOR POSITION ARRAYS
	*/
	cout << "Your " <<  sJapaneseCarrier << " is ";

	if (!iArrPlayerCarrierPosition[0])
	{
		cout << "vertically placed, and is at column " << iArrPlayerCarrierPosition[1];
		cout << " within these vertical coordinates " << endl;

		for (int i = 2; i < 7; ++i)
		{
			cout << iArrPlayerCarrierPosition[i] << " ";
		}

		cout << endl;
	}
	else
	{
		cout << "horizontally placed, and is at row " << iArrPlayerCarrierPosition[1];
		cout << " within these horizontal coordinates " << endl;

		for (int i = 2; i < 7; ++i)
		{
			cout << iArrPlayerCarrierPosition[i] << " ";
		}

		cout << endl;
	}

	cout << "Your " <<  sJapaneseBattleship << " is ";

	if (!iArrPlayerBattleshipPosition[0])
	{
		cout << "vertically placed, and is at column " << iArrPlayerBattleshipPosition[1];
		cout << " within these vertical coordinates " << endl;

		for (int i = 2; i < 6; ++i)
		{
			cout << iArrPlayerBattleshipPosition[i] << " ";
		}

		cout << endl;
	}
	else
	{
		cout << "horizontally placed, and is at row " << iArrPlayerBattleshipPosition[1];
		cout << " within these horizontal coordinates " << endl;

		for (int i = 2; i < 6; ++i)
		{
			cout << iArrPlayerBattleshipPosition[i] << " ";
		}

		cout << endl;
	}

	cout << "Your " <<  sJapaneseCruiser << " is ";

	if (!iArrPlayerCruiserPosition[0])
	{
		cout << "vertically placed, and is at column " << iArrPlayerCruiserPosition[1];
		cout << " within these vertical coordinates " << endl;

		for (int i = 2; i < 5; ++i)
		{
			cout << iArrPlayerCruiserPosition[i] << " ";
		}

		cout << endl;
	}
	else
	{
		cout << "horizontally placed, and is at row " << iArrPlayerCruiserPosition[1];
		cout << " within these horizontal coordinates " << endl;

		for (int i = 2; i < 5; ++i)
		{
			cout << iArrPlayerCruiserPosition[i] << " ";
		}

		cout << endl;
	}

	cout << "Your " <<  sJapaneseSubmarine << " is ";

	if (!iArrPlayerCruiserPosition[0])
	{
		cout << "vertically placed, and is at column " << iArrPlayerSubmarinePosition[1];
		cout << " within these vertical coordinates " << endl;

		for (int i = 2; i < 5; ++i)
		{
			cout << iArrPlayerSubmarinePosition[i] << " ";
		}

		cout << endl;
	}
	else
	{
		cout << "horizontally placed, and is at row " << iArrPlayerSubmarinePosition[1];
		cout << " within these horizontal coordinates " << endl;

		for (int i = 2; i < 5; ++i)
		{
			cout << iArrPlayerSubmarinePosition[i] << " ";
		}

		cout << endl;
	}

	cout << "Your " <<  sJapaneseDestroyer << " is ";

	if (!iArrPlayerDestroyerPosition[0])
	{
		cout << "vertically placed, and is at column " << iArrPlayerDestroyerPosition[1];
		cout << " within these vertical coordinates " << endl;

		for (int i = 2; i < 4; ++i)
		{
			cout << iArrPlayerDestroyerPosition[i] << " ";
		}

		cout << endl;
	}
	else
	{
		cout << "horizontally placed, and is at row " << iArrPlayerDestroyerPosition[1];
		cout << " within these horizontal coordinates " << endl;

		for (int i = 2; i < 4; ++i)
		{
			cout << iArrPlayerDestroyerPosition[i] << " ";
		}

		cout << endl;
	}

 
	return 0;
}
