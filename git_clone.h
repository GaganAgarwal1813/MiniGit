void create_remote_repo(string remote_repo_path) // for creating the remote repo
{

    string remote_directory = remote_repo_path;

    // creating remote reposirtory if doesn't exists
    string push_dir = remote_directory;
    struct stat sb;
    stat(push_dir.c_str(), &sb);
    bool isdir = S_ISDIR(sb.st_mode);
    if (!isdir) //If the remote repo does not exists
    {
        // creating push directory in the specified path
        check(mkdir(push_dir.c_str(), 0777), "unable to create directory");
    }
    else
    {
        cout << RED("remote repository already exists") << endl;
        return;
    }

    git_init(remote_directory);

    // updating add_commit file
    string add_commit = remote_directory + "/git/add_commit.txt";
    ofstream add_commit_file(add_commit.c_str());
    add_commit_file << "00 " << remote_directory;
    add_commit_file.close();

    cout << YELLOW_B("\t\tCreated remote repository at the location ") << remote_repo_path << endl;
}
void git_clone(string remote_repo_path)
{

    string remote_directory = remote_repo_path;

    if (!check_dir(remote_directory))
    {
        cout << RED("Remote repository doesn't exists") << endl;
        return;
    }

    // copying from remote repository
    vector<string> filenames = getAndSortFiles(remote_directory);

    for (string fname : filenames)
    {
        string fpath = remote_directory + "/" + fname;
        string bash_cmd = "cp " + fpath + " " + cwd + "/" + fname;
        system(&bash_cmd[0]);
    }

    // copying the git folder
    if (check_dir(cwd + "/git"))
    {
        remove_git(cwd + "/git");
        copy_git(remote_directory + "/git", cwd);
    }
    else
    {
        copy_git(remote_directory + "/git", cwd);
    }

    cout << YELLOW_B("\t\tCloned the repository successfully") << endl;
}