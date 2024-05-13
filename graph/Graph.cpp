#include <iostream>
#include <stdlib.h>
using namespace std;

struct Vertex { // for main list // vertical list 
	char vertex;
	Vertex* next;
	struct Edge* EdgeStart;
};
Vertex* Cstart = NULL;

struct Edge {  // for sub-list // horizontal list
	Vertex* tovertex; // ye address hold karega us vertex ka jisse connection hai
	Edge* next;
};

void InsertVertex(char b) {
	Vertex* temp = (Vertex*)malloc(sizeof(Vertex));
	temp->vertex = b;
	temp->next = NULL;
	//
	temp->EdgeStart = NULL; // horizontal list means edge list is null
	if (Cstart == NULL) { //  vertcal list means vertex list is null (1st time chalega)
		Cstart = temp;
	}
	else {      
		struct Vertex* current = Cstart; 
		while (current->next != NULL) {
			current = current->next;
		}
		current->next = temp; // (2nd time se start hoga) 
	}
}

void InsertEdge(char b) {// b is edge (kis vertex ko connect karna) 
	Vertex* curr = Cstart;
	while (curr != NULL) { // ye while check karega ke vertex jisko connect karna hai exist karta hai ya nahi
		if (curr->vertex == b) {
			cout << "vertex found" << endl;
			break; 
		}
		curr = curr->next;
	}
	if (curr == NULL) { // in case exist nahi karta tab ye chalega
		cout << "vertex not found" << endl;
		return;
	// if found the curr is holding the value of the vertex to be connected 
	}
	char vertex;    // kis se connect karna
	cout << "Enter the vertex in which Edge wants to enroll: ";
	cin >> vertex; 
	Vertex* curr2 = Cstart;
	while (curr2 != NULL) { // (ye last vertex tak chalega )
		if (curr2->vertex == vertex) { // in case vertex mil gayi 
			Edge* temp = (Edge*)malloc(sizeof(Edge));
			temp->tovertex = curr; // ye curr us vertex ko hold karta hai jisko jis se connect karna hai
			temp->next = NULL; 
			
			if (curr2->EdgeStart == NULL) { // in case kisi vertex ki pehli edge connect ho rahi hai
				curr2->EdgeStart = temp;
				cout << "Edge is successfully enrolled in vertex" << endl;
				return;
			}
			else {
				struct Edge* curren = curr2->EdgeStart; // to go till null to connect edge
				while (curren->next != NULL) {
					curren = curren->next;
				}
				curren->next = temp;
				cout << "Edge is successfully enrolled in vertex" << endl;
				return;
			}
		}
		curr2 = curr2->next;
	}
	//if (curr2 == NULL)cout << "invalid Main vertex number" << endl; // jis se connect karna tha not found 

}
void PrintVertex() { // same as linked list
	Vertex* ptr = Cstart;
	if (ptr == NULL) cout << "empty" << endl;
	while (ptr != NULL) {
		cout << ptr->vertex << endl;
		ptr = ptr->next;
	}
}
void PrintEdge() { 
	char vertex;
	cout << "Enter the vertex: ";
	cin >> vertex;
	Vertex* current = Cstart;
	if (current == NULL) {  // if graph is null
		cout << "vertex does not exist" << endl;
	}
	while (current != NULL) { 
		if (current->vertex == vertex) {
			Edge* ptr = current->EdgeStart;
			if (ptr == NULL) {  // in case edge nahi hai
				cout << "empty" << endl;
				return;
			}
			while (ptr != NULL) { // if vertex found now print its edgs till null na hojaye
				cout << ptr->tovertex->vertex << endl;
				ptr = ptr->next;
			}
			return;
		}
		current = current->next; // next vertex pe jaane ke liye
		if (current == NULL)cout << "vertex does not exist" << endl;
	}
}

void DeleteVertex(char b) {// deleting node vertex and its reference(edge) everywhere
	
	//first deleting all reference(edge) of the vertex you want to delete
	Vertex* VList = Cstart;
	while (VList != NULL) {
		if (VList->vertex != b) { //to not go in the sub list of the vertex itself
			Edge* EList = VList->EdgeStart;//current
			if (EList->tovertex->vertex == b) {//if reference is in the start of sub list
				VList->EdgeStart = EList->next;
				free(EList);
				VList = VList->next; 
				continue; // because each vertex contains exactly one copy of its edge
			}
			//in case muhjhe starting mai edge nahi mili then this code will run
			Edge* Elist2 = VList->EdgeStart->next;//next
			while (Elist2 != NULL) { //to find reference of the vertex in the sublist
				if (Elist2->tovertex->vertex == b) {
					EList->next = Elist2->next;
					free(Elist2);
					break;
				}
				// this is to increment and move to the next edge of the edged list
				EList = EList->next;
				Elist2 = Elist2->next;
			}
		}
		VList = VList->next;
	}

	//now deleting the vertex along with its sub list
	VList = Cstart;
	Edge* sub=NULL; // ye bhi Edge list hai
	Edge* sub2;
	if (VList->vertex == b) { //if the vertex is at the start
		Cstart = VList->next;
		sub = VList->EdgeStart;
		free(VList);
	}
	else {
		Vertex* VList2 = Cstart->next; //next (ye increment ke lie) in case agar vertex first na hua 
		while (VList2 != NULL) { // if the vertex is in the middle or end
			if (VList2->vertex == b) {
				VList->next = VList2->next; //setting ho rahi next se
				sub = VList2->EdgeStart; 
				free(VList2); // vertex deleted 
				break;
			}
			VList = VList->next;
			VList2 = VList2->next;
		}
	}
	if (sub == NULL) { // incase the deleted vertex did not have any edges
		cout << "deleted the vertex" << endl;
		return;
	}

	sub2 = sub;//next 
	while (sub != NULL) { // deleting edge list of the deleted vertex
		sub2 = sub2->next;
		free(sub);
		sub = sub2;
	}
	cout << "deleted the vertex" << endl;
	return;
}

