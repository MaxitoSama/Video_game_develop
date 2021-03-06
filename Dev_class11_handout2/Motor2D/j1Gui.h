#ifndef __j1GUI_H__
#define __j1GUI_H__

#include "p2List.h"
#include "p2Log.h"
#include "j1Module.h"


#define CURSOR_WIDTH 2

class SDL_Texture;
class SDL_Rect;
class UIElements;
enum UIElementType;

// TODO 1: Create your structure of classes

// ---------------------------------------------------

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

	// TODO 2: Create the factory methods
	// Gui creation functions

	void AddElementText(int x, int y, UIElementType type, const char* text=nullptr);
	void AddElementImage(int x, int y, UIElementType type, SDL_Rect* rect);
	void DeleteElements(UIElements* element);


	SDL_Texture* GetAtlas() const;

public:

	p2List<UIElements*> elements;
	
private:

	SDL_Texture* atlas;
	p2SString atlas_file_name;
};

#endif // __j1GUI_H__