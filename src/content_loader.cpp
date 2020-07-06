#include "content_loader.h"

#include "pugixml.hpp"
#include <iostream>
#include <string>
#include "globalvariables.h"
#include "sprite.h"

enemy_content_map enemyContentMap;

void SetEnemyContentFromEnemyDirXMLFile(std::string xml_enemy_scripts_file_dir,
									   std::string xml_enemy_scripts_file_path)
{
	// Create empty XML document within memory
    pugi::xml_document doc;
    
    // Load XML file into memory
    // Remark: to fully read declaration entries you have to specify
    // "pugi::parse_declaration"
    pugi::xml_parse_result result = doc.load_file(xml_enemy_scripts_file_path.c_str(),
												pugi::parse_default);
    if (!result)
    {
        std::cout << "Parse error: " << result.description()
            << ", character pos= " << result.offset;
        return;
    }
    
    pugi::xml_node enemyDirRoot = doc.child("EnemyDirRoot");
    
    size_t iterator = 0;
	
	//go through each tile type in tiles node
	for (pugi::xml_node enemyNode = enemyDirRoot.first_child(); enemyNode; enemyNode = enemyNode.next_sibling())
	{
		
		std::string valName = enemyNode.attribute("name").value();
		std::string valFilepath = enemyNode.attribute("scriptfilepath").value();
		std::string valMediaDir = enemyNode.attribute("mediaDir").value();
		std::string valXMLDefFilepath = enemyNode.attribute("xmldefpath").value();
		
		//assuming file paths in xml file is set relative to xml filepath itself
		std::string filepath = xml_enemy_scripts_file_dir + "/" + valFilepath;
		std::cout << "file read:" << filepath << std::endl;
		std::string mediaDir = xml_enemy_scripts_file_dir + "/" + valMediaDir;
		std::string xml_def_fp = xml_enemy_scripts_file_dir + "/" + valXMLDefFilepath;
		
		EnemyContent ec; 
		ec.name = valName; 
		ec.script_filepath = filepath;
		ec.mediaDir = mediaDir;
		ec.xml_def_filepath = xml_def_fp;
		std::pair<std::string,EnemyContent> thisEnemyContentPair (valName,ec);
		enemyContentMap.insert (thisEnemyContentPair);
		
		iterator++;		
	}
}

void LoadContentFromXMLFiles()
{	
	std::string xml_enemy_scripts_file_dir = DATADIR_STR + "/EnemyPacks";
	std::string xml_enemy_scripts_file_path = xml_enemy_scripts_file_dir + "/enemy_directory.xml";
	SetEnemyContentFromEnemyDirXMLFile(xml_enemy_scripts_file_dir,xml_enemy_scripts_file_path);
	
}

