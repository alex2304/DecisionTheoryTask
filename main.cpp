#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include <iostream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;
using namespace rapidjson;
//"variables" : ["Максимальное количество батарей в год", "Цена производства одной батареи", "Цена продажи одной батареи", "Вероятности спроса на батареи"]
/*
    {
        "solutions" : "3",
        "making_price" : "2",
        "sale_price" : "5",
        "probabilities" : "0.5,0.3,0.2"
    }
*/

vector<double> &split(const string &s, char delim, vector<double> &elems) {
    stringstream ss(s);
    string item;
    while (getline(ss, item, delim)) {
        elems.push_back(atof(item.c_str()));
    }
    return elems;
}


vector<double> split(const string &s, char delim) {
    vector<double> elems;
    split(s, delim, elems);
    return elems;
}

int main() {
    //setlocale(LC_ALL, "Russian");
    //const char* json = "{\"solutions\" : \"5\", \"making_price\" : \"3\", \"sale_price\" : \"4\", \"probabilities\" : \"0.18,0.19,0.22,0.20,0.21\" }";
    char json[500];
    cin.getline(json, 500);
    Document d;
    d.Parse(json);
    string fucking_str;
    int solutions_count;
    double making_price, sale_price;

    fucking_str = d["solutions"].GetString();
    solutions_count = atoi(fucking_str.c_str());

    fucking_str = d["making_price"].GetString();
    making_price = atof(fucking_str.c_str());

    fucking_str = d["sale_price"].GetString();
    sale_price = atof(fucking_str.c_str());

    fucking_str = d["probabilities"].GetString();
    vector<double> probabilities = split(fucking_str, ',');

    double* u = new double[solutions_count];
    double maxU = 0;
    vector<int> solution;
    solution.push_back(0);

    cout << "Usefulness of every decisions: ";
    for (int i = 0; i < solutions_count; i++){
        u[i] = (i + 1) * (sale_price - making_price);
        for (int j = 0; j < (i + 1); j++){
            u[i] -= ((i + 1 - j) * probabilities[j] * sale_price);
        }
        if (u[i] > maxU){
            solution.clear();
            maxU = u[i];
            solution.push_back((i + 1));
        } else if (u[i] == maxU){
            solution.push_back((i + 1));
        }
        cout << "  " << u[i];
    }

    cout << ";" << endl << "The best solutions: ";
    for (vector<int>::iterator it = solution.begin(); it != solution.end(); it++){
        cout << *it << " ";
    }

    delete [] u;
    return 0;
}
