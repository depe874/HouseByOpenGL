#include <gl/glut.h>
#include <stdlib.h>
#define _USE_MATH_DEFINES // for C++
#include <math.h>

//---------各種定数---------//
int w = 1120;
int h = 630;//ウィンドウサイズ16:9

double rotate_x = 0.0;
double rotate_y = 0.0;
double rotate_z = 0.0;

double boxa[8][3];//直方体の頂点の座標を格納する
double boxb[8][3];

GLfloat sca[3] = { 1.5, 1.5, 1.5 };//拡大縮小用
GLfloat tra[3] = { 0, 0, 0 };//視点移動用

//---------colors---------//
#define skyblue 0.5, 0.8, 1.0
#define grassgreen 0.0, 0.4, 0.2
#define gray 0.5, 0.5, 0.5
#define white 1.0, 1.0, 1.0
#define brown 0.4, 0.2, 0.2
#define waterblue 0.0, 0.6, 0.8
#define glass 0.8, 0.8, 1.0
#define darkbrown 0.2, 0.0, 0.0
#define gold 0.8, 0.6, 0.2
#define darkgray 0.6, 0.6, 0.6
#define green 0.4, 0.8, 0.4
#define darkblue 0.0, 0.2, 0.4


//--------- 各種コールバック関数-------//
void ConstractBox(double x, double y, double z, double x1, double y1, double z1) {
	//直方体の生成
	//点0
	boxa[0][0] = x;
	boxa[0][1] = y;
	boxa[0][2] = z;
	//点1
	boxa[1][0] = x;
	boxa[1][1] = y;
	boxa[1][2] = z + z1;
	//点2
	boxa[2][0] = x + x1;
	boxa[2][1] = y;
	boxa[2][2] = z + z1;
	//点3
	boxa[3][0] = x + x1;
	boxa[3][1] = y;
	boxa[3][2] = z;
	//残りの4つの頂点の確定
	for (int i = 0; i < 4; i++){
		for (int j = 0; j < 3; j++) {
			if (j == 1)
				boxa[i + 4][j] = boxa[i][j] + y1;
			else
				boxa[i + 4][j] = boxa[i][j];
		}
	}
}

void ConstractBox2(double x, double y, double z, double x1, double y1, double z1) {
	//点0
	boxb[0][0] = x;
	boxb[0][1] = y;
	boxb[0][2] = z;
	//点1
	boxb[1][0] = x;
	boxb[1][1] = y;
	boxb[1][2] = z + z1;
	//点4
	boxb[4][0] = x;
	boxb[4][1] = y + y1;
	boxb[4][2] = z;
	//点5
	boxb[5][0] = x;
	boxb[5][1] = y + y1;
	boxb[5][2] = z + z1 / 2;
	for (int i = 0; i < 3; i++) {
		if (i == 0) {
			boxb[3][i] = boxb[0][i] + x1;
			boxb[2][i] = boxb[1][i] + x1;
			boxb[6][i] = boxb[4][i] + x1;
			boxb[7][i] = boxb[5][i] + x1;
		}
		else {
			boxb[3][i] = boxb[0][i];
			boxb[2][i] = boxb[1][i];
			boxb[6][i] = boxb[4][i];
			boxb[7][i] = boxb[5][i];
		}
	}
}

