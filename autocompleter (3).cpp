// ALISSEN MORENO 
#include "autocompleter.h"
#include<vector>
#include<string>
using namespace std;

Autocompleter::Autocompleter()
{
    // MAKE ROOT NULLPTR 
    root = nullptr;
}

void Autocompleter::insert(string x, int freq)
{
    //How would we pass an entry to this function?
    //Note that you don't have an entry object yet.
    //So how would we make an entry object?
    Entry astronauts; // just call it whatever 
    astronauts.s = x;
    astronauts.freq = freq;

    insert_recurse(astronauts, root); // let's send this astronaut to where it needs to go
    //ok we done 
}
// THE SIZE CALL IT RECURSIVELY 
int Autocompleter::size()
{
    return size_recurse(root); // iguess this works 
}

void Autocompleter::completions(string x, vector<string>& T)
{
    T.clear();
    vector<Entry>ANOTHER_VECTOR;
    completions_recurse(x, root, ANOTHER_VECTOR);

    /*
    Sort from all of the completions that you have from most frequent
    to least frequent. But make sure to account the different amount of
    completions that you have.
    */
    // IF WE HAVE 0
    if (ANOTHER_VECTOR.size() == 0)
        return;
    // IF WE ONLY HAVE 1
    else if (ANOTHER_VECTOR.size() == 1) { T.push_back(ANOTHER_VECTOR[0].s); }


    else if (ANOTHER_VECTOR.size() == 2)
    {
        // IF WE ONLY HAVE 2
        if (ANOTHER_VECTOR[0].freq < ANOTHER_VECTOR[1].freq)
        {
            swap(ANOTHER_VECTOR[0], ANOTHER_VECTOR[1]);
            // T.push_back(ANOTHER_VECTOR[0].s);
            // T.push_back(ANOTHER_VECTOR[1].s);
        }
        // for both we're still inputing them in this order so... no else needed 
        T.push_back(ANOTHER_VECTOR[0].s);
        T.push_back(ANOTHER_VECTOR[1].s);

    }
    else if (ANOTHER_VECTOR.size() >= 3)
    {// EHH I JUST INITIALIZED IT HERE 
      // i initialized biggest so that i wouldn't get any errors, this literally fixed it 
      // idk if this might look similar to what you're doing in AC2 but 
        int biggest = 0;
        for (int i = 0; i < 3; i++) // constant run time
        {// RESET BIGGEST !!! 
          // I also reset it here 
            biggest = 0;
            for (int j = 0; j < ANOTHER_VECTOR.size(); j++) // run time of k because of the completions in this vector 
            {
                // COMPARE THEM AND STORE IT IN J
                if (ANOTHER_VECTOR[j].freq > ANOTHER_VECTOR[biggest].freq)
                    biggest = j;
            }
            // sooooooo the erase function is k because of the completions in the vecor ANOTHER_VECTOR
            T.push_back(ANOTHER_VECTOR[biggest].s);
            ANOTHER_VECTOR.erase(ANOTHER_VECTOR.begin() + biggest);
        }
    }
}

int Autocompleter::size_recurse(Node* p)
{
    //again shoutout to the TA's for showing us how to do this last semester y'all the real MVPS
    if (p == nullptr)
        return 0;
    return size_recurse(p->left) + size_recurse(p->right) + 1;
}

void Autocompleter::completions_recurse(string x, Node* p, vector<Entry>& C)
{
    if (p == nullptr)
        return;

    Entry astronauts; // just call it whatever 
    astronauts.s = p->e.s;
    astronauts.freq = p->e.freq;

    if (p->e.s.find(x) == 0)
    {
        C.push_back(astronauts);
        completions_recurse(x, p->left, C);
        completions_recurse(x, p->right, C);
    }

    else if (p->e.s > x)
    {
        completions_recurse(x, p->left, C);
    }
    else
        completions_recurse(x, p->right, C);
}

void Autocompleter::insert_recurse(Entry e, Node*& p)
{
    if (p == nullptr) { p = new Node(e); }
    else
    {
        //(x < p->data)
        if (e.s < p->e.s)
        {
            insert_recurse(e, p->left);
        }
        else
        {
            insert_recurse(e, p->right);
        }
        update_height(p);
        //don't forget to update height 
        rebalance(p);
    }
}

void Autocompleter::rebalance(Node*& p)
{ // let's make it more complicated because why nmot 
    if (height((*p).right) > height((*p).left) + 1)
    {
        if (height(p->right->right) > height(p->right->left))
            left_rotate(p);

        else {
            right_rotate((*p).right)/*-> left or right?*/;
            /*You need 1 more rotation.*/
            left_rotate(p);
        }
    }

    else if (height((*p).left) > height((*p).right) + 1)
    {
        if (height(p->left->left) > height(p->left->right))
        {
            right_rotate(p);
        }
        else
        {
            left_rotate((*p).left);
            right_rotate(p);
        }
    }

    else {
        //DO NOTHING AS PER SCHWELLER 
    }

}

void Autocompleter::right_rotate(Node*& p)
{
    Node* Butterfly = p;
    Node* Purse = p->left;
    Node* Switch_p = Purse->right;

    Butterfly->left = Switch_p;
    Purse->right = Butterfly;
    p = Purse;
    // now we updated the height from the header file 
    update_height(Butterfly);
    update_height(Purse);

}
void Autocompleter::left_rotate(Node*& p)
{
    //let's randomize because why not, life is too short 
    Node* Butterfly = p;
    Node* Purse = p->right;
    Node* Switch_p = Purse->left;

    Butterfly->right = Switch_p;
    Purse->left = Butterfly;
    p = Purse;
    // now we updated the height from the header file 
    update_height(Butterfly);
    update_height(Purse);


}
