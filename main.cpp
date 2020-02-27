#include <iostream> // for strings
#include <cstdlib> // for std::rand() and std::srand()
#include <ctime> // for std::time()

//CONSTANTS

const int MAJOR_KEY[] = {0, 2, 4, 5, 7, 9, 11},
		  MINOR_KEY[] = {0, 2, 3, 5, 7, 8, 10};

const int PROG_INDEX = 16; //number of chord progressions
const int PROG[PROG_INDEX][5] //List of chord progressions
{
	{1, 5, 6, 4, 0},
	{1, 5, 6, 3, 4},
	{6, 5, 4, 5, 0},
	{1, 6, 4, 5, 0},
	{1, 4, 6, 5, 0},
	{1, 5, 4, 5, 0},
	{4, 2, 1, 5, 1},
	{1, 5, 6, 5, 0},
	{1, 2, 1, 4, 0},
	{1, 3, 6, 4, 0},
	{4, 1, 5, 99, 0},
	{4, 1, 2, 5, 0},
	{4, 5, 13, 6, 0}, //Toggle Major/Minor?? (-10 at output)
	{1, 13, 6, 99, 0},
	{1, 21, 4, 5, 0}, //Dominant?? (-20 at output)
	{4, 14, 1, 99, 0} //99 = "Add your own!"
	
};

//SPECIAL DATA TYPES
enum Note
{
	NOTE_A,		//0
	NOTE_ASHARP,	//1
	NOTE_B,		//2
	NOTE_C,		//3
	NOTE_CSHARP,	//4
	NOTE_D,		//5
	NOTE_DSHARP,	//6
	NOTE_E,		//7
	NOTE_F,		//8
	NOTE_FSHARP,	//9
	NOTE_G,		//10
	NOTE_GSHARP	//11
};

enum Section
{
	SECTION_INTRO,
	SECTION_VERSE,
	SECTION_PRECHORUS,
	SECTION_CHORUS,
	SECTION_BRIDGE
};
/*-----------------------FUNCTIONS-------------------------*/

// Generate a random number between 1 and max (inclusive)
// Assumes std::srand() has already been called
// Assumes max - min <= RAND_MAX
int rollDie(int sides)
{
    static constexpr double fraction { 1.0 / (RAND_MAX + 1.0) };  // static used for efficiency, so we only calculate this value once
    // evenly distribute the random number across our range
    return 1 + static_cast<int>((sides - 2) * (std::rand() * fraction));
}

//Extrapolates the tonic into a scale
void setMajorKey(Note note, Note key[], const int interval[]) 
{
		for(int degree = 0; degree < 7; degree++)
		{
				key[degree] =  static_cast<Note>(note + interval[degree]);
				
				if (key[degree] > 11)
					key[degree] = static_cast<Note>(key[degree] - 12);
		}
}

//Lets the user choose a key for the song
int getUserKey() 
{
	int userChoice(0);
	
	std::cout << "1. C \n 2. C# \n 3. D \n 4. Eb \n 5. E \n 6. F \n 7. Gb \n 8. G \n 9. Ab \n 10. A \n 11. Bb \n 12. B \n";
					
	
	while (userChoice < 1 || userChoice > 12)	
	{
		userChoice = 0;
		std::cout << "Enter a number (1-12) and press Enter to Select a Key:";
		std::cin >> userChoice;
	}
	
	return userChoice;
}

//Determines whether the key should be displayed with sharps or flats
bool isKeySharp(int key)
{
	if (key == 1 || key == 2 || key == 3 || key == 5 || key == 8 || key == 10 || key == 12)
			return true;
	
	else
		return false;
}

void printSection(int section)
{
	std::string text = "";
	
	Section secCast = static_cast<Section>(section);
	
	switch(secCast)
	{
		case SECTION_INTRO:
			text = "Intro";
			break;
		case SECTION_VERSE:
			text = "Verse";
			break;
		case SECTION_CHORUS:
			text = "Chorus";
			break;
		case SECTION_PRECHORUS:
			text = "Prechorus";
			break;
		case SECTION_BRIDGE:
			text = "Bridge";
			break;
		default:
			std::cout << "ERROR IN void outputProgression()\n";

			
	}
	
	std::cout << text << ":\n";
}

int progToInt(int random, const int progression[][5], Note scale, int chordNum)
{
	int noteCast = static_cast<int>(scale);
	noteCast += progression[random][chordNum];
	if (noteCast > 6)
		noteCast -= 7;
	return noteCast;		
}

