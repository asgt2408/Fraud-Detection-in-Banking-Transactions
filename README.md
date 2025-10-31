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
a. In this basically, we have found day wise transactions.
    Normal : if amount < 50000, in one day
    Suspicious : if amount > 200000 in one day
    Alert: if amount > 50000 and amount < 200000 in one day

b. Now, we are taking starting date and ending date to find the transactions done and then check the following suspicious things.
    we have now, converted date to time for our ease to calculate the exact no. of days between two dates.
    We have classified between three categories:
    
    i) if days <= 7, then normal:50000, Alert:50000-200000, suspicious in else
    ii) if days>=7 and less than 30, normal: 1000000, alert: 1000000-2000000 and suspicious in else
    iii) if days beyond 30, normal: 3000000, alert: 3000000-5000000 and suspicious in else

c. Time wise breakup

    1. 5+ transactions in under 10 min, suspicious
    2. between 2 and 5, alert
    3. else normal

    1. 15+ transactions in under 30 min, suspicious
    2. between 10 and 15, alert
    3. else normal

    1. 30+ transactions in 1 hr, suspicious
    2. between 20 and 30, alert
    3. else normal

