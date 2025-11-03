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

    if(days_diff==1){
        cout<<"For: " <<start_date<<" Analysis\n";
    }

    else if (days_diff>1 && days_diff <= 7)
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

// Convert "hh:mm" → integer like 930 for 09:30
int timeToInt(const string &t) {
    int h = 0, m = 0;
    sscanf(t.c_str(), "%d:%d", &h, &m);
    return h * 100 + m;
}

// Get absolute difference in minutes between two times (same day)
int timeDiffMinutes(const string &t1, const string &t2) {
    int h1, m1, h2, m2;
    sscanf(t1.c_str(), "%d:%d", &h1, &m1);
    sscanf(t2.c_str(), "%d:%d", &h2, &m2);
    return abs((h2 * 60 + m2) - (h1 * 60 + m1));
}

void analysetime() {
    cout << "\n\n Time-Based Fraud Detection Report\n"
         << "----------------------------------------\n";

    string target_date;
    cout << "Enter the date to analyze (yyyy-mm-dd): ";
    cin >> target_date;

    for (auto &it : accounts) {
        string acc = it.first;
        vector<Transaction> &tx = it.second;

        // Filter transactions for selected date
        vector<Transaction> dayTx;
        for (auto &t : tx) {
            if (t.date == target_date)
                dayTx.push_back(t);
        }

        if (dayTx.empty())
            continue;

        sort(dayTx.begin(), dayTx.end(), [](const Transaction &a, const Transaction &b) {
            return a.time < b.time;
        });

        bool flagged = false;

        cout << "\nAccount: " << acc << " | Date: " << target_date << "\n";

        for (int i = 0; i < (int)dayTx.size(); i++) {
            int count10 = 1;

            for (int j = i + 1; j < (int)dayTx.size(); j++) {
                int diff = timeDiffMinutes(dayTx[i].time, dayTx[j].time);
                if (diff <= 10)
                    count10++;
                else
                    break;
            }

            // --- 10-min window analysis ---
            if (count10 > 5) {
                cout << "Suspicious Activity (10-min window): "
                     << count10 << " transactions within 10 minutes (starting at "
                     << dayTx[i].time << ")\n"
                     << " Reason: More than 5 rapid transactions is abnormal.\n"
                     << " -> Possible automation or system misuse.\n";
                flagged = true;
                break;
            } 
            else if (count10 >= 2 && count10 <= 5) {
                cout << "Alert (10-min window): "
                     << count10 << " transactions within 10 minutes (starting at "
                     << dayTx[i].time << ")\n"
                     << "Explanation: Quick repeated transactions -- may indicate card testing or fraud probes.\n";
                flagged = true;
                break;
            }
        }

        // ✅ If no suspicious or alert activity found
        if (!flagged) {
            cout << "Status: Normal -> " << dayTx.size()
                 << " transactions recorded for this date.\n"
                 << "Explanation: Transaction frequency within acceptable range.\n";
        }
    }
}


int main(){
    loadaccounts();
    displayaccounts();
    //analysedates();
    //analyseperiod();
    analysetime();
}


