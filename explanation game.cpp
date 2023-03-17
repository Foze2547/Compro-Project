//ไลบรารีสำหรับการรับและแสดงผลข้อมูล (input/output)
#include<iostream>
//ไลบรารีสำหรับการรับค่าจากคีย์บอร์ด-ใช้ในการเรียกใช้ฟังก์ชัน getch() ที่ใช้รับค่า Input จาก keyboard
#include<conio.h>
//ไลบรารีสำหรับการใช้ฟังก์ชัน sleep() เพื่อจำลองความเร็วของเกม
#include<dos.h>
//ไลบรารีสำหรับการใช้ฟังก์ชัน rand() เพื่อสุ่มตำแหน่งของท่อ
#include<stdlib.h>
//ไลบรารีสำหรับการใช้ฟังก์ชัน strlen() เพื่อหาความยาวของข้อความ
#include<string.h>
//ไลบรารีสำหรับการจัดการกับข้อมูลประเภท string (ข้อความ)
#include<string>
//ไลบรารีสำหรับการเปิดและปิดไฟล์เพื่ออ่านและเขียนข้อมูล
#include<fstream>
/*ไลบรารีสำหรับการใช้ฟังก์ชัน SetConsoleCursorPosition() ใช้ในการตั้งค่าตำแหน่ง Cursor บนหน้าจอ command prompt 
โดยโค้ดด้านบนเป็นการกำหนดค่าคงที่สำหรับตำแหน่งและขนาดของหน้าจอ เช่น SCREEN_WIDTH กำหนดขนาดความกว้างของหน้าจอเป็น 90 ตัวอักษร 
ส่วน bird และตัวแปรที่เกี่ยวข้องกับ game เช่น pipePos ใช้เก็บตำแหน่งของท่อ, gapPos เก็บตำแหน่งของช่องว่าง
, pipeFlag ใช้เก็บสถานะว่าท่อมีการแสดงอยู่หรือไม่, birdPos ใช้เก็บตำแหน่งของนก, score ใช้เก็บคะแนนที่ผู้เล่นได้ทำได้ในแต่ละรอบเกม เป็นต้น*/
#include<windows.h>
//ไลบรารีสำหรับการใช้ฟังก์ชัน time() เพื่อสุ่มตำแหน่งของท่อ
#include<time.h>
//ไลบรารีสำหรับการจัดเก็บข้อมูลเป็นลิสต์คู่ค่า โดยเก็บข้อมูลในรูปแบบ key-value โดยจะเรียงลำดับ key ให้เรียงตามลำดับตัวอักษร และไม่อนุญาตให้ key ซ้ำกัน
#include<map>
//ไลบรารีสำหรับการจัดเก็บข้อมูลในรูปแบบลิสต์โดยไม่จำเป็นต้องกำหนดขนาดล่วงหน้า โดยใช้ pointer ในการจัดเก็บข้อมูล
#include<vector>
//ไลบรารีสำหรับการทำงานกับอลกอริทึมที่ใช้ในการจัดเรียงข้อมูลแบบเร็ว ๆ และการทำงานอื่น ๆ ที่เกี่ยวข้องกับการจัดเรียงข้อมูล
#include<algorithm>

/*คำสั่ง#defineใช้สร้างค่าคงที่(constant) ซึ่งหมายความว่าค่านั้นจะไม่สามารถเปลี่ยนแปลงได้ในโปรแกรม*/
//ความกว้างของหน้าจอที่เราใช้เล่นเกม
#define SCREEN_WIDTH 90
//ความสูงของหน้าจอที่เราใช้เล่นเกม
#define SCREEN_HEIGHT 26
//ความกว้างของส่วนเกมในหน้าจอ
#define WIN_WIDTH 70
//ความกว้างของเมนูที่แสดงในหน้าจอ
#define MENU_WIDTH 20
//ขนาดช่องว่างของท่อ
#define GAP_SIZE 7
//ระยะห่างระหว่างท่อ
#define PIPE_DIF 45

using namespace std;

