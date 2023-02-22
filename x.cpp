/*-stdio.h เป็นไลบรารีที่มักจะใช้กันอยู่บ่อยในการทำงานเกี่ยวกับการอ่านและเขียนไฟล์ 
ส่วนไลบรารีอื่นๆ เช่น iostream,conio.h,dos.h ถูกนำมาใช้กับการเขียนโปรแกรมเกี่ยวกับคอมพิวเตอร์ อื่นๆ 
ส่วนในโปรแกรมนี้ใช้ไลบรารีต่างๆอย่างเช่น stdlib.h ไลบรารีนี้จะเป็นไลบรารีที่เกี่ยวข้องกับการจัดการหน่วยความจำ 
-iostream: ไลบรารีสำหรับการรับและแสดงผลข้อมูล (input/output) 
-conio.h: ไลบรารีสำหรับการรับค่าจากคีย์บอร์ด-ใช้ในการเรียกใช้ฟังก์ชัน getch() ที่ใช้รับค่า Input จาก keyboard
-dos.h: ไลบรารีสำหรับการใช้ฟังก์ชัน sleep() เพื่อจำลองความเร็วของเกม
-stdlib.h: ไลบรารีสำหรับการใช้ฟังก์ชัน rand() เพื่อสุ่มตำแหน่งของท่อ
-string.h: ไลบรารีสำหรับการใช้ฟังก์ชัน strlen() เพื่อหาความยาวของข้อความ
-windows.h: ไลบรารีสำหรับการใช้ฟังก์ชัน SetConsoleCursorPosition() ใช้ในการตั้งค่าตำแหน่ง Cursor บนหน้าจอ command prompt 
โดยโค้ดด้านบนเป็นการกำหนดค่าคงที่สำหรับตำแหน่งและขนาดของหน้าจอ เช่น SCREEN_WIDTH กำหนดขนาดความกว้างของหน้าจอเป็น 90 ตัวอักษร 
ส่วน bird และตัวแปรที่เกี่ยวข้องกับ game เช่น pipePos ใช้เก็บตำแหน่งของท่อ, gapPos เก็บตำแหน่งของช่องว่าง
, pipeFlag ใช้เก็บสถานะว่าท่อมีการแสดงอยู่หรือไม่, birdPos ใช้เก็บตำแหน่งของนก, score ใช้เก็บคะแนนที่ผู้เล่นได้ทำได้ในแต่ละรอบเกม เป็นต้น
-time.h: ไลบรารีสำหรับการใช้ฟังก์ชัน time() เพื่อสุ่มตำแหน่งของท่อ
โดยโค้ดที่ประกาศไว้ด้านบนเป็นการกำหนดค่าคงที่และตัวแปรที่ใช้ในการเก็บข้อมูลต่างๆ เช่น ตำแหน่งของท่อ (pipePos)
, ตำแหน่งของช่องว่างระหว่างท่อ (gapPos), สถานะของท่อ (pipeFlag), ตำแหน่งของนก (birdPos)
, คะแนน (score) และรูปแบบของนก (bird) ซึ่งถูกกำหนดเป็นอาร์เรย์สองมิติ */
#include<iostream>
#include<conio.h>
#include<dos.h>
#include<stdlib.h>
#include<string.h>
#include <windows.h>
#include <time.h>

#define SCREEN_WIDTH 90
#define SCREEN_HEIGHT 26
#define WIN_WIDTH 70
#define MENU_WIDTH 20
#define GAP_SIZE 7
#define PIPE_DIF 45

using namespace std;
//		cout<<"���������";
 
HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;

int pipePos[3];
int gapPos[3];
int pipeFlag[3];
char bird[2][6] = { '/','-','-','o','\\',' ',
					'|','_','_','_',' ','>' };
int birdPos = 6;
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

