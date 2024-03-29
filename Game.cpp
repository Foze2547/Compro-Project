#include<iostream>
#include<conio.h>
#include<dos.h>
#include<stdlib.h>
#include<string.h>
#include<string>
#include<fstream>
#include<windows.h>
#include<time.h>
#include<map>
#include<vector>
#include<algorithm>

#define SCREEN_WIDTH 90
#define SCREEN_HEIGHT 26
#define WIN_WIDTH 70
#define MENU_WIDTH 20
#define GAP_SIZE 7
#define PIPE_DIF 45

using namespace std;
 
HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;

int pipePos[3];
int gapPos[3];
int pipeFlag[3];
char bird[2][6] = { '/','-','-','o','\\',' ',
					'|','_','_','_',' ','>' };
int birdPos = 6;
int score = 0;

void gotoxy(int x, int y)
{
	CursorPosition.X = x;
	CursorPosition.Y = y;
	SetConsoleCursorPosition(console, CursorPosition);
}

void setcursor(bool visible, DWORD size) 
{
	if(size == 0)
		size = 20;	
	
	CONSOLE_CURSOR_INFO lpCursor;	
	lpCursor.bVisible = visible;
	lpCursor.dwSize = size;
	SetConsoleCursorInfo(console,&lpCursor);
}

void updateScore(){
	gotoxy(WIN_WIDTH + 7, 5);cout<<"Score: "<<score<<endl;
}

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
void genPipe(int ind){
	gapPos[ind] = 3 + rand()%14; 
}
void drawPipe(int ind){
	if( pipeFlag[ind] == true ){
		for(int i=0; i<gapPos[ind]; i++){ 
			gotoxy(WIN_WIDTH-pipePos[ind],i+1); cout<<"***"; 
		}
		for(int i=gapPos[ind]+GAP_SIZE; i<SCREEN_HEIGHT-1; i++){ 
			gotoxy(WIN_WIDTH-pipePos[ind],i+1); cout<<"***"; 
		}
	} 
}
void erasePipe(int ind){
	if( pipeFlag[ind] == true ){
		for(int i=0; i<gapPos[ind]; i++){ 
			gotoxy(WIN_WIDTH-pipePos[ind],i+1); cout<<"   "; 
		}
		for(int i=gapPos[ind]+GAP_SIZE; i<SCREEN_HEIGHT-1; i++){ 
			gotoxy(WIN_WIDTH-pipePos[ind],i+1); cout<<"   "; 
		}
	}
}

void drawBird(){
	for(int i=0; i<2; i++){
		for(int j=0; j<6; j++){
			gotoxy(j+2,i+birdPos); cout<<bird[i][j];
		}
	}
}
void eraseBird(){
	for(int i=0; i<2; i++){
		for(int j=0; j<6; j++){
			gotoxy(j+2,i+birdPos); cout<<" ";
		}
	}
}

int collision(){
	if( pipePos[0] >= 61  ){
		if( birdPos<gapPos[0] || birdPos >gapPos[0]+GAP_SIZE ){
			return 1;
		}
	}
	return 0;
}

void instructions(){
	
	system("cls");
	cout<<"Instructions";
	cout<<"\n----------------";
	cout<<"\n Press spacebar to make bird fly";
	cout<<"\n\nPress any key to go back to menu";
	getch();
}

void updateScore1(string playerName, int score) {
     ofstream outfile("abc.txt", ios::app);

    // Write name and score to file
    outfile << playerName << " " << score << endl;

    // Close file
    outfile.close();
}

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
