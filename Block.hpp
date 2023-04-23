#include <bits/stdc++.h>
#include "Transaction.hpp"

using namespace std;

class BLOCK
{
    private:
        int index;                             // to denote position in blockchain system
        int timeStamp;                         // to maintain track record of all the transactions

    public:
        vector<TRANSACTION> transactions;      // to store all the transactions
        string previousHash;                   // Hashcode of previous block
        string hash;                           // Hashcode of current block or lock under consideration

        // Custom Constructor
        BLOCK(int idx, const string &prevHash)
        {
            index = idx;
            previousHash = prevHash;
            timeStamp = time(NULL);
            hash = calculateHash();
        }

        /***----- Setters -----***/
        void setHash(const string &newHash)
        {
            hash = newHash ;
            return ;
        }

        void setTransactions(std::vector<TRANSACTION> transactions)
        {
            this->transactions = transactions ;
            return ;
        }

        void setTimestamp(time_t timestamp)
        {
            this->timeStamp = timestamp ;
            return ;
        }

        void setPreviousHash(string &ph)
        {
            previousHash = ph ;
            return ;
        }

        /***----- Getters -----***/
        vector<TRANSACTION> getTransactions()
        {
            return transactions ;
        }

        string getHash()
        {
            return hash ;
        }

        string getPreviousHash()
        {
            return previousHash ;
        }

        int getTimestamp()
        {
            return timeStamp ;
        }


    private: 
        string generate_basic_hash(string &data)
        {
            size_t hash1 = std :: hash<string>{}(data) ;
            size_t hash2 = std :: hash<string>{}("GROUP_2_ASSIGNMENT") ;
            size_t combined = hash1 ^ hash2 ;

            return std::to_string(combined) ;
        }

    public:
        string calculateHash()
        {
            string txsHash = "" ;
            for (auto &tx : transactions)
            {
                txsHash += to_string(tx.amount) + tx.getSender() + to_string(tx.p) + to_string(tx.q) + to_string(tx.a);
            }
            string blockData = to_string(index) + previousHash + to_string(timeStamp) + txsHash ;
            string hash = generate_basic_hash(blockData) ; // Calculate hash of blockData

            return hash ;
        }
};