#include <iostream> // for strings
#include <vector> // for dynamic array behavior
#include <cstdlib> // for std::rand() and std::srand()
#include <ctime> // for std::time()

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

int prog[][5] //List of chord progressions
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

// Generate a random number between 1 and max (inclusive)
// Assumes std::srand() has already been called
// Assumes max - min <= RAND_MAX
int rollDie(int sides)
{
    static constexpr double fraction { 1.0 / (RAND_MAX + 1.0) };  // static used for efficiency, so we only calculate this value once
    // evenly distribute the random number across our range
    return 1 + static_cast<int>((sides - 2) * (std::rand() * fraction));
}

void setMajorKey(Note note, Note key[], const int interval[]) //For sharp keys
{
		for(int degree = 0; degree < 7; degree++)
		{
				key[degree] =  static_cast<Note>(note + interval[degree]);
				
				if (key[degree] > 11)
					key[degree] = static_cast<Note>(key[degree] - 12);
		}
}


int main()
{	
	const int MAJOR_KEY[] = {0, 2, 4, 5, 7, 9, 11},
			  MINOR_KEY[] = {0, 2, 3, 5, 7, 8, 10};
	
	std::srand(static_cast<unsigned int>(std::time(nullptr))); // set initial seed value for random numbers to system clock
	
	
		
		
		
	//*******************************TEST*********************************//
	
	Note dMajor[7];
	
	setMajorKey(NOTE_D, dMajor, MAJOR_KEY);
	
	for (int i = 0; i < 6; i++)
		std::cout << dMajor[i] << "\n";
	
	
	
	return 0;

}
