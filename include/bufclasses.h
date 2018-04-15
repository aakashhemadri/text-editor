#include<iostream>
#include<string>
typedef struct NODE{ 
		std::string line; 
		NODE *next; 
}NODE; 		
class buffer{
		NODE *head;
		NODE *tail;
		int lineNum;
		void read(std::string);
};
void buffer::read(std::string readLine){
		NODE *temp;
		temp = new NODE;
		temp->line = readLine;
		temp->next = NULL;
		if(this->head == NULL){
				this->head = temp;
				this->tail = temp;
		}
		else {
				this->tail->next = temp;
				this->tail = this->tail->next;
		}
}
