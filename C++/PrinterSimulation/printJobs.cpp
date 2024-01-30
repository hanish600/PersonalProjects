#include <iostream>
#include "./printer.h"
#include <thread>

/*
    This project simulates how a printer might print a document using cups.
    Specifically, the goal of the project is to simulate job scheduling of a printer.
    It involves several calls to the cups utilities.

    This will use the outdated drv:///sample.drv/dymo.ppd model
    Threads are used to simulate different timestamps for queue entries
*/

using namespace std;

int main()
{
    // parameters are user, pid
    const job j1("John",1001);
    printer pairs;
    pairs.addNewJob(j1);
    this_thread::sleep_for(5000ms);
    const job j2("BOB",1002);
    pairs.addNewJob(j2);
    this_thread::sleep_for(5000ms);
    const job j3("Bill",1003);
    pairs.addNewJob(j3);
    pairs.rmJob(1002);
    // The parameters are printer name, printer driver/model
    pairs.addPrinter("ptest","drv:///sample.drv/dymo.ppd");
    pairs.addPrinter("ptest2","drv:///sample.drv/dymo.ppd");
    pairs.addPrinter("ptest3","drv:///sample.drv/dymo.ppd");
    // The printCall gives printOptions to choose the printer to print from
    pairs.printCall("./printJobs.cpp");
    pairs.rmPrinter("ptest2");
}
