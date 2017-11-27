#include "j1App.h"
#include "j1Render.h"
#include "j1Textures.h"
#include "j1Fonts.h"
#include "j1Gui.h"
#include "UIButton.h"



UIButton::UIButton(int x, int y, UIElementType type, ButtonType buttontype, const char* text):UIElements(x,y,type)
{
	if (text != nullptr)
	{
		buttontext = text;
		ButtonText=App->font->Print(buttontext, { 255, 255, 0 }, App->gui->fonts[0]);
	}
	
	btype = buttontype;
	ButtonTex = App->gui->buttons[0];

	App->tex->GetSize(ButtonTex, size_x, size_y);
}


UIButton::~UIButton()
{
}


void UIButton::Draw()
{
	if (btype == BUTTON_1)
	{
		App->render->Blit(ButtonTex, position.x - App->render->camera.x - size_x / 2, position.y - App->render->camera.y - size_y / 2,2.0f);
		App->render->Blit(ButtonText, position.x - App->render->camera.x , position.y - App->render->camera.y);

	}

}

bool UIButton::Iluminate()
{
	return true;
}