#include <3ds.h>
#include <citro3d.h>
#include <string.h>
// Modificacio 2
#include <stdio.h> // printf
//
#include "vshader_shbin.h"
#include "lenny.h"

// #define CLEAR_COLOR 0x68B0D8FF
// Modificacio 1
#define CLEAR_COLOR 0x000000FF // Si el vols negre
//

#define DISPLAY_TRANSFER_FLAGS \
	(GX_TRANSFER_FLIP_VERT(0) | GX_TRANSFER_OUT_TILED(0) | GX_TRANSFER_RAW_COPY(0) | \
	GX_TRANSFER_IN_FORMAT(GX_TRANSFER_FMT_RGBA8) | GX_TRANSFER_OUT_FORMAT(GX_TRANSFER_FMT_RGB8) | \
	GX_TRANSFER_SCALING(GX_TRANSFER_SCALE_NO))

static DVLB_s* vshader_dvlb;
static shaderProgram_s program;
static int uLoc_projection, uLoc_modelView;
static C3D_Mtx projection;

static C3D_LightEnv lightEnv;
static C3D_Light light;
static C3D_LightLut lut_Spec;

static void* vbo_data;
static float angleX = 0.0, angleY = 0.0;

// Modificancions 1
float posModelZ = -15.0f;

 C3D_Material material = // /opt/devkitpro/libctru/include/c3d/light.h
	{
// 		{ 0.0f, 0.0f, 0.0f }, //ambient             --> Ks
// 	    { 0.0f, 0.0f, 0.0f }, //diffuse  BGR!       --> Kd
// 		{ 0.5f, 0.5f, 0.5f }, //specular0           --> Ks
// 		{ 0.0f, 0.0f, 0.0f }, //specular1           --> Ke
// 		{ 0.0f, 0.0f, 0.0f }, //emission
		// Original
        { 0.1f, 0.1f, 0.1f }, //ambient
        { 0.4f, 0.4f, 0.4f }, //diffuse
        { 0.5f, 0.5f, 0.5f }, //specular0
        { 0.0f, 0.0f, 0.0f }, //specular1
        { 0.0f, 0.0f, 0.0f }, //emission
	};

  char *material_etiqueta[5] = 
	{
		"ambient",
		"diffuse",
		"specular0",
		"specular1",
		"emission"
	};

	
 int idMaterial = 0;
#define N_MATERIALS 9
char *materials_noms[N_MATERIALS] = {
		"lenny original",
		"emerald",
		"pearl",
		"bronze",
		"gold",
		"cyan plastic",
		"red plastic",
		"green rubber",
		"yellow rubber"
 };
 C3D_Material materials[N_MATERIALS] = {
	 { // 0 - Original Lenny
        { 0.1f, 0.1f, 0.1f }, //ambient
        { 0.4f, 0.4f, 0.4f }, //diffuse
        { 0.5f, 0.5f, 0.5f }, //specular0
        { 0.0f, 0.0f, 0.0f }, //specular1
        { 0.0f, 0.0f, 0.0f }, //emission	 },
	 },
	 { // Emerald
        { 0.0215f, 0.1745f, 0.0215f },    //Ambient
        { 0.07568f, 0.61424f, 0.07568f }, //Diffuse
        { 0.633f, 0.727811f, 0.633f},     // Specular
        { 0.6f, 0.6f, 0.6f },             //specular1
        { 0.0f, 0.0f, 0.0f },             //emission
	 },
	 { // Pearl	 
        { 0.25f, 	0.20725f, 	0.20725f },     // Ambient
        { 1.0f, 	0.829f, 	0.829f },  // Diffuse
        { 0.296648f, 	0.296648f, 	0.296648f}, // Specular
        { 0.088f, 0.088f, 0.088f },               // specular1
        { 0.0f, 0.0f, 0.0f },               // emission
	 },	 
	 { // Bronze
        {  	 0.2125f, 	0.1275f,	0.054f },     // Ambient
        { 0.714f, 	0.4284f, 	0.18144f },  // Diffuse
        { 0.393548f, 	0.271906f, 	0.166721f}, // Specular
        { 0.2f, 0.2f, 0.2f },               // specular1
        { 0.0f, 0.0f, 0.0f },               // emission
	 },
	 { // Gold
        { 0.24725f, 0.1995f, 0.0745f },     // Ambient
        { 0.75164f, 0.60648f, 0.022648f },  // Diffuse
        { 0.628281f, 0.555802f, 0.366065f}, // Specular
        { 0.4f, 0.4f, 0.4f },               // specular1
        { 0.0f, 0.0f, 0.0f },               // emission
	 },	 
	 { // cyan plastic 	
        { 0.0f, 	0.1f, 	0.06f },     // Ambient
        { 0.0f, 	0.50980392f, 	0.50980392f },  // Diffuse
        { 0.50196078f, 	0.50196078f, 	0.50196078f}, // Specular
        { 0.25f, 0.25f, 0.25f },               // specular1
        { 0.0f, 0.0f, 0.0f },               // emission
	 },	 
	 { // red plastic 	
        { 0.0f, 0.0f, 0.0f },     // Ambient
        { 0.5f, 0.0f, 0.0f },  // Diffuse
        { 0.7f, 0.6f, 0.6f}, // Specular
        { 0.25f, 0.25f, 0.25f },               // specular1
        { 0.0f, 0.0f, 0.0f },               // emission
	 },
	 { // green rubber 	
        { 0.0f, 0.05f, 0.0f },     // Ambient
        { 0.4f, 0.5f, 0.4f },  // Diffuse
        { 0.04f, 0.7f, 0.04}, // Specular
        { 0.078125f, 0.078125f, 0.078125f },               // specular1
        { 0.0f, 0.0f, 0.0f },               // emission
	 },
	 { // yellow rubber 	
        { 0.05f, 0.05f, 0.0f },     // Ambient
        { 0.5f, 0.5f, 0.4f },  // Diffuse
        { 0.7f, 0.7f, 0.04f}, // Specular
        { 0.078125f, 0.078125f, 0.078125f },               // specular1
        { 0.0f, 0.0f, 0.0f },               // emission
	 }
 };
	
