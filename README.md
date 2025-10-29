# Fraud-Detection-in-Banking-Transactions
This project aims to develop an intelligent fraud detection system that identifies suspicious or high-risk banking transactions by analyzing real-time transaction data.

Fields:
Transaction ID, Account ID, Date, Time, Amount, Location

It takes all the transaction data from transactions file(.txt) and sort them or you can say
doing hashing of all account id's with their transactions and store them wisely.

Ex. output: 
Account ID: ACC1078
Transactions:
  Transaction ID: TXN005 | Date: 2025-08-13 | Time: 10:25 | Amount: 120000 | Location: Delhi
  Transaction ID: TXN006 | Date: 2025-08-13 | Time: 10:45 | Amount: 99000 | Location: Delhi

Fraud Checks:
1. In this basically, we have found day wise transactions.
    Normal : if amount < 50000, in one day
    Suspicious : if amount > 200000 in one day
    Alert: if amount > 50000 and amount < 200000 in one day

2. Now, we are taking starting date and ending date to find the transactions done and then check the following suspicious things.
    

