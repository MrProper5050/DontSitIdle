#pragma once
#include <string>
#include <vector>

class SiteBlocker
{
public:
	SiteBlocker(std::vector<std::string> sites);
	~SiteBlocker();

	std::string pullOutSiteIps(std::string domain); //nslookup <site>
	std::string pullOutSitesIps(); 

	std::vector<std::string> get_sitesNames();
	std::vector<std::string> get_sitesIPs();



private:
	std::vector<std::string> sitesIPs;
	std::vector<std::string> sitesNames;
};