//การเรียกใช้งานฟังก์ชัน GetStdHandle เพื่อรับพอยน์เตอร์ที่ชี้ไปยังหน้าจอเพื่อเป็นการใช้งานหน้าจอ Console ของ Windows API
HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
//เป็นตัวแปรชนิด COORD ซึ่งเป็นตัวแปรที่ใช้เก็บพิกัดตำแหน่งของ Cursor ในหน้าจอ Console
COORD CursorPosition;

//เป็นอาเรย์ขนาด 3 ช่องที่ใช้เก็บตำแหน่งของท่อ (pipe) ในแนวแกน x
int pipePos[3];
//เป็นอาเรย์ขนาด 3 ช่องที่ใช้เก็บตำแหน่งของช่องว่างในท่อ (gap) ในแนวแกน y
int gapPos[3];
//เป็นอาเรย์ขนาด 3 ช่องที่ใช้เก็บค่าตัวแปรที่บอกว่าท่อตัวที่ i ยังมีอยู่หรือไม่
int pipeFlag[3];
//เป็นอาเรย์สองมิติขนาด 2x6 ที่เก็บรูปร่างของนก
char bird[2][6] = { '/','-','-','o','\\',' ',
					'|','_','_','_',' ','>' };
//เป็นตัวแปรที่ใช้เก็บตำแหน่งแนวตั้งของนก
int birdPos = 6;
//เป็นตัวแปรที่ใช้เก็บค่าคะแนนที่ผู้เล่นได้รับ และเริ่มต้นค่าจาก 0 คะแนน
int score = 0;

/* gotoxy(x, y): ใช้ในการเคลื่อนที่ Cursor ไปยังตำแหน่งที่ต้องการบน Console
void gotoxy(int x, int y)
ฟังก์ชั่นนี้ใช้เพื่อเลื่อน cursor ไปยังตำแหน่งที่กำหนดโดยการรับค่า x,y ซึ่งเป็นตำแหน่งบนแนวแกน x และ y ตามลำดับ 
จากนั้นใช้ฟังก์ชั่น SetConsoleCursorPosition() เพื่อเลื่อน cursor ไปยังตำแหน่งที่กำหนด */
void gotoxy(int x, int y)
{
	CursorPosition.X = x;
	CursorPosition.Y = y;
	SetConsoleCursorPosition(console, CursorPosition);
}

/*setcursor(visible, size): ใช้ในการเปลี่ยนการแสดงผล Cursor บน Console
void setcursor(bool visible, DWORD size)
ฟังก์ชั่นนี้ใช้สำหรับตั้งค่ารูปแบบของ cursor โดยมีการรับค่าพารามิเตอร์ visible ซึ่งจะกำหนดว่า cursor จะแสดงหรือไม่ และ size 
ซึ่งเป็นขนาดของ cursor หาก size เป็น 0 จะใช้ค่าเริ่มต้นขนาด 20 จากนั้นใช้ฟังก์ชั่น SetConsoleCursorInfo() เพื่อตั้งค่ารูปแบบของ cursor */
void setcursor(bool visible, DWORD size) 
{
	if(size == 0)
		size = 20;	
	
	CONSOLE_CURSOR_INFO lpCursor;	
	lpCursor.bVisible = visible;
	lpCursor.dwSize = size;
	SetConsoleCursorInfo(console,&lpCursor);
}

/*updateScore(): ใช้ในการแสดงคะแนนของผู้เล่นบน Console
ฟังก์ชัน updateScore() เป็นฟังก์ชันที่ไม่มีการรับค่าพารามิเตอร์และไม่มีการส่งค่ากลับ ซึ่งจะใช้สำหรับแสดงผลคะแนนของผู้เล่น 
โดยจะใช้ฟังก์ชัน gotoxy() เพื่อเลื่อน cursor ไปยังตำแหน่งที่ต้องการแสดงผล และใช้คำสั่ง cout() เพื่อแสดงผลข้อมูล */
void updateScore(){
	gotoxy(WIN_WIDTH + 7, 5);cout<<"Score: "<<score<<endl;
}

