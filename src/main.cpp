#include <iostream>
#include <string>
#include <args.hxx>
#include "Sender.hpp"
#include "TrafficGenerator.hpp"

using namespace std;

int main(int argc, char **argv)
{
    args::ArgumentParser parser("Gerador de tráfego.", "Desenvolvido por Gabriel Tiburski Júnior");
    args::HelpFlag help(parser, "help", "Mostra esse menu de ajuda", {'h', "help"});
    args::Group requiredArgs(parser, "Argumentos obrigatórios:", args::Group::Validators::All);
    args::Group notRequiredArgs(parser, "Argumentos não obrigatórios:", args::Group::Validators::DontCare);
    args::ValueFlag<string> argIp(requiredArgs, "ip", "ip destino", {'i'});
    args::ValueFlag<unsigned int> argPort(requiredArgs, "port", "porta destino", {'p'});
    args::ValueFlag<unsigned int> argRate(requiredArgs, "rate", "taxa em bits/s", {'r'});
    args::ValueFlag<unsigned int> argMtu(notRequiredArgs, "mtu", "unidade máxima de transmissão", {'m'});

    try {
        parser.ParseCLI(argc, argv);

        string ip = args::get(argIp);
        unsigned int port = args::get(argPort);
        unsigned int rate = args::get(argRate);
        unsigned int mtu = (argMtu) ? args::get(argMtu) : 512;

        TrafficGenerator trafficGenerator(new Sender(ip, port), rate, mtu);
        trafficGenerator.run();
    }
    catch (args::Help) {
        std::cout << parser;
        return 0;
    }
    catch (args::ParseError e) {
        std::cerr << e.what() << std::endl;
        std::cerr << parser;
        return 1;
    }
    catch (args::ValidationError e) {
        std::cerr << e.what() << std::endl;
        std::cerr << parser;
        return 1;
    }

    return 0;
}
