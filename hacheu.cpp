#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {
    string filename = "scores.txt";
    string searchName = "tonmoke";
    bool isFound = false;

    ifstream infile(filename);
    string name_and_scores;

    // อ่านชื่อตามลำดับของไฟล์และตรวจสอบว่าชื่อตรงกับชื่อที่ต้องการหรือไม่
    while (getline(infile, name_and_scores)) {
        const char* text = name_and_scores.c_str();
        char format[]="%s %d";
        char name[20];
        int scores;
        sscanf(text,format,name,&scores);
        if (name == searchName) {
            isFound = true;
            break;
        }
    }

    if (isFound) {
        cout << "Found " << searchName << " in " << filename << endl;
    } else {
        cout << "Could not find " << searchName << " in " << filename << endl;
    }

    infile.close();

    return 0;
}
