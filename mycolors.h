
/*

Name            FG  BG
Black           30  40
Red             31  41
Green           32  42
Yellow          33  43
Blue            34  44
Magenta         35  45
Cyan            36  46
White           37  47
Bright Black    90  100
Bright Red      91  101
Bright Green    92  102
Bright Yellow   93  103
Bright Blue     94  104
Bright Magenta  95  105
Bright Cyan     96  106
Bright White    97  107

*/

#define RED(x) "\x1B[31;1m"<<x<<"\033[0m"
#define GREEN(x) "\x1B[32;1m"<<x<<"\033[0m"
#define BROWN(x) "\x1B[33m"<<x<<"\033[0m"
#define BROWN_B(x) "\x1B[33;1m"<<x<<"\033[0m"
#define BLUE(x) "\x1B[34m"<<x<<"\033[0m"
#define PURPLE(x) "\x1B[35m"<<x<<"\033[0m"
#define YELLOW(x) "\x1B[93m"<<x<<"\033[0m"
#define YELLOW_B(x) "\x1B[93;1m"<<x<<"\033[0m"
#define WHITE(x) "\x1B[37m"<<x<<"\033[0m"
#define CYAN(x) "\x1B[36m"<<x<<"\033[0m"
#define MAGENTA(x) "\x1B[35m"<<x<<"\033[0m"
#define FBG(x) "\033[1;47;35m"<<x<<"\033[0m";


