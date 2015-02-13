#include <Ice/Ice.h>
#include <iostream>
#include "server.h"
#include "songDB.hpp"
using namespace std;

class ConcreteServer : public Server
{

	private:
		songDB db;

	public:

		virtual void addSong(const std::string& name, const std::string& artist, const std::string& path, const Ice::Current&)
		{
			std::cout << "AJOUT DE MORCEAU" << std::endl;
			db.addSong(name, artist, path);
			std::cout << name << " par " << artist << " ajoute" << std::endl;
		}

		virtual void remove(const std::string& path, const Ice::Current&)
		{
			std::cout << "SUPPRESSION" << std::endl;
			db.deleteSong(path);
			std::cout << path << " supprime" << std::endl;
		}

		virtual Player::songSeq findByTitle(const std::string& title, const Ice::Current&)
		{
			std::cout << "Recherde de " << title << " dans le titre"<< std::endl;
			return db.findByTitle(title);
		}

		virtual Player::songSeq findByArtist(const std::string& artist, const Ice::Current&)
		{
			std::cout << "Recherde de " << artist << " dans l'artiste'"<< std::endl;
			return db.findByArtist(artist);
		}

		virtual Player::songSeq list(const Ice::Current&)
		{
			std::cout << "Affichage de la liste des morceaux" << std::endl;
			return db.list();
		}
};

int main(int argc, char **argv)
{

	int status = 0;
	Ice::CommunicatorPtr ic;

	try
	{
		ic = Ice::initialize(argc, argv);
		Ice::ObjectAdapterPtr adapter = ic->createObjectAdapterWithEndpoints("ServerAdapter", "default -p 10000");
		Ice::ObjectPtr object = new ConcreteServer;
		adapter->add(object, ic->stringToIdentity("Server"));
		adapter->activate();
		ic->waitForShutdown();
	}
	catch (const Ice::Exception& e)
	{
		cerr << e << endl;
		status = 1;
	}
	catch (...)
	{
		status = 1;
	}

	if (ic)
	{
		try
		{
			ic->destroy();
		}
		catch (const Ice::Exception& e)
		{
			cerr << e << endl;
			status = 1;
		}
	}

	return status;
}
