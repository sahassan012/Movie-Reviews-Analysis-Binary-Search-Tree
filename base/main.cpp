//
//  Movie Reviews using Binary Search Trees:
//  	Inputs movies and reviews, allowing the user to search
//  	by movie ID, movie Name, or review ID.  Uses binary search trees for 
//  	an efficient search.
//

#include <iostream>
#include <fstream>
#include <string>

#include "bst.h"
using namespace std;

//
// Struct that holds movie ratings and publication year
// 
struct MovieData
{
	int PubYear;
	int Num5Stars = 0;
	int Num4Stars = 0;
	int Num3Stars = 0;
	int Num2Stars = 0;
	int Num1Stars = 0;
};


//
//
// trim:
//
// trims whitespace from beginning and end of string.
//
// Ref: https://stackoverflow.com/questions/25829143/trim-whitespace-from-a-string
// Modified: to handle empty strings, and strings of all blanks.
//
string trim(const string& str)
{
  size_t first = str.find_first_not_of(" \t\n\r");
  size_t last = str.find_last_not_of(" \t\n\r");

  if (first == string::npos && last == string::npos)  // empty, or all blanks:
    return "";
  else if (first == string::npos)  // no blanks at the start:
    first = 0;                     // 0-based
  else if (last == string::npos)   // no blanks trailing at end:
    last = str.length() - 1;       // 0-based

  return str.substr(first, (last - first + 1));
}


// 
// 
// isInt:
//  Checks for whether the input is an Integer value or not
// 
bool isInt(string s)
{
	for (unsigned int i = 0; i < s.length(); i++){
		if (!isdigit(s[i])){
			return false;
		}
	}
	return true;
}


//
//
// getAverage:
//  Takes a pointer to a Movie object
//  and returns weighted average of all ratings for the movie
//
double getAverage(MovieData* m){
	//Adding all ratings
	int sum = m->Num1Stars + m->Num2Stars +  m->Num3Stars + m->Num4Stars + m->Num5Stars;
	
	//Return if sum is 0, to avoid dividing by 0
	if (sum == 0){
		return 0.0;
	}
	//Store type double variables, and multiply with their stars
	double num1Sum = m->Num1Stars*1.0;
	double num2Sum = m->Num2Stars*2.0;
	double num3Sum = m->Num3Stars*3.0;
	double num4Sum = m->Num4Stars*4.0;
	double num5Sum = m->Num5Stars*5.0;
	
	//Calculate weighted average by dividing the total sum with the sum of the stars and return
	double average = (num1Sum + num2Sum + num3Sum + num4Sum + num5Sum)/(m->Num1Stars + m->Num2Stars + m->Num3Stars + m->Num4Stars + m->Num5Stars);
	return average;
}


// 
// 
// InputData:
//
// Inputs the data from the "reviews" file, which contains N>0 lines, where
// each line contains:
//   reviewID movieID rating
//
int InputData(string reviewsFilename, binarysearchtree <int, MovieData>& byID, binarysearchtree <string, MovieData>& byName, binarysearchtree<int, string> byNameID)
{
  //Initialize variables and load filename into ifstream
  int reviewsCount = 0;
  ifstream reviewsFile(reviewsFilename);
  int      reviewID, movieID, rating;

  //Check if it is a valid filename	
  if (!reviewsFile.good())
  {
    cout << "**Error: unable to open reviews file '" << reviewsFilename << "', exiting" << endl;
    return 0;
  }

  reviewsFile >> reviewID;  // get first ID, or set EOF flag if file empty:
  
  while (!reviewsFile.eof())
  {
    // we have more data, so input publication year and movie name:
    reviewsFile >> movieID;
	reviewsFile >> rating;

    // debugging:
    //cout << reviewID << ", " << movieID << ", " << rating << endl;
	
	//Initialize a local pointer to nullptr, stores MovieData pointer returned by BST when search performed using ID
	MovieData* value = nullptr;
	value = byID.search(movieID);
	  
	//Initialize a local pointer to nullptr, stores string pointer returned by BST when search performed using ID
	string* name = nullptr;
	name = byNameID.search(movieID);  

	//Initialize a local pointer to nullptr, stores MovieData pointer returned by BST when search performed using Name 
	MovieData* value2 = nullptr;
	value2 = byName.search(*name);
	  
	//If value isn't nullptr, continue
	if (value != nullptr) {
		//Store in both BST byID and BST byName the ratings for each movie respectively
		if (rating == 5)
		{
			value->Num5Stars += 1; 
			value2->Num5Stars += 1;
			
		}
		else if (rating == 4)
		{
			value->Num4Stars += 1; 
			value2->Num4Stars += 1; 
		}
		else if (rating == 3)
		{
			value->Num3Stars += 1; 
			value2->Num3Stars += 1; 
		}
		else if (rating == 2)
		{
			value->Num2Stars += 1; 
			value2->Num2Stars += 1; 
		}
		else if (rating == 1)
		{
			value->Num1Stars += 1; 
			value2->Num1Stars += 1; 
		}
	}
    reviewsFile >> reviewID;  // get next ID, or set EOF flag if no more data:
	reviewsCount++; //Increment reviews count
  }
return reviewsCount;
}


