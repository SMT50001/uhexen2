/* region.c
 * Copyright (C) 1996-1997  Id Software, Inc.
 * Copyright (C) 1997-1998  Raven Software Corp.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or (at
 * your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

#include "q_stdinc.h"
#include "compiler.h"
#include "arch_def.h"
#include "cmdlib.h"
#include "mathlib.h"
#include "bspfile.h"
#include "bsp5.h"

/*

input
-----
vertexes
edges
faces

output
------
smaller set of vertexes
smaller set of edges
regions
? triangulated regions
face to region mapping numbers

*/

#define	MAX_EDGES_IN_REGION	32

static int		firstedge;
#if 0	/* all uses are commented out */
static vec3_t	region_mins, region_maxs;

static void AddPointToRegion (vec3_t p)
{
	int		i;

	for (i = 0 ; i < 3 ; i++)
	{
		if (p[i] < region_mins[i])
			region_mins[i] = p[i];
		if (p[i] > region_maxs[i])
			region_maxs[i] = p[i];
	}
}

static void ClearRegionSize (void)
{
	region_mins[0] = region_mins[1] = region_mins[2] = 9999;
	region_maxs[0] = region_maxs[1] = region_maxs[2] = -9999;
}

static void AddFaceToRegionSize (face_t *f)
{
	int		i;

	for (i = 0 ; i < f->numpoints ; i++)
		AddPointToRegion (f->pts[i]);
}

/*
==============
CanJoinFaces
==============
*/
static qboolean CanJoinFaces (face_t *f, face_t *f2)
{
	vec3_t		oldmins, oldmaxs;
	int			i;

	if (f2->planenum != f->planenum
			|| f2->planeside != f->planeside
			|| f2->texturenum != f->texturenum)
		return false;
	if (f2->outputnumber != -1)
		return false;
	if (f2->contents[0] != f->contents[0])
	{	// does this ever happen? theyy shouldn't share.
		printf ("%s: edge with different contents", __thisfunc__);
		return false;
	}

// check size constraints
	if ( ! (texinfo[f->texturenum].flags & TEX_SPECIAL) )
	{
		VectorCopy (region_mins, oldmins);
		VectorCopy (region_maxs, oldmaxs);
		AddFaceToRegionSize (f2);
		for (i = 0 ; i < 3 ; i++)
		{
			if (region_maxs[i] - region_mins[i] > 240)
			{
				VectorCopy (oldmins, region_mins);
				VectorCopy (oldmaxs, region_maxs);
				return false;
			}
		}
	}
	else
	{
		if (numsurfedges - firstedge + f2->numpoints > MAX_EDGES_IN_REGION)
			return false;	// a huge water or sky polygon
	}

// check edge count constraints
	return true;
}


/*
==============
RecursiveGrowRegion
==============
*/
static void RecursiveGrowRegion (dface_t *r, face_t *f)
{
	int		e;
	face_t	*f2;
	int		i;

	if (f->outputnumber == numfaces)
		return;

	if (f->outputnumber != -1)
		COM_Error ("%s: region collision", __thisfunc__);
	f->outputnumber = numfaces;

// add edges
	for (i = 0 ; i < f->numpoints ; i++)
	{
		e = f->edges[i];
		if (!edgefaces[abs(e)][0])
			continue;	// edge has already been removed
		if (e > 0)
			f2 = edgefaces[e][1];
		else
			f2 = edgefaces[-e][0];
		if (f2 && f2->outputnumber == numfaces)
		{
			edgefaces[abs(e)][0] = NULL;
			edgefaces[abs(e)][1] = NULL;
			continue;	// already merged
		}
		if (f2 && CanJoinFaces (f, f2))
		{	// remove the edge and merge the faces
			edgefaces[abs(e)][0] = NULL;
			edgefaces[abs(e)][1] = NULL;
			RecursiveGrowRegion (r, f2);
		}
		else
		{
		// emit a surfedge
			if (numsurfedges == MAX_MAP_SURFEDGES)
				COM_Error ("numsurfedges == MAX_MAP_SURFEDGES");
			dsurfedges[numsurfedges] = e;
			numsurfedges++;
		}
	}
}

