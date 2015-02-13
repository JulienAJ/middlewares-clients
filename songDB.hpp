#pragma once
#include <string>
#include <vector>
#include "server.h"
using namespace Player;

class songDB
{
	private:
		std::vector<song> songTab;

		std::vector<song> search(std::vector<std::string> args, std::vector<std::string> values);

	public:

		void addSong(song s);
		void addSong(std::string name, std::string artist, std::string path);

		void deleteSong(std::string path);

		std::vector<song> list();
		std::vector<song> findByTitle(std::string title);
		std::vector<song> findByArtist(std::string artist);
		//std::vector<song> find(std::string searchKey);
};
