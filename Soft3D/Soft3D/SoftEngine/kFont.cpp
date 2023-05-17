#include "pch.h"
#include "kFont.h"
#define _CRT_SECURE_NO_DEPRECATE
#pragma warning (disable : 4996)
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
//#include "UI.h"

#include "QuickDraw.h"
//#include <iostream>
//#include <fstream>


kFont::kFont(const char* path) {


//	path = Application::GetPath(path);

	//game = g;

	chars.resize(256);

	FILE* fi;
	fi = fopen(path, "r");


	int lc = 0;

	for (int i = 0; i < 255; i++) {

		int cw, ch;
		
		fread(&cw, sizeof(int), 1, fi);
		fread(&ch, sizeof(int), 1, fi);

		//printf("W:%d dH:%d /n", cw, ch);

		unsigned char* pixs = (unsigned char *)malloc((size_t)(cw * ch * 4));

		int loc = 0;

		for (int cy = 0; cy < ch; cy++) {
			for (int cx = 0; cx < cw; cx++) {

				unsigned char r, g, b, a;

				fread(&r, sizeof(unsigned char), 1, fi);
				fread(&g, sizeof(unsigned char), 1, fi);
				fread(&b, sizeof(unsigned char), 1, fi);
				fread(&a, sizeof(unsigned char), 1, fi);

				pixs[loc++] = (unsigned char)r;

				pixs[loc++] = (unsigned char)g;
				
				pixs[loc++] = (unsigned char)b;
				
				if (r == 0 && g == 0 && b == 0)
				{
					a = 0;
				}

				pixs[loc++] = (unsigned char)a;


				//loc += 4;


				//rf >> pix[0] >> pix[1] >> pix[2] >> pix[3];
				
			}
		}
		if (cw == 0) {
			chars[i] = nullptr;
			continue;
		}
		Texture2D* nf = new Texture2D(cw, ch,(void *)pixs);
		//nf->Upload(pixs,true);

	

		chars[i] = nf;

	}

}

int kFont::getWidth(const char* text) {

	int cc = 0;
	float x = 0;

	while (true) {

		int cnum = text[cc];

		if (cnum == "\n"[0] || cnum =="\0"[0])
		{
			break;
		}

		if  (cnum >= 0 && cnum <= 255) {

		//	game->drawImg(x, y, (float)(chars[cnum]->w) * scale, (float)(chars[cnum]->h) * scale, 1, 1, 1, 1, chars[cnum]);
			if (chars[cnum] == nullptr) {
				cc++;
				continue;
			}
			x = x + (float)(chars[cnum]->GetWidth()) * scale + 2;

		}

		if (cc > 255)
		{
			break;
		}
		cc++;

	}

	return (int)x;

}

int kFont::getHeight() {


	return (float)(chars[33]->GetHeight()) * scale;

}

void kFont::drawText(const char* text, int x, int y, float r, float g, float b, float a, QuickDraw* draw) {

	int cc = 0;
	
	draw->Begin();
	float ax = (float)x;

	while (true) {

		int cnum = text[cc];

		if (cnum == "\n"[0] || cnum == "\0"[0])
		{
			break;
		}

		if (cnum >= 0 && cnum <= 255) {

			if (chars[cnum] == nullptr) {
				cc++;
				continue;
			}
			//UI::DrawTexture(chars[cnum], ax, y, (float)(chars[cnum]->GetWidth()) * scale, (float)(chars[cnum]->GetHeight()) * scale, r, g, b, a,draw);
			//game->drawImg(ax, y, (float)(chars[cnum]->w)*scale, (float)(chars[cnum]->h)*scale, 1, 1, 1, 1, chars[cnum]);
			
			draw->DrawTex(ax, y, (int)(float)(chars[cnum]->GetWidth()) * scale, (int)(float)(chars[cnum]->GetHeight()) * scale,chars[cnum], r, g, b, a);
			ax = ax + (float)(chars[cnum]->GetWidth()) * scale + 4;
			
		}

		if (cc > 255)
		{
			break;
		}
		cc++;

	}
	draw->End();

}

void kFont::drawText(const char* text, int x, int y, float r, float g, float b, float a) {


	int cc = 0;

	float ax = (float)x;

	//UI::Drawer->Begin();

	while (true) {

		int cnum = text[cc];

		if(cnum=="\n"[0] || cnum=="\0"[0])
		{
			break;
		}

		if (cnum >= 0 && cnum <= 255) {
			if (chars[cnum] == nullptr)
			{
				cc++;
				continue;
			}
		//	UI::DrawTexture(chars[cnum], ax, y, (float)(chars[cnum]->GetWidth()) * scale, (float)(chars[cnum]->GetHeight()) * scale, r, g, b, a);
			//game->drawImg(ax, y, (float)(chars[cnum]->w)*scale, (float)(chars[cnum]->h)*scale, 1, 1, 1, 1, chars[cnum]);

			ax = ax + (float)(chars[cnum]->GetWidth()) * scale + 1;

		}

		if (cc > 255)
		{
			break;
		}
		cc++;

	}

//	UI::Drawer->End();

}