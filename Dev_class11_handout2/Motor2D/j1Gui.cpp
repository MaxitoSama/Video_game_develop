#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1Textures.h"
#include "j1Fonts.h"
#include "j1Input.h"
#include "j1Gui.h"
#include "UIElements.h"
#include "UIText.h"
#include "UIImage.h"

j1Gui::j1Gui() : j1Module()
{
	name.create("gui");
}

// Destructor
j1Gui::~j1Gui()
{}

// Called before render is available
bool j1Gui::Awake(pugi::xml_node& conf)
{
	LOG("Loading GUI atlas");
	bool ret = true;

	atlas_file_name = conf.child("atlas").attribute("file").as_string("");

	return ret;
}

// Called before the first frame
bool j1Gui::Start()
{
	atlas = App->tex->Load(atlas_file_name.GetString());

	return true;
}

// Update all guis
bool j1Gui::PreUpdate()
{
	return true;
}

bool j1Gui::PostUpdate()
{
	p2List_item<UIElements*>* element=elements.start;

	while (element != nullptr)
	{
		element->data->Draw();
		element = element->next;
	}

	return true;
}

// Called after all Updates


// Called before quitting
bool j1Gui::CleanUp()
{
	LOG("Freeing GUI");

	return true;
}

// const getter for atlas
SDL_Texture* j1Gui::GetAtlas() const
{
	return atlas;
}

// class Gui ---------------------------------------------------

void j1Gui::AddElementText(int x, int y, UIElementType type, const char* text)
{
	UIElements* element_created;
	element_created = new UIText(x, y, type,text);
	elements.add(element_created);

}

void j1Gui::AddElementImage(int x, int y, UIElementType type, SDL_Rect* rect)
{
	UIElements* element_created;
	element_created = new UIImage(x, y, type, rect);
	elements.add(element_created);
}

void j1Gui::DeleteElements(UIElements* element)
{
	RELEASE(element);
}