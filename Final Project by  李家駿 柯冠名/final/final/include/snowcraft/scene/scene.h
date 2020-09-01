/*********************************
1072成圖技術與應用期末專題-雪球大戰
作者:第三組  
4104056004 資工四 李家駿 
4104056034 資工四 柯冠名
**********************************
This object will create a scene.
*********************************/
#ifndef SCENE_H
#define SCENE_H

#define BMP_Header_Length 54
#include "snowcraft\constants\init_constants.h"
#include "snowcraft\constants\vec.cpp"
class Scene {
public:
	Vec camera;	//相機位置
	Vec lookat;	//鏡頭對準的位置
	Vec camera_up;	//相機上方位置
	Scene() {
		camera = Vec(0, 0, 0);
		lookat = Vec(0, 0, 0);
		camera_up = Vec(0, 0, 0);
	}
	Scene(double camera_x, double camera_y, double camera_z
		, double lookat_x, double lookat_y, double lookat_z
		, double camera_up_x, double camera_up_y, double camera_up_z) {
		camera = Vec(camera_x, camera_y, camera_z);
		lookat = Vec(lookat_x, lookat_y, lookat_z);
		camera_up = Vec(camera_up_x, camera_up_y, camera_up_z);
	}
	/*將物體的3D座標轉換成2D座標，return 一個(x,y,0)的座標。
	請注意此座標並非螢幕座標，需要將螢幕高度減去y軸座標才是螢幕座標*/
	Vec position_to_mouse(Vec posi) {

		GLfloat mouseX, mouseY;

		GLdouble xt, yt, zt;

		GLdouble modelview[16], projection[16];
		GLint viewport[4];
		Vec to;
		/*Get matrix*/
		glGetIntegerv(GL_VIEWPORT, viewport);
		glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
		glGetDoublev(GL_PROJECTION_MATRIX, projection);

		gluProject(posi.x(), posi.y(), posi.z(), modelview, projection, viewport, &xt, &yt, &zt);
		to = Vec(xt, viewport[3]-yt, zt);
		//cout << to.x() << "," << to.y() << "," << to.z() << endl;
		return to;
	}

	/*將滑鼠位置轉換成3D座標，return一個(x,y,z)座標
	請注意y軸座標數值較詭異，不可使用。*/
	Vec GetCursorPlane(int x, int y)
	{
		GLfloat mouseX, mouseY;

		GLdouble posX1, posY1, posZ1;
		GLdouble posX2, posY2, posZ2;

		GLdouble modelview[16],projection[16];
		GLint viewport[4];
		Vec to;
		/*Get matrix*/
		//glMatrixMode(GL_VIEWPORT);
		glGetIntegerv(GL_VIEWPORT,viewport);
		glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
		glGetDoublev(GL_PROJECTION_MATRIX, projection);

		mouseX = (float)x;
		mouseY = (float)viewport[3] - (float)y;

		gluUnProject(mouseX, mouseY, 0.0, modelview, projection, viewport, &posX1, &posY1, &posZ1);
		gluUnProject(mouseX, mouseY, 1.0, modelview, projection, viewport, &posX2, &posY2, &posZ2);

		//Find X and Z when Y is 0
		float zeropoint, zeroperc;
		double posXt, posYt, posZt;
		posXt = posX1 - posX2;
		posYt = posY1 - posY2;
		posZt = posZ1 - posZ2;

		//Check the Y’s pass through the plane on 0
		if (posY1 < 0.0 && posY2 < 0.0 || posY1 > 0.0 && posY2 > 0.0)
			return to;

		//Now we’ll nudge out stuff up and find out the zero point
		zeropoint = 0.0f - (float)posY1;

		//Find the percentage that this point is between them
		zeroperc = (zeropoint / (float)posYt);

		
		to.x((float)posX1 + (float)(posXt * zeroperc));
		to.y((float)posY1 + (float)(posYt * zeroperc));
		to.z((float)posZ1 + (float)(posZt * zeroperc));
		//cout << to.x() << "," << to.y() << "," << to.z() << endl;
		return to;
	}
	int power_of_two(int n) {
		if (n <= 0) {
			return 0;
		}
		else {
			return(n & (n - 1)) == 0;
		}
	}
	/*讀取texture*/
	GLuint load_texture(const char* file_name)
	{
		GLint width, height, total_bytes;
		GLubyte* pixels = 0;
		GLuint last_texture_ID = 0, texture_ID = 0;

		FILE* pFile;
		if (fopen_s(&pFile, file_name, "rb") != 0)
			return 0;

		fseek(pFile, 0x0012, SEEK_SET);
		fread(&width, 4, 1, pFile);
		fread(&height, 4, 1, pFile);
		fseek(pFile, BMP_Header_Length, SEEK_SET);

		{
			GLint line_bytes = width * 3;
			while (line_bytes % 4 != 0)
				++line_bytes;
			total_bytes = line_bytes * height;
		}

		pixels = (GLubyte*)malloc(total_bytes);
		if (pixels == 0)
		{
			fclose(pFile);
			return 0;
		}

		if (fread(pixels, total_bytes, 1, pFile) <= 0)
		{
			free(pixels);
			fclose(pFile);
			return 0;
		}

		/*此段程式碼會將貼圖縮小以加快運算速度，但此專案不需要這段程式碼。*/
		// {
			// GLint max;
			// glGetIntegerv(GL_MAX_TEXTURE_SIZE, &max);
			// if (!power_of_two(width)
				// || !power_of_two(height)
				// || width > max
				// || height > max)
			// {
				// const GLint new_width = INITIAL_WIDTH;
				// const GLint new_height = INITIAL_HEIGHT;
				// GLint new_line_bytes, new_total_bytes;
				// GLubyte* new_pixels = 0;

				// new_line_bytes = new_width * 3;
				// while (new_line_bytes % 4 != 0)
					// ++new_line_bytes;
				// new_total_bytes = new_line_bytes * new_height;

				// new_pixels = (GLubyte*)malloc(new_total_bytes);
				// if (new_pixels == 0)
				// {
					// free(pixels);
					// fclose(pFile);
					// return 0;
				// }

				// gluScaleImage(GL_RGB,
					// width, height, GL_UNSIGNED_BYTE, pixels,
					// new_width, new_height, GL_UNSIGNED_BYTE, new_pixels);

				// free(pixels);
				// pixels = new_pixels;
				// width = new_width;
				// height = new_height;
			// }
		// }

		glGenTextures(1, &texture_ID);
		if (texture_ID == 0)
		{
			free(pixels);
			fclose(pFile);
			return 0;
		}

		GLint lastTextureID = last_texture_ID;
		glGetIntegerv(GL_TEXTURE_BINDING_2D, &lastTextureID);
		glBindTexture(GL_TEXTURE_2D, texture_ID);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0,
			GL_BGR_EXT, GL_UNSIGNED_BYTE, pixels);
		glBindTexture(GL_TEXTURE_2D, lastTextureID);
		free(pixels);
		return texture_ID;
	}

private:
};

#endif 