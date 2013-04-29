/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * Copyright (C) José Manuel Pintor Freire 2010 <jpfreire@correo.ei.uvigo.es>
 * 
 *     This program is free software: you can redistribute it and/or modify
 *     it under the terms of the GNU General Public License as published by
 *     the Free Software Foundation, either version 3 of the License, or
 *     (at your option) any later version.
 * 
 *     This program is distributed in the hope that it will be useful,
 *     but WITHOUT ANY WARRANTY; without even the implied warranty of
 *     MERCHANPOILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *     GNU General Public License for more details.
 * 
 *     You should have received a copy of the GNU General Public License
 *     along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "ScanFillLine.h"
#include <cmath>

/**
 Constructor.
 @param aV, int contiene el alto de la ventana.
 */
ScanFillLine::ScanFillLine(int aV)
{
	alturaVentana = aV;
}

/**
 Destructor.
 */
ScanFillLine::~ScanFillLine()
{

}

/**
 Algoritmo scanline fill.
 @param cnt, int contiene el numero de puntos.
 @param x, vector<int> contiene el vector de puntos del borde del eje x.
 @param y, vector<int> contiene el vector de puntos del borde del eje y.
 */
int ScanFillLine::scanFill(int cnt, vector<int> x, vector<int> y)
{
	Edge * edges[alturaVentana], * active;
	areaCelula = 0.0;

	//Coversion de vector a dcPt
	dcPt pts[cnt];

	for(unsigned int i = 0; i < x.size(); i++)
	{
		pts[i].x = x[i];
		pts[i].y = y[i];
	}
	
	for(int i = 0; i < alturaVentana; i++) 
	{
	  edges[i] = (Edge *) malloc (sizeof (Edge));
	  edges[i]->next = NULL;
	}
	
	buildEdgeList(cnt, pts, edges);
	active = (Edge *) malloc (sizeof (Edge));
	active->next = NULL;
	
	for(int scan = 0; scan < alturaVentana; scan++) 
	{
		buildActiveList (scan, active, edges);
		
		if (active->next) 
		{
			fillScan (scan, active);
			updateActiveList (scan, active);
			resortActiveList (active);
		}
	}

	areaCelula = areaCelula + cnt;
	
	return areaCelula;
}

/**
 Analiza el borde del ovocito.
 */
void ScanFillLine::buildEdgeList(int cnt, dcPt *pts, Edge *edges[])
{
	Edge *edge;
	dcPt v1, v2;
	int yPrev;

	yPrev = pts[cnt - 2].y;
	v1.x = pts[cnt - 1].x; 
	v1.y = pts[cnt - 1].y;
	
	for(int i = 0; i < cnt; i++)
	{
		v2 = pts[i];
		if(v1.y != v2.y)
		{                /* nonhorizontal line */
			edge = (Edge *) malloc (sizeof (Edge));
			if(v1.y < v2.y)
			{/* up-going edge      */
				makeEdgeRec (v1, v2, yNext (i, cnt, pts), edge, edges);
			}
			else
			{/* down-going edge    */
				makeEdgeRec (v2, v1, yPrev, edge, edges);
			}
		}
		yPrev = v1.y;
		v1 = v2;
	}
}

/**
 For an index, return y-coordinate of next nonhorizontal line 
 */
int ScanFillLine::yNext(int k, int cnt, dcPt * pts) 
{
	int j;

	if ((k+1) > (cnt-1))
	{
		j = 0;
	}
	else
	{
		j = k + 1;
	}
	
	while(pts[k].y == pts[j].y)
	{
		if ((j+1) > (cnt-1))
		{
   			j = 0;
		}
		else
		{
   			j++;
		}
	}
	return (pts[j].y);
}

/**
 Registra el borde.
 */
void ScanFillLine::makeEdgeRec(dcPt lower, dcPt upper, int yComp, 
                               Edge * edge, Edge * edges[])
{
	edge->dxPerScan = (float) (upper.x - lower.x) / (upper.y - lower.y);
	edge->xIntersect = lower.x;

	if(upper.y < yComp)
	{
		edge->yUpper = upper.y - 1;
	}
	else
	{
		edge->yUpper = upper.y;
	}

	insertEdge(edges[lower.y], edge);
}

/**
 Inserta el borde.
 */
void ScanFillLine::insertEdge(Edge *list, Edge *edge)
{
	Edge *p;
	Edge *q = list;
	
	p = q->next;

	while(p != NULL)
	{
		if (edge->xIntersect < p->xIntersect)
		{
  			p = NULL;
		}
		else
		{
  			q = p;
  			p = p->next;
		}
    }
	
	edge->next = q->next;
	q->next = edge;
}

/**
 Crear la lista activa.
 */
void ScanFillLine::buildActiveList(int scan, Edge * active, Edge * edges[])
{
	Edge *p, *q;
	p = edges[scan]->next;
	
	while(p)
	{
		q = p->next;
		insertEdge (active, p);
		p = q;
	}
}

/**
 Cuenta el area de la célula.
 @param scan, int.
 @param active, puntero Edge.
 */
void ScanFillLine::fillScan(int scan, Edge *active)
{
	Edge *p1, *p2;
	p1 = active->next;
	
	while(p1)
	{
		p2 = p1->next;

		if(p2 != NULL)
		{
			for(int i(static_cast<int>(floor(p1->xIntersect)));
				i < static_cast<int>(floor(p2->xIntersect)); i++)
			{
				areaCelula++;
			}
		
			p1 = p2->next;
		}
		else
		{
			p1 = NULL;
		}
	}
}

/**
 */
void ScanFillLine::updateActiveList(int scan, Edge *active)
{
	Edge *q = active, *p = active->next;

	while (p)
	{
		if (scan >= p->yUpper) 
		{
  			p = p->next;
  			deleteAfter (q);
		}
		else
		{
  			p->xIntersect = p->xIntersect + p->dxPerScan;
 			q = p;
  			p = p->next;
		}
    }
}

/**
 */
void ScanFillLine::deleteAfter(Edge * q)
{
	Edge * p = q->next;
	q->next = p->next;
	free(p);
}

/**
*/
void ScanFillLine::resortActiveList(Edge * active)
{
	Edge * q, * p = active->next;
	active->next = NULL;
	
	while(p)
	{
		q = p->next;
		insertEdge (active, p);
		p = q;
	}
}