//Equates the user's input to a key
Note setTonic (int key)
{
	switch (key)
	{
		case 1:
			return NOTE_C;
		case 2:
			return NOTE_CSHARP;
		case 3:
			return NOTE_D;
		case 4:
			return NOTE_DSHARP;
		case 5:
			return NOTE_E;
		case 6:
			return NOTE_F;
		case 7:
			return NOTE_FSHARP;
		case 8:
			return NOTE_G;
		case 9:
			return NOTE_GSHARP;
		case 10:
			return NOTE_A;
		case 11: 
			return NOTE_ASHARP;
		case 12: 
			return NOTE_B;
		default:
			std::cout << "ERROR IN Note setKey";
			break;
	}
			
}

void printChord(int chordInt, bool isSharp, Note chords[7])
{
	bool isMinor;
	
	
	if (chordInt == 1 || chordInt == 2 || chordInt == 5) //2nd, 3rd, and 6th degree are minor
		isMinor = true;
	
	if (chordInt > 10 && chordInt < 18) //To toggle major/minor, 10 is added in the original array and processed here
	{
		chordInt -= 10;
		
			if (isMinor == true)
				isMinor = false;
			
			else 
				isMinor = true;
		
	}
	
	std::string chordName = "";
	
	if (isSharp)
	{
		switch (chords[chordInt])
		{
			case NOTE_A:
				chordName = "A";
				break;
			case NOTE_ASHARP:
				chordName = "A#";
				break;
			case NOTE_B:
				chordName = "B";
				break;
			case NOTE_C:
				chordName = "C";
				break;
			case NOTE_CSHARP:
				chordName = "C#";
				break;
			case NOTE_D:
				chordName = "D";
				break;
			case NOTE_DSHARP:
				chordName = "D#";
				break;
			case NOTE_E:
				chordName = "E";
				break;
			case NOTE_F:
				chordName = "F";
				break;
			case NOTE_FSHARP:
				chordName = "F#";
				break;
			case NOTE_G:
				chordName = "G";
				break;
			case NOTE_GSHARP:
				chordName = "G#";
				break;
			default:
				std::cout << "*"; //Indicates "choose your own" chord
		}
	}
	
	else if(!isSharp)
	{
		switch (chords[chordInt])
		{
			case NOTE_A:
				chordName = "A";
				break;
			case NOTE_ASHARP:
				chordName = "Bb";
				break;
			case NOTE_B:
				chordName = "B";
				break;
			case NOTE_C:
				chordName = "C";
				break;
			case NOTE_CSHARP:
				chordName = "Db";
				break;
			case NOTE_D:
				chordName = "D";
				break;
			case NOTE_DSHARP:
				chordName = "Eb";
				break;
			case NOTE_E:
				chordName = "E";
				break;
			case NOTE_F:
				chordName = "F";
				break;
			case NOTE_FSHARP:
				chordName = "Gb";
				break;
			case NOTE_G:
				chordName = "G";
				break;
			case NOTE_GSHARP:
				chordName = "Ab";
				break;
			default:
				std::cout << "(*)"; //indicates "choose your own" chord
		}
	}
	
	std::cout << chordName;
	
	if(isMinor)
		std::cout << "m";
}

/*-------------------------------------------MAIN------------------------------------------------*/


int main()
{	
	std::srand(static_cast<unsigned int>(std::time(nullptr))); // set initial seed value for random numbers to system clock
	
	int userKey = getUserKey(); //Prompts user for input and returns it as an integer
	
	Note songChords[7], keyTonic;
	
	keyTonic = setTonic(userKey);	//gets the tonic as a Note to extrapolate into a scale
	
	setMajorKey(keyTonic, songChords, MAJOR_KEY); //Extrapolates the tonic into a scale, assigns to songChords by reference
	
	bool isSharp = isKeySharp(userKey);
	
	//Main Algorithm
	for (int i = 0; i < 5; i++)
	{
		printSection(i); //Displays Verse, chorus, etc
		
		int progNumber = rollDie(PROG_INDEX); //Choose a random chord progression
		
		for (int n = 0; n < 5; n++) 
		{
			int progID = progToInt(progNumber, PROG, keyTonic, n);//Applies the progression to the key
			
			printChord(progID, isSharp, songChords); //Prints the chord
			
			if (n == 4)
				std::cout << "\n";
			else
				std::cout << " ";
		}
	}
	
	std::cout << "\"*\" means \"choose a chord that sounds good to you\"\nEnjoy your song!\n";

	
	return 0;

}
