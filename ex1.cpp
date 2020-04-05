#include <Bangtal.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#pragma comment(lib, "Bangtal.lib")

/*
piece배열에 순서대로 1~16까지의 퍼즐조각 저장
num배열에 무작위로 중복없이 0~15의 수 저장
piece와 num배열의 [i]값이 같은 것끼리 매칭시켜 위치 지정
(이차원 배열의 사용이 필요없이 (y = num[i]/4, x = num[i]%4)의 좌표로 위치를 지정한다)
(여기서 num[i]의 i를 0~15중 무작위로 선정하고 그 num[i]값에 해당하는 퍼즐조각을 invisible로 만든다
(invisible된 퍼즐 조각은 모든 퍼즐 위치가 올바르면 메시지와 함께 보이도록 한다)
어떤 퍼즐 조각과 invisible된 퍼즐조각으로만 드래그로 위치 교환을 가능하게 한다
매 이동마다 모든 퍼즐 조각의 위치가 올바른지 판단하도록 한다
*/

/*
(250,432) (394,432) (538,432) (682,432)
(250,288) (394,288) (538,288) (682,288)
(250,144) (394,144) (538,144) (682,144)
(250,0) (394,0) (538,0) (682,0)
*/
SceneID scene1, scene2;
ObjectID piece[16], startbutton, skip;
int num[16], key;
char arr[16][15], t[40];
clock_t start, finish;
double duration = 0.0;


void ranNum() {

	int i, x, y, temp;

	srand(time(NULL));

	for (i = 0; i < 16; i++) num[i] = i;

	for (i = 0; i < 50; i++) {
		x = rand() % 16;
		y = rand() % 16;

		if (x != y) {
			temp = num[x];
			num[x] = num[y];
			num[y] = temp;
		}
	}
}

void createPuzzle() {

	ranNum();
	for (int i = 0; i < 16; i++) {
		locateObject(piece[i], scene2, 250 + ((num[i] % 4) * 144), 432 - ((num[i] / 4) * 144));
		showObject(piece[i]);
	}
	srand(time(NULL));
	key = rand() % 16;
	hideObject(piece[key]);
}

int upFinding() {
	for (int i = 0; i < 16; i++) {
		if (num[i] == num[key] - 4) {
			return i;
		}
	}
}

int downFinding() {
	for (int i = 0; i < 16; i++) {
		if (num[i] == num[key] + 4) {
			return i;
		}
	}
}

int rightFinding() {
	for (int i = 0; i < 16; i++) {
		if (num[i] == num[key] + 1) {
			return i;
		}
	}
}

int leftFinding() {
	for (int i = 0; i < 16; i++) {
		if (num[i] == num[key] - 1) {
			return i;
		}
	}
}

void success() {
	finish = clock();
	duration = (double)(finish - start) / CLOCKS_PER_SEC;
	sprintf_s(t, "축하합니다! (걸린시간: %d초)", (int)duration);
	showObject(startbutton);
	showObject(piece[key]);
	showMessage(t);
	locateObject(startbutton, scene2, 500, 70);
	setObjectImage(startbutton, "images\\restart.png");
}

void judge() {
	for (int i = 0; i < 16; i++) {
		if (num[i] != i) return;
	}
	success();
}

void mouseCallback(ObjectID object, int x, int y, MouseAction action) {

	if (object == startbutton) {
		enterScene(scene2);
		createPuzzle();
		hideObject(startbutton);
		start = clock();
	}
	if (object == piece[upFinding()]) {
		int k = upFinding();
		if (action == MOUSE_DRAG_DOWN) {
			int temp;
			temp = num[key];
			num[key] = num[k];
			num[k] = temp;
			locateObject(piece[key], scene2, 250 + ((num[key] % 4) * 144), 432 - ((num[key] / 4) * 144));
			locateObject(piece[k], scene2, 250 + ((num[k] % 4) * 144), 432 - ((num[k] / 4) * 144));
			judge();
		}
	}
	if (object == piece[downFinding()]) {
		int k = downFinding();
		if (action == MOUSE_DRAG_UP) {
			int temp;
			temp = num[key];
			num[key] = num[k];
			num[k] = temp;
			locateObject(piece[key], scene2, 250 + ((num[key] % 4) * 144), 432 - ((num[key] / 4) * 144));
			locateObject(piece[k], scene2, 250 + ((num[k] % 4) * 144), 432 - ((num[k] / 4) * 144));
			judge();
		}
	}
	if (object == piece[rightFinding()]) {
		int k = rightFinding();
		if (action == MOUSE_DRAG_LEFT) {
			int temp;
			temp = num[key];
			num[key] = num[k];
			num[k] = temp;
			locateObject(piece[key], scene2, 250 + ((num[key] % 4) * 144), 432 - ((num[key] / 4) * 144));
			locateObject(piece[k], scene2, 250 + ((num[k] % 4) * 144), 432 - ((num[k] / 4) * 144));
			judge();
		}
	}
	if (object == piece[leftFinding()]) {
		int k = leftFinding();
		if (action == MOUSE_DRAG_RIGHT) {
			int temp;
			temp = num[key];
			num[key] = num[k];
			num[k] = temp;
			locateObject(piece[key], scene2, 250 + ((num[key] % 4) * 144), 432 - ((num[key] / 4) * 144));
			locateObject(piece[k], scene2, 250 + ((num[k] % 4) * 144), 432 - ((num[k] / 4) * 144));
			judge();
		}
	}
	/* 스킵 버튼 (퍼즐이 너무 어려울때...)
	if (object == skip) {
		success();
	}
	*/
}

int main() {

	setMouseCallback(mouseCallback);

	for (int i = 0; i < 16; i++) {
		sprintf_s(arr[i], "images\\%d.png", i+1);
		piece[i] = createObject("퍼즐", arr[i]);
	}

	scene1 = createScene("원본", "images\\original.png");
	scene2 = createScene("퀴즈", "images\\base.png");

	/*	스킵 버튼 (퍼즐이 너무 어려울때...)
	skip = createObject("스킵", "images\\start.png");
	locateObject(skip, scene2, 100, 70);
	showObject(skip);
	*/

	startbutton = createObject("시작", "images\\start.png");
	locateObject(startbutton, scene1, 500, 70);
	showObject(startbutton);

	showMessage("퍼즐을 완성하세요!");

	startGame(scene1);

	}