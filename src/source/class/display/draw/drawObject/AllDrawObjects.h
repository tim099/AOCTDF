#ifndef SOURCE_CLASS_DISPLAY_DRAW_OBJECT_DRAWDATA_ALLDRAWOBJECTS_H_
#define SOURCE_CLASS_DISPLAY_DRAW_OBJECT_DRAWDATA_ALLDRAWOBJECTS_H_
#include "class/display/draw/drawObject/DrawObjectMap.h"
#include "class/tim/map/MapTree.h"
#include "class/tim/globalObject/GlobalObject.h"
namespace Display{
class AllDrawObjects: public Tim::MapTree<DrawObjectMap, DrawObject>,
		public Tim::GlobalObject<AllDrawObjects>,
		public Tim::Parser {
public:
	AllDrawObjects();
	AllDrawObjects(std::string path,std::string folder_path="");
	virtual ~AllDrawObjects();

protected:
	virtual inline std::string Script_name() const {
		return "#LOAD_ALL_DRAWOBJECTS_SCRIPT";
	}
	virtual void Parse_Script(std::istream &is, std::string &line);
	virtual void Parse_Script(std::ostream &os);

	virtual void Parse_Header(std::istream &is, std::string &line);
	virtual void Parse_Header(std::ostream &os);

	virtual void Parse_map(std::istream &is);
	virtual void Parse_dir(std::istream &is);
	std::string folder_path,path;
};
}
#endif /* SOURCE_CLASS_DISPLAY_DRAW_OBJECT_DRAWDATA_ALLDRAWOBJECTS_H_ */
