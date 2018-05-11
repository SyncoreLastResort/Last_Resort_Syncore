#include "Globals.h"
#include "Application.h"
#include "Animation.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleLevel1.h"
#include "ModulePlayer.h"
#include "ModulePlayer2.h"
#include "ModuleFadeToBlack.h"
#include "ModuleSceneIntro.h"
#include "ModuleBall.h"


ModuleSceneIntro::ModuleSceneIntro()
{
	introrect.x = 0;
	introrect.y = 0;
	introrect.w = 320;
	introrect.h = 224;
	
	intro_neogeo.Reset();
	max330.Reset();
	mega_pro.Reset();
	SNK.Reset();
	C_sprite.Reset();
	L_Anim.Reset();
	A_Anim.Reset();
	S_Anim.Reset();
	T_Anim.Reset();
	R_Anim.Reset();
	E_Anim.Reset();
	O_Anim.Reset();

	////NeoGeo
	//intro_neogeo.PushBack({ 0, 0, 39, 40 });
	//intro_neogeo.PushBack({ 38, 0, 39, 40 });
	//intro_neogeo.PushBack({ 77, 0, 66, 40 });
	//intro_neogeo.PushBack({ 143, 0, 68, 40 });
	//intro_neogeo.PushBack({ 211, 0, 85, 40 });
	//intro_neogeo.PushBack({ 296, 0, 100, 40 });
	//intro_neogeo.PushBack({ 396, 0, 112, 40 });
	//intro_neogeo.PushBack({ 508, 0, 127, 40 });
	//intro_neogeo.PushBack({ 635, 0, 141, 40 });
	//intro_neogeo.PushBack({ 776, 0, 156, 40 });
	//intro_neogeo.PushBack({ 0, 40, 168, 40 });
	//intro_neogeo.PushBack({ 169, 40, 186, 40 });
	//intro_neogeo.PushBack({ 355, 40, 199, 40 });
	//intro_neogeo.PushBack({ 554, 40, 210, 40 });
	//intro_neogeo.PushBack({ 766, 40, 227, 40 });
	//intro_neogeo.PushBack({ 0, 82, 227, 36 });
	//intro_neogeo.PushBack({ 227, 82, 227, 36 });
	//intro_neogeo.PushBack({ 454, 82, 227, 36 });
	//intro_neogeo.PushBack({ 681, 82, 227, 36 });
	//intro_neogeo.PushBack({ 0, 118, 227, 28 });
	//intro_neogeo.PushBack({ 227, 118, 227, 28 });
	//intro_neogeo.PushBack({ 454, 118, 227, 28 });
	//intro_neogeo.PushBack({ 681, 118, 227, 28 });
	//intro_neogeo.PushBack({ 0, 146, 227, 18 });
	//intro_neogeo.PushBack({ 227, 146, 227, 18 });
	//intro_neogeo.PushBack({ 454, 146, 224, 18 });
	//intro_neogeo.PushBack({ 678, 146, 227, 18 });
	//intro_neogeo.PushBack({ 0, 164, 224, 9 });
	//intro_neogeo.PushBack({ 227, 164, 221, 9 });
	//intro_neogeo.PushBack({ 454, 164, 227, 9 });
	//intro_neogeo.PushBack({ 680, 164, 227, 9 });
	//intro_neogeo.PushBack({ 0, 387, 221, 9 });
	//intro_neogeo.PushBack({ 221, 387, 224, 9});
	//intro_neogeo.PushBack({ 446, 387, 224, 9 });
	//intro_neogeo.PushBack({ 670, 387, 227, 10 });
	//intro_neogeo.PushBack({ 0, 399, 227, 12 });
	//intro_neogeo.PushBack({ 227, 399, 224, 19 });
	//intro_neogeo.PushBack({ 454, 399, 224, 19});
	//intro_neogeo.PushBack({ 681, 399, 227, 19 });
	//intro_neogeo.PushBack({ 0, 419, 227, 29 });
	//intro_neogeo.PushBack({ 227, 419, 227, 29 });
	//intro_neogeo.PushBack({ 454, 419, 227, 29 });
	//intro_neogeo.PushBack({ 681, 419, 227, 29 });
	//intro_neogeo.PushBack({ 0, 448, 227, 40 });
	//intro_neogeo.PushBack({ 227, 448, 227, 40 });
	//intro_neogeo.PushBack({ 454, 448, 227, 40 });
	//intro_neogeo.PushBack({ 681, 448, 227, 40 });
	//intro_neogeo.loop = false;
	//intro_neogeo.speed = 0.5f;

	////Max330
	//max330.PushBack({ 0, 0, 10, 15 });
	//max330.PushBack({ 0, 0, 20, 15 });
	//max330.PushBack({ 0, 0, 30, 15 });
	//max330.PushBack({ 0, 0, 40, 15 });
	//max330.PushBack({ 0, 0, 50, 15 });
	//max330.PushBack({ 0, 0, 60, 15 });
	//max330.PushBack({ 0, 0, 70, 15 });
	//max330.PushBack({ 0, 0, 80, 15 });
	//max330.PushBack({ 0, 0, 90, 15 });
	//max330.PushBack({ 0, 0, 100, 15 });
	//max330.PushBack({ 0, 0, 110, 15 });
	//max330.PushBack({ 0, 0, 120, 15 });
	//max330.PushBack({ 0, 0, 130, 15 });
	//max330.PushBack({ 0, 0, 133, 15 });
	//max330.loop = false;
	//max330.speed = 0.3f;

	////MegaPro
	//mega_pro.PushBack({ 0, 0, 10, 15 });
	//mega_pro.PushBack({ 0, 0, 20, 15 });
	//mega_pro.PushBack({ 0, 0, 30, 15 });
	//mega_pro.PushBack({ 0, 0, 40, 15 });
	//mega_pro.PushBack({ 0, 0, 50, 15 });
	//mega_pro.PushBack({ 0, 0, 60, 15 });
	//mega_pro.PushBack({ 0, 0, 70, 15 });
	//mega_pro.PushBack({ 0, 0, 80, 15 });
	//mega_pro.PushBack({ 0, 0, 90, 15 });
	//mega_pro.PushBack({ 0, 0, 100, 15 });
	//mega_pro.PushBack({ 0, 0, 110, 15 });
	//mega_pro.PushBack({ 0, 0, 120, 15 });
	//mega_pro.PushBack({ 0, 0, 130, 15 });
	//mega_pro.PushBack({ 0, 0, 133, 15 });
	//mega_pro.loop = false;
	//mega_pro.speed = 0.3f;

	////SNK
	//SNK.PushBack({ 216, 0, 72, 18 });
	//SNK.PushBack({ 288, 0, 72, 18 });
	//SNK.PushBack({ 360, 0, 72, 18 });
	//SNK.PushBack({ 432, 0, 72, 18 });
	//SNK.PushBack({ 0, 19, 72, 18 });
	//SNK.PushBack({ 72, 19, 72, 18 });
	//SNK.PushBack({ 144, 19, 72, 18 });
	//SNK.PushBack({ 216, 19, 72, 18 });
	//SNK.PushBack({ 288, 19, 72, 18 });
	//SNK.PushBack({ 360, 19, 72, 18 });
	//SNK.PushBack({ 432, 19, 72, 18 });
	//SNK.PushBack({ 0, 38, 72, 18 });
	//SNK.PushBack({ 72, 38, 72, 18 });
	//SNK.PushBack({ 144, 38, 72, 18 });
	//SNK.PushBack({ 216, 38, 72, 18 });
	//SNK.PushBack({ 288, 38, 72, 18 });
	//SNK.PushBack({ 360, 38, 72, 18 });
	//SNK.loop = false;
	//SNK.speed = 0.3f;

	////C
	//C_sprite.PushBack({ 693, 928, 240, 40 });
	//C_sprite.PushBack({ 693, 928, 240, 40 });
	//C_sprite.PushBack({ 693, 928, 240, 40 });
	//C_sprite.PushBack({ 693, 928, 240, 40 });
	//C_sprite.PushBack({ 693, 928, 240, 40 });
	//C_sprite.speed = 0.1f;

	//L
	L_Anim.PushBack({ 341, 297, 21, 121});
	L_Anim.PushBack({ 320, 297, 21, 121 });
	L_Anim.PushBack({ 299, 297, 21, 121 });
	L_Anim.PushBack({ 276, 297, 23, 121 });
	L_Anim.PushBack({ 253, 297, 23, 121 });
	L_Anim.PushBack({ 230, 297, 23, 121 });
	L_Anim.PushBack({ 207, 297, 23, 121 });
	L_Anim.PushBack({ 184, 297, 23, 121 });
	L_Anim.PushBack({ 161, 297, 23, 121 });
	L_Anim.PushBack({ 137, 297, 23, 121 });
	L_Anim.PushBack({ 92, 297, 32, 121 });
	L_Anim.PushBack({ 46, 297, 40, 121 });
	L_Anim.PushBack({ 0, 297, 45, 121 });
	L_Anim.PushBack({ 425, 171, 32, 126 });
	L_Anim.PushBack({ 374, 171, 48, 126 });
	L_Anim.PushBack({ 328, 171, 46, 126 });
	L_Anim.PushBack({ 280, 171, 48, 126 });
	L_Anim.PushBack({ 232, 171, 48, 126 });
	L_Anim.PushBack({ 189, 171, 43, 126 });
	L_Anim.PushBack({ 141, 171, 48, 126 });
	L_Anim.PushBack({ 94, 171, 47, 126 });
	L_Anim.PushBack({ 47, 171, 47, 126 });
	L_Anim.PushBack({ 0, 171, 46, 126 });
	L_Anim.PushBack({ 414, 114, 46, 57 });
	L_Anim.PushBack({ 414, 114, 46, 57 });
	L_Anim.PushBack({ 414, 114, 46, 57 });
	L_Anim.PushBack({ 414, 114, 46, 57 });
	L_Anim.PushBack({ 414, 114, 46, 57 });
	L_Anim.PushBack({ 414, 114, 46, 57 });
	L_Anim.PushBack({ 414, 114, 46, 57 });
	L_Anim.PushBack({ 414, 114, 46, 57 });
	L_Anim.PushBack({ 414, 114, 46, 57 });
	L_Anim.PushBack({ 414, 114, 46, 57 });
	L_Anim.PushBack({ 414, 114, 46, 57 });
	L_Anim.PushBack({ 414, 114, 46, 57 });
	L_Anim.PushBack({ 414, 114, 46, 57 });
	L_Anim.PushBack({ 414, 114, 46, 57 });
	L_Anim.PushBack({ 414, 114, 46, 57 });
	L_Anim.PushBack({ 414, 114, 46, 57 });
	L_Anim.PushBack({ 414, 114, 46, 57 });
	L_Anim.PushBack({ 414, 114, 46, 57 });
	L_Anim.PushBack({ 414, 114, 46, 57 });
	L_Anim.PushBack({ 414, 114, 46, 57 });
	L_Anim.PushBack({ 414, 114, 46, 57 });
	L_Anim.PushBack({ 414, 114, 46, 57 });
	L_Anim.PushBack({ 414, 114, 46, 57 });
	L_Anim.PushBack({ 414, 114, 46, 57 });
	L_Anim.PushBack({ 414, 114, 46, 57 });
	L_Anim.PushBack({ 414, 114, 46, 57 });
	L_Anim.PushBack({ 414, 114, 46, 57 });
	L_Anim.PushBack({ 414, 114, 46, 57 });
	L_Anim.PushBack({ 414, 114, 46, 57 });
	L_Anim.PushBack({ 414, 114, 46, 57 });
	L_Anim.PushBack({ 414, 114, 46, 57 });
	L_Anim.PushBack({ 414, 114, 46, 57 });
	L_Anim.PushBack({ 414, 114, 46, 57 });
	L_Anim.PushBack({ 414, 114, 46, 57 });
	L_Anim.PushBack({ 414, 114, 46, 57 });
	L_Anim.PushBack({ 414, 114, 46, 57 });
	L_Anim.PushBack({ 414, 114, 46, 57 });
	L_Anim.PushBack({ 414, 114, 46, 57 });
	L_Anim.PushBack({ 414, 114, 46, 57 });
	L_Anim.PushBack({ 414, 114, 46, 57 });
	L_Anim.PushBack({ 414, 114, 46, 57 });
	L_Anim.PushBack({ 414, 114, 46, 57 });
	L_Anim.PushBack({ 414, 114, 46, 57 });
	L_Anim.PushBack({ 414, 114, 46, 57 });
	L_Anim.PushBack({ 414, 114, 46, 57 });
	L_Anim.PushBack({ 414, 114, 46, 57 });
	L_Anim.PushBack({ 368, 114, 46, 57 });
	L_Anim.PushBack({ 322, 114, 46, 57 });
	L_Anim.PushBack({ 276, 114, 46, 57 });
	L_Anim.PushBack({ 230, 114, 46, 57 });
	L_Anim.PushBack({ 184, 114, 46, 57 });
	L_Anim.PushBack({ 138, 114, 46, 57 });
	L_Anim.PushBack({ 92, 114, 46, 57 });
	L_Anim.PushBack({ 46, 114, 46, 57 });
	L_Anim.PushBack({ 0, 114, 46, 57 });
	L_Anim.PushBack({ 414, 57, 46, 57 });
	L_Anim.PushBack({ 368, 57, 46, 57 });
	L_Anim.PushBack({ 322, 57, 46, 57 });
	L_Anim.PushBack({ 276, 57, 46, 57 });
	L_Anim.PushBack({ 230, 57, 46, 57 });
	L_Anim.PushBack({ 184, 57, 46, 57 });
	L_Anim.PushBack({ 138, 57, 46, 57 });
	L_Anim.PushBack({ 92, 57, 46, 57 });
	L_Anim.PushBack({ 46, 57, 46, 57 });
	L_Anim.PushBack({ 0, 57, 46, 57 });
	L_Anim.PushBack({ 414, 0, 46, 57 });
	L_Anim.PushBack({ 368, 0, 46, 57 });
	L_Anim.PushBack({ 322, 0, 46, 57 });
	L_Anim.PushBack({ 276, 0, 46, 57 });
	L_Anim.PushBack({ 230, 0, 46, 57 });
	L_Anim.PushBack({ 184, 0, 46, 57 });
	L_Anim.PushBack({ 138, 0, 46, 57 });
	L_Anim.PushBack({ 92, 0, 46, 57 });
	L_Anim.PushBack({ 46, 0, 46, 57 });
	L_Anim.PushBack({ 0, 0, 46, 57 });
	L_Anim.PushBack({ 46, 0, 46, 57 });
	L_Anim.PushBack({ 92, 0, 46, 57 });
	L_Anim.PushBack({ 138, 0, 46, 57 });
	L_Anim.PushBack({ 184, 0, 46, 57 });
	L_Anim.PushBack({ 230, 0, 46, 57 });
	L_Anim.PushBack({ 276, 0, 46, 57 });
	L_Anim.PushBack({ 322, 0, 46, 57 });
	L_Anim.PushBack({ 368, 0, 46, 57 });
	L_Anim.PushBack({ 414, 0, 46, 57 });
	L_Anim.PushBack({ 0, 57, 46, 57 });
	L_Anim.PushBack({ 46, 57, 46, 57 });
	L_Anim.PushBack({ 92, 57, 46, 57 });
	L_Anim.PushBack({ 138, 57, 46, 57 });
	L_Anim.PushBack({ 184, 57, 46, 57 });
	L_Anim.PushBack({ 230, 57, 46, 57 });
	L_Anim.PushBack({ 276, 57, 46, 57 });
	L_Anim.PushBack({ 322, 57, 46, 57 });
	L_Anim.PushBack({ 368, 57, 46, 57 });
	L_Anim.PushBack({ 414, 57, 46, 57 });
	L_Anim.PushBack({ 0, 114, 46, 57 });
	L_Anim.PushBack({ 46, 114, 46, 57 });
	L_Anim.PushBack({ 92, 114, 46, 57 });
	L_Anim.PushBack({ 138, 114, 46, 57 });
	L_Anim.PushBack({ 184, 114, 46, 57 });
	L_Anim.PushBack({ 230, 114, 46, 57 });
	L_Anim.PushBack({ 276, 114, 46, 57 });
	L_Anim.PushBack({ 322, 114, 46, 57 });
	L_Anim.PushBack({ 368, 114, 46, 57 });
	L_Anim.loop = false;
	L_Anim.speed = 0.3f;

	//A
	A_Anim.PushBack({ 495, 277, 12, 122 });
	A_Anim.PushBack({ 495, 277, 12, 122 });
	A_Anim.PushBack({ 495, 277, 12, 122 });
	A_Anim.PushBack({ 495, 277, 12, 122 });
	A_Anim.PushBack({ 495, 277, 12, 122 });
	A_Anim.PushBack({ 495, 277, 12, 122 });
	A_Anim.PushBack({ 495, 277, 12, 122 });
	A_Anim.PushBack({ 483, 277, 12, 122 });
	A_Anim.PushBack({ 471, 277, 12, 122 });
	A_Anim.PushBack({ 458, 277, 13, 122 });
	A_Anim.PushBack({ 445, 277, 13, 122 });
	A_Anim.PushBack({ 432, 277, 13, 122 });
	A_Anim.PushBack({ 419, 277, 13, 122 });
	A_Anim.PushBack({ 406, 277, 13, 122 });
	A_Anim.PushBack({ 393, 277, 13, 122 });
	A_Anim.PushBack({ 375, 277, 18, 122 });
	A_Anim.PushBack({ 356, 277, 18, 122 });
	A_Anim.PushBack({ 338, 277, 18, 122 });
	A_Anim.PushBack({ 317, 277, 21, 122 });
	A_Anim.PushBack({ 295, 277, 22, 122 });
	A_Anim.PushBack({ 272, 277, 23, 122 });
	A_Anim.PushBack({ 248, 277, 24, 122 });
	A_Anim.PushBack({ 216, 277, 32, 122 });
	A_Anim.PushBack({ 173, 277, 43, 122 });
	A_Anim.PushBack({ 132, 277, 41, 122 });
	A_Anim.PushBack({ 93, 277, 39, 122 });
	A_Anim.PushBack({ 50, 277, 43, 122 });
	A_Anim.PushBack({ 0, 277, 49, 122 });
	A_Anim.PushBack({ 457, 171, 51, 106 });
	A_Anim.PushBack({ 406, 171, 51, 106 });
	A_Anim.PushBack({ 356, 171, 51, 106 });
	A_Anim.PushBack({ 305, 171, 51, 106 });
	A_Anim.PushBack({ 254, 171, 51, 106 });
	A_Anim.PushBack({ 203, 171, 51, 106 });
	A_Anim.PushBack({ 152, 171, 51, 106 });
	A_Anim.PushBack({ 101, 171, 51, 106 });
	A_Anim.PushBack({ 50, 171, 51, 106 });
	A_Anim.PushBack({ 0, 171, 50, 106 });
	A_Anim.PushBack({ 0, 171, 50, 106 });
	A_Anim.PushBack({ 0, 171, 50, 106 });
	A_Anim.PushBack({ 0, 171, 50, 106 });
	A_Anim.PushBack({ 0, 171, 50, 106 });
	A_Anim.PushBack({ 0, 171, 50, 106 });
	A_Anim.PushBack({ 0, 171, 50, 106 });
	A_Anim.PushBack({ 0, 171, 50, 106 });
	A_Anim.PushBack({ 0, 171, 50, 106 });
	A_Anim.PushBack({ 0, 171, 50, 106 });
	A_Anim.PushBack({ 0, 171, 50, 106 });
	A_Anim.PushBack({ 0, 171, 50, 106 });
	A_Anim.PushBack({ 0, 171, 50, 106 });
	A_Anim.PushBack({ 0, 171, 50, 106 });
	A_Anim.PushBack({ 0, 171, 50, 106 });
	A_Anim.PushBack({ 0, 171, 50, 106 });
	A_Anim.PushBack({ 0, 171, 50, 106 });
	A_Anim.PushBack({ 0, 171, 50, 106 });
	A_Anim.PushBack({ 0, 171, 50, 106 });
	A_Anim.PushBack({ 0, 171, 50, 106 });
	A_Anim.PushBack({ 0, 171, 50, 106 });
	A_Anim.PushBack({ 0, 171, 50, 106 });
	A_Anim.PushBack({ 0, 171, 50, 106 });
	A_Anim.PushBack({ 0, 171, 50, 106 });
	A_Anim.PushBack({ 0, 171, 50, 106 });
	A_Anim.PushBack({ 0, 171, 50, 106 });
	A_Anim.PushBack({ 0, 171, 50, 106 });
	A_Anim.PushBack({ 0, 171, 50, 106 });
	A_Anim.PushBack({ 0, 171, 50, 106 });
	A_Anim.PushBack({ 0, 171, 50, 106 });
	A_Anim.PushBack({ 0, 171, 50, 106 });
	A_Anim.PushBack({ 0, 171, 50, 106 });
	A_Anim.PushBack({ 450, 114, 50, 57 });
	A_Anim.PushBack({ 400, 114, 50, 57 });
	A_Anim.PushBack({ 350, 114, 50, 57 });
	A_Anim.PushBack({ 300, 114, 50, 57 });
	A_Anim.PushBack({ 250, 114, 50, 57 });
	A_Anim.PushBack({ 200, 114, 50, 57 });
	A_Anim.PushBack({ 150, 114, 50, 57 });
	A_Anim.PushBack({ 100, 114, 50, 57 });
	A_Anim.PushBack({ 50, 114, 50, 57 });
	A_Anim.PushBack({ 0, 114, 50, 57 });
	A_Anim.PushBack({ 450, 57, 50, 57 });
	A_Anim.PushBack({ 400, 57, 50, 57 });
	A_Anim.PushBack({ 350, 57, 50, 57 });
	A_Anim.PushBack({ 300, 57, 50, 57 });
	A_Anim.PushBack({ 250, 57, 50, 57 });
	A_Anim.PushBack({ 200, 57, 50, 57 });
	A_Anim.PushBack({ 150, 57, 50, 57 });
	A_Anim.PushBack({ 100, 57, 50, 57 });
	A_Anim.PushBack({ 50, 57, 50, 57 });
	A_Anim.PushBack({ 0, 57, 50, 57 });
	A_Anim.PushBack({ 450, 0, 50, 57 });
	A_Anim.PushBack({ 400, 0, 50, 57 });
	A_Anim.PushBack({ 350, 0, 50, 57 });
	A_Anim.PushBack({ 300, 0, 50, 57 });
	A_Anim.PushBack({ 250, 0, 50, 57 });
	A_Anim.PushBack({ 200, 0, 50, 57 });
	A_Anim.PushBack({ 150, 0, 50, 57 });
	A_Anim.PushBack({ 100, 0, 50, 57 });
	A_Anim.PushBack({ 50, 0, 50, 57 });
	A_Anim.PushBack({ 0, 0, 50, 57 });
	A_Anim.PushBack({ 50, 0, 50, 57 });
	A_Anim.PushBack({ 100, 0, 50, 57 });
	A_Anim.PushBack({ 150, 0, 50, 57 });
	A_Anim.PushBack({ 200, 0, 50, 57 });
	A_Anim.PushBack({ 250, 0, 50, 57 });
	A_Anim.PushBack({ 300, 0, 50, 57 });
	A_Anim.PushBack({ 350, 0, 50, 57 });
	A_Anim.PushBack({ 400, 0, 50, 57 });
	A_Anim.PushBack({ 450, 0, 50, 57 });
	A_Anim.PushBack({ 0, 57, 50, 57 });
	A_Anim.PushBack({ 50, 57, 50, 57 });
	A_Anim.PushBack({ 100, 57, 50, 57 });
	A_Anim.PushBack({ 150, 57, 50, 57 });
	A_Anim.PushBack({ 200, 57, 50, 57 });
	A_Anim.PushBack({ 250, 57, 50, 57 });
	A_Anim.PushBack({ 300, 57, 50, 57 });
	A_Anim.PushBack({ 350, 57, 50, 57 });
	A_Anim.PushBack({ 400, 57, 50, 57 });
	A_Anim.PushBack({ 450, 57, 50, 57 });
	A_Anim.PushBack({ 0, 114, 50, 57 });
	A_Anim.PushBack({ 50, 114, 50, 57 });
	A_Anim.PushBack({ 100, 114, 50, 57 });
	A_Anim.PushBack({ 150, 114, 50, 57 });
	A_Anim.PushBack({ 200, 114, 50, 57 });
	A_Anim.PushBack({ 250, 114, 50, 57 });
	A_Anim.PushBack({ 300, 114, 50, 57 });
	A_Anim.PushBack({ 350, 114, 50, 57 });
	A_Anim.PushBack({ 400, 114, 50, 57 });
	A_Anim.PushBack({ 450, 114, 50, 57 });
	A_Anim.PushBack({ 0, 171, 50, 106 });
	A_Anim.loop = false;
	A_Anim.speed = 0.3f;

	//S
	S_Anim.PushBack({ 78, 318, 34, 106 });
	S_Anim.PushBack({ 78, 318, 34, 106 });
	S_Anim.PushBack({ 78, 318, 34, 106 });
	S_Anim.PushBack({ 78, 318, 34, 106 });
	S_Anim.PushBack({ 78, 318, 34, 106 });
	S_Anim.PushBack({ 78, 318, 34, 106 });
	S_Anim.PushBack({ 78, 318, 34, 106 });
	S_Anim.PushBack({ 78, 318, 34, 106 });
	S_Anim.PushBack({ 78, 318, 34, 106 });
	S_Anim.PushBack({ 78, 318, 34, 106 });
	S_Anim.PushBack({ 78, 318, 34, 106 });
	S_Anim.PushBack({ 78, 318, 34, 106 });
	S_Anim.PushBack({ 78, 318, 34, 106 });
	S_Anim.PushBack({ 78, 318, 34, 106 });
	S_Anim.PushBack({ 58, 318, 34, 106 });
	S_Anim.PushBack({ 34, 318, 24, 106 });
	S_Anim.PushBack({ 0, 318, 34, 106 });
	S_Anim.PushBack({ 487, 181, 24, 137 });
	S_Anim.PushBack({ 463, 181, 24, 137 });
	S_Anim.PushBack({ 436, 181, 27, 137 });
	S_Anim.PushBack({ 407, 181, 29, 137 });
	S_Anim.PushBack({ 378, 181, 29, 137 });
	S_Anim.PushBack({ 348, 181, 30, 137 });
	S_Anim.PushBack({ 317, 181, 31, 137 });
	S_Anim.PushBack({ 284, 181, 33, 137 });
	S_Anim.PushBack({ 253, 181, 31, 137 });
	S_Anim.PushBack({ 222, 181, 31, 137 });
	S_Anim.PushBack({ 191, 181, 31, 137 });
	S_Anim.PushBack({ 160, 181, 31, 137 });
	S_Anim.PushBack({ 126, 181, 34, 137 });
	S_Anim.PushBack({ 95, 181, 31, 137 });
	S_Anim.PushBack({ 64, 181, 31, 137 });
	S_Anim.PushBack({ 32, 181, 32, 137 });
	S_Anim.PushBack({ 0, 181, 32, 137 });
	S_Anim.PushBack({ 480, 58, 32, 123 });
	S_Anim.PushBack({ 448, 58, 32, 123 });
	S_Anim.PushBack({ 416, 58, 32, 123 });
	S_Anim.PushBack({ 384, 58, 32, 123 });
	S_Anim.PushBack({ 352, 58, 32, 123 });
	S_Anim.PushBack({ 320, 58, 32, 123 });
	S_Anim.PushBack({ 288, 58, 32, 123 });
	S_Anim.PushBack({ 256, 58, 32, 123 });
	S_Anim.PushBack({ 224, 58, 32, 123 });
	S_Anim.PushBack({ 192, 58, 32, 123 });
	S_Anim.PushBack({ 160, 58, 32, 123 });
	S_Anim.PushBack({ 160, 58, 32, 123 });
	S_Anim.PushBack({ 160, 58, 32, 123 });
	S_Anim.PushBack({ 160, 58, 32, 123 });
	S_Anim.PushBack({ 160, 58, 32, 123 });
	S_Anim.PushBack({ 160, 58, 32, 123 });
	S_Anim.PushBack({ 160, 58, 32, 123 });
	S_Anim.PushBack({ 160, 58, 32, 123 });
	S_Anim.PushBack({ 160, 58, 32, 123 });
	S_Anim.PushBack({ 160, 58, 32, 123 });
	S_Anim.PushBack({ 160, 58, 32, 123 });
	S_Anim.PushBack({ 160, 58, 32, 123 });
	S_Anim.PushBack({ 160, 58, 32, 123 });
	S_Anim.PushBack({ 160, 58, 32, 123 });
	S_Anim.PushBack({ 160, 58, 32, 123 });
	S_Anim.PushBack({ 160, 58, 32, 123 });
	S_Anim.PushBack({ 160, 58, 32, 123 });
	S_Anim.PushBack({ 160, 58, 32, 123 });
	S_Anim.PushBack({ 160, 58, 32, 123 });
	S_Anim.PushBack({ 160, 58, 32, 123 });
	S_Anim.PushBack({ 160, 58, 32, 123 });
	S_Anim.PushBack({ 160, 58, 32, 123 });
	S_Anim.PushBack({ 160, 58, 32, 123 });
	S_Anim.PushBack({ 160, 58, 32, 123 });
	S_Anim.PushBack({ 160, 58, 32, 123 });

	S_Anim.PushBack({ 128, 58, 32, 123 });
	S_Anim.PushBack({ 96, 58, 32, 123 });
	S_Anim.PushBack({ 64, 58, 32, 123 });
	S_Anim.PushBack({ 32, 58, 32, 123 });
	S_Anim.PushBack({ 0, 58, 32, 123 });
	S_Anim.PushBack({ 480, 0, 32, 58 });
	S_Anim.PushBack({ 448, 0, 32, 58 });
	S_Anim.PushBack({ 416, 0, 32, 58 });
	S_Anim.PushBack({ 384, 0, 32, 58 });
	S_Anim.PushBack({ 352, 0, 32, 58 });
	S_Anim.PushBack({ 320, 0, 32, 58 });
	S_Anim.PushBack({ 288, 0, 32, 58 });
	S_Anim.PushBack({ 256, 0, 32, 58 });
	S_Anim.PushBack({ 224, 0, 32, 58 });
	S_Anim.PushBack({ 192, 0, 32, 58 });
	S_Anim.PushBack({ 160, 0, 32, 58 });
	S_Anim.PushBack({ 128, 0, 32, 58 });
	S_Anim.PushBack({ 96, 0, 32, 58 });
	S_Anim.PushBack({ 64, 0, 32, 58 });
	S_Anim.PushBack({ 32, 0, 32, 58 });
	S_Anim.PushBack({ 0, 0, 32, 58 });
	S_Anim.PushBack({ 0, 0, 32, 58 });
	S_Anim.PushBack({ 0, 0, 32, 58 });
	S_Anim.PushBack({ 0, 0, 32, 58 });
	S_Anim.PushBack({ 0, 0, 32, 58 });
	S_Anim.PushBack({ 0, 0, 32, 58 });
	S_Anim.PushBack({ 0, 0, 32, 58 });
	S_Anim.PushBack({ 0, 0, 32, 58 });
	S_Anim.PushBack({ 0, 0, 32, 58 });
	S_Anim.PushBack({ 0, 0, 32, 58 });
	S_Anim.PushBack({ 0, 0, 32, 58 });
	S_Anim.PushBack({ 0, 0, 32, 58 });
	S_Anim.PushBack({ 0, 0, 32, 58 });
	S_Anim.PushBack({ 0, 0, 32, 58 });
	S_Anim.PushBack({ 0, 0, 32, 58 });
	S_Anim.PushBack({ 0, 0, 32, 58 });
	S_Anim.PushBack({ 32, 0, 32, 58 });
	S_Anim.PushBack({ 64, 0, 32, 58 });
	S_Anim.PushBack({ 96, 0, 32, 58 });
	S_Anim.PushBack({ 128, 0, 32, 58 });
	S_Anim.PushBack({ 160, 0, 32, 58 });
	S_Anim.PushBack({ 192, 0, 32, 58 });
	S_Anim.PushBack({ 224, 0, 32, 58 });
	S_Anim.PushBack({ 256, 0, 32, 58 });
	S_Anim.PushBack({ 288, 0, 32, 58 });
	S_Anim.PushBack({ 320, 0, 32, 58 });
	S_Anim.PushBack({ 352, 0, 32, 58 });
	S_Anim.PushBack({ 384, 0, 32, 58 });
	S_Anim.PushBack({ 416, 0, 32, 58 });
	S_Anim.PushBack({ 448, 0, 32, 58 });
	S_Anim.PushBack({ 480, 0, 32, 58 });
	S_Anim.PushBack({ 0, 58, 32, 123 });
	S_Anim.PushBack({ 32, 58, 32, 123 });
	S_Anim.PushBack({ 64, 58, 32, 123 });
	S_Anim.PushBack({ 96, 58, 32, 123 });
	S_Anim.PushBack({ 128, 58, 32, 123 });
	S_Anim.PushBack({ 160, 58, 32, 123 });
	S_Anim.loop = false;
	S_Anim.speed = 0.3f;

	//T
	T_Anim.PushBack({ 376, 374, 46, 121 });
	T_Anim.PushBack({ 330, 374, 46, 121 });
	T_Anim.PushBack({ 284, 374, 46, 121 });
	T_Anim.PushBack({ 238, 374, 46, 121 });
	T_Anim.PushBack({ 192, 374, 46, 121 });
	T_Anim.PushBack({ 144, 374, 48, 121 });
	T_Anim.PushBack({ 96, 374, 48, 121 });
	T_Anim.PushBack({ 48, 374, 48, 121 });
	T_Anim.PushBack({ 0, 374, 48, 121 });
	T_Anim.PushBack({ 432, 253, 48, 121 });
	T_Anim.PushBack({ 384, 253, 48, 121 });
	T_Anim.PushBack({ 336, 253, 48, 121 });
	T_Anim.PushBack({ 288, 253, 48, 121 });
	T_Anim.PushBack({ 240, 253, 48, 121 });
	T_Anim.PushBack({ 192, 253, 48, 121 });
	T_Anim.PushBack({ 144, 253, 48, 121 });
	T_Anim.PushBack({ 96, 253, 48, 121 });
	T_Anim.PushBack({ 48, 253, 48, 121 });
	T_Anim.PushBack({ 0, 253, 48, 121 });
	T_Anim.PushBack({ 427, 125, 48, 128 });
	T_Anim.PushBack({ 379, 125, 48, 128 });
	T_Anim.PushBack({ 331, 125, 48, 128 });
	T_Anim.PushBack({ 283, 125, 48, 128 });
	T_Anim.PushBack({ 234, 125, 49, 128 });
	T_Anim.PushBack({ 185, 125, 49, 128 });
	T_Anim.PushBack({ 138, 125, 47, 128 });
	T_Anim.PushBack({ 92, 125, 46, 128 });
	T_Anim.PushBack({ 46, 125, 46, 128 });
	T_Anim.PushBack({ 0, 125, 46, 128 });

	T_Anim.PushBack({ 460, 60, 46, 65 });
	T_Anim.PushBack({ 414, 60, 46, 65 });
	T_Anim.PushBack({ 368, 60, 46, 65 });
	T_Anim.PushBack({ 322, 60, 46, 65 });
	T_Anim.PushBack({ 276, 60, 46, 65 });
	T_Anim.PushBack({ 230, 60, 46, 65 });
	T_Anim.PushBack({ 184, 60, 46, 65 });
	T_Anim.PushBack({ 138, 60, 46, 65 });
	T_Anim.PushBack({ 92, 60, 46, 65 });
	T_Anim.PushBack({ 46, 60, 46, 65 });
	T_Anim.PushBack({ 0, 60, 46, 65 });

	T_Anim.PushBack({ 460, 0, 45, 59 });
	T_Anim.PushBack({ 414, 0, 45, 59 });
	T_Anim.PushBack({ 368, 0, 45, 59 });
	T_Anim.PushBack({ 322, 0, 45, 59 });
	T_Anim.PushBack({ 276, 0, 45, 59 });
	T_Anim.PushBack({ 230, 0, 45, 59 });
	T_Anim.PushBack({ 184, 0, 45, 59 });
	T_Anim.PushBack({ 138, 0, 45, 59 });
	T_Anim.PushBack({ 92, 0, 45, 59 });
	T_Anim.PushBack({ 46, 0, 45, 59 });
	T_Anim.PushBack({ 0, 0, 45, 59 });


	T_Anim.loop = false;
	T_Anim.speed = 0.3f;





}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{
	LOG("Loading intro");
	
	introbackground = App->textures->Load("assets/sprites/Intro_Neogeo/Title_Neogeo_Begining_Sprite.png");
	black = App->textures->Load("assets/sprites/Intro_Neogeo/Black.png");
	Max330 = App->textures->Load("assets/sprites/Intro_Neogeo/MAX_330.png");
	MegaPro = App->textures->Load("assets/sprites/Intro_Neogeo/MegaPro.png");
	SNK_Logo = App->textures->Load("assets/sprites/Intro_Neogeo/SNK_Beginning_Sprite.png");
	L = App->textures->Load("assets/sprites/Intro_LogoLastResort/L_Sprite.png");
	A = App->textures->Load("assets/sprites/Intro_LogoLastResort/A_Sprite.png");
	S = App->textures->Load("assets/sprites/Intro_LogoLastResort/S_Sprite.png");
	T = App->textures->Load("assets/sprites/Intro_LogoLastResort/T_Sprite.png");
	R = App->textures->Load("assets/sprites/Intro_LogoLastResort/R_Sprite.png");
	E = App->textures->Load("assets/sprites/Intro_LogoLastResort/E_Sprite.png");
	O = App->textures->Load("assets/sprites/Intro_LogoLastResort/O_Sprite.png");


	maintrackintro = App->audio->LoadMusic("assets/music/1.Last resort title.ogg");
	
	App->render->camera.x = App->render->camera.y = 0;

	current_animation = &intro_neogeo;
	
	return true;
}

