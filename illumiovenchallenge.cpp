//Simple NAT Implementation
//Gautam Nambiar

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <stdio.h>

class Address                                                                       //class to store distinct values of address(ip, port)
{
    public:
    std::string ip; 
    std::string port;
    Address(std::string line)
    {
        ip = line.substr(0, line.find(':'));
        port = line.substr(line.find(':') + 1);
    }
};

class NATAddressPair                                                                        //class to store addresses to be mapped
{  
    public:
    std::string originalAddress;
    std::string transAddress;
    NatMap(std::string line)
    {
        originalAddress = line.substr(0, line.find(','));
        transAddress = line.substr(line.find(',') + 1);
    }
};

int main()
{
    std::ifstream natfile ("NAT.txt");
    std::ifstream flowfile ("FLOW.txt");
    std::ofstream outfile ("OUT");
    std::string natline, flowline;
    std::map<std::string,std::string> natmap;
    if (flowfile.is_open() && natfile.is_open()) 
    {
        while(getline(natfile, natline))                                            //store the original and translated address in map(oredered)
        {
            NatMap natm(natline);
            natmap.insert(std::pair<std::string,std::string>(natm.originalAddress, natm.transAddress));
        }
        std::map<std::string, std::string>::reverse_iterator itr;
        // in the following loop flow, is checked against the original addresses in reverse sorted order
        // maps uses a simple ordering so all the address with "*"" ip address comes first.
        //in order to check for a numeric value if available, before a "*", traverse in reverse.
        while(getline(flowfile, flowline)) 
        {
            Address flow(flowline); 
            for (itr = natmap.rbegin(); itr != natmap.rend(); itr++)                //Traverse thorugh the map in reverse
            {
                Address nat(itr->first);
                if(nat.ip.compare(flow.ip) == 0) 
                {
                    if (nat.port.compare(flow.port) == 0) {
                        outfile << flowline << " -> " << itr->second << '\n';
                        break;
                    }
                    else if (nat.port.compare("*") == 0) {
                        outfile << flowline << " -> " << itr->second << '\n';
                        break;
                    }
                }
                else if (nat.ip.compare("*") == 0) 
                {
                    if (nat.port.compare(flow.port) == 0) {
                        outfile << flowline << " -> " << itr->second << '\n';
                        break;
                    }
                    else if (nat.port.compare("*") == 0) {
                        outfile << flowline << " -> " << itr->second << '\n';
                        break;
                    }
                }
            }
            if (itr == natmap.rend())                                               //If it ever reached the end the translation is not found
                outfile << "No nat match for " << flowline << '\n';
        }
    }
    else 
        outfile << "Can't read files";
    natfile.close();
    flowfile.close();
    outfile.close();
}