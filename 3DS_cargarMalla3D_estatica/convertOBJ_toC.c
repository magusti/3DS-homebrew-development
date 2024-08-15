//
//gcc convertOBJ_toC.c -o convertOBJ_toC
// gcc convertOBJ_toC.c -o convertOBJ_toC && convertOBJ_toC cubeBlender_includeNormals_Geometry_TriangulateFaces.obj 
// gcc convertOBJ_toC.c -o convertOBJ_toC && convertOBJ_toC monkeyBlender.obj > codic.c  && kate codic.c
// 
// $ gcc convertOBJ_toC.c -o convertOBJ_toC && convertOBJ_toC torus.obj torus.c torus.h
// $ gcc convertOBJ_toC.c -o convertOBJ_toC && convertOBJ_toC varios.obj varios.c varios.h
// 
// $ gcc convertOBJ_toC.c -o convertOBJ_toC && convertOBJ_toC monkeyBlender.obj monkeyBlender.c monkeyBlender.h
// $ cp -p monkeyBlender.c  source/lenny.c ; cp -p monkeyBlender.h  source/lenny.h
// $ make clean && make && citra.sh  lenny_a_OBJ.3dsx 
// 
// $ gcc convertOBJ_toC.c -o convertOBJ_toC && convertOBJ_toC teapot.obj dragon.c dragon.h
// teapot.obj                  teapot_pasatPerBlender.mtl  teapot_pasatPerBlender.obj  
// magusti@verdet:~/docencia/2k22-2k23/AEV/temes/lenny_a_OBJ$ gcc convertOBJ_toC.c -o convertOBJ_toC && convertOBJ_toC teapot_pasatPerBlender..obj teapot.c teapot.h
// 
//
#include <stdio.h> // FILE
#include <stdlib.h> // malloc
#include <string.h> // strstr
//
// En esta versió no es gasten els vt, encara que es conten si eixen
//
// Caldria comprovar que els indiex que vas a gastar de les 'f' han segut llegits antes en 'v', o 'vn'.
//
//

// https://www.kodeco.com/2604-how-to-export-blender-models-to-opengl-es-part-1-3
/*
 *    model.vertices = model.faces*3;
 */

#define LONGMAXLINIA 1024
int getOBJinfo(char *filepathOBJ, long int *nVertices, long int *nVTextura, long int *nNormals, long int *nCares ) {
    FILE *fichero;
    char linia[LONGMAXLINIA];
    
    if ((fichero = fopen(filepathOBJ, "r")) == NULL) {
        printf ( " Error al abrir %s\n ", filepathOBJ);
        return( 0 );
    }
    
    *nVertices = 0;
    *nVTextura = 0;
    *nNormals = 0;
    *nCares = 0;
    
    //  while()     {
    //   fscanf( fichero, "%s", linia);
    // while( !feof( fichero ) && !fgets(linia, LONGMAXLINIA, fichero) )     {     
    while(!feof( fichero ))     {
        if (!fgets(linia, LONGMAXLINIA, fichero)) break;
        
        //   printf("%ld ??? %s\n", strlen(linia), linia);
        
        if ((linia[0] != '#') && (linia[0] != '\n')){
            //     printf("%s\n", linia);
            if ( (linia[0] == 'v') && (linia[1] == ' ') ) {
                (*nVertices)++;
                //          printf("Vertex %ld\n", *nVertices);
            }
            else if ( (linia[0] == 'v') && (linia[1] == 't') ) {
                //          printf("Vertex textura \n");
                (*nVTextura)++;
                //          printf("Vertex textura %ld\n", *nVTextura);
            }
            else if ( (linia[0] == 'v') && (linia[1] == 'n') ) {
                //          printf("Normals \n");
                (*nNormals)++;
                //          printf("Normals %ld\n", *nNormals);
            }
            else if ( (linia[0] == 'f') && (linia[1] == ' ') ) {
                (*nCares)++;
                //          printf("Cares %ld\n", *nCares);
            }
            else{
                // De moment no se processen atres elements d'un OBJ                
            }
        }  
    }
    
    return( 1 );
} // Fi de getOBJinfo


