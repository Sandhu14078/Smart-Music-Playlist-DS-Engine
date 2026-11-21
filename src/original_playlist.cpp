#include<iostream>
#include<string>
using namespace std;

struct Node{
	string song;
	Node* next;
};

Node* head = NULL;
Node* current= NULL;

void createplaylist(){
	int n;
	cout<<"Enter number of songs: ";
	cin>>n;
	cin.ignore();
	for(int i=0; i<n;i++){
		Node* newnode = new Node;
		
		cout<<"Enter the name of song: ";
		getline(cin,newnode->song);
		
		if(head == NULL){
			head = newnode;
			current=newnode;
			newnode->next=head;
		}
		else{
			Node* temp = head;
			while(temp->next!=head){
				temp = temp->next;
			}
			temp->next = newnode;
			newnode->next=head;
		}
	}
}

void displayplaylist(){
	if(head ==NULL){
		cout<<"Playlist is empty. "<<endl;
		return;
	}
	Node* temp = head;
	
	do{
		cout<<temp->song<<endl;
		temp=temp->next;
	}while(temp!=head);
}

void playnext(){
	if(current ==NULL){
		cout<<"Playlist is empty. "<<endl;
		return;
	}
	current = current->next;
	cout<<"Now playing: "<<current->song<<endl;
}

void insertaftersong(){
	Node* newnode = new Node;
	cout<<"Enter the name of the song: ";
	getline(cin,newnode->song);
	
	if(current == NULL){
		head = newnode;
		current = newnode;
		newnode->next = head;
		return;
	}
	
	newnode->next = current->next;
	current->next = newnode;
}

void deletecurrent(){
	if(current==NULL){
		cout<<"Playlist is empty. "<<endl;
		return;
	}
	if(current->next == current){
		delete current;
		head = NULL;
		current = NULL;
		return;
	}
	Node* temp = head;
	while(temp->next!=current){
		temp=temp->next;
	}
	temp->next = current->next;
	if(current==head){
		head = current->next;
	}
	Node* deletenode= current;
	current = current->next;
	delete deletenode;
}

void searchsong(){
	string search;
	cout<<"Enter song to search: ";
	getline(cin,search);
	
	if(head==NULL){
		cout<<"Playlist is empty. "<<endl;
		return;
	}
	Node* temp = head;
	do{
		if(temp->song==search){
			cout<<"Song found!! "<<endl;
			return;
		}
		temp=temp->next;
	}while(temp!=head);
	cout<<"Song not found. "<<endl;
}

void playround(){
	if(current==NULL){
		cout<<"Playlist is empty. "<<endl;
		return;
	}
	Node* start = current;
	Node* temp = current;
	
	do{
		cout<<"Playing: "<<temp->song<<endl;
		temp = temp->next;
	}while(temp!=start);
}

int main(){
	createplaylist();

	cout<<endl;
	cout<<"Playlist: "<<endl;
	displayplaylist();

	cout<<endl;
	playnext();

	cout<<endl;
	insertaftersong();

	cout<<endl;
	cout<<"Updated Playlist: "<<endl;
	displayplaylist();

	cout<<endl;
	deletecurrent();

	cout<<endl;
	cout<<"Playlist after deleting current song: "<<endl;
	displayplaylist();

	cout<<endl;
	searchsong();

	cout<<endl;
	playround();

	return 0;
}