/*drawBorder(): ใช้ในการวาดเส้นขอบสี่เหลี่ยมที่กำหนดขนาดด้วยตัวแปร SCREEN_WIDTH และ SCREEN_HEIGHT
void drawBorder()
ฟังก์ชั่นนี้ใช้สำหรับวาดเส้นขอบบนหน้าจอ console โดยจะวาดเส้นตามแนวแกน x และ y ตามความยาวและความกว้างของหน้าจอ 
และเส้นตามแนว y ให้หยุดที่ตำแหน่ง WIN_WIDTH ซึ่งกำหนดเป็นค่าคงที่ ในโปรแกรมนี้เครื่องหมาย "X" ถูกใช้เพื่อแสดงเส้นขอบ */
void drawBorder(){ 
	
	for(int i=0; i<SCREEN_WIDTH; i++){
		gotoxy(i,0); cout<<"X";
		gotoxy(i,SCREEN_HEIGHT); cout<<"X";
	}
	
	for(int i=0; i<SCREEN_HEIGHT; i++){
		gotoxy(0,i); cout<<"X";
		gotoxy(SCREEN_WIDTH,i); cout<<"X";
	}
	for(int i=0; i<SCREEN_HEIGHT; i++){
		gotoxy(WIN_WIDTH,i); cout<<"X";
	}
}

/*genPipe(ind): ใช้ในการสุ่มตำแหน่งของท่อที่จะปรากฎบน Console
ฟังก์ชัน genPipe(int ind) จะรับพารามิเตอร์ ind ซึ่งเป็นตัวเลขที่แทนค่า index ของท่อ แล้วจะสุ่มตำแหน่งของช่องว่างในท่อ (gapPos) 
โดยให้ gapPos[ind] เท่ากับ 3 บวกกับค่าสุ่มที่ได้จาก rand()%14 เพื่อให้ช่องว่างอยู่ในแถวที่สูงสุด และไม่อยู่ในแถวขอบจอ */
void genPipe(int ind){
	gapPos[ind] = 3 + rand()%14; 
}
/*drawPipe(ind): ใช้ในการวาดท่อบน Console
ฟังก์ชัน drawPipe(int ind) จะรับพารามิเตอร์ ind ซึ่งเป็นตัวเลขที่แทนค่า index ของท่อ แล้วจะวาดท่อโดยใช้ gotoxy และ cout เพื่อสร้างเส้นท่อ
ด้วยเครื่องหมาย * โดยจะวาดเส้นท่อที่ต่ำแหน่ง pipePos[ind] (ตำแหน่งที่ท่ออยู่บนแกน x) โดยวาดจากบนลงล่างก่อน จากนั้นวาดจากล่างขึ้นบน */
void drawPipe(int ind){
	// ถ้าท่อยังไม่ถูกลบออกจากหน้าจอ
	if( pipeFlag[ind] == true ){
		// วาดท่อที่มีช่องว่างด้านบน
		for(int i=0; i<gapPos[ind]; i++){ 
			gotoxy(WIN_WIDTH-pipePos[ind],i+1); cout<<"***"; 
		}
		// วาดท่อที่มีช่องว่างด้านล่าง
		for(int i=gapPos[ind]+GAP_SIZE; i<SCREEN_HEIGHT-1; i++){ 
			gotoxy(WIN_WIDTH-pipePos[ind],i+1); cout<<"***"; 
		}
	} 
}
/*erasePipe(ind): ใช้ในการลบท่อบน Console
ฟังก์ชั่น erasePipe(int ind) จะรับค่าตัวแปร ind เป็นพารามิเตอร์ และทำการลบท่อที่ตำแหน่ง pipePos[ind] โดยใช้ gotoxy() 
ในการเลื่อนเคอร์เซอร์ไปยังตำแหน่งที่ต้องการลบ จากนั้นใช้คำสั่ง cout ในการแสดงผลตัวอักษรว่างเพื่อลบตัวอักษร *** ตามจำนวนตำแหน่ง gapPos[ind] 
และจำนวนตำแหน่งที่เหลือระหว่าง GAP_SIZE และ SCREEN_HEIGHT-1 ที่วาดไว้ก่อนหน้านี้ */
void erasePipe(int ind){
	// ถ้าท่อยังไม่ถูกลบออกจากหน้าจอ
	if( pipeFlag[ind] == true ){
		// ลบท่อที่มีช่องว่างด้านบน
		for(int i=0; i<gapPos[ind]; i++){ 
			gotoxy(WIN_WIDTH-pipePos[ind],i+1); cout<<"   "; 
		}
		// ลบท่อที่มีช่องว่างด้านล่าง
		for(int i=gapPos[ind]+GAP_SIZE; i<SCREEN_HEIGHT-1; i++){ 
			gotoxy(WIN_WIDTH-pipePos[ind],i+1); cout<<"   "; 
		}
	}
}
/*drawBird(): ใช้ในการวาดนกบน Console
ฟังก์ชั่น drawBird() ใช้สำหรับวาดนกลงบนหน้าจอ โดยใช้ตัวแปร birdPos ที่เก็บค่าตำแหน่งแกน y ของนก 
และใช้ gotoxy() เพื่อเลื่อนเคอร์เซอร์ไปยังตำแหน่งที่ต้องการแล้วแสดงตัวอักษรของนกตามตำแหน่งในตัวแปร bird */
void drawBird(){
	for(int i=0; i<2; i++){
		for(int j=0; j<6; j++){
			gotoxy(j+2,i+birdPos); cout<<bird[i][j];
		}
	}
}
/*eraseBird(): ใช้ในการลบนกบน Console
ฟังก์ชั่น eraseBird() ใช้สำหรับลบตัวนกที่วาดอยู่บนหน้าจอ โดยใช้ตัวแปร birdPos และ gotoxy() 
เหมือนกับฟังก์ชั่น drawBird() แต่แทนที่ตัวอักษรของนกด้วยช่องว่าง */
void eraseBird(){
	for(int i=0; i<2; i++){
		for(int j=0; j<6; j++){
			gotoxy(j+2,i+birdPos); cout<<" ";
		}
	}
}

