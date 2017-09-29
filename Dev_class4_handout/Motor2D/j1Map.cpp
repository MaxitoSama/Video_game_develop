#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1Textures.h"
#include "j1Map.h"
#include <math.h>

j1Map::j1Map() : j1Module(), map_loaded(false)
{
	name.create("map");
}

// Destructor
j1Map::~j1Map()
{}

// Called before render is available
bool j1Map::Awake(pugi::xml_node& config)
{
	LOG("Loading Map Parser");
	bool ret = true;

	folder.create(config.child("folder").child_value());

	return ret;
}

void j1Map::Draw()
{
	if(map_loaded == false)
		return;

	// TODO 6: Iterate all tilesets and draw all their 
	// images in 0,0 (you should have only one tileset for now)

	for (uint i = 0; i < first_map.map_tileset.Count(); i++) {
		
		App->render->Blit()
	}

}

// Called before quitting
bool j1Map::CleanUp()
{
	LOG("Unloading map");

	// TODO 2: Make sure you clean up any memory allocated
	// from tilesets / map


	map_file.reset();

	return true;
}

// Load new map
bool j1Map::Load(const char* file_name)
{
	bool ret = true;
	p2SString tmp("%s%s", folder.GetString(), file_name);

	pugi::xml_parse_result result = map_file.load_file(tmp.GetString());

	if(result == NULL)
	{
		LOG("Could not load map xml file %s. pugi error: %s", file_name, result.description());
		ret = false;
	}

	if(ret == true)
	{
		// TODO 3: Create and call a private function to load and fill
		// all your map data
		FillMap(map_file);
	}

	// TODO 4: Create and call a private function to load a tileset
	// remember to support more any number of tilesets!
	

	if(ret == true)
	{
		// TODO 5: LOG all the data loaded
		// iterate all tilesets and LOG everything
	}

	map_loaded = ret;

	return ret;
}

void j1Map::FillMap(const pugi::xml_document& document) {

	pugi::xml_node aux_node = document.child("map");

	LOG("-----------------Map Info--------------------------------------");
	first_map.orientation = String_to_Enum_2(aux_node.attribute("orientation").as_string());
	LOG("orientation --> %s ( %d )",aux_node.attribute("orientation").as_string(), first_map.orientation);

	first_map.renderorder = String_to_Enum_1(aux_node.attribute("renderorder").as_string());
	LOG("Renderorder --> %s ( %d )",aux_node.attribute("renderorder").as_string(), first_map.renderorder);

	first_map.width = aux_node.attribute("width").as_uint();
	LOG("width --> %d", first_map.width);

	first_map.height = aux_node.attribute("height").as_uint();
	LOG("height --> %d", first_map.height);

	first_map.tilewidth = aux_node.attribute("tilewidth").as_uint();
	LOG("tilewidth --> %d", first_map.tilewidth);

	first_map.tileheight = aux_node.attribute("tileheight").as_uint();
	LOG("tileheight --> %d", first_map.tileheight);

	first_map.nextobject = aux_node.attribute("nextobjectid").as_uint();
	LOG("nextobject --> %d", first_map.nextobject);

	FillTilset(document, first_map.map_tileset);
	

	LOG("---------------------------------------------------------------");

	

	
}

void j1Map::FillTilset(const pugi::xml_document& document, p2DynArray<Tileset>& tileset_map) {

	pugi::xml_node tilset;
	Tileset aux_tileset;
	uint counter = 1;

	for (tilset = document.child("map").child("tileset"); tilset; tilset = tilset.next_sibling("tileset")) {
		
		LOG("-----TileSet %d----", counter);

		aux_tileset.name = tilset.attribute("name").as_string();
		LOG("Name: %s", aux_tileset.name.GetString());

		aux_tileset.img_source = tilset.attribute("source").as_string();
		LOG("Image source: %s", aux_tileset.img_source.GetString());

		aux_tileset.tileWidth = tilset.attribute("tilewidth").as_uint();
		LOG("TileWidth: %d", aux_tileset.tileWidth);

		aux_tileset.tileHeight = tilset.attribute("tileheight").as_uint();
		LOG("TileHeight: %d", aux_tileset.tileHeight);

		aux_tileset.spacing = tilset.attribute("spacing").as_uint();
		LOG("Spacing: %d", aux_tileset.spacing);

		aux_tileset.margin = tilset.attribute("margin").as_uint();
		LOG("Margin: %d", aux_tileset.margin);

		tileset_map.PushBack(aux_tileset);
		counter++;
	}
}

Map_renderorder j1Map::String_to_Enum_1(p2SString str) {
	
	if (str == "right-down")
		return right_down;

	if (str == "right-up")
		return right_up;

	if (str == "left-down")
		return left_down;

	if (str == "left-up")
		return left_up;
}

Map_Orientation j1Map::String_to_Enum_2(p2SString str) {
	
	if (str == "orthogonal")
		return orthogonal;

	if (str == "isometric")
		return isometric;

	if (str == "staggered")
		return staggered;

	if (str == "hexagonal")
		return hexagonal;

}