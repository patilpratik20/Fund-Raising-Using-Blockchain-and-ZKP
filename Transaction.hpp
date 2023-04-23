#include <bits/stdc++.h>

using namespace std;

/***** _____ TRANSACTION CLASS _____ *****/
class TRANSACTION
{
    private:
        int s;   // PRIVATE KEY (0 < s < q {To be made randomly})
        
    /*------------- TRANSACTION DATA -------------*/
        string sender;

    public:
    /*------------- TRANSACTION DATA -------------*/
        double amount;
        string user_id;

    /*------------- ALGORITHM VARIABLES -------------*/

      /*GLOBAL PUBLIC KEYS*/
        int p;   // Prime no
        int q;   // prime no and a prime factor of p-1 

        int a;   // a^q = 1%p  
      // To say that a number a is 1 modulo p means that p divides a−1. So, in particular, the numbers 1,p+1,2p+1,… are all equal to 1 modulo p

      // (p = 2, q = 3, a = 5)
        
        int v;   // GLOBAL PUBLIC KEY
        string M;

      /*INTERMEDIATE VARIABLES*/
        int r;
        int x;

      /*SIGNATURE PAIRS*/
        int e;
        int y;


      // Constructor
        TRANSACTION(double amount, string sender, int p, int q, int a, string user_id)
        {   
            this->amount = amount;
            this->sender = sender;
            this->p = p;
            this->q = q;
            this->a = a;
            while(s < 1 || s > q){
                srand(time(NULL));
                s = rand()%q;
            }
            v = ((int)pow(a, -s)) % q;
            while(r < 1 || r > q){
                srand(time(NULL));
                r = rand() % q;
            }
            x = ((int)pow(a, -r)) % p;
            M = to_string((int)amount);
            M += user_id;
            e = hash<string>{}(M + to_string(x));
            y = (r + s*e) % q;
            this->user_id = user_id;
        }

        string getSender()
        {
            return sender;
        }
};