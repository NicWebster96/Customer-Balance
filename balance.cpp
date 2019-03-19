// Nicholas Webster
// Section 1

#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

struct PERSON {
  char Name[20];
  float Balance;
};

PERSON * readData(int & N) {
  PERSON *P;
  P = new PERSON[N];

  string fname, lname, sname;
  float num;
  int i = 0;
  ifstream dataIn("data.txt");

  while(dataIn >> fname >> lname >> num) {
    string firstN = fname.substr(0,9);
    string lastN = lname.substr(0,10);
    sname = firstN + " " + lastN + "\0";
    strcpy(P[i].Name, sname.c_str());
    P[i].Balance = num;
    i++;
  }

  dataIn.close();
  return P;
}

void display(PERSON P[], int N) {
  cout << "Name                  Balance" << endl;
  cout << "---------------------------------" << endl;
  for (int i = 0; i<N; i++) {
    cout << setw(20) << left;
    cout << P[i].Name << "  ";
    cout << "$" << setw(10) << left;
    cout << setprecision(2) << fixed << P[i].Balance << endl;
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

void findRichest(PERSON P[], int N) {
  float max = P[0].Balance;
  int arrayPosition = 0;

  for(int i=1; i<N; i++) {
    if(P[i].Balance > max) {
      max = P[i].Balance;
      arrayPosition = i;
    }
  }
  cout << "Highest balance: " << P[arrayPosition].Name << endl;
}

void deposit(PERSON P[], int N, string cust, float amount) {

  float custBalance = 0;

  for(int i=0; i<N; i++) {
    if(P[i].Name == cust) {
      P[i].Balance += amount;
      custBalance = P[i].Balance;
      break;
    }
  }
  cout << "New Balance: " << custBalance << endl << endl;
}

void newCopy(string fileName, PERSON P[], int N) {

  ofstream myFile(fileName);

  for (int i = 0; i<N; i++) {
    myFile << P[i].Name << " " << P[i].Balance << endl;
  }

  cout << "File Updated..." << endl;
  myFile.close();
}

void printmenu() {
    cout << "Please enter a choice:" << endl;
    cout << "1. Display records"<< endl;
    cout << "2. Deposit funds"<< endl;
    cout << "3. Find Highest Balance" << endl;
    cout << "4. Update records" << endl;
    cout << "5. Exit the program" << endl;
}

void depositInfo(string& custName, float& amount) {
  cout << "Enter name: ";
  getline(cin, custName);
  cout << "Amount: ";
  cin >> amount;
}

int main() {

    int N = totalClients("data.txt");

    PERSON * P = readData(N);

    string custName;
    float amount;

    int choice;
    do
    {
          printmenu();
          cin >> choice;
          cin.ignore();
          switch(choice)
          {
              case 1:
                  display(P, N);
                  break;

              case 2:
                  depositInfo(custName, amount);
                  deposit(P, N, custName, amount);
                  break;

              case 3:
                  findRichest(P, N);
                  break;

              case 4:
                  newCopy("data.txt", P, N);
                  break;

              case 5:
                  newCopy("data.txt", P, N);
                  break;

              default:
                  cout << "Invalid entry" << endl;
                  break;
          }
          cout << endl;
     } while(choice != 5);
        return 0;
}
