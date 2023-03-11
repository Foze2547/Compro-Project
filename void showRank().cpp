void showRank(){
//เปิดไฟล์
  ifstream source;
  source.open("abc.txt");
  
//อ่านไฟล์(ใช้ลูปgetline)
/*โดยใช้ฟังก์ชัน getline() เพื่ออ่านข้อมูลจากไฟล์และส่งเข้าไปใน string textline 
จากนั้นใช้ฟังก์ชัน substr() เพื่อแยกชื่อและคะแนนของผู้เล่น จากนั้นเก็บเข้าไว้ใน vector ชื่อ students*/
  string textline;
    vector<pair<string,int>> students;
    while(getline(source, textline)) {
        string name = textline.substr(0, textline.find("|"));
        int score = stoi(textline.substr(textline.find("|")+1));
        students.push_back({name, score});
    }

//เรียงลำดับมากไปน้อย ถ้าเท่ากันให้เรียงตามตัวอักษร
//ใช้ sort()
  sort(students.begin(), students.end(), [](pair<string,int> a, pair<string,int> b) {
        if(a.second != b.second) {
            return a.second > b.second;
        }
        return a.first < b.first;
    });

//cout<<แสดงชื่อและคะแนน5อันดับแรก
  cout << "Top 5 scores:" << endl;
    int count = 0;
    for(auto s : students) {
        cout << count+1 << "." << s.first << "|" << s.second << endl;
        count++;
        if(count == 5) {
            break;
        }
    }

//ปิดไฟล์
  source.close();

}