void build() {
	glBegin(GL_POLYGON);
	//左
	glNormal3f(-1.0, 0.0, 0.0);
	glVertex3f(boxa[1][0], boxa[1][1], boxa[1][2]);
	glVertex3f(boxa[0][0], boxa[0][1], boxa[0][2]);
	glVertex3f(boxa[4][0], boxa[4][1], boxa[4][2]);
	glVertex3f(boxa[5][0], boxa[5][1], boxa[5][2]);

	//右
	glNormal3f(1.0, 0.0, 0.0);
	glVertex3f(boxa[7][0], boxa[7][1], boxa[7][2]);
	glVertex3f(boxa[6][0], boxa[6][1], boxa[6][2]);
	glVertex3f(boxa[2][0], boxa[2][1], boxa[2][2]);
	glVertex3f(boxa[3][0], boxa[3][1], boxa[3][2]);

	//前
	glNormal3f(0.0, 0.0, 1.0);
	glVertex3f(boxa[5][0], boxa[5][1], boxa[5][2]);
	glVertex3f(boxa[6][0], boxa[6][1], boxa[6][2]);
	glVertex3f(boxa[2][0], boxa[2][1], boxa[2][2]);
	glVertex3f(boxa[1][0], boxa[1][1], boxa[1][2]);

	//後
	glNormal3f(0.0, 0.0, -1.0);
	glVertex3f(boxa[0][0], boxa[0][1], boxa[0][2]);
	glVertex3f(boxa[3][0], boxa[3][1], boxa[3][2]);
	glVertex3f(boxa[7][0], boxa[7][1], boxa[7][2]);
	glVertex3f(boxa[4][0], boxa[4][1], boxa[4][2]);

	//上
	glNormal3f(0.0, 1.0, 0.0);
	glVertex3f(boxa[4][0], boxa[4][1], boxa[4][2]);
	glVertex3f(boxa[7][0], boxa[7][1], boxa[7][2]);
	glVertex3f(boxa[6][0], boxa[6][1], boxa[6][2]);
	glVertex3f(boxa[5][0], boxa[5][1], boxa[5][2]);

	//下
	glNormal3f(0.0, -1.0, 0.0);
	glVertex3f(boxa[0][0], boxa[0][1], boxa[0][2]);
	glVertex3f(boxa[1][0], boxa[1][1], boxa[1][2]);
	glVertex3f(boxa[2][0], boxa[2][1], boxa[2][2]);
	glVertex3f(boxa[3][0], boxa[3][1], boxa[3][2]);

	glEnd();
}

void build2() {
	glBegin(GL_POLYGON);
	//下
	glNormal3f(0.0, -1.0, 0.0);
	glVertex3f(boxb[0][0], boxb[0][1], boxb[0][2]);
	glVertex3f(boxb[1][0], boxb[1][1], boxb[1][2]);
	glVertex3f(boxb[2][0], boxb[2][1], boxb[2][2]);
	glVertex3f(boxb[3][0], boxb[3][1], boxb[3][2]);
	glEnd();

	glBegin(GL_POLYGON);
	//左
	glNormal3f(-1.0, 0.0, 0.0);
	glVertex3f(boxb[1][0], boxb[1][1], boxb[1][2]);
	glVertex3f(boxb[0][0], boxb[0][1], boxb[0][2]);
	glVertex3f(boxb[4][0], boxb[4][1], boxb[4][2]);
	glVertex3f(boxb[5][0], boxb[5][1], boxb[5][2]);
	glEnd();

	glBegin(GL_POLYGON);
	//右
	glNormal3f(1.0, 0.0, 0.0);
	glVertex3f(boxb[7][0], boxb[7][1], boxb[7][2]);
	glVertex3f(boxb[6][0], boxb[6][1], boxb[6][2]);
	glVertex3f(boxb[3][0], boxb[3][1], boxb[3][2]);
	glVertex3f(boxb[2][0], boxb[2][1], boxb[2][2]);
	glEnd();

	glBegin(GL_POLYGON);
	//前
	glNormal3f(0.0, 0.0, 1.0);
	glVertex3f(boxb[5][0], boxb[5][1], boxb[5][2]);
	glVertex3f(boxb[6][0], boxb[6][1], boxb[6][2]);
	glVertex3f(boxb[2][0], boxb[2][1], boxb[2][2]);
	glVertex3f(boxb[1][0], boxb[1][1], boxb[1][2]);
	glEnd();

	glBegin(GL_POLYGON);
	//後
	glNormal3f(0.0, 0.0, -1.0);
	glVertex3f(boxb[0][0], boxb[0][1], boxb[0][2]);
	glVertex3f(boxb[3][0], boxb[3][1], boxb[3][2]);
	glVertex3f(boxb[7][0], boxb[7][1], boxb[7][2]);
	glVertex3f(boxb[4][0], boxb[4][1], boxb[4][2]);
	glEnd();

	glBegin(GL_POLYGON);
	//上
	glNormal3f(0.0, 1.0, 0.0);
	glVertex3f(boxb[4][0], boxb[4][1], boxb[4][2]);
	glVertex3f(boxb[7][0], boxb[7][1], boxb[7][2]);
	glVertex3f(boxb[6][0], boxb[6][1], boxb[6][2]);
	glVertex3f(boxb[5][0], boxb[5][1], boxb[5][2]);
	glEnd();
}

