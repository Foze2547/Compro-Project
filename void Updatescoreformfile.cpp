#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <sstream>
using namespace std;

void updateScoreFromFile(const string& filename){
     //หาตำแหน่งไฟล์เพื่อเก็บรายชื่อและคะแนน
    map<string, int> score;

     //เปิดไฟล์เพื่ออ่านข้อมูลชื่อ
    ifstream inFile(filename);
    if (!inFile){
        cerr << "Unable to open file " << filename << endl;
        return;
    }

    //อ่านไฟล์ในแต่ละบรรทัด
    string line;
    while (getline(inFile, line)){
        //แยกชื่อและคะแนนในแต่ละบรรทัด
        string name;
        int scoreValue;
        if (istringstream(line) >> name >> scoreValue) {
            //เช็คว่าชื่อนั้นมีอยู่ในไฟล์นั้นหรือไม่
            auto it = score.find(name);
            if (it != score.end()){
                //ถ้ามีชื่อนั้นอยู่แล้ว ให้เช็คคะแนนล่าสุดว่ามีค่ามากกว่าคะแนนเดิมหรือไม่
                if (scoreValue > it->second){
                    //อัพเดทค่าคะแนนใหม่
                    it->second = scoreValue;
                    cout << "Updated score for " << name << " to " << scoreValue << endl;
                }
            } else {
                //ในกรณีที่ชื่อนั้นยังไม่ได้อยู่ในไฟล์ ให้เพิ่มชื่อและเพิ่มคะแนนเข้าไปในไฟล์
                score[name] = scoreValue;
                cout <<"Added " << name << " with score " << scoreValue << endl;
            }
        } else {
            cerr << "Error reading line: " << line << endl;
            continue;
        }
    }

    //ปิดไฟล์ 
    inFile.close();
}
