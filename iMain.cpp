#include <errno.h>
#include "iGraphics.h"
#include<string>

#define screenHeight 600
#define screenWidth 930
#define backgroundSpeed 70
#define JUMPLIMIT 50
#define upperBackgroundspeed 10
#define lowerBackgroundspeed 12
#define ENEMYNUMBER 4
#define PI 3.14 
int mposx, mposy,i,j;
//int mx = 0;
//int my = 0;
bool musicOn = true;
int x = 0;
int y = 0;
int r = 255;
int g = 255;
int b = 255;
int dx[40] = { 0, 8, 4, -16, 8, 4, -16, 0, -2, -2, 0, -30, -23, -8, -6, -9, -8, -7, -5, -7, -2, -6, -7, -7, -43, -39, -43, -24, -46, 65, 77, 55, -33, -33, -33, -33, -17 };
int dy[40] = { 0, 0, -2, -1, 0, -2, -1, 0, 0, 0, 0, 0, 1, 0, -1, 0, -1, -2, -3, -1, -1, -4, -1, -4, 0, -1, -1, -1, -4, -5, -3, -9, -2, -2, -1, -1, -1, -1, -1, -9 };

char backgroundImage[14][15] = { "Gleaner\\1.bmp", "Gleaner\\2.bmp", "Gleaner\\3.bmp", "Gleaner\\4.bmp", "Gleaner\\5.bmp", "Gleaner\\6.bmp", "Gleaner\\7.bmp", "Gleaner\\8.bmp", "Gleaner\\9.bmp", "Gleaner\\10.bmp", "Gleaner\\11.bmp", "Gleaner\\12.bmp", "Gleaner\\13.bmp", "Gleaner\\14.bmp" };
//:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::Idraw Here::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::://
char coin[10][18] = { "Gleaner\\coin1.bmp","Gleaner\\coin2.bmp","Gleaner\\coin3.bmp","Gleaner\\coin4.bmp","Gleaner\\coin5.bmp","Gleaner\\coin6.bmp" };
int coinCordinateX=150;
int coinCordinateY =40;
int coinIndex = 0;
struct background
{
	int x;
	int y;
};
background imgpos[14],coinCordinate[10];
//character
boolean shoot = false;
int shootCount;

//point value
int point = 0;
int newHighScore = 0;

char str[1000];
char  str2[1000] = "Minhajur Rahman Mahi";
int indexNumber = 0;

//timer var
char pinku[5][15] = { "char\\1.bmp", "char\\2.bmp", "char\\3.bmp", "char\\4.bmp" ,"char\\5.bmp" };
char pinkuJ[2][20] = { "char\\Jum1.bmp","char\\jump2.bmp" };
char pinkuShoot[15] = { "char\\Shoot.bmp" };
char pinkuH[15] = { "char\\Hit.bmp" };
char pinkuS[15] = { "char\\0.bmp" };
int pinkuCorX = 0;
int pinkuCorY = 80;
int pinkIndex = 0;
int yatoIndex = 0;
bool jump = false;
bool jumpUp = false;
//bool jumpDown = false;
int  pinkuCorJ = 0;

int jCondCheck = 0;
int gConCheck = 0;

int pinkuShootIndex = 0;
//shooting fact
boolean pinkuShootbool = false;
boolean pinkuHitbool = false;

bool standP = true;
int standCo = 0;
int p = 200;
int q = 300;

struct buttonCor
{
	int x;
	int y;
}bCor[3];

//gun section 
int bullet_x[50];
int bullet_y[50];
boolean showBullet[50];
int bulletIndex = 0;
int bulletLoop = 50;
int bulletMiniRasenganIndex = 0;
char bulletMiniRasengan[5][20] = { "gun\\bull1.bmp","gun\\bullet1.bmp", "gun\\bullet2.bmp", "gun\\bullet3.bmp", "gun\\bullet4.bmp" };
int bulletMotionSpeed = 0;
int bulletSpeed = 10;
int qeta[50];
//shooting cor

int n_x = 30, n_y = 30;

void bulletChangeMotion();


char enemyOne[8][15] = { "enem\\enum1.bmp", "enem\\enum2.bmp", "enem\\enum3.bmp", "enem\\enum4.bmp", "enem\\enum5.bmp", "enem\\enum6.bmp", "enem\\enum7.bmp", "enem\\enum8.bmp" };

