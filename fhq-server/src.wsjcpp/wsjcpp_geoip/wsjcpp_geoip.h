#pragma once
#ifndef WSJCPP_GEOIP_H
#define WSJCPP_GEOIP_H

#include <string>
#include <json.hpp>

class WsjcppGeoIPResult {
    public:
        // ok
        WsjcppGeoIPResult(
            const std::string &sServiceName,
            const std::string &sIpAddress,
            const std::string &sCountry,
            const std::string &sRegionName,
            const std::string &sCity,
            double nLatitude,
            double nLongitude
        );
        // error
        WsjcppGeoIPResult(
            const std::string &sServiceName,
            const std::string &sIpAddress,
            const std::string &sErrorDescription
        );
        bool hasError();
        std::string getServiceName();
        std::string getIpAddress();
        std::string getErrorDescription();
        std::string getCountry();
        std::string getRegionName();
        std::string getCity();
        double getLatitude();
        double getLongitude();
        nlohmann::json toJson();

    private:
        std::string TAG;
        bool m_bHasError;
        std::string m_sServiceName;
        std::string m_sIpAddress;
        std::string m_sErrorDescription;
        std::string m_sCountry;
        std::string m_sRegionName;
        std::string m_sCity;
        double m_nLatitude;
        double m_nLongitude;    
};

// ---------------------------------------------------------------------

class WsjcppGeoIPv4 {
    public:
        WsjcppGeoIPv4();
        WsjcppGeoIPv4(const unsigned char arrIpLeft[4]);
        WsjcppGeoIPv4(unsigned char c1, unsigned char c2, unsigned char c3, unsigned char c4);
        bool fromString(const std::string &sIpAddress);
        std::string toString();
        bool operator==(const WsjcppGeoIPv4& rhs);
        bool operator<(const WsjcppGeoIPv4& rhs);
        bool operator>(const WsjcppGeoIPv4& rhs);
        bool operator<=(const WsjcppGeoIPv4& rhs);
        bool operator>=(const WsjcppGeoIPv4& rhs);
    private:
        unsigned char m_arrIP[4];
};

// ---------------------------------------------------------------------

class WsjcppGeoIP {
    public:
        static WsjcppGeoIPResult requestToIpApiCom(const std::string &sIpAddress);
        static WsjcppGeoIPResult parseResponseIpApiCom(const std::string &sIpAddress, const std::string &sJson);
        static bool isIPv4InReservedRange(const WsjcppGeoIPv4& ipV4, std::string &sError);
};

// ---------------------------------------------------------------------

#endif // WSJCPP_GEOIP_H
