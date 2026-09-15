
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <iomanip>
#include <cmath>
#include <random>
#include <set>
using namespace std;

struct employee {
    string name;
    int EIN;
    double rate;
    double hours;
    double grossPay;

};


void parseLine(string line,employee &emp) {
    emp.name = line.substr(0, line.find(","));
    line = line.substr(line.find(",")+1);
    emp.EIN = stoi(line.substr(0, line.find(",")));
    line = line.substr(line.find(",")+1);
    emp.rate = stod(line.substr(0, line.find(",")));
    line = line.substr(line.find(",")+1);
    emp.hours = stod(line.substr(0, line.find(",")));
};




void getDataFromCSV(vector<employee> &employees) {
    string line;
    ifstream csv("EmployeeData.csv");
    getline(csv,line);
    while (getline(csv,line)) {
        employee nextEmployee;
        parseLine(line, nextEmployee);
        employees.push_back(nextEmployee);
    }
    csv.close();

};

void randomize(vector<employee> &employees) {
    random_device rd;
    mt19937 gen(rd());
    shuffle(employees.begin(), employees.end(), gen);

}



void printTable(vector<employee> employees) {
    cout<<fixed<<setprecision(2);
    cout<<"\nNAME               EIN        HOURLY RATE    HOURS WORKED   GROSS PAY\n";
    cout<<"----------------------------------------------------------------------";
    for (auto emp: employees) {
        cout<<endl;
        cout<<emp.name<<setw(23-emp.name.length())<<emp.EIN<<setw(10)<<"$"<<emp.rate<<setw(15)<<emp.hours<<setw(10)<<"$"<<emp.grossPay;
    }
}

int main() {
    vector<employee> employees;
    getDataFromCSV(employees);
    for (auto &employee: employees) {
        employee.grossPay = employee.rate * employee.hours;
        employee.grossPay = round(employee.grossPay*100)/100;
    };
    printTable(employees);
    randomize(employees);
    printTable(employees);
    sort(employees.begin(), employees.end(),[](employee a,employee b)->bool {return a.grossPay > b.grossPay;});
    printTable(employees);


    return 0;
};












