/*****************************************************************************************************************
 Program: MathTutor V4
 Programmer: Asher
 Date:11/11/2024
Description: This is an interactive math tutor designed for young learners.
In this third version, the program first prompts the user to enter their full name.
It then randomly generates a math problem using one of the four basic operations: addition,
subtraction, multiplication, or division. If an errors occurs, an error message will be displayed,
informing the user that something went wrong.

After generating the question, the program presents it to user, allowing them to attempt an answer.
It provides immediate feedback, letting them know if their answer is correct or incorrect. If the user answers
incorrectly, the same questions is repeated until they get it right. Answering correctly will cause them
to "level up," while an incorrect answer results in "leveling down." Each level increases the difficulty
by adding 10 to the numbers in the problems.

At the end, a summary report will display the total number of questions asked, the number of correct answers,
the number of incorrect answers, and the user's overall accuracy percentage.
*******************************************************************************************************************/





#include <iostream> // this is needed for the cin/cout and left/right alignment
#include <string> // this is needed for the string
#include <cstdlib>
#include <ctime>
#include <vector>
#include <limits>
#include <iomanip>
using namespace std;
// This section enables user input in the running code.

int main() {
 const int NUM_ATTEMPTS = 3;
 const int LEVEL_RANGE_CHANGE = 10;
 int totalCorrect = 0;
 int totalIncorrect = 0;
 int mathLevel = 1;
 int totalAccuracy = 0;
 string userName = "?"; // This is so that the user can enter there name
 string userInput = "?";
 int userAnswer = 0;
 int leftNum = 0;
 int rightNum = 0;
 enum MathType{MT_ADD, MT_SUB, MT_MUL, MT_DIV}; //Declares mathtype with values of 4 math types (+, -, *, /)
  MathType mathType = MT_ADD;
 int tempNum = 0;
 int levelChange = 10;
 int correctAnswer = 0;
 char mathSymbol = '+';
 vector<vector<int>> questions;
 srand(time(nullptr));
 // This is a start to the things that make it look nicer to look at
 cout << "**************************************************************";
 cout << endl;
 // this right here is the Ascii art
 cout << " __ __ _ _ _____ _ " << endl;
 cout << " | \\/ | __ _ | |_ | |__ |_ _|_ _ | |_ ___ _ __ "
 << endl;
 cout << R"( | |\/| | / _` || __|| '_ \ | | | | | || __|/ _ \ | '__| )"
 << endl;
 cout << " | | | || (_| || |_ | | | | | | | |_| || |_| (_) || | " << endl;
 cout << R"( |_| |_| \__,_| \__||_| |_| |_| \__,_| \__|\___/ |_| )"
 << endl;
 cout << endl;
 // here is the welcome and the look good things "*"
 cout << "**************************************************************"
 << endl;
 cout << "* Welcome to the easy Math Tutor *"
 << endl;
 cout << "**************************************************************"
 << endl;
 cout << endl;
 // the begging of the facts
 cout << "Fun facts about math:" << endl;
 cout << endl;
 // here are the facts that the user can enjoy
 cout << " * The Egyptians were the first to use multiplication tables."
 << endl;
 cout << " * Every odd number has the letter e in it." << endl;
 cout << " * On dice, opposite sides always add up to the number seven."
 << endl;
 cout << endl;
 // more of the make look good things
 cout << "***************************************************************"
 << endl;
 cout << endl;
 // This is where the user can enter there name and then the code welcomes them
 // with their name
 cout << "What is your name? ";
 getline(cin, userName);
 cout << endl;
 cout << "Welcome " << userName << " to the easy math tutor!" << endl;
 cout << endl;
 do {
  leftNum = rand() % (levelChange * mathLevel) + 1;
  rightNum = rand() % (levelChange * mathLevel) + 1;
  mathType = static_cast<MathType>(rand() % 3 + 1);
  //This line randomly generates the equation for the user to attempt
  switch (mathType) {
   case 0: // addition
    mathSymbol = '+';
   correctAnswer = leftNum + rightNum;
   break;
   case 1: // subtraction
    mathSymbol = '-';
   if (leftNum < rightNum) { //ensure no negatives are given
    tempNum = leftNum;
    leftNum = rightNum;
    rightNum = tempNum;
   }
   correctAnswer = leftNum - rightNum;
   break;
   case 2: // multiplication
    mathSymbol = '*';
   correctAnswer = leftNum * rightNum;
   break;
   case 3: // division
    mathSymbol = '/';
   correctAnswer = leftNum; // ensure solution is never a fraction
   leftNum *= rightNum;
   break;
   default: //ensuring system doesn't break when there is an invalid math type
    cout << "Invalid Math Type is " << mathType << endl;
   cout << "Ending Program." << endl;
   return -1;
  }
  vector<int> row = {mathLevel, leftNum, mathSymbol, rightNum, correctAnswer};
  for (int i = 1; i <= NUM_ATTEMPTS; i++) {
   cout << "[Level #" << mathLevel << "] " << "What is " << leftNum << " " << mathSymbol
  << " " << rightNum << " = ";
   while (!(cin >> userAnswer)) {
    cin.clear(); // clear the cin error flag
    //need to include the limits library to use numeric_limits
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); //ignore the max input, up to

     cout << "Invalid input!" << endl;
    cout << "\tPlease enter a number: ";
   }
   if (userAnswer == correctAnswer) {
    cout << "Good job! You got it correct!" << endl;
    if (totalAccuracy < 0) {
     totalAccuracy = 0;
    }
    row.push_back(i);
    totalAccuracy++;
    break;
   }
   else {
    if (i != 3) {
     cout << "Sorry, that was the wrong answer." << endl;
     cout << "You have " << NUM_ATTEMPTS - i << " attempts left." << endl;
    }
    else {
     cout << "Sadly, that was also incorrect and you have no more attempts." << endl;
     if (totalAccuracy > 0) {
      totalAccuracy = 0;
     }
     row.push_back(0);
     totalAccuracy--;
     break;
    }
   }
  }
  questions.push_back(row);
  if (totalAccuracy == 3) {
   mathLevel++;
   totalAccuracy = 0;
   cout << "Level up! You are now on level " << mathLevel << endl;
  }
  else if (totalAccuracy == -3) {
   if (mathLevel > 1) {
    mathLevel--;
    totalAccuracy = 0;
    cout << "Level down! You are now on level " << mathLevel << endl;
   }
   else {
    cout << "You are at the lowest level. You cannot go any lower!" << endl;
    totalAccuracy = 0;
   }
  }
  cout << "Would you like to continue? (y/n): ";
  cin >> userInput;
 } while (tolower(userInput == "y") or tolower(userInput == "yes"));
 cout << "******************************************" << endl;
 cout << "                Summary Report " << endl;
 cout << "******************************************" << endl;
 cout << "Level         Question          Attempts " << endl;
 cout << "------- -------------------- ------------" << endl;
 for(int i = 0; i < questions.size(); i++) {
  mathLevel = questions.at(i).at(0);
  leftNum = questions.at(i).at(1);
  mathSymbol = static_cast<char>(questions.at(i).at(2));
  rightNum = questions.at(i).at(3);
  correctAnswer = questions.at(i).at(4);
  totalAccuracy = questions.at(i).at(5);
  cout << " " << setw(2) << right << mathLevel << " "
  << setw(9) << right << leftNum << " "
  << mathSymbol << " "
  << setw(3) << left << rightNum
  << " = "
  << setw(3) << right << correctAnswer;
  if (totalAccuracy != 0) {
   cout << setw(10) << right << totalAccuracy << endl;
   totalCorrect++;
  }
  else {
   cout << setw(10) << left << "      Incorrect" << endl;
   totalIncorrect++;
  }
 }
 cout << endl;
 int totalQuestions = totalCorrect + totalIncorrect;
 if (totalQuestions > 0)
 {
  cout << "Total Questions: " << setw(5) << right << totalCorrect + totalIncorrect << endl;
  cout << "Total Correct : " << setw(5) << right << totalCorrect << endl;
  cout << "Total Incorrect: " << setw(5) << right << totalIncorrect << endl;
  double averagePercentage = (static_cast<double>(totalCorrect) / totalQuestions) *
 100;
  cout << "Average Correct: " << setw(5) << right << fixed << setprecision(0.0) <<
 averagePercentage << "%" << endl;
 }
 else {
  cout << " There are no questions answered." << endl;
 }
 cout << endl;
 cout << "Keep calm and do math!" << endl;
 return 0;
}
