#include "symbol_info.h"

class scope_table
{
private:
    int bucket_count;
    int unique_id;
    scope_table *parent_scope = NULL;
    vector<list<symbol_info *>> table;

    int hash_function(string name)
    {
        int sum = 0;
        for (char c : name)
            sum += (int)c;
        return sum % bucket_count; 
    }

public:
    scope_table();
    scope_table(int bucket_count, int unique_id, scope_table *parent_scope);
    scope_table *get_parent_scope();
    int get_unique_id();
    symbol_info *lookup_in_scope(symbol_info* symbol);
    bool insert_in_scope(symbol_info* symbol);
    bool delete_from_scope(symbol_info* symbol);
    void print_scope_table(ofstream& outlog);
    ~scope_table();

    // you can add more methods if you need
};

scope_table::scope_table()
{
    this->bucket_count = 10;
    this->unique_id = 1;
    this->parent_scope = NULL;
    table.resize(bucket_count);
}

scope_table::scope_table(int bucket_count, int unique_id, scope_table *parent_scope)
{
    this->bucket_count = bucket_count;
    this->unique_id = unique_id;
    this->parent_scope = parent_scope;
    table.resize(bucket_count);
}

scope_table *scope_table::get_parent_scope()
{
    return parent_scope;
}

int scope_table::get_unique_id()
{
    return unique_id;
}

symbol_info *scope_table::lookup_in_scope(symbol_info* symbol)
{
    int idx = hash_function(symbol->get_name());
    for (symbol_info* s : table[idx])
    {
        if (s->get_name() == symbol->get_name())
            return s;
    }
    return NULL;
}

bool scope_table::insert_in_scope(symbol_info* symbol)
{
    // duplicate check within this scope only
    if (lookup_in_scope(symbol) != NULL)
        return false;

    int idx = hash_function(symbol->get_name());
    table[idx].push_back(symbol);
    return true;
}

bool scope_table::delete_from_scope(symbol_info* symbol)
{
    int idx = hash_function(symbol->get_name());
    for (auto it = table[idx].begin(); it != table[idx].end(); ++it)
    {
        if ((*it)->get_name() == symbol->get_name())
        {
            table[idx].erase(it);
            return true;
        }
    }
    return false;
}

// you can add more methods if you need

// complete the methods of scope_table class
void scope_table::print_scope_table(ofstream& outlog)
{
    outlog << "ScopeTable # "+ to_string(unique_id) << endl;

    for (int i = 0; i < bucket_count; i++)
    {
        if (table[i].empty())
            continue;

        outlog << i << " --> " << endl;
        for (symbol_info* s : table[i])
        {
            outlog << "< " << s->get_name() << " : ID >" << endl;

            if (s->get_symbol_category() == "VARIABLE")
            {
                outlog << "Variable" << endl;
                outlog << "Type: " << s->get_data_type() << endl;
                outlog << endl;
            }
            else if (s->get_symbol_category() == "ARRAY")
            {
                outlog << "Array" << endl;
                outlog << "Type: " << s->get_data_type() << endl;
                outlog << "Size: " << s->get_array_size() << endl;
                outlog << endl;
            }
            else if (s->get_symbol_category() == "FUNCTION")
            {
                outlog << "Function Definition" << endl;
                outlog << "Return Type: " << s->get_data_type() << endl;
                outlog << "Number of Parameters: " << s->get_parameters().size() << endl;
                outlog << "Parameter Details: ";
                auto params = s->get_parameters();
                for (size_t p = 0; p < params.size(); p++)
                {
                    outlog << params[p].first << " " << params[p].second;
                    if (p != params.size() - 1)
                        outlog << ", ";
                }
                outlog << endl;
            }
        }
    }
}

scope_table::~scope_table()
{
    for (int i = 0; i < bucket_count; i++)
    {
        for (symbol_info* s : table[i])
            delete s;
        table[i].clear();
    }
}