/*drawBorder(): ใช้ในการวาดเส้นขอบสี่เหลี่ยมที่กำหนดขนาดด้วยตัวแปร SCREEN_WIDTH และ SCREEN_HEIGHT
void drawBorder()
ฟังก์ชั่นนี้ใช้สำหรับวาดเส้นขอบบนหน้าจอ console โดยจะวาดเส้นตามแนวแกน x และ y ตามความยาวและความกว้างของหน้าจอ 
และเส้นตามแนว y ให้หยุดที่ตำแหน่ง WIN_WIDTH ซึ่งกำหนดเป็นค่าคงที่ ในโปรแกรมนี้เครื่องหมาย "�" ถูกใช้เพื่อแสดงเส้นขอบ */
void drawBorder(){ 
	
	for(int i=0; i<SCREEN_WIDTH; i++){
		gotoxy(i,0); cout<<"�";
		gotoxy(i,SCREEN_HEIGHT); cout<<"�";
	}
	
	for(int i=0; i<SCREEN_HEIGHT; i++){
		gotoxy(0,i); cout<<"�";
		gotoxy(SCREEN_WIDTH,i); cout<<"�";
	}
	for(int i=0; i<SCREEN_HEIGHT; i++){
		gotoxy(WIN_WIDTH,i); cout<<"�";
	}
}

/*genPipe(ind): ใช้ในการสุ่มตำแหน่งของท่อที่จะปรากฎบน Console
ฟังก์ชัน genPipe(int ind) จะรับพารามิเตอร์ ind ซึ่งเป็นตัวเลขที่แทนค่า index ของท่อ แล้วจะสุ่มตำแหน่งของช่องว่างในท่อ (gapPos) 
โดยให้ gapPos[ind] เท่ากับ 3 บวกกับค่าสุ่มที่ได้จาก rand()%14 เพื่อให้ช่องว่างอยู่ในแถวที่สูงสุด และไม่อยู่ในแถวขอบจอ */
void genPipe(int ind){
	// กำหนดตำแหน่งของช่องว่างของท่อแบบสุ่ม
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
//			cout<< " HIT ";
//			getch();
			return 1;
		}
	}
	return 0;
}

/*debug(): ใช้ในการแสดงข้อมูลสถานะต่าง ๆ บน Console
ฟังก์ชัน debug() เป็นฟังก์ชันที่ไม่มีการรับค่าพารามิเตอร์และไม่มีการส่งค่ากลับ ซึ่งจะใช้สำหรับการแสดงผลข้อมูลที่ต้องการตรวจสอบในการดีบัก 
ในที่นี้จะเป็นการแสดงผลตำแหน่งของท่อ (pipe) ในเกม โดยจะใช้ฟังก์ชัน gotoxy() เพื่อเลื่อน cursor ไปยังตำแหน่งที่ต้องการแสดงผล 
และใช้คำสั่ง cout() เพื่อแสดงผลข้อมูล */
void debug(){
//	gotoxy(SCREEN_WIDTH + 3, 4); cout<<"Pipe Pos: "<<pipePos[0];
	
}

/*gameover(): ใช้ในการแสดงหน้าจอ Game Over เมื่อนกชนกับท่อ
ฟังก์ชัน gameover() เป็นฟังก์ชันที่ไม่มีการรับค่าพารามิเตอร์และไม่มีการส่งค่ากลับ ซึ่งจะใช้สำหรับแสดงผลข้อความ Game Over 
และรอการกดปุ่มจากผู้เล่นเพื่อกลับไปยังหน้าเมนู โดยจะใช้คำสั่ง system("cls") เพื่อล้างหน้าจอ และใช้คำสั่ง cout() เพื่อแสดงผลข้อความ */
void gameover(){
	system("cls");
	cout<<endl;
	cout<<"\t\t--------------------------"<<endl;
	cout<<"\t\t-------- Game Over -------"<<endl;
	cout<<"\t\t--------------------------"<<endl<<endl;
	cout<<"\t\tPress any key to go back to menu.";
	getch();
}

/*updateScore(): ใช้ในการแสดงคะแนนของผู้เล่นบน Console
ฟังก์ชัน updateScore() เป็นฟังก์ชันที่ไม่มีการรับค่าพารามิเตอร์และไม่มีการส่งค่ากลับ ซึ่งจะใช้สำหรับแสดงผลคะแนนของผู้เล่น 
โดยจะใช้ฟังก์ชัน gotoxy() เพื่อเลื่อน cursor ไปยังตำแหน่งที่ต้องการแสดงผล และใช้คำสั่ง cout() เพื่อแสดงผลข้อมูล */
void updateScore(){
	gotoxy(WIN_WIDTH + 7, 5);cout<<"Score: "<<score<<endl;
}

