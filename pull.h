void git_pull()
{
    // to get remote repository path
    string add_commit = cwd + "/git/add_commit.txt";
    ifstream add_commit_file;
    add_commit_file.open(add_commit.c_str(), ios::in);
    string check_bit, push_directory;
    getline(add_commit_file, check_bit, ' ');
    getline(add_commit_file, push_directory, ' ');
    add_commit_file.close();

    string remote_dir = push_directory;
    string pushFile = cwd + "/git/push_index.txt";

    // getting filenames and their sha of remote repo
    string remote_push_index_file = push_directory + "/git/push_index.txt";
    ifstream infile;
    infile.open(remote_push_index_file, ios::in);
    unordered_map<string, string> remote_fileDetails;

    string line;

    while (getline(infile, line))
    {
        string fname, sha;
        stringstream ss(line);
        getline(ss, fname, ' ');
        getline(ss, sha, ' ');
        remote_fileDetails[fname] = sha;
    }
    infile.close();

    // getting filedetails of local repo
    vector<string> filenames = getAndSortFiles(cwd);
    unordered_map<string, string> localfileDetails;

    for (string fname : filenames)
    {
        string fpath = cwd + "/" + fname;
        string sha = get_sha(fpath);
        localfileDetails[fname] = sha;
    }



    for (auto fname : remote_fileDetails)
    {
        // if the file is present in remote repo but not in local repo
        // copying from remote to local repo
        if (localfileDetails.find(fname.first) == localfileDetails.end())
        {
            string fpath = remote_dir + "/" + fname.first;
            string bash_cmd = "cp " + fpath + " " + cwd + "/" + fname.first;
            system(&bash_cmd[0]);
            LOGC("Command Executed : " + bash_cmd);
            fpath = cwd + "/" + fname.first;
            localfileDetails[fname.first] = get_sha(fpath);
        }
        else
        {
            // if sha is not matching then replacing the file with remote repo file
            if (localfileDetails[fname.first] != remote_fileDetails[fname.first])
            {
                string fpath = cwd + "/" + fname.first;
                remove(fpath.c_str());
                fpath = remote_dir + "/" + fname.first;
                string bash_cmd = "cp " + fpath + " " + cwd + "/" + fname.first;
                LOGC("Command Executed : " + bash_cmd);
                system(&bash_cmd[0]);
                fpath = cwd + "/" + fname.first;
                localfileDetails[fname.first] = get_sha(fpath);
            }
        }
    }

    // upating the push_index file with filename->sha
    ofstream push_file(pushFile.c_str());
    for (auto name : localfileDetails)
        push_file << name.first << " " << name.second << "\n";
    push_file.close();

    update_remote_git(push_directory,cwd);

    cout << YELLOW_B("\t\tPulled Successfully!!!") << endl;
}