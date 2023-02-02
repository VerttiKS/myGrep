#include <iostream>
#include <string>
#include <fstream>


//-------------------------------------
//Functions

void search(char*, char*, char*);

std::string turnLowercase(std::string);

void oldGrep();


//-------------------------------------
//Main
int main(int argc, char* argv[])
{

	switch (argc)
	{
		case 1:
		{
			//This happens if you only write ./mygrep
			oldGrep();

			break;
		}

		case 2:
		{
			//This happens if you only write "./mygrep *text*" (used for "./mygrep help")
			std::cout << "The correct syntax for finding a word is './mygrep *searchword* *fileName*'" << std::endl;
			std::cout << "The correct syntax for finding a word with an options is './mygrep -o[options] *searchword* *fileName*'" << std::endl << std::endl;

			std::cout << "-------------------------List of options-------------------------" << std::endl;
			std::cout << "'-ol' ----------> Display the number of the written line" << std::endl;
			std::cout << "'-oo' ----------> Display the amount of lines written" << std::endl;
			std::cout << "'-or' ----------> Display lines that don't have your searchword" << std::endl;
			std::cout << "'-oi' ----------> Upper- and lowercase letters have the same value" << std::endl << std::endl;

			std::cout << "You can also also put the options together for example '-olo' or 'olori'." << std::endl;
			std::cout << "The order of the options doesn't matter, so '-olori' and '-orilo' do the same thing." << std::endl;
			break;
		}

		case 3:
		{
			//This happens, if you write something like "./mygrep *text* *fileName*"
			char noArg = 'n';

			search(argv[1], argv[2], &noArg);
			break;
		}

		case 4:
		{
			//This happens, if you write something like "./mygrep *option* *text* *fileName*"

			search(argv[2], argv[3], argv[1]);

			break;
		}

		default:
		{
			std::cout << "An exception occurred!" << std::endl;
			std::cout << "You wrote too many arguments!" << std::endl << std::endl;
			std::cout << "Write './mygrep help' for help!" << std::endl;
			break;
		}
	}

	//a line ender to make commandline look more clean
	std::cout << std::endl;

	return 0;
}


