#include <iostream> // for strings
#include <vector> // for dynamic array behavior
#include <cstdlib> // for std::rand() and std::srand()
#include <ctime> // for std::time()


const int NOTE_NUM = 12, DEGREES = 7;

// Generate a random number between 1 and max (inclusive)
// Assumes std::srand() has already been called
// Assumes max - min <= RAND_MAX
int rollDie(int sides)
{
    static constexpr double fraction { 1.0 / (RAND_MAX + 1.0) };  // static used for efficiency, so we only calculate this value once
    // evenly distribute the random number across our range
    return 1 + static_cast<int>((sides - 2) * (std::rand() * fraction));
}

int main()
{
	
	std::srand(static_cast<unsigned int>(std::time(nullptr))); // set initial seed value for random numbers to system clock
	
	int key[DEGREES] = {0,0,0,0,0,0,0};
	std::string notesSharp[NOTE_NUM] = {"A", "A#", "B", "C", "C#", "D", "D#", "E", "F", "F#", "G", "G#"},
		   notesFlat[NOTE_NUM] = {"A", "Bb", "B", "C", "Db", "D", "Eb", "E", "F", "Gb", "G", "Ab"};
	
	
	
	return 0;

}
