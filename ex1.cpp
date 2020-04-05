#include <Bangtal.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#pragma comment(lib, "Bangtal.lib")

/*
piece�迭�� ������� 1~16������ �������� ����
num�迭�� �������� �ߺ����� 0~15�� �� ����
piece�� num�迭�� [i]���� ���� �ͳ��� ��Ī���� ��ġ ����
(������ �迭�� ����� �ʿ���� (y = num[i]/4, x = num[i]%4)�� ��ǥ�� ��ġ�� �����Ѵ�)
(���⼭ num[i]�� i�� 0~15�� �������� �����ϰ� �� num[i]���� �ش��ϴ� ���������� invisible�� �����
(invisible�� ���� ������ ��� ���� ��ġ�� �ùٸ��� �޽����� �Բ� ���̵��� �Ѵ�)
� ���� ������ invisible�� �����������θ� �巡�׷� ��ġ ��ȯ�� �����ϰ� �Ѵ�
�� �̵����� ��� ���� ������ ��ġ�� �ùٸ��� �Ǵ��ϵ��� �Ѵ�
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
	sprintf_s(t, "�����մϴ�! (�ɸ��ð�: %d��)", (int)duration);
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
	/* ��ŵ ��ư (������ �ʹ� ����ﶧ...)
	if (object == skip) {
		success();
	}
	*/
}

int main() {

	setMouseCallback(mouseCallback);

	for (int i = 0; i < 16; i++) {
		sprintf_s(arr[i], "images\\%d.png", i+1);
		piece[i] = createObject("����", arr[i]);
	}

	scene1 = createScene("����", "images\\original.png");
	scene2 = createScene("����", "images\\base.png");

	/*	��ŵ ��ư (������ �ʹ� ����ﶧ...)
	skip = createObject("��ŵ", "images\\start.png");
	locateObject(skip, scene2, 100, 70);
	showObject(skip);
	*/

	startbutton = createObject("����", "images\\start.png");
	locateObject(startbutton, scene1, 500, 70);
	showObject(startbutton);

	showMessage("������ �ϼ��ϼ���!");

	startGame(scene1);

	}