// UnLoad assets
bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading intro scene");

	App->textures->Unload(introbackground);
	App->textures->Unload(black);
	App->textures->Unload(Max330);
	App->textures->Unload(MegaPro);
	App->textures->Unload(SNK_Logo);
	App->textures->Unload(L);
	App->textures->Unload(A);
	App->textures->Unload(S);
	App->textures->Unload(T);
	App->textures->Unload(R);
	App->textures->Unload(E); 
	App->textures->Unload(O);

	/*App->audio->StopAudio();*/
	App->audio->UnloadMusic(maintrackintro);
	
	return true;
}

// Update: draw background
update_status ModuleSceneIntro::Update()
{



	// Draw everything --------------------------------------
		
	
	App->render->Blit(introbackground, 50 , 50, &(intro_neogeo.GetCurrentFrame()));
		
	/*if (intro_neogeo.Finished()){
		App->render->Blit(Max330, 90, 100, &(max330.GetCurrentFrame()));
		}
	if (max330.Finished()) {
		App->render->Blit(MegaPro, 90, 115, &(mega_pro.GetCurrentFrame()));
		}
	if (mega_pro.Finished()) {
		App->render->Blit(SNK_Logo, 125, 150, &(SNK.GetCurrentFrame()));
		}
	if (SNK.Finished()) {
		App->render->Blit(introbackground, 49, 50, &(C_sprite.GetCurrentFrame()));
	}
	if (C_sprite.Finished()) {*/
		App->render->Blit(black, 0, 0, &introrect);
		App->audio->PlayMusic(maintrackintro, ONCE);
		App->render->Blit(L, 70, 16, &(L_Anim.GetCurrentFrame()));
		App->render->Blit(A, 116, 16, &(A_Anim.GetCurrentFrame()));
		App->render->Blit(S, 168, 16, &(S_Anim.GetCurrentFrame()));
		App->render->Blit(T, 202, 16, &(T_Anim.GetCurrentFrame()));
		App->render->Blit(R, 6, 16, &(R_Anim.GetCurrentFrame()));
		App->render->Blit(E, 66, 16, &(E_Anim.GetCurrentFrame()));
		//App->render->Blit(S, 126, 16, &(S_Anim.GetCurrentFrame()));
		App->render->Blit(O, 186, 16, &(O_Anim.GetCurrentFrame()));
		//App->render->Blit(R, 246, 16, &(R_Anim.GetCurrentFrame()));
		//App->render->Blit(T, 306, 16, &(T_Anim.GetCurrentFrame()));
	//}
	

	if(App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_DOWN && App->fade->IsFading() == false)
	{
		Mix_FadeOutMusic(1000);
		App->fade->FadeToBlack(this, (Module*)App->level4); 
		App->audio->StopAudio();
	}

	return UPDATE_CONTINUE;
}