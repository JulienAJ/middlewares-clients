#include <iostream>
#include <list>
#include <string>
#include <vector>
#include "songDB.hpp"
#include "server.h"
using namespace Player;

void songDB::addSong(song s)
{
	songTab.push_back(s);
}

void songDB::addSong(std::string name, std::string artist, std::string path)
{
	song s;
	s.name = name;
	s.artist = artist;
	s.path = path;

	this->addSong(s);
}

void songDB::deleteSong(std::string path)
{
	if(songTab.empty())
		return;

	std::vector<song>::iterator it;
	for(it = songTab.begin(); it != songTab.end(); ++it)
	{
		if(it->path.compare(path) == 0)
			it = songTab.erase(it);
		if(it == songTab.end())
			return;
	}
}

std::vector<song> songDB::list()
{
	return songTab;
}

std::vector<song> songDB::search(std::vector<std::string> args, std::vector<std::string> values)
{
	std::vector<song> returnVal;

	std::vector<std::string>::size_type size = args.size();
	bool nameSearch = false, artistSearch = false;
	std::string name, artist;
	for(size_t i = 0; i < size; i++)
	{
		if(args[i] == "name")
		{
			nameSearch = true;
			name = values[i];
		}
		else if(args[i] == "artist")
		{
			artistSearch = true;
			artist = values[i];
		}
	}

	std::vector<song>::size_type sizeT = songTab.size();
	for(size_t i = 0; i < sizeT; i++)
	{
		if(nameSearch && songTab[i].name.compare(name) != 0)
			continue;

		if(artistSearch && songTab[i].artist.compare(artist) != 0)
			continue;

		returnVal.push_back(songTab[i]);
	}

	return returnVal;
}

std::vector<song> songDB::findByTitle(std::string title)
{
	std::vector<std::string> args;
	args.push_back("name");
	std::vector<std::string> values;
	values.push_back(title);

	return search(args, values);
}

std::vector<song> songDB::findByArtist(std::string artist)
{
	std::vector<std::string> args;
	args.push_back("artist");
	std::vector<std::string> values;
	values.push_back(artist);

	return search(args, values);
}
