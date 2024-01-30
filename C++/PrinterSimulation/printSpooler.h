#include <iostream>
#include <ctime>
#include <fstream>


class job
{
    std::string user;
    std::string startTime; 
    int pid;
    public:
        job(const std::string& u,const int newPID)
        {
            user=u;
            std::ifstream readTime;
            system("date +%T > lastPrintJob");
            readTime.open("lastPrintJob");
            if (readTime.is_open())
            {
                getline(readTime,startTime);
                readTime.close();
            }
            else {startTime="UNKNOWN";}
            pid=newPID;
        }
        std::string getusr() const  {return this->user;}
        std::string getTime() const {return this->startTime;}
        int getPID() const {return this->pid;}
};