static void RecursiveGrowRegion2 (dface2_t *r, face_t *f)
{
	int		e;
	face_t	*f2;
	int		i;

	if (f->outputnumber == numfaces)
		return;

	if (f->outputnumber != -1)
		COM_Error ("%s: region collision", __thisfunc__);
	f->outputnumber = numfaces;

// add edges
	for (i = 0 ; i < f->numpoints ; i++)
	{
		e = f->edges[i];
		if (!edgefaces[abs(e)][0])
			continue;	// edge has already been removed
		if (e > 0)
			f2 = edgefaces[e][1];
		else
			f2 = edgefaces[-e][0];
		if (f2 && f2->outputnumber == numfaces)
		{
			edgefaces[abs(e)][0] = NULL;
			edgefaces[abs(e)][1] = NULL;
			continue;	// already merged
		}
		if (f2 && CanJoinFaces (f, f2))
		{	// remove the edge and merge the faces
			edgefaces[abs(e)][0] = NULL;
			edgefaces[abs(e)][1] = NULL;
			RecursiveGrowRegion2 (r, f2);
		}
		else
		{
		// emit a surfedge
			if (numsurfedges == MAX_MAP_SURFEDGES)
				COM_Error ("numsurfedges == MAX_MAP_SURFEDGES");
			dsurfedges[numsurfedges] = e;
			numsurfedges++;
		}
	}
}
#endif	/* all uses commented out */

#if 0	/* no uses */
void PrintDface (int f)
{	// for debugging
	dface_t	*df;
	dedge_t	*e;
	int		i, n;

	df = &dfaces[f];
	for (i = 0 ; i < df->numedges ; i++)
	{
		n = dsurfedges[df->firstedge+i];
		e = &dedges[abs(n)];
		if (n < 0)
			printf ("%5i  =  %5i : %5i\n", n, e->v[1], e->v[0]);
		else
			printf ("%5i  =  %5i : %5i\n", n, e->v[0], e->v[1]);
	}
}

void PrintDface2 (int f)
{	// for debugging
	dface2_t	*df;
	dedge2_t	*e;
	int		i, n;

	df = &dfaces2[f];
	for (i = 0 ; i < df->numedges ; i++)
	{
		n = dsurfedges[df->firstedge+i];
		e = &dedges2[abs(n)];
		if (n < 0)
			printf ("%5i  =  %5i : %5i\n", n, e->v[1], e->v[0]);
		else
			printf ("%5i  =  %5i : %5i\n", n, e->v[0], e->v[1]);
	}
}

void FindVertexUse (int v)
{	// for debugging
	int		i, j, n;
	dface_t	*df;
	dedge_t	*e;

	for (i = firstmodelface ; i < numfaces ; i++)
	{
		df = &dfaces[i];
		for (j = 0 ; j < df->numedges ; j++)
		{
			n = dsurfedges[df->firstedge+j];
			e = &dedges[abs(n)];
			if (e->v[0] == v || e->v[1] == v)
			{
				printf ("on face %i\n", i);
				break;
			}
		}
	}
}

void FindVertexUse2 (int v)
{	// for debugging
	int		i, j, n;
	dface2_t	*df;
	dedge2_t	*e;

	for (i = firstmodelface ; i < numfaces ; i++)
	{
		df = &dfaces2[i];
		for (j = 0 ; j < df->numedges ; j++)
		{
			n = dsurfedges[df->firstedge+j];
			e = &dedges2[abs(n)];
			if (e->v[0] == v || e->v[1] == v)
			{
				printf ("on face %i\n", i);
				break;
			}
		}
	}
}

void FindEdgeUse (int v)
{	// for debugging
	int		i, j, n;
	dface_t	*df;

	for (i = firstmodelface ; i < numfaces ; i++)
	{
		df = &dfaces[i];
		for (j = 0 ; j < df->numedges ; j++)
		{
			n = dsurfedges[df->firstedge+j];
			if (n == v || -n == v)
			{
				printf ("on face %i\n", i);
				break;
			}
		}
	}
}

