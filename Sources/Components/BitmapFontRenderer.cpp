
#include <map>
#include <math.h>

#include "BitmapFontRenderer.h"
#include "../Debug/Logger.h"
#include "../Systems/ScreenSystem.h"
#include "../Components/Camera.h"

BitmapFontRenderer::~BitmapFontRenderer()
{
	delete drawer_;
	if (text_ != NULL)delete text_;
}

BitmapFontRenderer::BitmapFontRenderer()
{
	drawer_ = new GLDrawer(GL_TRIANGLES, VBO);
	drawer_->setVertexIndex(0);
	drawer_->setTexCoordIndex(1);
}

void BitmapFontRenderer::Create()
{

}

void BitmapFontRenderer::Init()
{
	//setText("Hello baby\nhow are you?\nI'm fine.How are you?\n");
}

void BitmapFontRenderer::Render(int materialIndex /* = 0 */)
{
	if (isDirty_)
	{
		if (textLength_ > 0)
		{
			calculatGeometry();
			if (vertices_.size() > 0 && uvs_.size() > 0)
			{
				drawer_->setVertexData(2, false, vertices_.size(), vertices_[0].getPointer());
				drawer_->setTexCoordData(2, false, uvs_.size(), uvs_[0].getPointer());
			}
		}
		else
		{
			drawer_->setVertexData(2, false, 0, NULL);
			drawer_->setTexCoordData(2, false, 0, NULL);
		}
		isDirty_ = false;
	}

	drawer_->draw();
}

void BitmapFontRenderer::setText(const char* text)
{
	if (text_)
		delete text_;
	
	if (text)
	{
		textLength_ = strlen(text);
		if (textLength_ > 0)
		{
			text_ = new char[textLength_];
			strcpy(text_, text);
		}
	}

	isDirty_ = true;
}

void BitmapFontRenderer::calculatGeometry()
{
	if (font_.isEmpty())
		return;

	vertices_.clear();
	uvs_.clear();
	
	int sWidth = ScreenSystem::getWidth();
	int sHeight = ScreenSystem::getWidth();

	int txtWidth = font_->scaleW;
	int txtHeight = font_->scaleH;
	
	Vector2 camSize = Camera::main->getHalfSize()*2;
	float screenToWorldH = camSize.x / sWidth;
	float screenToWorldV = camSize.y / sHeight;

	Vector2 textSize;
	float maxLineWidth = 0;
	float textHeight = 0;
	int lines = 1;

	for (int i = 0; i < textLength_; i++)
	{
		char c = text_[i];
		//Logger::Print("Char %c\n", c);
		
		std::map<int, CharacterInfo*>::iterator iter = font_->characters.find(c);
		if (iter == font_->characters.end()) //if character not found
		{
			switch (c)
			{
			case '\n':
				lines++;
				maxLineWidth = max(textSize.x, maxLineWidth);
				textSize.y -= font_->lineHeight*screenToWorldV;
				textSize.x = 0;
				break;
			}
			continue;
		}

		CharacterInfo& character = *iter->second;

		/* 3 -------- 2
			 |    / | 
			 |	 /  |	//quad based on two triangles - 012 and 230
			 |	/ 	| 
			 | /	|
		   0 -------- 1
		*/

		//Logger::Print("Font x=%d,y=%d,width=%d,height=%d\n", character.x, character.y, character.width, character.height);

		//character uv cordinates
		float fLeft = (float)character.x / txtWidth;
		float fRight = (float)(character.x + character.width) / txtWidth;
		float fTop = 1.0f-(float)character.y / txtHeight;
		float fBottom = 1.0f-(float)(character.y + character.height) / txtHeight;

		//Logger::Print("UV:: %f,%f,%f,%f\n", fLeft, fRight, fBottom, fTop);
 		uvs_.push_back(Vector2(fLeft, fBottom)); //0
		uvs_.push_back(Vector2(fRight, fBottom)); //1
		uvs_.push_back(Vector2(fRight, fTop)); //2

		uvs_.push_back(Vector2(fRight, fTop)); //2
		uvs_.push_back(Vector2(fLeft, fTop)); //3
		uvs_.push_back(Vector2(fLeft, fBottom)); //0

		//character local cordinates
		fLeft = textSize.x + character.xoffset*screenToWorldH;
		fRight = fLeft + character.width*screenToWorldH;
		fTop = textSize.y - character.yoffset*screenToWorldV;
		fBottom = fTop - character.height*screenToWorldV;

		//Logger::Print("VERTICES:: %f,%f,%f,%f\n", fLeft, fRight, fBottom, fTop);
		vertices_.push_back(Vector2(fLeft, fBottom)); //0
		vertices_.push_back(Vector2(fRight, fBottom)); //1
		vertices_.push_back(Vector2(fRight, fTop)); //2

		vertices_.push_back(Vector2(fRight, fTop)); //2
		vertices_.push_back(Vector2(fLeft, fTop)); //3
		vertices_.push_back(Vector2(fLeft, fBottom)); //0

		textSize.x += character.xadvance*screenToWorldH;

		//Logger::Print("Text Size %f\n", textSize.x);
	}

	//Logger::Print("Info lines_count=%d, maxLineWidth=%f\n", lines, maxLineWidth);

	//calculating horizontal and vertical alignment
	textHeight = lines*font_->lineHeight*screenToWorldV;

// 	for (int i = 0, len = vertices_.size(); i < len; i++)
// 	{
// 		vertices_[i].x -= maxLineWidth / 2.0f;
// 		vertices_[i].y += textHeight / 2.0f;
// 	}
}