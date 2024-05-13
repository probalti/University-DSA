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

void InsertEdgeDirected(char vertex,char b,int weight) {//Directed graph 
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
	
	Vertex* current = Cstart;
	while (current != NULL) { // for finding connection from vertex
		if (current->vertex == vertex) {
			Edge* temp = new Edge;
			temp->weight = weight;
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

void InsertEdge(char source, char desti, int weight) {//Undirected
	Vertex* curr1 = Cstart;// for if the vertex exist from which we want to connect
	while (curr1 != NULL) {
		if (curr1->vertex == source) {
			break;
		}
		curr1 = curr1->next;
	}

	if (curr1 == NULL) {
		cout << "Vertex not found" << endl;
		return;
	}

	Vertex* curr2 = Cstart;// for if the vertex which we want to connect to exists
	while (curr2 != NULL)
	{
		if (curr2->vertex == desti)
		{
			Edge* temp = new Edge;
			temp->tovertex = curr2;
			temp->next = NULL;
			temp->weight = weight;

			if (curr1->Sstart == NULL) {
				curr1->Sstart = temp;
				cout << "Edge is successfully linked with vertex" << source << "\t" << desti << endl;
			}
			else {
				Edge* Ecurr1 = curr1->Sstart;
				while (Ecurr1->next != NULL) {
					Ecurr1 = Ecurr1->next;
				}
				Ecurr1->next = temp;
				cout << "Edge is successfully linked with vertex" << source << "\t" << desti << endl;
			}

			//Now making the reverse connection
			Edge* temp2 = new Edge;
			temp2->tovertex = curr1;
			temp2->next = NULL;
			temp2->weight = weight;

			if (curr2->Sstart == NULL) {
				curr2->Sstart = temp2;
				cout << "Edge is successfully linked with vertex" << source << "\t" << desti << endl;
				return;
			}
			else {
				Edge* Ecurr2 = curr2->Sstart;
				while (Ecurr2->next != NULL) {
					Ecurr2 = Ecurr2->next;
				}
				Ecurr2->next = temp2;
				cout << "Edge is successfully linked with vertex" << source << "\t" << desti << endl;
				return;
			}

		}
		curr2 = curr2->next;
	}
	if (curr2 == NULL)
	{
		cout << "the other vertex is not in list...\n";
		return;
	}

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
	int* Visited = new int[26];//check
	for (int i = 0; Visited[i]; i++) {// initializing array
		Visited[i] = 0;
	}
	Vertex* main = Cstart;
	while (main != NULL) {// finding source
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

	Visited[Hashfn(main->vertex)] = 1;// makes source visited

	int n = 0;
	Arr* ar = new Arr[VertexCount];// for storing vertex
	main->weight2 = 0;
	ar[0].vertex = main;// storing source vertex
	Vertex* lowest = NULL;
	int weight = main->weight2;// to save final weight

	while (true) {
		Edge* sub = main->Sstart;
		//cout << main->vertex<<endl;
		while (sub != NULL) {// giving weights to every vertex connected with current one
			if (sub->tovertex->weight2 == -1) {//arr[Hashfn(sub->tovertex->vertex)] != 1
				sub->tovertex->weight2 = main->weight2 + sub->weight;
				//cout <<"weight " << sub->tovertex->weight2<<endl;
			}
			sub = sub->next;
		}
		// finding the least weight vertex out of all the children of all already visited vertex

		int save = 99999999999999999; // to save lowest vertex

		for (int i = 0; i < n + 1; i++) {// to access all visited vertex
			Edge* sub2 = ar[i].vertex->Sstart;

			while (sub2 != NULL) { // accessing all the sublist of vertex
				if ((sub2->tovertex->weight2 < save) && Visited[Hashfn(sub2->tovertex->vertex)] != 1) {
					lowest = sub2->tovertex;
					save = lowest->weight2;
				}
				sub2 = sub2->next;
			}
		}
		main = lowest;
		cout << lowest->vertex << endl;
		/*cout << main->vertex;
		cout << "\t" << main->weight2<<endl;*/
		if (main->vertex == desti) { // if destination is reached
			cout << "Weight is: " << weight << endl;
			cout << "source found" << endl;
			return;
		}
		weight = main->weight2;
		Visited[Hashfn(main->vertex)] = 1;
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
	InsertVertex('f');
	InsertVertex('g');
	InsertVertex('h');
	InsertVertex('i');
	InsertVertex('j');
	InsertVertex('k');
	InsertVertex('l');
	InsertEdge('j', 'i', 1);
	InsertEdge('j', 'l', 1);
	InsertEdge('j', 'k', 5);
	InsertEdge('l', 'i', 1);
	InsertEdge('j', 'g', 2);
	InsertEdge('i', 'g', 2);
	InsertEdge('j', 'e', 6);
	InsertEdge('g', 'h', 2);
	InsertEdge('e', 'f', 2);
	InsertEdge('e', 'd', 2);
	InsertEdge('d', 'a', 2);
	InsertEdge('d', 'f', 3);
	InsertEdge('a', 'b', 2);
	InsertEdge('h', 'b', 5);
	InsertEdge('g', 'c', 1);
	InsertEdge('c', 'a', 3);

	int a = 0;
	int d;
	char c,b;
	while (a != 20) {
		cout << "1 insert vertex, 2 insert edge, 3 print vertx, 4 print Edge, 5 delete Edge from 1 vertex, 6 delete vertex," << endl;
		cin >> a;
		if (a == 1) {
			cin >> c;
			InsertVertex(c);
		}
		if (a == 2) {
			cout << "Enter Vertex: ";
			cin >> b;
			cout << "Enter edge: ";
			cin >> c;
			cout << "Enter weight";
			cin >> d;
			InsertEdge(b, c, d);
		}
		if (a == 3) {
			cin >> c;
			cin >> b;
			Djikstra(c,b);
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
