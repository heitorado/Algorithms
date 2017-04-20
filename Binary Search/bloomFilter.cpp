#include <iostream>
#include <vector>

using namespace std;

//Function
int applyBloomHash(string word, int base, int vecSize); //apply bloom filter and return hash position

int main(int argc, char const *argv[])
{
  //First, we read how many words are in our initial database.
  int wordsInDatabase;
  cin >> wordsInDatabase;

  //now we create a vector to store it and resize it accordingly.
  vector<string> databaseVector;
  databaseVector.resize(wordsInDatabase);

  //then we fill up our database vector.
  for(int i = 0; i < wordsInDatabase; ++i)
      cin >> databaseVector[i];

  //now we read the size of our hash vector and the number of hash functions to be applied.
  int bitVectorSize, hashFunctions;
  cin >> bitVectorSize >> hashFunctions;

  //Now we create a binary vector to store the results of our bloom filter and resize it.
  //and set all the bits to zero, since we need it clean to apply the filter.
  vector<bool> bitVector(0);
  bitVector.resize(bitVectorSize);

  //Now we create a vector to hold the bases for the hash functions.
  vector<int> baseVector;
  baseVector.resize(hashFunctions);

  //now we read all the bases for our hash Functions
  for(int i = 0; i < hashFunctions; ++i)
      cin >> baseVector[i];

  //Great. Now we have all the info we need to 'Register' all the words in our binary array with the hash function (bloom filter)
  for(int i = 0; i < wordsInDatabase; ++i)   //for each word in DB
      for(int j = 0; j < hashFunctions; ++j) //we apply all hash functions
        bitVector[applyBloomHash(databaseVector[i],baseVector[j],bitVectorSize)] = 1;//put 1 in the position returned by the hash function.

  //Now we read all the words we want to check for existance in database.
  int wordsToSearch;
  cin >> wordsToSearch;

  //Done with the preparing.
  //Now let's search for words in the database and check whether it's a false positive or not.

  //The first step is to read each word and see if they match with our binary vector.
  //If there's at least one zero in the vector, the word is "TOTALLY NOT THERE".
  //If there's no zeroes, the word "MIGHT BE THERE"
  string word;
  bool maybeIsThere=true;

  for(int i = 0; i < wordsToSearch; ++i)
  {
    cin >> word;

    for(int j = 0; j < hashFunctions; ++j)
    {
      if(bitVector[applyBloomHash(word,baseVector[j],bitVectorSize)] == 0)
          maybeIsThere = false; //false if we found a zero.
    }

    if(maybeIsThere) //let's do a binary search to make sure
    {
      //this will be used to confirm our false positive or not
      bool isThere=false;
      //and those will be used in our binary search
      int right = wordsInDatabase-1;
      int left = 0;
      int middle = (right+left)/2;

      //BINARY SEARCH STARTING HOLD ON TO YOUR SEATS THIS IS O(n.lgn)
      while(right>=left)
      {
        //if(checkStrMatch(word, databaseVector[middle]) == 0)
        if(word.compare(databaseVector[middle]) == 0)
        {
          cout << "2\n";
          isThere = true; //now we are sure! (2)
          break;
        }

        //if(checkStrMatch(word, databaseVector[middle]) == -1) //if the word found is "greater alphabetically"
        if(word.compare(databaseVector[middle]) < 0)
        {
          right = middle-1; //so our word must be in the left half
          middle = (right+left)/2;
        }

        //if(checkStrMatch(word, databaseVector[middle]) == 1) //if the word found is "lesser alphabetically"
        if(word.compare(databaseVector[middle]) > 0)
        {
          left = middle+1; //so our word must be in the right half
          middle = (right+left)/2;
        }
      }

      //if we didn't found with a binary search, we just got a false positive (1)
      if(isThere == false)
          cout << "1\n";
    }

    //if we found a zero, we are sure that the word isn't there.(0)
    else
    {
        cout << "0\n";
    }

    maybeIsThere=true;

  }

  return 0;
}

int applyBloomHash(string word, int base, int vecSize)
{
  int hash = word[0]%vecSize;
  int res = 1;

  for(int i = 1; word[i]!='\0'; ++i)
  {
    res = ((res%vecSize) * (base%vecSize)) % vecSize;
    hash = hash + ((word[i]%vecSize) * (res%vecSize)) % vecSize;
  }

  return hash % vecSize;
}