/*collision(): ใช้ในการตรวจสอบว่านกชนกับท่อหรือไม่
ฟังก์ชั่น collision() ใช้สำหรับตรวจสอบว่านกชนกำแพงหรือไม่ โดยเช็คว่าตำแหน่งของท่อที่ต่ำแหน่งตัวแปร pipePos[0] 
มีค่ามากกว่าหรือเท่ากับ 61 และตำแหน่งของนก birdPos อยู่ระหว่างช่องว่างของท่อหรือไม่ ถ้าใช่จะ return ค่า 1 แสดงว่าเกมจบลงและนกชนกำแพง 
หากไม่ใช่จะ return ค่า 0 แสดงว่าเกมยังไม่จบ */
int collision(){
	if( pipePos[0] >= 61  ){
		if( birdPos<gapPos[0] || birdPos >gapPos[0]+GAP_SIZE ){
			return 1;
		}
	}
	return 0;
}

/*ฟังก์ชั่น instructions() นี้จะแสดงคำแนะนำในการเล่นเกม โดยจะแสดงข้อความ "Instructions" 
และข้อความ "Press spacebar to make bird fly" บนหน้าจอ และรอการกดปุ่มใดๆ เพื่อกลับไปยังหน้าเมนู */
void instructions(){
	
	system("cls");
	cout<<"Instructions";
	cout<<"\n----------------";
	cout<<"\n Press spacebar to make bird fly";
	cout<<"\n\nPress any key to go back to menu";
	getch();
}

