#include <bits/stdc++.h>
#include "Block.hpp"

using namespace std;

#define TRANSACTION_LIMIT 5

/***** _____ BLOCKCHAIN CLASS _____ *****/
class BLOCKCHAIN
{
    private:
        vector<BLOCK> chain;
        int difficulty;

        int p ;
        int q ;
        int a ;

        multimap<double, string> top5;
        double totalDonation = 0.0;
        set<string> idS;

    public:

        // Custom Constructor
        BLOCKCHAIN(int diff, int p, int q, int a)
        {
            difficulty = diff ;
            this->p = p;
            this->q = q;
            this->a = a;

            // Creating and mining genesis block
            BLOCK genesisBlock(1, "");
            mineBlock(genesisBlock, diff);

            chain.emplace_back(genesisBlock) ;   // Chaining genesis block
        }

        /***----- Getters -----***/
        void getTotalDonations()
        {
            cout << "TOTAL AMOUNT RAISED BY THE FUND: " << totalDonation << endl << endl;
        }

        void getMaxDonation()
        {
            cout << "HIGHEST DONATION YET:" << endl;
            auto ritr = top5.rbegin();
            double prev = ritr->first;
            while(ritr != top5.rend() && ritr->first == prev)
            {
                cout << "User ID: " << ritr->second << "  |  Amount: " << ritr->first << endl;
                prev = ritr->first;
                ritr++; 
            }
            cout << endl;
        }

        void getTotalDonators()
        {
            cout << "TOTAL PEOPLE WHO HAVE HELPED THE FUND: " << idS.size() << endl << endl;
        }

        void getTop5()
        {
            cout << "TOP 5 HIGHEST DONATIONS YET:" << endl;
            auto ritr = top5.rbegin();
            while(ritr != top5.rend())
            {
                cout << "User ID: " << ritr->second << "  |  Amount: " << ritr->first << endl;
                ritr++; 
            }
            cout << endl;
        }

        /***----- Hashing functions -----***/
        string generate_basic_hash(const string &data) const
        {
            size_t hash1 = hash<string>{}(data) ;
            size_t hash2 = hash<string>{}("GROUP_2_ASSIGNMENT") ;
            size_t combined = hash1 ^ hash2 ;
            return to_string(combined) ;
        }

        string calculateHash(BLOCK &block)
        {
            string data = block.getHash();
            data += to_string(block.getTimestamp()) + block.calculateHash();
            return generate_basic_hash(data) ;
        }

        bool mineBlock(BLOCK &newBlock, int difficulty)
        {
            string str(difficulty, '1') ; // Create a string of zeroes with length equal to difficulty

            while(newBlock.getHash().substr(0, difficulty) != str) // Keep hashing until the required number of zeroes are found
            {
                newBlock.setHash(calculateHash(newBlock)) ; // Calculate the new hash
            }
            return true;
        }

        // Add a empty block if number of entries (transactions) are full
        void createBlock()
        {
            if(chain.back().getTransactions().size() < TRANSACTION_LIMIT)
            {
                cout << "Error\n Number of transactions in current block is less than TRANSACTION_LIMIT" << endl;
                return;
            }

            int index = chain.size();
            string prevHash = chain.back().getHash();
            BLOCK newBlock(index, prevHash);
            
            if(mineBlock(newBlock, difficulty))
            {
                chain.push_back(newBlock);
            }
        }

        void addTransaction(TRANSACTION &tx)
        {
            // Check that the transaction is valid before adding it
            if(tx.user_id == "" || tx.getSender() == "" || tx.amount <= 0)
            {
                cout << "Invalid transaction" << endl ;
                return ;
            }

            // Adds new block in chain if transaction limit is exceeded
            if(chain.back().getTransactions().size() >= TRANSACTION_LIMIT)
            {
                createBlock();
            }

            // Add the transaction to the current block
            chain.back().transactions.push_back(tx);

            // Maintaining top 5 donations
            top5.insert({tx.amount, tx.user_id});
            if(top5.size() > 5)
            {
                top5.erase(top5.begin());
            }

            // Updating total donations
            totalDonation += tx.amount;

            // updating number of donators
            idS.insert(tx.user_id);
            return;
        }

        // ZERO KNOWLEDGE PROOF IMPLEMENTATION FOR VERIFICATION
        bool verifyTransaction(const TRANSACTION &tx, string user_id, double amount) const
        {
            string M = tx.M;
            int e = tx.e;
            int y = tx.y;
            int a = tx.a;
            int p = tx.p;
            int q = tx.q;
            int v = tx.v;

            int newX = ((int)((pow(a, y))*(pow(v, e)))) % p;
            string newM = to_string((int)amount);
            newM += user_id;
            int newE = hash<string>{}(newM + to_string(newX));

            if(e != newE)
            {
                return false;
            }

            return true;
        }

        // Checking if chain is valid
        bool isChainValid()
        {
            for (int i = 1 ; i < chain.size() ; ++i)
            {
                const BLOCK &currentBlock = chain[i] ;
                const BLOCK &previousBlock = chain[i - 1] ;

                if (currentBlock.previousHash != previousBlock.hash)
                {
                    return false ;
                }
            }
            return true ;
        }

        // Printing all transactions against a user
        void viewUser(string user_id) const
        {
            int count = 0;
            for (int i = 0 ; i < chain.size() ; ++i)
            {
                BLOCK currentBlock = chain[i] ;

                for (int j = 0 ; j < currentBlock.getTransactions().size() ; ++j)
                {
                    TRANSACTION currentTransaction = currentBlock.getTransactions()[j] ;
                    
                    if(currentTransaction.user_id == user_id)
                    {
                        count++;
                        cout << "Transaction #" << count;
                        cout << ":  User ID: " << currentTransaction.user_id;
                        // cout << "Sender: " << currentTransaction.getSender() << endl ;
                        cout << "    Amount: " << currentTransaction.amount << endl;
                    }
                }
            }
            cout << endl;
        }

        // Print all the transactions in all the blocks in the Bloclchain system
        void printChain()
        {
            for (int i = 0 ; i < chain.size() ; ++i)
            {
                BLOCK currentBlock = chain[i] ;
                cout << "Block #" << i + 1 << endl ;
                cout << "\tHash: " << currentBlock.getHash() << endl ;
                cout << "\tPrevious Hash: " << currentBlock.getPreviousHash() << endl ;
                cout << "\tTimestamp: " << currentBlock.getTimestamp() << endl ;
                cout << "\tTransactions: " << endl ;
                for (int j = 0 ; j < currentBlock.getTransactions().size() ; ++j)
                {
                    TRANSACTION currentTransaction = currentBlock.getTransactions()[j] ;
                    cout << "\t\t     Transaction #" << j + 1;
                    cout << ":  User ID: " << currentTransaction.user_id;
                    // cout << "Sender: " << currentTransaction.getSender() << endl ;
                    cout << "    Amount: " << currentTransaction.amount << endl;
                }
                cout << endl;
            }
        }
};