#include "ResourceManager.h"

ResourceManager & ResourceManager::getInstance()
{
	static ResourceManager instance;

	return instance;
}

sf::Texture * ResourceManager::getTexture(const Object_t & index)
{
	return &m_objects.at(index);
}

ResourceManager::ResourceManager()
{
	m_objects.resize(Max);
	m_photo.resize(Max_b);

	const std::string sname = "Images/image";
	const std::string bname = "Images/photo";
	const std::string picType = ".png";
	std::string name;

	for (int i = 0; i < Max; i++)
	{
		name = sname + std::to_string(i) + picType;
		m_objects[i].loadFromFile(name);
	}

	/*for (int i = 0; i < 1; i++)
	{
		name = bname + std::to_string(i) + picType;
		m_photo[i].loadFromFile(name);
	}

	m_font.loadFromFile("font/GOUDYSTO.ttf");*/

}