struct enPro
{
	int enemyX;
	int enemyY;
	int enemyIndex;
	bool enemyShow;

};
enPro enemy[ENEMYNUMBER];
//Menu
char button[10][15] = { "menu\\start.bmp", "menu\\score.bmp", "menu\\ins.bmp" };
char button2[10][15] = { "menu\\start.bmp", "menu\\score.bmp", "menu\\ins.bmp" };
char homemenu[15] = { "menu\\menu.bmp" };
char ins[15] = { "menu\\int.bmp" };
char highscore[20] = { "menu\\highscore.bmp" };
int w = 930;
int h = 600;
int mid = h / 2;
int st = 0;
typedef struct Player player;
struct Player{
	char name[200];
	int sc;
};
const int N = 5;
player info[N];
int score;
char my_str[200];
int mode = 0;
int len = 0;
char name_str[200];
char saved_name[200];
int game_end = 0;
char SS[1000];

void swap(player* xp, player* yp)
{
	player temp;
	strcpy_s(temp.name, 100, xp->name);
	temp.sc = xp->sc;
	strcpy_s(xp->name, 100, yp->name);
	xp->sc = yp->sc;
	strcpy_s(yp->name, 100, temp.name);
	yp->sc = temp.sc;
}


void selectionSort()
{
	int i, j, max_idx;
	for (i = 0; i < N - 1; i++)
	{
		max_idx = i;
		for (j = i + 1; j < N; j++)
		if (info[j].sc > info[max_idx].sc)
			max_idx = j;
		swap(&info[i], &info[max_idx]);
	}
}


void update()
{
	FILE* fp = fopen("highscore.txt", "r");
	if (!fp){
		printf("Error opening file\n");
		exit(0);
	}
	int i = 0;
	for (i = 0; i<N; i++) fscanf(fp, "%d %[^\n]%*c", &info[i].sc, info[i].name);
	selectionSort();
	//for(i=0;i<N;i++) printf("%d %s\n",info[i].sc,info[i].name);
	int min_score = info[N - 1].sc;
	fclose(fp);
	FILE* fw = fopen("highscore.txt", "w");
	if (!fw){
		printf("Error opening file\n");
		exit(0);
	}
	score = 120;//remember to comment it out
	if (score >= min_score){
		strcpy(info[N - 1].name, saved_name);
		info[N - 1].sc = score;
	}
	selectionSort();
	for (i = 0; i<N; i++) fprintf(fw, "%d %s\n", info[i].sc, info[i].name);
	fclose(fw);
	//    game_end=0;
	//    st=4;
	//    show_2=1;
	//    show_3=0;
}


void show_highscore()
{
	FILE* fp = fopen("highscore.txt", "r");
	if (!fp){
		printf("Error opening file\n");
		exit(0);
	}
	for (int i = 0; i<N; i++){
		fscanf(fp, "%d %[^\n]%*c", &info[i].sc, info[i].name);
		char temp1[200], temp2[200], space[] = "  ";
		strcpy(temp1, info[i].name);
		_itoa(info[i].sc, temp2, 10);
		strcat(temp1, space);
		strcat(temp1, temp2);
		iText(w / 2 - 200, mid*1.5 - (i + 1) * 30, temp1, GLUT_BITMAP_TIMES_ROMAN_24);
	}
	fclose(fp);
}



int gamestate = -1;
struct ButtonCordinate
{
	int x;
	int y;
};
ButtonCordinate bCordinate[3];
bool collision(int px, int py, int pw, int ph, int ex, int ey, int ew, int eh)
{
	if (px + pw>ex && px<ex + ew && py + ph>ey && py<ey + eh)

		return true;
	else

		return false;

}

void pinkuMove()
{
	/*if (shoot == true)
	{

	iShowBMP2(pinkuCorX, pinkuCorY, pinkuS, NULL);
	if (shootCount >= 20)
	shoot = false;

	}*/

	if (jump)
	{
		if (jumpUp)
		{
			iShowBMP2(pinkuCorX + 90, pinkuCorY + pinkuCorJ + 150, pinkuJ[0], NULL);
		}
		else
		{
			iShowBMP2(pinkuCorX + 90, pinkuCorY + pinkuCorJ + 150, pinkuJ[1], NULL);
		}
	}
	else
	{
		if (!standP)
		{
			iShowBMP2(pinkuCorX + 80, pinkuCorY, pinku[pinkIndex], NULL);//running
			standCo++;
			if (standCo >= 800)
			{
				standCo = 0;
				pinkIndex = 0;
				standP = true;
			}
			//gun loop
			for (int i = 0; i < bulletLoop; i++)
			{
				if (showBullet[i]){
					iShowBMP2(bullet_x[i], bullet_y[i]+40, bulletMiniRasengan[bulletMiniRasenganIndex], 0);
				}
			}
		}
		else
		{
			iShowBMP2(pinkuCorX, pinkuCorY, pinkuS, NULL);//stand still;
		}

	}


	//shootCount++;
	for (int i = 0; i < ENEMYNUMBER; i++) {
		if (enemy[i].enemyShow) {
			if (collision(pinkuCorX, pinkuCorY, 100, 200, enemy[i].enemyX, enemy[i].enemyY, 70, 200)) {
				printf("hit\n");
			}
		}
	}

	for (int i = 0; i < 10; i++) {
		if (collision(pinkuCorX, pinkuCorY, 100, 200, coinCordinate[i].x, coinCordinate[i].y, 100, 100)) {
			printf("hit3\n");
		}
	}

}

