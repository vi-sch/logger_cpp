#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <chrono>
#include <sstream>
#include <iomanip>
#include <vector>

using namespace std;


std::string getCurrentDateTime() {
     auto now = std::chrono::system_clock::now();
    auto now_c = std::chrono::system_clock::to_time_t(now);
    std::stringstream ss;
    ss << std::put_time(std::localtime(&now_c), "%Y-%m-%d %H:%M:%S");
    return ss.str();
}





class Logger{
    protected: 
        int count;
        string name;

        Logger(string n){
            cout << n<<" has been created\n";
            int count=0;
            name=n;
        }

        virtual void logmsg(string msg)=0;


        ~Logger(){
            cout << "Logger is being shut down"<<endl;
        }
};


class LoggerFile : public Logger{
    private:
    string filename;
    ofstream outfile;

    public:
    LoggerFile(string n, string nfile):Logger(n){
        filename=nfile;
        outfile.open(filename);
    }


    void logmsg(string msg){
        string tmnow=getCurrentDateTime();
        outfile <<tmnow << " | Line " << count <<": "<< msg <<endl;
        count ++;
    }


    ~LoggerFile(){
        cout << "LoggerFile is being shut down"<<endl;
        outfile.close();
    }

    
};



class LoggerHTML : public Logger{
    private:
        ofstream outfile;
        string logfname;

    public:
        LoggerHTML(string n, string logfilename, string websitename): Logger(n){
            outfile.open(logfilename);
            logfname=logfilename;

            outfile << "<!DOCTYPE html>\n";
            outfile << "<html>\n";
            outfile << "    <head>\n";
            outfile << "        <title>\n";
            outfile << "            " << websitename << "\n";
            outfile << "        </title>\n";
            outfile << "    </head>\n";
            outfile << "    <body>\n";
        }



        void logmsg(string msg){
            string tmnow=getCurrentDateTime();
            outfile <<  "\t\t<p>" <<
                        tmnow <<
                        " | Line " << 
                        count <<
                        ": "<< 
                        msg <<
                        "</p>" << endl;
            count ++;
        }


        ~LoggerHTML(){
            outfile << "    </body>\n";
            outfile << "</html>\n";
            outfile.close();
        }

};










int main()
{
    //cout <<"Hello world!" <<endl;

    LoggerHTML* l1;
    l1 = new LoggerHTML("l1", "test.html", "Teschdseide");
    l1->logmsg("Testosterono");
    l1->logmsg("Biblidibu");

    delete l1;
    return 0;
}