/*
Function used for searching for things for a file
*/
void search(char* searchword, char* fileName, char* opt)
{
	//-------------------------------------
	//Variables used for reading a file

	std::string listener; //Variable that will get lines from the reader

	std::fstream reader; //Variable that will give lines to the reader

	bool wordFound = false; //Bool used for checking if the word was found


	//-------------------------------------
	//Variable chars turned into strings

	std::string word(searchword); //char "searchWord" changed to string "word"

	std::string file(fileName); //char "fileName" changed to string "file"

	std::string option(opt); //char "opt" changed to string "option"


	//-------------------------------------
	//Variables used for options
	int optionLength = option.length(); //lenght of option

	bool optionLORI[4] = { false, false, false ,false }; //Bool used for determining the options selected [0] = l, [1] = o, [2] = r, [3] = i

	char optionLetters[4] = { 'l', 'o', 'r', 'i' };


	//Starts reading the file
	reader.open(file);

	//Checks if reader can read the file
	if (reader.is_open() == false) 
	{
		//print out and error message
		std::cout << "An exception occurred!" << std::endl;
		std::cout << "Could not open the file '" << file << "'!" << std::endl << std::endl;
		std::cout << "Write './mygrep help' for help!" << std::endl;

		//Exit the program if the file is not found
		return;
	}

	//this happens, if there was no options
	if (option == "n")
	{
		//While loop where the "reader" passes file lines to the "listener"
		while (std::getline(reader, listener))
		{
			//This string checks if the word if found
			size_t stringFound = listener.find(word);

			//Prints the line, if the word is found
			if (stringFound != std::string::npos)
			{
				std::cout << listener << std::endl;
				wordFound = true;
			}
		}

		//If word was not found
		if (wordFound == false)
		{
			//Print out that it wasn't found
			std::cout << "'" << word << "' NOT found in '" << file << "'" << std::endl;
		}

		//let's return back to the program
		return;
	}


	//Switch case used for determining the options selected
	switch(optionLength)
	{
		//If only one option was selected
		case 3:
		{
			//Checks what option was selected
			for (int i = 0; i < 4; i++)
			{
				//check the first option
				if (option[2] == optionLetters[i])
				{
					optionLORI[i] = true;
				}
			}

			//Leave the switch case
			break;
		}

		//If only two options were selected
		case 4:
		{
			//For loop that checks the first and second option
			for (int k = 0; k < 2; k++)
			{
				//Checks what option was selected
				for (int i = 0; i < 4; i++)
				{
					//check the first option
					if (option[(k+2)] == optionLetters[i])
					{
						optionLORI[i] = true;
					}
				}
			}

			//Leave the switch case
			break;
		}

		//If only three options were selected
		case 5:
		{
			//For loop that checks the first, second and third option
			for (int k = 0; k < 3; k++)
			{
				//Checks what option was selected
				for (int i = 0; i < 4; i++)
				{
					//check the first option
					if (option[(k + 2)] == optionLetters[i])
					{
						optionLORI[i] = true;
					}
				}
			}

			//Leave the switch case
			break;
		}

		//If only four options were selected
		case 6:
		{
			//For loop that checks the first, second, third and fourth option
			for (int k = 0; k < 4; k++)
			{
				//Checks what option was selected
				for (int i = 0; i < 4; i++)
				{
					//check the first option
					if (option[(k + 2)] == optionLetters[i])
					{
						optionLORI[i] = true;
					}
				}
			}

			//Leave the switch case
			break;
		}

		default:
		{
			//Print out and error message
			std::cout << "An exception occurred!" << std::endl;
			std::cout << "You wrote too many or too little options!" << std::endl << std::endl;

			std::cout << "Write './mygrep help' for help!" << std::endl;

			//return to main
			return;
		}
	}

	//---------------------------------------------------
	//Variables used for gathering data from the read

	int linesFound = 0; //Int that records the number of lines that have the word

	int lineNum = 0; //Int used for recording the number of pages that the document had


	//If reverse search is false
	if (optionLORI[2] == false)
	{
		//While loop where the "reader" passes file lines to the "listener"
		while (std::getline(reader, listener))
		{
			size_t stringFound; //string used for checking if a word is found


			//Let's see if case insensitive comparison is enabled
			if (optionLORI[3] == true)
			{
				//Check if the word is found (case insentivite)
				stringFound = turnLowercase(listener).find(turnLowercase(word));
			}
			else
			{
				//Check if the word is found (case sentivite)
				stringFound = listener.find(word);
			}


			//Every new loop of the while is a new line
			if (optionLORI[0] == true)
			{
				lineNum++;
			}


			//Prints the line, if the word is found
			if (stringFound != std::string::npos)
			{
				//word was found
				wordFound = true;

				//Checks if the line numbers will be printed
				if (optionLORI[0] == true)
				{
					//Prints with the line number
					std::cout << lineNum << ":     " << listener << std::endl;
				}
				else
				{
					//Prints without the line number
					std::cout << listener << std::endl;
				}

				//If a line is found and option is selected, this goes up
				if (optionLORI[1] == true)
				{
					linesFound++;
				}
			}
		}


		//If word was not found
		if (wordFound == false)
		{
			//Print out that it wasn't found
			std::cout << "'" << word << "' NOT found in '" << file << "'" << std::endl;
		}
		else if(optionLORI[1] == true) //If line printing was selected and word was found
		{
			//prints the number of found lines
			std::cout << std::endl << std::endl << "Occurrences of lines containing '" << word << "': " << linesFound << std::endl;
		}

		//return back to main
		return;

	}
	else //If reverse search is true
	{
		//While loop where the "reader" passes file lines to the "listener"
		while (std::getline(reader, listener))
		{
			size_t stringFound; //string used for checking if a word is found


			//Let's see if case insensitive comparison is enabled
			if (optionLORI[3] == true)
			{
				//Check if the word is found (case insentivite)
				stringFound = turnLowercase(listener).find(turnLowercase(word));
			}
			else
			{
				//Check if the word is found (case sentivite)
				stringFound = listener.find(word);
			}


			//Every new loop of the while is a new line
			if (optionLORI[0] == true)
			{
				lineNum++;
			}


			//Prints the line, if the word is not found
			if (stringFound == std::string::npos)
			{
				//word was found
				wordFound = true;

				//Checks if the line numbers will be printed
				if (optionLORI[0] == true)
				{
					//Prints with the line number
					std::cout << lineNum << ":     " << listener << std::endl;
				}
				else
				{
					//Prints without the line number
					std::cout << listener << std::endl;
				}

				//If a line is found and option is selected, this goes up
				if (optionLORI[1] == true)
				{
					linesFound++;
				}
			}
		}


		//If line was not found
		if (wordFound == false)
		{
			//Print out that it wasn't found
			std::cout << "A line without the word '" << word << "' NOT found in '" << file << "'" << std::endl;
		}
		else if (optionLORI[1] == true) //If line printing was selected and word was found
		{
			//prints the number of found lines
			std::cout << std::endl << std::endl << "Occurrences of lines not containing '" << word << "': " << linesFound << std::endl;
		}

		//return back to main
		return;
	}

	

	//If this goes off, none of the if statements were triggered
	std::cout << "An exception occurred!" << std::endl;
	std::cout << "The search function was not triggered for some reason." << std::endl << std::endl;
	std::cout << "Write './mygrep help' for help!" << std::endl;

	//return back to main
	return;
}



//Function used for turning strings to lowercase when compared. Doesn't use reference, because we don't want to affect the actual string 
std::string turnLowercase(std::string line)
{
	for (int i = 0; i < line.length(); i++)
	{
		line[i] = tolower(line[i]);
	}

	return line;
}



//Function that happens if you only do only the ./mygrep command
void oldGrep()
{
	//Variables
	std::string word,
		sentence;


	//Print and get lines
	std::cout << "Give a string from which to search for: ";
	std::getline(std::cin, sentence);

	std::cout << "Give search string: ";
	std::getline(std::cin, word);


	//Compare the lines and print based on the if else
	size_t stringFound = sentence.find(word);

	if (stringFound != std::string::npos)
	{
		std::cout << "'" << word << "' found in '" << sentence << "' in position " << stringFound << std::endl;
	}
	else
	{
		std::cout << "'" << word << "' NOT found in '" << sentence << "'" << std::endl;
	}


	//Return back to main
	return;
}