void FindEdgeUse2 (int v)
{	// for debugging
	int		i, j, n;
	dface2_t	*df;

	for (i = firstmodelface ; i < numfaces ; i++)
	{
		df = &dfaces2[i];
		for (j = 0 ; j < df->numedges ; j++)
		{
			n = dsurfedges[df->firstedge+j];
			if (n == v || -n == v)
			{
				printf ("on face %i\n", i);
				break;
			}
		}
	}
}
#endif	/* no uses */


#if 0	/* all uses are commented out */
/*
================
HealEdges

Extends e1 so that it goes all the way to e2, and removes all references
to e2
================
*/
static int		edgemapping[MAX_MAP_EDGES];
static void HealEdges (int e1, int e2)
{
	int		i, j, n, saved;
	dface_t	*df;
	dedge_t	*ed, *ed2;
	vec3_t	v1, v2;
	dface_t	*found[2];
	int		foundj[2];

// FIXME !!!!!
	return;

	e1 = edgemapping[e1];
	e2 = edgemapping[e2];

// extend e1 to e2
	ed = &dedges[e1];
	ed2 = &dedges[e2];
	VectorSubtract (dvertexes[ed->v[1]].point, dvertexes[ed->v[0]].point, v1);
	VectorNormalize (v1);

	if (ed->v[0] == ed2->v[0])
		ed->v[0] = ed2->v[1];
	else if (ed->v[0] == ed2->v[1])
		ed->v[0] = ed2->v[0];
	else if (ed->v[1] == ed2->v[0])
		ed->v[1] = ed2->v[1];
	else if (ed->v[1] == ed2->v[1])
		ed->v[1] = ed2->v[0];
	else
		COM_Error ("%s: edges don't meet", __thisfunc__);

	VectorSubtract (dvertexes[ed->v[1]].point, dvertexes[ed->v[0]].point, v2);
	VectorNormalize (v2);

	if (!VectorCompare (v1, v2))
		COM_Error ("%s: edges not colinear", __thisfunc__);

	edgemapping[e2] = e1;
	saved = 0;

// remove all uses of e2
	for (i = firstmodelface ; i < numfaces ; i++)
	{
		df = &dfaces[i];
		for (j = 0 ; j < df->numedges ; j++)
		{
			n = dsurfedges[df->firstedge+j];
			if (n == e2 || n == -e2)
			{
				found[saved] = df;
				foundj[saved] = j;
				saved++;
				break;
			}
		}
	}

	if (saved != 2)
		printf ("WARNING: didn't find both faces for a saved edge\n");
	else
	{
		for (i = 0 ; i < 2 ; i++)
		{	// remove this edge
			df = found[i];
			j = foundj[i];
			for (j++ ; j < df->numedges ; j++)
				dsurfedges[df->firstedge+j-1] = dsurfedges[df->firstedge+j];
			dsurfedges[df->firstedge+j-1] = 0;
			df->numedges--;
		}

		edgefaces[e2][0] = edgefaces[e2][1] = NULL;
	}
}

