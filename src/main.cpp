#include <fstream>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "siteblocker_h.h"

void someBody() {
	//system("nslookup vk.com");


	std::vector<std::string> sites;

	FILE* pipe;

	char buf[100];


	if ((pipe = _popen("nslookup vk.com", "r")) == NULL)
	{
		perror("nslookup vk.com");
		exit(1);
	}
	short i = 0;
	std::string buf_s;
	
	while (fgets(buf, 100, pipe) != NULL) {
		/*std::cout << buf_s.size() <<"\n";
		const char* b = buf_s.data();*/
		buf_s = buf;
		std::cout << buf_s.size() << "\n";
		i++;
		if (buf_s.size() > 1) {
			if (i == 5) {
				/*std::cout << "buf_s: " << buf_s.data() << "\n";
				std::cout << "buf_s.size(): " << buf_s.size() << std::endl;
				std::cout<<"SUB: "<<buf_s.substr(11, buf_s.size() - 11)<<std::endl;*/
				//std::cout << "SUB1:" << buf_s.substr(12, buf_s.size() - 10) << std::endl;
				sites.push_back(buf_s.substr(12, buf_s.size() - 13));
			}
			if (i > 5) {
				//std::cout << "SUB2:" << buf_s.substr(3, buf_s.size() - 4) << std::endl;
				sites.push_back( buf_s.substr(3, buf_s.size() - 4) );
			}
			printf("%d]Got line: %s", i, buf);
		}
		
	}
	std::vector<std::string>::iterator it = sites.begin();

	
	while (it != sites.end()) {
		std::cout << *it<<' ';

		it++;
	}
	if (ferror(pipe))
		perror("nslookup vk.com");

	_pclose(pipe);

	exit(0);

}
int main() {
	setlocale(LC_ALL, "rus");
	//write
	//std::ofstream myFileW("C:\\Windows\\System32\\drivers\\etc\\hosts", std::ios_base::app);
	// 
	//std::ofstream myFileW("mytext.txt");

	//if (!myFileW.is_open()) {
	//	std::cout << "Программа не может открыть файл!";
	//	std::cin.get();
	//	return 1;
	//}

	//myFileW << "127.0.0.1 vk.com";
	//myFileW.close();

	SiteBlocker sb({"vk.com","ok.ru"});

	std::string err = sb.pullOutSitesIps();
	if (err.size()) {
		std::cout << err;
		return 12;
	}

	std::vector<std::string> ips = sb.get_sitesIPs();
	std::vector<std::string>::iterator it = ips.begin();
	while (it != ips.end()) {
		std::cout << *it << ' ';

		it++;
	}


	////read
	//char buff[50];
	//std::ifstream myFileR("testC++file.txt");

	//myFileR.getline(buff, 50);
	//myFileR.close();
	//std::cout << buff;
	
	std::cin.get();

}
