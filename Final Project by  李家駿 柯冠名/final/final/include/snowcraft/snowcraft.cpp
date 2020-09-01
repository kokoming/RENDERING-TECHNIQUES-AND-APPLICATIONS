/*********************************
1072���ϧ޳N�P���δ����M�D-���y�j��
�@��:  
4104056004 ��u�| ���a�@
4104056034 ��u�| �_�a�W
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
	unsigned char now_input;	//�����{�b��input
	int mouse_x, mouse_y;		//�����ƹ���m
	int stage=1;				//������e���d
	int cheat = 0;				//�@���Ҧ��}�Ҭ�1�A������0
	Snowcraft(int t) {
		if(t==1)	//�קK���ƫŧi
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

	/*�����ഫ*/
	void change_scene(int scene) {

		TCHAR szDirectory[MAX_PATH] = { 0 };
		GetCurrentDirectory(MAX_PATH, szDirectory);
		CString sndPath;

		now_scene = scene;
		/*����BGM*/
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

	/*��l�ƾ԰�����*/
	void init_battle_scene()
	{
		//y�b��30��,������45��
		battle_scene = Battle_scene(-40.0*1.732, 80.0, -40.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0,stage);
		//�}�ҧ@���Ҧ�
		battle_scene.open_cheat(cheat);	
	}

	/*��ܳ���*/
	void Display_scene() {
		switch (now_scene) {
			case START_SCENE:	//Show the start menu.
				/*�ھ�start_menu return ��choose��ܦ��*/
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

				/*�P�_battle_scene��flag�A�p�Gwin_flag==true�A��ܳӧQ;�p�GLose_flag==true�A��ܥ���*/
				if (battle_scene.Win_Flag)	//Win the game.
				{
					stage++;
					cout << "Go to stage" << stage << endl;
					if (stage == 6)		//���d�����A�e���ӧQ�e���C
						change_scene(WIN_SCENE);
					else				//�|�����d�A�e���L���e��
						change_scene(MIDDLE_SCENE);
				}
				else if (battle_scene.Lose_Flag)//Lose the game.
				{
					//�ѥ_�A�e�����`�e��
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
						init_battle_scene();	//���sŪ�J�U�@������ƨê�l��battle_scene
						change_scene(BATTLE_SCENE);
						break;
					default:
						middle_scene[stage-1].Draw();	//�ھ����dø�s�L���e��
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
		/*�C���e����s����now_input��l���ťաA�קK���ƿ�J*/
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