static void HealEdges2 (int e1, int e2)
{
	int		i, j, n, saved;
	dface2_t	*df;
	dedge2_t	*ed, *ed2;
	vec3_t	v1, v2;
	dface2_t	*found[2];
	int		foundj[2];

// FIXME !!!!!
	return;

	e1 = edgemapping[e1];
	e2 = edgemapping[e2];

// extend e1 to e2
	ed = &dedges2[e1];
	ed2 = &dedges2[e2];
	VectorSubtract (dvertexes[ed->v[1]].point, dvertexes[ed->v[0]].point, v1);
	VectorNormalize (v1);

	if (ed->v[0] == ed2->v[0])
		ed->v[0] = ed2->v[1];
	else if (ed->v[0] == ed2->v[1])
		ed->v[0] = ed2->v[0];
	else if (ed->v[1] == ed2->v[0])
		ed->v[1] = ed2->v[1];
	else if (ed->v[1] == ed2->v[1])
		ed->v[1] = ed2->v[0];
	else
		COM_Error ("%s: edges don't meet", __thisfunc__);

	VectorSubtract (dvertexes[ed->v[1]].point, dvertexes[ed->v[0]].point, v2);
	VectorNormalize (v2);

	if (!VectorCompare (v1, v2))
		COM_Error ("%s: edges not colinear", __thisfunc__);

	edgemapping[e2] = e1;
	saved = 0;

// remove all uses of e2
	for (i = firstmodelface ; i < numfaces ; i++)
	{
		df = &dfaces2[i];
		for (j = 0 ; j < df->numedges ; j++)
		{
			n = dsurfedges[df->firstedge+j];
			if (n == e2 || n == -e2)
			{
				found[saved] = df;
				foundj[saved] = j;
				saved++;
				break;
			}
		}
	}

	if (saved != 2)
		printf ("WARNING: didn't find both faces for a saved edge\n");
	else
	{
		for (i = 0 ; i < 2 ; i++)
		{	// remove this edge
			df = found[i];
			j = foundj[i];
			for (j++ ; j < df->numedges ; j++)
				dsurfedges[df->firstedge+j-1] = dsurfedges[df->firstedge+j];
			dsurfedges[df->firstedge+j-1] = 0;
			df->numedges--;
		}

		edgefaces[e2][0] = edgefaces[e2][1] = NULL;
	}
}

typedef struct
{
	int		numedges;
	int		edges[2];
} checkpoint_t;

static checkpoint_t	checkpoints[MAX_MAP_VERTS];

/*
==============
RemoveColinearEdges
==============
*/
static void RemoveColinearEdges (void)
{
	int		i, j, v;
	int		c0, c1, c2, c3;
	checkpoint_t	*cp;

// no edges remapped yet
	for (i = 0 ; i < numedges ; i++)
		edgemapping[i] = i;

// find vertexes that only have two edges
	memset (checkpoints, 0, sizeof(checkpoints));

	for (i = firstmodeledge ; i < numedges ; i++)
	{
		if (!edgefaces[i][0])
			continue;	// removed
		for (j = 0 ; j < 2 ; j++)
		{
			v = dedges[i].v[j];
			cp = &checkpoints[v];
			if (cp->numedges<2)
				cp->edges[cp->numedges] = i;
			cp->numedges++;
		}
	}

// if a vertex only has two edges and they are colinear, it can be removed
	c0 = c1 = c2 = c3 = 0;

	for (i = 0 ; i < numvertexes ; i++)
	{
		cp = &checkpoints[i];
		switch (cp->numedges)
		{
		case 0:
			c0++;
			break;
		case 1:
			c1++;
			break;
		case 2:
			c2++;
			if (usebsp2)
				HealEdges2 (cp->edges[0], cp->edges[1]);
			else
				HealEdges (cp->edges[0], cp->edges[1]);
			break;
		default:
			c3++;
			break;
		}
	}

//	qprintf ("%5i c0\n", c0);
//	qprintf ("%5i c1\n", c1);
//	qprintf ("%5i c2\n", c2);
//	qprintf ("%5i c3+\n", c3);
	qprintf ("%5i deges removed by tjunction healing\n", c2);
}
#endif	/* all uses commented out */


/*
==============
CountRealNumbers
==============
*/
static void CountRealNumbers (void)
{
	int		i;
	int		c;

	qprintf ("%5i regions\n", numfaces-firstmodelface);

	c = 0;
	for (i = firstmodelface ; i < numfaces ; i++)
		c += usebsp2 ? dfaces2[i].numedges : dfaces[i].numedges;
	qprintf ("%5i real marksurfaces\n", c);

	c = 0;
	for (i = firstmodeledge ; i < numedges ; i++)
	{
		if (edgefaces[i][0])
			c++;		// not removed
	}

	qprintf ("%5i real edges\n", c);
}

//=============================================================================