void DrawATree(double x, double y, double z) {
	glTranslatef(x, y, z);
	glColor3f(green);
	glutSolidSphere(25.0, 20, 20);

	glTranslatef(10, 0, 0);
	glutSolidSphere(25.0, 20, 20);

	glTranslatef(-10, 0, -10);
	glutSolidSphere(25.0, 20, 20);

	glTranslatef(0, 0, 20);
	glutSolidSphere(25.0, 20, 20);

	glTranslatef(0, 10, -20);
	glutSolidSphere(25.0, 20, 20);
	glTranslatef(-x, -y-10, -z+10);
}

void Drawgrass(){//芝生
	glBegin(GL_POLYGON);
	ConstractBox(-300, 0, -200, 1200, 10, 1100);
	glColor3f(grassgreen);
	build();
}

void Drawroad1() {//道路
	glBegin(GL_POLYGON);
	ConstractBox(-300, 10, 600, 1200, 4, 100);
	glColor3f(gray);
	build();
	for (int i = 0; i < 12; i++) {
		//glBegin(GL_POLYGON);
		ConstractBox((GLfloat)i * 100 - 300, 14, (GLfloat)600 + 45, 40, 1, 10);
		glColor3f(white);
		build();
	}
}

void Drawroad2() {//小道
	glBegin(GL_POLYGON);
	glColor3f(darkgray);
	for (int i = 0; i < 5; i++) {
		ConstractBox(230, 10, 250 + (GLfloat)i * 50, 50, 2, 15);
		build();
	}
	for (int i = 0; i < 4; i++) {
		ConstractBox(250, 10, 325 + (GLfloat)i * 50, 50, 2, 15);
		build();
	}
}

void Drawwall1() {//塀
	glBegin(GL_POLYGON);
	ConstractBox(-200, 10, -100, 20, 30, 600);
	glColor3f(white);
	build();
	ConstractBox(-180, 10, -100, 900, 30, 20);
	build();
	ConstractBox(720, 10, -100, 20, 30, 600);
	build();
	ConstractBox(-180, 10, 480, 420, 30, 20);
	build();
	ConstractBox(300, 10, 480, 420, 30, 20);
	build();
	//柱//glBegin(GL_POLYGON);
	ConstractBox(-200, 10, -100, 20, 60, 20);
	build();
	ConstractBox(720, 10, -100, 20, 60, 20);
	build();
	ConstractBox(-200, 10, 480, 20, 60, 20);
	build();
	ConstractBox(220, 10, 480, 20, 60, 20);
	build();
	ConstractBox(300, 10, 480, 20, 60, 20);
	build();
	ConstractBox(720, 10, 480, 20, 60, 20);
	build();
}

void Drawwall2() {//柵
	glBegin(GL_POLYGON);
	glColor3f(brown);
	for (int i = -180 + 20; i < 220; i += 20) {
		ConstractBox(i, 40, 490, 6, 30, 6);
		build();
	}
	for (int i = 300 + 20; i < 720; i += 20) {
		ConstractBox(i, 40, 490, 6, 30, 6);
		build();
	}
	for (int i = -100 + 20; i < 480; i += 20) {
		ConstractBox(-190, 40, i, 6, 30, 6);
		build();
	}
	for (int i = -100 + 20; i < 480; i += 20) {
		ConstractBox(730, 40, i, 6, 30, 6);
		build();
	}
	for (int i = -180 + 20; i < 720; i += 20) {
		ConstractBox(i, 40, -90, 6, 30, 6);
		build();
	}
}

