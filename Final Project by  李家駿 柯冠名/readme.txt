final
--include
	--GL:opengl functions.
	--snowcraft
		--constants
			init_constants.h:存放各種常數與global variables，並include所有需要的headers，load model與建立Display list的function也在這裡。
			vec.cpp:自己寫的3D向量(座標)物件，可進行向量的加、減、dot與cross運算。
		--objects
			bounding_box.cpp:可用於碰撞偵測的bounding_box，這程式沒用到。
			enemy.cpp:定義Enemy物件。
			hero.cpp:定義Hero物件。
			Moving_object.h:各種移動物件的父類別，定義一個三維空間可移動的物件。
			snowball.cpp:定義Snowball物件。
		--scene
			battle_scene.cpp:定義戰場場景的物件。
			death_scene.cpp:定義死亡畫面的物件。
			middle_scene.cpp:定義過場畫面的物件。
			pause_scene.cpp:原定暫停畫面的物件宣告，並無實作。
			scene.h:各種場景物件的父類別，其中包含了滑鼠位置to3D座標的function，以及讀取texture的function。
			start_menu.cpp:定義開始畫面的物件。
			win_scene.cpp:定義勝利畫面的物件。
		snowcraft.cpp:定義整個遊戲的物件。
--lib:存放需要的lib
--model
	--Lego:樂高人model，己方操作人物
	--Snowman:雪人怪物model，敵方人物
--picture:存放所有的texture
--stage:存放關卡設定資料
--music:存放音樂
final.cpp:主程式位置
glm.cpp:obj model loader

learn more information in 李家駿's github:
https://github.com/JJ-Tom-Li/Rendering-Techniques-and-Applications-Assignments/tree/master/Final
