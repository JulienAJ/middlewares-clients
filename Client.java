import java.util.Arrays;
import java.io.*;
import Player.*;

public class Client
{

	public static void main(String[] args)
	{

		int status = 0;
		Ice.Communicator ic = null;

		try
		{

			ic = Ice.Util.initialize(args);
			//Ice.ObjectPrx base = ic.stringToProxy("Server:default -h datdroplet.ovh -p 10000");
			Ice.ObjectPrx base = ic.stringToProxy("Server:default -p 10000");
			Player.ServerPrx server = Player.ServerPrxHelper.checkedCast(base);
			if (server == null)
				throw new Error("Invalid proxy");


			int choice = 0;
			BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
			while(true)
			{
				choice = 0;
				while(choice < 1 || choice > 7)
				{
					System.out.println("Quelle action voulez-vous executer ?");
					System.out.println("1 - Ajouter un morceau");
					System.out.println("2 - Supprimer un morceau");
					System.out.println("3 - Rechercher par titre");
					System.out.println("4 - Rechercher par artiste");
					System.out.println("5 - Lister les morceaux");
					System.out.println("6 - Lancer un streaming");
					System.out.println("7 - Quitter");
					choice = Integer.parseInt(br.readLine());
				}

				if(choice == 1)
				{
					System.out.print("Entrez le titre : ");
					String title = br.readLine();

					System.out.print("Entrez l'artiste : ");
					String artist = br.readLine();

					System.out.print("Entrez le chemin : ");
					String path = br.readLine();

					server.addSong(title, artist, path);
				}

				else if(choice == 2)
				{
					System.out.print("Entrez le chemin : ");
					String path = br.readLine();

					server.remove(path);
				}
				else if(choice == 3)
				{
					System.out.print("Entrez le titre : ");
					String title = br.readLine();

					song[] results = server.findByTitle(title);
					System.out.println("Resultats : ");
					if(results.length == 0)
						System.out.println("Aucun resultat");
					for(int i = 0; i < results.length; i++)
					{
						System.out.println(results[i].name + " par " + results[i].artist + " : " + results[i].path);
					}
				}
				else if(choice == 4)
				{
					System.out.print("Entrez l'artiste : ");
					String artist = br.readLine();

					song[] results = server.findByArtist(artist);
					System.out.println("Resultats : ");
					if(results.length == 0)
						System.out.println("Aucun resultat");
					for(int i = 0; i < results.length; i++)
					{
						System.out.println(results[i].name + " par " + results[i].artist + " : " + results[i].path);
					}
				}
				else if(choice == 5)
				{
					song[] results = server.list();
					System.out.println("Contenu de la base : ");
					if(results.length == 0)
						System.out.println("Base vide");

					for(int i = 0; i < results.length; i++)
					{
						System.out.println(results[i].name + " par " + results[i].artist + " : " + results[i].path);
					}
				}
				else if(choice == 6)
				{
					String myId = server.start("go.mp3");
					server.play(myId);
					System.out.println("OUI : " + myId);
				}
				else
					break;
			}
			br.close();
		}
		catch (Ice.LocalException e)
		{

			e.printStackTrace();
			status = 1;
		}
		catch (Exception e)
		{
			System.err.println(e.getMessage());
			status = 1;
		}

		if (ic != null) {

			try {

				ic.destroy();
			} catch (Exception e) {

				System.err.println(e.getMessage());
				status = 1;
			}
		}
		System.exit(status);
	}
}
