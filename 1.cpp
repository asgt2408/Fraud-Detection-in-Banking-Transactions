#include<iostream>
#include<fstream>
#include<unordered_map>
#include<sstream>
#include<vector>
using namespace std;

struct Transaction{
    string trans_id;
    string acc_id;
    string date;
    string time;
    string amount;
    string location;
};

unordered_map<string, vector<Transaction>> accounts;

void loadaccounts(){

    ifstream account_file("transactions.txt");

    if(!account_file){
        cout<<"No account found";
        return;
    }

    string id;

    while(getline(account_file,id)){
        
        stringstream ss(id);
        string acc_id, trans_id, date, location;
        string time, amount;

        if (getline(ss,trans_id,'|') &&
            getline(ss,acc_id,'|') &&
            getline(ss,date,'|') &&
            getline(ss,time,'|') &&
            getline(ss,amount,'|') &&
            getline(ss,location,'|'))
            {

            Transaction t{trans_id, acc_id, date,time, amount,location};
            accounts[acc_id].push_back(t);
        }


    }

    account_file.close();
}

void displayaccounts() {
    for (auto &pair : accounts) {
        cout << "\nAccount ID: " << pair.first << endl;
        cout << "Transactions:\n";
        for (auto &t : pair.second) {
            cout << "  Transaction ID: " << t.trans_id
                 << " | Date: " << t.date
                 << " | Time: " << t.time
                 << " | Amount: " << t.amount
                 << " | Location: " << t.location << endl;
        }
    }
}

int main(){
    loadaccounts();
    displayaccounts();
}

