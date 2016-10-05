#ifndef SOURCE_CLASS_DISPLAY_TEXTURE_TEXTURECREATOR_H_
#define SOURCE_CLASS_DISPLAY_TEXTURE_TEXTURECREATOR_H_
#include "class/tim/map/MapContainer.h"
#include "class/tim/globalObject/Singleton.h"
#include "class/tim/globalObject/GlobalObject.h"
#include "class/display/texture/Texture.h"
namespace Display {

class TextureCreator : public Tim::Singleton<TextureCreator>{
public:
	TextureCreator();
	virtual ~TextureCreator();

	Texture* create(std::string type_name);
protected:
	void push(Texture* obj);
	Tim::MapContainer<std::string,Texture>creator;

};

} /* namespace Display */

#endif /* SOURCE_CLASS_DISPLAY_TEXTURE_TEXTURECREATOR_H_ */