//
//
// InputMovies:
//
// Inputs the data from the "movies" file, which contains N>0 lines, where
// each line contains:
//     id pubYear name
//
void InputMovies(string moviesFilename, string reviewsFilename)
{
  //Declaring the binarysearchtree Objects to be used	
  binarysearchtree <int, MovieData> treeByID;      //<ID, MovieData>
  binarysearchtree <string, MovieData> treeByName; //<Name, MovieData>
  binarysearchtree <int, string> treeNameID;       //<Name, ID>
  binarysearchtree <string, int> treeIDName;       //<ID, Name>
	
  //Declaring variables and loading filename into ifstream
  ifstream moviesFile(moviesFilename);
  int      id, pubYear, movieCount;
  movieCount = 0;
  string   name;
	
  //Checking for valid filename
  if (!moviesFile.good())
  {
    cout << "**Error: unable to open movies file '" << moviesFilename << "', exiting" << endl;
    return;
  }
  
  moviesFile >> id;  // get first ID, or set EOF flag if file empty:
  while (!moviesFile.eof())
  {
    // we have more data, so input publication year and movie name:
    moviesFile >> pubYear;
    getline(moviesFile, name);  // movie name fills rest of input line:
	
    // trim potential whitespace from both ends of movie name:
    name = trim(name);  

    // debugging:
    //cout << id << "," << pubYear << "," << name << endl;
	
	//Instance of movie data that stores pubYear
	MovieData m1;
	m1.PubYear = pubYear;
	
	//Inserting into all trees
	treeByName.insert(name, m1);
	treeByID.insert(id, m1);
	treeNameID.insert(id, name);
	treeIDName.insert(name, id);
	  
    moviesFile >> id;  // get next ID, or set EOF flag if no more data:
	movieCount++;   //Increase movie count
  }
	//Calling inputData() function and passing all trees and reviewfile name
	int reviewsCount = InputData(reviewsFilename, treeByID, treeByName, treeNameID);
	
	//Printing data
	cout << "Num movies: " << movieCount << endl;
	cout << "Num reviews: " << reviewsCount << endl;	
	cout << endl;
	cout << "Tree by movie id: size=" << treeByID.size() << ", height=" << treeByID.height() << endl;
	cout << "Tree by movie name: size=" << treeByName.size() << ", height=" << treeByName.height() << endl;
	cout << endl;
	
	//Initializing input string for while loop to run until sentinel is entered
	string input = "";
	while(input != "#")
	{
	  cout << "Enter a movie id or name (or # to quit)> "; // Prompt
	  getline(cin, input);
		
	  //If the input is not blank and #, continue	
	  if (input != "" && input != "#" ){
		  MovieData* value = nullptr;  
		  //Check if input is an integer
		  if (isInt(input)){
			//Store the integer value and search BST using ID
			int id = stoi(input);
			value = treeByID.search(id);  
			 
			//Check if returned value is a nullptr, if it isn't, continue  
			if (value != nullptr)
			{
				//Print movie and rating information
				cout << "Movie ID: " << id << endl;
				cout << "Movie Name: " << *treeNameID.search(id) << endl; 
				cout << "Avg rating: " << getAverage(treeByID.search(id)) << endl;
				cout << "5 stars: " << value->Num5Stars << endl;
				cout << "4 stars: " << value->Num4Stars << endl;
				cout << "3 stars: " << value->Num3Stars << endl; 
				cout << "2 stars: " << value->Num2Stars << endl;
				cout << "1 star: " << value->Num1Stars << endl;
				cout << endl;
			}
			else
			{  
				//If value is nullptr, there was no match
				cout << "not found...\n" << endl;
			}
		  }
		  else{
			value = nullptr;
			value = treeByName.search(input);	
			if (value != nullptr)
			{
				//Print movie and rating information
				cout << "Movie ID: " << *treeIDName.search(input) << endl;
				cout << "Movie Name: " << input << endl; 
				cout << "Avg rating: " << getAverage(treeByName.search(input)) << endl;
				cout << "5 stars: " << value->Num5Stars << endl;
				cout << "4 stars: " << value->Num4Stars << endl;
				cout << "3 stars: " << value->Num3Stars << endl; 
				cout << "2 stars: " << value->Num2Stars << endl;
				cout << "1 star: " << value->Num1Stars << endl;
				cout << endl;
			}
			else
			{
				//If value is nullptr, there was no match
				cout << "not found...\n" << endl;
			}
		  }
		}
	}
}


//
//
// main
//
int main()
{
  
  string moviesFilename; // = "movies1.txt";
  string reviewsFilename; // = "reviews1.txt";
  cout << "movies file?> ";
  cin >> moviesFilename;

  cout << "reviews file?> ";
  cin >> reviewsFilename;

  string junk;
  getline(cin, junk);  // discard EOL following last input:
  
  InputMovies(moviesFilename, reviewsFilename);

  //junk = "";
  //getline(cin, junk);  // discard EOL following last input:


  return 0;
}
