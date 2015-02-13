<?php
require 'Ice.php';
require 'server.php';

$ic = null;
try
{

	$ic = Ice_initialize();
	$base = $ic->stringToProxy("Server:default -p 10000");
	$server = Player_ServerPrxHelper::checkedCast($base);
	if(!$server)
		throw new RuntimeException("Invalid proxy");
	
	// CONTENT
	
	while(true)
	{
		$choice = 0;
		while($choice < 1 || $choice > 6)
		{
			print "Quelle action voulez-vous executer ? \n";
			print "1 - Ajouter un morceau \n";
			print "2 - Supprimer un morceau \n";
			print "3 - Rechercher par titre \n";
			print "4 - Rechercher par artiste \n";
			print "5 - Lister les morceaux \n";
			print "6 - Quitter \n";
			fscanf(STDIN, "%d\n", $choice);
		}

		if($choice == 1)
		{
			print "Entrez le titre : ";
			$title = trim(fgets(STDIN));

			print "Entrez l'artiste : ";
			$artist = trim(fgets(STDIN));

			print "Entrez le chemin : ";
			$path = trim(fgets(STDIN));

			$server->addSong($title, $artist, $path);
		}

		else if($choice == 2)
		{
			print "Entrez le chemin : ";
			$path = trim(fgets(STDIN));

			$server->remove($path);
		}
		else if($choice == 3)
		{
			print "Entrez le titre : ";
			$title = trim(fgets(STDIN));

			$results = $server->findByTitle($title);
			print "Resultats :  \n";
			if(count($results) == 0)
				print "Aucun resultat \n";
			foreach($results as $result)
			{
				print $result->name." par ".$result->artist." : ".$result->path."\n";
			}
		}
		else if($choice == 4)
		{
			print "Entrez l'artiste : ";
			$artist = trim(fgets(STDIN));

			$results = $server->findByArtist($artist);
			print "Resultats :  \n";
			if(count($results) == 0)
				print "Aucun resultat \n";
			foreach($results as $result)
			{
				print $result->name." par ".$result->artist." : ".$result->path."\n";
			}
		}
		else if($choice == 5)
		{
			$results = $server->_list();
			print "Contenu de la base :  \n";

			foreach($results as $result)
			{
				print $result->name." par ".$result->artist." : ".$result->path."\n";
			}
		}
		else
			break;
	}
}
catch(Exception $ex)
{
	    echo $ex;
}

if($ic)
{
	try
	{
		$ic->destroy();
	}
	catch(Exception $ex)
	{
		echo $ex;
	}
}
?>
