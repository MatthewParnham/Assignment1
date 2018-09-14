//main.cpp
#include <iostream>
#include <string>
#include <cmath>
#include <fstream>
#include <cstdlib>
#include <time.h>

using namespace std;

const double PI = 3.14159265358979323846; //Pi constant

void toUpperCase(string& str) {
  //Takes a string passed by reference and updates each character to be Uppercase
  for (int i = 0; i < str.size(); i++) {
    str[i] = toupper(str[i]);
  }
}


int main(int argc, char *argv[]) {

  ofstream outputFile; //creating output file stream
  outputFile.open("MatthewParnham.out", std::ofstream::out | std::ofstream::app); //open file in output mode and append mode
  bool repeat = true; //boolean for while loop
  string filePath;
  if (argc != 2) { //Checks for valid command line arguments and saves argument to filePath variable
    cerr << "Incorrect number of arguments. Execution terminated." << endl;
    return 0;
  }
  else {
    filePath = argv[1];
  }

  while(repeat) {
    //Trys to open file w/ given file filePath
    ifstream inputFile;
    inputFile.open(filePath);
    if(!inputFile) { //if the file path does not lead to a file, will return false
      cerr << "Failed to open file. Execution terminated." << endl;
      return 0;
    }
    else {
      cout << "Successfully opened file \"" << filePath << "\"." << endl;
    }

    //variables to perform operations on
    int countA = 0; //counting individual nucleotides
    int countC = 0;
    int countT = 0;
    int countG = 0;
    int totalChars; //total characters throughout file
    double freqA; //frequency of nucleotides throughout entire file as a decimal
    double freqC;
    double freqT;
    double freqG;

    int AA = 0, AC = 0, AT = 0, AG = 0, //countingDNA bigrams
        CA = 0, CC = 0, CT = 0, CG = 0,
        TA = 0, TC = 0, TT = 0, TG = 0,
        GA = 0, GC = 0, GT = 0, GG = 0;
    double freqAA, freqAC, freqAT, freqAG, //frequency of bigrams
           freqCA, freqCC, freqCT, freqCG,
           freqTA, freqTC, freqTT, freqTG,
           freqGA, freqGC, freqGT, freqGG;
    int totalBigrams = 0; //total number of bigrams counted in file

    int sumLineLength = 0; //sum of line lengths, for calculating mean
    int totalLineCount = 0; //total number of lines, used for calculating mean

    double meanLineLength;
    double variance;
    double stdDev;

    string line;
    //start of file reading
    while(getline(inputFile, line)) { //line read in as conditional of loop because it returns true if successful

      toUpperCase(line); //changes line to uppercase
      sumLineLength += line.size() - 1; // -1 because line.size() returns one too many lines by default
      totalLineCount++;

      for (int i = 0; i < line.size()-1; i++) { //iterate through each character and count each character

        if(line[i] == 'A') {
          countA++;
        }
        else if(line[i] == 'C') {
          countC++;
        }
        else if(line[i] == 'T') {
          countT++;
        }
        else if(line[i] == 'G') {
          countG++;
        }
        else {
          cout << "Invalid character. Execution terminated." << endl;
          return 0;
        }
      }
    }

    inputFile.close();



    meanLineLength = double(sumLineLength) / totalLineCount; //calculate mean

    //Math for calculating relative frequency of each nucleotide (ACTG)
    totalChars = countA + countC + countT + countG;
    freqA = double(countA) / totalChars;
    freqC = double(countC) / totalChars;
    freqT = double(countT) / totalChars;
    freqG = double(countG) / totalChars;

  //Open file for second pass
    inputFile.open(filePath);
    if(!inputFile) {
      cerr << "Failed to open file. Execution terminated." << endl;
      return 0;
    }

  //reading file second time
  double varianceNumeratorSum = 0;
  while(getline(inputFile,line)) {
    toUpperCase(line); //changes line to uppercase
    varianceNumeratorSum += pow((line.size() - 1) - meanLineLength,2);
    //numerator for variance is (x-x_bar)^2

    //bigram counting
    for(int i = 0; i < line.size() -2; i++) { //line.size() - 2 because the last character in a string isn't a bigram
      string bigram = line.substr(i,2);

      if(bigram == "AA") {
        AA++;
      }
      else if(bigram == "AC") {
        AC++;
      }
      else if(bigram == "AT") {
        AT++;
      }
      else if(bigram == "AG") {
        AG++;
      }
      else if(bigram == "CA") {
        CA++;
      }
      else if(bigram == "CC") {
        CC++;
      }
      else if(bigram == "CT") {
        CT++;
      }
      else if(bigram == "CG") {
        CG++;
      }
      else if(bigram == "TA") {
        TA++;
      }
      else if(bigram == "TC") {
        TC++;
      }
      else if(bigram == "TT") {
        TT++;
      }
      else if(bigram == "TG") {
        TG++;
      }
      else if(bigram == "GA") {
        GA++;
      }
      else if(bigram == "GC") {
        GC++;
      }
      else if(bigram == "GT") {
        GT++;
      }
      else if(bigram == "GG") {
        GG++;
      }
      else {
        cout << "Invalid character. Execution terminated." << endl;
        return 0;
      }
    }
  }
  inputFile.close();

  //calculate bigram relative frequency
  totalBigrams = AA + AC + AT + AG +
                 CA + CC + CT + CG +
                 TA + TC + TT + TG +
                 GA + GC + GT + GG;
  freqAA = double(AA) / totalBigrams;
  freqAC = double(AC) / totalBigrams;
  freqAT = double(AT) / totalBigrams;
  freqAG = double(AG) / totalBigrams;
  freqCA = double(CA) / totalBigrams;
  freqCC = double(CC) / totalBigrams;
  freqCT = double(CT) / totalBigrams;
  freqCG = double(CG) / totalBigrams;
  freqTA = double(TA) / totalBigrams;
  freqTC = double(TC) / totalBigrams;
  freqTT = double(TT) / totalBigrams;
  freqTG = double(TG) / totalBigrams;
  freqGA = double(GA) / totalBigrams;
  freqGC = double(GC) / totalBigrams;
  freqGT = double(GT) / totalBigrams;
  freqGG = double(GG) / totalBigrams;

  //calculate variance and standard deviation
  variance = varianceNumeratorSum / totalLineCount;
  stdDev = sqrt(variance);




  //test print statements
    cout << "A's: " << countA << " / " << totalChars << " = " << freqA << endl;
    cout << "C's: " << countC << " / " << totalChars << " = " << freqC << endl;
    cout << "T's: " << countT << " / " << totalChars << " = " << freqT << endl;
    cout << "G's: " << countG << " / " << totalChars << " = " << freqG << endl;
    cout << "Sum of line lengths: " << sumLineLength << endl;
    cout << "Mean line length: " << meanLineLength << endl;
    cout << "Variance of line length: " << variance << endl;
    cout << "Standard Deviation of line length: " << stdDev << endl;
    cout << "AA: " << AA << " / " << totalBigrams << " = " << freqAA << endl;
    cout << "AC: " << AC << " / " << totalBigrams << " = " << freqAC << endl;
    cout << "AT: " << AT << " / " << totalBigrams << " = " << freqAT << endl;
    cout << "AG: " << AG << " / " << totalBigrams << " = " << freqAG << endl;
    cout << "CA: " << CA << " / " << totalBigrams << " = " << freqCA << endl;
    cout << "CC: " << CC << " / " << totalBigrams << " = " << freqCC << endl;
    cout << "CT: " << CT << " / " << totalBigrams << " = " << freqCT << endl;
    cout << "CG: " << CG << " / " << totalBigrams << " = " << freqCG << endl;
    cout << "TA: " << TA << " / " << totalBigrams << " = " << freqTA << endl;
    cout << "TC: " << TC << " / " << totalBigrams << " = " << freqTC << endl;
    cout << "TT: " << TT << " / " << totalBigrams << " = " << freqTT << endl;
    cout << "TG: " << TG << " / " << totalBigrams << " = " << freqTG << endl;
    cout << "GA: " << GA << " / " << totalBigrams << " = " << freqGA << endl;
    cout << "GC: " << GC << " / " << totalBigrams << " = " << freqGC << endl;
    cout << "GT: " << GT << " / " << totalBigrams << " = " << freqGT << endl;
    cout << "GG: " << GG << " / " << totalBigrams << " = " << freqGG << endl;

    //ofstream outputting same information to outputFile

    outputFile << "Matthew Parnham\n";
    outputFile << "2287511\n";
    outputFile << "parnham@chapman.edu\n\n";

    outputFile << "Sum of line lengths: " << sumLineLength << endl;
    outputFile << "Mean line length: " << meanLineLength << endl;
    outputFile << "Variance of line length: " << variance << endl;
    outputFile << "Standard Deviation of line length: " << stdDev << endl;
    outputFile << "\nIndividual Nucleotide Relative Frequencies:\n";
    outputFile << "A's: " << countA << " / " << totalChars << " = " << freqA << endl;
    outputFile << "C's: " << countC << " / " << totalChars << " = " << freqC << endl;
    outputFile << "T's: " << countT << " / " << totalChars << " = " << freqT << endl;
    outputFile << "G's: " << countG << " / " << totalChars << " = " << freqG << endl;
    outputFile << "\nBigram Relative Frequencies:\n";
    outputFile << "AA: " << AA << " / " << totalBigrams << " = " << freqAA << endl;
    outputFile << "AC: " << AC << " / " << totalBigrams << " = " << freqAC << endl;
    outputFile << "AT: " << AT << " / " << totalBigrams << " = " << freqAT << endl;
    outputFile << "AG: " << AG << " / " << totalBigrams << " = " << freqAG << endl;
    outputFile << "CA: " << CA << " / " << totalBigrams << " = " << freqCA << endl;
    outputFile << "CC: " << CC << " / " << totalBigrams << " = " << freqCC << endl;
    outputFile << "CT: " << CT << " / " << totalBigrams << " = " << freqCT << endl;
    outputFile << "CG: " << CG << " / " << totalBigrams << " = " << freqCG << endl;
    outputFile << "TA: " << TA << " / " << totalBigrams << " = " << freqTA << endl;
    outputFile << "TC: " << TC << " / " << totalBigrams << " = " << freqTC << endl;
    outputFile << "TT: " << TT << " / " << totalBigrams << " = " << freqTT << endl;
    outputFile << "TG: " << TG << " / " << totalBigrams << " = " << freqTG << endl;
    outputFile << "GA: " << GA << " / " << totalBigrams << " = " << freqGA << endl;
    outputFile << "GC: " << GC << " / " << totalBigrams << " = " << freqGC << endl;
    outputFile << "GT: " << GT << " / " << totalBigrams << " = " << freqGT << endl;
    outputFile << "GG: " << GG << " / " << totalBigrams << " = " << freqGG << endl;
    outputFile << "\n\n\n";
    cout << "File output successful." << endl;

    //create seed for rand()
    srand(time(NULL));

    for (int j = 0; j < 1000; j++) {
      //generate random numbers a and b between 0 and 1
      double a = (double(rand()) / (RAND_MAX));
      double b = (double(rand()) / (RAND_MAX));
      double c = sqrt((-2) * (log(a))) * cos(2 * PI * b); //use a and b to compute random normal number with stanDev of 1 and mean of 0
      double d = (stdDev * c) + meanLineLength; //adds correct mean and stanDev

      string newLine = ""; //blank line to add characters to
      //previous letter variable
      char prevLetter;


      //first letter
      double e = double(rand() % 100) / 100;
      //This letter is selected based off of the probability calculated for individual nucleotides
      if(e < freqA) {
        newLine += 'A';
        prevLetter = 'A';
      }
      else if(e < freqA + freqC) {
        newLine += 'C';
        prevLetter = 'C';
      }
      else if(e < freqA + freqC + freqT) {
        newLine += 'T';
        prevLetter = 'T';
      }
      else {
        newLine += 'G';
        prevLetter = 'G';
      }


      //subsequent letters
      for(int i = 0; i < d - 1; i++) {
        double f = double(rand() % 100) / 100;
        //All letters after the first per line are selected based off of the previous letter

        if(prevLetter == 'A') {

          int sumABigrams = AA + AC + AT + AG;
          double frAA = double(AA) / sumABigrams; //finds the frequency of the second letter in each bigram
          double frAC = double(AC) / sumABigrams;
          double frAT = double(AT) / sumABigrams;
          double frAG = double(AG) / sumABigrams;

          if(f < frAA) {
            newLine += 'A';
            prevLetter = 'A';
          }
          else if(f < frAA + frAC) {
            newLine += 'C';
            prevLetter = 'C';
          }
          else if(f < frAA + frAC + frAT) {
            newLine += 'T';
            prevLetter = 'T';
          }
          else {
            newLine += 'G';
            prevLetter = 'G';
          }

        }
        else if(prevLetter == 'C') {

          int sumCBigrams = CA + CC + CT + CG;
          double frCA = double(CA) / sumCBigrams;
          double frCC = double(CC) / sumCBigrams;
          double frCT = double(CT) / sumCBigrams;
          double frCG = double(CG) / sumCBigrams;

          if(f < frCA) {
            newLine += 'A';
            prevLetter = 'A';
          }
          else if(f < frCA + frCC) {
            newLine += 'C';
            prevLetter = 'C';
          }
          else if(f < frCA + frCC + frCT) {
            newLine += 'T';
            prevLetter = 'T';
          }
          else {
            newLine += 'G';
            prevLetter = 'G';
          }

        }
        else if(prevLetter == 'T') {

          int sumTBigrams = TA + TC + TT + TG;
          double frTA = double(TA) / sumTBigrams;
          double frTC = double(TC) / sumTBigrams;
          double frTT = double(TT) / sumTBigrams;
          double frTG = double(TG) / sumTBigrams;

          if(f < frTA) {
            newLine += 'A';
            prevLetter = 'A';
          }
          else if(f < frTA + frTC) {
            newLine += 'C';
            prevLetter = 'C';
          }
          else if(f < frTA + frTC + frTT) {
            newLine += 'T';
            prevLetter = 'T';
          }
          else {
            newLine += 'G';
            prevLetter = 'G';
          }

        }
        else if(prevLetter == 'G') {

          int sumGBigrams = GA + GC + GT + GG;
          double frGA = double(GA) / sumGBigrams;
          double frGC = double(GC) / sumGBigrams;
          double frGT = double(GT) / sumGBigrams;
          double frGG = double(GG) / sumGBigrams;

          if(f < frGA) {
            newLine += 'A';
            prevLetter = 'A';
          }
          else if(f < frGA + frGC) {
            newLine += 'C';
            prevLetter = 'C';
          }
          else if(f < frGA + frGC + frGT) {
            newLine += 'T';
            prevLetter = 'T';
          }
          else {
            newLine += 'G';
            prevLetter = 'G';
          }

        }

      }
      outputFile << newLine << endl;
    }
    outputFile << "\n\n\n"; //extra lines added in case user wants to analyze a second file

    //Prompt repeat
    cout << "Would you like to process another file? (y/n)" << endl;
    char repeatInput;
    cin >> repeatInput;
    if (repeatInput == 'y' || repeatInput == 'Y') {
      cout << "Please input new file name:" << endl;
      cin >> filePath;
    }
    else {
      repeat = false; //setting repeat to false exits the loop
      outputFile.close(); //output file is closed
    }
  }

  return 0;
}
