void git_commit()
{

    string add_commit = cwd + "/git/add_commit.txt";
    ifstream add_commit_file;
    add_commit_file.open(add_commit.c_str(), ios::in);
    string check_bit, push_directory;

    getline(add_commit_file, check_bit, ' ');
    getline(add_commit_file, push_directory, ' ');
    add_commit_file.close();

    if (check_bit == "00")
    {
        cout << RED("       Please add first") << endl;
        exit(0);
    }

    // getting version number from version.txt
    string versionfile = cwd + "/git/version.txt";
    ifstream infile;
    infile.open(versionfile, ios::in);
    string data;
    infile >> data;
    infile.close();

    // converting version number to integer and incrementing the version number
    stringstream con(data);
    int v_no = 0;
    con >> v_no;
    v_no += 1;

    // writing version number to the version.txt
    ofstream outfile;
    outfile.open(versionfile, ios::out);
    outfile << v_no;
    outfile.close();

    // creating new directory with new version number
    string newDirectory = cwd + "/git/version/v_" + to_string(v_no);
    check(mkdir(newDirectory.c_str(), 0777), "unable to create directory");

    // copying index file contents to new index file
    string prevIndexPath = cwd + "/git/version/v_" + to_string(v_no - 1) + "/index.txt";
    string newIndexPath = cwd + "/git/version/v_" + to_string(v_no) + "/index.txt";
    copyFile(prevIndexPath, newIndexPath);

    // to get current time
    auto currTime = std::chrono::system_clock::now();
    time_t time = std::chrono::system_clock::to_time_t(currTime);
    string Time = ctime(&time);

    // copying the commit time in log.txt
    string log_file = cwd + "/git/log.txt";
    outfile.open(log_file, ios::app);

    // writing commit time into log file
    string toLog = "Commit No:" + to_string(v_no - 1) + " Commit by: " + cwd + " Commit Time: " + Time;
    outfile << toLog;
    outfile.close();

    ofstream add_commit_file_out(add_commit.c_str());
    add_commit_file_out << "11 " << push_directory;
    add_commit_file_out.close();

    cout << YELLOW_B("\t\tCommit Successful!!!") << endl;
}