#ifndef RESOURCEMGR_H
#define RESOURCEMGR_H
#include <map>
#include <string>

class ResourceMgr
{
public:
	ResourceMgr() = default;
	~ResourceMgr() = default;
	bool LoadResource(const std::string& name); 
	unsigned int GetResourceID(const std::string& name);
private:
	std::map<std::string, unsigned int> m_Textures;
	unsigned int m_ResourcesCount = 0;
};

#endif /* end of include guard RESOURCEMGR_H */

