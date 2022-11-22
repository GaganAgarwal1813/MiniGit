void get_logs()
{
    string bash_cmd="cat "+cwd+"/git/log.txt";
    system(&bash_cmd[0]);
}