#include <iostream>
using namespace std;

struct Vertex { // for main list
	char vertex;
	int weight2=-1;
	Vertex* next;
	struct Edge* Sstart;
};
Vertex* Cstart = NULL;

struct Edge {  // for sub-list
	Vertex* tovertex;
	int weight;
	Edge* next;
};

struct Arr {
	Vertex* vertex;
};

int VertexCount=0;

void InsertVertex(char b) {
	Vertex* temp = new Vertex;
	temp->vertex = b;
	temp->next = NULL;
	temp->Sstart = NULL;
	VertexCount++;
	if (Cstart == NULL) {
		Cstart = temp;
	}
	else {
		struct Vertex* current = Cstart;
		while (current->next != NULL) {
			current = current->next;
		}
		current->next = temp;
	}
}

void InsertEdge(char b) {
	Vertex* curr = Cstart;
	while (curr != NULL) { // finding connection to vertex
		if (curr->vertex == b) {
			cout << "vertex found" << endl;
			break;
		}
		curr = curr->next;
	}
	if (curr == NULL) {
		cout << "vertex not found" << endl;
		return;
	}
	char vertex;
	cout << "Enter the vertex in which Edge wants to enroll: ";
	cin >> vertex;
	Vertex* current = Cstart;
	while (current != NULL) { // for finding connection from vertex
		if (current->vertex == vertex) {
			Edge* temp = new Edge;
			cout << "enter weight";
			cin >> temp->weight;
			temp->tovertex = curr;
			temp->next = NULL;

			if (current->Sstart == NULL) {
				current->Sstart = temp;
				cout << "Edge is successfully enrolled in course" << endl;
				return;
			}
			else {
				struct Edge* curren = current->Sstart;
				while (curren->next != NULL) {
					curren = curren->next;
				}
				curren->next = temp;
				cout << "Edge is successfully enrolled in course" << endl;
				return;
			}
		}
		current = current->next;
	}
	if (current == NULL)cout << "invalid Main vertex number" << endl;

}

void printgraph() {
	struct Vertex* current = Cstart;
	if (current == NULL) {
		cout << "Linked List is empty";
	}
	else {
		while (current != NULL) {
			cout << "Vertex : " << current->vertex << endl;
			struct Edge* ECurr = current->Sstart;
			while (ECurr != NULL)
			{
				cout << "Edge: " << (ECurr->tovertex->vertex) << endl;
				ECurr = ECurr->next;
			}

			current = current->next;
		}
	}
}

int Hashfn(char b) {
	int a = (int)b - 97;
	return(a);
}


void Djikstra(char source, char desti) {
	int* arr = new int[26];//check
	for (int i = 0; arr[i]; i++) {// initializing array
		arr[i] = 0;
	}
	Vertex* main = Cstart;
	while (main!=NULL) {
		if (main->vertex == source) {
			cout << "found vertex" << endl;
			break;
		}
		main = main->next;
	}
	if (main == NULL) {
		cout << "source doesnt exist" << endl;
		return;
	}
	int index = Hashfn(main->vertex);
	arr[index] = 1;

	int n = 0;
	Arr* ar = new Arr[VertexCount];// for storing vertex
	main->weight2 = 0;
	ar[0].vertex = main;
	while (true) {
		Edge* sub = main->Sstart;

		while (sub != NULL) {
			index = Hashfn(sub->tovertex->vertex);
			if (arr[index] != 1) {
				sub->tovertex->weight2 = main->weight2 + sub->weight;
				cout << sub->tovertex->weight2;
			}
			sub = sub->next;
		}

		Vertex* lowest = main->Sstart->tovertex;
		for (int i = 0; i < n + 1; i++) {
		Edge* sub2=ar[i].vertex->Sstart;
		while (sub2 != NULL) {
			index = Hashfn(sub2->tovertex->vertex);
			if ((sub2->tovertex->weight2 < lowest->weight2) && arr[index] != 1) {
				lowest = sub2->tovertex;
			}
			sub2 = sub2->next;
			}
		}
		main = lowest;
		/*cout << main->vertex;
		cout << "\t" << main->weight2<<endl;*/
		if (main->vertex == desti) {
			cout << "source found" << endl;
			return;
		}
		index = Hashfn(main->vertex);
		arr[index] = 1;
		n++;
		ar[n].vertex = main;
     
	}
}

int main() {
	InsertVertex('a');
	InsertVertex('b');
	InsertVertex('c');
	InsertVertex('d');
	InsertVertex('e');
	InsertEdge('b');
	InsertEdge('c');
	
	InsertEdge('c');
	InsertEdge('d');

	InsertEdge('b');
	InsertEdge('d');
	InsertEdge('e');
	
	InsertEdge('e');

	InsertEdge('d');

	int a = 0;
	char c,d;
	while (a != 20) {
		cout << "1 insert vertex, 2 insert edge, 3 print vertx, 4 print Edge, 5 delete Edge from 1 vertex, 6 delete vertex," << endl;
		cin >> a;
		if (a == 1) {
			cin >> c;
			InsertVertex(c);
		}
		if (a == 2) {
			cout << "Enter edge: ";
			cin >> c;
			InsertEdge(c);
		}
		if (a == 3) {
			cin >> c;
			cin >> d;
			Djikstra(c,d);
		}
		/*if (a == 4) {
			PrintEdge();
		}
		if (a == 5) {
			cout << "Enter edge: ";
			cin >> c;
			DeleteVertex(c);
		}

		if (a == 6) {
			cout << "Enter vertex: ";
			cin >> c;
			DeleteEdge(c);
		}
		if (a == 7) {
			cout << "Enter the vertex you want to find: ";
			cin >> c;
			BreadthFirst(c);

		}*/
		if (a == 8) {
			printgraph();

		}
		/*if (a == 14) {
			cout << "Enter which vertex's outdegree you want to know:" << endl;
			cin >> c;
			Outdegree(c);
		}
		if (a == 15) {
			cout << "Enter which vertex's indegree you want to know:" << endl;
			cin >> c;
			InDegree(c);
		}*/
	}
}
