#include "j1App.h"
#include "j1Input.h"
#include "j1Render.h"
#include "j1Textures.h"
#include "j1Fonts.h"
#include "j1Gui.h"
#include "UIButton.h"



UIButton::UIButton(int x, int y, UIElementType type, ButtonType buttontype, const char* text, j1Module* modul):UIElements(x,y,type,modul)
{
	if (text != nullptr)
	{
		buttontext = text;
		ButtonText=App->font->Print(buttontext, { 255, 255, 0 }, App->gui->fonts[1]);
		App->tex->GetSize(ButtonText, sizeTx, sizeTy);
	}
	
	btype = buttontype;
	ElementTexture = App->gui->buttons[0];
	scale = 2.0f;

	App->tex->GetSize(ElementTexture, size_x, size_y);
	
}


UIButton::~UIButton()
{
}


void UIButton::Draw()
{
	if (!isWindowElement)
	{
		int rect_x = position.x - (size_x / 2)*scale;
		int rect_y = position.y;

		Elementrect = { rect_x,rect_y,(int)size_x*(int)scale,(int)size_y*(int)scale };
		App->render->Blit(ElementTexture, position.x - App->render->camera.x - size_x, position.y - App->render->camera.y, 2.0f);
		App->render->Blit(ButtonText, position.x - App->render->camera.x - sizeTx / 2, position.y - App->render->camera.y + sizeTy / 2);

		if (debug == true)
		{
			App->render->DrawQuad(Elementrect, 255, 0, 255, 80);
		}

		if (light)
		{
			App->render->Blit(App->gui->buttons[1], position.x - App->render->camera.x - size_x - 12, position.y - App->render->camera.y - 12, 2.0f);
		}

		if (action)
		{
			Move();
		}

		App->input->GetMousePosition(mouseend.x, mouseend.y);
	}
}

void UIButton::Move()
{
	App->input->GetMousePosition(mousestart.x, mousestart.y);

	if (mousestart.x != mouseend.x || mousestart.y != mouseend.y)
	{
		position.x += mousestart.x - mouseend.x;
		position.y += mousestart.y - mouseend.y;
	}
}

void UIButton::Action()
{
	
	if (!light)
	{
		light = true;
	}
	else
	{
		light = false;
	}
}