void Drawwall3() {//家の壁
	//裏面の壁//glBegin(GL_POLYGON);
	glColor3f(white);
	ConstractBox(-110, 10, -40, 520, 150, 10);
	build();
	//左壁//glBegin(GL_POLYGON);
	ConstractBox(-110, 10, -40, 10, 40, 320);
	build();
	ConstractBox(-110, 110, -40, 10, 50, 320);
	build();
	ConstractBox(-110, 50, -40, 10, 60, 50);
	build();
	ConstractBox(-110, 50, 100, 10, 60, 40);
	build();
	ConstractBox(-110, 50, 230, 10, 60, 50);
	build();
	//正面の壁//glBegin(GL_POLYGON);
	ConstractBox(-110, 10, 270, 350, 40, 10);
	build();
	ConstractBox(-110, 50, 270, 180, 60, 10);
	build();
	ConstractBox(190, 50, 270, 50, 60, 10);
	build();
	ConstractBox(290, 10, 270, 120, 100, 10);
	build();
	ConstractBox(-110, 110, 270, 520, 50, 10);
	build();
	//右壁//glBegin(GL_POLYGON);
	ConstractBox(400, 110, -40, 10, 50, 320);
	build();
	ConstractBox(400, 10, -40, 10, 100, 120);
	build();
	ConstractBox(400, 10, 220, 10, 100, 50);
	build();
	glColor3f(darkbrown);
	ConstractBox(400, 110, -40, 60, 5, 320);
	build();
	ConstractBox(450, 10, -20, 5, 100, 5);
	build();
	ConstractBox(450, 10, 260, 5, 100, 5);
	build();
}

void Drawpool() {//プール
	glBegin(GL_POLYGON);
	glColor3f(waterblue);
	ConstractBox(520, 10, -30, 150, 8, 300);
	build();
	glColor3f(white);
	ConstractBox(510, 10, -40, 10, 12, 320);
	build();
	glColor3f(white);
	ConstractBox(510, 10, -40, 170, 12, 10);
	build();
	glColor3f(white);
	ConstractBox(510, 10, 270, 170, 12, 10);
	build();
	glColor3f(white);
	ConstractBox(670, 10, -40, 10, 12, 320);
	build();
}

void Drawlight() {//灯
	//材質 (環境光､拡散光､鏡面光､鏡面指数) のパラメータ（パール）
	glColor3f(white);
	glTranslatef(-190, 82, -90);
	glutSolidSphere(12.0, 20, 20);
	glTranslatef(920, 0, 0);
	glutSolidSphere(12.0, 20, 20);
	glTranslatef(0, 0, 580);
	glutSolidSphere(12.0, 20, 20);
	glTranslatef(-420, 0, 0);
	glutSolidSphere(12.0, 20, 20);
	glTranslatef(-80, 0, 0);
	glutSolidSphere(12.0, 20, 20);
	glTranslatef(-420, 0, 0);
	glutSolidSphere(12.0, 20, 20);
	glTranslatef(190, -82, -490);
}

void Drawfloor() {//床
	glBegin(GL_POLYGON);
	glColor3f(brown);
	ConstractBox(-100, 10, -30, 550, 5, 300);
	build();
}

void Drawglass() {//窓
	glBegin(GL_POLYGON);
	glColor4f(glass, 0.35);
	ConstractBox(-110, 50, 10, 10, 60, 90);
	build();
	ConstractBox(-110, 50, 140, 10, 60, 90);
	build();
	ConstractBox(70, 50, 270, 120, 60, 10);
	build();
}

void Drawdoor() {//ドア
	glBegin(GL_POLYGON);
	glColor3f(darkbrown);
	ConstractBox(240, 10, 270, 50, 100, 5);
	build();
	glColor3f(gold);
	ConstractBox(245, 50, 275, 5, 5, 5);
	build();
}

void Drawroof() {//屋根
	glBegin(GL_POLYGON);
	glColor3f(darkblue);
	ConstractBox2(-110, 160, 120, 520, 50, 190);
	build2();
	ConstractBox2(-110, 160, 120, 520, 50, -190);
	build2();
	ConstractBox2(-110, 200, 120, 520, 40, 130);
	build2();
	ConstractBox2(-110, 200, 120, 520, 40, -130);
	build2();
	ConstractBox2(-110, 230, 120, 520, 30, 90);
	build2();
	ConstractBox2(-110, 230, 120, 520, 30, -90);
	build2();
}

