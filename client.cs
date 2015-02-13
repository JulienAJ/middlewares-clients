using System;
using Player;

public class Client
{

	public static void Main(string[] args)
	{

		int status = 0;
		Ice.Communicator ic = null;
		try
		{
			ic = Ice.Util.initialize(ref args);
			Ice.ObjectPrx obj = ic.stringToProxy("Server:default -p 10000");
			ServerPrx server = ServerPrxHelper.checkedCast(obj);
			if (server == null)
				throw new ApplicationException("Invalid proxy");

			// CONTENT
			int choice = 0;
			string temp;
			while(true)
			{
				choice = 0;
				while(choice < 1 || choice > 6)
				{
					Console.WriteLine("Quelle action voulez-vous executer ?");
					Console.WriteLine("1 - Ajouter un morceau");
					Console.WriteLine("2 - Supprimer un morceau");
					Console.WriteLine("3 - Rechercher par titre");
					Console.WriteLine("4 - Rechercher par artiste");
					Console.WriteLine("5 - Lister les morceaux");
					Console.WriteLine("6 - Quitter");
					temp = Console.ReadLine();
					choice = Convert.ToInt32(temp);
				}

				if(choice == 1)
				{
					Console.Write("Entrez le titre : ");
					string title = Console.ReadLine();

					Console.Write("Entrez l'artiste : ");
					string artist = Console.ReadLine();

					Console.Write("Entrez le chemin : ");
					string path = Console.ReadLine();

					server.addSong(title, artist, path);
				}

				else if(choice == 2)
				{
					Console.Write("Entrez le chemin : ");
					string path = Console.ReadLine();

					server.remove(path);
				}
				else if(choice == 3)
				{
					Console.Write("Entrez le titre : ");
					string title = Console.ReadLine();

					song[] results = server.findByTitle(title);
					Console.WriteLine("Resultats : ");
					if(results.Length == 0)
						Console.WriteLine("Aucun resultat");
					for(int i = 0; i < results.Length; i++)
					{
						Console.WriteLine(results[i].name + " par " + results[i].artist + " : " + results[i].path);
					}
				}
				else if(choice == 4)
				{
					Console.Write("Entrez l'artiste : ");
					string artist = Console.ReadLine();

					song[] results = server.findByArtist(artist);
					Console.WriteLine("Resultats : ");
					if(results.Length == 0)
						Console.WriteLine("Aucun resultat");
					for(int i = 0; i < results.Length; i++)
					{
						Console.WriteLine(results[i].name + " par " + results[i].artist + " : " + results[i].path);
					}
				}
				else if(choice == 5)
				{
					song[] results = server.list();
					Console.WriteLine("Contenu de la base : ");
					if(results.Length == 0)
						Console.WriteLine("Base vide");

					for(int i = 0; i < results.Length; i++)
					{
						Console.WriteLine(results[i].name + " par " + results[i].artist + " : " + results[i].path);
					}
				}
				else
					break;
			}
		}
		catch(Exception e)
		{
			Console.Error.WriteLine(e);
			status = 1;
		}
		if(ic != null)
		{
			try
			{
				ic.destroy();
			}
			catch(Exception e)
			{
				Console.Error.WriteLine(e);
				status = 1;
			}
		}
		Environment.Exit(status);
	}
}