//
	
static void sceneInit(void)
{
	// Load the vertex shader, create a shader program and bind it
	vshader_dvlb = DVLB_ParseFile((u32*)vshader_shbin, vshader_shbin_size);
	shaderProgramInit(&program);
	shaderProgramSetVsh(&program, &vshader_dvlb->DVLE[0]);
	C3D_BindProgram(&program);

	// Get the location of the uniforms
	uLoc_projection   = shaderInstanceGetUniformLocation(program.vertexShader, "projection");
	uLoc_modelView    = shaderInstanceGetUniformLocation(program.vertexShader, "modelView");

	// Configure attributes for use with the vertex shader
	C3D_AttrInfo* attrInfo = C3D_GetAttrInfo();
	AttrInfo_Init(attrInfo);
	AttrInfo_AddLoader(attrInfo, 0, GPU_FLOAT, 3); // v0=position
	AttrInfo_AddLoader(attrInfo, 1, GPU_FLOAT, 3); // v1=normal

	// Create the VBO (vertex buffer object)
	vbo_data = linearAlloc(sizeof(vertex_list));
	memcpy(vbo_data, vertex_list, sizeof(vertex_list));

	// Configure buffers
	C3D_BufInfo* bufInfo = C3D_GetBufInfo();
	BufInfo_Init(bufInfo);
	BufInfo_Add(bufInfo, vbo_data, sizeof(vertex), 2, 0x10);

	// Configure the first fragment shading substage to blend the fragment primary color
	// with the fragment secondary color.
	// See https://www.opengl.org/sdk/docs/man2/xhtml/glTexEnv.xml for more insight
	C3D_TexEnv* env = C3D_GetTexEnv(0);
	C3D_TexEnvInit(env);
	C3D_TexEnvSrc(env, C3D_Both, GPU_FRAGMENT_PRIMARY_COLOR, GPU_FRAGMENT_SECONDARY_COLOR, 0);
	C3D_TexEnvFunc(env, C3D_Both, GPU_ADD);

// Modificacions 1bis
// 	static const C3D_Material material =
// 	{
// 		{ 0.1f, 0.1f, 0.1f }, //ambient
// 		{ 0.4f, 0.4f, 0.4f }, //diffuse
// 		{ 0.5f, 0.5f, 0.5f }, //specular0
// 		{ 0.0f, 0.0f, 0.0f }, //specular1
// 		{ 0.0f, 0.0f, 0.0f }, //emission
// 	};

	C3D_LightEnvInit(&lightEnv);
	C3D_LightEnvBind(&lightEnv);
	C3D_LightEnvMaterial(&lightEnv, &material);

	LightLut_Phong(&lut_Spec, 20.0f);
	C3D_LightEnvLut(&lightEnv, GPU_LUT_D0, GPU_LUTINPUT_NH, false, &lut_Spec);

	C3D_LightInit(&light, &lightEnv);
}

