#include <iostream>
#include <sstream>
#include <algorithm>
#include <ctime>
using namespace std;

class Pet 
{
private:
	static const int MAX_NAME_LENGTH = 10;
	static const int MIN_NAME_LENGTH = 5;
	static const int MAX_NUM_LIBS = 6;
	static const int MIN_NUM_LIBS = 2;

	static const int DEFAULT_ID = -1;
	static const int DEFAULT_NUM_LIBS = 4;
	static const string DEFAULT_NAME;

	long id;
	string name;
	int numLimbs;
	static int population;

public:
	static const long MIN_PET_ID = 0;
	static const long MAX_STORE_SIZE = 1000 * 1000;
   static const long MAX_PET_ID = MAX_STORE_SIZE * 10;

	static const Pet DEFAULT_PET;

	Pet();
	Pet(long id, string name, int numLimbs);
	~Pet();

	static int genRandomId();
	static int genRandomLibs();
	static string genRandomName();
	static int getPopulation() { return population; };
	static bool compare(const Pet* firstPet, const Pet* secondPet);

	long getId() const { return id; };
	string getName() const { return name; };
	int getNumLimbs() const { return numLimbs; };

	bool setId(long id);
	bool setName(string name);
	bool setNumLibs(int numLibs);
	
	string toString();
};

const string Pet::DEFAULT_NAME = "noname";
const Pet Pet::DEFAULT_PET = Pet();
int Pet::population = 0;

void sortStore(Pet** store) 
{
	sort(store, store + Pet::MAX_STORE_SIZE, Pet::compare);
}

const Pet& binarySearch(Pet** store, long top, long bot, long id) 
{
	int mid, result;

	if (top > bot)
	{
		return Pet::DEFAULT_PET;
	}

	mid = (top + bot) / 2;
	result = store[mid]->getId() - id;

	if (result == 0)
		return *(store[mid]);
	else if (result > 0)
		return binarySearch(store, top, mid - 1, id);
	else
		return binarySearch(store, mid + 1, bot, id);
}

const Pet& search(Pet** store, long id) 
{
	return binarySearch(store, 0, Pet::MAX_STORE_SIZE - 1, id);
}

int main() 
{
   //cout << sizeof(int) << endl; return 0;////

	srand( (unsigned int) time(NULL));



	Pet **store;
	store = new Pet*[Pet::MAX_STORE_SIZE];

	cout << "Initializing pet store...\n";
	for (int i = 0; i < Pet::MAX_STORE_SIZE; i++)
	{
		store[i] = new Pet();
		store[i]->setId( Pet::genRandomId() );
		store[i]->setName( Pet::genRandomName() );
		store[i]->setNumLibs( Pet::genRandomLibs() );
	}

	cout << "Sorting pet store...\n";
	sortStore(store);

	string userInput;
	int id;

	while(true)
	{
		cout << "Please enter the id to search or q(quit): ";
		getline(cin, userInput);
		if (userInput == "q")
			break;
		istringstream(userInput) >> id;
		Pet resultPet = search(store, id);
		cout << resultPet.toString() << endl;
	}

	cout << "Deleting pet store...\n";
	for (int i = 0; i < Pet::MAX_STORE_SIZE; i++)
	{
		delete store[i];
	}

	delete[] store;
	cout << "Bye~ \n";

	return 0;
}

Pet::Pet()
{
	population++;
	id = DEFAULT_ID;
	name = DEFAULT_NAME;
	numLimbs = DEFAULT_NUM_LIBS;
}

Pet::Pet(long id, string name, int numLimbs) 
{
	if (!setId(id))
	{
		this->id = DEFAULT_ID;
	}

	if (!setName(name))
	{
		this->name = DEFAULT_NAME;
	}
	
	if (!setNumLibs(numLimbs))
	{
		this->numLimbs = DEFAULT_NUM_LIBS;
	}

}

Pet::~Pet() 
{
	population--;
}

bool Pet::setId(long id)
{
	if (id < 0 || id > MAX_PET_ID)
	{
		return false;
	}

	this->id = id;
	return true;

}

bool Pet::setName(string name) 
{
	if (name.length() < MIN_NAME_LENGTH || name.length() > MAX_NAME_LENGTH)
	{
		return false;
	}

	this->name = name;
	return true;
}

bool Pet::setNumLibs(int numLibs)
{
	if (numLibs < MIN_NUM_LIBS || numLibs > MAX_NUM_LIBS)
	{
		return false;
	}

	this->numLimbs = numLibs;
	return true;
}

string Pet::genRandomName() {
	const int MAX_NAME_LENGTH = 10;
	const int MIN_NAME_LENGTH = 5;
	string vowels("aeiouy");
	string cons("bcdfghjklmnpqrstvwxz");
	enum CharType { vowel, con };
	static CharType prevCharType = con;

	int nameLen = rand() % (MAX_NAME_LENGTH - MIN_NAME_LENGTH) + MIN_NAME_LENGTH;

	string name = "";
	for (int i = 0; i<nameLen; i++) 
	{
		if (prevCharType == vowel) 
		{
			prevCharType = con;
			name += vowels[rand() % vowels.length()];
		}
		else 
		{
			prevCharType = vowel;
			name += cons[rand() % cons.length()];
		}
	}

	return name;
}

int Pet::genRandomLibs()
{
	int limbs = rand() % (MAX_NUM_LIBS - MIN_NUM_LIBS) + MIN_NUM_LIBS;
	return limbs;
}

int Pet::genRandomId()
{
	int randId = rand() % (MAX_PET_ID - MIN_PET_ID) + MIN_PET_ID;
	return randId;
}

string Pet::toString()
{
	stringstream ss;
	ss << "Id is: " << id << ", "
		<< "Name is: " << name << ", "
		<< "Limbs is: " << numLimbs;

	return ss.str();
}

bool Pet::compare(const Pet* firstPet, const Pet* secondPet)
{
	return firstPet->id < secondPet->id;
}