/*ฟังก์ชัน updateScore1 รับพารามิเตอร์สองตัว คือ playerName และ score โดย playerName 
เป็นข้อความแทนชื่อผู้เล่นและ score เป็นจำนวนเต็มแทนคะแนนที่ผู้เล่นได้รับในการเล่นเกมหนึ่งๆ
ฟังก์ชันจะทำการเปิดไฟล์ abc.txt ในโหมดเพิ่มเติม (append mode) โดยใช้ ofstream เพื่อทำการเขียนข้อมูลลงไปในไฟล์ 
จากนั้น จะทำการเขียน playerName และ score ในบรรทัดเดียวกัน โดยคั่นด้วยช่องว่าง และจบด้วยการขึ้นบรรทัดใหม่ (endl) 
เพื่อให้ข้อมูลถูกเขียนลงไปในบรรทัดใหม่ทุกครั้งที่เขียนลงไป
เมื่อเขียนข้อมูลเสร็จสิ้น ฟังก์ชันจะทำการปิดไฟล์โดยใช้ outfile.close() เพื่อป้องกันการเขียนข้อมูลเข้าไปในไฟล์ในขณะที่ไฟล์ยังเปิดอยู่ 
ซึ่งอาจทำให้เกิดความผิดพลาดได้ ดังนั้นการปิดไฟล์เป็นสิ่งสำคัญที่ต้องทำหลังจากเขียนข้อมูลลงไปในไฟล์เสร็จแล้ว*/
void updateScore1(string playerName, int score) {
     ofstream outfile("abc.txt", ios::app);

    // Write name and score to file
    outfile << playerName << " " << score << endl;

    // Close file
    outfile.close();
}

/*ฟังก์ชัน gameover() เป็นฟังก์ชันที่ถูกเรียกใช้เมื่อผู้เล่นเล่นเกมจนคะแนนหมด หรือเกมจบลง 
โดยมีหน้าที่แสดงคะแนนของผู้เล่นที่ได้รับ และบันทึกคะแนนของผู้เล่นลงในไฟล์เพื่อเก็บประวัติคะแนน
การทำงานของฟังก์ชัน gameover() จะเริ่มต้นด้วยการเคลียร์หน้าจอด้วยฟังก์ชัน system("cls") จากนั้นจะแสดงข้อความ 
"Game over! Your score is " พร้อมกับค่า score ที่เก็บคะแนนที่ผู้เล่นได้รับ ดังนั้นผู้เล่นจะเห็นผลลัพธ์ที่แสดงคะแนนที่ได้เมื่อเล่นเกมจบลง
จากนั้นฟังก์ชันจะขอข้อมูลชื่อของผู้เล่นโดยแสดงข้อความ "Enter your name: " และรับชื่อผู้เล่นจากผู้ใช้ผ่านคำสั่ง 
cin >> playerName; หลังจากนั้นฟังก์ชันจะเรียกใช้ฟังก์ชัน updateScore1(playerName, score); 
เพื่อบันทึกคะแนนลงในไฟล์ abc.txt โดยใช้ชื่อของผู้เล่นและคะแนนที่ได้รับ
สุดท้ายฟังก์ชันจะแสดงข้อความ "Press any key to go back to menu...." และรอรับอินพุตจากผู้ใช้ด้วยคำสั่ง getch(); 
โดยการกดปุ่มใดๆบนคีย์บอร์ดจะเป็นการกลับไปยังเมนูหลักของเกม*/
void gameover(){
    system("cls");
    cout<<endl;
    cout<<"\t\t-------------------------------------------"<<endl;
    cout<<"\t\t--------Game over! Your score is " << score << "--------" << endl;
    cout<<"\t\t-------------------------------------------"<<endl<<endl;

    // Prompt user to enter their name
    cout << "\t\t\tGame over! Your score is " << score << endl;

	// Prompt player to enter their name
	cout << "\t\t\tEnter your name: ";
	string playerName;
	cin >> playerName;
	// Update scores file
	updateScore1(playerName, score);


    cout<<"\t\tPress any key to go back to menu....";
    getch();
}

