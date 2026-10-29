#include "scope_table.h"

class symbol_table
{
private:
    scope_table *current_scope;
    int bucket_count;
    int current_scope_id;

public:
    symbol_table(int bucket_count);
    ~symbol_table();
    void enter_scope();
    void exit_scope();
    bool insert(symbol_info* symbol);
    symbol_info* lookup(symbol_info* symbol);
    int get_current_scope_id();
    void print_current_scope();
    void print_all_scopes(ofstream& outlog);

    // you can add more methods if you need 
};

// complete the methods of symbol_table class

symbol_table::symbol_table(int bucket_count)
{
    this->bucket_count = bucket_count;
    this->current_scope_id = 0;
    this->current_scope = NULL;
}

void symbol_table::enter_scope()
{
    current_scope_id++;
    scope_table *new_scope = new scope_table(bucket_count, current_scope_id, current_scope);
    current_scope = new_scope;
}

void symbol_table::exit_scope()
{
    if (current_scope == NULL)
        return;

    scope_table *temp = current_scope;
    current_scope = temp->get_parent_scope();
    delete temp;
}

bool symbol_table::insert(symbol_info* symbol)
{
    if (current_scope == NULL)
        return false;

    return current_scope->insert_in_scope(symbol);
}

symbol_info* symbol_table::lookup(symbol_info* symbol)
{
    scope_table *temp = current_scope;
    while (temp != NULL)
    {
        symbol_info *found = temp->lookup_in_scope(symbol);
        if (found != NULL)
            return found;
        temp = temp->get_parent_scope();
    }
    return NULL;
}

int symbol_table::get_current_scope_id()
{
    return (current_scope != NULL) ? current_scope->get_unique_id() : -1;
}

void symbol_table::print_current_scope()
{
    if (current_scope == NULL)
        return;

    // debug helper - prints to console, not the log file
    ofstream dummy; // not used for file output here
    cout << "ScopeTable # " << current_scope->get_unique_id() << endl;
}

void symbol_table::print_all_scopes(ofstream& outlog)
{
    outlog<<"################################"<<endl<<endl;
    scope_table *temp = current_scope;
    while (temp != NULL)
    {
        temp->print_scope_table(outlog);
        outlog << endl;
        temp = temp->get_parent_scope();
    }
    outlog<<"################################"<<endl<<endl;
}

symbol_table::~symbol_table()
{
    while (current_scope != NULL)
    {
        scope_table *temp = current_scope;
        current_scope = temp->get_parent_scope();
        delete temp;
    }
}