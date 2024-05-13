#include <iostream>
#include <stdlib.h>
#include <queue>
using namespace std;

struct Vertex { // for main list
	char vertex;
	int index;
	Vertex* next;
	struct Edge* Sstart;
};

struct Edge {  // for sub-list
	int weight;
	Vertex* ToVertex;
	Edge* next;
};

struct loop {
	Vertex* parent;
	Vertex* child;
};

struct Weight { // for array
	int weight;
	Vertex* source;
	Vertex* desti;
};

struct Arr {
	Vertex* vertex;
};

Vertex* Cstart = NULL;
Vertex* Cstart2 = NULL;
int VertexCount = 0; // count of vertex
int EdgeCount = 0; //count of edges

int Hashfn(char b) {
	int node = (int)b - 97;
	return(node);
}

void InsertVertex(char c) {
	struct Vertex* temp = new Vertex;
	VertexCount += 1;
	temp->vertex = c;
	temp->next = NULL;
	temp->Sstart = NULL;
	temp->index = VertexCount - 1;
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

void InsertVertex2(char c) {
	struct Vertex* temp = new Vertex;
	temp->vertex = c;
	temp->next = NULL;
	temp->Sstart = NULL;
	temp->index = VertexCount - 1;
	if (Cstart2 == NULL) {
		Cstart2 = temp;

	}
	else {
		struct Vertex* current = Cstart2;
		while (current->next != NULL) {
			current = current->next;
		}
		current->next = temp;
	}
}


void InsertEdge(char source, char desti, int weight) {
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
			EdgeCount += 1;// counting number of edges
			Edge* temp = new Edge;
			temp->ToVertex = curr2;
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
			temp2->ToVertex = curr1;
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

void InsertEdge2(char source, char desti, int weight) {
	Vertex* curr1 = Cstart2;// for if the vertex exist from which we want to connect
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

	Vertex* curr2 = Cstart2;// for if the vertex which we want to connect to exists
	while (curr2 != NULL)
	{
		if (curr2->vertex == desti)
		{
			Edge* temp = new Edge;
			temp->ToVertex = curr2;
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
			temp2->ToVertex = curr1;
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

void printgraph(Vertex* cstart) {
	Vertex* current = cstart;
	if (current == NULL) {
		cout << "graph is empty" << endl;
	}
	else {
		while (current != NULL) {
			cout << "Vertex : " << current->vertex << endl;
			struct Edge* ECurr = current->Sstart;
			while (ECurr != NULL)
			{
				cout << "Edge: " << (ECurr->ToVertex->vertex) << "\t";
				cout << "Edge's weight is: " << (ECurr->weight) << endl;
				ECurr = ECurr->next;
			}

			current = current->next;
		}
	}
}

void DeleteEdge(char source, char destination) { //deleting an edge from node specific vertex

	Vertex* current = Cstart;
	while (current != NULL) {
		if (current->vertex == source) { // vertex

			Edge* sub1 = current->Sstart;
			Vertex* save = NULL;
			if (sub1 == NULL) { // if sublist is null
				cout << "no Edge" << endl;
				return;
			}

			if (sub1->ToVertex->vertex == destination) {// if at Sstart
				save = sub1->ToVertex;
				EdgeCount--;
				current->Sstart = sub1->next;
				free(sub1);
			}
			else {
				Edge* sub2 = current->Sstart;
				sub2 = sub2->next;
				while (sub2 != NULL) {
					if (sub2->ToVertex->vertex == destination) {
						save = sub2->ToVertex;
						EdgeCount--;
						sub1->next = sub2->next;
						free(sub2);
						break;
					}
					sub1 = sub1->next;
					sub2 = sub2->next;
				}
			}
			// Now deleting opposite
			//save b
			//current node
			Edge* sub = save->Sstart;
			if (save->Sstart->ToVertex->vertex == source) {// if at Sstart
				save->Sstart = sub->next;
				free(sub);
				return;
			}
			else {
				Edge* sub2 = save->Sstart;
				sub2 = sub2->next;
				while (sub2 != NULL) {
					if (sub2->ToVertex->vertex == source) {
						sub->next = sub2->next;
						free(sub2);
						return;
					}
					sub = sub->next;
					sub2 = sub2->next;
				}


			}
			cout << "Error" << endl;

		}
		current = current->next;
	}
	cout << "Vertex not found" << endl;
}

void DeleteEdge2(char source, char destination) { //deleting an edge from node specific vertex

	Vertex* current = Cstart2;
	while (current != NULL) {
		if (current->vertex == source) { // vertex

			Edge* sub1 = current->Sstart;
			Vertex* save = NULL;
			if (sub1 == NULL) { // if sublist is null
				cout << "no Edge" << endl;
				return;
			}

			if (sub1->ToVertex->vertex == destination) {// if at Sstart
				save = sub1->ToVertex;
				EdgeCount--;
				current->Sstart = sub1->next;
				free(sub1);
			}
			else {
				Edge* sub2 = current->Sstart;
				sub2 = sub2->next;
				while (sub2 != NULL) {
					if (sub2->ToVertex->vertex == destination) {
						save = sub2->ToVertex;
						sub1->next = sub2->next;
						free(sub2);
						break;
					}
					sub1 = sub1->next;
					sub2 = sub2->next;
				}
			}
			// Now deleting opposite
			//save b
			//current node
			Edge* sub = save->Sstart;
			if (save->Sstart->ToVertex->vertex == source) {// if at Sstart
				save->Sstart = sub->next;
				free(sub);
				return;
			}
			else {
				Edge* sub2 = save->Sstart;
				sub2 = sub2->next;
				while (sub2 != NULL) {
					if (sub2->ToVertex->vertex == source) {
						sub->next = sub2->next;
						free(sub2);
						return;
					}
					sub = sub->next;
					sub2 = sub2->next;
				}


			}
			cout << "Error" << endl;

		}
		current = current->next;
	}
	cout << "Vertex not found" << endl;
}

void AllConn(Vertex* node, int* arr) {// DFS
	if (node == NULL) {
		return;
	}
	if (node->Sstart == NULL) {// if some vertex which are not connected with root vertex but is connected with other vertex
		AllConn(node->next, arr);
		return;
	}
	arr[Hashfn(node->vertex)] = 1;


	Edge* sub = node->Sstart;
	while (sub != NULL) {
		if (arr[Hashfn(sub->ToVertex->vertex)] != 1) {
			AllConn(sub->ToVertex, arr);

		}
		sub = sub->next;
	}

}

int LoopDetect(char b) {
	// array
	int* arr = new int[VertexCount];
	for (int i = 0; arr[i]; i++) {
		arr[i] = 0;
	}

	Vertex* main = Cstart2; 
	while (main!=NULL)    // Min spanning tree men wo source dhondh rahe hen(only for prims)
	{
		if (main->vertex==b)
		{
			break;
		}
		main = main->next;
	}

	queue <loop*> q1;
	loop* relation = new loop;
	relation->parent = main;
	relation->child = main;
	q1.push(relation);
	// root is visited
	arr[Hashfn(main->vertex)] = 1;
	while (!q1.empty()) {
		loop* output = q1.front();
		q1.pop();

		if (output->child->Sstart == NULL) {// if the sub list is empty
			continue;
		}
		Edge* sub = output->child->Sstart;

		while (sub != NULL) {// traversing sublist
			if (arr[Hashfn(sub->ToVertex->vertex)] == 1 && sub->ToVertex->vertex != output->parent->vertex) {//found the vertex through path
				cout << "loop exist" << endl;
				return(1);
			}
			if (arr[Hashfn(sub->ToVertex->vertex)] == 0)
			{
				loop* relation2 = new loop;
				relation2->parent = output->child;
				relation2->child = sub->ToVertex;
				q1.push(relation2);
				int index = Hashfn(sub->ToVertex->vertex);
				// root is visited
				arr[index] = 1;
			}
			sub = sub->next;
		}
	}
	cout << "loop doesn't exit" << endl;
	return(0);
}

void Prims(Vertex* start) {

	int* visited = new int[VertexCount];
	for (int i = 0; visited[i]; i++) {// initializing array
		visited[i] = 0;
	}
	Arr* arr = new Arr[VertexCount];// for saving the visited vertexes
	int n = 0;
	arr[0].vertex = start;
	visited[Hashfn(start->vertex)] = 1;
	int check = 2;
	while (true) {
		int* Visit = new int[VertexCount];
		for (int j = 0; j < VertexCount; j++) {
			Visit[j] = 0;
		}
		AllConn(Cstart2, Visit);// telling which vertex are visited -- returns array

		check = 0;
		for (int k = 0; k < VertexCount; k++) {
			if (Visit[k] == 0)check = 1; //if any single vertex is not connected it shifts to 1
		}
		
		if (check == 0)break; //means all are connectedd
		int lowest = 9999;
		Weight* save=new Weight;
		for (int i = 0; i < n + 1; i++) {// to access all visited vertex
			Edge* sub2 = arr[i].vertex->Sstart;

			while (sub2 != NULL) { // accessing all the sublist of vertex
				if ((sub2->weight < lowest) && visited[Hashfn(sub2->ToVertex->vertex)] != 1) {
					save->weight = sub2->weight;
					save->source = arr[i].vertex;
					save->desti = sub2->ToVertex;
					lowest = sub2->weight;
				}
				sub2 = sub2->next;
			}
		}

		if(check == 1){
			InsertEdge2(save->source->vertex, save->desti->vertex, save->weight);
			
			if (LoopDetect(save->source->vertex) == 1) { // Checking and deleting if the inserted edge made node loop
				DeleteEdge2(save->source->vertex, save->desti->vertex);
				DeleteEdge(save->source->vertex, save->desti->vertex); //delete from graph must else inifinite loop
				cout << "deleted" << save->source->vertex << "\t" << save->desti->vertex;
				continue;
			}
			n++; //to update array -- to keep track of visited vertex
			arr[n].vertex = save->desti;
			visited[Hashfn(save->desti->vertex)] = 1;
		}

	}

}

int main()
{
//InsertVertex('a');
//InsertVertex('b');
//InsertVertex('c');
//InsertVertex('d');
//InsertVertex('e');
//InsertVertex('f');
//InsertVertex('g');
//InsertVertex('h');
//InsertVertex('i');
//InsertVertex('j');
//InsertVertex('k');
//
//InsertVertex2('a');
//InsertVertex2('b');
//InsertVertex2('c');
//InsertVertex2('d');
//InsertVertex2('e');
//InsertVertex2('f');
//InsertVertex2('g');
//InsertVertex2('h');
//InsertVertex2('i');
//InsertVertex2('j');
//InsertVertex2('k');
//
//InsertEdge('a', 'c', 3);
//InsertEdge('a', 'b', 2);
//InsertEdge('h', 'b', 5);
//InsertEdge('a', 'd', 2);
//InsertEdge('c', 'g', 1);
//InsertEdge('g', 'h', 7);
//InsertEdge('g', 'i', 3);
//InsertEdge('g', 'j', 2);
//InsertEdge('j', 'k', 9);
//InsertEdge('d', 'e', 6);
//InsertEdge('d', 'f', 3);
//InsertEdge('e', 'f', 7);
//InsertEdge('e', 'j', 6);
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

InsertVertex2('a');
InsertVertex2('b');
InsertVertex2('c');
InsertVertex2('d');
InsertVertex2('e');
InsertVertex2('f');
InsertVertex2('g');
InsertVertex2('h');
InsertVertex2('i');
InsertVertex2('j');
InsertVertex2('k');

InsertEdge('a', 'c', 3);
InsertEdge('a', 'b', 2);
InsertEdge('h', 'b', 5);
InsertEdge('a', 'd', 2);
InsertEdge('c', 'g', 1);
InsertEdge('g', 'h', 7);
InsertEdge('g', 'i', 3);
InsertEdge('g', 'j', 2);
InsertEdge('j', 'k', 9);
InsertEdge('d', 'e', 6);
InsertEdge('d', 'f', 3);
InsertEdge('e', 'f', 7);
InsertEdge('e', 'j', 6);
	int node = 0;
	int d;
	char c, b;
	while (node != 20) {
		cout << "1 insert vertex, 2 insert edge, 3 print vertx, 4 print Edge" << endl;
		cin >> node;
		if (node == 1) {
			cin >> c;
			InsertVertex(c);
			InsertVertex2(c);
		}
		if (node == 2) {
			cout << "Enter Vertex: ";
			cin >> b;
			cout << "Enter edge: ";
			cin >> c;
			cout << "Enter weight";
			cin >> d;
			InsertEdge(b, c, d);
		}
		if (node == 3) {
			printgraph(Cstart);

		}
		if (node == 4) {
			printgraph(Cstart2);

		}
		if (node == 5) {
			Prims(Cstart);

		}
	}
}
