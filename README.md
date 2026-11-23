Fraud Detection in Banking Transactions
A C++ console application that flags banking transactions for review based on transaction amounts, rapid activity, and quick changes between cities.
Features
- Load and summarize 180 sample transactions across six accounts.
- View daily reports and classify accounts as Normal, Alert, or Suspicious.
- Analyze individual accounts, calculate a risk score out of 10, and view saved risk history.
- Explore relationships between accounts that share suspicious transaction patterns.
Run locally

From the repository folder, compile and run with transactions.txt in the same directory:
g++ -std=c++17 1.cpp -o fraud_detection
./fraud_detection


For a quick demo, choose option 2, enter 2026-12-01, and select Y for the detailed report.
Agile Development Lab
The project illustrates an iterative and incremental SDLC. Each increment supports a user story, starting with transaction import and daily reports, then adding account analysis, saved risk history, and relationship analysis. The lab report includes the proposed sprint plan, acceptance criteria, and test results.
