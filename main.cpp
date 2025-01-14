#include <config.h>

#include <pathtest.h>

#include <iostream>
#include <fstream>
#include <filesystem>
using namespace std;



namespace fs = std::filesystem;

#include <jsoncpp/json/json.h>
// Hilfetext (David Prinz)
const char * const HilfeText = {
    "Usage: options [OPTIONS] file ... \n" \
    "-h, --help         Hier die Funktion, die beschrieben werden muessen\n" \
    "\n" \
    "For more information contact david.prinz1123@gmail.com"
};

int main(const int argc, const char **argv) {

    //Simples Beispiel zum auslesen einer json Datei
    if(argc != 2) {
        cerr << "Bitte eine Datei angeben!" << endl;
        return EXIT_FAILURE;
    }
    else {
        auto path = fs::weakly_canonical(argv[1]);

        if(!fs::exists(path)) {
            cerr << "Datei existiert nicht: " << path.string() << endl;
            return EXIT_FAILURE;
        }

        ifstream ifs(path.string());

        Json::Reader reader;
        Json::Value root;
        if(!reader.parse(ifs, root)) {
            cerr << "Datei ist ungueltig: " << path.string() << endl;
            return EXIT_FAILURE;
        }

        //Zuerst wird das Land ausgeben
        cout << "Land: " << root["country"].asString() << endl;

        {
            //Werte aus dem Array
            const Json::Value persons = root["persons"];

            if(persons.isArray())
                for (Json::Value::ArrayIndex i = 0; i < persons.size(); ++i) {
                    auto person = persons[i];

                    cout << "Id: " << person["id"].asInt() << endl;
                    //.....
                }
        }

        return EXIT_SUCCESS;
    }
}
//test