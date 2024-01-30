#define MAXJOBS 256
#include <queue>
#include <list>
#include <iterator>
#include "./printSpooler.h"

class printer{
    int FINISH=1;
    // Recreated this to be efficient from vector to list
    std::list<job> jobList;
    // create a list of printers added
    std::vector<std::string> printers;
    public:
        bool addNewJob(const job &job){
            if (jobList.size()==MAXJOBS) { 
                std::cout<<std::endl;
                std::cout<<"Print Queue Full";
                return false;}
            std::cout<<"Added New Job:"<<job.getPID()<<'\n';
            jobList.push_back(job);
            getStatus();
            return true;
        }
        void getStatus()
        {
            std::list<job>::iterator i;
            std::cout<<std::endl;
            std::cout<<"*** PRINT JOBS ***"<<std::endl;
            for (i = jobList.begin();i != jobList.end();i++)
            {
                std::cout<<"PID:"<<i->getPID();
                std::cout<<" USER:"<<i->getusr();
                std::cout<<" TIME:"<<i->getTime();
                switch (FINISH)
                {
                    case 0:
                        std::cout<<" STATUS:FINISHED";
                        break;
                    case 1:
                        std::cout<<" STATUS:IN PROGRESS";
                        break;
                    case -1:
                        std::cout<<" STATUS:ERROR_EXCEPTION";
                        break;
                    default:
                        break;
                }
                std::cout<<std::endl;
            }
            std::cout<<std::endl;
        }

        bool rmJob(const int rmPID)
        {
            if (jobList.size()<=0) {return -5;}
            std::cout<<"Removing job:"<<rmPID;
            if (jobList.back().getPID()==rmPID) {
                jobList.pop_back();
                getStatus();
                return true;
            }
            std::list<job>::iterator i;
            for (i=jobList.begin();i != jobList.end();i++)
            {
                if (i->getPID()==rmPID)
                {
                    i = jobList.erase(i);
                    getStatus();
                    return true;
                }
            }
            // ERR
            return false;
        }

        // This shouldn't fail if inputs are valid
        void addPrinter(const std::string printerName, const std::string modelName)
        {
            // invalid entries get ignored automatically
            std::string string_to_send="lpadmin -p ";
            string_to_send.append(printerName);
            string_to_send.append(" -E -m ");
            string_to_send.append(modelName);
            system(string_to_send.c_str());
            try {printers.push_back(printerName);}
            catch(...) {std::cout<<"UNSUCESSFUL";return;}
            return;
        }

        // Call lp to print
        void printCall(std::string file)
        {
            if (printers.size()==0) {
                std::cout<<std::endl;
                std::cout<<"NO PRINTER DETECTED ERROR";
                std::cout<<std::endl;
                return;
            }
            std::cout<<std::endl;
            std::string optionSelected = printOptions();
            std::string string_to_print = "lp -d ";
            string_to_print.append(optionSelected);
            string_to_print.append(" ");
            string_to_print.append(file);
            // Errors will be displayed by cups
            system(string_to_print.c_str());
            jobList.erase(jobList.begin());
        }

        void rmPrinter(std::string printer)
        {
            bool rmStatus=0;
            for (int i=0;i<printers.size();i++)
            {
                if (printers[i]==printer)
                {
                    printers.erase(printers.begin()+i);
                    rmStatus=1;
                }
                if (rmStatus=0)
                {
                    std::cout<<std::endl;
                    std::cout<<"CANNOT REMOVE";
                    std::cout<<std::endl;
                }
            }
            std::cout<<"REMOVED:"<<printer<<std::endl;
            std::string string_to_call="lpadmin -x ";
            string_to_call.append(printer);
            system(string_to_call.c_str());
            showPrinters();
        }

private:
        std::string printOptions()
        { 
            std::string printerOption;
            std::cout<<"Enter a printer you would like to use: ";
            std::cout<<std::endl;
            showPrinters();
            std::cout<<std::endl;
            std::cin>>printerOption;
            return printerOption;
        }

        void showPrinters()
        {
            std::cout<<std::endl;
            std::cout<<"Priners Available"<<std::endl;
            for (int i=0;i<printers.size();++i)
            {
                std::cout<<printers[i];
                std::cout<<std::endl;
            }
        }
};