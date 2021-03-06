#ifndef __j1GUI_H__
#define __j1GUI_H__

#include "p2List.h"
#include "p2Log.h"
#include "j1Module.h"
#include "p2DynArray.h"


#define CURSOR_WIDTH 2

class SDL_Texture;
class SDL_Rect;
class UIElements;
enum UIElementType;
enum ButtonType;
class _TTF_Font;

enum UIEvents
{
	MOUSE_ENTER,
	MOUSE_LEAVE,
	MOUSE_CLICK,
	MOUSE_STOP_CLICK
};

class j1Gui : public j1Module
{
public:

	j1Gui();

	// Destructor
	virtual ~j1Gui();

	// Called when before render is available
	bool Awake(pugi::xml_node&);

	// Call before first frame
	bool Start();

	// Called before all Updates
	bool PreUpdate();

	//bool Update(float dt);

	// Called after all Updates
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

	bool GUIEvent(UIEvents eventType, UIElements* element) { return true; }

	// TODO 2: Create the factory methods
	// Gui creation functions

	void AddBackground(int x, int y, UIElementType type, j1Module* modul);
	void AddElementText(int x, int y, UIElementType type, j1Module* modul, const char* text=nullptr);
	UIElements* AddElementTextBox(int x, int y, UIElementType type, j1Module* modul, const char* text = nullptr);
	void AddElementImage(int x, int y, UIElementType type, SDL_Rect* rect, j1Module* modul);
	UIElements* AddElementButton(int x, int y, UIElementType type, ButtonType btype, j1Module* modul, const char* text = nullptr,bool iswinelem=false);
	UIElements* AddElementWindow(int x, int y, UIElementType type, j1Module* modul, p2List<UIElements*>* elementslist);
	
	void DeleteElements(UIElements* element);

	bool CheckMouse(UIElements*)const;


	SDL_Texture* GetAtlas() const;
	SDL_Texture* GetBackground() const;

public:

	p2List<UIElements*> elements;
	SDL_Texture* background=nullptr;
	SDL_Texture* textbox = nullptr;
	p2DynArray<_TTF_Font*> fonts;
	p2DynArray<SDL_Texture*> buttons;
	
private:

	SDL_Texture* atlas=nullptr;
	p2SString atlas_file_name;
	bool elementclicked = false;
};

#endif // __j1GUI_H__