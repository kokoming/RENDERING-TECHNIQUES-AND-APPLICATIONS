/*********************************
1072成圖技術與應用期末專題-雪球大戰
作者:  
4104056004 資工四 李家駿
4104056034 資工四 柯冠名
**********************************
This object will start a snowcraft game.
*********************************/
#include "scene\start_menu.cpp"
#include "scene\battle_scene.cpp"
#include "scene\win_scene.cpp"
#include "scene\death_scene.cpp"
#include "scene\middle_scene.cpp"
#include <atlstr.h>
#include<windows.h>
#include<Mmsystem.h>
#pragma comment(lib,"winmm.lib")
class Snowcraft {
public :
	unsigned char now_input;	//紀錄現在的input
	int mouse_x, mouse_y;		//紀錄滑鼠位置
	int stage=1;				//紀錄當前關卡
	int cheat = 0;				//作弊模式開啟為1，關閉為0
	Snowcraft(int t) {
		if(t==1)	//避免重複宣告
		{
			cout << "startint\n";
			change_scene(START_SCENE);
			now_input = ' ';
			load_all_models();
			init_battle_scene();
			middle_scene.push_back(Middle_scene(1));
			middle_scene.push_back(Middle_scene(2));
			middle_scene.push_back(Middle_scene(3));
			middle_scene.push_back(Middle_scene(4));
			middle_scene.push_back(Middle_scene(5));

		}
	}

	/*場景轉換*/
	void change_scene(int scene) {

		TCHAR szDirectory[MAX_PATH] = { 0 };
		GetCurrentDirectory(MAX_PATH, szDirectory);
		CString sndPath;

		now_scene = scene;
		/*切換BGM*/
		switch (scene) {
			case START_SCENE:
				sndPath.Format(_T("%s\\music\\start_bgm.wav"), szDirectory);
				wcout << (const wchar_t*)sndPath << endl;
				PlaySound(sndPath, NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
				break;
			case DEATH_SCENE:
				sndPath.Format(_T("%s\\music\\dead_bgm.wav"), szDirectory);
				wcout << (const wchar_t*)sndPath << endl;
				PlaySound(sndPath, NULL, SND_FILENAME | SND_ASYNC);
				break;
			case WIN_SCENE:
				sndPath.Format(_T("%s\\music\\win_bgm.wav"), szDirectory);
				wcout << (const wchar_t*)sndPath << endl;
				PlaySound(sndPath, NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
				break;
			//case BATTLE_SCENE:

		}
	}

	/*初始化戰鬥場景*/
	void init_battle_scene()
	{
		//y軸轉30度,視角轉45度
		battle_scene = Battle_scene(-40.0*1.732, 80.0, -40.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0,stage);
		//開啟作弊模式
		battle_scene.open_cheat(cheat);	
	}

	/*顯示場景*/
	void Display_scene() {
		switch (now_scene) {
			case START_SCENE:	//Show the start menu.
				/*根據start_menu return 的choose選擇行動*/
				switch (start_menu.Draw(now_input)) {
					case 1:		
						/*Start the game*/
						cout << "Start menu:start_game\n";
						change_scene(MIDDLE_SCENE);
						break;
					case 2:
						/*Options*/
						//Show options.
						cout << "Start menu:option\n";
						break;
					case 3:
						/*Exit game*/
						cout << "Start menu:exit game\n";
						exit(EXIT_SUCCESS);
						break;
					case 4:
						/*Openg cheat mode*/
						cheat = 1;
					default:
						break;
				}
				
				break;
			case BATTLE_SCENE:	//Show the battle scene.
				//cout << "Now scene:Battle scene.\n";
				battle_scene.Draw(now_input,mouse_x,mouse_y);

				/*判斷battle_scene的flag，如果win_flag==true，表示勝利;如果Lose_flag==true，表示失敗*/
				if (battle_scene.Win_Flag)	//Win the game.
				{
					stage++;
					cout << "Go to stage" << stage << endl;
					if (stage == 6)		//關卡結束，前往勝利畫面。
						change_scene(WIN_SCENE);
					else				//尚有關卡，前往過場畫面
						change_scene(MIDDLE_SCENE);
				}
				else if (battle_scene.Lose_Flag)//Lose the game.
				{
					//敗北，前往死亡畫面
					change_scene(DEATH_SCENE);
				}
				else
					;
				break;
			case DEATH_SCENE:	//Show the death scene.
				switch (now_input) {
					case 13:	//Enter.Continue
						stage = 1;
						change_scene(START_SCENE);
						break;
					default:
						death_scene.Draw();
						break;
				}
				break;
			case MIDDLE_SCENE:	//Show the pause scene.
				switch (now_input) {
					case 13:
						init_battle_scene();	//重新讀入下一關的資料並初始化battle_scene
						change_scene(BATTLE_SCENE);
						break;
					default:
						middle_scene[stage-1].Draw();	//根據關卡繪製過場畫面
				}
				break;
			case WIN_SCENE:
				switch (now_input) { 
					case 13:	//Enter.Continue
						stage = 1;
						change_scene(START_SCENE);
						break;
					default:
						win_scene.Draw();
						break;
				}
				break;
			default:
				break;
		}
		/*每次畫面更新都把now_input初始為空白，避免重複輸入*/
		now_input = ' ';
	}
private:
	int now_scene ;
	Start_menu start_menu;
	Battle_scene battle_scene;
	Death_scene death_scene;
	vector<Middle_scene> middle_scene;
	Win_scene win_scene;
};