// typedef
//  float vt[3];
//  float vn[2];
//  float v[3]
// }tipo_punts;
// 
// typedef
//  float vt[3];
//  float v[3]
// }tipo_punts_senseTextura;
// 
// tipo_punts *model;
// tipo_punts_senseTextura *model_senseTextura;
//
// Model Info
// Model model = 




typedef struct {
    float x;
    float y;
    float z;
}tipoVectorVertices;

typedef struct {
    float u;
    float v;
}tipoVectorTextures;

typedef struct {
    float x;
    float y;
    float z;
}tipoVectorNormales;


typedef struct {
    tipoVectorVertices *v;
    tipoVectorNormales *vn;
}tipoPosicionsMalla;

tipoPosicionsMalla *malla; // Que es dimensiona a #posicions = 3*nCares de tipoPosicionsMalla

typedef struct {
    tipoVectorVertices *v;
    tipoVectorTextures *vt;
    tipoVectorNormales *vn;
}tipoPosicionsMalla_conTextura;



// Imprimeix les posicions de la rejilla -> {vertex, normal] per a cada un dels 3 punt dels triangles en que es dibuixen les cares.
int volcartRejillaOBJ( char *filepathOBJ, long int nVertices, long int nVTextures, long int nNormals, long int nCares, char *nomModel_c, char *nomModel_h ) {
    FILE *fichero, *fitxerCodic;
    char linia[LONGMAXLINIA];  
    tipoVectorVertices *vectorVertex;
    tipoVectorTextures *vectorVTextures;
    tipoVectorNormales *vectorNormals;
    long int lnVertices, lnVTextures, lnNormals, lnCares;
    long int v1, vt1, vn1, v2, vt2, vn2, v3, vt3, vn3;
    int escriureCapsalera = 1;
    int n;
    long int contaorLinia;
    
    lnVertices = 0;
    lnVTextures = 0;
    lnNormals = 0;
    lnCares = 0;
    
    
    
    if ((fichero = fopen(filepathOBJ, "r")) == NULL) {
        printf ( "volcarRejilla: Error al abrir %s\n ", filepathOBJ);
        return( 0 );
    }
    
    
    vectorVertex = (tipoVectorVertices *)malloc( nVertices * sizeof(tipoVectorVertices));
    if (vectorVertex == NULL) {
        printf("Falta memòria per als vertex\n");
        return( -1 );
    }
    printf("Vertex   %p --> %p\n", &vectorVertex, vectorVertex);
    
    vectorVTextures = (tipoVectorTextures *)malloc( nVTextures * sizeof(tipoVectorTextures));
    if (vectorVTextures == NULL) {
        printf("Falta memòria per als vertex de textures\n");
        return( -2 );
    }
    printf("Textures %p\n", vectorVTextures);
    //  free( vectorVTextures);
    //  printf("Textures %p\n", vectorVTextures);
    
    vectorNormals = (tipoVectorNormales *)malloc( nNormals * sizeof(tipoVectorNormales) );
    if (vectorNormals == NULL) {
        printf("Falta memòria per als vectors de  normals\n");
        return( -3 );
    }
    printf("Normals  %p\n", vectorNormals);
    
    //  vectorVTextures= (tipoVectorTextures *)malloc( nVertices * sizeof(tipoVectorTextures));
    //  if (vectorVTextures == NULL) {
    //       printf("Falta memòria per als vertex de textures\n");
    //       return( -2 );
    //  }
    //  printf("Textures %p\n", vectorVTextures);
    
    
    if ((fitxerCodic = fopen(nomModel_h, "wt")) == NULL) {
        printf ( " Error al abrir %s\n ", nomModel_h);
        return( 0 );
    }
    fprintf(fitxerCodic, "\
    //lenny.h\n\
    #pragma once\n\
    \n\
    typedef struct\n\
    {\n\
    float x, y, z;\n\
    float nx, ny, nz;\n\
} vertex;\n\
\n\
extern const vertex vertex_list[%ld];\n\
#define vertex_list_count (sizeof(vertex_list)/sizeof(vertex_list[0]))\n\n\n\
", nCares*3);
    fclose( fitxerCodic );
    
    
    if ((fitxerCodic = fopen(nomModel_c, "wt")) == NULL) {
        printf ( " Error al abrir %s\n ", nomModel_h);
        return( 0 );
    }
    fprintf(fitxerCodic, "\
    #include \"lenny.h\"\n\n\
    const vertex vertex_list[%ld] = {\n", nCares*3);
    
    
    contaorLinia = 0;
    
    while(!feof( fichero ))     {
        //   fgets(linia, LONGMAXLINIA, fichero);
        if (!fgets(linia, LONGMAXLINIA, fichero)) break;
        //    if ( escriureCapsalera ) {
        //        escriureCapsalera = !escriureCapsalera;
        //        printf("\
        // //lenny.h\n\
        // #pragma once\n\
        // \n\
        // typedef struct\n\
        // {\n\
        // 	float x, y, z;\n\
        // 	float nx, ny, nz;\n\
        // } vertex;\n\
        // \n\
        // extern const vertex vertex_list[%ld];\n\
        // #define vertex_list_count (sizeof(vertex_list)/sizeof(vertex_list[0]))\n\n\n\
        // ", nCares*3);
        //    
        //        
        //        printf("//lenny.c\n\
        // #include \"lenny.h\"\n\n\
        // const vertex vertex_list[%ld] = {\n", nCares*3);
        //            
        //    }
        
        contaorLinia++;
        //       printf("(%ld); %s\n", contaorLinia, linia);
        //     continue;
        
        if ((linia[0] != '#') && (linia[0] != '\n')){
            //       printf("%s\n", linia);
            if ( (linia[0] == 'v') && (linia[1] == ' ') ) {         
                //          printf("Vertex %ld <-- %s\n", lnVertices, linia);
                n = sscanf(linia, "v %f %f %f",  &(vectorVertex[lnVertices].x), &(vectorVertex[lnVertices].y), &(vectorVertex[lnVertices].z) );
                //          printf("Vertex[%ld] = %f,  %f, %f\n", lnVertices, vectorVertex[lnVertices].x, vectorVertex[lnVertices].y, vectorVertex[lnVertices].z );
                if (n < 3 ) {
//                     printf("v: Error en format de la linea %ld: %s i fichero = %ld\n", contaorLinia, linia, fichero);
                      printf("v: Error en format de la linea %ld: %s\n", contaorLinia, linia);                    
                    break;                    
                }         
                lnVertices++;
                fprintf( stderr, "v: %ld/%ld\r", lnVertices, nVertices);                   
            }
            else if ( (linia[0] == 'v') && (linia[1] == 't') ) {
                //          printf("Vectors textures %ld <-- %s\n", lnVTextures, linia);
                n = sscanf(linia, "vt %f %f",  &(vectorVTextures[lnVTextures].u), &(vectorVTextures[lnVTextures].v) );
                //          printf("vTextures[%ld] = %f,  %f, %f\n", lnNormals, vectorVTextures[lnVTextures].u, vectorVTextures[lnVTextures].v );
                if (n < 2 ) {
                    printf("vt: Error en format de la linea %ld: %s\n", contaorLinia, linia);
                    break;
                }         
                lnVTextures++;
                fprintf( stderr, "vt: %ld/%ld\r", lnVTextures, nVTextures);         
            }
            else if ( (linia[0] == 'v') && (linia[1] == 'n') ) {
                //          printf("Normals %ld <-- %s\n", lnNormals, linia);
                n = sscanf(linia, "vn %f %f %f",  &(vectorNormals[lnNormals].x), &(vectorNormals[lnNormals].y), &(vectorNormals[lnNormals].z) );
                //          printf("Normal[%ld] = %f,  %f, %f\n", lnNormals, vectorNormals[lnNormals].x, vectorNormals[lnNormals].y,vectorNormals[lnNormals].z );
                if (n < 3 ) {
                    printf("vn: Error en format de la linea %ld: %s\n", contaorLinia, linia);
                    break;
                }         
                lnNormals++;
                fprintf( stderr, "vn: %ld/%ld\r", lnNormals, nNormals);         
                
            }
            else if ( (linia[0] == 'f') && (linia[1] == ' ') ) {
                fprintf(stderr, "Cara %ld <-- %s\n", lnCares, linia);
                // 'f' --> per cada triangle: {v1, uv1, vn1, v2, uv2, vn2, v3, uv3, vn3,}  a on v és vertex uv són coords. textura i vn son les normals
                n = sscanf(linia, "f %ld/%ld/%ld %ld/%ld/%ld %ld/%ld/%ld",  &v1, &vt1, &vn1, &v2, &vt2, &vn2, &v3, &vt3, &vn3  );
                //          printf("%ld components de la cara %ld = %ld/%ld/%ld  %ld/%ld/%ld  %ld/%ld/%ld\n", n, lnCares,  v1, vt1, vn1, v2, vt2, vn2, v3, vt3, vn3  );
                if (n < 9 ) {
                    fprintf(stderr, "(%d) Error <9 en format de la linea %ld: %s\n", n,contaorLinia, linia);
                    //              break;
                    n = sscanf(linia, "f %ld//%ld %ld//%ld %ld//%ld",  &v1, &vn1, &v2, &vn2, &v3, &vn3  );
                    if (n < 6 ) {
                        fprintf(stderr, "(%d) Error <6 en format de la linea %ld: %s\n", n, contaorLinia, linia);
                        //              break;
                        exit( 2 ) ;
                    }    
                }    
                fprintf(stderr, "n = %d, f { %ld, %ld, %ld, %ld, %ld, %ld }\n", n, v1, vn1, v2, vn2, v3, vn3 );
                fprintf(fitxerCodic , "{ %f, %f, %f, %f, %f, %f },\n", vectorVertex[v1-1].x, vectorVertex[v1-1].y, vectorVertex[v1-1].z, vectorNormals[vn1-1].x, vectorNormals[vn1-1].y,  vectorNormals[vn1-1].z );
                fprintf(fitxerCodic , "{ %f, %f, %f, %f, %f, %f },\n", vectorVertex[v2-1].x, vectorVertex[v2-1].y, vectorVertex[v2-1].z, vectorNormals[vn2-1].x, vectorNormals[vn2-1].y,  vectorNormals[vn2-1].z );
                fprintf(fitxerCodic , "{ %f, %f, %f, %f, %f, %f },\n", vectorVertex[v3-1].x, vectorVertex[v3-1].y, vectorVertex[v3-1].z, vectorNormals[vn3-1].x, vectorNormals[vn3-1].y,  vectorNormals[vn3-1].z );
                lnCares++;
                fprintf( stderr, "f: %ld/%ld\r", lnCares, nCares);         
                //          printf("Cares %ld\n", lnCares);
            }    
        }  
    }
    
    //  if ( !escriureCapsalera ) fprintf(fitxerCodic , "};\n\n");
    fprintf(fitxerCodic , "};\n\n");
    fclose( fitxerCodic );
    
    fflush( stdout );
//     printf(" LLiberant recursos\n");
//     printf(">>>#vt: %ld/%ld\n", 
//            lnVTextures, nVTextures         );         
//     printf("#vn: %ld/%ld\n#f: %ld/%ld\n" , 
//            lnNormals, nNormals, lnCares, nCares);         
//     printf(">>>#v: %ld/%ld\n>>>>>>>>>>>>>>>>#vt: %ld/%ld\n#vn: %ld/%ld\n#f: %ld/%ld\n", 
//            lnVertices, nVertices, lnVTextures, nVTextures, 
//            lnNormals, nNormals, lnCares, nCares);         
//     
//     printf("Vertex   %p\n", vectorVertex);
    if ( vectorVertex    != NULL ) { 
        free( vectorVertex ); 
//         fprintf(stderr, "llibera v\n");         
    }
//     printf("Textures %p\n", vectorVTextures);
    if ( vectorVTextures != NULL ) { 
        free( vectorVTextures); 
//         fprintf(stderr, "llibera vt\n");         
    }
//     printf("Normals  %p\n", vectorNormals);
    if ( vectorNormals   != NULL ) { 
        free( vectorNormals ); 
//         fprintf(stderr, "llibera vn\n"); 
    }
    
} // Fi de volcartRejillaOBJ



