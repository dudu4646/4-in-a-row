#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include<fcntl.h>
#include<io.h>
#define blue(ch) { SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE);wprintf(L"%c",ch);SetConsoleTextAttribute(hConsole, saved_attributes);}
#define red(ch) {SetConsoleTextAttribute(hConsole, FOREGROUND_RED);wprintf(L"%c",ch);SetConsoleTextAttribute(hConsole, saved_attributes);}
#define yellow(ch) {SetConsoleTextAttribute(hConsole, 0x6);wprintf(L"%c",ch);SetConsoleTextAttribute(hConsole, saved_attributes);}
#define START HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);CONSOLE_SCREEN_BUFFER_INFO consoleInfo;WORD saved_attributes;GetConsoleScreenBufferInfo(hConsole, &consoleInfo);saved_attributes = consoleInfo.wAttributes;
#define left 75
#define right 77
#define Enter 13

//global var
char board[13][15], sign, ch;
int p_j, flg, turn, win;

//print board
void pb() {
	int i, j;

	START

		for (i = 0; i < 13; i++)
		{
			for (j = 0; j < 15; j++)
				switch (board[i][j])
				{
				case '|':
					blue(board[i][j])
						break;
				case '-':
					blue(board[i][j])
						break;
				default:
					wprintf(L" ");
					break;
				case 'X':
					yellow(board[i][j]);
					break;
				case 'O':
					red(board[i][j]);
					break;
				}

			wprintf(L"\n");
		}
}

void second_print() {
	system("CLS");
	wprintf(L"\n\n");
	pb();
	Sleep(50);
}

void check_j() {
	int i;
	for (i = 11; i >= 3; i -= 2) {
		if (board[i][p_j * 2 - 1] == ' ') break;
	}
	flg = (board[i][p_j * 2 - 1] == ' ') ? 1 : 0;
}

void enter_new() {
	int i;
	for (i = 1; i <= 11 && board[i][p_j * 2 - 1] == ' '; i += 2) {
		board[i][p_j * 2 - 1] = sign;
		if (i > 1)board[i - 2][p_j * 2 - 1] = ' ';
		second_print();
	}
}

int use_arrow() {
	int j, temp;
	char dir;

	for (j = 0; j != p_j * 2 - 1; j++) wprintf(L" ");
	wprintf(L"\x2191\n");
	//	getch();
	dir = getch();
	if ((dir == 0) || (dir == -32))
	{
		dir = getch();
		switch (dir) {
		case right:
			if (p_j < 7) p_j++;
			break;
		case left:
			if (p_j > 1)p_j--;
			break;

		}
	}
	if ((dir == '\r') || (dir == '\n')) check_j();
	if (!flg) return 0;
	flg = 0;
	enter_new();
	return 1;
}

void play() {
	int j;
	sign = (turn % 2) ? 'X' : 'O';
	system("CLS");
	wprintf(L"Player %d, choose where to put %c:\n", turn % 2 + 1, sign);
	for (j = 0; j != p_j * 2 - 1; j++) wprintf(L" ");
	wprintf(L"\x2193\n");
	pb();
	if (use_arrow() == 0)play();
}

int UP(int i, int j, int num) {
	if (board[i][j] == sign)
		if (num == 3) return 1;
		else UP(i - 2, j, num + 1);
	else return 0;

}
int DOWN(int i, int j, int num) {
	if (board[i][j] == sign)
		if (num == 3) return 1;
		else DOWN(i + 2, j, num + 1);
	else return 0;
}
int RIGHT(int i, int j, int num) {
	if (board[i][j] == sign)
		if (num == 3) return 1;
		else RIGHT(i, j + 2, num + 1);
	else return 0;
}
int LEFT(int i, int j, int num) {
	if (board[i][j] == sign)
		if (num == 3) return 1;
		else LEFT(i, j - 2, num + 1);
	else return 0;
}
int UP_LEFT(int i, int j, int num) {
	if (board[i][j] == sign)
		if (num == 3) return 1;
		else UP_LEFT(i - 2, j - 2, num + 1);
	else return 0;
}
int UP_RIGHT(int i, int j, int num) {
	if (board[i][j] == sign)
		if (num == 3) return 1;
		else UP_RIGHT(i - 2, j + 2, num + 1);
	else return 0;
}
int DOWN_LEFT(int i, int j, int num) {
	if (board[i][j] == sign)
		if (num == 3) return 1;
		else DOWN_LEFT(i + 2, j - 2, num + 1);
	else return 0;
}
int DOWN_RIGHT(int i, int j, int num) {
	if (board[i][j] == sign)
		if (num == 3) return 1;
		else DOWN_RIGHT(i + 2, j + 2, num + 1);
	else return 0;
}

int check_win() {
	int i, j;
	for (i = 1; i < 12; i += 2) {
		for (j = 1; j < 14; j += 2)
			if (board[i][j] == sign) {
				if (i < 7) {
					if (DOWN(i + 2, j, 1)) return 1;
					if ((j > 5) && (DOWN_LEFT(i + 2, j - 2, 1))) return 1;
					if ((j < 9) && (DOWN_RIGHT(i + 2, j + 2, 1))) return 1;
				}
				if (i > 5) {
					if (UP(i - 2, j, 1)) return 1;
					if ((j > 5) && (UP_LEFT(i - 2, j - 2, 1))) return 1;
					if ((j < 9) && (UP_RIGHT(i - 2, j + 2, 1))) return 1;
				}
				if ((j > 5) && (LEFT(i, j - 2, 1))) return 1;
				if ((j < 9) && (RIGHT(i, j + 2, 1)))return 1;
			}
	}
	return 0;
}

void print_win() {
	int i, j;
	START
		system("cls");
	wprintf(L"\n-= The winner is player %d - ", turn % 2 + 1);
	if (turn % 2) yellow(sign)
	else red(sign)
		wprintf(L" =-\n");

	for (i = 0; i < 13; i++)
	{
		for (j = 0; j < 15; j++)
			if ((board[i][j] == '|') || (board[i][j] == '-'))
				blue(board[i][j])
			else	if (board[i][j] == sign)
				if (turn % 2) yellow(sign)
				else red(sign)
			else wprintf(L" ");

		wprintf(L"\n");
	}
	wprintf(L"\nTo play again press Y or anything else to Quit: ");
	ch = getche();
	if (ch == 'y')ch = 'Y';
}

void print_tie() {
	win = 1;
	system("CLS");
	wprintf(L"-= Its a tie!!!! =-\n\n");
	pb();
	wprintf(L"\nTo play again press Y or anything else to Quit: ");
	ch = getche();
	if (ch == 'y')ch = 'Y';
}

void main() {
	_setmode(_fileno(stdout), _O_U16TEXT);
	START
		ch = 'Y';
	int i, j;

	while (ch == 'Y') {
		p_j = 1, flg = 0, turn = 0, win = 0;
		//reset the board
		for (i = 0; i < 13; i++)
			for (j = 0; j < 15; j++)
				if ((i % 2 == 0) && (j % 2 == 1)) board[i][j] = '-';
				else if ((i % 2 == 1) && (j % 2 == 0)) board[i][j] = '|';
				else board[i][j] = ' ';

				while (!win) {
					_flushall();
					play();
					if (win = check_win())
						print_win();
					else if (turn < 41)
						turn++;
					else
						print_tie();
				}
	}
}



