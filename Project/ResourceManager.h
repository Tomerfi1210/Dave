#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Keys.h"
//#include <SFML/Audio.hpp>
//#include <unordered_map>
//#include <memory>
//#include <exception>
//#include <unordered_set>

class ResourceManager
{
public:
	static ResourceManager& getInstance();
	sf::Texture * getTexture(const Object_t & index);//texture of every object in the game.
private:
	ResourceManager();
	~ResourceManager() {};
	std::vector<sf::Texture>m_photo;
	std::vector<sf::Texture>m_objects;
	sf::Font m_font;
};
//template class that can work for different resource types(not sf::music)
//template <class Key, class ResourceType>
//class ResourceManager
//{
//public:
//	ResourceManager(const ResourceManager&) = delete;
//	ResourceManager operator=(const ResourceManager&) = delete;
//	//const so it is not changed
//	const ResourceType& get(const Key&)const;
//	void load(const Key& id, const std::string& file);
//private:
//	ResourceManager();
//	~ResourceManager() = default;
//
//	std::unordered_map<Key, ResourceType> m_map;
//};
////-----------------------------------------------------------
//template <class Key, class ResourceType>
//const ResourceType& ResourceManager<Key, ResourceType>::get(const Key& id) const
//{
//	auto it = m_map.find(id);
//	if (it == m_map.end())
//		throw std::runtime_error("Bad Id, no resource found");
//	return *it->second;
//}
////-----------------------------------------------------------
//template<class Key, class ResourceType>
//inline void ResourceManager<Key, ResourceType>::load(const Key& id, const std::string& filename)
//{
//	auto resource = std::make_shared<ResourceType>;
//	if (!resource->loadFromFile(filename))
//		throw std::runtime_error("failed to load " + filename);
//
//	auto pair = std::make_pair(id, std::move(resource));
//	auto inserted = m_map.insert(pair);
//	if (!inserted) throw std::runtime_error("ResourceManager - failed to insert ");
//}
//
////typedefs for the options of this class
//using TextureManager = ResourceManager<std::string, sf::Texture>;
//using FontManager = ResourceManager<std::string, sf::Font>;
//using SoundManager = ResourceManager<std::string, sf::SoundBuffer>;
////----------------------------------------------------------------------------------------
//
//
//template <class Key>
//class MusicPlayer
//{
//public:
//	static MusicPlayer& getInstance()
//	{
//		//creating static one time instance of this class
//		static MusicPlayer instance;
//		return instance;
//	}
//	MusicPlayer(const MusicPlayer&) = delete;
//	MusicPlayer operator=(const MusicPlayer&) = delete;
//	void play(const Key&);
//	void stop();
//private:
//	//for the current music
//	MusicPlayer() = default;
//	sf::Music m_music;
//	std::map<Key, std::string> m_fileNames;
//};
//
//
//
//template<class Key>
//inline void MusicPlayer<Key>::play(const Key&k)
//{
//	const std::string filename = m_fileNames[k];
//	if (!m_music.openFromFile(filename))
//		throw std::runtime_error("Music " + filename + " could not be loaded.");
//
//	m_music.setLoop(true);
//	m_music.play();
//}
//
//template<class Key>
//inline void MusicPlayer<Key>::stop()
//{
//	m_music.stop();
//}
//
//
//
//
//
////---------------------------------------------------------------------------------------c-
//template <class Key>
//class SoundPlayer
//{
//public:
//	static SoundPlayer& getInstance()
//	{
//		static SoundManager sm;
//		static SoundPlayer instance(sm);
//		return instance;
//	}
//	void play(const Key&);
//	void clear_ended_sounds();
//private:
//	//make singleton
//	SoundPlayer(SoundManager& sm);
//	SoundPlayer(const SoundPlayer&) = delete;
//	SoundPlayer operator=(const SoundPlayer&) = delete;
//	SoundManager m_sound_manager;
//	std::unordered_multiset<sf::Sound> m_sounds;
//};
//
//template <class Key>
//void SoundPlayer<Key>::clear_ended_sounds()
//{
//	auto it = std::remove_if(m_sounds.begin(), m_sounds.end(), [](const auto & sound) {sound->getStatus == sf::Sound::Stopped; });
//	m_sounds.erase(it, m_sounds.end());
//}
//
//template <class Key>
//void SoundPlayer<Key>::play(const Key& key)
//{
//	//TODO there might be a problem here, playing sound then putting in copy
//	auto t = sf::Sound(m_sound_manager.get(key));
//	t.play();
//	m_sounds.insert(t);
//}
//
//template <class Key>
//SoundPlayer<Key>::SoundPlayer(SoundManager& sm) :m_sound_manager(sm)
//{
//	m_sound_manager.load("tmp", "tmp.wav");
//}