static void sceneRender(float iod)
{
	// Compute the projection matrix
	Mtx_PerspStereoTilt(&projection, C3D_AngleFromDegrees(40.0f), C3D_AspectRatioTop, 0.01f, 1000.0f, iod, 2.0f, false);

	C3D_FVec objPos   = FVec4_New(0.0f, 0.0f, -3.0f, 1.0f);
	C3D_FVec lightPos = FVec4_New(0.0f, 0.0f, -0.5f, 1.0f);

	// Modificació 2
    objPos.z = posModelZ;
    //
	
	// Calculate the modelView matrix
	C3D_Mtx modelView;
	Mtx_Identity(&modelView);
	Mtx_Translate(&modelView, objPos.x, objPos.y, objPos.z, true);
	Mtx_RotateY(&modelView, C3D_Angle(angleY), true);
	Mtx_Scale(&modelView, 2.0f, 2.0f, 2.0f);

	C3D_LightPosition(&light, &lightPos);

	// Update the uniforms
	C3D_FVUnifMtx4x4(GPU_VERTEX_SHADER, uLoc_projection, &projection);
	C3D_FVUnifMtx4x4(GPU_VERTEX_SHADER, uLoc_modelView,  &modelView);

	// Draw the VBO
	C3D_DrawArrays(GPU_TRIANGLES, 0, vertex_list_count);
}

static void sceneExit(void)
{
	// Free the VBO
	linearFree(vbo_data);

	// Free the shader program
	shaderProgramFree(&program);
	DVLB_Free(vshader_dvlb);
}

// Modificacions 2

void mostraIluminant( int propMaterialLLum, int elIndex) {
    
//         //To move the cursor you have to print "\x1b[r;cH", where r and c are respectively
//         //The top screen has 30 rows and 50 columns
//         //The bottom screen has 30 rows and 40 columns
//         printf("\x1b[16;20HHello World!");

//     printf("\x1b[2J");
    printf("\x1b[4;3\n");
//     printf("          ******************************\n"); 
    printf("             %c     %c     %c\n", 
           (elIndex == 0? '*' : ' '), (elIndex == 1? '*' : ' '),  (elIndex == 2? '*' : ' ') );
    
    printf("%c %s    %1.5f, %1.5f, %1.5f\n", (propMaterialLLum == 0? '*' : ' '), 
           "ambient", material.ambient[0], material.ambient[1],material.ambient[2]);
	
    printf("%c %s    %1.5f, %1.5f, %1.5f\n", (propMaterialLLum == 1? '*' : ' '), 
           "diffuse", material.diffuse[0], material.diffuse[1],material.diffuse[2]);
    
    printf("%c %s  %1.5f, %1.5f, %1.5f\n", (propMaterialLLum == 2? '*' : ' '), 
           "specular0", material.specular0[0], material.specular0[1],material.specular0[2]);
    
    printf("%c %s  %1.5f, %1.5f, %1.5f\n", (propMaterialLLum == 3? '*' : ' '), 
           "specular1", material.specular1[0], material.specular1[1],material.specular1[2]);
    
    printf("%c %s   %1.5f, %1.5f, %1.5f\n", (propMaterialLLum == 4? '*' : ' '), 
           "emission", material.emission[0], material.emission[1],material.emission[2]);
        
    
}// void mostraIluminant() {

 int propMaterialLLum = 0,  // ambient, diffuse, specular0, specular1, emission
		elIndex=2;  // 0 B 1 G 2 R  totes de 0.0 .. 1.0

