#include<bits/stdc++.h>
using namespace std;

class symbol_info
{
private:
    string name;
    string type;

    string symbol_category;                    //  (variable/array/function)
    string data_type;                           // int/float/void/char
    int array_size;                              
    vector<pair<string,string>> parameters;      // (data_type, param_name) pairs for func 

public:
    symbol_info(string name, string type)
    {
        this->name = name;
        this->type = type;
        this->symbol_category = "";
        this->data_type = "";
        this->array_size = 0;
    }
    string get_name()
    {
        return name;
    }
    string get_type()
    {
        return type;
    }
    void set_name(string name)
    {
        this->name = name;
    }
    void set_type(string type)
    {
        this->type = type;
    }


    string getname()
    {
        return name;
    }
    string gettype()
    {
        return type;
    }

    string get_symbol_category()
    {
        return symbol_category;
    }
    void set_symbol_category(string category)
    {
        this->symbol_category = category;
    }

    string get_data_type()
    {
        return data_type;
    }
    void set_data_type(string data_type)
    {
        this->data_type = data_type;
    }

    int get_array_size()
    {
        return array_size;
    }
    void set_array_size(int size)
    {
        this->array_size = size;
    }

    vector<pair<string,string>> get_parameters()
    {
        return parameters;
    }
    void add_parameter(string param_type, string param_name)
    {
        parameters.push_back({param_type, param_name});
    }
    void clear_parameters()
    {
        parameters.clear();  //clear mem
    }

    ~symbol_info()
    {
        parameters.clear();   //clear mem
    }
};