#include <bits/stdc++.h>
#include <filesystem>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fstream>
#include <iostream>
#include "sha1.hpp"
#include <chrono>
#include <ctime>
#include <fcntl.h>
#include <termios.h>
#include <sys/sendfile.h>
#include <string.h>
#include <termios.h>
#include <dirent.h>
#include "mycolors.h"


#ifdef DEBUG

#define LOG(x) cout << RED("LOG: ") << x << endl;
#define LOGY(x) cout << RED("LOG: ") << YELLOW(x) << endl;
#define LOGB(x) cout << RED("LOG: ") << BLUE(x) << endl;
#define LOGG(x) cout << RED("LOG: ") << GREEN(x) << endl;
#define LOGP(x) cout << RED("LOG: ") << PURPLE(x) << endl;
#define LOGR(x) cout << RED("LOG: ") << RED(x) << endl;
#define LOGC(x) cout << RED("LOG: ") << CYAN(x) << endl;

#else

#define LOG(x)
#define LOGY(x)
#define LOGB(x)
#define LOGG(x)
#define LOGP(x)
#define LOGR(x)
#define LOGC(x)
#endif

using namespace std;
string cwd;
