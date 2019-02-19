// Created by Nicholas Webster

#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

struct PERSON {
  char Name[20];
  float Balance;
};

void display(PERSON P[], int N) {
  cout << "Name                  Balance" << endl;
  cout << "---------------------------------" << endl;
  for (int i = 0; i<N; i++) {
    cout << setw(20) << left;
    cout << P[i].Name << "  ";
    cout << setw(10) << left;
    cout << P[i].Balance << endl;
  }
  cout << endl;
}

int totalClients(string fileName) {

  ifstream myFile(fileName);

  int tmp = 0;
  string line;

  while(getline(myFile, line)) {
    tmp += 1;
  }

  myFile.close();
  return tmp;
}

void project(PERSON P[], string fileName) {

  string fname, lname, sname;
  float num;
  int i = 0;

  ifstream myFile(fileName);
  while(myFile >> fname >> lname >> num) {
    sname = fname + " " + lname;
    strcpy(P[i].Name, sname.c_str());
    P[i].Balance = num;
    i++;

  }
  cout << endl;
  myFile.close();
}

void findRichest(PERSON P[], int N) {
  float max = P[0].Balance;
  int arrayPosition = 0;

  for(int i=1; i<N; i++) {
    if(P[i].Balance > max) {
      max = P[i].Balance;
      arrayPosition = i;
    }
  }
  cout << "The customer with maximum balance is " << P[arrayPosition].Name << "." << endl;
  cout << P[arrayPosition].Name << "'s balance is " << P[arrayPosition].Balance << endl << endl;
}

void deposit(string cust, PERSON P[], int N) {

  float cashDeposit = 0;
  cout << "How much would you like to deposit? ";
  cin >> cashDeposit;
  cout << "You are depositing $" << cashDeposit << endl;

  float custBalance = 0;
  for(int i=0; i<N; i++) {
    if(P[i].Name == cust) {
      P[i].Balance += cashDeposit;
      custBalance = P[i].Balance;
      break;
    }
  }
  cout << "Now your new balance is $" << custBalance << endl << endl;
}

void newCopy(string fileName, PERSON P[], int N) {

  ofstream myFile(fileName);

  for (int i = 0; i<N; i++) {
    myFile << P[i].Name << " " << P[i].Balance << endl;
  }

  myFile.close();
}

int main() {

  int N = totalClients("data.txt");
  cout << endl << "Number of clients: " << N << endl;

  PERSON P[N];

  project(P, "data.txt");
  display(P, N);
  findRichest(P, N);

  string custName;
  cout << "Enter your full name to deposit money: ";
  getline(cin, custName);
  deposit(custName, P, N);

  newCopy("data.txt", P, N);
}
