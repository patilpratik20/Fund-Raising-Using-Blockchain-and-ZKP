# Decentralized Crowd Funding Platform

## Contributors
| Name |
| :-------- |
| `Pratik Patil` |
| `Himanshu Patil` |
| `Varad Gorantyal` |
| `Saksham Sawhney` |
| `Sahil Somil` |

## Aim
This project aims to develop a system for crowd funding platform utilising the ZKP(Zero Knowledge Proof), which is implemented using through Schnorr Signature Scheme.

## Technology Used
- C++

## Working of Every Module

### main.cpp file
Functions:
- `main()`: The main function of the program which controls the flow of execution.
- `BLOCKCHAIN(int, int, int, int)`: A constructor for the `BLOCKCHAIN` class which initializes the blockchain with the specified parameters.
- `addTransaction(TRANSACTION)`: Adds a new transaction to the blockchain.
- `verifyTransaction(TRANSACTION, string, double)`: Verifies if a transaction is valid.
- `viewUser(string)`: Prints all transactions related to a specific user.
- `getTotalDonations()`: Prints the total amount of donations made.
- `getTotalDonators()`: Prints the total number of people who have made a donation.
- `getMaxDonation()`: Prints the highest donation made so far.
- `getTop5()`: Prints the top 5 highest donations made so far.
- `isChainValid()`: Checks if the blockchain is valid.
- `printChain()`: Prints the entire blockchain.

Variables:
- `p`: A prime number used in the encryption algorithm for transactions.
- `q`: Another prime number used in the encryption algorithm for transactions.
- `a`: A constant used in the encryption algorithm for transactions.
- `count`: The number of transactions the user wants to add to the blockchain.
- `i`: A counter variable used in the `while` loop for adding transactions.
- `tx`: A vector of `TRANSACTION` objects representing the transactions added to the blockchain.
- `amount`: The amount of money being transferred in a transaction.
- `sender`: The name of the person sending the money in a transaction.
- `user_id`: A unique identifier for every user in the blockchain.
- `tx_temp`: A `TRANSACTION` object used to store a transaction before it is added to the blockchain.
- `control`: An integer variable used to control the switch case in the program.
- `temp`: A temporary variable used to store the index of a transaction to be verified.
- `user_idTemp`: A temporary variable used to store the user_id of a user whose transactions are to be viewed or verified.
- `amountTemp`: A temporary variable used to store the amount of money to be verified in a transaction.

### Blockchain.hpp file
Functions:
- `BLOCKCHAIN(int diff, int p, int q, int a)`: a constructor that takes the mining difficulty and the integers `p`, `q`, and `a` as arguments. It creates a genesis    block and adds it to the blockchain.
- `void getTotalDonations()`: a function that prints the total amount of donations.
- `void getMaxDonation()`: a function that prints the highest donation and the user ID who made it.
- `void getTotalDonators()`: a function that prints the total number of unique donators.
- `void getTop5()`: a function that prints the top 5 donations with the user IDs and donation amounts.
- `string generate_basic_hash(const string &data) const`: a function that generates a hash for a given string `data`.
- `string calculateHash(BLOCK &block)`: a function that calculates the hash for a `BLOCK` object.
- `bool mineBlock(BLOCK &newBlock, int difficulty)`: a function that mines a `BLOCK` object by repeatedly calculating hashes until a hash with the required number of leading zeroes is found.
- `void createBlock()`: a function that creates a new block in the blockchain if the current block has reached its transaction limit.
- `void addTransaction(TRANSACTION &tx)`: a function that adds a new transaction to the current block if it is valid, and creates a new block if the current block has reached its transaction limit.
- `bool verifyTransaction(const TRANSACTION &tx, string user_id, double amount) const`: a function that implements a zero-knowledge proof for verifying transactions.
- `bool isChainValid()`: a function that checks if the blockchain is valid by iterating over all the blocks in the chain and verifying their hashes and transactions.

Variables:
- `vector<BLOCK> chain`: a vector of `BLOCK` objects representing the blockchain.
- `int difficulty`: an integer representing the mining difficulty.
- `int p`, `int q`, `int a`: integers used in the zero-knowledge proof for verifying transactions.
- `multimap<double, string> top5`: a multimap that stores the top 5 donations with the user IDs as keys and donation amounts as values.
- `double totalDonation`: a double representing the total amount of donations.
- `set<string> idS`: a set that stores the unique IDs of the donators.

### Block.hpp file
Functions:
- `BLOCK(int idx, const string &prevHash)`: A constructor function that initializes the `BLOCK` object with an `index` and a `previousHash`, sets the current `timeStamp`, and calculates the `hash` of the block.
- `void setHash(const string &newHash)`: A setter function to update the value of the `hash` variable.
- `void setTransactions(std::vector<TRANSACTION> transactions)`: A setter function to update the value of the `transactions` vector.
- `void setTimestamp(time_t timestamp)`: A setter function to update the value of the `timeStamp` variable.
- `void setPreviousHash(string &ph)`: A setter function to update the value of the `previousHash` variable.
- `vector<TRANSACTION> getTransactions()`: A getter function to return the `transactions` vector.
- `string getHash()`: A getter function to return the `hash` value.
- `string getPreviousHash()`: A getter function to return the `previousHash` value.
- `int getTimestamp()`: A getter function to return the `timeStamp` value.
- `string calculateHash()`: A function to calculate the hash of the block data, including the `index`, `previousHash`, `timeStamp`, and all `transactions` in the block.

Variables:
- `int index`: An integer to denote the position of the block in the blockchain system.
- `int timeStamp`: A Unix timestamp to maintain a record of all the transactions in the block.
- `vector<TRANSACTION> transactions`: A vector of `TRANSACTION` objects to store all the transactions in the block.
- `double Max`: A double variable initialized to -1.
- `string previousHash`: A string variable to store the hash code of the previous block in the blockchain.
- `string hash`: A string variable to store the hash code of the current block or the block under consideration.

### Transaction.hpp file
Functions:
- `hash<string>{}(M + to_string(x))`: computes a hash value for a given string, which is a deterministic output based on the input. Here, it is used to generate the signature for the transaction.

Variables:
- `s`: a private key for the transaction.
- `sender`: a string representing the sender of the transaction.
- `amount`: a double representing the amount of the transaction.
- `user_id`: a string representing the user ID associated with the transaction.
- `p`: a prime number used as a parameter in the algorithm.
- `q`: another prime number that is a prime factor of `p-1`, also used as a parameter in the algorithm.
- `a`: a number such that `a^q = 1 mod p`, used as a parameter in the algorithm.
- `v`: a global public key used in the algorithm.
- `M`: a string that combines the amount and user ID of the transaction, used to generate the signature.
- `r`: an intermediate variable used in the algorithm.
- `x`: another intermediate variable used in the algorithm.
- `e`: a signature value generated using the `hash` function.
- `y`: the final signature value for the transaction, generated using `r`, `s`, and `e`.
