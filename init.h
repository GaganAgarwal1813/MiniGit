void git_init(string path_of_dir)
{

    string path = path_of_dir + "/git/version/v_1";
    string idxfile = path + "/index.txt";
    string logfile = path_of_dir + "/git/log.txt";
    string versionfile = path_of_dir + "/git/version.txt";
    string add_commit = path_of_dir + "/git/add_commit.txt";
    string pushFile = path_of_dir + "/git/push_index.txt";

    string git_folder = path_of_dir + "/git";
    string git_version = path_of_dir + "/git/version";

    // creating the directories
    check(mkdir(git_folder.c_str(), 0777), "unable to create directory");
    check(mkdir(git_version.c_str(), 0777), "unable to create directory");
    check(mkdir(path.c_str(), 0777), "unable to create directory14");

    // creating log file
    ofstream log_file(logfile.c_str());
    log_file.close();

    // creating version.txt and writing the version as 1
    ofstream version_file(versionfile.c_str());
    version_file << "1";
    log_file.close();

    // creating index file
    ofstream index_file(idxfile.c_str());
    index_file << "";
    index_file.close();

    // creating add_commit file (for storig whether the file has pushed or not) 0-add 0-commit and also push_directory path
    ofstream add_commit_file(add_commit.c_str());
    add_commit_file << "00";
    add_commit_file.close();

    // creating the push file
    ofstream push_file(pushFile.c_str());
    push_file.close();

   
}