bool loadScriptedEnemyVisualMedia(std::string xml_file_path,std::string xml_file_dir,
						LTexture* cTexture,
                        std::vector <SDL_Rect> &walk_clips,
                        SDL_Renderer* gRenderer )
{
    
    // Create empty XML document within memory
	pugi::xml_document doc;

	// Load XML file into memory
	// Remark: to fully read declaration entries you have to specify
	// "pugi::parse_declaration"
	pugi::xml_parse_result result = doc.load_file(xml_file_path.c_str(),
											pugi::parse_default);
	if (!result)
	{
		std::cout << "Parse error: " << result.description() << ", character pos= " << result.offset;
		return false;
	}
    
    pugi::xml_node root = doc.child("EnemyRoot");
    
    std::string cTexFilePath = xml_file_dir + "/" + root.child("Texture").attribute("path").value();
    
    //initialize texture
    if(!cTexture->loadFromFile(cTexFilePath.c_str(),gRenderer) )
    {
        std::cout << "scripted enemy image loading failed! \n";
        std::cout << "filepath:" << cTexFilePath << std::endl;
        return false;
    }
    else
    {
		
		std::string valString;
		
		//set size of walk clips vector
		valString = root.child("WalkClips").child("clip_num").attribute("number").value();
		size_t clipsNum = atoi(valString.c_str());
        walk_clips.resize(clipsNum);
		
		//set width and height of each uniform clips
		valString = root.child("WalkClips").child("clip_width").attribute("width").value();
        std::int8_t width = atoi(valString.c_str());
        valString = root.child("WalkClips").child("clip_height").attribute("height").value();
        std::int8_t height = atoi(valString.c_str());
        
        SDL_Rect clip;
        clip.w = width;
        clip.h = height;
        
        valString = root.child("WalkClips").child("UP_1").attribute("x").value();
        clip.x = atoi(valString.c_str());;
        valString = root.child("WalkClips").child("UP_1").attribute("y").value();
        clip.y = atoi(valString.c_str());;
        walk_clips[Sprite::UP_1] = clip;
        
        valString = root.child("WalkClips").child("UP_2").attribute("x").value();
        clip.x = atoi(valString.c_str());;
        valString = root.child("WalkClips").child("UP_2").attribute("y").value();
        clip.y = atoi(valString.c_str());;
        walk_clips[Sprite::UP_2] = clip; 
        
        valString = root.child("WalkClips").child("UP_3").attribute("x").value();
        clip.x = atoi(valString.c_str());;
        valString = root.child("WalkClips").child("UP_3").attribute("y").value();
        clip.y = atoi(valString.c_str());;
        walk_clips[Sprite::UP_3] = clip; 
        
        valString = root.child("WalkClips").child("UP_4").attribute("x").value();
        clip.x = atoi(valString.c_str());;
        valString = root.child("WalkClips").child("UP_4").attribute("y").value();
        clip.y = atoi(valString.c_str());;
        walk_clips[Sprite::UP_4] = clip;
        
        valString = root.child("WalkClips").child("UP_LEFT_1").attribute("x").value();
        clip.x = atoi(valString.c_str());;
        valString = root.child("WalkClips").child("UP_LEFT_1").attribute("y").value();
        clip.y = atoi(valString.c_str());;
        walk_clips[Sprite::UP_LEFT_1] = clip;
        
        valString = root.child("WalkClips").child("UP_LEFT_2").attribute("x").value();
        clip.x = atoi(valString.c_str());;
        valString = root.child("WalkClips").child("UP_LEFT_2").attribute("y").value();
        clip.y = atoi(valString.c_str());;
        walk_clips[Sprite::UP_LEFT_2] = clip;
        
        valString = root.child("WalkClips").child("UP_LEFT_3").attribute("x").value();
        clip.x = atoi(valString.c_str());;
        valString = root.child("WalkClips").child("UP_LEFT_3").attribute("y").value();
        clip.y = atoi(valString.c_str());;
        walk_clips[Sprite::UP_LEFT_3] = clip;
        
        valString = root.child("WalkClips").child("UP_LEFT_4").attribute("x").value();
        clip.x = atoi(valString.c_str());;
        valString = root.child("WalkClips").child("UP_LEFT_4").attribute("y").value();
        clip.y = atoi(valString.c_str());;
        walk_clips[Sprite::UP_LEFT_4] = clip;
        
        valString = root.child("WalkClips").child("LEFT_1").attribute("x").value();
        clip.x = atoi(valString.c_str());;
        valString = root.child("WalkClips").child("LEFT_1").attribute("y").value();
        clip.y = atoi(valString.c_str());;
        walk_clips[Sprite::LEFT_1] = clip;
        
        valString = root.child("WalkClips").child("LEFT_2").attribute("x").value();
        clip.x = atoi(valString.c_str());;
        valString = root.child("WalkClips").child("LEFT_2").attribute("y").value();
        clip.y = atoi(valString.c_str());;
        walk_clips[Sprite::LEFT_2] = clip;
        
        valString = root.child("WalkClips").child("LEFT_3").attribute("x").value();
        clip.x = atoi(valString.c_str());;
        valString = root.child("WalkClips").child("LEFT_3").attribute("y").value();
        clip.y = atoi(valString.c_str());;
        walk_clips[Sprite::LEFT_3] = clip;
        
        valString = root.child("WalkClips").child("LEFT_4").attribute("x").value();
        clip.x = atoi(valString.c_str());;
        valString = root.child("WalkClips").child("LEFT_4").attribute("y").value();
        clip.y = atoi(valString.c_str());;
        walk_clips[Sprite::LEFT_4] = clip;
        
        valString = root.child("WalkClips").child("DOWN_LEFT_1").attribute("x").value();
        clip.x = atoi(valString.c_str());;
        valString = root.child("WalkClips").child("DOWN_LEFT_1").attribute("y").value();
        clip.y = atoi(valString.c_str());;
        walk_clips[Sprite::DOWN_LEFT_1] = clip;
        
        valString = root.child("WalkClips").child("DOWN_LEFT_2").attribute("x").value();
        clip.x = atoi(valString.c_str());;
        valString = root.child("WalkClips").child("DOWN_LEFT_2").attribute("y").value();
        clip.y = atoi(valString.c_str());;
        walk_clips[Sprite::DOWN_LEFT_2] = clip;
        
        valString = root.child("WalkClips").child("DOWN_LEFT_3").attribute("x").value();
        clip.x = atoi(valString.c_str());;
        valString = root.child("WalkClips").child("DOWN_LEFT_3").attribute("y").value();
        clip.y = atoi(valString.c_str());;
        walk_clips[Sprite::DOWN_LEFT_3] = clip;
        
        valString = root.child("WalkClips").child("DOWN_LEFT_4").attribute("x").value();
        clip.x = atoi(valString.c_str());;
        valString = root.child("WalkClips").child("DOWN_LEFT_4").attribute("y").value();
        clip.y = atoi(valString.c_str());;
        walk_clips[Sprite::DOWN_LEFT_4] = clip;
        
        valString = root.child("WalkClips").child("DOWN_1").attribute("x").value();
        clip.x = atoi(valString.c_str());;
        valString = root.child("WalkClips").child("DOWN_1").attribute("y").value();
        clip.y = atoi(valString.c_str());;
        walk_clips[Sprite::DOWN_1] = clip;
        
        valString = root.child("WalkClips").child("DOWN_2").attribute("x").value();
        clip.x = atoi(valString.c_str());;
        valString = root.child("WalkClips").child("DOWN_2").attribute("y").value();
        clip.y = atoi(valString.c_str());;
        walk_clips[Sprite::DOWN_2] = clip;
        
        valString = root.child("WalkClips").child("UP_1").attribute("x").value();
        clip.x = atoi(valString.c_str());;
        valString = root.child("WalkClips").child("UP_1").attribute("y").value();
        clip.y = atoi(valString.c_str());;
        walk_clips[Sprite::DOWN_3] = clip;
        
        valString = root.child("WalkClips").child("DOWN_4").attribute("x").value();
        clip.x = atoi(valString.c_str());;
        valString = root.child("WalkClips").child("DOWN_4").attribute("y").value();
        clip.y = atoi(valString.c_str());;
        walk_clips[Sprite::DOWN_4] = clip;
        
        valString = root.child("WalkClips").child("RIGHT_1").attribute("x").value();
        clip.x = atoi(valString.c_str());;
        valString = root.child("WalkClips").child("RIGHT_1").attribute("y").value();
        clip.y = atoi(valString.c_str());;
        walk_clips[Sprite::RIGHT_1] = clip;
        
        valString = root.child("WalkClips").child("RIGHT_2").attribute("x").value();
        clip.x = atoi(valString.c_str());;
        valString = root.child("WalkClips").child("RIGHT_2").attribute("y").value();
        clip.y = atoi(valString.c_str());;
        walk_clips[Sprite::RIGHT_2] = clip;
        
        valString = root.child("WalkClips").child("RIGHT_3").attribute("x").value();
        clip.x = atoi(valString.c_str());;
        valString = root.child("WalkClips").child("RIGHT_3").attribute("y").value();
        clip.y = atoi(valString.c_str());;
        walk_clips[Sprite::RIGHT_3] = clip;
        
        valString = root.child("WalkClips").child("RIGHT_4").attribute("x").value();
        clip.x = atoi(valString.c_str());;
        valString = root.child("WalkClips").child("RIGHT_4").attribute("y").value();
        clip.y = atoi(valString.c_str());;
        walk_clips[Sprite::RIGHT_4] = clip;
        
        valString = root.child("WalkClips").child("DOWN_RIGHT_1").attribute("x").value();
        clip.x = atoi(valString.c_str());;
        valString = root.child("WalkClips").child("DOWN_RIGHT_1").attribute("y").value();
        clip.y = atoi(valString.c_str());;
        walk_clips[Sprite::DOWN_RIGHT_1] = clip;
        
        valString = root.child("WalkClips").child("DOWN_RIGHT_2").attribute("x").value();
        clip.x = atoi(valString.c_str());;
        valString = root.child("WalkClips").child("DOWN_RIGHT_2").attribute("y").value();
        clip.y = atoi(valString.c_str());;
        walk_clips[Sprite::DOWN_RIGHT_2] = clip;
        
        valString = root.child("WalkClips").child("DOWN_RIGHT_3").attribute("x").value();
        clip.x = atoi(valString.c_str());;
        valString = root.child("WalkClips").child("DOWN_RIGHT_3").attribute("y").value();
        clip.y = atoi(valString.c_str());;
        walk_clips[Sprite::DOWN_RIGHT_3] = clip;
        
        valString = root.child("WalkClips").child("DOWN_RIGHT_4").attribute("x").value();
        clip.x = atoi(valString.c_str());;
        valString = root.child("WalkClips").child("DOWN_RIGHT_4").attribute("y").value();
        clip.y = atoi(valString.c_str());;
        walk_clips[Sprite::DOWN_RIGHT_4] = clip;
        
        valString = root.child("WalkClips").child("UP_RIGHT_1").attribute("x").value();
        clip.x = atoi(valString.c_str());;
        valString = root.child("WalkClips").child("UP_RIGHT_1").attribute("y").value();
        clip.y = atoi(valString.c_str());;
        walk_clips[Sprite::UP_RIGHT_1] = clip;
        
        valString = root.child("WalkClips").child("UP_RIGHT_2").attribute("x").value();
        clip.x = atoi(valString.c_str());;
        valString = root.child("WalkClips").child("UP_RIGHT_2").attribute("y").value();
        clip.y = atoi(valString.c_str());;
        walk_clips[Sprite::UP_RIGHT_2] = clip;
        
        valString = root.child("WalkClips").child("UP_RIGHT_3").attribute("x").value();
        clip.x = atoi(valString.c_str());;
        valString = root.child("WalkClips").child("UP_RIGHT_3").attribute("y").value();
        clip.y = atoi(valString.c_str());;
        walk_clips[Sprite::UP_RIGHT_3] = clip;
        
        valString = root.child("WalkClips").child("UP_RIGHT_4").attribute("x").value();
        clip.x = atoi(valString.c_str());;
        valString = root.child("WalkClips").child("UP_RIGHT_4").attribute("y").value();
        clip.y = atoi(valString.c_str());;
        walk_clips[Sprite::UP_RIGHT_4] = clip;
    }
    
    return true;
}

void freeScriptedEnemyVisualMedia(LTexture* cTexture)
{
    if(cTexture != nullptr)
    {
        cTexture = nullptr;
    }
}

bool setEnemyTypeAttributes(EnemyContent* thisEnemyContent, std::string xml_file_path)
{
	// Create empty XML document within memory
	pugi::xml_document doc;

	// Load XML file into memory
	// Remark: to fully read declaration entries you have to specify
	// "pugi::parse_declaration"
	pugi::xml_parse_result result = doc.load_file(xml_file_path.c_str(),
											pugi::parse_default);
	if (!result)
	{
		std::cout << "Parse error: " << result.description() << ", character pos= " << result.offset;
		return false;
	}
    
    pugi::xml_node root = doc.child("EnemyRoot");
    
    std::string healthStr = root.child("Attributes").attribute("health").value();
	std::string speedStr = root.child("Attributes").attribute("speed").value();
	
	thisEnemyContent->health = std::stoi(healthStr);
	thisEnemyContent->speed = std::stof(speedStr);
	
	return true;
}