/*
==============
GrowNodeRegion_r
==============
*/
static void GrowNodeRegion_r (node_t *node)
{
	dface_t		*r;
	face_t		*f;
	int			i;

	if (node->planenum == PLANENUM_LEAF)
		return;

	node->firstface = numfaces;

	for (f = node->faces ; f ; f = f->next)
	{
		//if (f->outputnumber != -1)
		//	continue;	// already grown into an earlier region

	// emit a region
		if (numfaces == MAX_MAP_FACES)
			COM_Error ("MAX_MAP_FACES");
		f->outputnumber = numfaces;
		r = &dfaces[numfaces];

		r->planenum = node->outputplanenum;
		r->side = f->planeside;
		r->texinfo = f->texturenum;
		for (i = 0 ; i < MAXLIGHTMAPS ; i++)
			r->styles[i] = 255;
		r->lightofs = -1;

	// add the face and mergable neighbors to it
#if 0
		ClearRegionSize ();
		AddFaceToRegionSize (f);
		RecursiveGrowRegion (r, f);
#endif
		r->firstedge = firstedge = numsurfedges;
		for (i = 0 ; i < f->numpoints ; i++)
		{
			if (numsurfedges == MAX_MAP_SURFEDGES)
				COM_Error ("numsurfedges == MAX_MAP_SURFEDGES");
			dsurfedges[numsurfedges] = f->edges[i];
			numsurfedges++;
		}

		r->numedges = numsurfedges - r->firstedge;

		LightValues[numfaces] = f->Light;

		numfaces++;
	}

	node->numfaces = numfaces - node->firstface;

	GrowNodeRegion_r (node->children[0]);
	GrowNodeRegion_r (node->children[1]);
}

static void GrowNodeRegion_r2 (node_t *node)
{
	dface2_t	*r;
	face_t		*f;
	int			i;

	if (node->planenum == PLANENUM_LEAF)
		return;

	node->firstface = numfaces;

	for (f = node->faces ; f ; f = f->next)
	{
		//if (f->outputnumber != -1)
		//	continue;	// already grown into an earlier region

	// emit a region
		if (numfaces == MAX_MAP_FACES)
			COM_Error ("MAX_MAP_FACES");
		f->outputnumber = numfaces;
		r = &dfaces2[numfaces];

		r->planenum = node->outputplanenum;
		r->side = f->planeside;
		r->texinfo = f->texturenum;
		for (i = 0 ; i < MAXLIGHTMAPS ; i++)
			r->styles[i] = 255;
		r->lightofs = -1;

	// add the face and mergable neighbors to it
#if 0
		ClearRegionSize ();
		AddFaceToRegionSize (f);
		RecursiveGrowRegion2 (r, f);
#endif
		r->firstedge = firstedge = numsurfedges;
		for (i = 0 ; i < f->numpoints ; i++)
		{
			if (numsurfedges == MAX_MAP_SURFEDGES)
				COM_Error ("numsurfedges == MAX_MAP_SURFEDGES");
			dsurfedges[numsurfedges] = f->edges[i];
			numsurfedges++;
		}

		r->numedges = numsurfedges - r->firstedge;

		LightValues[numfaces] = f->Light;

		numfaces++;
	}

	node->numfaces = numfaces - node->firstface;

	GrowNodeRegion_r2 (node->children[0]);
	GrowNodeRegion_r2 (node->children[1]);
}


/*
==============
GrowNodeRegions
==============
*/
void GrowNodeRegions (node_t *headnode)
{
	qprintf ("---- GrowRegions ----\n");

	if (usebsp2)
		GrowNodeRegion_r2 (headnode);
	else
		GrowNodeRegion_r (headnode);

	//RemoveColinearEdges ();
	CountRealNumbers ();
}


/*
===============================================================================

Turn the faces on a plane into optimal non-convex regions
The edges may still be split later as a result of tjunctions

typedef struct
{
	vec3_t	dir;
	vec3_t	origin;
	vec3_t	p[2];
}
for all faces
	for all edges
		for all edges so far
			if overlap
				split

===============================================================================
*/

