#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main()
{
    string name;
    int score;

    cout << "Enter name: ";
    getline(cin, name);
    cout << "Enter score: ";
    cin >> score;

    ofstream file("scores.txt");

    if (!file.is_open()) {
        cout << "Error opening file!" << endl;
        return 1;
    }

    file << name << " " << score << endl;

    file.close();

    cout << "Score saved to file!" << endl;

    return 0;
}
