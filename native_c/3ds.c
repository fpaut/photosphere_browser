/*
 * ---------------- www.spacesimulator.net --------------
 *   ---- Space simulators and 3d engine tutorials ----
 *
 * Author: Damiano Vitulli
 *
 * This program is released under the BSD licence
 * By using this program you agree to licence terms on spacesimulator.net copyright page
 *
 *
 * Tutorial 4: 3d engine - 3ds models loader
 *
 * Include File: 3dsloader.cpp
 *
 */

/*
Linux port by Panteleakis Ioannis
mail: pioann@csd.auth.gr

just run: make and you are done.
of course you may need to change the makefile
*/


#include <stdio.h>
#include <stdlib.h>
#include <GL/gl.h>
#include "3ds.h"

#include <sys/stat.h>

/**********************************************************
 *
 * VARIABLES DECLARATION
 *
 *********************************************************/

/**********************************************************
 *
 * FUNCTION Load3DS (obj_type_ptr, char *)
 *
 * This function loads a mesh from a 3ds file.
 * Please note that we are loading only the vertices, polygons and mapping lists.
 * If you need to load meshes with advanced features as for example:
 * multi objects, materials, lights and so on, you must insert other chunk parsers.
 *
 *********************************************************/


long filelength(int f)
{
    struct stat buf;

    fstat(f, &buf);

    return(buf.st_size);
}

void display3DSobj(obj_3ds_ptr pObj3ds)
{
    int l_index;


    glBindTexture(GL_TEXTURE_2D, pObj3ds->id_texture); // We set the active texture

    glBegin(GL_TRIANGLES); // glBegin and glEnd delimit the vertices that define a primitive (in our case triangles)
    for (l_index=0;l_index<pObj3ds->polygons_qty;l_index++)
    {
        //----------------- FIRST VERTEX -----------------
        // Texture coordinates of the first vertex
        glTexCoord2f( pObj3ds->mapcoord[ pObj3ds->polygon[l_index].a ].u,
                      pObj3ds->mapcoord[ pObj3ds->polygon[l_index].a ].v);
        // Coordinates of the first vertex
        glVertex3f( pObj3ds->vertex[ pObj3ds->polygon[l_index].a ].x,
                    pObj3ds->vertex[ pObj3ds->polygon[l_index].a ].y,
                    pObj3ds->vertex[ pObj3ds->polygon[l_index].a ].z); //Vertex definition

        //----------------- SECOND VERTEX -----------------
        // Texture coordinates of the second vertex
        glTexCoord2f( pObj3ds->mapcoord[ pObj3ds->polygon[l_index].b ].u,
                      pObj3ds->mapcoord[ pObj3ds->polygon[l_index].b ].v);
        // Coordinates of the second vertex
        glVertex3f( pObj3ds->vertex[ pObj3ds->polygon[l_index].b ].x,
                    pObj3ds->vertex[ pObj3ds->polygon[l_index].b ].y,
                    pObj3ds->vertex[ pObj3ds->polygon[l_index].b ].z);

        //----------------- THIRD VERTEX -----------------
        // Texture coordinates of the third vertex
        glTexCoord2f( pObj3ds->mapcoord[ pObj3ds->polygon[l_index].c ].u,
                      pObj3ds->mapcoord[ pObj3ds->polygon[l_index].c ].v);
        // Coordinates of the Third vertex
        glVertex3f( pObj3ds->vertex[ pObj3ds->polygon[l_index].c ].x,
                    pObj3ds->vertex[ pObj3ds->polygon[l_index].c ].y,
                    pObj3ds->vertex[ pObj3ds->polygon[l_index].c ].z);
    }
    glEnd();

    glFlush(); // This force the execution of OpenGL commands
}

