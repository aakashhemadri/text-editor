#ifndef UNDO_H 
#define UNDO_H 
 
#include<string> 
 
class Undo{ 
    std::string line; 
    int pos; 
    struct NODE* left; 
    struct NODE* right; 
 
    public: 
    Undo(); 
    void ifInsert(std::string, int); 
    void ifDelete(std::string, int); 
}; 
 
#endif 