void enemyMovement()
{
	for (int i = 0; i < ENEMYNUMBER; i++)
	{
		if (enemy[i].enemyShow)
		{
			iShowBMP2(enemy[i].enemyX, enemy[i].enemyY, enemyOne[enemy[i].enemyIndex], NULL);
		}
	}


}





void iDraw()
{
	iClear();
	if (gamestate == -1){
		iShowBMP(0, 0, homemenu);
		for (int i = 0; i < 3; i++)
		{
			iShowBMP2(bCordinate[i].x, bCordinate[i].y, button[i], 0);
		}
	}
	else if (gamestate == 0){
		for (int i = 0; i < 14; i++)
		{

			iShowBMP(imgpos[i].x, 0, backgroundImage[i]);

		}

		for (int i = 0, j = 0; i < 10, j < 3; i++, j++)
		{
			iShowBMP2(coinCordinate[i].x, coinCordinate[i].y, coin[coinIndex], 0);
			iShowBMP2(coinCordinate[i].x + 200, coinCordinate[j].y + 180, coin[coinIndex], 0);
		}

		// New gun 

		for (int i = 0; i < bulletLoop; i++)
		{
			if (showBullet[i]){
				iShowBMP2(bullet_x[i], bullet_y[i] + 150, bulletMiniRasengan[bulletMiniRasenganIndex], 0);
			}
		}

		pinkuMove();
		enemyMovement();

		iSetColor(0, 0, 0);
		iText(740, 550, "SCORE : ", GLUT_BITMAP_HELVETICA_18);
		iText(740, 520, "HEALTH :  ", GLUT_BITMAP_HELVETICA_18);

	}
	else if (gamestate == 1){
		iShowBMP(0, 0, highscore);
		iText(w / 2, mid*1.5, "HALL OF FAME:", GLUT_BITMAP_TIMES_ROMAN_24);
		show_highscore();

	}
	else if (gamestate == 2){
		iShowBMP(0, 0, ins);
		

	}
	else
	{

	}
	
}


//collision
void Collision()
{

}

//score


/*function iMouseMove() is called when the user presses and drags the mouse.
(mx, my) is the position where the mouse pointer is.
*/


void iMouseMove(int mx, int my)
{
	
}
//*******************************************************************ipassiveMouse***********************************************************************//
void iPassiveMouseMove(int mx, int my)
{
	
}

void iMouse(int button, int state, int mx, int my)
{


	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		for (int i = 0; i < 3; i++)
		{
			if (mx >= bCordinate[i].x && mx <= bCordinate[i].x + 260 && my >= bCordinate[i].y && my <= bCordinate[i].y + 90)
			{
				gamestate = i;
			}
		}

	}



if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
{

}
}

/*
function iKeyboard() is called whenever the user hits a key in keyboard.
key- holds the ASCII value of the key pressed.
*/



void iKeyboard(unsigned char key)
{
	
		if (key == '\r')
		{

		}
		else if (key == ' ')
		{
			if (!jump)
			{
				jump = true;
				jumpUp = true;
			}
		}


		if (key == '1' || key == '2')
		{
			shoot = true;
			if (key == '1')
				//iShowBMP2(pinkuCorX, pinkuCorY, pinkuShoot[], NULL);

				qeta[bulletIndex] = 0;

			if (key == '2')
				qeta[bulletIndex] = 45;


			//pinkuShootBool = true;
			if (!jump){

				bullet_x[bulletIndex] = n_x + 70;
				bullet_y[bulletIndex] = n_y + 5;
				showBullet[bulletIndex] = true;
				bulletIndex++;
				if (bulletIndex >= 50)
				{
					bulletIndex = 0;
				}

			}
			else if (jump){

				bullet_x[bulletIndex] = n_x + 90;
				bullet_y[bulletIndex] = n_y + 150;
				showBullet[bulletIndex] = true;
				bulletIndex++;

				if (bulletIndex >= 50)
				{
					bulletIndex = 0;
				}

			}

		}
		
		}

	
	


