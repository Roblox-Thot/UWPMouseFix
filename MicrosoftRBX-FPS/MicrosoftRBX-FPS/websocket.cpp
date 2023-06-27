#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>
#include <thread>
#include <vector>
#include <iostream>
#include <fstream>
#include "websocket.h"

#pragma region Colors
#define RST  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"

#define FRED(x) KRED x RST
#define FGRN(x) KGRN x RST
#define FYEL(x) KYEL x RST
#define FBLU(x) KBLU x RST
#define FMAG(x) KMAG x RST
#define FCYN(x) KCYN x RST
#define FWHT(x) KWHT x RST

#define BOLD(x) "\x1B[1m" x RST
#define UNDL(x) "\x1B[4m" x RST
#pragma endregion

bool rightClickDown;
bool inFirstPerson;
bool roActive;
HWND curHWND;
//Remove this comment to beable to see the output in time\\

#define outDebug

void printGayStatus()
{
    system("cls");
    /*std::cout << KBLU;
    std::cout << BOLD("Roblox-HWND: ") << curHWND << std::endl;*/
    std::cout << KRED;
    std::cout << BOLD("Mode: ") << "Websocket script" << std::endl;
    /*std::cout << KYEL;
    std::cout << BOLD("Keybind: ") << toggleKeyName << std::endl;*/
    //std::cout << KCYN;
    //std::cout << BOLD("Enabled: ") << (isEnabled ? "Enabled" : "Disabled");
#ifdef outDebug
    std::cout << KWHT;
    std::cout << BOLD("rightClickDown: ") << rightClickDown << std::endl;
    std::cout << BOLD("inFirstPerson: ") << inFirstPerson << std::endl;
    std::cout << BOLD("roActive: ") << roActive << std::endl;
#endif // outDebug

}

void mice() {
    while (1 + 2 == 3) {
        if ((rightClickDown || inFirstPerson) && roActive) {
            // Reusing code from the right click lock since lazy
            POINT p;
            curHWND = GetForegroundWindow();
            if (GetCursorPos(&p))
            {
                if (ScreenToClient(curHWND, &p))
                {
                    RECT rect = { NULL };
                    if (GetWindowRect(curHWND, &rect)) {
                        POINT realP;
                        if (GetCursorPos(&realP))
                        {
                            while ((rightClickDown || inFirstPerson) && roActive) {
                                SetCursorPos(realP.x, realP.y);
                            }
                        }
                    }
                }
            }
        }

    }
}

std::vector<std::string> splitString(const std::string& inputString)
{
    std::vector<std::string>   result;
    std::stringstream  data(inputString);
    std::string line;
    while (std::getline(data, line, '_'))
    {
        result.push_back(line);
    }

    return result;
}

void handleMyBitchAss(std::string data) {
    auto bttData = splitString(data);
    // How data MAY be held idk yet \\
   //                                \\
      Right click? | FP | win active

    //#ifdef DEBUG
    //    for (const auto& str : bttData)
    //    {
    //        std::cout << str << std::endl;
    //    }
    //#endif // DEBUG outputs
    rightClickDown = bttData[0] == "true" ? true : false;
    inFirstPerson = bttData[1] == "true" ? true : false;
    roActive = bttData[2] == "true" ? true : false;
    printGayStatus();

}

// stole most this this from https://github.com/PhysicsX/ExampleCode/blob/master/Cpp/websocket.cpp ngl because C++ websocets are strange af
namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace http = beast::http;           // from <boost/beast/http.hpp>
namespace websocket = beast::websocket; // from <boost/beast/websocket.hpp>
namespace net = boost::asio;            // from <boost/asio.hpp>
using tcp = boost::asio::ip::tcp;       // from <boost/asio/ip/tcp.hpp>

//------------------------------------------------------------------------------

void startWebsocket(){
    auto const address = net::ip::make_address("127.0.0.1");
    auto const port = static_cast<unsigned short>(std::atoi("58008"));

    // The io_context is required for all I/O
    net::io_context ioc{1};

    // The acceptor receives incoming connections
    tcp::acceptor acceptor{ioc, { address, port }};
    while (true)
    {
        // This will receive the new connection
        tcp::socket socket{ioc};

        // Block until we get a connection
        acceptor.accept(socket);

        // Launch the session, transferring ownership of the socket

        auto session = [](tcp::socket socket) {

            // Construct the stream by moving in the socket
            websocket::stream<tcp::socket> ws{std::move(socket)};

            // Set a decorator to change the Server of the handshake
            ws.set_option(websocket::stream_base::decorator(
                [](websocket::response_type& res)
                {
                    res.set(http::field::server,
                    std::string(BOOST_BEAST_VERSION_STRING) +
                    " websocket-server-sync");
                }));

            // Accept the websocket handshake
            ws.accept();

            while (true)
            {
                // This buffer will hold the incoming message
                beast::flat_buffer buffer;

                // Read a message
                ws.read(buffer);

                auto out = beast::buffers_to_string(buffer.cdata());
                handleMyBitchAss(out);
                // im tired as shit been up 19+ hr please give me help and hope that anything will make sense in the morning

                //ws.write(buffer.data());
            }
        };

        std::thread(session, std::move(socket)).detach();
    }
}


void websocketMain()
{
    // May make it write file in the folder but
    // will prob just include it in the zip and repo
    //    std::ifstream file("script.lua");
    //    if (!file.is_open()) {
    //        std::cout << "The file does not exist." << std::endl;
    // 
    //        std::ofstream myfile;
    //        myfile.open("example.txt");
    //        myfile << "Writing this to a file.\n";
    //        myfile.close();
    //    }

    // lazy ass
    printGayStatus();
    std::thread mouseThread(mice);
    std::thread websocketThread(startWebsocket);
    mouseThread.join();
    websocketThread.join();
}