/*ฟังก์ชัน printLeaderboard() ใช้สำหรับอ่านไฟล์ abc.txt ที่เก็บข้อมูลผู้เล่นและคะแนนของพวกเขา 
และแสดงอันดับ 5 อันดับแรกของผู้เล่นที่มีคะแนนสูงสุดในการเล่นเกม
เมื่อเปิดไฟล์ abc.txt แล้ว เริ่มต้นโดยสร้าง map เพื่อเก็บชื่อผู้เล่นและคะแนนของพวกเขา จากนั้นวนลูปในการอ่านไฟล์ abc.txt 
เพื่อดึงชื่อผู้เล่นและคะแนนของพวกเขาออกมา ถ้าชื่อผู้เล่นนั้นมีอยู่ใน map แล้ว จะเปรียบเทียบคะแนนใหม่กับคะแนนเดิม แล้วเก็บคะแนนสูงสุดไว้ 
ถ้าชื่อผู้เล่นนั้นยังไม่มีอยู่ใน map จะเพิ่มชื่อผู้เล่นและคะแนนของพวกเขาลงใน map
เมื่อได้ข้อมูลผู้เล่นและคะแนนของพวกเขาจัดเก็บใน map เรียบร้อยแล้ว จะเริ่มต้นด้วยการเรียงลำดับผู้เล่นตามคะแนนที่ได้จากมันในลำดับน้อยไปหามาก 
โดยใช้ vector เพื่อเก็บข้อมูลนี้ จากนั้นใช้ฟังก์ชัน sort() เพื่อเรียงลำดับตามคะแนนในแบบน้อยไปหามาก
เมื่อได้ลำดับผู้เล่นที่มีคะแนนสูงสุด จะแสดงผลลัพธ์โดยแสดงอันดับของผู้เล่น ชื่อผู้เล่น และคะแนนของพวกเขา โดยจะแสดงเพียง 5 อันดับแรกเท่านั*/
void printLeaderboard() {
    // Open file for reading
	system("cls");
    ifstream infile("abc.txt");

    // Create a map to store player names and scores
    map<string, int> scores;

    string line;
    while (getline(infile, line)) {
        // Extract player name and score from line
        string name = line.substr(0, line.find(" "));
        int score = stoi(line.substr(line.find(" ") + 1));

        // If the name already exists in the map, update score if new score is higher
        if (scores.find(name) != scores.end()) {
            int existingScore = scores[name];
            if (score > existingScore) {
                scores[name] = score;
            }
        }
        // If the name does not exist in the map, add it with the score
        else {
            scores[name] = score;
        }
    }

    // Sort players by score in descending order
    vector<pair<string, int>> sortedScores;
    for (auto it = scores.begin(); it != scores.end(); ++it) {
        sortedScores.push_back(make_pair(it->first, it->second));
    }
    sort(sortedScores.begin(), sortedScores.end(), [](pair<string, int> a, pair<string, int> b) { return a.second > b.second; });

    // Print leaderboard
    cout << "LEADERBOARD" << endl;
    for (int i = 0; i < sortedScores.size() && i < 5; ++i) {
        cout << i+1 << ". " << sortedScores[i].first << " : " << sortedScores[i].second << " Point"<< endl;
    }

    // Close file
    infile.close();
	getch();
}

