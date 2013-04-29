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

#ifndef _SCANFILLLINE_H_
	#define _SCANFILLLINE_H_

	#include <iostream>
	#include <cstdlib>
	#include <vector>

	using namespace std;

	typedef struct tEdge
	{
		int yUpper;
		float xIntersect, dxPerScan;
		struct tEdge *next;
	} Edge;

	typedef struct tdcPt
	{
		int x;
		int y;
	} dcPt;

	class ScanFillLine
	{
		public:
			ScanFillLine(int aV);
			~ScanFillLine();
			int scanFill(int cnt, vector<int> x, vector<int> y);
		private:
			void buildEdgeList(int cnt, dcPt *pts, Edge *edges[]);
			int yNext(int k, int cnt, dcPt *pts);
			void makeEdgeRec(dcPt lower, dcPt upper, int yComp, Edge *edge, Edge *edges[]);
			void insertEdge(Edge *list, Edge *edge);
			void buildActiveList(int scan, Edge *active, Edge *edges[]);
			void fillScan(int scan, Edge *active);
			void updateActiveList(int scan, Edge *active);
			void deleteAfter(Edge *q);
			void resortActiveList(Edge * active);
			//Atributos
			int alturaVentana;
			double areaCelula;
			
			
	};
#endif //_SCANFILLLINE_H_
