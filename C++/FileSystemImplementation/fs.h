#include <iostream>
#include <vector>
#include <algorithm>
#include <stdlib.h>
#include <fstream>
#include <sys/stat.h>
using namespace std;

// My attempt at simulating a Linux FileSystem(Contains bugs - I've seen several)

/*  Used with the Packt coding example & design,
    The add, chdir, and find code is rewritten to understand the implementation
    and to improve it

    *** CHANGED FROM RECURSION TO ITERATIVE ***

    +++ COMMENTS ADDED TO ADD READABILITY +++
    +++ ADDED FUNCTIONS SUCH AS PERMISSIONS & Links +++
    +++ ADDED ADDITIONAL CONST PARAMETERS +++ 
    --- REMOVED RECURSION ---

    Improvements are made similar to the Linux system such as
    permissions, inodes, links & link counts, device tracking(device numbering), 
    improved ls(Now shows Permissions, date & time)
    
    NOTE: SIZE WILL NOT BE CALLED(Since it requires writing files to drive)
    size functionality which calls on the operating system(disk software) to provide an estimate

*/

// A node can be a file, folder, or a device
// Every type will have a name, permission, inode, links, size and device number
// Every entry should keep an entry of last modified timestamp through the OS Calls
// Our node will not be devices

/*
    inode numbers and will be random for our filesystem
    device for our case will be 0 for sda
    uint size will start with 0 then will be calculated later
    permissions by default are set to 664 and can be changed later
    nlinks are set to 0 and can later be changed
*/
struct n_arr_node
{
    string name;
    const bool is_dir;
    vector<n_arr_node*> children;
    string date_time;
    uint permissions=664;
    bool is_dev=0;
    uint inode=rand()%65535;
    // negative nlinks & dev mean error/removed
    short nlinks=0;
    // This is different from is_dev in that 
    // this is the device number vs determining the type
    int dev_num=0;
    // The size will be implemented but not used for this project
    uint size=0;
    // Contains addresses to links
    vector <n_arr_node*> links;
};


struct file_system
{
    using node = n_arr_node;
    using node_ptr = node *;
    // All parameters will require constant variables for safety and security
    // Ideally these values shouldn't get changed as it is user input
    // A program mostly shouldn't touch and modify these parameters for any reason
    private:
        node_ptr root,cwd;
        node_ptr find(const node_ptr dir, const string path)
        {
            node_ptr curr_dir = dir;
            string curr_path = path;
            while (!curr_path.empty())
            {
                auto sep = curr_path.find('/');
                // Seperate root path & rest of dir
                string rootPath = sep == string::npos ? curr_path : curr_path.substr(0,sep);
                string restOfPath = sep == string::npos ? "" : curr_path.substr(sep+1);
                // Go through directory to find it using lambda and reference capture
                // return a iterator to the child of the path
                auto found = std::find_if(curr_dir->children.begin(),curr_dir->children.end(),
                                            [&](const node_ptr child) {
                                                return child->name == rootPath;
                                            });
                // find next directory(subdirectory) if directory is found (not reached end)
                if (found != curr_dir->children.end())
                {
                    curr_dir = *found;
                    curr_path = restOfPath;
                }
                // not found since find_if reached end and there was still filenames to search
                else {return nullptr;}
            }
            return curr_dir;
        }

        string modify_time()
        {
            fstream readDateTime;
            string date_to_send="";
            date_to_send.append("date");
            date_to_send.append(" +\"%B %d %H:%M\"");
            date_to_send.append(" > dateTime.txt");
            system(date_to_send.c_str());
            readDateTime.open("dateTime.txt");
            getline(readDateTime,date_to_send);
            readDateTime.close();
            return date_to_send;
        }

