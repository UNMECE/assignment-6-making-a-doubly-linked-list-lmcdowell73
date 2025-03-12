#include <iostream>
#include "coordinate.h"
#include <cmath>
#include <ctime>
#include <cstdlib>

using namespace std;

Coordinate *Glist_beginning = NULL;
Coordinate *Glist_end = NULL;


int list_length(Coordinate *list_beginning)
{
Coordinate *temp = list_beginning;
int length = 0;
while(temp != NULL){
	length++;
	temp = temp->next;
	}
	return length;
}
void add_coordinate(Coordinate *list_end, float x, float y){
Coordinate *new_coord = new Coordinate();
new_coord->x = x;
new_coord->y = y;
new_coord->next = NULL;
new_coord->previous = NULL;
new_coord->coord_id = list_length(Glist_beginning) +1;

if(Glist_beginning == NULL){
	Glist_beginning = new_coord;
	Glist_end = new_coord;
	}else{
		Glist_end->next = new_coord;
		new_coord->previous = Glist_end;
		Glist_end = new_coord;
	}	
}
void forward_display(Coordinate *list_beginning)
{
Coordinate *temp = list_beginning;
cout << "Display forwards: ";
while(temp != NULL)	{
	cout << "(" << temp->x << ", " << temp->y << ") ";
	temp = temp->next;
	}	
cout << endl;
}

void backward_display(Coordinate *list_end)
{
Coordinate *temp = list_end;
if (temp == NULL){
	cout << "list is empty." << endl;
	return;
	}

while(temp->next != NULL) {
	temp = temp->next;
	}	

cout << "Reverse list: ";
while(temp != NULL) {
		cout << "(" << temp->x << ", " << temp->y << ") ";
		temp = temp->previous;
}
cout << endl;

}
void delete_coordinate(Coordinate *list_beginning, int coord_id_to_delete)
{
Coordinate *temp = list_beginning;

while(temp->next != NULL){
		if(temp->coord_id == coord_id_to_delete)
		{
			if(temp->previous != NULL){
					temp->previous->next = temp->next;
			}else{
					Glist_beginning = temp->next;
		}
		if(temp->next != NULL){
			 temp->next->previous = temp->previous;
		}else{
			 Glist_end = temp->previous;
	}
		delete temp;
		return;
	}
	temp = temp->next;
	}	
}

void closest_to(Coordinate *list_beginning, float x, float y)
{
Coordinate *current = list_beginning;
Coordinate *closest = current;
double minDistance = sqrt(pow(x - current->x,2) + pow(y - current->y,2));
current = current->next;

while(current != NULL){
	double Distance = sqrt(pow(x - current->x,2) + pow(y - current->y,2));
	if(Distance < minDistance){
		minDistance = Distance;
		closest = current;
		}
	current = current->next;
	}		
cout << "Closest coordinate to (" << x << ", " << y << ") is:" << endl;
cout << "ID: " << closest->coord_id << " (" << closest->x << ", " << closest->y 
<< ") " << "with distance: " << minDistance << endl;
}

int main(int argc, char *argv[])
{
if (argc != 2) {
		cout << "Usage: " << argv[0] << " <number_of_coordinates>" << endl;
		return 1;
	}								     

int numCoords = atoi(argv[1]);
if (numCoords <= 0) {
	cout << "Please enter a positive integer for the number of coordinates." << endl;
	return 1;
}

srand(static_cast<unsigned int>(time(NULL)));

for (int i = 0; i < numCoords; i++) {
		float x = static_cast<float>(rand() % 100);
		float y = static_cast<float>(rand() % 100);
		add_coordinate(NULL,x, y);
}

cout << "Forward display of coordinates:" << endl;
forward_display(Glist_beginning);

cout << "\nBackward display of coordinates:" << endl;
backward_display(Glist_end);

cout << "\nDeleting coordinate with ID 3:" << endl;
delete_coordinate(Glist_beginning, 3);

cout << "\nForward display after deletion:" << endl;
forward_display(Glist_beginning);

cout << "\nFinding coordinate closest to (50, 50):" << endl;
closest_to(Glist_beginning, 50.0f, 50.0f);

while (Glist_beginning != NULL) {
	Coordinate* temp = Glist_beginning;
	Glist_beginning = Glist_beginning->next;
delete temp;
}
return 0;
}
