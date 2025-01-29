#include "Base/Base.h"
#include"Game/Field.h"
#include"Game/AnimData.h"
#include"Game/Map.h"
#include"Game/Player.h"
#include"Game/Game.h"
#include"Game/Enemy.h"
#include"Game/Enemy1.h"
#include"Game/Enemy2.h"
#include"Game/Enemy3.h"
#include"Game/Enemy4.h"
#include"Game/Enemy5.h"
#include"Game/BossEnemy.h"
#include"Game/Item.h"
#include"Game/UI.h"
#include"Game/Menyu.h"
#include"Game/Effect.h"
#include"Game/GameData.h"
#include"Game/TP.h"
#include"Game/Slash.h"
#include"Game/Goal.h"
#include"Title/Title.h"

//--------------------------------------------
//グローバル変数領域
//--------------------------------------------






void MainLoop(void) {
	//--------------------------------------------------------------
	//ゲーム中の動きはここに書く
	//ゲーム中はこの関数_を1秒間に60回呼び出している
	//--------------------------------------------------------------
	Base::CheckKillAll();
	Base::UpdateAll();
	Base::CollisionAll();
	Base::DrawAll();

}
void Init(void)
{

	CFPS::SetFPS(60);
	//フレーム制御初期化
	CFPS::Init();
	//ボタンの設定
	CInput::Init();
	CInput::SetButton(0, CInput::eButton1, 'Z');
	CInput::SetButton(0, CInput::eButton2, 'X');
	CInput::SetButton(0, CInput::eButton3, 'C');
	CInput::SetButton(0, CInput::eButton4, 'V');
	CInput::SetButton(0, CInput::eButton5, VK_SPACE);
	CInput::SetButton(0, CInput::eButton6, 'A');
	CInput::SetButton(0, CInput::eButton10, VK_RETURN);
	CInput::SetButton(0, CInput::eUp, VK_UP);
	CInput::SetButton(0, CInput::eDown, VK_DOWN);
	CInput::SetButton(0, CInput::eLeft, VK_LEFT);
	CInput::SetButton(0, CInput::eRight, VK_RIGHT);
	CInput::SetButton(0, CInput::eMouseL, VK_LBUTTON);
	CInput::SetButton(0, CInput::eMouseR, VK_RBUTTON);
	CInput::SetButton(0, CInput::eMouseC, VK_MBUTTON);
	//	CInput::SetMouseInside(true);
	//	CInput::ShowCursor(false);
	CInput::Update();
	CInput::Update();



	SetCurrentDirectory("data");
	CSound::GetInstance();

	//-----------------------------------------------------
	//初期化の命令を書く
	//ゲーム起動時に一度だけ呼ばれる
	//-----------------------------------------------------
	ADD_RESOURCE("Player", CImage::CreateImage("Image/player2.png", player_anim_data, 16, 16));
	ADD_RESOURCE("Enemy", CImage::CreateImage("Image/nezumi.png", Enemy_anim_data, 16, 16));
	ADD_RESOURCE("Enemy1", CImage::CreateImage("Image/tako.png", Enemy1_anim_data, 16, 16));
	ADD_RESOURCE("Enemy2", CImage::CreateImage("Image/gobuta.png", Enemy2_anim_data, 150, 150));
	ADD_RESOURCE("Enemy3", CImage::CreateImage("Image/Slime3.png", Enemy3_anim_data, 16, 16));
	ADD_RESOURCE("Enemy4", CImage::CreateImage("Image/lex .png", Enemy4_anim_data, 16, 16));
	ADD_RESOURCE("Enemy5", CImage::CreateImage("Image/honoo.png", Enemy5_anim_data, 16, 16));
	ADD_RESOURCE("BossEnemy", CImage::CreateImage("Image/LastBoss.png", BossEnemy_anim_data, 16, 16));
	ADD_RESOURCE("Map_Tip1", CImage::CreateImage("Image/gatiyuka.png"));
	ADD_RESOURCE("Item", CImage::CreateImage("Image/a-ma-.png"));
	ADD_RESOURCE("Item1", CImage::CreateImage("Image/kaihuku.png"));
	ADD_RESOURCE("Item2", CImage::CreateImage("Image/yumi.png"));
	ADD_RESOURCE("Item3", CImage::CreateImage("Image/kenn.png"));
	ADD_RESOURCE("Bullet", CImage::CreateImage("Image/hone.png"));
	ADD_RESOURCE("UI", CImage::CreateImage("Image/hyouzi2.png",UI_anim_data, 120, 30));
	ADD_RESOURCE("Effect", CImage::CreateImage("Image/Slash.png", Effect_anim_data, 538, 538));
	ADD_RESOURCE("menyu-", CImage::CreateImage("Image/menyu-.png", Menyu_anim_data, 32, 32));
	ADD_RESOURCE("Itemmenyu-", CImage::CreateImage("Image/Itemmenyu-.png", Menyu_anim_data, 32, 32)); 
	ADD_RESOURCE("HP", CImage::CreateImage("Image/gauge.png"));
	ADD_RESOURCE("GoalTP", CImage::CreateImage("Image/GoalTP.png"));
	ADD_RESOURCE("Goal", CImage::CreateImage("Image/Goalhaikei.png"));
	ADD_RESOURCE("Title", CImage::CreateImage("Image/haikei.png"));
	ADD_RESOURCE("Slash", CImage::CreateImage("Image/Slash.png", Slash_anim_data, 32, 32));
	//ADD_RESOURCE("Title", CImage::CreateImage("Image/Title.png"));
	//ADD_RESOURCE("Effect", CImage::CreateImage("Image/Effect.png", Effect_anim_data, 535, 535));
	ADD_RESOURCE("Tp", CImage::CreateImage("Image/Tp.png"));
	ADD_RESOURCE("sirusi", CImage::CreateImage("Image/sirusi.png"));
	ADD_RESOURCE("a", CImage::CreateImage("Image/a.png"));
	ADD_RESOURCE("sukiru", CImage::CreateImage("Image/skillbi-mu.png"));
	ADD_RESOURCE("GameOver", CImage::CreateImage("Image/ge-muo-ba-.png"));
	//ステージのランダム
	srand(time(NULL));

	Base::Add(new Title);
	

}


