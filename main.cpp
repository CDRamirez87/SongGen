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

void outputSection(int section)
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
			std::cout << "ERROR IN void outputProgression()";

			
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


/*-------------------------------------------MAIN------------------------------------------------*/


int main()
{	
	std::srand(static_cast<unsigned int>(std::time(nullptr))); // set initial seed value for random numbers to system clock
	
	int userKey = getUserKey(); //Prompts user for input and returns it as an integer
	
	Note songChords[7], keyTonic;
	
	keyTonic = setTonic(userKey);	//gets the tonic as a Note to extrapolate into a scale
	
	setMajorKey(keyTonic, songChords, MAJOR_KEY); //Extrapolates the tonic into a scale, assigns to songChords by reference
	
	bool isSharp = isKeySharp(userKey);
	
	//TODO - randomly select chord progressions and traspose them to key, output in sections
	
	
		
	/*******************************TEST*********************************
	
	Note dMajor[7];
	
	setMajorKey(NOTE_D, dMajor, MAJOR_KEY);
	
	for (int i = 0; i < 6; i++)
		std::cout << dMajor[i] << "\n";
	
	*/
	
	for (int i = 0; i < 100 ; i++)
		std::cout << rollDie(6) << "\n";
	
	return 0;

}
