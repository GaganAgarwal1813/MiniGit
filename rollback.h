void git_rollback(string rollVersion)
{
	string version = cwd+"/git/version.txt";
	
	ifstream in(version);
	string v_no;
	in >> v_no;
	in.close();

	int newNum = (stoi(v_no)+1);
	string newVersion = to_string(stoi(v_no)+1);

	if(to_string(stoi(rollVersion))==v_no)
	{
		cout<<"You are on same version!!!";
		return;
	}
	else if(stoi(rollVersion)+1 >= stoi(v_no))
	{
		cout<<"Invalid Version!!!";
		return;
	}


	string newDirectory = cwd + "/git/version/v_" + newVersion;
    check(mkdir(newDirectory.c_str(), 0777), "unable to create directory");


    // copying index file contents to new index file
    string pPath = cwd + "/git/version/v_" + rollVersion;
    string prevIndexPath = cwd + "/git/version/v_" + rollVersion + "/index.txt";
    string newIndexPath = cwd + "/git/version/v_" + newVersion + "/index.txt";
    copyFile(prevIndexPath, newIndexPath);

	if(v_no=="1")
	{
		cout<<"No previous Vesion Present";
		return;
	}

	int vnum = stoi(v_no);

	//string removePath = cwd+"/git/version/v_"+v_no; 
	//string prevVersion = to_string(vnum-1);


	string path1 =  cwd+"/git/version/v_"+rollVersion;
	string ind_file = path1 + "/index.txt";

	LOGY("CWD:"+cwd);
	LOGY("Path1 : "+path1);
	LOGY("index file:"+ind_file);
	LOGY("New Version"+newVersion);

	unordered_map<string, vector<string> > mmap;
	ifstream index(ind_file);

	string line;

	// generating token from index File
	while(getline(index,line))
	{
		
		vector<string> parts = stringToken(line,' ');
		int len=parts.size();
		LOGP("----->"+parts[0]+" "+parts[1]);				
		for(int i=1;i<len;i++)
		{
			mmap[parts[0]].push_back(parts[i]);
			LOG("	|------>"+parts[i]);
		}

	}
	index.close();

	struct stat statbuf,checkFile;  
	struct dirent **namelist=NULL;
	int n = scandir(&cwd[0], &namelist, NULL, alphasort);
	vector<string> currDirItem;


	for(int i=0;i<n;i++)
	{
		string filename(namelist[i]->d_name);
	      stat(&filename[0], &statbuf);

	    if(statbuf.st_mode & S_IFDIR)//True: Directory
	        {
	            continue;
	        }
	        else
	        {
			    if(mmap.find(filename)==mmap.end())
		    	{
		    		LOGR(filename + " removed as not present in previous version!!");
		            string cmd="rm "+filename;
		            system(&cmd[0]);
		            LOGC(cmd);
		    	}
    		}
	}

	for(auto it : mmap)
	   {
	   		string filename=it.first;
	   		//string filename(namelist[i]->d_name);
	       	stat(&filename[0], &statbuf);
	       	//currDirItem.push_back(filename);
	       	

	       	if(statbuf.st_mode & S_IFDIR)//True: Directory
	        {
	            continue;
	        }
	        else
	        {
				
				LOG(filename);

				vector<string> list(mmap[filename].begin()+3,mmap[filename].end());
				vector<string> cversion;
				for(string s:list)
				{
					if(stoi(s)<=stoi(rollVersion))
						cversion.push_back(s);
					else
						break;
				}
				cout<<"size"<<" "<<cversion.size()<<endl;
				for(string s : cversion)
				{
					cout<<s<<" ";
				}

				LOG("Calling retrieve File!!!");
				retrieve_file(v_no,filename,cversion,path1);
	        }

	   }

	   n = scandir(&pPath[0], &namelist, NULL, alphasort);

		for(int i=0;i<n;i++)
		{
			string filename(namelist[i]->d_name);
		      stat(&filename[0], &statbuf);

		    if((statbuf.st_mode & S_IFDIR) || filename=="index.txt")//True: Directory
	        {
	            continue;
	        }
	        else
	        {
				string prevPath = cwd + "/git/version/v_" + rollVersion + "/"+filename;//"/index.txt";
			    string newPath = cwd + "/git/version/v_" + to_string(stoi(v_no) + 1) + "/" +filename;//"/index.txt";
			    copyFile(prevPath, newPath);
			    LOGY("Copied File from Version Roll "<<rollVersion<<" to new Version"<<to_string(vnum+1));

	        }
	        
		}

	   //string cmd="rm -r "+removePath;
	   //system(&cmd[0]);

	   	string prevVersion = to_string(vnum+1);

		ofstream out(version, ios::trunc);
		out<<prevVersion;
		out.close();



	   cout<<GREEN("You are succesfully Rollbacked the Change!!! Now you are in version "+ newVersion);

}