void Drawtrees() {//木
	glBegin(GL_POLYGON);
	for (int i = 0; i < 8; i++) {
		glColor3f(brown);
		ConstractBox(-250 + 150 * i, 10, 550, 10, 60, 10);
		build();
		DrawATree(-250 + 150 * i, 70, 550);
	}
	for (int i = 0; i < 8; i++) {
		glColor3f(brown);
		ConstractBox(-250 + 150 * i, 10, 750, 10, 60, 10);
		build();
		DrawATree(-250 + 150 * i, 70, 750);
	}
}

void display(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glRotatef(rotate_x, 1.0, 0.0, 0.0);
	glRotatef(rotate_y, 0.0, 1.0, 0.0);
	glRotatef(rotate_z, 0.0, 0.0, 1.0);
	//glMatrixMode(GL_PROJECTION);
	//glLoadIdentity();
	//glScalef(2,2,2);
	glTranslatef(0, 30, 0);

	glScalef(sca[0], sca[1], sca[2]);
	glTranslatef(tra[0], tra[1], tra[2]);

	Drawgrass();
	Drawroad1();
	Drawroad2();
	Drawwall1();
	Drawwall2();
	Drawwall3();
	Drawlight();
	Drawpool();
	Drawfloor();
	Drawglass();
	Drawdoor();
	Drawroof();
	Drawtrees();
	
	glutSwapBuffers();
}

void keyboard1(unsigned char key, int x, int y) {
	switch (key) {
	case'1':
		for (int i = 0; i < 3; i++)
			sca[i] += 0.1;
		break;
	case'2':
		for (int i = 0; i < 3; i++)
			sca[i] -= 0.1;
		break;
	case'w':
		tra[2] += 10;
		break;
	case's':
		tra[2] -= 10;
		break;
	case'a':
		tra[0] += 10;
		break;
	case'd':
		tra[0] -= 10;
		break;
	}
	glutPostRedisplay();
}

void keyboard2(int key, int x, int y){
	if (key == GLUT_KEY_RIGHT) {
		rotate_y -= 1;
	}
	else if (key == GLUT_KEY_LEFT) {
		rotate_y += 1;
	}
	else if (key == GLUT_KEY_DOWN) {
		rotate_x -= 1;
	}
	else if (key == GLUT_KEY_UP) {
		rotate_x += 1;
	}
	glutPostRedisplay();
}

//--------- 各種設定-----------//

void Init(void){
	GLfloat sunPos[] = { 700.0, 300.0, 100.0, 1.0 };//位置
	GLfloat sunCol[] = { 1.0, 0.8, 0.6, 1.0 };//拡散光
	GLfloat Amb[] = { 0.5, 0.5, 0.5, 1.0 };//環境光

	//光源の設定
	glEnable(GL_LIGHT0);
	glLightfv(GL_LIGHT0, GL_POSITION, sunPos);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, sunCol);

	glEnable(GL_LIGHTING);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, Amb);

	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);//環境光と拡散光を同時に指定

	glEnable(GL_COLOR_MATERIAL);

	glEnable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);

	//視野の設定
	glViewport(0, 0, w, h);
	//glMatrixMode(GL_MODELVIEW);
	//glLoadIdentity();//変換行列の初期化
	glMatrixMode(GL_PROJECTION);
	//glOrtho(-w, w, -h, h, -w, w);
	gluPerspective(30.0, (double)w / h, 1.0, 2000.0);
	gluLookAt(400.0, 70.0, 900.0, //カメラの座標
		400.0, 70.0, 0.0, // 注視点の座標
		0.0, 1.0, 0.0);
	//線の太さ
	glLineWidth(5);
	glClearColor(0.6, 0.8, 1.0, 0.0);
}

int main(int argc, char* argv[]){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(w, h);
	glutCreateWindow("My House");
	glEnable(GL_DEPTH_TEST);

	//コールバック関数登録
	Init();
	glutKeyboardFunc(keyboard1);
	glutSpecialFunc(keyboard2);
	glutDisplayFunc(display);

	glutMainLoop();

	return 0;
}