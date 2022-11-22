void getdiff(string vno, string filename, vector<string> list1, string path1)
{

    string version = cwd+"/git/version.txt";
    
    ifstream in(version);
    string v_no;
    in >> v_no;
    in.close();
    vector<string> list(list1.begin()+3,list1.end());
    //no changes required to file in current version
    if(list.size()!=0  && (list[ list.size() -1 ] == v_no ) )
    {
    	list.pop_back();
    }

    //if this is the very first change
    if(list.size()==1)
    {
    	//path where the file introduced for the first time....
    	string parent_path = cwd + "/git/version/v_" + list[0] + "/"+filename;

    	string bash_cmd ="diff "+parent_path+" "+ cwd+"/"+filename;
    	system(&bash_cmd[0]);

    	LOGC("Command Executed : "+bash_cmd);
    }
    else
    {
		string parent_path = cwd + "/git/version/v_";
		string temp_file   = cwd + "/git/version/temp";

		// patch <parent_file> <changes file of prev version> ---------------------------
		string generate_file_cmd = "patch "+ parent_path + list[0] + "/" + filename + " " + parent_path + list[1] + "/" + filename + " -o " + temp_file + "2;";
        int i=2;

        while(i<list.size())
        {
            generate_file_cmd += "patch "+temp_file+to_string(i)+" "+parent_path+list[i]+"/"+filename+" -o "+temp_file+to_string(i+1)+";";
            i++;
        }

        LOG(CYAN(generate_file_cmd));

        system(&generate_file_cmd[0]);

        generate_file_cmd = "diff "+temp_file+to_string(i)+" "+cwd+"/"+filename;

        system(&generate_file_cmd[0]);
        LOG(CYAN(generate_file_cmd));
    }

}



void git_diff()
{
    string version = cwd+"/git/version.txt";
    
    ifstream in(version);
    string v_no;
    in >> v_no;
    in.close();

    string path1 =  cwd+"/git/version/v_"+v_no;
    string ind_file = path1 + "/index.txt";

    LOGY("CWD:"+cwd);
    LOGY("Path1 : "+path1);
    LOGY("index file:"+ind_file);

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
            LOG("   |------>"+parts[i]);
        }
    }
    index.close();

    struct stat statbuf,checkFile;  
    struct dirent **namelist=NULL;
    int n = scandir(&cwd[0], &namelist, NULL, alphasort);

    for(int i=0;i<n;i++)
       {
            string filename(namelist[i]->d_name);
            stat(namelist[i]->d_name, &statbuf);
            if(statbuf.st_mode & S_IFDIR)//True: Directory
            {
                continue;
            }
            else
            {
                // current object is file calculating sha
                string sha = get_sha(filename);
                


                if(mmap.find(filename)!=mmap.end())
                {
                    if(mmap[filename][0]!=sha)
                    {
                        LOGR(filename+" "+sha+" file is modified!!!");      
                        if(mmap[filename][1]==v_no);
                        else
                        {
                            LOG("Calling Fetch File!!!");

                            cout<<RED("\n\nmodified file : ")<<CYAN(filename)<<endl;
                            getdiff(v_no,filename,mmap[filename],path1);
                                                    
                        }


                    }


                }


                
            }

       }

}





void git_diff_file(string filename)
{
	string version = cwd+"/git/version.txt";
	
	ifstream in(version);
	string v_no;
	in >> v_no;
	in.close();

	string path1 =  cwd+"/git/version/v_"+v_no;
	string ind_file = path1 + "/index.txt";

	LOGY("CWD:"+cwd);
	LOGY("Path1 : "+path1);
	LOGY("index file:"+ind_file);

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
	
    
    string filepath=filename;               //Path of given file.
	struct stat statbuf,checkFile;
	stat(filepath.c_str(), &statbuf);
	cout<<filepath<<endl;
	if(statbuf.st_mode & S_IFDIR)//True: Directory
	{
	    //do nothing
	} 
	else
	{

	    // file exists , calculating sha of file
		string sha = get_sha(filepath);
	
		if(mmap.find(filename)!=mmap.end())
		{

			if(mmap[filename][0]!=sha)
			{	
				LOGR(filename+" "+sha+" file is modified!!!");		
				mmap[filename][0]=sha;
				if(mmap[filename][1]==v_no)
					copyFile(filename,path1+"/"+filename);
				else
				{
					LOG("Calling getdiff Function!!!");
					getdiff(v_no,filename,mmap[filename],path1);	        				  
                }
            }
        }
    }
}