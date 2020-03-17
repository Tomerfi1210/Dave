#pragma once
#include <map>
#include <memory>
#include <SFML/Graphics.hpp>



template<typename T>
class Factory
{
public:
	static std::unique_ptr<T> create(const char& c, sf::Vector2f&); //gets the key and returns a pointer to new object
	static bool registerit(const char & name, std::unique_ptr<T>(*f)(sf::Vector2f &))
	{
		getMap().emplace(name, f); //insert into map
		return true;

	}
private:
	static std::map<char, std::unique_ptr<T>(*)(sf::Vector2f&)>& getMap() {
		static myMap m_map;
		return m_map;;
	}
	Factory() {};
	~Factory() {};
	
	using myMap = std::map<char, std::unique_ptr<T>(*)(sf::Vector2f&)>;
};

template<typename T>
inline std::unique_ptr<T> Factory<T>::create(const char& c, sf::Vector2f &place)
{
	auto it = getMap().find(c); //looking for cell in map
	if (it == getMap().end()) //if cell does not exist
		return nullptr;
	return it->second(place); //call the function that creates the pointer
}