        bool add(const node_ptr dir, const string &path,bool is_dir)
        {
            node_ptr curr_dir=dir;
            string curr_path=path;
            string rootPath;
            while (curr_dir -> is_dir)
            {
                auto sep = curr_path.find('/');
                if (sep == string::npos)
                {
                    auto found = find_if(curr_dir->children.begin(),curr_dir->children.end(),
                                        [&](const node_ptr child) {
                                            return child->name == curr_path;
                                        });
                    if (found != curr_dir->children.end())
                    {
                        cout<<"There's already a file/directory named:"<<curr_path;
                        cout<<" inside "<<curr_dir->name<<endl;
                        return false;
                    }
                    string last_modified = modify_time();
                    curr_dir->children.push_back(new node {curr_path,is_dir,{},last_modified});
                    return true;
                }
                rootPath = curr_path.substr(0,sep);
                // Find root path and set it as currrent directory
                auto found = find_if(curr_dir->children.begin(),curr_dir->children.end(), [&](const node_ptr child)
                                        {
                                            return child->name == rootPath && child->is_dir;
                                        });
                if (found != curr_dir->children.end())
                {
                    curr_dir = *found;
                    curr_path = curr_path.substr(sep+1);
                    is_dir=is_dir;
                }
                else if (found == curr_dir->children.end())
                {
                    cout<<"There was no directory "<<rootPath<< " inside "<<curr_dir->name<<endl;
                    return false;
                }
            }
            cout<<"There is no directory "<< rootPath <<" inside "<<curr_dir->name<<endl;
            return false; 
        }
        // This function is similar to Linux's chmod
        bool modify_perm(const string &path, const int perms)
        {
            // find if int exceeds XXXX values
            int size=sizeof(perms);
            if (size>4)
            {
                cout<<"Error: Permissions size";
                return -1;
            }
            // Permissions should not exceed 7s
            else if (size==4 && perms>7777)
            {
                cout<<"Invalid permissions"<<endl;
                return -2;
            }
            else if (size<4 && perms>777)
            {
                cout<<"Invalid permissions"<<endl;
                return -3;
            }
            auto found = find_path(path);
            if (!found){cout<<"Error: Path does not exist"<<endl;return false;}
            (*found).permissions=perms;
            return 0;
        }
        // return path permissions for showing dir
        string getPermissions(const int perms){
            string permission = to_string(perms);
            int size = permission.length();
            bool SUID=false;
            bool SGID=false;
            bool Sticky=false;
            string to_return="";
            int i=0;
            // check for special permissions
            if (size==4 && permission[0]!=0)
            {
                if (permission[0]=='1'){ Sticky=true;}
                else if (permission[0]=='2'){ SGID=true;}
                else if (permission[0]=='3'){SGID=true;Sticky=true;}
                else if (permission[0]=='4') {SUID=true;}
                else if (permission[0]=='5'){SUID=true;Sticky=true;}
                else if (permission[0]=='6'){SUID=true;SGID=true;}
                else {SUID=true;SGID=true;Sticky=true;}
            }
            // This is meant to avoid printing extra 3 or 3 less
            if (size==4) {i=1;}
            else {i=0;}
            // This string will be replaced if specials are found
            for (i;i<=size;i++)
            {
                if (permission[i]=='0')
                {
                    to_return.append("---");
                }
                else if (permission[i]=='1'){
                    to_return.append("--x");
                }
                else if (permission[i]=='2'){
                    to_return.append("-w-");
                }
                else if (permission[i]=='3'){
                    to_return.append("-wx");
                }
                else if (permission[i]=='4'){
                    to_return.append("r--");
                }
                else if (permission[i]=='5'){
                    to_return.append("r-x");
                }
                else if (permission[i]=='6'){
                    to_return.append("rw-");
                }
                else if (permission[i]=='7'){
                    to_return.append("rwx");
                }
            }
            // Similar to Linux denote lower s for user/group execute perms
            // Upper S for no exec perms
            // t for other exec perms
            // T for other no exec perms
            // This is special permissions for elevated level requirements
            if (SUID || SGID || Sticky)
            {
                if (SUID && to_return[2]=='x') 
                {to_return[2]='s';}

                if (SUID && to_return[2]!='x' && to_return[2]!='s')
                {to_return[2]='S';}

                if (SGID && to_return[5]=='x') 
                {to_return[5]='s';}

                if (SGID && to_return[5]!='x' && to_return[5]!='s') 
                {to_return[5]='S';}

                if (Sticky && to_return[8]=='x')
                {to_return[8]='t';}

                if (Sticky && to_return[8]!='x' && to_return[8]!='t')
                {to_return[8]='T';}
            }
            return to_return;
        }

    public:
        file_system()
        {
            string last_modified=modify_time();
            root = new node{"/",true,{},last_modified};
            cwd=root;
        }

        node_ptr find_path(const string &path)
        {
            if (path[0]=='/') // Absolute Path
            {
                return find(root,path.substr(1));
            }
            return find(cwd,path); // Relative Path
        }

        bool add_path(const string &path,const bool is_dir)
        {
            if (path[0]=='/') // Absolute path
            {
                return add(root,path.substr(1),is_dir);
            }
            return add(cwd,path,is_dir); // Relative path
        }

        bool change_dir(const string &path){
            auto found = find_path(path);
            if (found && found->is_dir)
            {
                cwd = found;
                cout << "New directory changed to: "<<cwd->name<<endl;
                return true;
            }
            cout<<"Error There is no: "<<path<<" that exists"<<endl;
            return false;
        }

        bool change_permissions(const string &path, const uint permissions)
        { return modify_perm(path,permissions);}

        bool ln_s(const string &path, const string& dest)
        {
            auto pathLn = find_path(path);
            if (!pathLn) {cout<<"Path not present"<<endl; return false;}
            bool added=find_path(dest);
            if (!added) {cout<<"destination path invalid"<<endl; return false;}
            auto pathDest = find_path(dest);
            ++pathLn->nlinks;
            pathDest->links.push_back(pathLn);
            return true;
        }

        bool show_path(const string &path)
        {
            auto found = find_path(path);
            int curr_perms;
            string perms;
            if (!found) { 
                cout<<"No such path exists"<<endl; 
                return -1;
            }
            if (found->is_dir)
            {
                for (auto child : found->children)
                {
                    curr_perms=child->permissions;
                    perms=getPermissions(curr_perms);
                    cout<<(child->is_dir ? "d" : "-")<<perms<<"  "<<"  "<<child->date_time<<"  ";
                    cout<<child->name<<endl;
                    if (!child->links.empty()){
                        for (int i=0;i<child->links.size();i++)
                        {
                            cout<<'l'<<perms<<"  "<<child->links[i]->date_time<<"  ";
                            cout<<child->name<< " -> "<<child->links[i]->name<<endl;
                        }
                    }
                }
            }
            else{
                curr_perms=found->permissions;
                perms=getPermissions(curr_perms);
                cout<<'-'<<perms<<"  "<<found->date_time<<" ";
                cout<<found->name<<endl;
                if (!found->links.empty())
                {
                    for (int i=0;i<found->links.size();i++)
                    {
                        cout<<'l'<<perms<<"  "<<found->links[i]->date_time<<"  ";
                        cout<<found->name<< " -> "<< found->links[i]->name<<endl;
                    }
                }
            }
            return 0;
        }

        size_t getFileSize(const string &file)
        {
            struct stat file_stat;
            if (stat(file.c_str(), &file_stat) != 0 )
            {
                return 0;
            }
            return file_stat.st_size;
        }
};
