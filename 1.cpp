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
    time_t datetotime(const string &date) {
    struct tm tm{};
    sscanf(date.c_str(), "%d-%d-%d", &tm.tm_year, &tm.tm_mon, &tm.tm_mday);
    tm.tm_year -= 1900; 
    tm.tm_mon -= 1;     
    tm.tm_hour = 0;
    tm.tm_min = 0;
    tm.tm_sec = 0;
    return mktime(&tm);
}

//  Period-wise analysis (real date range)
void analyseperiod() {
    string start_date, end_date;
    cout << "\nEnter the start date (yyyy-mm-dd): ";
    cin >> start_date;
    cout << "Enter the end date (yyyy-mm-dd): ";
    cin >> end_date;

    time_t start = datetotime(start_date);
    time_t end = datetotime(end_date);

    // Calculate actual difference in days
    double days_diff = difftime(end, start) / (60 * 60 * 24) + 1;
    cout << "\nDate range covers approximately " << days_diff << " days.\n";

    if (days_diff <= 7)
        cout << " Duration Type: Weekly Analysis\n";
    else if (days_diff > 7 && days_diff <= 30)
        cout << "Duration Type: Monthly Analysis\n";
    else
        cout << " Duration Type: Long-term Analysis\n";

    for (auto &pair : accounts) {
        string acc = pair.first;
        vector<Transaction> &txn = pair.second;

        unordered_map<string, long long> periodtotal;
        long long grandtotal = 0;

        for (auto &one : txn) {
            time_t datetime = datetotime(one.date);
            if (datetime >= start && datetime <= end) {
                long long amount = stoll(one.amount);
                periodtotal[one.date] += amount;
                grandtotal += amount;
            }
        }

        if (grandtotal == 0) {
            cout << "\nAccount: " << acc
                 << " → No transactions found in this range.\n";
            continue;
        }

        cout << "\nAccount: " << acc
             << "\nDate Range: " << start_date << " → " << end_date
             << "\nTotal Amount: " << grandtotal << endl;

        // Classification logic
        if(days_diff<=7){
        if (grandtotal < 50000)
            cout << "Status: Normal Transaction\n";
        else if (grandtotal >= 50000 && grandtotal < 200000)
            cout << "Status: Alert \n";
        else
            cout << "Status: Suspicious \n";
        }

        else if(days_diff>=7 && days_diff<=30){
            if (grandtotal < 1000000)
            cout << "Status: Normal Transaction\n";
        else if (grandtotal >= 1000000 && grandtotal <= 2000000)
            cout << "Status: Alert \n";
        else
            cout << "Status: Suspicious \n";
        }
        else{
            if (grandtotal < 3000000)
            cout << "Status: Normal Transaction\n";
        else if (grandtotal >= 3000000 && grandtotal <= 5000000)
            cout << "Status: Alert \n";
        else
            cout << "Status: Suspicious \n";
        }
}
}

int main(){
    loadaccounts();
    displayaccounts();
    //analysedates();
    analyseperiod();
}


