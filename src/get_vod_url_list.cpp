#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <chrono>

#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>

using namespace curlpp::options;

void process_one_url(const std::string &url)
{
    size_t pos = url.find_last_of("/");
    size_t end_pos = url.find(".m3u8");
    std::string prefix = url.substr(0, pos);
    std::string output_file_name = url.substr(pos + 1, (end_pos - pos - 1));

    try
    {
        curlpp::Cleanup myCleanup;
        curlpp::Easy myRequest;
        myRequest.setOpt<Url>(url);

        std::ostringstream os;
		curlpp::options::WriteStream ws(&os);
		myRequest.setOpt(ws);
		myRequest.perform();

        std::string line;
        std::stringstream ss;
        ss << os.str();

        std::ofstream output_file;
        output_file.open("output/" + output_file_name + ".txt");

        output_file << url << std::endl;
        while (std::getline(ss, line))
        {
            if (line.find(".ts") != line.npos)
            {
                //std::cout << prefix << "/" << line << std::endl;
                output_file << prefix << "/" << line << std::endl;
            }
        }

        output_file.close();
    }
    catch(curlpp::RuntimeError& e)
    {
        std::cerr << e.what() << '\n';
    }
    catch(curlpp::LogicError & e)
    {
        std::cout << e.what() << std::endl;
    }

}

int main(int argc, char *argv[])
{
    //std::string url("http://vod-ali.vlightv.com/ead6f92ac61143b68d275deccb59563b/a8343980346c4865950c88c2de3f64e5-18616a8d2843a001dcde031ba54f587f-fd.m3u8?auth_key=1629722735-71ce1a6d74da46cdb77252b6cda73a38-0-eb4f6c8fad668da166cdc0bc45f3d315");
    
    std::cout << argv[1] << std::endl;

    std::ifstream url_list(argv[1]);
    std::string url;

    while (std::getline(url_list, url))
    {
        unsigned long long start = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
        process_one_url(url);
        unsigned long long end = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
        std::cout << url << " done tm=" << (end - start) << std::endl;
    }
    return 0;
}
