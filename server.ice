module Player
{
	struct song
	{
		string name;
		string artist;
		string path;
	};

	sequence<song> songSeq;

	interface Server
	{
		void addSong(string name, string artist, string path);
		void remove(string path);
		songSeq findByTitle(string name);
		songSeq findByArtist(string artist);
		songSeq list();
	};
};