char Load3DS (obj_3ds_ptr pObj3ds, char *p_filename)
{
	int i; //Index variable

	FILE *l_file; //File pointer

	unsigned short l_chunk_id; //Chunk identifier
	unsigned int l_chunk_lenght; //Chunk lenght

	unsigned char l_char; //Char variable
	unsigned short l_qty; //Number of elements in each chunk

	unsigned short l_face_flags; //Flag that stores some face information

	if ((l_file=fopen (p_filename, "rb"))== NULL) return 0; //Open the file

	while (ftell (l_file) < filelength (fileno (l_file))) //Loop to scan the whole file
	//while(!EOF)
	{
		//getch(); //Insert this command for debug (to wait for keypress for each chuck reading)

		fread (&l_chunk_id, 2, 1, l_file); //Read the chunk header
		printf("ChunkID: %x\n",l_chunk_id);
		fread (&l_chunk_lenght, 4, 1, l_file); //Read the lenght of the chunk
		printf("ChunkLenght: %x\n",l_chunk_lenght);

		switch (l_chunk_id)
        {
			//----------------- MAIN3DS -----------------
			// Description: Main chunk, contains all the other chunks
			// Chunk ID: 4d4d
			// Chunk Lenght: 0 + sub chunks
			//-------------------------------------------
			case 0x4d4d:
			break;

			//----------------- EDIT3DS -----------------
			// Description: 3D Editor chunk, objects layout info
			// Chunk ID: 3d3d (hex)
			// Chunk Lenght: 0 + sub chunks
			//-------------------------------------------
			case 0x3d3d:
			break;

			//--------------- EDIT_OBJECT ---------------
			// Description: Object block, info for each object
			// Chunk ID: 4000 (hex)
			// Chunk Lenght: len(object name) + sub chunks
			//-------------------------------------------
			case 0x4000:
				i=0;
				do
				{
					fread (&l_char, 1, 1, l_file);
                    pObj3ds->name[i]=l_char;
					i++;
                }while(l_char != '\0' && i<20);
			break;

			//--------------- OBJ_TRIMESH ---------------
			// Description: Triangular mesh, contains chunks for 3d mesh info
			// Chunk ID: 4100 (hex)
			// Chunk Lenght: 0 + sub chunks
			//-------------------------------------------
			case 0x4100:
			break;

			//--------------- TRI_VERTEXL ---------------
			// Description: Vertices list
			// Chunk ID: 4110 (hex)
			// Chunk Lenght: 1 x unsigned short (number of vertices)
			//             + 3 x float (vertex coordinates) x (number of vertices)
			//             + sub chunks
			//-------------------------------------------
			case 0x4110:
				fread (&l_qty, sizeof (unsigned short), 1, l_file);
                pObj3ds->vertices_qty = l_qty;
                printf("Number of vertices: %d\n",l_qty);
                for (i=0; i<l_qty; i++)
                {
					fread (&pObj3ds->vertex[i].x, sizeof(float), 1, l_file);
                    fread (&pObj3ds->vertex[i].y, sizeof(float), 1, l_file);
					fread (&pObj3ds->vertex[i].z, sizeof(float), 1, l_file);
 					printf("Vertices list x: %f\t  y: %f\t  z: %f\n", pObj3ds->vertex[i].x, pObj3ds->vertex[i].y, pObj3ds->vertex[i].z);
				}
				break;

			//--------------- TRI_FACEL1 ----------------
			// Description: Polygons (faces) list
			// Chunk ID: 4120 (hex)
			// Chunk Lenght: 1 x unsigned short (number of polygons)
			//             + 3 x unsigned short (polygon points) x (number of polygons)
			//             + sub chunks
			//-------------------------------------------
			case 0x4120:
				fread (&l_qty, sizeof (unsigned short), 1, l_file);
                pObj3ds->polygons_qty = l_qty;
                printf("Number of polygons: %d\n",l_qty);
                for (i=0; i<l_qty; i++)
                {
					fread (&pObj3ds->polygon[i].a, sizeof (unsigned short), 1, l_file);
					fread (&pObj3ds->polygon[i].b, sizeof (unsigned short), 1, l_file);
					fread (&pObj3ds->polygon[i].c, sizeof (unsigned short), 1, l_file);
					fread (&l_face_flags, sizeof (unsigned short), 1, l_file);
					printf("Polygon point a: %d\t b: %d\t c: %d\t Face flags: %x\n",pObj3ds->polygon[i].a, pObj3ds->polygon[i].b, pObj3ds->polygon[i].c, l_face_flags);
				}
                break;

			//------------- TRI_MAPPINGCOORS ------------
			// Description: Vertices list
			// Chunk ID: 4140 (hex)
			// Chunk Lenght: 1 x unsigned short (number of mapping points)
			//             + 2 x float (mapping coordinates) x (number of mapping points)
			//             + sub chunks
			//-------------------------------------------
			case 0x4140:
				fread (&l_qty, sizeof (unsigned short), 1, l_file);
				for (i=0; i<l_qty; i++)
				{
					fread (&pObj3ds->mapcoord[i].u, sizeof (float), 1, l_file);
                    fread (&pObj3ds->mapcoord[i].v, sizeof (float), 1, l_file);
					printf("Mapping list  u: %f\t v: %f\n", pObj3ds->mapcoord[i].u, pObj3ds->mapcoord[i].v);
				}
                break;

			//----------- Skip unknow chunks ------------
			//We need to skip all the chunks that currently we don't use
			//We use the chunk lenght information to set the file pointer
			//to the same level next chunk
			//-------------------------------------------
			default:
				 fseek(l_file, l_chunk_lenght-6, SEEK_CUR);
        }
	}
	fclose (l_file); // Closes the file stream
	return (1); // Returns ok
}
