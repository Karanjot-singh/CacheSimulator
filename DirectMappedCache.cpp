#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <cmath>
#include <cstdlib>
#include <ctime>
//new
#define loop(x, a, n) for (int x = a; x < n; ++x)
typedef long long ll;
using namespace std;
//Assuming a 16 bit memory system.
int cache_size, block_size, cache_lines, number_ways, op_type, offset, num_entries = 0;
ll address, data, idx = 0;
//new
ll tag_Part, idx_part, dec_address = 0;
string s = "";

//to initialise
void pre(ll tag[][2])
{
    loop(x, 0, num_entries)
        loop(y, 0, 2)
            tag[x][y] = -1;
}
//convert from binary to decimal
ll bintod(ll n)
{
    ll num = n;
    ll val = 0;
    ll base = 1;
    ll temp = num;
    while (temp)
    {
        ll lsb = temp % 10;
        temp = temp / 10;
        val += lsb * base;
        base = base * 2;
    }
    return val;
}
// convert from decimal to binary
ll dectob(ll n, string &s)
{
    s = "";
    for (int i = 15; i >= 0; i--)
    {
        ll k = n >> i;
        if (k & 1)
            s = s + "1";
        else
            s = s + "0";
    }
    return stoi(s);
}
// to display the cache
void display(ll tag[][2])
{
    cout << "Tag  "
         << " Data" << endl;
    loop(x, 0, num_entries)
    {
        loop(y, 0, 2)
        {
            if (tag[x][y] != -1)
                cout << tag[x][y] << " ";
        }
        if (tag[x][0] != -1 && tag[x][1] != -1) //newb
            cout << endl;
    }
}

// to search in the cache for read operation
ll search(ll tag[][2], ll tag_Part, ll idx_part)
{
    if (tag[idx_part][0] == tag_Part)
        return tag[idx_part][1];
    return -1;
}

// to replace data in case of overlap
void replace(ll tag[][2], ll tag_Part, int data, int num_entries, ll address, ll idx_part)
{   //newb Tag
    cout << "Block with Tag Adress " << tag[idx_part][0] << " and Data " << tag[idx_part][1] << " is removed." << endl;
    tag[idx_part][0] = tag_Part;//newb
    tag[idx_part][1] = data;
    cout << "Block with Tag Adress " << tag[idx_part][0] << " and Data " << tag[idx_part][1] << " is added." << endl;
}

//write operation
void write(ll tag[][2], ll tag_Part, int data, ll address, ll idx_part)
{
    // cout << tag_Part << " " << idx_part << endl;
    int fl = 0;
    if (tag[idx_part][1] == -1)
    {
        tag[idx_part][0] = tag_Part;
        tag[idx_part][1] = data;
        fl = 1;
    }
    if (fl == 0)
    {
        cout << "Cache Full, Replacement" << endl;
        replace(tag, tag_Part, data, num_entries, address, idx_part);
    }

    cout << "Write operation successful " << endl;
}

int main(int argc, const char *argv[])
{
    cout << "##############################################" << endl;
    cout << "Direct Mapped Cache Simulator" << endl;
    cout << "by Karanjot Singh" << endl;
    cout << "##############################################" << endl;
    cout << "Memory size : 16 bit" << endl;
    cout << "Please enter the cache size in KB: " << endl;
    cin >> cache_size;
    cout << "Please enter the block size in bytes: " << endl;
    cin >> block_size;
    //offset calculation
    offset = log2(block_size);
    //calculation of index
    num_entries = log2(cache_size);
    num_entries = num_entries + 10 - offset;
    idx = num_entries;
    num_entries = pow(2, num_entries);
    // cout << idx << "id-num" << num_entries << endl;
    ll tag[num_entries][2]; //0 column is tag array 1 column is data array
    // new
    pre(tag);
    cout << "##################### Main Menu #########################" << endl;
    cout << "Please enter 1 for read , 2 for write , 3 for display , 0 for exit: " << endl;
    cin >> op_type;
    while (op_type != 0)
    {
        if (op_type == 1)
        {
            cout << "Please enter the 16 bit address > than " << offset << " bits: " << endl;
            cin >> address;
            dec_address = bintod(address); //stores the address in decimal
            // cout<<"dec"<<dec_address<<endl;
            tag_Part = dec_address >> offset; // calculation the tag part of address
            // cout << "tag decimal val " << tag_Part << endl;
            idx_part = tag_Part % (int)(pow(2, idx));
            tag_Part = tag_Part >> idx;
            tag_Part = dectob(tag_Part, s); //1000000001
            idx_part = bintod(idx_part);
            // cout << "tag value in binary " << tag_Part <<" "<<idx_part<< endl;
            //newb
            ll val = search(tag, tag_Part, idx_part);
            if (val == -1)
                cout << "Miss. Address not found" << endl;
            else
                cout << "Hit. "
                     << "Data for this Address is " << val << endl;
        }
        else if (op_type == 2)
        {
            cout << "Please enter the new 16 bit address > than " << offset << " bits: " << endl;
            cin >> address;
            dec_address = bintod(address); //stores the address in decimal
            // cout<<"dec"<<dec_address<<endl;
            tag_Part = dec_address >> offset; // calculation the tag part of address
            // cout << "tag decimal val " << tag_Part << endl;
            idx_part = tag_Part % (int)(pow(2, idx));
            tag_Part = tag_Part >> idx;
            tag_Part = dectob(tag_Part, s); //1000000001
            idx_part = bintod(idx_part);
            // cout << "tag value in binary " << tag_Part <<" "<<idx_part<< endl;
            cout << "Please enter the numerical data : " << endl; //assuming positive integer data
            cin >> data;
            write(tag, tag_Part, data, address, idx_part);
        }
        else if (op_type == 3)
            display(tag);
        else
            break;

        cout << "##################### Main Menu #########################" << endl;
        cout << "Please enter 1 for read , 2 for write , 3 for display , 0 for exit: " << endl;
        cin >> op_type;
    }
}
