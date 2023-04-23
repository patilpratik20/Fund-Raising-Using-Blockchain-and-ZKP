#include <bits/stdc++.h>
#include "Blockchain.hpp"

using namespace std;

int main()
{
    int p = 2, q = 3, a = 5;
    BLOCKCHAIN blockchain(4,p,q,a);

    cout << "How many transactions do you want to add(5 transactions per block): ";
    int count, i = 0;
    cin >> count;
    vector<TRANSACTION> tx;
    while(i != count){
        double amount;
        string sender, user_id;
        cout << i + 1 << ") ";
        cout << "Amount: "; cin >> amount;
        cout << "   Sender name: "; cin >> sender;
        cout << "   User_Id(unique for every user): "; cin >> user_id;
        TRANSACTION tx_temp{amount,sender,p,q,a,user_id};
        tx.push_back(tx_temp);
        blockchain.addTransaction(tx[i]);
        i++;
    }

    cout << "\n\n*****************  PRESS A KEY  *****************\n" << endl 
            << "1 --> VERIFY A TRANSACTION" << endl             << "2 --> SHOW ALL TRANSACTIONS AGAINST A USER" << endl 
            << "3 --> TOTAL AMOUNT RAISED BY THE FUND" <<endl   << "4 --> TOTAL PEOPLE WHO HAVE HELPED THE FUND" << endl 
            << "5 --> HIGHEST DONATION YET" << endl             << "6 --> TOP 5 HIGHEST DONATIONS YET" << endl    
            << "7 --> CHECK IF CHAIN IS VALID" << endl          << "8 --> PRINT THE CHAIN"<< endl
            << "9 --> END PROGRAM\n" << endl;
    int control = -1;
    int temp;
    string user_idTemp;
    double amountTemp;
    while(control != 9){
        cout << "Input: ";
        cin >> control;
        switch(control){
            case 1:
                cout << "Which transction to verify: "; cin >> temp;
                cout << "Input details to be checked with respect to the transaction:" << endl;
                cout << "User ID: "; cin >> user_idTemp;
                cout << "Amount"; cin >> amountTemp;
                if(blockchain.verifyTransaction(tx[temp-1], user_idTemp, amountTemp) == true)
                    cout << "VERIFIED\n" << endl;
                else
                    cout << "UNVERIFIED\n" << endl;
                break;
            case 2:
                cout << "Input the user_id of the user whose transactions are to be seen: "; cin >> user_idTemp;
                blockchain.viewUser(user_idTemp);
                break;
            case 3:
                blockchain.getTotalDonations();
                break;
            case 4:
                blockchain.getTotalDonators();
                break;
            case 5:
                blockchain.getMaxDonation();
                break;
            case 6:
                blockchain.getTop5();
                break;
            case 7:
                if(blockchain.isChainValid() == true)
                    cout << "CHAIN IS VALID\n" << endl;
                else
                    cout << "CHAIN IS NOT VALID\n" << endl;
                break;
            case 8:
                blockchain.printChain();
                break;
            case 9:
                break;
            default:
                cout << "Try another input" << endl;
                break;
        }
    }
    return 0;
}
// int main()
// {
//     // string user_id ;
//     // cout << "Enter the User ID" << endl ;
//     // cin >> user_id ;
//     int p = 2, q = 3, a = 5;
//     // Initialize blockchain
//     BLOCKCHAIN blockchain(1, p, q, a);

//     // Create some transactions
//     TRANSACTION tx1{100.0, "Alice", p, q, a, "1234"} ;
//     TRANSACTION tx2{20.0, "Bob", p, q, a, "12345"} ;
//     TRANSACTION tx3{5.0, "Charlie", p, q, a, "123456"} ;
//     TRANSACTION tx4{15.0, "Bob", p, q, a, "12345"} ;
//     // Add transactions to the blockchain
//     blockchain.addTransaction(tx1) ;
//     blockchain.addTransaction(tx2) ;
//     blockchain.addTransaction(tx3) ;
//     blockchain.addTransaction(tx4) ;
//     blockchain.addTransaction(tx4) ;
//     blockchain.addTransaction(tx4) ;
//     blockchain.addTransaction(tx4) ;
//     cout << "Verification: "<< blockchain.verifyTransaction(tx2, "12345", 20.0) << endl;
//     cout << "Verification: "<< blockchain.verifyTransaction(tx2, "1234", 20.0) << endl;
//     cout << "Verification: "<< blockchain.verifyTransaction(tx3, "1234", 20.0) << endl;
//     cout << "Verification: "<< blockchain.verifyTransaction(tx3, "123456", 5.0) << endl;
//     // Print the latest block's hash
//     // cout << "Latest block's hash: " << blockchain.getLatestBLOCK().getHash() << endl ;
//     blockchain.printCHAIN();
//     blockchain.getTotalDonations();
//     blockchain.getMaxDonations();
//     blockchain.getTotalDonators();
//     cout << endl;
//     blockchain.viewUser("12345");

//     cout << endl;
//     cout << blockchain.isChainValid();

//     return 0;
// }