/*instructions(): ใช้ในการแสดงคำแนะนำในการเล่นเกม Flappy Bird
ฟังก์ชั่น instructions() นี้จะแสดงคำแนะนำในการเล่นเกม โดยจะแสดงข้อความ "Instructions" 
และข้อความ "Press spacebar to make bird fly" บนหน้าจอ และรอการกดปุ่มใดๆ เพื่อกลับไปยังหน้าเมนู */
void instructions(){
	
	system("cls");
	cout<<"Instructions";
	cout<<"\n----------------";
	cout<<"\n Press spacebar to make bird fly";
	cout<<"\n\nPress any key to go back to menu";
	getch();
}

/*ฟังก์ชั่น play() นี้จะเป็นส่วนหลักของเกม Flappy Bird โดยจะตั้งค่าต่างๆ เช่น ตำแหน่งของนก คะแนน ตำแหน่งท่อ และสร้างท่อ 
จากนั้นจะแสดงหน้าจอของเกม โดยจะมีข้อความ "FLAPPY BIRD" และข้อความ "Control" แสดงวิธีการควบคุมของเกม 
และข้อความ "Press any key to start" ซึ่งผู้เล่นจะต้องกดปุ่มใดๆ เพื่อเริ่มเล่นเกม
ในลูป while(1) นี้จะเป็นการวนลูปเพื่อเล่นเกม โดยจะตรวจสอบว่าผู้เล่นกดปุ่มใดๆ หรือไม่ หากกดปุ่ม spacebar จะเป็นการกระโดดของนก 
โดยการเลื่อนตำแหน่งของนกไปด้านบน และตรวจสอบการชนกับท่อ หากเกิดการชนกัน จะแสดงหน้าจอ Game Over และกลับไปยังหน้าเมนู 
แต่ถ้านกลอยผ่านท่อได้ จะเพิ่มคะแนน และสร้างท่อใหม่ โดยฟังก์ชั่น genPipe() และอัปเดตคะแนนที่แสดงบนหน้าจอผ่านฟังก์ชั่น updateScore() */
void play(){
	
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
				break;
			}
		}
		
		drawBird();
		drawPipe(0);
		drawPipe(1);
		debug();
		if( collision() == 1 ){
			gameover();
			return;
		}
		Sleep(100);
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
			updateScore();
			pipeFlag[1] = 0;
			pipePos[0] = pipePos[1];
			gapPos[0] = gapPos[1];
		}
		
	}
	 
}

/*ฟังก์ชัน int main() เป็นฟังก์ชันหลักในโปรแกรม C++ ที่เป็นจุดเริ่มต้นในการทำงานของโปรแกรม ซึ่งในโปรแกรม Flappy Bird จะมีการเรียกใช้ฟังก์ชันต่างๆดังนี้
1.setcursor(0,0); เป็นฟังก์ชันที่ใช้ในการปิดการแสดงผล cursor บนหน้าจอ
2.srand( (unsigned)time(NULL)); เป็นฟังก์ชันที่ใช้ในการกำหนด seed ให้กับการสุ่มตัวเลขโดยใช้เวลาปัจจุบันเป็น seed
3.do-while loop ที่ใช้ในการแสดงเมนูหลักของเกม Flappy Bird และรอให้ผู้เล่นเลือก option เพื่อทำงานต่างๆ 
โดยจะวนลูปอย่างต่อเนื่องจนกว่าผู้เล่นจะเลือก option เป็น 3 (Quit)
4.ฟังก์ชัน play() เป็นฟังก์ชันที่ใช้ในการเริ่มเล่นเกม Flappy Bird
5.ฟังก์ชัน instructions() เป็นฟังก์ชันที่ใช้ในการแสดงคำอธิบายวิธีการเล่น Flappy Bird และความหมายของอุปสรรคต่างๆ
6.ฟังก์ชัน exit(0) เป็นฟังก์ชันที่ใช้ในการจบโปรแกรมทันทีโดยที่ไม่ต้องทำงานอื่นๆต่อไป */
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
		gotoxy(10,11); cout<<"3. Quit";
		gotoxy(10,13); cout<<"Select option: ";
		char op = getche();
		
		if( op=='1') play();
		else if( op=='2') instructions();
		else if( op=='3') exit(0);
		
	}while(1);
	
	return 0;
}