/*ฟังก์ชั่น play() ใช้สำหรับเริ่มเกม Flappy Bird โดยทำงานตามลำดับดังนี้
1.กำหนดค่าเริ่มต้นของตัวแปรต่าง ๆ ที่จำเป็นในการทำงานของเกม เช่น ความเร็วของเกม (speed) ตำแหน่งของท่อ (pipePos) และคะแนน (score)
2.เรียกใช้ฟังก์ชั่น drawBorder() เพื่อวาดเส้นขอบของหน้าจอเกม
3.เรียกใช้ฟังก์ชั่น genPipe() เพื่อสร้างท่อแรก และเรียกใช้ฟังก์ชั่น updateScore() เพื่อแสดงคะแนนเริ่มต้น
4.แสดงหัวข้อเกม และคำแนะนำการควบคุมเกมบนด้านขวาของหน้าจอ
5.รอการกดปุ่มใด ๆ เพื่อเริ่มเล่นเกม และลบข้อความ "Press any key to start" ทิ้งไป
6.เข้าสู่ลูป while และทำต่อไปเรื่อย ๆ จนกว่าผู้เล่นจะตายหรือกดปุ่ม ESC เพื่อออกจากเกม
7.ตรวจสอบว่ามีการกดปุ่มที่กำหนดในฟังก์ชั่น kbhit() หรือไม่ โดยปุ่มที่รองรับได้คือปุ่ม Spacebar เพื่อกระโดดขึ้นบนจอ และปุ่ม ESC เพื่อออกจากเกม
8.เรียกใช้ฟังก์ชั่นสำหรับวาดตัวนก และท่อที่แสดงบนจอ ตรวจสอบว่าเกิดการชนกับท่อหรือไม่ ถ้าเกิดการชน ให้แสดงข้อความ Game Over และออกจากเกม
9.ลบตัวนกและท่อออกจากจอ และเลื่อนตำแหน่งตัวนกไปข้างล่าง*/
void play(){
	int speed = 100;
	birdPos = 6;
	score = 0;
	pipeFlag[0] = 1; 
	pipeFlag[1] = 0;
	pipePos[0] = pipePos[1] = 4;
	system("cls"); 
	drawBorder();
	genPipe(0);
	updateScore();
	
	gotoxy(WIN_WIDTH + 5, 2);cout<<"FLAPPY BIRD";
	gotoxy(WIN_WIDTH + 6, 4);cout<<"----------";
	gotoxy(WIN_WIDTH + 6, 6);cout<<"----------";
	gotoxy(WIN_WIDTH + 7, 12);cout<<"Control ";
	gotoxy(WIN_WIDTH + 7, 13);cout<<"-------- ";
	gotoxy(WIN_WIDTH + 2, 14);cout<<" Spacebar = jump";
	
	gotoxy(10, 5);cout<<"Press any key to start";
	getch();
	gotoxy(10, 5);cout<<"                      ";
	
	while(1){
		 
		if(kbhit()){
			char ch = getch();
			if(ch==32){
				if( birdPos > 3 )
					birdPos-=3;
			} 
			if(ch==27){
				exit(0);
			}
		}
		
		drawBird();
		drawPipe(0);
		drawPipe(1);
		if( collision() == 1 ){
			gameover();
			return;
		}
		Sleep(speed);
		eraseBird();
		erasePipe(0);
		erasePipe(1);
		birdPos += 1;
		
		if( birdPos > SCREEN_HEIGHT - 2 ){
			gameover();
			return;
		}
		
		if( pipeFlag[0] == 1 )
			pipePos[0] += 2;
		
		if( pipeFlag[1] == 1 )
			pipePos[1] += 2;
		
		if( pipePos[0] >= 40 && pipePos[0] < 42 ){
			pipeFlag[1] = 1;
			pipePos[1] = 4;
			genPipe(1);
		}
		if( pipePos[0] > 68 ){
			score++;
			speed--;
			updateScore();
			pipeFlag[1] = 0;
			pipePos[0] = pipePos[1];
			gapPos[0] = gapPos[1];
		}
	}
	 
}

int main()
{
	setcursor(0,0); 
	srand( (unsigned)time(NULL)); 
	
//	play();
	
	do{
		system("cls");
		gotoxy(10,5); cout<<" -------------------------- "; 
		gotoxy(10,6); cout<<" |      Flappy Bird       | "; 
		gotoxy(10,7); cout<<" --------------------------";
		gotoxy(10,9); cout<<"1. Start Game";
		gotoxy(10,10); cout<<"2. Instructions";	 
		gotoxy(10,11); cout<<"3. Ranking";
		gotoxy(10,12); cout<<"4. Quit";
		gotoxy(10,14); cout<<"Select option: ";
		char op = getche();
		
		if( op=='1') play();
		else if( op=='2') instructions();
		else if( op=='3') printLeaderboard();
		else if( op=='4') exit(0);
		
	}while(1);
	
	return 0;
}
