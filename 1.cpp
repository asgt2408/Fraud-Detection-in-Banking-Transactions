#include<iostream>
#include<fstream>
#include<unordered_map>
#include<sstream>
#include<vector>
#include<algorithm>
#include<ctime>
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

void analysedates(){
    for (auto &pair : accounts){
        string acc = pair.first;
        vector<Transaction> &t = pair.second;

        unordered_map<string, long long> dailytotal;

        for(auto &p : t){
            long long amt = stoi(p.amount);
            dailytotal[p.date] += amt;
        }

        for(auto &one : dailytotal){
            cout<<acc<<endl;
            cout<<"\nFor date: "<<one.first<<" , Total amount transacted: "<<one.second<<endl;

            if(one.second < 50000){
                cout<<"Normal Transaction"<<endl;
            }
            else if(one.second>50000 && one.second<200000){
                cout<<"Alert"<<endl;
            }
            else{ cout<<"Suspicious "<<endl;}
        }
    }
}

long long datetoint(const string & date){
    string s = date;
    s.erase(remove(s.begin(),s.end(),'-'),s.end());
    return stoll(s);
}

void analyseperiod(){
    string start_date;
    cout<<"Enter the start date(yyyy-mm-dd): ";
    cin>>start_date;

    string end_date;
    cout<<"Enter the end date(yyyy-mm-dd): ";
    cin>>end_date;

    long long start = datetoint(start_date);
    long long end = datetoint(end_date);

    for(auto &pair : accounts){
        string acc = pair.first;
        vector<Transaction> & txn = pair.second;

        unordered_map<string, long long> periodtotal;
        long long grandtotal = 0;

        for(auto & one : txn){
            long long datetime = datetoint(one.date);
            if(datetime>=start && datetime<=end){
                long long amount = stoi(one.amount);
                periodtotal[one.date] += amount;
                grandtotal += amount;
            }
        }
        if (grandtotal == 0) {
            cout << "\nAccount: " << acc 
                 << " -> No transactions found in this range.\n";
            continue;
        }
        cout << "\nAccount: " << acc 
                 << "\nDate Range: " << start_date << " -> " << end_date 
                 << "\nTotal Amount: " << grandtotal << endl;

            // Classification logic (same as daily)
            if (grandtotal < 50000)
                cout << "Status: Normal Transaction\n";
            else if (grandtotal >= 50000 && grandtotal < 200000)
                cout << "Status: Alert \n";
            else
                cout << "Status: Suspicious \n";
            
        
    }
    }




int main(){
    loadaccounts();
    displayaccounts();
    analysedates();
    analyseperiod();
}

