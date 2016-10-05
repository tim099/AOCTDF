#include "class/display/texture/TextureCreator.h"

#include "class/display/texture/texture3D/cubemap/TextureCubeMap.h"
#include "class/display/texture/texture3D/Texture2DArr/Texture2DArr.h"
#include "class/display/texture/texture2D/Texture2D.h"


namespace Display {

TextureCreator::TextureCreator() {
	push(new Texture2D());
	push(new Texture2DArr());
	push(new TextureCubeMap());
}
TextureCreator::~TextureCreator() {

}
Texture* TextureCreator::create(std::string type_name){
	if (!creator.get(type_name)) {
		std::cerr << "Texture name:" << type_name
				<< " not exist in this TextureCreator" << std::endl;
		return 0;
	}
	return creator.get(type_name)->clone();
}
void TextureCreator::push(Texture* obj){
	creator.push(obj->get_type(),obj);
}
} /* namespace Display */
