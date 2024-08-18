<!--
Sintaxis README
https://docs.github.com/es/get-started/writing-on-github/getting-started-with-writing-and-formatting-on-github/basic-writing-and-formatting-syntax#hiding-content-with-comments

Tokens
https://docs.github.com/es/authentication/keeping-your-account-and-data-secure/managing-your-personal-access-tokens
-->
# 3DS-homebrew-development
Homebrew examples for 3DS from "videoconsole development" subject.

Contents of this repo:
- Using Box2D with SDL on [3DS__SDL1_2_box2D](https://github.com/magusti/3DS-homebrew-development#3ds__sdl1_2_box2d
* Using sprites ib SDL 1.2 on [3DS__SDL1_2_box2D](https://github.com/magusti/3DS-homebrew-development#3ds_sdl1_2_sprites)
+ Loading 3D mesh OBJ files statically on [3DS_cargarMalla3D_estatica](https://github.com/magusti/3DS-homebrew-development#3ds_cargarmalla3d_estatica).



## 3DS__SDL1_2_box2D
The SDL 1.2 version of *box2D* example from **3ds-examples**.

Screenshot of 3DS example *physics/box2d* using SDL 1.2.
![Screenshot of 3DS example *physics/box2d* using SDL 1.2.](Screenshot_3DS_SDL1_2_box2D_fig.png)

## 3DS_SDL1_2_sprites
The SDL 1.2 version of *gpusprites* example from **3ds-examples**.

Screenshot of 3DS example *graphics/gpu/gpusprites* rewriting the graphic interface using SDL 1.2.
![Screenshot of 3DS example *graphics/gpu/gpusprites* rewriting the graphic interface using SDL 1.2.](Screenshot_3DS_SDL1_2_sprites_fig.png)
[Related to Switch example]().


## 3DS_cargarMalla3D_estatica
A review of *lenny* example, from **3ds-examples**, that loads an OBJ mesh choosen at compile time.

Examples of outputs from the lenny example rewrite as a 3D mesh visualizer (a) original and (b) three models converted from OBJ format to C code with "convertOBJ_toC.c".
![Ejemplos de salida en pantalla de un visualizador de mallas 3D: (a) original y (b) utilizando otros posibles modelos.](cargarMalle3D_estatica_fig1.png).

Comented in [M. Agustí. (2024). Importar mallas 3D en tiempo de compilación para una aplicación de videojuego en la 3DS. Universitat Politècnica de València](http://hdl.handle.net/10251/205403).


## Ejemplos básicos de portabilidad de aplicaciones basadas en SDL: comparativa entre plataforma Switch, escritorio y 3DS
A review of Switch examples **sdl2/sdl2-simple** y **sdl2/sdl2-demo** ported to 3DS (SDL 1.2) and Linux (PC, SDL 2.0).

Screenshot of Switch example *sdl2/sdl2-simple* and *sdl2/sdl2-demo* (upper row), 3DS (lover row, left)  and PC (lover row, right) version.
![Screenshot of Switch example sdl2/sdl2-simple and sdl2/sdl2-demo ported to 3DS and PC (Linux.](Screenshot_SDL_simple_demo_fig.png)

