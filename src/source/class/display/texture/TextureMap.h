#ifndef TEXTUREMAP_H_
#define TEXTUREMAP_H_

#include "class/display/texture/Texture.h"
#include "class/tim/parser/Parser.h"
#include "class/tim/map/MapContainer.h"
#include <string>
#include <map>
namespace Display{
class TextureMap : public Tim::Parser{
public:
	TextureMap(std::string path="NULL",std::string folder_path="");
	virtual ~TextureMap();
	std::string get_name()const;
	void set_name(std::string name);

	void push(std::string tex_name,Texture* tex);
	Texture* get(std::string tex_name);
	std::string folder_path;
	std::string path;
protected:
	virtual inline std::string Script_name()const{
		return "#LOAD_TEXTUREMAP_SCRIPT";
	}
	virtual void Parse_Script(std::istream &is,std::string &line);
	virtual void Parse_Script(std::ostream &os);
	virtual void Parse_Header(std::istream &is,std::string &line);
	virtual void Parse_Header(std::ostream &os);
	Tim::MapContainer<std::string,Texture>textures;

	std::string name;
};
}
#endif /* TEXTUREMAP_H_ */
