string hash_file(string str) {
    string hash = "";
    return hash;
}
inline bool exists_test3 (const std::string& name) {
    struct stat buffer;
    return (stat (name.c_str(), &buffer) == 0);
}

void git_status()
{
    string version = cwd+"/git/version.txt";
	ifstream in(version);
	string v_no;
	in >> v_no;
	in.close();

    unordered_map<string,string > mp;
	
    string idxfile = cwd+"/git/version/v_"+v_no + "/index.txt";
    ifstream index(idxfile);
	string line;
	while(getline(index,line))
	{
		vector<string> parts = stringToken(line,' ');
		mp[parts[0]]=parts[1];
	}
	index.close();

    vector<string> untracked;
    vector<string> newfile;
    vector<string> modified;

    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir (cwd.c_str())) != NULL) {
        /* print all the files and directories within directory */
        while ((ent = readdir (dir)) != NULL) {
            // printf ("%s\n", ent->d_name);
            string current = ent->d_name;
            string checkfile;
            checkfile=cwd+"/"+current;
            struct stat statbuf;
            stat(&current[0], &statbuf);
            if (statbuf.st_mode & S_IFDIR) //True: Directory
            {
                continue;
            }

            if (exists_test3(checkfile)) 
            {
                //cout<<endl<<checkfile<<endl;
                // auto it = map1.find(current);
                if (mp.find(current) == mp.end()) {
                    cout << RED("untracked : " )<< current << endl;
                    untracked.push_back(current);
                    // cout<<endl;
                } 
                else 
                {
                    string sha1 = get_sha(checkfile);
                    //cout<<sha1<<endl;
                    if (mp[current] == sha1) 
                    {
                        cout <<GREEN( "Tracked : " )<< current << endl;
                        newfile.push_back(current);
                    } 
                    else 
                    {
                        cout << YELLOW("modified : " )<< current << endl;
                        modified.push_back(current);
                    }
                }
            }
        }
    }
}
