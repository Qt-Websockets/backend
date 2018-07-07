#ifndef UTILS_LXD_H
#define UTILS_LXD_H

#include <string>

class UtilsLXDAuth {
    public:
        static bool check_trust_certs(std::string &sError);
        static bool connect_with_lxd(std::string sPass, std::string &sError);
        static bool set_trusted(std::string sPass, std::string &sError);
};

#endif
