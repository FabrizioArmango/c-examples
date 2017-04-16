#include <stdio.h>
#include <stdbool.h>
#include <malloc.h>

/*
 *
 * ************************************************************************
 * *** * 16/04/2017											  			  *
 * *** * Fabrizio Armango									  			  *
 *   *							    								  *   *
 *   *   Feel free to use, copy, alter and share this source code.	  *   *
 *   *	 															  *	  *
 **************************************************************************
 *
*/ 

typedef struct Point
{
	float x;
	float y;
	struct Point* next;
} Point;

typedef struct PointList
{
	struct Point* head;
} PointList;

void pointPrint(Point* p) 
{
  printf("(%f,%f)", p->x, p->y);
}

void printPointList(PointList* list)
{	
	Point* p = list->head;
	printf("List: [  ");
	if (p != NULL)
	{		
		pointPrint(p);
		while(p->next != NULL)
		{
			printf(", ");
			p = p->next;
			pointPrint(p);	
		}		
	}
	printf("  ]\n");
}

Point* createPoint(float x, float y)
{
	Point* 	point = malloc(sizeof(Point));
			point->x = x;
			point->y = y;
			point->next = NULL;
    return  point;
}

PointList* createPointList()
{
	PointList* 	point = malloc(sizeof(PointList));
			point->head = NULL;
    return  point;
}

void insertPointTo(float x, float y, PointList* list)
{
	Point* p = list->head;
	bool notExists = true;
	bool goOn = true;
	
	if (p == NULL)
	{
		list->head = createPoint(x, y);
	} else 
	{				
		while (goOn == true && notExists == true)
		{
			if(p->x == x && p->y == y)
				notExists = false;
			
			if(p->next != NULL)
				p = p->next;
			else goOn = false;
		}
		if (notExists == true)
			p->next = createPoint(x, y);
					
	}
}

bool removePointFrom(float x, float y, PointList* list)
{
	Point* p = list->head;
	Point* tmp;
	if (p == NULL)
		return false;
		
	if(p->x == x && p->y == y)
	{		
		list->head = p->next;
		free(p);
		return true;
	}
	
	while (p != NULL)
	{
		tmp = p->next;
		if(tmp->x == x || tmp->y == y)
		{
			p->next = tmp->next;
			free(tmp);
			return true;
		}
		p = p->next;
	}
	
	return false;		
}

bool existsPointIn(float x, float y, PointList* list)
{
	Point* p = list->head;
	if (p == NULL)
		return false;
		
	if(p->x == x && p->y == y)
		return true;

	while(p->next != NULL)
	{
		p = p->next;
		if(p->x == x && p->y == y)
			return true;
	}
	
	return false;

}

int main(void)
{
	PointList* lista = createPointList(); 	
	
	insertPointTo(1, 1.2, lista);

	insertPointTo(2, 1.2, lista);
		
	insertPointTo(3, 1.2, lista);
	insertPointTo(3, 1.2, lista);
	insertPointTo(22.1, 1.11, lista);
	printPointList(lista);
	
	removePointFrom(22.1, 1.11, lista);
	printPointList(lista);
	
	printf("Exists: %s\n", existsPointIn(3, 1.2, lista) ? "si" : "no");
	printf("Exists: %s\n", existsPointIn(1, 0, lista) ? "si" : "no");

	
	return 0;
}
