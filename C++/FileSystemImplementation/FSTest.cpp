#include <iostream>
#include <fstream>
#include "./fs.h"
using namespace std;

int main()
{
    file_system fs;
    fs.add_path("usr", true);       // Add directory usr in "/"
    fs.add_path("etc", true);       // Add directory etc in "/"
    fs.add_path("var", true);       // Add directory var in "/"
    fs.add_path("tmp_file", false); // Add file tmp_file in "/"

    std::cout << "Files/Directories under \"/\"" << std::endl;
    fs.show_path("/"); // List files/directories in "/"

    std::cout << std::endl;
    fs.change_dir("usr");
    fs.add_path("H", true);
    fs.add_path("H/Downloads", true);
    fs.change_permissions("/usr",755);
    fs.change_permissions("/tmp_file",2770);
    fs.add_path("bin",true);
    fs.add_path("H/Desktop",true);
    fs.add_path("H/Desktop/BIN",true);
    fs.ln_s("bin","H/Desktop/BIN");
    fs.add_path("changingThosePermissions",true);
    fs.add_path("ReallyChangingThePerms",true);
    fs.add_path("Appleman/Downloads",true);
    fs.change_permissions("changingThosePermissions",5413);
    fs.change_permissions("ReallyChangingThePerms",4632);
    fs.add_path("iAmTheLink",false);
    fs.ln_s("ReallyChangingThePerms","iAmTheLink");
    fs.add_path("H/Downloads/newFile.cpp", false);
    fs.add_path("addLink",false);
    fs.ln_s("/tmp_file","addLink");
    fs.change_permissions("H/Downloads/newFile.cpp",7773);
    std::cout<< "After changing permissions under /: "<<endl;
    fs.show_path("/");

    std::cout << "Let’s see the contents of dir usr: " << std::endl;
    fs.show_path("usr"); // This will not print the path successfully, since we’re already inside the dir usr. And there’s no directory named usr inside it.

    std::cout << "Let’s see the contents of \"/usr\"" << std::endl;
    fs.show_path("/usr");

    std::cout << "Let’s see the contents of \"/usr/H/Downloads\"" << std::endl;
    fs.show_path("/usr/H/Downloads");

    std::cout << "Show the contents of \"H/Desktop\"" << std::endl;
    fs.show_path("/usr/H/Desktop");
}