void canviaMaterial(int idMaterial) {
 int i;
 
//  for(i=0; i < 5*3; i++)
// 	material[i] = materials[idMaterial][i];	

 for(i=0; i < 3; i++)   material.ambient[i] = materials[idMaterial].ambient[2-i];
 for(i=0; i < 3; i++)   material.diffuse[i] = materials[idMaterial].diffuse[2-i];
 for(i=0; i < 3; i++)   material.specular0[i] = materials[idMaterial].specular0[2-i];
 for(i=0; i < 3; i++)   material.specular1[i] = materials[idMaterial].specular1[2-i];
 for(i=0; i < 3; i++)   material.emission[i] = materials[idMaterial].emission[2-i];
	
}
		
		
int main()
{
	// Initialize graphics
	gfxInitDefault();
	gfxSet3D(true); // Enable stereoscopic 3D
	consoleInit(GFX_BOTTOM, NULL);
	C3D_Init(C3D_DEFAULT_CMDBUF_SIZE);

	// Initialize the render targets
	C3D_RenderTarget* targetLeft  = C3D_RenderTargetCreate(240, 400, GPU_RB_RGBA8, GPU_RB_DEPTH24_STENCIL8);
	C3D_RenderTarget* targetRight = C3D_RenderTargetCreate(240, 400, GPU_RB_RGBA8, GPU_RB_DEPTH24_STENCIL8);
	C3D_RenderTargetSetOutput(targetLeft,  GFX_TOP, GFX_LEFT,  DISPLAY_TRANSFER_FLAGS);
	C3D_RenderTargetSetOutput(targetRight, GFX_TOP, GFX_RIGHT, DISPLAY_TRANSFER_FLAGS);

	// Initialize the scene
	sceneInit();

	// Main loop
	while (aptMainLoop())
	{		
		hidScanInput();

		// Respond to user input
		u32 kDown = hidKeysDown();
		u32 kHeld = hidKeysHeld();
		if (kDown & KEY_START)
			break; // break in order to return to hbmenu

		float slider = osGet3DSliderState();
		float iod = slider/3;

		// Rotate the model
		if (!(kHeld & KEY_A))
		{
			angleX += 1.0f/64;
			angleY += 1.0f/256;
//        		// Modificació 2
// 			printf("\x1b[12;3\n");
// 			printf("aX %2.2f, aY %2.2f, posZ %2.2f\n", angleX, angleY, posModelZ);		
		}

		// Modifiació 2
		// Moure the model: https://github.com/devkitPro/citro3d/blob/master/include/c3d/types.h
		if (kHeld & KEY_UP) //Up ó T
		{
  	      posModelZ += 0.1;
//           // Modificació 2: Per vore-ho
// 		  printf("\x1b[12;3\n");
// 		  printf("aX %2.2f, aY %2.2f, posZ %2.2f\n", angleX, angleY, posModelZ);
		}
		// Moure the mode
		if (kHeld & KEY_DOWN) // Down ó G
		{
  	      posModelZ -= 0.1;
//           // Modificació 2: Per vore-ho
// 		  printf("\x1b[12;3\n");
// 		  printf("aX %2.2f, aY %2.2f, posZ %2.2f\n", angleX, angleY, posModelZ);
		}


        if (kDown & KEY_Y)  // Y
		{
			propMaterialLLum = ((propMaterialLLum+1) % 5);
//        		mostraIluminant(propMaterialLLum, elIndex);
		}
     	if ((kDown & KEY_X))  // X
		{
			elIndex = ((elIndex+1) % 3);
//        		mostraIluminant(propMaterialLLum, elIndex);
		}
      
		if ((kDown & KEY_RIGHT)) // Right i G
		{
            switch (propMaterialLLum) {
                case 0:
                    material.ambient[elIndex] += 0.1f;
                    break;
                case 1:
                    material.diffuse[elIndex] += 0.1f;
                    break;
                case 2:
                    material.specular0[elIndex] += 0.1f;
                    break;
                case 3:
                    material.specular1[elIndex] += 0.1f;
                    break;
                case 4:
                    material.emission[elIndex] += 0.1f;
                    break;
            }  	      
          	C3D_LightEnvMaterial(&lightEnv, &material);
//    		    mostraIluminant(propMaterialLLum, elIndex);
		}		
        
		if ((kDown & KEY_LEFT))  // Left i F
		{
            switch (propMaterialLLum) {
                case 0:
                    material.ambient[elIndex] -= 0.1f;
                    break;
                case 1:
                    material.diffuse[elIndex] -= 0.1f;
                    break;
                case 2:
                    material.specular0[elIndex] -= 0.1f;
                    break;
                case 3:
                    material.specular1[elIndex] -= 0.1f;
                    break;
                case 4:
                    material.emission[elIndex] -= 0.1f;
                    break;
            }  	      
          	C3D_LightEnvMaterial(&lightEnv, &material);
//             mostraIluminant(propMaterialLLum, elIndex);
		}

        if (kDown & KEY_B)  // B
		{
			idMaterial = ((idMaterial+1) % N_MATERIALS);
			canviaMaterial(idMaterial);
          	C3D_LightEnvMaterial(&lightEnv, &material);
		}
		
		
//           // Modificació 2: Per vore-ho
		// Modificació 2
		printf("\x1b[2J");
		//
		mostraIluminant(propMaterialLLum, elIndex);
//         printf("\x1b[21;3\n");
		printf("\x1b[15;0H[B] idMaterial = %d (%s)", idMaterial, materials_noms[idMaterial] );
		printf("\x1b[17;0H[X] RGB, [Y] propietat,\n" );
		printf("\x1b[18;0H[Left/Rigth] valor 0,1\n" );
     	printf("\x1b[21;0HaX %2.2f, aY %2.2f, posZ %2.2f\n", angleX, angleY, posModelZ );			
		
		// Render the scene
		C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
		{
			C3D_RenderTargetClear(targetLeft, C3D_CLEAR_ALL, CLEAR_COLOR, 0);
			C3D_FrameDrawOn(targetLeft);
			sceneRender(-iod);

			if (iod > 0.0f)
			{
				C3D_RenderTargetClear(targetRight, C3D_CLEAR_ALL, CLEAR_COLOR, 0);
				C3D_FrameDrawOn(targetRight);
				sceneRender(iod);
			}
		}
		C3D_FrameEnd(0);
	}

	// Deinitialize the scene
	sceneExit();

	// Deinitialize graphics
	C3D_Fini();
	gfxExit();
	return 0;
}