void Release()
{
	CLoadThread::ClearInstance();
	CSound::ClearInstance();
	CResourceManager::ClearInstance();
}

static void ResizeCallback(GLFWwindow* window, int w, int h)
{
	glViewport(0, 0, w, h);

	//画面解像度変動
	CCamera::GetCamera()->SetSize((float)w, (float)h);
	//画面解像度固定
	//CCamera::GetCamera()->SetSize(SCREEN_WIDTH, SCREEN_HEIGHT);

	CCamera::GetCamera()->Viewport(0, 0, w, h);
	CCamera::GetCurrent()->Perspective(DtoR(60.0), (float)w / (float)h, 1.0, 1000.0);

	glfwGetWindowPos(window, &GL::window_x, &GL::window_y);
	GL::UpdateWindowRect(GL::window_x, GL::window_y, w, h);
	CInput::UpdateClipCursor(true);

}
static void WheelCallback(GLFWwindow* _window, double _offsetx, double _offsety) {
	CInput::AddMouseWheel((int)_offsety);

}
static void PosCallback(GLFWwindow* _window, int x, int y) {
	GL::window_x = x;
	GL::window_y = y;
	GL::UpdateWindosRect(x, y, GL::window_width, GL::window_height);
	CInput::UpdateClipCursor(true);

}
static void FocusCallback(GLFWwindow* _window, int f) {
	CInput::UpdateClipCursor(f);
	GL::focus = f;
}

static void error_callback(int error, const char* description)
{
	printf("Error: %s\n", description);
}

//フルスクリーン?ウインドウモードの切り替え
//Alt+Enterで切り替える
void CheckFullScreen() {
	static int key_enter = 0;
	int key_enter_buf = key_enter;
	if (key_enter_buf ^ (key_enter = glfwGetKey(GL::window, GLFW_KEY_ENTER)) && key_enter && (glfwGetKey(GL::window, GLFW_KEY_LEFT_ALT) || glfwGetKey(GL::window, GLFW_KEY_RIGHT_ALT))) {
		GL::ChangeFullScreen(!GL::full_screen);
	}
}

int __main(int* argcp, char** argv) {
	// メモリリーク検出
	//	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF | _CRTDBG_CHECK_ALWAYS_DF);
	//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);


	//OpenGL4.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


	glfwSetErrorCallback(error_callback);
	if (!glfwInit()) return -1;
	//	glutInit(argcp, argv);

	GL::window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Simple", nullptr, nullptr);
	glfwGetWindowSize(GL::window, &GL::window_width, &GL::window_height);
	glfwGetWindowPos(GL::window, &GL::window_x, &GL::window_y);

	glfwSetFramebufferSizeCallback(GL::window, ResizeCallback);
	glfwSetScrollCallback(GL::window, WheelCallback);
	glfwSetWindowFocusCallback(GL::window, FocusCallback);
	glfwSetWindowPosCallback(GL::window, PosCallback);
	if (!GL::window) {
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(GL::window);
	glfwSwapInterval(1);
	ResizeCallback(GL::window, SCREEN_WIDTH, SCREEN_HEIGHT);

	GLenum err = glewInit();
	if (err == GLEW_OK) {
		printf("%s\n", glewGetString(GLEW_VERSION));
	}
	else {
		printf("%s\n", glewGetErrorString(err));
		getchar();
		return -1;
	}
	HDC glDc = wglGetCurrentDC();
	GL::hWnd = WindowFromDC(glDc);
	glClearColor(0.0, 0.0, 0.0, 1.0);

	glEnable(GL_DEPTH_TEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);//ブレンドの有効化
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	//固定シェーダー用
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glEnable(GL_ALPHA_TEST);

	Init();
	while (!glfwWindowShouldClose(GL::window)) {
		CheckFullScreen();


		CInput::Update();
		//各バッファーをクリア
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		MainLoop();


		glfwSwapBuffers(GL::window);


		CFPS::Wait();

		char title[32];
		sprintf_s(title, "summer");
		glfwSetWindowTitle(GL::window, title);

		glfwPollEvents();
		if (glfwGetKey(GL::window, GLFW_KEY_ESCAPE)) {
			glfwSetWindowShouldClose(GL::window, GL_TRUE);
		}

	}

	glfwTerminate();




	Release();
	return 0;
}

INT WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR argv, INT argc)
{
	return __main(&__argc, __argv);
}

int main(int argc, char** argv)
{
	return __main(&argc, argv);
}