int main( int argc, char *argv[] ) {
    
    long int nVertices, nVTextura, nNormals, nCares;
    char *p;
    char nomModel_c[1024],nomModel_h[1024];;
    
    // printf("arguments %ld\n", argc);
    //  if ( argc == 1 ) {
    //      fprintf(stderr, "Falta l'argument del nom del model en OBJ\n");
    //      exit( 1 );
    //  }
    //  printf("L'argument 1 és %s\n", argv[1]);
    // 
    //  strcpy( nomModel_c, "codic.c" );    
    //  strcpy( nomModel_h, "codic.h" );
    //  printf("Convertint OBJ %s a fitxer en C es diu: %s i %s\n", argv[1], nomModel_c,nomModel_h);
    
    
    if  (argc == 4) {
        strcpy( nomModel_c, argv[2] );    
        strcpy( nomModel_h, argv[3] );
        printf("Convertint OBJ %s a fitxer en C es diu: %s i %s\n", argv[1], nomModel_c,nomModel_h);
        printf("== 4: Convertint OBJ %s a fitxer en C es diu: %s i %s\n", argv[1], nomModel_c,nomModel_h);
        
    }
    else {
        printf("Es gasta: %s fitxer.obj fitxer.c fitxer.h\n", argv[0]);
        printf("Retorna:\n\
0 en cas de poder fer la conversió\n\        
1 en cas de falta de parámetres\n\
2 en cas de falta de format de la definició de cares con a triangles\n\
3 en cas de no poder llegir l'OBJ\n");
        exit( 1 );
        // Podria tratar el generar els noms dels fitxers de còdic, però ja eixien molts línies i no cal robar-li protagoniste al que toca ;-)
        //  if  (argc < 4) {
        //   strcpy( nomModel_c, argv[2] );    
        //    printf("< 4 Convertint OBJ %s a fitxer en C es diu: %s i %s\n", argv[1], nomModel_c,nomModel_h);
        // 
        //  }
        //  else {
        //  if  (argc < 3) {
        //      // int n = sscanf(argv[1], "%s.obj",  nomModel);
        //  strcpy( nomModel_c, argv[1] );  
        //  if( ( p = strstr(nomModel_c, ".obj") ) == NULL ){
        //      fprintf(stderr, "No topete l'extensió OBJ en %s\n", argv[1] );
        //  }
        //  strcpy( p, ".c  ");
        //  printf(".c: Convertint OBJ %s a fitxer en C es diu: %s i %s\n", argv[1], nomModel_c,nomModel_h);
        // 
        //  strcpy( nomModel_h, argv[1] );  
        //  if( ( p = strstr(nomModel_h, ".obj") ) == NULL ){
        //      fprintf(stderr, "No topete l'extensió OBJ en %s\n", argv[1] );
        //  }
        //  strcpy( p, ".h  ");
        //   }
        //  printf("Convertint OBJ %s a fitxer en C es diu: %s i %s\n", argv[1], nomModel_c,nomModel_h);
        //  }
    }
    //
    //
    //   exit(0);
    //
    //
    
    
    if ( getOBJinfo( argv[1], &nVertices, &nVTextura, &nNormals, &nCares ) ) {
        printf("Model %s té \n %ld vertex\n %ld nVTextura (texels)\n %ld Normals\n %ld Cares triangulars\n", argv[1], nVertices, nVTextura, nNormals, nCares);
        // Comprobacions
        printf(" %ld Cares triangulars == %ld Normals * 2 = %ld?\n", nCares, nNormals, nNormals*2);
        printf(" %ld posicions en la malla == %ld Cares triangulars * 3?\n", nCares*3, nCares );
        
        
        // Ara ja pots dimensionar les estructures de dades i tornar a llegir el fitxer, buscant el tipos de linies que saps que te i omplint els vectors
        // Ara vull poder mostrar les posicioms: 
        // 1a versió imprimint-ho en eixida estàndar
        volcartRejillaOBJ( argv[1], nVertices, nVTextura, nNormals, nCares, nomModel_c, nomModel_h );
        
        // 2a versió: Guardant-ho en una estructura de dades
        //  obtindreModelOBJ( argv[1], nVertices, nNormals, nCares );
        return( 0 );
        
        
    }
    else {
        printf("No he pogut llegir el model de %s\n", argv[1]);
        return( 3 );
    }
    
} // main
