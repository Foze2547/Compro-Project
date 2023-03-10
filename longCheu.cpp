#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main()
{
    string name;
    int score;

    // Get the name and score from the user
    cout << "Enter name: ";
    getline(cin, name);
    cout << "Enter score: ";
    cin >> score;

    // Open the file for writing
    ofstream file("scores.txt");

    // Check if the file was opened successfully
    if (!file.is_open()) {
        cout << "Error opening file!" << endl;
        return 1;
    }

    // Write the name and score to the file
    file << name << " " << score << endl;

    // Close the file
    file.close();

    cout << "Score saved to file!" << endl;

    return 0;
}