void DeleteEdge(char b) { //deleting an edge from node specific vertex
	char vertex;
	cout << "Enter vertex : ";
	cin >> vertex;
	Vertex* current = Cstart;
	while (current != NULL) {
		if (current->vertex == vertex) {  // agar vertex mil gaya jaha se edge delete karna hai
			
			Edge* prev = current->EdgeStart;
			if (prev == NULL) { // in case no edge exists
				cout << "no Edge exists" << endl;
				return;
			}

			if (prev->tovertex->vertex==b) { // incase shuru edge list ke shuru mai hi edge mil gai
				current->EdgeStart = prev->next;
				free(prev);
				return;
			}
			Edge* curr = current->EdgeStart; // aik aur variable banaya hai jo current ko hold kar raha
			curr = curr->next; //current pechle wale ko hold kar raha and curr uske next wale ko
			while (curr != NULL) {
				if (curr->tovertex->vertex == b) {
					prev->next = curr->next; 
					free(curr);
					return;
				}
				prev = prev->next;
				curr = curr->next;
			}
			cout << "Edge not found" << endl;
			return;
		}
		current = current->next;
	}
	cout << "Vertex not found" << endl;
}

void Outdegree(int b) {
	Vertex* curr = Cstart;
	while (curr != NULL) {
		if (curr->vertex == b) {
			cout << "vertex found" << endl;
			break;
		}
		curr = curr->next;
	}
	if (curr == NULL) {
		cout << "sub vertex not found" << endl;
		return;
	}
	int counter = 0;
	Edge* temp = curr->EdgeStart;
	while (temp != NULL) {
		counter++;
		temp = temp->next;
	}
	cout << "Outdegree is: " << counter << endl;
}

void InDegree(int b) {
	int counter = 0;
	Vertex* main = Cstart;
	Edge* sub = NULL;
	while (main != NULL) {
		sub = main->EdgeStart;
		while (sub != NULL) {
			if (sub->tovertex->vertex == b) {
				counter++;
			}
			sub = sub->next;
		}
		main = main->next;
	}
	cout << "Indegree is: " << counter << endl;
}
void printgraph() {
    struct Vertex* current = Cstart;
    if (current == NULL) {
        cout << "Linked List is empty";
    }
    else {
        while (current != NULL) {
            cout << "Vertex : " << current->vertex << endl;
            struct Edge* ECurr = current->EdgeStart;
            while (ECurr != NULL)
            {
                cout << "Edge: " << (ECurr->tovertex->vertex) << endl;
                ECurr = ECurr->next;
            }

            current = current->next;
        }
    }
}
int main() {
	int node = 0;
	char c;
	while (node != 15) {
		cout << "1 insert vertex, 2 insert edge, 3 print vertx, 4 print Edge, 5 delete Edge from node vertex, 6 delete vertex " << endl;
		cout<< " 7 to print the vertex's outdegree , 8 to print the vertex's indegree, 9 to print the graph " << endl;
		cin >> node; 
		if (node == 1) {
			cin >> c;
			InsertVertex(c);
		}
		if (node == 2) {
			cout << "Enter edge: ";
			cin >> c;
			InsertEdge(c);
		}
		if (node == 3) {
			PrintVertex();
		}
		if (node == 4) {
			PrintEdge();
		}
		if (node == 5) {
			cout << "Enter edge: ";
			cin >> c;
			DeleteVertex(c);
		}

		if (node == 6) {
			cout << "Enter vertex: ";
			cin >> c;
			DeleteEdge(c);
		}
		if (node == 7) {
			cout << "Enter which vertex's outdegree you want to know:" << endl;
			cin >> c;
			Outdegree(c);
		}
		if (node == 8) {
			cout << "Enter which vertex's indegree you want to know:" << endl;
			cin >> c;
			InDegree(c);
		}
		if (node == 9) {
			printgraph();
		}
		}
	}