/*
function iSpecialKeyboard() is called whenver user hits special keys like-
function keys, home, end, pg up, pg down, arraows etc. you have to use
appropriate constants to detect them. A list is:
GLUT_KEY_F1, GLUT_KEY_F2, GLUT_KEY_F3, GLUT_KEY_F4, GLUT_KEY_F5, GLUT_KEY_F6,
GLUT_KEY_F7, GLUT_KEY_F8, GLUT_KEY_F9, GLUT_KEY_F10, GLUT_KEY_F11, GLUT_KEY_F12,
GLUT_KEY_LEFT, GLUT_KEY_UP, GLUT_KEY_RIGHT, GLUT_KEY_DOWN, GLUT_KEY_PAGE UP,
GLUT_KEY_PAGE DOWN, GLUT_KEY_HOME, GLUT_KEY_END, GLUT_KEY_INSERT
*/
void iSpecialKeyboard(unsigned char key)
{

	
	if (key == GLUT_KEY_RIGHT)
	{
		pinkuCorX = 0;
		pinkIndex++;
		if (n_x <= 50)
		{
			n_x += 20;
		}
		if (pinkIndex >= 5)
			pinkIndex = 0;
		standP = false;


	}
	if (key == GLUT_KEY_LEFT)
	{
		pinkuCorX = 0;
		pinkIndex--;
		if (pinkIndex <0)
			pinkIndex = 4;
		standP = false;
	}

	if (key == GLUT_KEY_HOME)
	{

	}

	
}
void setAll()
{
	int i, j;
	for (i = 0, j = 0; i < 14; i++)
	{
		imgpos[i].x = j;
		j += 70;
	}

	
}
void coinSet()
{
	int i, j;
	for (i = 0, j = 150; i < 10; i++)
	{
		coinCordinate[i].y = 100;
		coinCordinate[i].x = j;
		j += 100;

	}

}

void change()
{
	
		for (int i = 0; i < 14; i++)
		{
			imgpos[i].x -= 70;

		}

		for (int i = 0; i < 14; i++)
		{

			if (imgpos[i].x < 0)
			{
				imgpos[i].x = 910;

			}


		}
	}
void charchange()
{
	if (jump)
	{
		if (jumpUp)
		{
			pinkuCorJ += 5;

			if (pinkuCorJ >= JUMPLIMIT)
			{
				jumpUp = false;
			}

		}

		else
		{
			pinkuCorJ -= 5;
			if (pinkuCorJ < 0)
			{
				jump = false;
				pinkuCorJ = 0;
			}
		}
	}
}

void charchange2()
{
	for (int i = 0; i < ENEMYNUMBER; i++)
	{
		enemy[i].enemyX -= 10;
		if (enemy[i].enemyX <= 0)
		{
			enemy[i].enemyX = screenWidth + rand() % 300;
		}
		enemy[i].enemyIndex++;
		if (enemy[i].enemyIndex++ >= 3)
		{
			enemy[i].enemyIndex = 0;
		}
	}
}
void coinchange()
{
	
	coinIndex++;
	if (coinIndex >= 6)
	{
		coinIndex = 0;
	}
	for (int i = 0; i <10; i++)
	{
		coinCordinate[i].x -= 10;
	}
	
	for (int i = 0; i < 10; i++)
	{

		if (coinCordinate[i].x < 0)
		{
			coinCordinate[i].x = 1000;
			
			
		}
	}
}

	
void  bulletChangeMotion()
{
	for (int i = 0; i < bulletLoop; i++)
	{
		if (showBullet[i])
		{
			bullet_x[i] += bulletSpeed*cos(qeta[i] * PI / 180);
			bullet_y[i] += bulletSpeed*sin(qeta[i] * PI / 180);
			for (int j = 0; j < bulletLoop; j++) {
				if (enemy[j].enemyShow) {
					if (collision(bullet_x[i], bullet_y[i], 100, 10, enemy[i].enemyX, enemy[i].enemyY, 70, 200)) {
						printf("hitw2\n");
					}
				}
			}

		}
	}
}

void enemySetVariable()
{
	for (int i = 0; i < ENEMYNUMBER; i++)
	{
		enemy[i].enemyX = screenWidth + rand() % 900;
		enemy[i].enemyY = 85;
		enemy[i].enemyIndex = rand() % 4;
		enemy[i].enemyShow = true;
	}

}
void change5()
{

}

int main()
{
	int sum = 150;
	for (int i = 2; i >= 0; i--)
	{
		bCordinate[i].x = 400;
		bCordinate[i].y = sum;
		sum += 80;

	}
	iSetTimer(1000, change);
	enemySetVariable();
	
	setAll();
	coinSet();
	
	iSetTimer(150, change);
	iSetTimer(100, coinchange);
	
	
	iSetTimer(10, charchange);
	iSetTimer(200, charchange2);
	iSetTimer(30, bulletChangeMotion);
	
	iInitialize(screenWidth, screenHeight, "Project Title");
	///updated see the documentations
	iStart();
	return 0;
}